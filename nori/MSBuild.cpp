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

std::string NewGuid() noexcept
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
    return id;
}

struct MSBuildProject {
    std::string guid;
    std::string name;
};

std::string EncodeGuid(const std::string& guid)
{
    return '{' + guid + '}';
}

std::string GenerateSolutionFile(
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
        EncodeGuid(entryTypeGuid).c_str(),
        project.name.c_str(),
        relativePath.c_str(),
        EncodeGuid(project.guid).c_str());
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
        EncodeGuid(project.guid) + ".Debug|x64.ActiveCfg = Debug|x64",
        EncodeGuid(project.guid) + ".Debug|x64.Build.0 = Debug|x64",
        EncodeGuid(project.guid) + ".Debug|x86.ActiveCfg = Debug|Win32",
        EncodeGuid(project.guid) + ".Debug|x86.Build.0 = Debug|Win32",
        EncodeGuid(project.guid) + ".Release|x64.ActiveCfg = Release|x64",
        EncodeGuid(project.guid) + ".Release|x64.Build.0 = Release|x64",
        EncodeGuid(project.guid) + ".Release|x86.ActiveCfg = Release|Win32",
        EncodeGuid(project.guid) + ".Release|x86.Build.0 = Release|Win32",
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

    std::string GetIndent() const noexcept
    {
        std::string spaces;
        for (size_t i = 1; i < stack.size(); ++i) {
            spaces += "  ";
        }
        return spaces;
    }

    void StartElement(const std::string& name)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));

        stream << GetIndent();
        stream << "<" << name << ">";
    }

    void StartElement(const std::string& name, const std::string& attributes)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));
        stream << GetIndent() << "<" << name << " " << attributes << ">";
    }

    void EndElement()
    {
        assert(!stack.empty());
        auto & element = stack.back();
        if (!element.hasValue && !element.hasElements) {
            stream << "\r\n";
        }
        if (!element.hasValue) {
            stream << GetIndent();
        }
        stream << "</" << element.name << ">\r\n";
        stack.pop_back();
    }

    void WriteElement(const std::string& name, const std::string& attributes)
    {
        if (!stack.empty() && !stack.back().hasElements) {
            stream << "\r\n";
            stack.back().hasElements = true;
        }
        XmlElement element;
        element.name = name;
        stack.push_back(std::move(element));
        stream << GetIndent() << "<" << name << " " << attributes << " />\r\n";
        stack.pop_back();
    }

    void WriteValue(const std::string& value)
    {
        assert(!stack.empty());
        stack.back().hasValue = true;
        stream << value;
    }

    void WriteBool(bool value)
    {
        WriteValue(value ? "true" : "false");
    }
};

std::string GenerateVcxprojFiltersFile(const CompileOptions& options)
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
    writer.StartElement("Project",
        "ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\"");
        writer.StartElement("ItemGroup");
            writer.StartElement("Filter", "Include=\"Source Files\"");
                writer.StartElement("UniqueIdentifier");
                    writer.WriteValue(EncodeGuid("4FC737F1-C7A5-4376-A066-2A32D752A2FF"));
                writer.EndElement();
                writer.StartElement("Extensions");
                    writer.WriteValue("cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx");
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Filter", "Include=\"Header Files\"");
                writer.StartElement("UniqueIdentifier");
                    writer.WriteValue(EncodeGuid("93995380-89BD-4b04-88EB-625FBE52EBFB"));
                writer.EndElement();
                writer.StartElement("Extensions");
                    writer.WriteValue("h;hh;hpp;hxx;hm;inl;inc;xsd");
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Filter", "Include=\"Resource Files\"");
                writer.StartElement("UniqueIdentifier");
                    writer.WriteValue(EncodeGuid("67DA6AB6-F800-4c08-8B7A-83BB121AAD01"));
                writer.EndElement();
                writer.StartElement("Extensions");
                writer.WriteValue(
                    "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;"
                    "gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms");
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();
        writer.StartElement("ItemGroup");
        for (auto & source : headerFiles) {
            writer.StartElement("ClInclude", "Include=\"" + source + "\"");
                writer.StartElement("Filter");
                    writer.WriteValue("Header Files");
                writer.EndElement();
            writer.EndElement();
        }
        writer.EndElement();
        writer.StartElement("ItemGroup");
        for (auto & source : sourceFiles) {
            writer.StartElement("ClCompile", "Include=\"" + source + "\"");
                writer.StartElement("Filter");
                    writer.WriteValue("Source Files");
                writer.EndElement();
            writer.EndElement();
        }
        writer.EndElement();
    writer.EndElement();
    return stream.str();
}

