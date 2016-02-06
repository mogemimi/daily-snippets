// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "FileSystem.h"
#include <cassert>
#include <vector>

#ifdef _MSC_VER
#define SOMERA_IS_WINDOWS
#endif

#ifdef SOMERA_IS_WINDOWS

#else
#include <array>
#include <algorithm>
#include <cstdio>
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
    return std::move(result);
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
    return std::move(result);
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
    return std::move(result);
}

//bool FileSystem::isAbsolute(const std::string& path)
//{
//#if defined(SOMERA_IS_WINDOWS)
//    // See https://msdn.microsoft.com/en-us/library/bb773660.aspx
//    //PathIsRelative()
//#else
//
//#endif
//}

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
    return std::move(fullPath);
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
    return std::move(result);
}

std::string FileSystem::getCurrentDirectory()
{
#ifdef SOMERA_IS_WINDOWS
    // See https://msdn.microsoft.com/en-us/library/windows/desktop/aa364934.aspx
    //GetCurrentDirectory
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
#ifdef SOMERA_IS_WINDOWS
#else
    assert(!path.empty());
    struct stat st;
    if (::stat(path.c_str(), &st) != -1) {
        return false;
    }
    return ::mkdir(path.c_str(), S_IRWXU) == 0;
#endif
}

bool FileSystem::createDirectories(const std::string& path)
{
#ifdef SOMERA_IS_WINDOWS

#else
    assert(!path.empty());
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
#ifdef SOMERA_IS_WINDOWS

#else
    assert(!path.empty());
    return ::access(path.c_str(), F_OK) != -1;
#endif
}

bool FileSystem::isDirectory(const std::string& path)
{
#ifdef SOMERA_IS_WINDOWS

#else
    assert(!path.empty());
    struct stat st;
    if (::stat(path.c_str(), &st) != 0) {
        return false;
    }
    return S_ISDIR(st.st_mode);
#endif
}

} // namespace somera
