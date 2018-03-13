#include "Basic/Diagnostic.h"
#include "Basic/Location.h"
#include <iostream>

DiagnosticHandler::DiagnosticHandler()
    : errorCount(0)
{
}

void DiagnosticHandler::setProgramName(const std::string& name)
{
    programName = name;
}

bool DiagnosticHandler::hasError() const
{
    return errorCount > 0;
}

void DiagnosticHandler::error(const Location& loc, const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName;
    }
    std::cerr << loc.toString() << ": ";
    std::cerr << "error: " << msg << std::endl;
    ++errorCount;
}

void DiagnosticHandler::error(const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName << ": ";
    }
    std::cerr << "error: " << msg << std::endl;
    ++errorCount;
}

void DiagnosticHandler::warn(const Location& loc, const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName;
    }
    std::cerr << loc.toString() << ": ";
    std::cerr << "warning: " << msg << std::endl;
}

void DiagnosticHandler::warn(const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName << ": ";
    }
    std::cerr << "warning: " << msg << std::endl;
}
