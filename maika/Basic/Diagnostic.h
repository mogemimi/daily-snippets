#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>
#include <vector>

class DiagnosticStream {
public:
    virtual ~DiagnosticStream() = default;
    virtual void error(const std::string& err) = 0;
    virtual void warn(const std::string& warning) = 0;
};

class StdoutDiagnosticStream final : public DiagnosticStream {
public:
    void error(const std::string& err) override;
    void warn(const std::string& warning) override;
};

class UnitTestDiagnosticStream final : public DiagnosticStream {
private:
public:
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

public:
    void error(const std::string& err) override;
    void warn(const std::string& warning) override;

    bool hasError(const std::string& err) const;
    bool hasWarning(const std::string& warning) const;
};

class DiagnosticHandler final {
private:
    std::shared_ptr<DiagnosticStream> stream;
    std::string programName;
    int errorCount;

public:
    DiagnosticHandler();

    void setStream(const std::shared_ptr<DiagnosticStream>& stream);

    void setProgramName(const std::string& name);

    bool hasError() const;

    void error(const Location& loc, const std::string& msg);

    void error(const std::string& msg);

    void warn(const Location& loc, const std::string& msg);

    void warn(const std::string& msg);
};
