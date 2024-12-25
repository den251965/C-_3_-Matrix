#pragma once
#include <algorithm>
#include <iostream>
#include <unordered_map>

template <typename T>
class Matrix2D {
public:
  explicit Matrix2D(size_t h, size_t w) : row_(h), column_(w) {};

  void Radomize() {
    size_t count = row_ ^ 2;
    size_t k, l;
    T item;
    for (size_t i = 0; i < count; ++i) {
      k = std::rand() % row_;
      l = std::rand() % column_;
      item = static_cast<T>(random());
      InsertItem(k, l, item);
    }
  }

  void InsertItem(size_t k, size_t l, T& item) {
    table_[{k, l}] = item;
  }

  void DeleteItem(size_t k, size_t l) {
    table_->erase({k, l});
  }

  struct KeyHasher {
    size_t operator()(const std::pair<size_t, const size_t>& points) const {
      size_t SettingSize_ = 10000;
      return points.first * SettingSize_ * 10 + points.second;
    }
  };

  std::unordered_map<std::pair<const size_t, const size_t>, T, KeyHasher>& GetMatrix() {
    return table_;
  }

  const T& GetItem(size_t k, size_t l) {
    if (table_.count({k, l}))
      return table_.at({k, l});
    return static_cast<T>(0);
  }

  size_t H() {
    return row_;
  }

  size_t W() {
    return column_;
  }

  Matrix2D& operator+=(Matrix2D& t) {
    for (const auto& [key, value] : t.GetMatrix())
      table_[key] += value;
    return *this;
  }

  Matrix2D& operator-=(Matrix2D& t) {
    for (const auto& [key, value] : t.GetMatrix())
      table_[key] -= value;
    return *this;
  }

  Matrix2D& operator*=(Matrix2D& t) {
    for (const auto& [key, value] : t.GetMatrix())
      table_[key] *= value;
    return *this;
    ;
  }

  Matrix2D& operator^=(int t) {
    std::unordered_map<std::pair<const size_t, const size_t>, T, KeyHasher> temp = table_;
    for (int i = 0; i < t; ++i) {
      for (const auto& [key, value] : table_)
        table_[key] *= temp[key];
    }
    return *this;
  }

  void transpon() {
    std::unordered_map<std::pair<const size_t, const size_t>, T, KeyHasher> temp;
    for (auto& [key, value] : table_) {
      temp[{key.second, key.first}] = value;
    }
    table_ = temp;
    std::swap(row_, column_);
  }

private:
  std::unordered_map<std::pair<const size_t, const size_t>, T, KeyHasher> table_;
  size_t row_;
  size_t column_;

  // Рандом у нас идет от 0 и до 50 , чтоб глаза не мазолить
  int random() {
    return std::rand() % 51;
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix2D<T> table) {
  out << "matrix ptint\n";
  for (size_t i = 0; i < table.H(); ++i) {
    out << "| ";
    for (size_t j = 0; j < table.W(); ++j) {
      const T item = table.GetItem(i, j);
      if (item)
        out << item << " | ";
      else
        out << " NL | ";
    }
    out << "\n";
  }
  out << "\n";
  return out;
}