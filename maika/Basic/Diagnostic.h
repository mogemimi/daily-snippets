#pragma once

#include "Basic/Forward.h"
#include "location.hh"
#include <memory>
#include <string>

class DiagnosticHandler {
private:
    std::string programName;
    int errorCount;

public:
    DiagnosticHandler();

    void setProgramName(const std::string& name);

    bool hasError() const;

    void error(const yy::location& loc, const std::string& msg);

    void error(const std::string& msg);

    void warn(const yy::location& loc, const std::string& msg);

    void warn(const std::string& msg);
};
