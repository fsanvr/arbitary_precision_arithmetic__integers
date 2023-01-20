#pragma once
#include <vector>
//#include <compare>
#include <string>
#include <iostream>
#include <limits>
typedef unsigned long long uint64_t;
// Arbitrary-precision arithmetic representation of integers

namespace arbitary_precision_arithmetic {

class Integer {
 private:
  typedef int32_t dataType;
  static const dataType base = 100;

  bool _is_negative = false;
  std::vector<dataType> _data;

  static std::string ToString(const Integer& value);
  static std::string ToString(uint64_t value);

 public:
  Integer();
  Integer(const Integer&);
  Integer(Integer&&) noexcept;  // -__-
  ~Integer();

  template<
    typename T,
    typename S = std::enable_if_t<std::is_integral<T>::value>>
  explicit Integer(T);

  Integer& operator=(const Integer&);
  Integer& operator=(Integer&&) noexcept;  // -__-

  Integer operator-() const;
  Integer& operator--();
  const Integer operator--(int);

  Integer operator+() const;
  Integer& operator++();
  const Integer operator++(int);

  [[nodiscard]] Integer operator-(const Integer&) const;
  Integer& operator-=(const Integer&);

  [[nodiscard]] Integer operator+(const Integer&) const;
  Integer& operator+=(const Integer&);

  [[nodiscard]] Integer operator*(const Integer&) const;
  Integer& operator*=(const Integer&);

  [[nodiscard]] Integer operator/(const Integer&) const;
  Integer& operator/=(const Integer&);

  [[nodiscard]] Integer operator%(const Integer&) const;
  Integer& operator%=(const Integer&);

  template<
    typename T,
    typename S = std::enable_if_t<std::is_integral<T>::value>>
  [[nodiscard]] explicit operator T() const;

  [[nodiscard]] bool operator==(const Integer&) const;
  [[nodiscard]] bool operator!=(const Integer&) const;
  [[nodiscard]] bool operator<(const Integer&) const;
  [[nodiscard]] bool operator<=(const Integer&) const;
  [[nodiscard]] bool operator>(const Integer&) const;
  [[nodiscard]] bool operator>=(const Integer&) const;
  // ...or you could read about operator<=> and implement it instead of
  // implementation of comparators above

  // Output stream print helper
  template <typename OStream>
  friend OStream&& operator<<(OStream&&, const Integer&);
}; //class Integer

}  // namespace arbitary_precision_arithmetic
