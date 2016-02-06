// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "MSBuild.h"
#include "somera/Any.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <cassert>
#include <fstream>
#include <map>
#include <random>
#include <utility>
#include <sstream>
#include <string>
#include <vector>

namespace somera {
namespace {

std::string newGuid() noexcept
{
    // UUID version 4 (RFC 4122)
    std::mt19937 random(std::random_device{}());
    std::uniform_int_distribution<uint16_t> dist(0x0000, 0xffff);
    auto id = StringHelper::format(
        "%04X%04X-%04X-%04X-%04X-%04X%04X%04X",
        dist(random),
        dist(random),
        dist(random),
        (dist(random) & 0x0fff) | 0x4000,
        dist(random) % 0x3fff + 0x8000,
        dist(random),
        dist(random),
        dist(random));
    return std::move(id);
}

struct MSBuildProject {
    std::string guid;
    std::string name;
};

std::string encodeGuid(const std::string& guid)
{
    return '{' + guid + '}';
}

std::string generateSolutionFile(
    const CompileOptions& options,
    const MSBuildProject& project,
    const std::string& solutionFilePath,
    const std::string& vcxprojPath)
{
    std::stringstream stream;
    stream << "﻿\r\n";
    stream <<
        "Microsoft Visual Studio Solution File, Format Version 12.00\r\n"
        "# Visual Studio 14\r\n"
        "VisualStudioVersion = 14.0.23107.0\r\n"
        "MinimumVisualStudioVersion = 10.0.40219.1\r\n";

    constexpr auto entryTypeGuid = "8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942";

    const auto relativePath = StringHelper::replace(
        FileSystem::relative(vcxprojPath, solutionFilePath), "/", "\\");

    stream << StringHelper::format(
        "Project(\"%s\") = \"%s\", \"%s\", \"%s\"\r\n",
        encodeGuid(entryTypeGuid).c_str(),
        project.name.c_str(),
        relativePath.c_str(),
        encodeGuid(project.guid).c_str());
    stream << "EndProject\r\n";

    stream << "Global\r\n";

    stream << "  GlobalSection(SolutionConfigurationPlatforms) = preSolution\r\n";
    const std::vector<std::string> variants = {
        "Debug|x64 = Debug|x64",
        "Debug|x86 = Debug|x86",
        "Release|x64 = Release|x64",
        "Release|x86 = Release|x86",
    };
    for (auto & variant : variants) {
        stream << "    " << variant << "\r\n";
    }
    stream << "  EndGlobalSection\r\n";

    stream << "  GlobalSection(ProjectConfigurationPlatforms) = postSolution\r\n";
    const std::vector<std::string> variantsAndPlatforms = {
        encodeGuid(project.guid) + ".Debug|x64.ActiveCfg = Debug|x64",
        encodeGuid(project.guid) + ".Debug|x64.Build.0 = Debug|x64",
        encodeGuid(project.guid) + ".Debug|x86.ActiveCfg = Debug|Win32",
        encodeGuid(project.guid) + ".Debug|x86.Build.0 = Debug|Win32",
        encodeGuid(project.guid) + ".Release|x64.ActiveCfg = Release|x64",
        encodeGuid(project.guid) + ".Release|x64.Build.0 = Release|x64",
        encodeGuid(project.guid) + ".Release|x86.ActiveCfg = Release|Win32",
        encodeGuid(project.guid) + ".Release|x86.Build.0 = Release|Win32",
    };
    for (auto & v : variantsAndPlatforms) {
        stream << "    " << v << "\r\n";
    }
    stream << "  EndGlobalSection\r\n";

    stream << "  GlobalSection(SolutionProperties) = preSolution\r\n";
    stream << "    HideSolutionNode = FALSE\r\n";
    stream << "  EndGlobalSection\r\n";

    stream << "EndGlobal\r\n";
    return stream.str();
}

struct XmlElement {
    std::string name;
    bool hasElements = false;
    bool hasValue = false;
};

class XmlWriter {
    std::stringstream & stream;
    std::vector<XmlElement> stack;

public:
    explicit XmlWriter(std::stringstream & streamIn)
        : stream(streamIn)
    {
        stream << "﻿<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
    }

    std::string getIndent() const noexcept
    {
        std::string spaces;
        for (size_t i = 1; i < stack.size(); ++i) {
            spaces += "  ";
        }
        return std::move(spaces);
    }

    void startElement(const std::string& name)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));

