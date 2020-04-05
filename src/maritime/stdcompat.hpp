// #ifndef MARITIME_STDCOMPAT_HPP
// #define MARITIME_STDCOMPAT_HPP

// #if __cplusplus < 201703
// #include <cstddef>

// namespace std {

// template <class C>
// constexpr auto size(const C& c) -> decltype(c.size()) {
//   return c.size();
// }

// template <class T, size_t N>
// constexpr size_t size(const T (&array)[N]) noexcept {
//   return N;
// }

// }  // namespace std
// #endif

// #endif
