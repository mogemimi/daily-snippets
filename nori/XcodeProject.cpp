// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "XcodeProject.h"
#include "somera/Any.h"
#include "somera/FileSystem.h"
#include "somera/Optional.h"
#include "somera/StringHelper.h"
#include <algorithm>
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

std::string GenerateXcodeID() noexcept
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

std::string GenerateXCWorkSpaceData(const std::string& xcodeprojName)
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

std::string EncodeDoubleQuotes(const std::string& comment)
{
    return '\"' + comment + '\"';
}

std::string EncodeString(const std::string& comment)
{
    if (comment.empty()) {
        return "\"\"";
    }

    bool needToAddDoubleQuotes = false;
    for (auto c : comment) {
        if ((c == '_') ||
            (c == '.') ||
            ('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z') ||
            ('0' <= c && c <= '9')) {
            continue;
        }
        needToAddDoubleQuotes = true;
    }

    if (!needToAddDoubleQuotes) {
        return comment;
    }

    return '\"' + comment + '\"';
}

std::string StringifyUUID(const std::string& uuid, const std::string& comment)
{
    std::stringstream stream;
    stream << uuid;
    if (!comment.empty()) {
        stream << ' ' << "/* " << comment << " */";
    }
    return stream.str();
}

bool IsUpperCase(const std::string& word)
{
    std::string lowerCases = "abcdefghi";
    for (auto & c : word) {
        if ('A' <= c && c <= 'Z') {
            return true;
        }
        if ('a' <= c && c <= 'z') {
            return false;
        }
    }
    return false;
}

struct XcodeObject {
    XcodeObject(const XcodeObject&) = delete;
    XcodeObject & operator=(const XcodeObject&) = delete;

    virtual ~XcodeObject() = default;
    virtual std::string isa() const noexcept = 0;

    XcodeObject() : uuid(GenerateXcodeID()) {}

    std::string GetUuid() const noexcept
    {
        return uuid;
    }

private:
    std::shared_ptr<XcodeObject> parent;
    std::string const uuid;
};

struct XcodeBuildPhase : public XcodeObject {
    virtual ~XcodeBuildPhase() = default;
    virtual std::string GetComment() const noexcept = 0;
};

struct XcodeTargetAttribute final {
    std::shared_ptr<PBXNativeTarget> target;
    Optional<std::string> CreatedOnToolsVersion;
    Optional<std::string> DevelopmentTeam;
    Optional<std::string> TestTargetID;
};

struct XcodeProject final {
    XcodeProject() = default;
    XcodeProject(const XcodeProject&) = delete;
    XcodeProject & operator=(const XcodeProject&) = delete;

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

