// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "Error.h"
#include <string>
#include <vector>
#include <tuple>
#include <memory>

namespace somera {

struct FileDetection {
    std::string type;
    double accuracy = 0;
};

struct FileFormatDescription final {
    std::vector<std::string> extensions;
    std::vector<uint8_t> signature;
    std::string name;
};

class FileDetector final {
public:
    explicit FileDetector(FileFormatDescription && descriptionIn);

    bool IsSignatureEnabled() const noexcept;

    bool IsExtensionEnabled() const noexcept;

    bool MatchExtension(const std::string& extension) const noexcept;

    bool MatchSignature(const std::vector<uint8_t>& signature) const noexcept;

    std::string GetName() const noexcept;

private:
    FileFormatDescription description;
};

class WhatIsThisFile final {
public:
    WhatIsThisFile();

    std::tuple<FileDetection, Error> Detect(const std::string& path);

private:
    std::vector<std::shared_ptr<FileDetector>> detectors;
};

} // namespace somera
