// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "XcodeProject.h"
#include "somera/Any.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <cassert>
#include <ctime>
#include <fstream>
#include <map>
#include <random>
#include <utility>
#include <sstream>
#include <string>
#include <vector>

namespace somera {
namespace {

std::string generateXcodeID() noexcept
{
    std::mt19937 random(std::random_device{}());
    static uint32_t hash1 = random();
    hash1 += 1;
    ::time_t timeRaw;
    ::time(&timeRaw);
    static uint32_t hash2 = static_cast<uint32_t>(timeRaw);
    hash2 += 1;
    static const uint32_t hash3 = random();
    std::string id = StringHelper::format("%08X%08X%08X", hash1, hash2, hash3);
    return id;
}

std::string generateXCWorkSpaceData(const std::string& xcodeprojName)
{
    std::stringstream stream;
    stream <<
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<Workspace\n"
    "   version = \"1.0\">\n"
    "   <FileRef\n";
    stream <<
    "      location = \"self:" << xcodeprojName << "\">\n";
    stream <<
    "   </FileRef>\n"
    "</Workspace>\n";
    return stream.str();
}

struct XcodeProject;
struct XcodeObject;
struct XcodeBuildPhase;
struct PBXBuildFile;
struct PBXCopyFilesBuildPhase;
struct PBXFileReference;
struct PBXFrameworksBuildPhase;
struct PBXGroup;
struct PBXNativeTarget;
struct PBXProject;
struct PBXSourcesBuildPhase;
struct XCBuildConfiguration;
struct XCConfigurationList;

std::string encodeComment(const std::string& comment)
{
    return "/* " + comment + " */";
}

std::string encodeDoubleQuotes(const std::string& comment)
{
    return '\"' + comment + '\"';
}

std::string stringifyUUID(const std::string& uuid, const std::string& comment)
{
    std::stringstream stream;
    stream << uuid;
    if (!comment.empty()) {
        stream << ' ' + encodeComment(comment);
    }
    return stream.str();
}

std::string stringifyUUID(const std::string& uuid, Optional<std::string> comment)
{
    std::stringstream stream;
    stream << uuid;
    if (comment && !comment->empty()) {
        stream << ' ' + encodeComment(*comment);
    }
    return stream.str();
}

struct Noncopyable {
    Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable & operator=(const Noncopyable&) = delete;
};

struct XcodeObject : Noncopyable {
    virtual ~XcodeObject() = default;
    virtual std::string isa() const noexcept = 0;

    std::string const uuid;
    XcodeObject() : uuid(generateXcodeID()) {}
};

struct XcodeBuildPhase : public XcodeObject {
    virtual ~XcodeBuildPhase() = default;
    virtual std::string comments() const noexcept = 0;
};

struct XcodeTargetAttribute final {
    std::shared_ptr<PBXNativeTarget> target;
    Optional<std::string> CreatedOnToolsVersion;
    Optional<std::string> DevelopmentTeam;
    Optional<std::string> TestTargetID;
};

struct XcodeProject final : Noncopyable {
    std::string archiveVersion;
    std::string objectVersion;
    //std::map<std::string, Any> classes;
    //std::map<std::string, std::shared_ptr<XcodeObject>> objects;
    std::shared_ptr<PBXProject> rootObject;
    std::string name;

    std::vector<std::shared_ptr<XCBuildConfiguration>> buildConfigurations;
    std::vector<std::shared_ptr<XCConfigurationList>> configurationLists;
    std::vector<std::shared_ptr<PBXFileReference>> fileReferences;
    std::vector<std::shared_ptr<PBXSourcesBuildPhase>> sourcesBuildPhases;
    std::vector<std::shared_ptr<PBXGroup>> groups;
    std::vector<std::shared_ptr<PBXFrameworksBuildPhase>> frameworkBuildPhases;
    std::vector<std::shared_ptr<PBXCopyFilesBuildPhase>> copyFilesBuildPhases;
    std::vector<std::shared_ptr<PBXNativeTarget>> nativeTargets;
    std::vector<std::shared_ptr<PBXProject>> projects;
};

struct PBXBuildFile final : public XcodeObject {
    std::string isa() const noexcept override { return "PBXBuildFile"; }
    std::shared_ptr<PBXFileReference> fileRef;
};

struct PBXFileReference final : public XcodeObject {
    std::string isa() const noexcept override { return "PBXFileReference"; }
    Optional<std::string> explicitFileType;
    Optional<std::string> includeInIndex;
    Optional<std::string> lastKnownFileType;
    std::string path;
    std::string sourceTree;
};

struct PBXGroup final : public XcodeObject {
    std::string isa() const noexcept override { return "PBXGroup"; }
    std::vector<std::shared_ptr<XcodeObject>> children;

    Optional<std::string> name;
    Optional<std::string> path;
    Optional<std::string> sourceTree;

    std::string getSourceTree() const noexcept
    {
        return sourceTree ? *sourceTree : "\"<group>\"";
    }

    std::string getUuidWithComment()
    {
        if (name) {
            return stringifyUUID(uuid, *name);
        }
        if (path) {
            return stringifyUUID(uuid, *path);
        }
        return uuid;
    }

    std::vector<std::string> getChildrenString() const
    {
        std::vector<std::string> result;
        for (auto & child : children) {
            if (auto group = std::dynamic_pointer_cast<PBXGroup>(child)) {
                result.push_back(group->getUuidWithComment());
            }
            else if (auto file = std::dynamic_pointer_cast<PBXFileReference>(child)) {
                result.push_back(stringifyUUID(file->uuid, file->path));
            }
        }
        return result;
    }

