#include "Basic/Diagnostic.h"

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

void DiagnosticHandler::error(const yy::location& loc, const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName;
    }
    std::cerr << loc << ": ";
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

void DiagnosticHandler::warn(const yy::location& loc, const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName;
    }
    std::cerr << loc << ": ";
    std::cerr << "warning: " << msg << std::endl;
}

void DiagnosticHandler::warn(const std::string& msg)
{
    if (!programName.empty()) {
        std::cerr << programName << ": ";
    }
    std::cerr << "warning: " << msg << std::endl;
}