std::string GenerateVcxprojFile(const CompileOptions& options, const MSBuildProject& project)
{
    std::stringstream stream;

    struct ProjectConfiguration {
        std::string Include;
        std::string Configuration;
        std::string Platform;
    };

    XmlWriter writer(stream);
    writer.StartElement("Project",
        "DefaultTargets=\"Build\" ToolsVersion=\"14.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\"");

        writer.StartElement("ItemGroup", "Label=\"ProjectConfigurations\"");
            writer.StartElement("ProjectConfiguration", "Include=\"Debug|Win32\"");
                writer.StartElement("Configuration");
                    writer.WriteValue("Debug");
                writer.EndElement();
                writer.StartElement("Platform");
                    writer.WriteValue("Win32");
                writer.EndElement();
            writer.EndElement();

            writer.StartElement("ProjectConfiguration", "Include=\"Release|Win32\"");
                writer.StartElement("Configuration");
                    writer.WriteValue("Release");
                writer.EndElement();
                writer.StartElement("Platform");
                    writer.WriteValue("Win32");
                writer.EndElement();
            writer.EndElement();

            writer.StartElement("ProjectConfiguration", "Include=\"Debug|x64\"");
                writer.StartElement("Configuration");
                    writer.WriteValue("Debug");
                writer.EndElement();
                writer.StartElement("Platform");
                    writer.WriteValue("x64");
                writer.EndElement();
            writer.EndElement();

            writer.StartElement("ProjectConfiguration", "Include=\"Release|x64\"");
                writer.StartElement("Configuration");
                    writer.WriteValue("Release");
                writer.EndElement();
                writer.StartElement("Platform");
                    writer.WriteValue("x64");
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Label=\"Globals\"");
            writer.StartElement("ProjectGuid");
                writer.WriteValue(EncodeGuid(project.guid));
            writer.EndElement();
            writer.StartElement("Keyword");
                writer.WriteValue("Win32Proj");
            writer.EndElement();
            writer.StartElement("RootNamespace");
                writer.WriteValue(project.name);
            writer.EndElement();
            writer.StartElement("WindowsTargetPlatformVersion");
                writer.WriteValue("8.1");
            writer.EndElement();
        writer.EndElement();

        writer.WriteElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\"");

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\" Label=\"Configuration\"");
            writer.StartElement("ConfigurationType");
                writer.WriteValue("Application");
            writer.EndElement();
            writer.StartElement("UseDebugLibraries");
                writer.WriteBool(true);
            writer.EndElement();
            writer.StartElement("PlatformToolset");
                writer.WriteValue("v140");
            writer.EndElement();
            writer.StartElement("CharacterSet");
                writer.WriteValue("Unicode");
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\" Label=\"Configuration\"");
            writer.StartElement("ConfigurationType");
                writer.WriteValue("Application");
            writer.EndElement();
            writer.StartElement("UseDebugLibraries");
                writer.WriteBool(false);
            writer.EndElement();
            writer.StartElement("PlatformToolset");
                writer.WriteValue("v140");
            writer.EndElement();
            writer.StartElement("WholeProgramOptimization");
                writer.WriteBool(true);
            writer.EndElement();
            writer.StartElement("CharacterSet");
                writer.WriteValue("Unicode");
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\" Label=\"Configuration\"");
            writer.StartElement("ConfigurationType");
                writer.WriteValue("Application");
            writer.EndElement();
            writer.StartElement("UseDebugLibraries");
                writer.WriteBool(true);
            writer.EndElement();
            writer.StartElement("PlatformToolset");
                writer.WriteValue("v140");
            writer.EndElement();
            writer.StartElement("CharacterSet");
                writer.WriteValue("Unicode");
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\" Label=\"Configuration\"");
            writer.StartElement("ConfigurationType");
                writer.WriteValue("Application");
            writer.EndElement();
            writer.StartElement("UseDebugLibraries");
                writer.WriteBool(false);
            writer.EndElement();
            writer.StartElement("PlatformToolset");
                writer.WriteValue("v140");
            writer.EndElement();
            writer.StartElement("WholeProgramOptimization");
                writer.WriteBool(true);
            writer.EndElement();
            writer.StartElement("CharacterSet");
                writer.WriteValue("Unicode");
            writer.EndElement();
        writer.EndElement();

        writer.WriteElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\"");

        writer.StartElement("ImportGroup", "Label=\"ExtensionSettings\"");
        writer.EndElement();

        writer.StartElement("ImportGroup", "Label=\"Shared\"");
        writer.EndElement();

        writer.StartElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.WriteElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.EndElement();

        writer.StartElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.WriteElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.EndElement();

        writer.StartElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.WriteElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.EndElement();

        writer.StartElement("ImportGroup", "Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.WriteElement("Import", "Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\"");
        writer.EndElement();

        writer.WriteElement("PropertyGroup", "Label=\"UserMacros\"");

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.StartElement("LinkIncremental");
                writer.WriteBool(true);
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.StartElement("LinkIncremental");
                writer.WriteBool(true);
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.StartElement("LinkIncremental");
                writer.WriteBool(false);
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("PropertyGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.StartElement("LinkIncremental");
                writer.WriteBool(false);
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\"");
            writer.StartElement("ClCompile");
                writer.StartElement("PrecompiledHeader");
                writer.EndElement();
                writer.StartElement("WarningLevel");
                    writer.WriteValue("Level3");
                writer.EndElement();
                writer.StartElement("Optimization");
                    writer.WriteValue("Disabled");
                writer.EndElement();
                writer.StartElement("PreprocessorDefinitions");
                    writer.WriteValue("WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.EndElement();
                writer.StartElement("SDLCheck");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Link");
                writer.StartElement("SubSystem");
                    writer.WriteValue("Console");
                writer.EndElement();
                writer.StartElement("GenerateDebugInformation");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\"");
            writer.StartElement("ClCompile");
                writer.StartElement("PrecompiledHeader");
                writer.EndElement();
                writer.StartElement("WarningLevel");
                    writer.WriteValue("Level3");
                writer.EndElement();
                writer.StartElement("Optimization");
                    writer.WriteValue("Disabled");
                writer.EndElement();
                writer.StartElement("PreprocessorDefinitions");
                    writer.WriteValue("_DEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.EndElement();
                writer.StartElement("SDLCheck");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Link");
                writer.StartElement("SubSystem");
                    writer.WriteValue("Console");
                writer.EndElement();
                writer.StartElement("GenerateDebugInformation");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\"");
            writer.StartElement("ClCompile");
                writer.StartElement("WarningLevel");
                    writer.WriteValue("Level3");
                writer.EndElement();
                writer.StartElement("PrecompiledHeader");
                writer.EndElement();
                writer.StartElement("Optimization");
                    writer.WriteValue("MaxSpeed");
                writer.EndElement();
                writer.StartElement("FunctionLevelLinking");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("IntrinsicFunctions");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("PreprocessorDefinitions");
                    writer.WriteValue("WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.EndElement();
                writer.StartElement("SDLCheck");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Link");
                writer.StartElement("SubSystem");
                    writer.WriteValue("Console");
                writer.EndElement();
                writer.StartElement("GenerateDebugInformation");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("EnableCOMDATFolding");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("OptimizeReferences");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();

        writer.StartElement("ItemDefinitionGroup", "Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\"");
            writer.StartElement("ClCompile");
                writer.StartElement("WarningLevel");
                    writer.WriteValue("Level3");
                writer.EndElement();
                writer.StartElement("PrecompiledHeader");
                writer.EndElement();
                writer.StartElement("Optimization");
                    writer.WriteValue("MaxSpeed");
                writer.EndElement();
                writer.StartElement("FunctionLevelLinking");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("IntrinsicFunctions");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("PreprocessorDefinitions");
                    writer.WriteValue("NDEBUG;_CONSOLE;%(PreprocessorDefinitions)");
                writer.EndElement();
                writer.StartElement("SDLCheck");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
            writer.StartElement("Link");
                writer.StartElement("SubSystem");
                    writer.WriteValue("Console");
                writer.EndElement();
                writer.StartElement("GenerateDebugInformation");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("EnableCOMDATFolding");
                    writer.WriteBool(true);
                writer.EndElement();
                writer.StartElement("OptimizeReferences");
                    writer.WriteBool(true);
                writer.EndElement();
            writer.EndElement();
        writer.EndElement();

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
            writer.StartElement("ItemGroup");
                writer.WriteElement(fileType, "Include=\"" + source + "\"");
            writer.EndElement();
        }

        writer.WriteElement("Import", "Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\"");
        writer.StartElement("ImportGroup", "Label=\"ExtensionTargets\"");
        writer.EndElement();
    writer.EndElement();
    return stream.str();
}

} // unnamed namespace

GeneratorError MSBuild::GenerateMSBuildProject(const CompileOptions& options)
{
    namespace FileSystem = somera::FileSystem;

    const auto projectDirectoryPath = FileSystem::join(
        options.generatorOutputDirectory,
        options.targetName);
    if (!FileSystem::exists(projectDirectoryPath)) {
        FileSystem::createDirectories(projectDirectoryPath);
    }

    MSBuildProject project;
    project.guid = NewGuid();
    project.name = options.targetName;

    const auto vcxprojPath = FileSystem::join(
        projectDirectoryPath, options.targetName + ".vcxproj");

    {
        std::ofstream stream(vcxprojPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << GenerateVcxprojFile(options, project);
    }
    {
        const auto vcxprojFilterPath = FileSystem::join(
            projectDirectoryPath, options.targetName + ".vcxproj.filters");
        std::ofstream stream(vcxprojFilterPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << GenerateVcxprojFiltersFile(options);
    }
    {
        const auto solutionFilePath = FileSystem::join(
            options.generatorOutputDirectory, options.targetName + ".sln");
        std::ofstream stream(solutionFilePath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << GenerateSolutionFile(options, project, solutionFilePath, vcxprojPath);
    }

    return {};
}

} // namespace somera
