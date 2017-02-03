// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <map>
#include <string>
#include <vector>

namespace somera {

struct GeneratorError {
    GeneratorError()
        : hasError(false)
    {
    }

    explicit GeneratorError(const std::string& desc)
        : description(desc)
        , hasError(true)
    {}

    std::string description;
    bool hasError = false;
};

struct CompileOptions {
    std::string generatorOutputDirectory;
    std::string productName;
    std::string targetName;
    std::vector<std::string> sources;
    std::vector<std::string> libraries;
    std::vector<std::string> includeSearchPaths;
    std::vector<std::string> librarySearchPaths;
    std::vector<std::string> preprocessorDefinitions;
    std::map<std::string, std::string> buildSettings;
    std::string author;
    bool enableCppExceptions = true;
    bool enableCppRtti = true;
};

} // namespace somera
