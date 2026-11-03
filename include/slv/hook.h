#ifndef SLV_HOOK_H_
#define SLV_HOOK_H_

#include "type.h"

#include <polyhook2/Detour/x64Detour.hpp>

#include <format>
#include <stdexcept>
#include <type_traits>

namespace slv::internal {

template <typename T>
concept member_fn_ptr = std::is_member_function_pointer_v<T>;

// forward declare
struct hook_factory;

} // namespace slv::internal

namespace slv {

template <auto O>
class hook final {
  friend class internal::hook_factory;

 private:
  using type      = decltype(O);
  using traits    = fn_traits<type>;
  using ret       = typename traits::ret;
  using this_type = typename traits::this_type;
  using cb_sig    = typename traits::cb_sig;

 public:
  explicit hook(cb_sig cb)
    : tramp_(nullptr)
    , det_(resolve_fn_addr(O), reinterpret_cast<std::uint64_t>(cb),
           reinterpret_cast<std::uint64_t*>(&tramp_)) {
    if (!attach()) {
      throw std::runtime_error(
        std::format("failed to install hook at {:#x}", reinterpret_cast<std::uint64_t>(cb)));
    }
  }

  hook(hook const&)            = delete;
  hook& operator=(hook const&) = delete;

  ~hook(void) {
    (void)detach();
  }

  template <typename... Args>
  inline ret original(this_type obj, Args... args) const {
    return tramp_(obj, args...);
  }

  inline bool attach() {
    return det_.hook();
  }

  inline bool detach() {
    return det_.unHook();
  }

 private:
  [[nodiscard]] std::uint64_t resolve_fn_addr(type pmf) const {
    std::uint64_t addr{};
    (void)std::memcpy(&addr, &pmf, sizeof(addr));
    return addr;
  }

  // todo: change type depending on architecture
  PLH::x64Detour det_;
  cb_sig tramp_;
};

} // namespace slv

#endif // SLV_HOOK_H_