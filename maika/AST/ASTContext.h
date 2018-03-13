#pragma once

#include "Basic/Forward.h"
#include <memory>
#include <string>

class ASTContext final {
public:
    std::shared_ptr<TranslationUnitDecl> translationUnit;

    std::string dump() const;
};
