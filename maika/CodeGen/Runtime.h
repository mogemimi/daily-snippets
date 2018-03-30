#pragma once

#include "Basic/Forward.h"
#include "CodeGen/Instruction.h"
#include <memory>
#include <string>
#include <vector>

// NOTE: the following class reperesents a VM
class Runtime final {
private:
    std::vector<std::shared_ptr<Value>> valueStack;

public:
    bool run(const std::vector<std::shared_ptr<Instruction>>& instructions);

    std::string getResultString() const;

    static void dump(const std::vector<std::shared_ptr<Instruction>>& instructions);
};
