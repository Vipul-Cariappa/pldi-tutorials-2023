/* See the LICENSE file in the project root for license terms. */

#include "p3-ex4-lib.h"

const char *Code = " \n #include <typeinfo> \n \
    void* operator new(__SIZE_TYPE__, void* __p) noexcept; \
    extern \"C\" int printf(const char*,...); \
    class A {}; \
    class B { \
    public: \
      template<typename T> \
      static void callme(T) { \
        printf(\" Instantiated with [%s] \\n\", typeid(T).name()); \
      }\
    };";

int main(int argc, char **argv) {
  Clang_Parse(Code);
  Decl_t TemplatedClass = Clang_LookupName("B", /*Context=*/0);

  // Instantiate B::callme with the given types
  Decl_t Instantiation =
      Clang_InstantiateTemplate(TemplatedClass, "callme", "A");

  // Get the symbol to call
  typedef void (*fn_def)(void *);
  fn_def callme_fn_ptr = (fn_def)Clang_GetFunctionAddress(Instantiation);

  // Create objects of type A
  Decl_t T = Clang_LookupName("A", /*Context=*/0);
  void *NewA = Clang_CreateObject(T);

  callme_fn_ptr(NewA);

  return 0;
}

