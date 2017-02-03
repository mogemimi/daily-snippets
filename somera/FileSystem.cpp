// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "FileSystem.h"
#include <algorithm>
#include <cassert>
#include <vector>

#ifdef _MSC_VER
#define SOMERA_IS_WINDOWS
#endif

#ifdef SOMERA_IS_WINDOWS
#include <experimental/filesystem>
#include <Windows.h>
#else
#include "somera/Defer.h"
#include <array>
#include <cstdio>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace somera {
namespace {

std::string::size_type findFirstOfSlash(
    const std::string& path,
    std::string::size_type first = 0)
{
    assert(first != std::string::npos);
    auto index = path.find_first_of('/', first);
//#if defined(SOMERA_IS_WINDOWS)
    const auto windowsIndex = path.find_first_of('\\', first);
    if (index != std::string::npos) {
        if (windowsIndex != std::string::npos) {
            index = std::min(index, windowsIndex);
        }
    }
    else if (windowsIndex != std::string::npos) {
        assert(index == std::string::npos);
        index = windowsIndex;
    }
//#endif
    if (index == 0) {
        return index + 1;
    }
    return index;
}

class PathIterator {
    const std::string* source;
    std::string::size_type startPos;
    std::string::size_type endPos;

public:
    PathIterator()
        : source(nullptr)
        , startPos(std::string::npos)
        , endPos(std::string::npos)
    {}

    PathIterator(const std::string& path_, std::string::size_type start_, std::string::size_type end_)
        : source(&path_)
        , startPos(start_)
        , endPos(end_)
    {}

    std::string operator*() const
    {
        assert(source != nullptr);
        if (source->empty()) {
            return "";
        }
        assert(startPos != std::string::npos);
        assert(endPos != std::string::npos);
        if (endPos == std::string::npos) {
            return source->substr(startPos);
        }
        return source->substr(startPos, endPos - startPos);
    }

    bool operator==(const PathIterator& iter) const
    {
        return (source == iter.source)
            && (startPos == iter.startPos)
            && (endPos == iter.endPos);
    }

    bool operator!=(const PathIterator& iter) const
    {
        return (source != iter.source)
            || (startPos != iter.startPos)
            || (endPos != iter.endPos);
    }

    static PathIterator begin(const std::string& path)
    {
        if (path.empty()) {
            return PathIterator(path, std::string::npos, std::string::npos);
        }
        auto index = findFirstOfSlash(path);
        if (std::string::npos == index) {
            return PathIterator(path, 0, path.size());
        }
        return PathIterator(path, 0, index);
    }

    static PathIterator end(const std::string& path)
    {
        return PathIterator(path, std::string::npos, std::string::npos);
    }