    void visit(const std::function<void(std::shared_ptr<PBXFileReference>)>& func) const
    {
        assert(func);
        for (auto & child : children) {
            if (auto file = std::dynamic_pointer_cast<PBXFileReference>(child)) {
                func(file);
            }
            else if (auto group = std::dynamic_pointer_cast<PBXGroup>(child)) {
                group->visit(func);
            }
        }
    }
};

struct PBXNativeTarget final : public XcodeObject {
    std::string isa() const noexcept override { return "PBXNativeTarget"; }
    std::shared_ptr<XCConfigurationList> buildConfigurationList;
    std::vector<std::shared_ptr<XcodeBuildPhase>> buildPhases;
    std::vector<std::string> buildRules;
    std::vector<std::string> dependencies;
    std::string name;
    std::string productName;
    std::shared_ptr<PBXFileReference> productReference;
    std::string productType;

    std::vector<std::string> getBuildPhasesString() const
    {
        std::vector<std::string> result;
        for (auto & phase : buildPhases) {
            result.push_back(stringifyUUID(phase->uuid, phase->comments()));
        }
        return result;
    }
};

struct PBXProject final : public XcodeObject {
    std::string isa() const noexcept override { return "PBXProject"; }
    std::map<std::string, Any> attributes;
    std::shared_ptr<XCConfigurationList> buildConfigurationList;
    std::string compatibilityVersion;
    std::string developmentRegion;
    std::string hasScannedForEncodings;
    std::vector<std::string> knownRegions;
    std::shared_ptr<PBXGroup> mainGroup;
    std::shared_ptr<PBXGroup> productRefGroup;
    std::string projectDirPath;
    std::string projectRoot;
    std::vector<std::shared_ptr<PBXNativeTarget>> targets;

    std::vector<std::string> getTargetsString() const
    {
        std::vector<std::string> result;
        for (auto & target : targets) {
            result.push_back(stringifyUUID(target->uuid, target->name));
        }
        return result;
    }

    void addAttribute(const std::string& key, const std::string& value)
    {
        attributes.emplace(key, value);
    }

    void addAttribute(const std::string& key, std::vector<XcodeTargetAttribute> && value)
    {
        attributes.emplace(key, std::move(value));
    }
};

struct PBXCopyFilesBuildPhase final : public XcodeBuildPhase {
    std::string isa() const noexcept override { return "PBXCopyFilesBuildPhase"; }
    std::string buildActionMask;
    std::string dstPath;
    std::string dstSubfolderSpec;
    std::string runOnlyForDeploymentPostprocessing;
    std::vector<std::string> files;

    std::string comments() const noexcept override { return "CopyFiles"; }
};

struct PBXFrameworksBuildPhase final : public XcodeBuildPhase {
    std::string isa() const noexcept override { return "PBXFrameworksBuildPhase"; }
    std::string buildActionMask;
    std::vector<std::shared_ptr<PBXBuildFile>> files;
    std::string runOnlyForDeploymentPostprocessing;

    std::string comments() const noexcept override { return "Frameworks"; }
};

struct PBXSourcesBuildPhase final : public XcodeBuildPhase {
    std::string isa() const noexcept override { return "PBXSourcesBuildPhase"; }
    std::string buildActionMask;
    std::vector<std::shared_ptr<PBXBuildFile>> files;
    std::string runOnlyForDeploymentPostprocessing;

    std::string comments() const noexcept override { return "Sources"; }
};

template <class BuildPhase>
std::vector<std::string> toFileListString(const BuildPhase& phase)
{
    static_assert(std::is_base_of<XcodeBuildPhase, BuildPhase>::value, "");
    std::vector<std::string> result;
    for (auto & buildFile : phase.files) {
        result.push_back(stringifyUUID(
            buildFile->uuid,
            buildFile->fileRef->path + " in " + phase.comments()));
    }
    return result;
}

struct XCBuildConfiguration final : public XcodeObject {
    std::string isa() const noexcept override { return "XCBuildConfiguration"; }
    std::vector<std::pair<std::string, Any>> buildSettings;
    std::string name;

    void addBuildSettings(const std::string& key, const std::string& value)
    {
        auto iter = std::find_if(std::begin(buildSettings), std::end(buildSettings),
            [&](const auto& a){ return a.first == key; });
        if (iter != std::end(buildSettings)) {
            iter->second = value;
            return;
        }
        buildSettings.emplace_back(key, value);
        std::sort(std::begin(buildSettings), std::end(buildSettings),
            [](const auto& a, const auto& b){ return a.first < b.first; });
    }

    void addBuildSettings(const std::string& key, const std::vector<std::string>& value)
    {
        auto iter = std::find_if(std::begin(buildSettings), std::end(buildSettings),
            [&](const auto& a){ return a.first == key; });
        if (iter != std::end(buildSettings)) {
            iter->second = value;
            return;
        }
        buildSettings.emplace_back(key, value);
        std::sort(std::begin(buildSettings), std::end(buildSettings),
            [](const auto& a, const auto& b){ return a.first < b.first; });
    }
};

struct XCConfigurationList final : public XcodeObject {
    std::string isa() const noexcept override { return "XCConfigurationList"; }
    std::vector<std::shared_ptr<XCBuildConfiguration>> buildConfigurations;
    std::string defaultConfigurationIsVisible;
    Optional<std::string> defaultConfigurationName;

