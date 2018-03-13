#include "Basic/Location.h"

std::string Position::toString() const
{
    std::string s = filename;
    if (line > 0) {
        if (!s.empty()) {
            s += ":";
        }
        s += std::to_string(line);
        if (column > 0) {
            s += ":";
            s += std::to_string(column);
        }
    }
    if (s.empty()) {
        s += "-";
    }
    return s;
}

std::string Location::toString() const
{
    return begin.toString();
}