    void Visit(const std::function<void(std::shared_ptr<PBXFileReference>)>& func) const
    {
        assert(func);
        for (auto & child : children) {
            if (auto file = std::dynamic_pointer_cast<PBXFileReference>(child)) {
                func(file);
            }
            else if (auto group = std::dynamic_pointer_cast<PBXGroup>(child)) {
                group->Visit(func);
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

    void AddAttribute(const std::string& key, const std::string& value)
    {
        attributes.emplace(key, value);
    }

    void AddAttribute(const std::string& key, std::vector<XcodeTargetAttribute> && value)
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

    std::string GetComment() const noexcept override { return "CopyFiles"; }
};

struct PBXFrameworksBuildPhase final : public XcodeBuildPhase {
    std::string isa() const noexcept override { return "PBXFrameworksBuildPhase"; }
    std::string buildActionMask;
    std::vector<std::shared_ptr<PBXBuildFile>> files;
    std::string runOnlyForDeploymentPostprocessing;

    std::string GetComment() const noexcept override { return "Frameworks"; }
};

struct PBXSourcesBuildPhase final : public XcodeBuildPhase {
    std::string isa() const noexcept override { return "PBXSourcesBuildPhase"; }
    std::string buildActionMask;
    std::vector<std::shared_ptr<PBXBuildFile>> files;
    std::string runOnlyForDeploymentPostprocessing;

    std::string GetComment() const noexcept override { return "Sources"; }
};

struct XCBuildConfiguration final : public XcodeObject {
    std::string isa() const noexcept override { return "XCBuildConfiguration"; }
    std::vector<std::pair<std::string, Any>> buildSettings;
    std::string name;

    void AddBuildSettings(const std::string& key, const std::string& value)
    {
        auto iter = std::find_if(std::begin(buildSettings), std::end(buildSettings),
            [&](const auto& a){ return a.first == key; });
        if (iter != std::end(buildSettings)) {
            iter->second = value;
            return;
        }
        buildSettings.emplace_back(key, value);
        std::stable_sort(std::begin(buildSettings), std::end(buildSettings),
            [](const auto& a, const auto& b){ return a.first < b.first; });
    }

    void AddBuildSettings(const std::string& key, const std::vector<std::string>& value)
    {
        auto iter = std::find_if(std::begin(buildSettings), std::end(buildSettings),
            [&](const auto& a){ return a.first == key; });
        if (iter != std::end(buildSettings)) {
            iter->second = value;
            return;
        }
        buildSettings.emplace_back(key, value);
        std::stable_sort(std::begin(buildSettings), std::end(buildSettings),
            [](const auto& a, const auto& b){ return a.first < b.first; });
    }
};

struct XCConfigurationList final : public XcodeObject {
    std::string isa() const noexcept override { return "XCConfigurationList"; }
    std::vector<std::shared_ptr<XCBuildConfiguration>> buildConfigurations;
    std::string defaultConfigurationIsVisible;
    std::string targetTypeName;
    Optional<std::string> defaultConfigurationName;
};

struct XcodePrinterSettings {
    bool isSingleLine = false;
};

struct UUIDWithComment {
    std::string uuid;
    std::string comment;
};

UUIDWithComment MakeUUIDWithComment(const std::string& uuid, const std::string& comment)
{
    UUIDWithComment pair;
    pair.uuid = uuid;
    pair.comment = comment;
    return pair;
}

UUIDWithComment MakeUUIDWithComment(const std::string& uuid, const Optional<std::string>& comment)
{
    UUIDWithComment pair;
    pair.uuid = uuid;
    if (comment) {
        pair.comment = *comment;
    }
    return pair;
}

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

    std::string GetIndent() const noexcept
    {
        std::string spaces;
        for (int i = 0; i < tabs; ++i) {
            spaces += "\t";
        }
        return spaces;
    }

    void BeginKeyValue(const std::string& key)
    {
        if (!IsSingleLine()) {
            stream << GetIndent();
        }
        stream << key << " = ";
    }

    void BeginKeyValue(const UUIDWithComment& key)
    {
        if (!IsSingleLine()) {
            stream << GetIndent();
        }
        stream << StringifyUUID(key.uuid, key.comment) << " = ";
    }

    void EndKeyValue()
    {
        stream << ";";
        if (!IsSingleLine()) {
            stream << "\n";
        } else {
            stream << " ";
        }
    }

    void PrintKeyValue(const std::string& key, const std::string& value)
    {
        BeginKeyValue(key);
        stream << EncodeString(value);
        EndKeyValue();
    }

    void PrintKeyValue(const std::string& key, const UUIDWithComment& value)
    {
        BeginKeyValue(key);
        stream << StringifyUUID(value.uuid, value.comment);
        EndKeyValue();
    }

    void PrintKeyValue(const UUIDWithComment& key, const std::function<void()>& valuePrinter)
    {
        BeginKeyValue(key);
        valuePrinter();
        EndKeyValue();
    }

    void PrintKeyValue(const std::string& key, const std::function<void()>& valuePrinter)
    {
        BeginKeyValue(key);
        valuePrinter();
        EndKeyValue();
    }

    void PrintKeyValue(const std::string& key, const std::vector<std::string>& array)
    {
        BeginKeyValue(key);
        if (array.size() == 1 && IsUpperCase(key)) {
            auto & value = array.front();
            stream << EncodeString(value);
        }
        else {
            stream << "(";
            if (!IsSingleLine()) {
                stream << "\n";
            }
            ++tabs;
            for (auto & value : array) {
                stream << GetIndent() << EncodeString(value) << ",";
                if (!IsSingleLine()) {
                    stream << "\n";
                } else {
                    stream << " ";
                }
            }
            --tabs;
            stream << GetIndent() << ")";
        }
        EndKeyValue();
    }

    void PrintKeyValue(const std::string& key, const std::vector<UUIDWithComment>& array)
    {
        BeginKeyValue(key);
        if (array.size() == 1 && IsUpperCase(key)) {
            auto & value = array.front();
            stream << StringifyUUID(value.uuid, value.comment);
        }
        else {
            stream << "(";
            if (!IsSingleLine()) {
                stream << "\n";
            }
            ++tabs;
            for (auto & value : array) {
                stream << GetIndent() << StringifyUUID(value.uuid, value.comment) << ",";
                if (!IsSingleLine()) {
                    stream << "\n";
                } else {
                    stream << " ";
                }
            }
            --tabs;
            stream << GetIndent() << ")";
        }
        EndKeyValue();
    }

    void BeginObject()
    {
        XcodePrinterSettings settings;
        settings.isSingleLine = false;
        BeginObject(std::move(settings));
    }

    void BeginObject(XcodePrinterSettings && settings)
    {
        settingsStack.push_back(std::move(settings));
        stream << "{";
        if (!IsSingleLine()) {
            stream << "\n";
            ++tabs;
        }
    }

    void EndObject()
    {
        if (!IsSingleLine()) {
            --tabs;
            stream << GetIndent();
        }
        stream << "}";
        settingsStack.pop_back();
    }

    bool IsSingleLine() const
    {
        assert(!settingsStack.empty());
        return settingsStack.back().isSingleLine;
    }

    void BeginSection(const std::string& sectionIn)
    {
        XcodePrinterSettings settings;
        settings.isSingleLine = false;
        settingsStack.push_back(std::move(settings));
        this->section = sectionIn;
        stream << "\n";
        stream << "/* Begin " << section << " section */\n";
    }

    void EndSection()
    {
        stream << "/* End " << section << " section */\n";
        settingsStack.pop_back();
    }
};

void PrintObject(
    XcodePrinter & printer,
    const std::vector<std::pair<std::string, Any>>& object)
{
    printer.BeginObject();
    for (auto & pair : object) {
        auto & key = pair.first;
        auto & value = pair.second;
        if (value.is<std::string>()) {
            printer.PrintKeyValue(key, value.as<std::string>());
        }
        else if (pair.second.is<std::vector<std::string>>()) {
            printer.PrintKeyValue(key, value.as<std::vector<std::string>>());
        }
    }
    printer.EndObject();
}

std::string FindLastKnownFileType(const std::string& path) noexcept
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
        return "sourcecode.c.c";
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
    if (ext == "framework") {
        return "wrapper.framework";
    }
    return "sourcecode";
}

bool IsSourceFile(const std::string& path) noexcept
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

void SetDefaultBuildConfig(XCBuildConfiguration& config)
{
    config.AddBuildSettings("ALWAYS_SEARCH_USER_PATHS", "NO");
    config.AddBuildSettings("CLANG_CXX_LANGUAGE_STANDARD", "c++17");
    config.AddBuildSettings("CLANG_CXX_LIBRARY", "libc++");
    config.AddBuildSettings("CLANG_ENABLE_MODULES", "YES");
    config.AddBuildSettings("CLANG_ENABLE_OBJC_ARC", "YES");
    config.AddBuildSettings("CLANG_WARN_BLOCK_CAPTURE_AUTORELEASING", "YES");
    config.AddBuildSettings("CLANG_WARN_BOOL_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_COMMA", "YES");
    config.AddBuildSettings("CLANG_WARN_CONSTANT_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_DIRECT_OBJC_ISA_USAGE", "YES_ERROR");
    config.AddBuildSettings("CLANG_WARN_EMPTY_BODY", "YES");
    config.AddBuildSettings("CLANG_WARN_ENUM_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_INFINITE_RECURSION", "YES");
    config.AddBuildSettings("CLANG_WARN_INT_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_NON_LITERAL_NULL_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_OBJC_LITERAL_CONVERSION", "YES");
    config.AddBuildSettings("CLANG_WARN_OBJC_ROOT_CLASS", "YES_ERROR");
    config.AddBuildSettings("CLANG_WARN_RANGE_LOOP_ANALYSIS", "YES");
    config.AddBuildSettings("CLANG_WARN_STRICT_PROTOTYPES", "YES");
    config.AddBuildSettings("CLANG_WARN_SUSPICIOUS_MOVE", "YES");
    config.AddBuildSettings("CLANG_WARN_UNREACHABLE_CODE", "YES");
    config.AddBuildSettings("CLANG_WARN__DUPLICATE_METHOD_MATCH", "YES");
    config.AddBuildSettings("CODE_SIGN_IDENTITY", "-");
    config.AddBuildSettings("COPY_PHASE_STRIP", "NO");
    config.AddBuildSettings("GCC_C_LANGUAGE_STANDARD", "c11");
    config.AddBuildSettings("GCC_NO_COMMON_BLOCKS", "YES");
    config.AddBuildSettings("GCC_WARN_64_TO_32_BIT_CONVERSION", "YES");
    config.AddBuildSettings("GCC_WARN_ABOUT_MISSING_FIELD_INITIALIZERS", "YES");
    config.AddBuildSettings("GCC_WARN_ABOUT_MISSING_NEWLINE", "YES");
    config.AddBuildSettings("GCC_WARN_ABOUT_MISSING_PROTOTYPES", "YES");
    config.AddBuildSettings("GCC_WARN_ABOUT_RETURN_TYPE", "YES_ERROR");
    config.AddBuildSettings("GCC_WARN_SHADOW", "YES");
    config.AddBuildSettings("GCC_WARN_SIGN_COMPARE", "YES");
    config.AddBuildSettings("GCC_WARN_UNDECLARED_SELECTOR", "YES");
    config.AddBuildSettings("GCC_WARN_UNINITIALIZED_AUTOS", "YES_AGGRESSIVE");
    config.AddBuildSettings("GCC_WARN_UNKNOWN_PRAGMAS", "YES");
    config.AddBuildSettings("GCC_WARN_UNUSED_FUNCTION", "YES");
    config.AddBuildSettings("GCC_WARN_UNUSED_LABEL", "YES");
    config.AddBuildSettings("GCC_WARN_UNUSED_VARIABLE", "YES");
    config.AddBuildSettings("MACOSX_DEPLOYMENT_TARGET", "10.11");
    config.AddBuildSettings("SDKROOT", "macosx");
}

void SetSearchPathsToBuildConfig(
    XCBuildConfiguration& config,
    const CompileOptions& options)
{
    if (!options.includeSearchPaths.empty()) {
        config.AddBuildSettings("HEADER_SEARCH_PATHS", options.includeSearchPaths);
    }
    if (!options.librarySearchPaths.empty()) {
        config.AddBuildSettings("LIBRARY_SEARCH_PATHS", options.librarySearchPaths);
    }
    if (!options.otherLinkerFlags.empty()) {
        config.AddBuildSettings("OTHER_LDFLAGS", options.otherLinkerFlags);
    }

    if (!options.enableCppExceptions) {
        config.AddBuildSettings("GCC_ENABLE_CPP_EXCEPTIONS", "NO");
    }
    if (!options.enableCppRtti) {
        config.AddBuildSettings("GCC_ENABLE_CPP_RTTI", "NO");
    }

    {
        ///@todo Please refactor here
        auto iter = options.buildSettings.find("-std=");
        if (iter != std::end(options.buildSettings)) {
            config.AddBuildSettings("CLANG_CXX_LANGUAGE_STANDARD", iter->second);
        }
    }
    {
        ///@todo Please refactor here
        auto iter = options.buildSettings.find("-stdlib=");
        if (iter != std::end(options.buildSettings)) {
            config.AddBuildSettings("CLANG_CXX_LIBRARY", iter->second);
        }
    }
}

std::shared_ptr<XcodeProject> CreateXcodeProject(const CompileOptions& options)
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
        fileRef->explicitFileType = "compiled.mach-o.executable";
        fileRef->includeInIndex = "0";
        fileRef->path = options.productName;
        fileRef->sourceTree = "BUILT_PRODUCTS_DIR";
        productsGroup->children.push_back(fileRef);
        return fileRef;
    }();

    for (auto & source : options.sources) {
        auto fileRef = std::make_shared<PBXFileReference>();
        fileRef->lastKnownFileType = FindLastKnownFileType(source);
        fileRef->path = source;
        fileRef->sourceTree = "<group>";

        auto getGroup = [&](const std::string& directory) -> std::shared_ptr<PBXGroup> {
            if (directory.empty()) {
                return sourceGroup;
            }
            auto iter = std::find_if(
                std::begin(sourceGroup->children),
                std::end(sourceGroup->children),
                [&](const std::shared_ptr<XcodeObject>& object) {
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

        const auto directory = std::get<0>(FileSystem::split(source));
        const auto group = getGroup(directory);
        group->children.push_back(fileRef);
    }

    std::stable_sort(std::begin(sourceGroup->children), std::end(sourceGroup->children),
        [](const std::shared_ptr<XcodeObject>& a, const std::shared_ptr<XcodeObject>& b) {
            std::string nameA;
            std::string nameB;
            int costA = 0;
            int costB = 0;
            {
                auto groupA = std::dynamic_pointer_cast<PBXGroup>(a);
                if (groupA && groupA->name) {
                    nameA = *groupA->name;
                    costA += 1;
                }

                auto groupB = std::dynamic_pointer_cast<PBXGroup>(b);
                if (groupB && groupB->name) {
                    nameB = *groupB->name;
                    costB += 1;
                }
            }
            if (costA + costB >= 2) {
                return nameA < nameB;
            }
            if (costA + costB >= 1) {
                return costA > costB;
            }
            return a->GetUuid() < b->GetUuid();
        });

    for (auto & library : options.libraries) {
        auto fileRef = std::make_shared<PBXFileReference>();
        fileRef->lastKnownFileType = FindLastKnownFileType(library);
        if ("tbd" == std::get<1>(FileSystem::splitExtension(library))) {
            ///@todo This code is bad.
            fileRef->path = FileSystem::join("usr/lib/", library);
            fileRef->sourceTree = "SDKROOT";
        }
        else if ("framework" == std::get<1>(FileSystem::splitExtension(library))) {
            fileRef->path = FileSystem::join("System/Library/Frameworks/", library);
            fileRef->sourceTree = "SDKROOT";
        }
        else {
            fileRef->path = library;
            fileRef->sourceTree = "<group>";
        }
        frameworksGroup->children.push_back(fileRef);
    }

    const auto buildConfigurationDebug = [&] {
        auto definitions = options.preprocessorDefinitions;
        definitions.push_back("DEBUG=1");
        definitions.push_back("$(inherited)");
    
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Debug";
        SetDefaultBuildConfig(*config);
        SetSearchPathsToBuildConfig(*config, options);
        config->AddBuildSettings("DEBUG_INFORMATION_FORMAT", "dwarf");
        config->AddBuildSettings("ENABLE_STRICT_OBJC_MSGSEND", "YES");
        config->AddBuildSettings("ENABLE_TESTABILITY", "YES");
        config->AddBuildSettings("GCC_DYNAMIC_NO_PIC", "NO");
        config->AddBuildSettings("GCC_OPTIMIZATION_LEVEL", "0");
        config->AddBuildSettings("GCC_PREPROCESSOR_DEFINITIONS", definitions);
        config->AddBuildSettings("MTL_ENABLE_DEBUG_INFO", "YES");
        config->AddBuildSettings("ONLY_ACTIVE_ARCH", "YES");
        return config;
    } ();
    const auto buildConfigurationRelease = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Release";
        SetDefaultBuildConfig(*config);
        SetSearchPathsToBuildConfig(*config, options);
        config->AddBuildSettings("DEBUG_INFORMATION_FORMAT", "dwarf-with-dsym");
        config->AddBuildSettings("ENABLE_NS_ASSERTIONS", "NO");
        config->AddBuildSettings("ENABLE_STRICT_OBJC_MSGSEND", "YES");
        if (!options.preprocessorDefinitions.empty()) {
            config->AddBuildSettings("GCC_PREPROCESSOR_DEFINITIONS", options.preprocessorDefinitions);
        }
        config->AddBuildSettings("MTL_ENABLE_DEBUG_INFO", "NO");
        return config;
    }();
    const auto buildConfigurationTargetDebug = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Debug";
        config->AddBuildSettings("PRODUCT_NAME", "$(TARGET_NAME)");
        return config;
    }();
    const auto buildConfigurationTargetRelease = [&] {
        auto config = std::make_shared<XCBuildConfiguration>();
        config->name = "Release";
        config->AddBuildSettings("PRODUCT_NAME", "$(TARGET_NAME)");
        return config;
    }();

    const auto configurationListForProject = [&] {
        auto configurationList = std::make_shared<XCConfigurationList>();
        configurationList->buildConfigurations.push_back(buildConfigurationDebug);
        configurationList->buildConfigurations.push_back(buildConfigurationRelease);
        configurationList->defaultConfigurationIsVisible = "0";
        configurationList->defaultConfigurationName = "Release";
        configurationList->targetTypeName = "PBXProject";
        return configurationList;
    }();
    const auto configurationListForNativeTarget = [&] {
        auto configurationList = std::make_shared<XCConfigurationList>();
        configurationList->buildConfigurations.push_back(buildConfigurationTargetDebug);
        configurationList->buildConfigurations.push_back(buildConfigurationTargetRelease);
        configurationList->defaultConfigurationIsVisible = "0";
        configurationList->defaultConfigurationName = "Release";
        configurationList->targetTypeName = "PBXNativeTarget";
        return configurationList;
    }();

    const auto sourcesBuildPhase = [&] {
        auto phase = std::make_shared<PBXSourcesBuildPhase>();
        phase->buildActionMask = "2147483647";
        phase->runOnlyForDeploymentPostprocessing = "0";
        sourceGroup->Visit([&](std::shared_ptr<PBXFileReference> source) {
            if (IsSourceFile(source->path)) {
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
        frameworksGroup->Visit([&](std::shared_ptr<PBXFileReference> source) {
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
        target->productType = "com.apple.product-type.tool";
        return target;
    }();

    const auto pbxProject = [&] {
        auto project = std::make_shared<PBXProject>();
        project->buildConfigurationList = configurationListForProject;
        project->compatibilityVersion = "Xcode 3.2";
        project->developmentRegion = "English";
        project->hasScannedForEncodings = "0";
        project->knownRegions = {"en"};
        project->mainGroup = mainGroup;
        project->productRefGroup = productsGroup;
        project->projectDirPath = "";
        project->projectRoot = "";
        project->targets.push_back(nativeTarget);

        project->AddAttribute("LastUpgradeCheck", "0800");
        if (!options.author.empty()) {
            project->AddAttribute("ORGANIZATIONNAME", options.author);
        }

        std::vector<XcodeTargetAttribute> targetAttributes;
        {
            XcodeTargetAttribute attribute;
            attribute.target = nativeTarget;
            attribute.CreatedOnToolsVersion = "7.1.1";
            targetAttributes.push_back(std::move(attribute));
        }
        project->AddAttribute("TargetAttributes", std::move(targetAttributes));
        return project;
    }();

    auto xcodeProject = std::make_shared<XcodeProject>();
    xcodeProject->name = options.targetName;
    xcodeProject->archiveVersion = "1";
    xcodeProject->objectVersion = "46";
    xcodeProject->rootObject = pbxProject;
    sourceGroup->Visit([&](std::shared_ptr<PBXFileReference> source) {
        xcodeProject->fileReferences.push_back(source);
    });
    frameworksGroup->Visit([&](std::shared_ptr<PBXFileReference> source) {
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

    std::stable_sort(std::begin(xcodeProject->groups), std::end(xcodeProject->groups),
        [](const std::shared_ptr<PBXGroup>& a, const std::shared_ptr<PBXGroup>& b) {
            return a->GetUuid() < b->GetUuid();
        });

    std::stable_sort(std::begin(xcodeProject->fileReferences), std::end(xcodeProject->fileReferences),
        [](const std::shared_ptr<PBXFileReference>& a, const std::shared_ptr<PBXFileReference>& b) {
            return a->GetUuid() < b->GetUuid();
        });

    return xcodeProject;
}

std::string GenerateComment(
    const std::shared_ptr<PBXFileReference>& fileRef,
    Optional<std::string> buildPhaseComment = somera::NullOpt)
{
    auto baseName = FileSystem::getBaseName(fileRef->path);
    auto comment = !baseName.empty() ? baseName : fileRef->path;
    if (buildPhaseComment) {
        comment = comment + " in " + *buildPhaseComment;
    }
    return comment;
}


template <class BuildPhase>
std::vector<UUIDWithComment> ToFileListString(const BuildPhase& phase)
{
    static_assert(std::is_base_of<XcodeBuildPhase, BuildPhase>::value, "");
    std::vector<UUIDWithComment> result;
    for (auto & buildFile : phase.files) {
        UUIDWithComment pair;
        pair.uuid = buildFile->GetUuid();
        pair.comment = GenerateComment(buildFile->fileRef, phase.GetComment());
        result.push_back(std::move(pair));
    }
    return result;
}

template <typename BuildPhase>
void PrintPBXBuildFiles(XcodePrinter & printer, const BuildPhase& phase)
{
    for (auto & buildFile : phase.files) {
        printer.BeginKeyValue(MakeUUIDWithComment(
            buildFile->GetUuid(),
            GenerateComment(buildFile->fileRef, phase.GetComment())));
        XcodePrinterSettings settings;
        settings.isSingleLine = true;
        printer.BeginObject(std::move(settings));
        printer.PrintKeyValue("isa", buildFile->isa());
        printer.PrintKeyValue("fileRef", MakeUUIDWithComment(
            buildFile->fileRef->GetUuid(),
            GenerateComment(buildFile->fileRef)));
        printer.EndObject();
        printer.EndKeyValue();
    }
}

std::vector<UUIDWithComment> GetTargetsString(const PBXProject& project)
{
    std::vector<UUIDWithComment> result;
    for (auto & target : project.targets) {
        UUIDWithComment pair;
        pair.uuid = target->GetUuid();
        pair.comment = target->name;
        result.push_back(std::move(pair));
    }
    return result;
}

std::vector<UUIDWithComment> GetBuildPhasesString(const PBXNativeTarget& target)
{
    std::vector<UUIDWithComment> result;
    for (auto & phase : target.buildPhases) {
        UUIDWithComment pair;
        pair.uuid = phase->GetUuid();
        pair.comment = phase->GetComment();
        result.push_back(std::move(pair));
    }
    return result;
}

std::string GetSourceTree(const PBXGroup& group) noexcept
{
    return group.sourceTree ? *group.sourceTree : "<group>";
}

UUIDWithComment GetUuidWithComment(const PBXGroup& group)
{
    if (group.name) {
        return MakeUUIDWithComment(group.GetUuid(), *group.name);
    }
    if (group.path) {
        return MakeUUIDWithComment(group.GetUuid(), *group.path);
    }
    return MakeUUIDWithComment(group.GetUuid(), "");
}

std::vector<UUIDWithComment> GetChildrenString(const PBXGroup& group)
{
    std::vector<UUIDWithComment> result;
    for (auto & child : group.children) {
        if (auto childGroup = std::dynamic_pointer_cast<PBXGroup>(child)) {
            result.push_back(GetUuidWithComment(*childGroup));
        }
        else if (auto file = std::dynamic_pointer_cast<PBXFileReference>(child)) {
            result.push_back(MakeUUIDWithComment(file->GetUuid(), GenerateComment(file)));
        }
    }
    return result;
}

std::vector<UUIDWithComment> GetBuildConfigurationsString(const XCConfigurationList& configurationList)
{
    std::vector<UUIDWithComment> result;
    for (auto & buildConfig : configurationList.buildConfigurations) {
        result.push_back(MakeUUIDWithComment(buildConfig->GetUuid(), buildConfig->name));
    }
    return result;
}

void PrintObjects(XcodePrinter & printer, const XcodeProject& xcodeProject)
{
    printer.BeginSection("PBXBuildFile");
    for (auto & phase : xcodeProject.sourcesBuildPhases) {
        PrintPBXBuildFiles(printer, *phase);
    }
    for (auto & phase : xcodeProject.frameworkBuildPhases) {
        PrintPBXBuildFiles(printer, *phase);
    }
    printer.EndSection();

    printer.BeginSection("PBXCopyFilesBuildPhase");
    for (auto & phase : xcodeProject.copyFilesBuildPhases) {
        printer.BeginKeyValue(MakeUUIDWithComment(phase->GetUuid(), phase->GetComment()));
            printer.BeginObject();
            printer.PrintKeyValue("isa", phase->isa());
            printer.PrintKeyValue("buildActionMask", phase->buildActionMask);
            printer.PrintKeyValue("dstPath", phase->dstPath);
            printer.PrintKeyValue("dstSubfolderSpec", phase->dstSubfolderSpec);
            printer.PrintKeyValue("files", phase->files);
            printer.PrintKeyValue("runOnlyForDeploymentPostprocessing",
                phase->runOnlyForDeploymentPostprocessing);
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXFileReference");
    for (auto & fileRef : xcodeProject.fileReferences) {
        printer.BeginKeyValue(MakeUUIDWithComment(fileRef->GetUuid(), GenerateComment(fileRef)));
            XcodePrinterSettings settings;
            settings.isSingleLine = true;
            printer.BeginObject(std::move(settings));
                printer.PrintKeyValue("isa", fileRef->isa());
                if (fileRef->explicitFileType) {
                    printer.PrintKeyValue("explicitFileType", *fileRef->explicitFileType);
                }
                if (fileRef->includeInIndex) {
                    printer.PrintKeyValue("includeInIndex", *fileRef->includeInIndex);
                }
                if (fileRef->lastKnownFileType) {
                    printer.PrintKeyValue("lastKnownFileType", *fileRef->lastKnownFileType);
                }
                if (!FileSystem::getDirectoryName(fileRef->path).empty()) {
                    printer.PrintKeyValue("name", FileSystem::getBaseName(fileRef->path));
                }
                printer.PrintKeyValue("path", fileRef->path);
                printer.PrintKeyValue("sourceTree", fileRef->sourceTree);
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXFrameworksBuildPhase");
    for (auto & phase : xcodeProject.frameworkBuildPhases) {
        printer.BeginKeyValue(MakeUUIDWithComment(phase->GetUuid(), phase->GetComment()));
            printer.BeginObject();
                printer.PrintKeyValue("isa", phase->isa());
                printer.PrintKeyValue("buildActionMask", phase->buildActionMask);
                printer.PrintKeyValue("files", ToFileListString(*phase));
                printer.PrintKeyValue("runOnlyForDeploymentPostprocessing",
                    phase->runOnlyForDeploymentPostprocessing);
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXGroup");
    for (auto & group : xcodeProject.groups) {
        const auto pair = GetUuidWithComment(*group);
        printer.BeginKeyValue(MakeUUIDWithComment(pair.uuid, pair.comment));
            printer.BeginObject();
                printer.PrintKeyValue("isa", group->isa());
                printer.PrintKeyValue("children", GetChildrenString(*group));
                if (group->name) {
                    printer.PrintKeyValue("name", *group->name);
                }
                if (group->path) {
                    printer.PrintKeyValue("path", *group->path);
                }
                printer.PrintKeyValue("sourceTree", GetSourceTree(*group));
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXNativeTarget");
    for (auto & target : xcodeProject.nativeTargets) {
        printer.BeginKeyValue(MakeUUIDWithComment(target->GetUuid(), target->name));
            printer.BeginObject();
                printer.PrintKeyValue("isa", target->isa());
                printer.PrintKeyValue("buildConfigurationList", MakeUUIDWithComment(
                    target->buildConfigurationList->GetUuid(),
                    "Build configuration list for "
                        + target->isa()
                        + ' '
                        + EncodeDoubleQuotes(target->name)));
                printer.PrintKeyValue("buildPhases", GetBuildPhasesString(*target));
                printer.PrintKeyValue("buildRules", target->buildRules);
                printer.PrintKeyValue("dependencies", target->dependencies);
                printer.PrintKeyValue("name", target->name);
                printer.PrintKeyValue("productName", target->productName);
                printer.PrintKeyValue("productReference", MakeUUIDWithComment(
                    target->productReference->GetUuid(),
                    target->productReference->path));
                printer.PrintKeyValue("productType", target->productType);
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXProject");
    for (auto & project : xcodeProject.projects) {
        printer.BeginKeyValue(MakeUUIDWithComment(project->GetUuid(), "Project object"));
            printer.BeginObject();
                printer.PrintKeyValue("isa", project->isa());
                printer.PrintKeyValue("attributes", [&] {
                    printer.BeginObject();
                    for (auto & pair : project->attributes) {
                        if (pair.second.is<std::string>()) {
                            printer.PrintKeyValue(pair.first, pair.second.as<std::string>());
                        }
                        else if (pair.second.is<std::vector<XcodeTargetAttribute>>()) {
                            auto & targetAttributes = pair.second.as<std::vector<XcodeTargetAttribute>>();
                            printer.PrintKeyValue(pair.first, [&] {
                                printer.BeginObject();
                                for (auto & targetAttribute : targetAttributes) {
                                    printer.BeginKeyValue(targetAttribute.target->GetUuid());
                                        printer.BeginObject();
                                            if (targetAttribute.CreatedOnToolsVersion) {
                                                printer.PrintKeyValue("CreatedOnToolsVersion",
                                                    *targetAttribute.CreatedOnToolsVersion);
                                            }
                                            if (targetAttribute.DevelopmentTeam) {
                                                printer.PrintKeyValue("DevelopmentTeam",
                                                    *targetAttribute.DevelopmentTeam);
                                            }
                                            if (targetAttribute.TestTargetID) {
                                                printer.PrintKeyValue("TestTargetID",
                                                    *targetAttribute.TestTargetID);
                                            }
                                        printer.EndObject();
                                    printer.EndKeyValue();
                                }
                                printer.EndObject();
                            });
                        }
                    }
                    printer.EndObject();
                });
                printer.PrintKeyValue("buildConfigurationList", MakeUUIDWithComment(
                    project->buildConfigurationList->GetUuid(),
                    "Build configuration list for "
                        + project->isa()
                        + ' '
                        + EncodeDoubleQuotes(xcodeProject.name)));
                printer.PrintKeyValue("compatibilityVersion", project->compatibilityVersion);
                printer.PrintKeyValue("developmentRegion", project->developmentRegion);
                printer.PrintKeyValue("hasScannedForEncodings", project->hasScannedForEncodings);
                printer.PrintKeyValue("knownRegions", project->knownRegions);
                printer.PrintKeyValue("mainGroup", project->mainGroup->GetUuid());
                printer.PrintKeyValue("productRefGroup",
                    MakeUUIDWithComment(project->productRefGroup->GetUuid(), project->productRefGroup->name));
                printer.PrintKeyValue("projectDirPath", project->projectDirPath);
                printer.PrintKeyValue("projectRoot", project->projectRoot);
                printer.PrintKeyValue("targets", GetTargetsString(*project));
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("PBXSourcesBuildPhase");
    for (auto & phase : xcodeProject.sourcesBuildPhases) {
        printer.BeginKeyValue(MakeUUIDWithComment(phase->GetUuid(), phase->GetComment()));
            printer.BeginObject();
                printer.PrintKeyValue("isa", phase->isa());
                printer.PrintKeyValue("buildActionMask", phase->buildActionMask);
                printer.PrintKeyValue("files", ToFileListString(*phase));
                printer.PrintKeyValue("runOnlyForDeploymentPostprocessing",
                    phase->runOnlyForDeploymentPostprocessing);
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();

    printer.BeginSection("XCBuildConfiguration");
    for (auto & config : xcodeProject.buildConfigurations) {
        printer.PrintKeyValue(MakeUUIDWithComment(config->GetUuid(), config->name), [&] {
            printer.BeginObject();
                printer.PrintKeyValue("isa", config->isa());
                printer.PrintKeyValue("buildSettings", [&] {
                    PrintObject(printer, config->buildSettings);
                });
                printer.PrintKeyValue("name", config->name);
            printer.EndObject();
        });
    }
    printer.EndSection();

    printer.BeginSection("XCConfigurationList");
    for (auto & configurationList : xcodeProject.configurationLists) {
        printer.BeginKeyValue(MakeUUIDWithComment(
            configurationList->GetUuid(),
            "Build configuration list for "
                + configurationList->targetTypeName
                + ' '
                + EncodeDoubleQuotes(xcodeProject.name)));
            printer.BeginObject();
                printer.PrintKeyValue("isa", configurationList->isa());
                printer.PrintKeyValue("buildConfigurations",
                    GetBuildConfigurationsString(*configurationList));
                printer.PrintKeyValue("defaultConfigurationIsVisible",
                    configurationList->defaultConfigurationIsVisible);
                if (configurationList->defaultConfigurationName) {
                    printer.PrintKeyValue("defaultConfigurationName",
                        *configurationList->defaultConfigurationName);
                }
            printer.EndObject();
        printer.EndKeyValue();
    }
    printer.EndSection();
}

std::string GeneratePbxproj(const XcodeProject& xcodeProject)
{
    std::stringstream stream;
    stream << "// !$*UTF8*$!\n";

    XcodePrinter printer(stream);
    printer.BeginObject();
    printer.PrintKeyValue("archiveVersion", xcodeProject.archiveVersion);
    printer.PrintKeyValue("classes", [&] {
        printer.BeginObject();
        printer.EndObject();
    });
    printer.PrintKeyValue("objectVersion", xcodeProject.objectVersion);
    printer.PrintKeyValue("objects", [&] {
        printer.BeginObject();
        PrintObjects(printer, xcodeProject);
        printer.EndObject();
    });
    printer.PrintKeyValue("rootObject",
        MakeUUIDWithComment(xcodeProject.rootObject->GetUuid(), "Project object"));
    printer.EndObject();

    stream << "\n";
    return stream.str();
}

} // unnamed namespace

GeneratorError Xcode::GenerateXcodeProject(const CompileOptions& options)
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

    auto xcodeProject = CreateXcodeProject(options);
    {
        const auto pbxprojPath = FileSystem::join(
            xcodeprojPath, "project.pbxproj");
        std::ofstream stream(pbxprojPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        stream << GeneratePbxproj(*xcodeProject);
    }
    {
        const auto xcworkspacedataPath = FileSystem::join(
            xcworkspacePath, "contents.xcworkspacedata");
        std::ofstream stream(xcworkspacedataPath, std::ios::out | std::ios::trunc);
        if (!stream) {
            return GeneratorError("Error: Cannot open.");
        }
        auto xcodeprojName = std::get<1>(FileSystem::split(xcodeprojPath));
        stream << GenerateXCWorkSpaceData(xcodeprojName);
    }
    return {};
}

} // namespace somera
