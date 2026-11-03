#ifndef SLV_TRAITS_H_
#define SLV_TRAITS_H_

namespace slv {

template <typename>
struct fn_traits;

#define SLV_FN_TRAITS(__CV__, __REF__, __NOEXCEPT__)                                               \
  template <typename Ret, typename Class, typename... Args>                                        \
  struct fn_traits<Ret (Class::*)(Args...) __CV__ __REF__ __NOEXCEPT__> final {                    \
    fn_traits()     = delete;                                                                      \
    using ret       = Ret;                                                                         \
    using this_type = Class __CV__*;                                                               \
    using cb_sig    = Ret (*)(this_type, Args...) __NOEXCEPT__;                                    \
  }

SLV_FN_TRAITS(, , );
SLV_FN_TRAITS(const, , );
SLV_FN_TRAITS(const volatile, , );

SLV_FN_TRAITS(, &, );
SLV_FN_TRAITS(const, &, );
SLV_FN_TRAITS(const volatile, &, );

SLV_FN_TRAITS(, &&, );
SLV_FN_TRAITS(const, &&, );
SLV_FN_TRAITS(const volatile, &&, );

SLV_FN_TRAITS(, , noexcept);
SLV_FN_TRAITS(const, , noexcept);
SLV_FN_TRAITS(const volatile, , noexcept);

SLV_FN_TRAITS(, &, noexcept);
SLV_FN_TRAITS(const, &, noexcept);
SLV_FN_TRAITS(const volatile, &, noexcept);

SLV_FN_TRAITS(, &&, noexcept);
SLV_FN_TRAITS(const, &&, noexcept);
SLV_FN_TRAITS(const volatile, &&, noexcept);

#undef SLV_FN_TRAITS

} // namespace slv

#endif // SLV_TRAITS_H_