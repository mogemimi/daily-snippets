#pragma once

#include "Forward.h"
#include "Type.h"
#include <cassert>
#include <string>
#include <vector>
#include <memory>
#include <utility>

class ASTDumper final {
    std::string indent;
    bool allowMultiLine;
public:
    ASTDumper() = default;
    explicit ASTDumper(bool multiLine) : allowMultiLine(multiLine) {}

    std::string GetIndent() const
    {
        if (!allowMultiLine) {
            return "";
        }
        return indent;
    }

    void SetIndent(const std::string& i)
    {
        indent = i;
    }

    bool isMultiLine()
    {
        return allowMultiLine;
    }
};
