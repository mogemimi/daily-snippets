#pragma once

#include "Basic/Forward.h"
#include "CodeGen/Instruction.h"
#include "Sema/Value.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// NOTE: the following class reperesents a VM
class Runtime final {
private:
    std::unordered_map<std::string, std::shared_ptr<Value>> variables;
    std::vector<std::shared_ptr<Value>> valueStack;

public:
    bool run(const BytecodeProgram& program);

    std::string getResultString() const;

    static void dump(const BytecodeProgram& program);
};
