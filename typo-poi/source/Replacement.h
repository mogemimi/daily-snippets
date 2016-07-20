// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include <cstddef>
#include <cstdint>

namespace somera {

class SourceRange final {
public:
    SourceRange()
        : offset(0)
        , length(0)
    {
    }

    SourceRange(SourceRange && other)
    {
        offset = std::move(other.offset);
        length = std::move(other.length);
        other.offset = 0;
        other.length = 0;
    }

    SourceRange(std::size_t offsetIn, std::size_t lengthIn)
        : offset(offsetIn)
        , length(lengthIn)
    {
    }

    SourceRange& operator=(SourceRange && other)
    {
        offset = std::move(other.offset);
        length = std::move(other.length);
        other.offset = 0;
        other.length = 0;
        return *this;
    }

    std::size_t GetLength() const noexcept
    {
        return length;
    }

    std::size_t GetOffset() const noexcept
    {
        return offset;
    }

    bool Contains(const SourceRange& range) const noexcept
    {
        return offset <= range.offset
            && (range.offset + range.length <= offset + length);
    }

    bool operator==(const SourceRange& range) const noexcept
    {
        return offset == range.offset && length == range.length;
    }

private:
    std::size_t offset;
    std::size_t length;
};

} // namespace somera