    std::vector<std::string> getBuildConfigurationsString() const
    {
        std::vector<std::string> result;
        for (auto & buildConfig : buildConfigurations) {
            result.push_back(stringifyUUID(
                buildConfig->uuid, buildConfig->name));
        }
        return result;
    }
};

struct XcodePrinterSettings {
    bool isSingleLine = false;
};

class XcodePrinter {
    std::stringstream & stream;
    int tabs;
    std::string section;
    std::vector<XcodePrinterSettings> settingsStack;

public:
    explicit XcodePrinter(std::stringstream & streamIn)
        : stream(streamIn)
        , tabs(0)
    {
        XcodePrinterSettings settings;
        settings.isSingleLine = false;
        settingsStack.push_back(std::move(settings));
    }

    std::string getIndent() const noexcept
    {
        std::string spaces;
        for (int i = 0; i < tabs; ++i) {
            spaces += "\t";
        }
        return spaces;
    }

    void beginKeyValue(const std::string& key)
    {
        if (!isSingleLine()) {
            stream << getIndent();
        }
        stream << key << " = ";
    }

    void endKeyValue()
    {
        stream << ";";
        if (!isSingleLine()) {
            stream << "\n";
        } else {
            stream << " ";
        }
    }

    void printKeyValue(const std::string& key, const std::string& value)
    {
        beginKeyValue(key);
        stream << value;
        endKeyValue();
    }

    void printKeyValue(const std::string& key, const std::function<void()>& valuePrinter)
    {
        beginKeyValue(key);
        valuePrinter();
        endKeyValue();
    }

    void printKeyValue(const std::string& key, const std::vector<std::string>& array)
    {
        beginKeyValue(key);
        stream << "(";
        if (!isSingleLine()) {
            stream << "\n";
        }
        ++tabs;
        for (auto & value : array) {
            stream << getIndent() << value << ",";
            if (!isSingleLine()) {
                stream << "\n";
            } else {
                stream << " ";
            }
        }
        --tabs;
        stream << getIndent() << ")";
        endKeyValue();
    }

    void beginObject(bool singleLine = false)
    {
        settingsStack.push_back(XcodePrinterSettings{singleLine});
        stream << "{";
        if (!isSingleLine()) {
            stream << "\n";
            ++tabs;
        }
    }

    void endObject()
    {
        if (!isSingleLine()) {
            --tabs;
            stream << getIndent();
        }
        stream << "}";
        settingsStack.pop_back();
    }

    bool isSingleLine() const
    {
        assert(!settingsStack.empty());
        return settingsStack.back().isSingleLine;
    }

    void beginSection(const std::string& sectionIn)
    {
        settingsStack.push_back(XcodePrinterSettings{false});
        this->section = sectionIn;
        stream << "\n";
        stream << "/* Begin " << section << " section */\n";
    }

