/* See the LICENSE file in the project root for license terms. */

/// This file demonstrates how we could embed Clang and use it as a library in a
/// codebase.

#include "clang/AST/Comment.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/Tooling/Tooling.h"

const char* Code = R"(
/// This is the documentation for the ComplexNumber.
// This comment won't appear in the documentation!
template<typename T>
struct ComplexNumber { T real; T imag; };

ComplexNumber<int> c; // variable
)";

int main() {
  using namespace clang;
  auto ASTU = tooling::buildASTFromCodeWithArgs(Code, /*Args=*/{"-std=c++20"});
  auto &C = ASTU->getASTContext();
  auto* TU = C.getTranslationUnitDecl();
  TU->dump();
  // Can we feed more code and use clang as a service?
}