    static PathIterator next(const PathIterator& iter)
    {
        assert(iter.source != nullptr);
        assert(iter.startPos != std::string::npos);
        assert(iter.endPos != std::string::npos);
        auto endPos = iter.endPos;
        if (endPos == iter.source->size()) {
            return PathIterator(*iter.source, std::string::npos, std::string::npos);
        }

        if (iter.source->at(endPos) == '/'
//#if defined(SOMERA_IS_WINDOWS)
            || iter.source->at(endPos) == '\\'
//#endif
        ) {
            if (endPos < iter.source->size()) {
                endPos++;
            }
        }
        auto index = findFirstOfSlash(*iter.source, endPos);
        if (std::string::npos == index) {
            if (endPos < iter.source->size()) {
                return PathIterator(*iter.source, endPos, iter.source->size());
            }
            return PathIterator(*iter.source, index, index);
        }
        return PathIterator(*iter.source, endPos, index);
    }
};

#if 0
TEST(PathIterator, Case_01)
{
    std::string path = "";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
    EXPECT_EQ("", *iter);
}

TEST(PathIterator, Case_02)
{
    std::string path = "/";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("/", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_03)
{
    std::string path = ".";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ(".", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_04)
{
    std::string path = "../hoge";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("..", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("hoge", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_05)
{
    std::string path = "../hoge/";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("..", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("hoge", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_06)
{
    std::string path = "../foo\\hoge";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("..", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("foo", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("hoge", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_07)
{
    std::string path = "../foo\\hoge\\";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("..", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("foo", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ("hoge", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}

TEST(PathIterator, Case_08)
{
    std::string path = ".\\";
    auto iter = PathIterator::begin(path);
    EXPECT_EQ(iter, PathIterator::begin(path));
    EXPECT_NE(iter, PathIterator::end(path));
    EXPECT_EQ(".", *iter);
    iter = PathIterator::next(iter);
    EXPECT_NE(iter, PathIterator::begin(path));
    EXPECT_EQ(iter, PathIterator::end(path));
}
#endif

} // unnamed namespace

std::string FileSystem::join(const std::string& path1, const std::string& path2)
{
    std::string result = path1;
#if defined(SOMERA_IS_WINDOWS)
    if (!result.empty() && '\\' == result.back()) {
        result.erase(std::prev(std::end(result)));
        result += '/';
    }
#endif
    if (!result.empty() && '/' != result.back()) {
        if (!path2.empty() && '/' != path2.front()) {
            result += '/';
        }
    }
    result += path2;
    return result;
}

std::string FileSystem::getBaseName(const std::string& path)
{
    const auto lastIndex = path.find_last_of('/');
    if (std::string::npos != lastIndex) {
        return path.substr(lastIndex + 1);
    }
    return path;
}

std::string FileSystem::getDirectoryName(const std::string& path)
{
    if (!path.empty() && path.back() == '/') {
        return path;
    }
    const auto lastIndex = path.find_last_of('/');
    if (std::string::npos != lastIndex) {
        return path.substr(0, lastIndex);
    }
    return {};
}

std::size_t FileSystem::getFileSize(const std::string& path, std::error_code& errorCode)
{
#if defined(_MSC_VER)
    FILE* fp = nullptr;
    auto fopenResult = fopen_s(&fp, path.c_str(), "rb");
    if (fp != 0) {
        // Error: Failed to open the file
        errorCode.assign(fopenResult, std::generic_category());
        return 0;
    }
#else
    auto fp = fopen(path.c_str(), "rb");
    if (fp == nullptr) {
        // Error: Failed to open the file
        errorCode.assign(errno, std::generic_category());
        return 0;
    }
#endif

#if defined(_MSC_VER)
    auto descriptor = _fileno(fp);
#else
    auto descriptor = fileno(fp);
#endif
    struct stat statBuf;
    if (fstat(descriptor, &statBuf) == -1) {
        fclose(fp);
        errorCode.assign(errno, std::generic_category());
        return 0;
    }
    fclose(fp);
    return statBuf.st_size;
}

std::tuple<std::string, std::string>
FileSystem::split(const std::string& path)
{
    std::tuple<std::string, std::string> result;
    auto lastIndex = path.find_last_of('/');
    if (std::string::npos != lastIndex) {
        std::get<0>(result) = path.substr(0, lastIndex);
        std::get<1>(result) = path.substr(lastIndex + 1);
    } else {
        std::get<1>(result) = path;
    }
    return result;
}

std::tuple<std::string, std::string>
FileSystem::splitExtension(const std::string& path)
{
    std::tuple<std::string, std::string> result;
    auto lastIndex = path.find_last_of('.');
    if (std::string::npos != lastIndex) {
        std::get<0>(result) = path.substr(0, lastIndex);
        std::get<1>(result) = path.substr(lastIndex + 1);
    } else {
        std::get<0>(result) = path;
    }
    return result;
}

bool FileSystem::isAbsolute(const std::string& path)
{
    // See https://msdn.microsoft.com/en-us/library/bb773660.aspx
    if (path.empty()) {
        return false;
    }

    // TODO: Windows's drive (ex. 'C:' drive) and '\\[server name]'
    return path.front() == '/';
}

std::string FileSystem::normalize(const std::string& path)
{
    auto fullPath = path;
    if (fullPath.front() != '/') { // TODO: Windows's drive (ex. 'C:' drive) and '\\[server name]'
        // NOTE: 'path' is not full path.
        fullPath = FileSystem::join(getCurrentDirectory(), fullPath);
    }

    std::vector<std::string> paths;
    auto iter = PathIterator::begin(fullPath);
    while (iter != PathIterator::end(fullPath)) {
        auto current = *iter;
        iter = PathIterator::next(iter);

        if (current == ".") {
            continue;
        }
        if (current == "..") {
            assert(!paths.empty());
            if (paths.empty()) {
                return fullPath;
            }
            paths.pop_back();
            continue;
        }
        paths.push_back(current);
    }

    fullPath.clear();
    for (auto & current : paths) {
        if (fullPath.empty() && current == "/") {
            fullPath = current;
            continue;
        }
        fullPath = FileSystem::join(fullPath, current);
    }
    return fullPath;
}

std::string
FileSystem::relative(const std::string& path, const std::string& start)
{
    const auto fullPath = normalize(path);
    const auto fullPathStart = normalize(start);

    auto iterL = PathIterator::begin(fullPath);
    auto iterR = PathIterator::begin(fullPathStart);
    while ((iterL != PathIterator::end(fullPath))
        && (iterR != PathIterator::end(fullPathStart))) {
        if (*iterL != *iterR) {
            break;
        }
        iterR = PathIterator::next(iterR);
        iterL = PathIterator::next(iterL);
    }

    std::string result;
    while (iterR != PathIterator::end(fullPathStart)) {
        result = FileSystem::join(result, "..");
        iterR = PathIterator::next(iterR);
    }
    while (iterL != PathIterator::end(fullPath)) {
        result = FileSystem::join(result, *iterL);
        iterL = PathIterator::next(iterL);
    }
    if (result.empty()) {
        result = '.';
    }
    return result;
}

std::string FileSystem::getCurrentDirectory()
{
#ifdef SOMERA_IS_WINDOWS
    // See https://msdn.microsoft.com/en-us/library/windows/desktop/aa364934.aspx
    auto bufferSize = GetCurrentDirectory(0, nullptr);
    if (bufferSize <= 0) {
        return {};
    }
    std::vector<char> cwd(bufferSize + 1, 0);
    bufferSize = GetCurrentDirectory(cwd.size(), cwd.data());
    assert(!cwd.empty());
    assert(cwd.size() == (bufferSize + 1));
    if (bufferSize <= 0) {
        return {};
    }
    return cwd.data();
#else
    char cwd[2048];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        return cwd;
    }
    return {};
#endif
}

bool FileSystem::createDirectory(const std::string& path)
{
    assert(!path.empty());
#ifdef SOMERA_IS_WINDOWS
    namespace fs = std::experimental::filesystem;
    return fs::create_directory(path);
#else
    struct stat st;
    if (::stat(path.c_str(), &st) != -1) {
        return false;
    }
    return ::mkdir(path.c_str(), S_IRWXU) == 0;
#endif
}

bool FileSystem::createDirectories(const std::string& path)
{
    assert(!path.empty());
#ifdef SOMERA_IS_WINDOWS
    namespace fs = std::experimental::filesystem;
    return fs::create_directories(path);
#else
    if (path.empty()) {
        return false;
    }

    auto tmp = path;
    if (tmp.back() == '/') {
        tmp.pop_back();
    }
    assert(!tmp.empty());
    if (tmp.empty()) {
        return false;
    }

    auto iter = std::next(std::begin(tmp), 1);
    for (; iter != std::end(tmp); iter++) {
        if (*iter == '/') {
            *iter = 0;
            ::mkdir(tmp.c_str(), S_IRWXU);
            *iter = '/';
        }
    }
    return ::mkdir(tmp.c_str(), S_IRWXU) == 0;
#endif
}

bool FileSystem::exists(const std::string& path)
{
    assert(!path.empty());
#ifdef SOMERA_IS_WINDOWS
    namespace fs = std::experimental::filesystem;
    return fs::exists(path);
#else
    return ::access(path.c_str(), F_OK) != -1;
#endif
}

bool FileSystem::isDirectory(const std::string& path)
{
    assert(!path.empty());
#ifdef SOMERA_IS_WINDOWS
    namespace fs = std::experimental::filesystem;
    return fs::is_directory(path);
#else
    struct stat st;
    if (::stat(path.c_str(), &st) != 0) {
        return false;
    }
    return S_ISDIR(st.st_mode);
#endif
}

std::tuple<std::vector<std::string>, std::error_code>
FileSystem::readDirectory(const std::string& directory) noexcept
{
    if (!FileSystem::isDirectory(directory)) {
        // error: This directory path is not directory.
        std::error_code err {0, std::generic_category()};
        return std::make_tuple(std::vector<std::string>{}, std::move(err));
    }

#ifdef SOMERA_IS_WINDOWS
    std::vector<std::string> files;
    namespace fs = std::experimental::filesystem;
    for (auto& p : fs::directory_iterator(directory)) {
        files.push_back(p.path().u8string());
    }
    return std::make_tuple(std::move(files), std::error_code{});
#else
    ::DIR* directoryPointer = ::opendir(directory.c_str());

    if (directoryPointer == nullptr) {
        // error: Failed to open directory
        std::error_code err {errno, std::generic_category()};
        return std::make_tuple(std::vector<std::string>{}, std::move(err));
    }

    somera::Defer defer([&] {
        ::closedir(directoryPointer);
    });

    std::vector<std::string> files;
    ::dirent* entry = nullptr;
    do {
        entry = ::readdir(directoryPointer);
        if (entry != nullptr) {
            files.emplace_back(entry->d_name);
        }
    } while (entry != nullptr);

    return std::make_tuple(std::move(files), std::error_code{});
#endif
}

std::error_code FileSystem::rename(const std::string& oldname, const std::string& newname) noexcept
{
    if (!FileSystem::exists(oldname)) {
        // error: Cannot find the file.
        std::error_code err {0, std::generic_category()};
        return err;
    }
    if (::rename(oldname.c_str(), newname.c_str()) != 0) {
        // Error renaming file
        std::error_code err {0, std::generic_category()};
        return err;
    }
    // Yay, rename succeeded!
    return {};
}

} // namespace somera