    void endSection()
    {
        stream << "/* End " << section << " section */\n";
        settingsStack.pop_back();
    }
};

void printObject(
    XcodePrinter & printer,
    const std::vector<std::pair<std::string, Any>>& object)
{
    printer.beginObject();
    for (auto & pair : object) {
        auto & key = pair.first;
        auto & value = pair.second;
        if (value.is<std::string>()) {
            printer.printKeyValue(key, value.as<std::string>());
        }
        else if (pair.second.is<std::vector<std::string>>()) {
            printer.printKeyValue(key, value.as<std::vector<std::string>>());
        }
    }
    printer.endObject();
}

std::string findLastKnownFileType(const std::string& path) noexcept
{
    auto ext = std::get<1>(FileSystem::splitExtension(path));
    if (ext == "cpp" || ext == "cxx" || ext == "cc") {
        return "sourcecode.cpp.cpp";
    }
    if (ext == "ii") {
        return "sourcecode.cpp.cpp.preprocessed";
    }
    if (ext == "hpp" || ext == "hxx" || ext == "hh") {
        return "sourcecode.cpp.h";
    }
    if (ext == "mm") {
        return "sourcecode.cpp.objcpp";
    }
    if (ext == "m") {
        return "sourcecode.c.objc";
    }
    if (ext == "c") {
        return "sourcecode.c";
    }
    if (ext == "i") {
        return "sourcecode.c.c.preprocessed";
    }
    if (ext == "h") {
        return "sourcecode.c.h";
    }
    if (ext == "swift") {
        return "sourcecode.swift";
    }
    if (ext == "tbd") {
        return "sourcecode.text-based-dylib-definition";
    }
    if (ext == "dylib") {
        return "compiled.mach-o.dylib";
    }
    if (ext == "a") {
        return "archive.ar";
    }
    return "sourcecode";
}

bool isSourceFile(const std::string& path) noexcept
{
    auto ext = std::get<1>(FileSystem::splitExtension(path));
    return (ext == "c" || ext == "cc" || ext == "cpp" || ext == "cxx"
        || ext == "m" || ext == "mm" || ext == "swift");
}

template <typename C, typename T>
auto find(C & container, T & value) -> decltype(std::begin(container))
{
    return std::find(std::begin(container), std::end(container), value);
}

void setDefaultBuildConfig(XCBuildConfiguration& config)
{
    config.addBuildSettings("ALWAYS_SEARCH_USER_PATHS", "NO");
    config.addBuildSettings("CLANG_CXX_LANGUAGE_STANDARD", "\"c++14\"");
    config.addBuildSettings("CLANG_CXX_LIBRARY", "\"libc++\"");
    config.addBuildSettings("CLANG_ENABLE_MODULES", "YES");
    config.addBuildSettings("CLANG_ENABLE_OBJC_ARC", "YES");
    config.addBuildSettings("CLANG_WARN_BOOL_CONVERSION", "YES");
    config.addBuildSettings("CLANG_WARN_CONSTANT_CONVERSION", "YES");
    config.addBuildSettings("CLANG_WARN_DIRECT_OBJC_ISA_USAGE", "YES_ERROR");
    config.addBuildSettings("CLANG_WARN_EMPTY_BODY", "YES");
    config.addBuildSettings("CLANG_WARN_ENUM_CONVERSION", "YES");
    config.addBuildSettings("CLANG_WARN_INT_CONVERSION", "YES");
    config.addBuildSettings("CLANG_WARN_OBJC_ROOT_CLASS", "YES_ERROR");
    config.addBuildSettings("CLANG_WARN_UNREACHABLE_CODE", "YES");
    config.addBuildSettings("CLANG_WARN__DUPLICATE_METHOD_MATCH", "YES");
    config.addBuildSettings("CODE_SIGN_IDENTITY", "\"-\"");
    config.addBuildSettings("COPY_PHASE_STRIP", "NO");
    config.addBuildSettings("GCC_C_LANGUAGE_STANDARD", "c11");
    config.addBuildSettings("GCC_NO_COMMON_BLOCKS", "YES");
    config.addBuildSettings("GCC_WARN_64_TO_32_BIT_CONVERSION", "YES");
    config.addBuildSettings("GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS", "YES");
    config.addBuildSettings("GCC_WARN_ABOUT_MISSING_NEWLINE", "YES");
    config.addBuildSettings("GCC_WARN_ABOUT_MISSING_PROTOTYPES", "YES");
    config.addBuildSettings("GCC_WARN_ABOUT_RETURN_TYPE", "YES_ERROR");
    config.addBuildSettings("GCC_WARN_SHADOW", "YES");
    config.addBuildSettings("GCC_WARN_SIGN_COMPARE", "YES");
    config.addBuildSettings("GCC_WARN_UNDECLARED_SELECTOR", "YES");
    config.addBuildSettings("GCC_WARN_UNINITIALIZED_AUTOS", "YES_AGGRESSIVE");
    config.addBuildSettings("GCC_WARN_UNKNOWN_PRAGMAS", "YES");
    config.addBuildSettings("GCC_WARN_UNUSED_FUNCTION", "YES");
    config.addBuildSettings("GCC_WARN_UNUSED_LABEL", "YES");
    config.addBuildSettings("GCC_WARN_UNUSED_VARIABLE", "YES");
    config.addBuildSettings("MACOSX_DEPLOYMENT_TARGET", "10.11");
    config.addBuildSettings("SDKROOT", "macosx");
}

void setSearchPathsToBuildConfig(
    XCBuildConfiguration& config,
    const CompileOptions& options)
{
    if (!options.includeSearchPaths.empty()) {
        config.addBuildSettings(
            "HEADER_SEARCH_PATHS", options.includeSearchPaths);
    }
    if (!options.librarySearchPaths.empty()) {
        config.addBuildSettings(
            "LIBRARY_SEARCH_PATHS", options.librarySearchPaths);
    }

    {
        ///@todo Please refactor here
        auto iter = options.buildSettings.find("-std=");
        if (iter != std::end(options.buildSettings)) {
            config.addBuildSettings("CLANG_CXX_LANGUAGE_STANDARD", encodeDoubleQuotes(iter->second));
        }
    }
    {
        ///@todo Please refactor here
        auto iter = options.buildSettings.find("-stdlib=");
        if (iter != std::end(options.buildSettings)) {
            config.addBuildSettings("CLANG_CXX_LIBRARY", encodeDoubleQuotes(iter->second));
        }
    }
}

std::shared_ptr<XcodeProject> createXcodeProject(const CompileOptions& options)
{
    const bool hasFrameworks = !options.libraries.empty();

    const auto sourceGroup = [&] {
        auto group = std::make_shared<PBXGroup>();
        group->name = "Source";
        return group;
    }();
    const auto frameworksGroup = [&] {
        auto group = std::make_shared<PBXGroup>();
        group->name = "Frameworks";
        return group;
    }();
    const auto productsGroup = [&] {
        auto group = std::make_shared<PBXGroup>();
        group->name = "Products";
        return group;
    }();
    const auto mainGroup = [&] {
        auto group = std::make_shared<PBXGroup>();
        group->children.push_back(sourceGroup);
        if (hasFrameworks) {
            group->children.push_back(frameworksGroup);
        }
        group->children.push_back(productsGroup);
        return group;
    }();

    const auto productReference = [&] {
        auto fileRef = std::make_shared<PBXFileReference>();
        fileRef->explicitFileType = "\"compiled.mach-o.executable\"";
        fileRef->includeInIndex = "0";
        fileRef->path = options.productName;
        fileRef->sourceTree = "BUILT_PRODUCTS_DIR";
        productsGroup->children.push_back(fileRef);
        return fileRef;
    }();

    for (auto & source : options.sources) {
        auto fileRef = std::make_shared<PBXFileReference>();
        fileRef->lastKnownFileType = findLastKnownFileType(source);
        fileRef->path = source;
        fileRef->sourceTree = "\"<group>\"";

        auto getGroup = [&]() -> std::shared_ptr<PBXGroup> {
            auto directory = std::get<0>(FileSystem::split(source));
            if (directory.empty()) {
                return sourceGroup;
            }
            auto iter = std::find_if(
                std::begin(sourceGroup->children),
                std::end(sourceGroup->children),
                [&directory](const std::shared_ptr<XcodeObject>& object) {
                    auto group = std::dynamic_pointer_cast<PBXGroup>(object);
                    return group && group->name && (*group->name == directory);
                });
            if (iter != std::end(sourceGroup->children)) {
                return std::dynamic_pointer_cast<PBXGroup>(*iter);
            }
            auto group = std::make_shared<PBXGroup>();
            group->name = directory;
            sourceGroup->children.push_back(group);
            return group;
        };
        const auto group = getGroup();
        group->children.push_back(fileRef);
    }

    for (auto & library : options.libraries) {
        auto fileRef = std::make_shared<PBXFileReference>();
        fileRef->lastKnownFileType = findLastKnownFileType(library);
        if ("tbd" == std::get<1>(FileSystem::splitExtension(library))) {
            ///@todo This code is bad.
            fileRef->path = FileSystem::join("usr/lib/", library);
            fileRef->sourceTree = "SDKROOT";
        } else {
            fileRef->path = library;
            fileRef->sourceTree = "\"<group>\"";
        }
        frameworksGroup->children.push_back(fileRef);
    }

    const auto buildConfigurationDebug = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Debug";
        setDefaultBuildConfig(*config);
        setSearchPathsToBuildConfig(*config, options);
        config->addBuildSettings("DEBUG_INFORMATION_FORMAT", "dwarf");
        config->addBuildSettings("ENABLE_STRICT_OBJC_MSGSEND", "YES");
        config->addBuildSettings("ENABLE_TESTABILITY", "YES");
        config->addBuildSettings("GCC_DYNAMIC_NO_PIC", "NO");
        config->addBuildSettings("GCC_OPTIMIZATION_LEVEL", "0");
        config->addBuildSettings("GCC_PREPROCESSOR_DEFINITIONS", std::vector<std::string>{
            "\"DEBUG=1\"",
            "\"$(inherited)\"",
        });
        config->addBuildSettings("MTL_ENABLE_DEBUG_INFO", "YES");
        config->addBuildSettings("ONLY_ACTIVE_ARCH", "YES");
        return config;
    } ();
    const auto buildConfigurationRelease = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Release";
        setDefaultBuildConfig(*config);
        setSearchPathsToBuildConfig(*config, options);
        config->addBuildSettings("DEBUG_INFORMATION_FORMAT", "\"dwarf-with-dsym\"");
        config->addBuildSettings("ENABLE_NS_ASSERTIONS", "NO");
        config->addBuildSettings("ENABLE_STRICT_OBJC_MSGSEND", "YES");
        config->addBuildSettings("MTL_ENABLE_DEBUG_INFO", "NO");
        return config;
    }();
    const auto buildConfigurationTargetDebug = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Debug";
        config->addBuildSettings("PRODUCT_NAME", "\"$(TARGET_NAME)\"");
        return config;
    }();
    const auto buildConfigurationTargetRelease = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Release";
        config->addBuildSettings("PRODUCT_NAME", "\"$(TARGET_NAME)\"");
        return config;
    }();

    const auto configurationListForProject = [&] {
        auto configurationList = std::make_shared<XCConfigurationList>();
        configurationList->buildConfigurations.push_back(buildConfigurationDebug);
        configurationList->buildConfigurations.push_back(buildConfigurationRelease);
        configurationList->defaultConfigurationIsVisible = "0";
        configurationList->defaultConfigurationName = "Release";
        return configurationList;
    }();
    const auto configurationListForNativeTarget = [&] {
        auto configurationList = std::make_shared<XCConfigurationList>();
        configurationList->buildConfigurations.push_back(buildConfigurationTargetDebug);
        configurationList->buildConfigurations.push_back(buildConfigurationTargetRelease);
        configurationList->defaultConfigurationIsVisible = "0";
        configurationList->defaultConfigurationName = "Release";
        return configurationList;
    }();

    const auto sourcesBuildPhase = [&] {
        auto phase = std::make_shared<PBXSourcesBuildPhase>();
        phase->buildActionMask = "2147483647";
        phase->runOnlyForDeploymentPostprocessing = "0";
        sourceGroup->visit([&](std::shared_ptr<PBXFileReference> source) {
            if (isSourceFile(source->path)) {
                auto file = std::make_shared<PBXBuildFile>();
                file->fileRef = source;
                phase->files.push_back(std::move(file));
            }
        });
        return phase;
    }();

    const auto frameworksBuildPhase = [&] {
        auto phase = std::make_shared<PBXFrameworksBuildPhase>();
        phase->buildActionMask = "2147483647";
        phase->runOnlyForDeploymentPostprocessing = "0";
        frameworksGroup->visit([&](std::shared_ptr<PBXFileReference> source) {
            auto file = std::make_shared<PBXBuildFile>();
            file->fileRef = source;
            phase->files.push_back(std::move(file));
        });
        return phase;
    }();

    const auto copyFilesBuildPhase = [&] {
        auto phase = std::make_shared<PBXCopyFilesBuildPhase>();
        phase->buildActionMask = "2147483647";
        phase->dstPath = "/usr/share/man/man1/";
        phase->dstSubfolderSpec = "0";
        phase->runOnlyForDeploymentPostprocessing = "1";
        return phase;
    }();

    const auto nativeTarget = [&] {
        auto target = std::make_shared<PBXNativeTarget>();
        target->buildConfigurationList = configurationListForNativeTarget;
        target->buildPhases.push_back(sourcesBuildPhase);
        target->buildPhases.push_back(frameworksBuildPhase);
        target->buildPhases.push_back(copyFilesBuildPhase);
        target->name = options.targetName;
        target->productName = options.productName;
        target->productReference = productReference;
        target->productType = "\"com.apple.product-type.tool\"";
        return target;
    }();

    const auto pbxProject = [&] {
        auto project = std::make_shared<PBXProject>();
        project->buildConfigurationList = configurationListForProject;
        project->compatibilityVersion = "\"Xcode 3.2\"";
        project->developmentRegion = "English";
        project->hasScannedForEncodings = "0";
        project->knownRegions = {"en"};
        project->mainGroup = mainGroup;
        project->productRefGroup = productsGroup;
        project->projectDirPath = "\"\"";
        project->projectRoot = "\"\"";
        project->targets.push_back(nativeTarget);

        project->addAttribute("LastUpgradeCheck", "0710");
        if (!options.author.empty()) {
            project->addAttribute("ORGANIZATIONNAME", encodeDoubleQuotes(options.author));
        }

        std::vector<XcodeTargetAttribute> targetAttributes;
        {
            XcodeTargetAttribute attribute;
            attribute.target = nativeTarget;
            attribute.CreatedOnToolsVersion = "7.1.1";
            targetAttributes.push_back(std::move(attribute));
        }
        project->addAttribute("TargetAttributes", std::move(targetAttributes));
        return project;
    }();

    auto xcodeProject = std::make_shared<XcodeProject>();
    xcodeProject->name = options.targetName;
    xcodeProject->archiveVersion = "1";
    xcodeProject->objectVersion = "46";
    xcodeProject->rootObject = pbxProject;
    sourceGroup->visit([&](std::shared_ptr<PBXFileReference> source) {
        xcodeProject->fileReferences.push_back(source);
    });
    frameworksGroup->visit([&](std::shared_ptr<PBXFileReference> source) {
        xcodeProject->fileReferences.push_back(source);
    });
    xcodeProject->fileReferences.push_back(productReference);
    xcodeProject->groups.push_back(sourceGroup);
    if (hasFrameworks) {
        xcodeProject->groups.push_back(frameworksGroup);
    }
    xcodeProject->groups.push_back(productsGroup);
    xcodeProject->groups.push_back(mainGroup);
    for (auto & child : sourceGroup->children) {
        if (auto group = std::dynamic_pointer_cast<PBXGroup>(child)) {
            xcodeProject->groups.push_back(group);
        }
    }
    xcodeProject->buildConfigurations.push_back(buildConfigurationDebug);
    xcodeProject->buildConfigurations.push_back(buildConfigurationRelease);
    xcodeProject->buildConfigurations.push_back(buildConfigurationTargetDebug);
    xcodeProject->buildConfigurations.push_back(buildConfigurationTargetRelease);
    xcodeProject->configurationLists.push_back(configurationListForProject);
    xcodeProject->configurationLists.push_back(configurationListForNativeTarget);
    xcodeProject->sourcesBuildPhases.push_back(sourcesBuildPhase);
    xcodeProject->frameworkBuildPhases.push_back(frameworksBuildPhase);
    xcodeProject->copyFilesBuildPhases.push_back(copyFilesBuildPhase);
    xcodeProject->nativeTargets.push_back(nativeTarget);
    xcodeProject->projects.push_back(pbxProject);

    std::sort(std::begin(xcodeProject->groups), std::end(xcodeProject->groups),
        [](const std::shared_ptr<PBXGroup>& a, const std::shared_ptr<PBXGroup>& b) {
            auto cost = [](const PBXGroup& group) {
                int c = 0;
                if (!group.name && !group.path) {
                    c += 42;
                }
                for (auto & child : group.children) {
                    if (child->isa() == "PBXGroup") {
                        c += 1;
                    }
                }
                return c;
            };
            return cost(*a) >= cost(*b);
        });

    return xcodeProject;
}

