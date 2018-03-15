#pragma once

#include <memory>
#include <string>

class Position final {
public:
    // TODO: Replace std::string with integer type as a file identifier.
    // file name
    std::string filename;

    // line number
    int line;

    // column number
    int column;

    // file offset
    // int offset;

    bool isValid() const noexcept { return line > 0; }

    bool operator==(const Position& rhs) const
    {
        return (line == rhs.line) && (column == rhs.column);
    }

    bool operator!=(const Position& rhs) const
    {
        return (line != rhs.line) || (column != rhs.column);
    }

    bool operator<(const Position& rhs) const
    {
#if 0
		return offset < rhs.offset;
#else
        if (line == rhs.line) {
            return column < rhs.column;
        }
        return line < rhs.line;
#endif
    }

    std::string toString() const;
};

class Location final {
private:
    Position begin;
    Position end;

public:
    Location() = default;
    Location(const Position& loc)
        : begin(loc)
        , end(loc)
    {
    }
    Location(const Position& b, const Position& e)
        : begin(b)
        , end(e)
    {
    }

    Position getBegin() const { return begin; }
    Position getEnd() const { return end; }

    void setBegin(const Position& b) { begin = b; }
    void setEnd(const Position& e) { begin = e; }

    bool isValid() const noexcept { return begin.isValid() && end.isValid(); }

    bool operator==(const Location& rhs) { return (begin == rhs.begin) && (end == rhs.end); }

    bool operator!=(const Location& rhs) { return (begin != rhs.begin) || (end != rhs.end); }

    std::string toString() const;
};
