
#include <utility>
#include <proxy/proxy_macros.h>

/// `proxy` is exported from `proxy.ixx`
/// Error: Module 'proxy' not found
/// `E[07:05:17.608] Failed to build module proxy; due to Failed to build compiler invocation`
import proxy;

/// `proxy_` is exported from `proxy.cpp`
// import proxy_;

extern "C++" {
namespace mem {
PRO_DEF_MEM_DISPATCH(foo, foo);
}
}

struct Foo 
    : pro::facade_builder
    ::add_convention<mem::foo, int() const>
    ::build {};

auto f1(pro::proxy<Foo> p) {
    p->; // <- trigger auto completion here, `foo` should show up.
}

int main() {

}