std::string getFilename(const std::string& path)
{
    return std::get<1>(FileSystem::split(path));
}

void printObjects(XcodePrinter & printer, const XcodeProject& xcodeProject)
{
    constexpr bool isSingleLine = true;

    printer.beginSection("PBXBuildFile");
    auto printPBXBuildFile = [&](
        const std::vector<std::shared_ptr<PBXBuildFile>>& files,
        const std::string& comments) {
        for (auto & f : files) {
            auto & buildFile = *f;
            printer.beginKeyValue(stringifyUUID(
                buildFile.uuid,
                getFilename(buildFile.fileRef->path) + " in " + comments));
                printer.beginObject(isSingleLine);
                printer.printKeyValue("isa", buildFile.isa());
                printer.printKeyValue("fileRef",
                    stringifyUUID(buildFile.fileRef->uuid, getFilename(buildFile.fileRef->path)));
                printer.endObject();
            printer.endKeyValue();
        }
    };
    for (auto & phase : xcodeProject.sourcesBuildPhases) {
        printPBXBuildFile(phase->files, phase->comments());
    }
    for (auto & phase : xcodeProject.frameworkBuildPhases) {
        printPBXBuildFile(phase->files, phase->comments());
    }
    printer.endSection();

    printer.beginSection("PBXCopyFilesBuildPhase");
    for (auto & phase : xcodeProject.copyFilesBuildPhases) {
        printer.beginKeyValue(stringifyUUID(phase->uuid, phase->comments()));
            printer.beginObject();
            printer.printKeyValue("isa", phase->isa());
            printer.printKeyValue("buildActionMask", phase->buildActionMask);
            printer.printKeyValue("dstPath", phase->dstPath);
            printer.printKeyValue("dstSubfolderSpec", phase->dstSubfolderSpec);
            printer.printKeyValue("files", phase->files);
            printer.printKeyValue("runOnlyForDeploymentPostprocessing",
                phase->runOnlyForDeploymentPostprocessing);
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXFileReference");
    for (auto & f : xcodeProject.fileReferences) {
        auto & fileRef = *f;
        printer.beginKeyValue(stringifyUUID(fileRef.uuid, fileRef.path));
            printer.beginObject(isSingleLine);
                printer.printKeyValue("isa", fileRef.isa());
                if (fileRef.explicitFileType) {
                    printer.printKeyValue("explicitFileType", *fileRef.explicitFileType);
                }
                if (fileRef.includeInIndex) {
                    printer.printKeyValue("includeInIndex", *fileRef.includeInIndex);
                }
                if (fileRef.lastKnownFileType) {
                    printer.printKeyValue("lastKnownFileType", *fileRef.lastKnownFileType);
                }
                if (!FileSystem::getDirectoryName(fileRef.path).empty()) {
                    printer.printKeyValue("name", FileSystem::getBaseName(fileRef.path));
                }
                printer.printKeyValue("path", fileRef.path);
                printer.printKeyValue("sourceTree", fileRef.sourceTree);
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXFrameworksBuildPhase");
    for (auto & phase : xcodeProject.frameworkBuildPhases) {
        printer.beginKeyValue(stringifyUUID(phase->uuid, phase->comments()));
            printer.beginObject();
                printer.printKeyValue("isa", phase->isa());
                printer.printKeyValue("buildActionMask", phase->buildActionMask);
                printer.printKeyValue("files", toFileListString(*phase));
                printer.printKeyValue("runOnlyForDeploymentPostprocessing",
                    phase->runOnlyForDeploymentPostprocessing);
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXGroup");
    for (auto & group : xcodeProject.groups) {
        printer.beginKeyValue(group->getUuidWithComment());
            printer.beginObject();
                printer.printKeyValue("isa", group->isa());
                printer.printKeyValue("children", group->getChildrenString());
                if (group->name) {
                    printer.printKeyValue("name", *group->name);
                }
                if (group->path) {
                    printer.printKeyValue("path", *group->path);
                }
                printer.printKeyValue("sourceTree", group->getSourceTree());
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXNativeTarget");
    for (auto & target : xcodeProject.nativeTargets) {
        printer.beginKeyValue(stringifyUUID(target->uuid, target->name));
            printer.beginObject();
                printer.printKeyValue("isa", target->isa());
                printer.printKeyValue("buildConfigurationList", stringifyUUID(
                    target->buildConfigurationList->uuid,
                    "Build configuration list for "
                    + target->isa()
                    + ' '
                    + encodeDoubleQuotes(target->name)));
                printer.printKeyValue("buildPhases", target->getBuildPhasesString());
                printer.printKeyValue("buildRules", target->buildRules);
                printer.printKeyValue("dependencies", target->dependencies);
                printer.printKeyValue("name", target->name);
                printer.printKeyValue("productName", target->productName);
                printer.printKeyValue("productReference",
                    stringifyUUID(target->productReference->uuid, target->productReference->path));
                printer.printKeyValue("productType", target->productType);
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXProject");
    for (auto & project : xcodeProject.projects) {
        printer.beginKeyValue(stringifyUUID(project->uuid, "Project object"));
            printer.beginObject();
                printer.printKeyValue("isa", project->isa());
                printer.printKeyValue("attributes", [&] {
                    printer.beginObject();
                    for (auto & pair : project->attributes) {
                        if (pair.second.is<std::string>()) {
                            printer.printKeyValue(pair.first, pair.second.as<std::string>());
                        }
                        else if (pair.second.is<std::vector<XcodeTargetAttribute>>()) {
                            auto & targetAttributes = pair.second.as<std::vector<XcodeTargetAttribute>>();
                            printer.printKeyValue(pair.first, [&] {
                                printer.beginObject();
                                for (auto & targetAttribute : targetAttributes) {
                                    printer.beginKeyValue(targetAttribute.target->uuid);
                                        printer.beginObject();
                                            if (targetAttribute.CreatedOnToolsVersion) {
                                                printer.printKeyValue("CreatedOnToolsVersion",
                                                    *targetAttribute.CreatedOnToolsVersion);
                                            }
                                            if (targetAttribute.DevelopmentTeam) {
                                                printer.printKeyValue("DevelopmentTeam",
                                                    *targetAttribute.DevelopmentTeam);
                                            }
                                            if (targetAttribute.TestTargetID) {
                                                printer.printKeyValue("TestTargetID",
                                                    *targetAttribute.TestTargetID);
                                            }
                                        printer.endObject();
                                    printer.endKeyValue();
                                }
                                printer.endObject();
                            });
                        }
                    }
                    printer.endObject();
                });
                printer.printKeyValue("buildConfigurationList", stringifyUUID(
                    project->buildConfigurationList->uuid,
                    "Build configuration list for PBXProject "
                        + encodeDoubleQuotes(xcodeProject.name)));
                printer.printKeyValue("compatibilityVersion", project->compatibilityVersion);
                printer.printKeyValue("developmentRegion", project->developmentRegion);
                printer.printKeyValue("hasScannedForEncodings", project->hasScannedForEncodings);
                printer.printKeyValue("knownRegions", project->knownRegions);
                printer.printKeyValue("mainGroup", project->mainGroup->uuid);
                printer.printKeyValue("productRefGroup",
                    stringifyUUID(project->productRefGroup->uuid, project->productRefGroup->name));
                printer.printKeyValue("projectDirPath", project->projectDirPath);
                printer.printKeyValue("projectRoot", project->projectRoot);
                printer.printKeyValue("targets", project->getTargetsString());
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("PBXSourcesBuildPhase");
    for (auto & phase : xcodeProject.sourcesBuildPhases) {
        printer.beginKeyValue(stringifyUUID(phase->uuid, phase->comments()));
            printer.beginObject();
                printer.printKeyValue("isa", phase->isa());
                printer.printKeyValue("buildActionMask", phase->buildActionMask);
                printer.printKeyValue("files", toFileListString(*phase));
                printer.printKeyValue("runOnlyForDeploymentPostprocessing",
                    phase->runOnlyForDeploymentPostprocessing);
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();

    printer.beginSection("XCBuildConfiguration");
    for (auto & config : xcodeProject.buildConfigurations) {
        printer.printKeyValue(stringifyUUID(config->uuid, config->name), [&] {
            printer.beginObject();
                printer.printKeyValue("isa", config->isa());
                printer.printKeyValue("buildSettings", [&] {
                    printObject(printer, config->buildSettings);
                });
                printer.printKeyValue("name", config->name);
            printer.endObject();
        });
    }
    printer.endSection();

    printer.beginSection("XCConfigurationList");
    for (auto & configurationList : xcodeProject.configurationLists) {
        printer.beginKeyValue(stringifyUUID(
            configurationList->uuid,
            "Build configuration list for PBXProject " + encodeDoubleQuotes(xcodeProject.name)));
            printer.beginObject();
                printer.printKeyValue("isa", configurationList->isa());
                printer.printKeyValue("buildConfigurations",
                    configurationList->getBuildConfigurationsString());
                printer.printKeyValue("defaultConfigurationIsVisible",
                    configurationList->defaultConfigurationIsVisible);
                if (configurationList->defaultConfigurationName) {
                    printer.printKeyValue("defaultConfigurationName",
                        *configurationList->defaultConfigurationName);
                }
            printer.endObject();
        printer.endKeyValue();
    }
    printer.endSection();
}

std::string generatePbxproj(const XcodeProject& xcodeProject)
{
    std::stringstream stream;
    stream << "// !$*UTF8*$!\n";

    XcodePrinter printer(stream);
    printer.beginObject();
    printer.printKeyValue("archiveVersion", xcodeProject.archiveVersion);
    printer.printKeyValue("classes", [&] {
        printer.beginObject();
        printer.endObject();
    });
    printer.printKeyValue("objectVersion", xcodeProject.objectVersion);
    printer.printKeyValue("objects", [&] {
        printer.beginObject();
        printObjects(printer, xcodeProject);
        printer.endObject();
    });
    printer.printKeyValue("rootObject",
        stringifyUUID(xcodeProject.rootObject->uuid, "Project object"));
    printer.endObject();

    stream << "\n";
    return stream.str();
}

} // unnamed namespace

GeneratorError Xcode::generateXcodeProject(const CompileOptions& options)
{
    namespace FileSystem = somera::FileSystem;

    const auto xcodeprojPath = FileSystem::join(
        options.generatorOutputDirectory,
        options.targetName + ".xcodeproj");

    if (FileSystem::exists(xcodeprojPath)) {
        if (!FileSystem::isDirectory(xcodeprojPath)) {
            return GeneratorError("Error: A file with the name '" + xcodeprojPath + "' already exists.");
        }
    }
    else {
        FileSystem::createDirectories(xcodeprojPath);
    }

    const auto xcworkspacePath = FileSystem::join(xcodeprojPath, "project.xcworkspace");
    if (!FileSystem::exists(xcworkspacePath)) {
        FileSystem::createDirectories(xcworkspacePath);
    }

    auto xcodeProject = createXcodeProject(options);
    {
        const auto pbxprojPath = FileSystem::join(
            xcodeprojPath, "project.pbxproj");
        std::ofstream stream(pbxprojPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << generatePbxproj(*xcodeProject);
    }
    {
        const auto xcworkspacedataPath = FileSystem::join(
            xcworkspacePath, "contents.xcworkspacedata");
        std::ofstream stream(xcworkspacedataPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        auto xcodeprojName = std::get<1>(FileSystem::split(xcodeprojPath));
        stream << generateXCWorkSpaceData(xcodeprojName);
    }
    return {};
}

} // namespace somera
