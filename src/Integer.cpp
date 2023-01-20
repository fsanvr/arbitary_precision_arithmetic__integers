#include "Integer.hpp"

namespace arbitary_precision_arithmetic {

template <typename OStream>
OStream&& operator<<(OStream&& os, const Integer& value) {
  os << Integer::ToString(value);
  return os;
}

std::string Integer::ToString(const Integer& value) {
  std::string result;
  if (value._data.empty()) {
    return result = "0";
  }
  if (value._is_negative) {
    result.append("-");
  }
  result.append(std::to_string(value._data[value._data.size() - 1]));

  for (int64_t idx = static_cast<int64_t>(value._data.size()) - 2; idx >= 0;
       --idx) {
    std::string temp = Integer::ToString(value._data[idx]);
    result.append(temp);
  }
  return result;
}

std::string Integer::ToString(uint64_t value) {
  std::string str_base = std::to_string(Integer::base);
  std::string str_value = std::to_string(value);
  std::string result(str_base.length() - str_value.length() - 1, '0');
  result.append(str_value);
  return result;
}

Integer::Integer() { _data.resize(0); }

Integer::Integer(const Integer& other) {
  _is_negative = other._is_negative;
  _data.assign(other._data.begin(), other._data.end());
}

Integer::Integer(Integer&& other) noexcept
    : _is_negative(other._is_negative), _data(std::move(other._data)) {}

Integer& Integer::operator=(const Integer& other) {
  _is_negative = other._is_negative;
  _data.assign(other._data.begin(), other._data.end());
  return *this;
}

Integer& Integer::operator=(Integer&& other) noexcept {
  _is_negative = other._is_negative;
  _data = std::move(other._data);
  return *this;
}

template<
    typename T,
    typename S>
Integer::Integer(T value) {
  _is_negative = value < 0;
  while (value) {
    _data.push_back(value % Integer::base);
    value /= Integer::base;
  }
}

Integer::~Integer() = default;

Integer Integer::operator-() const {
  Integer copy(*this);
  copy._is_negative = !copy._is_negative;
  return copy;
}

Integer& Integer::operator--() { return *this -= Integer(1); }

const Integer Integer::operator--(int) {
  Integer result(*this);
  *this -= Integer(1);
  return result;
}

Integer Integer::operator+() const { return *this; }

Integer& Integer::operator++() { return *this += Integer(1); }

const Integer Integer::operator++(int) {
  Integer result(*this);
  *this += Integer(1);
  return result;
}

Integer Integer::operator+(const Integer& other) const {
  if (this->_is_negative && !other._is_negative) return other - (-*this);
  if (!this->_is_negative && other._is_negative) return *this - (-other);

  if (other > *this) return other + *this;
  Integer result(*this);
  result._data.resize(result._data.size() + 1);

  for (int i = 0; i < other._data.size(); ++i) {
    result._data[i] += other._data[i];
  }

  for (int i = 0; i < result._data.size(); ++i) {
    if (result._data[i] >= Integer::base) {
      result._data[i] -= Integer::base;
      result._data[i + 1]++;
    }
  }

  while (result._data[result._data.size() - 1] == 0 && !result._data.empty()) {
    result._data.pop_back();
  }

  return result;
}

Integer& Integer::operator+=(const Integer& other) {
  return *this = *this + other;
}

Integer Integer::operator-(const Integer& other) const {
  if (this->_is_negative && !other._is_negative) return other + (-*this);
  if (!this->_is_negative && other._is_negative) return *this + (-other);

  if (other > *this) return -(other - *this);
  Integer result(*this);

  for (int i = 0; i < other._data.size(); ++i) {
    result._data[i] -= other._data[i];
  }

  for (int i = 0; i < result._data.size(); ++i) {
    if (result._data[i] < 0) {
      result._data[i] += Integer::base;
      result._data[i + 1]--;
    }
  }

  while (result._data[result._data.size() - 1] == 0 && !result._data.empty()) {
    result._data.pop_back();
  }

  return result;
}

Integer& Integer::operator-=(const Integer& other) {
  return *this = *this - other;
}

Integer Integer::operator*(const Integer& other) const {
  Integer result;
  result._is_negative = this->_is_negative ^ other._is_negative;
  result._data.resize(this->_data.size() + other._data.size());

  for (int j = 0; j < other._data.size(); ++j) {
    for (int i = 0; i < this->_data.size(); ++i) {
      result._data[i + j] += other._data[j] * this->_data[i];
    }
  }

  dataType balance = 0;

  for (int& i : result._data) {
    i += balance;
    balance = i / Integer::base;
    i %= Integer::base;
  }

  while (result._data[result._data.size() - 1] == 0 && !result._data.empty()) {
    result._data.pop_back();
  }

  return result;
}

Integer& Integer::operator*=(const Integer& other) {
  return *this = *this * other;
}

Integer Integer::operator/(const Integer& other) const {
  {
    Integer left(*this);
    left._is_negative = false;
    Integer right(other);
    right._is_negative = false;
    
    if (left < right) {
      return Integer(0);
    }
    if (right == Integer(1)) {
      return *this;
    }
  }

  // divination on shit

  Integer factor(1);
  factor._is_negative = this->_is_negative ^ other._is_negative;
  while (true) {
    Integer result(other * factor);
    if (result <= *this && (result + other) >= *this) {
      return factor;
    } else if (result < *this) {
      factor *= Integer(2);
    } else if (result > *this) {
      factor--;
    }
  }
}

Integer& Integer::operator/=(const Integer& other) {
  return *this = *this / other;
}

Integer Integer::operator%(const Integer& other) const {
  Integer result = *this - (*this / other) * other;
  if (result._is_negative) result += other;
  return result;
}

Integer& Integer::operator%=(const Integer& other) {
  return *this = *this % other;
}

template<
    typename T,
    typename S>
Integer::operator T() const {
  return *this >= Integer(std::numeric_limits<T>::max()) ? std::numeric_limits<T>::max()
    : static_cast<T>(std::stoll(Integer::ToString(*this)));
}

bool Integer::operator==(const Integer& other) const {
  return this->_is_negative == other._is_negative && this->_data == other._data;
}

bool Integer::operator!=(const Integer& other) const {
  return !(*this == other);
}

bool Integer::operator>(const Integer& other) const {
  if (this->_is_negative && !other._is_negative) return false;
  if (this->_data.size() < other._data.size()) return false;
  if (this->_data.size() > other._data.size()) return true;

  for (uint64_t i = this->_data.size() - 1; i >= 0; --i) {
    if (this->_data[i] > other._data[i]) return true;
    if (this->_data[i] < other._data[i]) return false;
  }
  return false;
}

bool Integer::operator>=(const Integer& other) const {
  return *this > other || *this == other;
}

bool Integer::operator<(const Integer& other) const { return other > *this; }

bool Integer::operator<=(const Integer& other) const {
  return other > *this || *this == other;
}

// also you could implement your own string-literal for this type
// Integer ""_li(const char*);
}