        stream << getIndent();
        stream << "<" << name << ">";
    }

    void startElement(const std::string& name, const std::string& attributes)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));
        stream << getIndent() << "<" << name << " " << attributes << ">";
    }

    void endElement()
    {
        assert(!stack.empty());
        auto & element = stack.back();
        if (!element.hasValue && !element.hasElements) {
            stream << "\r\n";
        }
        if (!element.hasValue) {
            stream << getIndent();
        }
        stream << "</" << element.name << ">\r\n";
        stack.pop_back();
    }

    void writeElement(const std::string& name, const std::string& attributes)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));
        stream << getIndent() << "<" << name << " " << attributes << " />\r\n";
        stack.pop_back();
    }

    void writeValue(const std::string& value)
    {
        assert(!stack.empty());
        stack.back().hasValue = true;
        stream << value;
    }

    void writeBool(bool value)
    {
        writeValue(value ? "true" : "false");
    }
};

std::string generateVcxprojFiltersFile(const CompileOptions& options)
{
    std::stringstream stream;

    std::vector<std::string> headerFiles;
    std::vector<std::string> sourceFiles;

    for (auto & source : options.sources) {
        std::string ext;
        std::tie(std::ignore, ext) = FileSystem::splitExtension(source);
        if (ext == ".h" || ext == ".hh" || ext == ".hpp" || ext == ".hxx") {
            headerFiles.push_back(source);
        }
        else if (ext == ".c" || ext == ".cc" || ext == ".cpp" || ext == ".cxx") {
            sourceFiles.push_back(source);
        }
    }

    XmlWriter writer(stream);
    writer.startElement("Project",
        "ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\"");
        writer.startElement("ItemGroup");
            writer.startElement("Filter", "Include=\"Source Files\"");
                writer.startElement("UniqueIdentifier");
                    writer.writeValue(encodeGuid("4FC737F1-C7A5-4376-A066-2A32D752A2FF"));
                writer.endElement();
                writer.startElement("Extensions");
                    writer.writeValue("cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx");
                writer.endElement();
            writer.endElement();
            writer.startElement("Filter", "Include=\"Header Files\"");
                writer.startElement("UniqueIdentifier");
                    writer.writeValue(encodeGuid("93995380-89BD-4b04-88EB-625FBE52EBFB"));
                writer.endElement();
                writer.startElement("Extensions");
                    writer.writeValue("h;hh;hpp;hxx;hm;inl;inc;xsd");
                writer.endElement();
            writer.endElement();
            writer.startElement("Filter", "Include=\"Resource Files\"");
                writer.startElement("UniqueIdentifier");
                    writer.writeValue(encodeGuid("67DA6AB6-F800-4c08-8B7A-83BB121AAD01"));
                writer.endElement();
                writer.startElement("Extensions");
                writer.writeValue(
                    "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;"
                    "gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms");
                writer.endElement();
            writer.endElement();
        writer.endElement();
        writer.startElement("ItemGroup");
        for (auto & source : headerFiles) {
            writer.startElement("ClInclude", "Include=\"" + source + "\"");
                writer.startElement("Filter");
                    writer.writeValue("Header Files");
                writer.endElement();
            writer.endElement();
        }
        writer.endElement();
        writer.startElement("ItemGroup");
        for (auto & source : sourceFiles) {
            writer.startElement("ClCompile", "Include=\"" + source + "\"");
                writer.startElement("Filter");
                    writer.writeValue("Source Files");
                writer.endElement();
            writer.endElement();
        }
        writer.endElement();
    writer.endElement();
    return stream.str();
}

