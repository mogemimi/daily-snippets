#include "TypeResolver.h"
#include "AST.h"
#include "Decl.h"
#include "Entity.h"
#include "Expr.h"
#include "Stmt.h"
#include <cassert>
#include <sstream>
#include <utility>

namespace {

using TypeVariableIndex = uint64_t;
//TypeVariableIndex typeVariableIndex;
std::unordered_map<TypeVariableIndex, std::string> table2;
std::unordered_map<std::string, std::vector<std::shared_ptr<const Decl>>> table;

void addDecl(const std::string& name, const std::shared_ptr<const Decl>& decl)
{
    auto iter = table.find(name);
    if (iter == std::end(table)) {
        table.emplace(name, std::vector<std::shared_ptr<const Decl>>{});
        iter = table.find(name);
    }
    iter->second.push_back(decl);
}

//TypeVariableIndex makeTypeVariableIndex()
//{
//    static TypeVariableIndex typeIndex = 10000;
//    ++typeIndex;
//    return typeIndex;
//}

} // end of anonymous namespace

void TypeResolver::visit(const std::shared_ptr<FunctionDecl>& decl)
{
}

void TypeResolver::visit(const std::shared_ptr<VariableDecl>& decl)
{
    assert(decl->namedDecl);

    //const auto typeIndex = makeTypeVariableIndex();
    addDecl(decl->namedDecl->getName(), decl->namedDecl);
    //printf("[%d] %s\n", static_cast<int>(typeIndex), decl->namedDecl->name.c_str());

    //table.emplace(decl->namedDecl->name, decl->named);
}

void TypeResolver::visit(const std::shared_ptr<NamedDecl>& namedDecl)
{
    auto var = namedDecl->getEntity();
    if (!var) {
        return;
    }
    std::stringstream ss;
    ss << namedDecl->getName()
        << "("
        << namedDecl->getLocation()
        << "): defined at "
        << var->getDecl()->getLocation();
    printf("%s\n", ss.str().c_str());

    //const auto typeIndex = makeTypeVariableIndex();
    addDecl(namedDecl->getName(), namedDecl);
    //printf("[%d] %s\n", static_cast<int>(typeIndex), namedDecl->name.c_str());
}
