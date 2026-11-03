#include <slv/hook.h>

#include <print>

#if defined(_MSC_VER)
  #define SLV_NOINLINE __declspec(noinline)
#else
  #define SLV_NOINLINE __attribute__((noinline))
#endif

struct apple {
  SLV_NOINLINE int banana(void) const {
    std::println("apple::banana()");
    return 1;
  }

  SLV_NOINLINE void cantaloupe(int a) const {
    std::println("apple::cantaloupe({})", a);
  }
};

namespace {

slv::hook<&apple::banana> hk_apple_banana{+[](apple const* obj) -> int {
  std::println("hello from hk_apple_banana");
  return hk_apple_banana.original(obj);
}};

slv::hook<&apple::cantaloupe> hk_cantaloupe{+[](apple const* obj, int a) -> void {
  std::println("hello from hk_cantaloupe");
  hk_cantaloupe.original(obj, a);
}};

} // namespace

int main(void) {
  apple a;
  a.banana();
  a.cantaloupe(10);
  return 0;
}
