// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <string>
#include <system_error>
#include <tuple>
#include <vector>

namespace somera {
namespace FileSystem {

std::string join(const std::string& path1, const std::string& path2);

std::string getBaseName(const std::string& path);

std::string getDirectoryName(const std::string& path);

std::size_t getFileSize(const std::string& path);

std::size_t getFileSize(const std::string& path, std::error_code& errorCode);

std::tuple<std::string, std::string> split(const std::string& path);

std::tuple<std::string, std::string> splitExtension(const std::string& path);

//std::string isAbsolute(const std::string& path);

std::string normalize(const std::string& path);

std::string relative(const std::string& path, const std::string& start);

std::string getCurrentDirectory();

bool createDirectory(const std::string& path);

bool createDirectories(const std::string& path);

bool exists(const std::string& path);

bool isDirectory(const std::string& path);

// NOTE: Return a list the names of files or folders in the directory.
std::tuple<std::vector<std::string>, std::error_code>
readDirectory(const std::string& directory) noexcept;

std::error_code rename(const std::string& oldname, const std::string& newname) noexcept;

} // namespace FileSystem
} // namespace somera
