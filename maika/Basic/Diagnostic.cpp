#include "Basic/Diagnostic.h"
#include "Basic/Location.h"
#include "Basic/StringHelper.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

namespace {

std::string getErrorString(
    const std::string& errorLevel,
    const std::string& programName,
    const Location& loc,
    const std::string& msg)
{
    std::stringstream ss;
    if (!programName.empty()) {
        ss << programName;
    }
    ss << loc.toString() << ": ";
    ss << errorLevel + ": " << msg;
    return ss.str();
}

std::string getErrorString(
    const std::string& errorLevel, const std::string& programName, const std::string& msg)
{
    std::stringstream ss;
    if (!programName.empty()) {
        ss << programName;
    }
    ss << errorLevel + ": " << msg;
    return ss.str();
}

} // end of anonymous namespace

void StdoutDiagnosticStream::error(const std::string& err)
{
    std::cerr << err << std::endl;
}

void StdoutDiagnosticStream::warn(const std::string& warning)
{
    std::cout << warning << std::endl;
}

void UnitTestDiagnosticStream::error(const std::string& err)
{
    errors.push_back(err);
}

void UnitTestDiagnosticStream::warn(const std::string& warning)
{
    warnings.push_back(warning);
}

bool UnitTestDiagnosticStream::hasError(const std::string& err) const
{
    return std::find_if(std::begin(errors), std::end(errors), [&](const std::string& e) -> bool {
               return StringHelper::endWith(e, err);
           }) != std::end(errors);
}

bool UnitTestDiagnosticStream::hasWarning(const std::string& warning) const
{
    return std::find(std::begin(warnings), std::end(warnings), warning) != std::end(warnings);
}

DiagnosticHandler::DiagnosticHandler()
    : errorCount(0)
{
    stream = std::make_shared<StdoutDiagnosticStream>();
}

void DiagnosticHandler::setStream(const std::shared_ptr<DiagnosticStream>& streamIn)
{
    stream = streamIn;
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
    assert(stream);
    stream->error(getErrorString("error", programName, loc, msg));
    ++errorCount;
}

void DiagnosticHandler::error(const std::string& msg)
{
    assert(stream);
    stream->error(getErrorString("error", programName, msg));
    ++errorCount;
}

void DiagnosticHandler::warn(const Location& loc, const std::string& msg)
{
    assert(stream);
    stream->warn(getErrorString("warning", programName, loc, msg));
}

void DiagnosticHandler::warn(const std::string& msg)
{
    assert(stream);
    stream->warn(getErrorString("warning", programName, msg));
}
