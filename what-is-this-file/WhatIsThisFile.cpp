// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "WhatIsThisFile.h"
#include "somera/FileSystem.h"
#include <algorithm>
#include <fstream>

namespace somera {
namespace {

std::tuple<FileDetection, Error> DetectIfThisIsDirectory(const std::string& path)
{
    auto extention = std::get<1>(FileSystem::splitExtension(path));
    if (extention == ".xcodeproj") {
        assert(FileSystem::isDirectory(path));
        auto readDirectoryResult = FileSystem::readDirectory(path);
        auto readDirectoryErrorCode = std::get<1>(readDirectoryResult);
        if (readDirectoryErrorCode) {
            auto error = MakeError("Cannot read directory.", __FILE__, __LINE__);
            return std::make_tuple(FileDetection{}, std::move(error));
        }

        FileDetection detection;
        detection.type = "";
        detection.accuracy = 0.5;

        auto files = std::get<0>(readDirectoryResult);
        auto findFile = [&files](const std::string& filePath) -> bool {
            return std::end(files) != std::find(std::begin(files), std::end(files), filePath);
        };
        if (findFile("project.pbxproj")) {
            detection.accuracy += 0.4;
        }
        if (findFile("project.xcworkspace")) {
            detection.accuracy += 0.4;
        }
        if (findFile("xcuserdata")) {
            detection.accuracy += 0.2;
        }
        detection.accuracy = std::max(detection.accuracy, 1.0);
        return std::make_tuple(std::move(detection), Error{});
    }
    auto error = MakeError("Cannot detect the file type.", __FILE__, __LINE__);
    return std::make_tuple(FileDetection{}, std::move(error));
}

} // unnamed namespace

FileDetector::FileDetector(FileFormatDescription && descriptionIn)
    : description(std::move(descriptionIn))
{}

bool FileDetector::IsSignatureEnabled() const noexcept
{
    return !description.signature.empty();
}

bool FileDetector::IsExtensionEnabled() const noexcept
{
    return !description.extensions.empty();
}

bool FileDetector::MatchExtension(const std::string& extension) const noexcept
{
    const auto& e = description.extensions;
    return std::find(std::begin(e), std::end(e), extension) != std::end(e);
}

bool FileDetector::MatchSignature(const std::vector<uint8_t>& signature) const noexcept
{
    const auto& s = description.signature;
    if (signature.size() < s.size()) {
        return false;
    }
    assert(signature.size() >= s.size());
    return std::equal(std::begin(s), std::end(s), std::begin(signature));
}

std::string FileDetector::GetName() const noexcept
{
    return description.name;
}

WhatIsThisFile::WhatIsThisFile()
{
    {
        FileFormatDescription desc;
        desc.name = "PNG (Portable Network Graphics)";
        desc.extensions = {".png"};
        desc.signature = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "JPEG";
        desc.extensions = {".jpg", ".jpeg", ".jpe"};
        desc.signature = {0xFF, 0xD8, 0xFF};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "MagicaVoxel";
        desc.extensions = {".vox"};
        desc.signature = {'V', 'O', 'X', ' '};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "DMG (OS X Disk Image)";
        desc.extensions = {".dmg"};
        desc.signature = {0x45, 0x52, 0x02, 0x00};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "ZIP";
        desc.extensions = {".zip"};
        desc.signature = {0x50, 0x4B, 0x03, 0x04};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "PSD (Photoshop File Format)";
        desc.extensions = {".psd"};
        desc.signature = {0x38, 0x42, 0x50, 0x53, 0x00, 0x01, 0x00, 0x00};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "PDF (Portable Document Format)";
        desc.extensions = {".pdf"};
        desc.signature = {0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x35};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "Microsoft PowerPoint .ppt Binary File Format";
        desc.extensions = {".ppt"};
        desc.signature = {
            0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x3E, 0x00, 0x03, 0x00, 0xFE, 0xFF, 0x09, 0x00,
        };
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "Microsoft Excel .xls Binary File Format";
        desc.extensions = {".xls"};
        desc.signature = {
            0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x3E, 0x00, 0x03, 0x00, 0xFE, 0xFF, 0x09, 0x00,
        };
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
    {
        FileFormatDescription desc;
        desc.name = "Microsoft Word .doc Binary File Format";
        desc.extensions = {".doc"};
        desc.signature = {
            0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x3E, 0x00, 0x03, 0x00, 0xFE, 0xFF, 0x09, 0x00,
        };
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));

    }
    {
        FileFormatDescription desc;
        desc.name = "Microsoft PowerPoint .pptx Binary File Format";
        desc.extensions = {".pptx"};
        desc.signature = {0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x06, 0x00};
        detectors.push_back(std::make_shared<FileDetector>(std::move(desc)));
    }
}

std::tuple<FileDetection, Error> WhatIsThisFile::Detect(const std::string& path)
{
    if (FileSystem::isDirectory(path)) {
        return DetectIfThisIsDirectory(path);
    }

    std::size_t fileSize = 0;
    {
        std::error_code errorCode;
        fileSize = somera::FileSystem::getFileSize(path, errorCode);
        if (errorCode) {
            return std::make_tuple(FileDetection{}, MakeError(errorCode));
        }
    }

    if (fileSize <= 0) {
        auto error = MakeError("The file is empty.", __FILE__, __LINE__);
        return std::make_tuple(FileDetection{}, std::move(error));
    }

    std::vector<uint8_t> fileBuffer;
    {
        std::ifstream input(path, std::ios::binary);
        if (!input) {
            auto error = MakeError("Cannot read the file.", __FILE__, __LINE__);
            return std::make_tuple(FileDetection{}, std::move(error));
        }

        const auto readableSize = std::min<std::size_t>(fileSize, 32);
        fileBuffer.resize(readableSize, 0);
        input.read(reinterpret_cast<char*>(fileBuffer.data()), readableSize);
    }

    if (!fileBuffer.empty()) {
        auto iter = std::find_if(std::begin(detectors), std::end(detectors), [&fileBuffer](const auto& detector) {
            return detector->MatchSignature(fileBuffer);
        });

        if (iter != std::end(detectors)) {
            auto& detector = *iter;
            FileDetection detection;
            detection.type = detector->GetName();
            detection.accuracy = 1.0;
            return std::make_tuple(std::move(detection), Error{});
        }
    }

    auto extension = std::get<1>(FileSystem::splitExtension(path));
    if (!extension.empty()) {
        auto iter = std::find_if(std::begin(detectors), std::end(detectors), [&extension](const auto& detector) {
            return detector->MatchExtension(extension);
        });

        if (iter != std::end(detectors)) {
            auto& detector = *iter;
            FileDetection detection;
            detection.type = detector->GetName();
            detection.accuracy = 1.0;
            return std::make_tuple(std::move(detection), Error{});
        }
    }

    // error: Cannot detect the file type.
    return std::make_tuple(FileDetection{}, Error{});
}

} // namespace somera