std::string generateVcxprojFile(const CompileOptions& options, const MSBuildProject& project)
{
    std::stringstream stream;

    struct ProjectConfiguration {
        std::string Include;
        std::string Configuration;
        std::string Platform;
    };

    XmlWriter writer(stream);
    writer.startElement("Project",
        "DefaultTargets=\"Build\" ToolsVersion=\"14.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\"");

        writer.startElement("ItemGroup", "Label=\"ProjectConfigurations\"");
            writer.startElement("ProjectConfiguration", "Include=\"Debug|Win32\"");
                writer.startElement("Configuration");
                    writer.writeValue("Debug");
                writer.endElement();
                writer.startElement("Platform");
                    writer.writeValue("Win32");
                writer.endElement();
            writer.endElement();

            writer.startElement("ProjectConfiguration", "Include=\"Release|Win32\"");
                writer.startElement("Configuration");
                    writer.writeValue("Release");
                writer.endElement();
                writer.startElement("Platform");
                    writer.writeValue("Win32");
                writer.endElement();
            writer.endElement();

            writer.startElement("ProjectConfiguration", "Include=\"Debug|x64\"");
                writer.startElement("Configuration");
                    writer.writeValue("Debug");
                writer.endElement();
                writer.startElement("Platform");
                    writer.writeValue("x64");
                writer.endElement();
            writer.endElement();

            writer.startElement("ProjectConfiguration", "Include=\"Release|x64\"");
                writer.startElement("Configuration");
                    writer.writeValue("Release");
                writer.endElement();
                writer.startElement("Platform");
                    writer.writeValue("x64");
                writer.endElement();
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Label=\"Globals\"");
            writer.startElement("ProjectGuid");
                writer.writeValue(encodeGuid(project.guid));
            writer.endElement();
            writer.startElement("Keyword");
                writer.writeValue("Win32Proj");
            writer.endElement();
            writer.startElement("RootNamespace");
                writer.writeValue(project.name);
            writer.endElement();
            writer.startElement("WindowsTargetPlatformVersion");
                writer.writeValue("8.1");
            writer.endElement();
        writer.endElement();

        writer.writeElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\"");

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"Configuration\"");
            writer.startElement("ConfigurationType");
                writer.writeValue("Application");
            writer.endElement();
            writer.startElement("UseDebugLibraries");
                writer.writeBool(true);
            writer.endElement();
            writer.startElement("PlatformToolset");
                writer.writeValue("v140");
            writer.endElement();
            writer.startElement("CharacterSet");
                writer.writeValue("Unicode");
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"Configuration\"");
            writer.startElement("ConfigurationType");
                writer.writeValue("Application");
            writer.endElement();
            writer.startElement("UseDebugLibraries");
                writer.writeBool(false);
            writer.endElement();
            writer.startElement("PlatformToolset");
                writer.writeValue("v140");
            writer.endElement();
            writer.startElement("WholeProgramOptimization");
                writer.writeBool(true);
            writer.endElement();
            writer.startElement("CharacterSet");
                writer.writeValue("Unicode");
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"Configuration\"");
            writer.startElement("ConfigurationType");
                writer.writeValue("Application");
            writer.endElement();
            writer.startElement("UseDebugLibraries");
                writer.writeBool(true);
            writer.endElement();
            writer.startElement("PlatformToolset");
                writer.writeValue("v140");
            writer.endElement();
            writer.startElement("CharacterSet");
                writer.writeValue("Unicode");
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\"");
            writer.startElement("ConfigurationType");
                writer.writeValue("Application");
            writer.endElement();
            writer.startElement("UseDebugLibraries");
                writer.writeBool(false);
            writer.endElement();
            writer.startElement("PlatformToolset");
                writer.writeValue("v140");
            writer.endElement();
            writer.startElement("WholeProgramOptimization");
                writer.writeBool(true);
            writer.endElement();
            writer.startElement("CharacterSet");
                writer.writeValue("Unicode");
            writer.endElement();
        writer.endElement();

        writer.writeElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\"");

        writer.startElement("ImportGroup", "Label=\"ExtensionSettings\"");
        writer.endElement();

        writer.startElement("ImportGroup", "Label=\"Shared\"");
        writer.endElement();

        writer.startElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.writeElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.endElement();

        writer.startElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.writeElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.endElement();

        writer.startElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.writeElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.endElement();

        writer.startElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.writeElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.endElement();

        writer.writeElement("PropertyGroup", "Label=\"UserMacros\"");

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.startElement("LinkIncremental");
                writer.writeBool(true);
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.startElement("LinkIncremental");
                writer.writeBool(true);
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.startElement("LinkIncremental");
                writer.writeBool(false);
            writer.endElement();
        writer.endElement();

        writer.startElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.startElement("LinkIncremental");
                writer.writeBool(false);
            writer.endElement();
        writer.endElement();

        writer.startElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.startElement("ClCompile");
                writer.startElement("PrecompiledHeader");
                writer.endElement();
                writer.startElement("WarningLevel");
                    writer.writeValue("Level3");
                writer.endElement();
                writer.startElement("Optimization");
                    writer.writeValue("Disabled");
                writer.endElement();
                writer.startElement("PreprocessorDefinitions");
                    writer.writeValue("WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.endElement();
                writer.startElement("SDLCheck");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
            writer.startElement("Link");
                writer.startElement("SubSystem");
                    writer.writeValue("Console");
                writer.endElement();
                writer.startElement("GenerateDebugInformation");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
        writer.endElement();

        writer.startElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.startElement("ClCompile");
                writer.startElement("PrecompiledHeader");
                writer.endElement();
                writer.startElement("WarningLevel");
                    writer.writeValue("Level3");
                writer.endElement();
                writer.startElement("Optimization");
                    writer.writeValue("Disabled");
                writer.endElement();
                writer.startElement("PreprocessorDefinitions");
                    writer.writeValue("_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.endElement();
                writer.startElement("SDLCheck");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
            writer.startElement("Link");
                writer.startElement("SubSystem");
                    writer.writeValue("Console");
                writer.endElement();
                writer.startElement("GenerateDebugInformation");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
        writer.endElement();

        writer.startElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.startElement("ClCompile");
                writer.startElement("WarningLevel");
                    writer.writeValue("Level3");
                writer.endElement();
                writer.startElement("PrecompiledHeader");
                writer.endElement();
                writer.startElement("Optimization");
                    writer.writeValue("MaxSpeed");
                writer.endElement();
                writer.startElement("FunctionLevelLinking");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("IntrinsicFunctions");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("PreprocessorDefinitions");
                    writer.writeValue("WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.endElement();
                writer.startElement("SDLCheck");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
            writer.startElement("Link");
                writer.startElement("SubSystem");
                    writer.writeValue("Console");
                writer.endElement();
                writer.startElement("GenerateDebugInformation");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("EnableCOMDATFolding");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("OptimizeReferences");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
        writer.endElement();

        writer.startElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.startElement("ClCompile");
                writer.startElement("WarningLevel");
                    writer.writeValue("Level3");
                writer.endElement();
                writer.startElement("PrecompiledHeader");
                writer.endElement();
                writer.startElement("Optimization");
                    writer.writeValue("MaxSpeed");
                writer.endElement();
                writer.startElement("FunctionLevelLinking");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("IntrinsicFunctions");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("PreprocessorDefinitions");
                    writer.writeValue("NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.endElement();
                writer.startElement("SDLCheck");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
            writer.startElement("Link");
                writer.startElement("SubSystem");
                    writer.writeValue("Console");
                writer.endElement();
                writer.startElement("GenerateDebugInformation");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("EnableCOMDATFolding");
                    writer.writeBool(true);
                writer.endElement();
                writer.startElement("OptimizeReferences");
                    writer.writeBool(true);
                writer.endElement();
            writer.endElement();
        writer.endElement();

        for (auto & source : options.sources) {
            const auto fileType = [&] {
                std::string ext;
                std::tie(std::ignore, ext) = FileSystem::splitExtension(source);
                if (ext == ".h" || ext == ".hh" || ext == ".hpp" || ext == ".hxx") {
                    return "ClInclude";
                }
                else if (ext == ".c" || ext == ".cc" || ext == ".cpp" || ext == ".cxx") {
                    return "ClCompile";
                }
                return "ClCompile";
            }();
            writer.startElement("ItemGroup");
                writer.writeElement(fileType, "Include=\"" + source + "\"");
            writer.endElement();
        }

        writer.writeElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\"");
        writer.startElement("ImportGroup", "Label=\"ExtensionTargets\"");
        writer.endElement();
    writer.endElement();
    return stream.str();
}

} // unnamed namespace

GeneratorError MSBuild::generateMSBuildProject(const CompileOptions& options)
{
    namespace FileSystem = somera::FileSystem;

    const auto projectDirectoryPath = FileSystem::join(
        options.generatorOutputDirectory,
        options.targetName);
    if (!FileSystem::exists(projectDirectoryPath)) {
        FileSystem::createDirectories(projectDirectoryPath);
    }

    MSBuildProject project;
    project.guid = newGuid();
    project.name = options.targetName;

    const auto vcxprojPath = FileSystem::join(
        projectDirectoryPath, options.targetName + ".vcxproj");

    {
        std::ofstream stream(vcxprojPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << generateVcxprojFile(options, project);
    }
    {
        const auto vcxprojFilterPath = FileSystem::join(
            projectDirectoryPath, options.targetName + ".vcxproj.filters");
        std::ofstream stream(vcxprojFilterPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << generateVcxprojFiltersFile(options);
    }
    {
        const auto solutionFilePath = FileSystem::join(
            options.generatorOutputDirectory, options.targetName + ".sln");
        std::ofstream stream(solutionFilePath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << generateSolutionFile(options, project, solutionFilePath, vcxprojPath);
    }

    return {};
}

} // namespace somera
