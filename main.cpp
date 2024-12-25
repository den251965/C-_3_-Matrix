#include <iostream>
#include <vector>

#include "log_duration.h"
#include "matrix.hpp"

size_t SettingSize = 10000;  // Настройка размера матрицы

#define Correct(x)                                                                    \
  if (x > SettingSize) {                                                              \
    std::cout << "Bad size matrix " << #x << " = " << x << " if allowed ( 0 < " << #x \
              << " <= " << SettingSize << ")";                                        \
    return 0;                                                                         \
  }

// Заполняем наш вектор-матрицу
//  Рандом у нас идет от 0 и до 50 , чтоб глаза не мазолить
int random() {
  return std::rand() % 51;
}

template <typename T>
void Radomize(std::vector<std::vector<T>>& matrix) {
  size_t count = matrix.size()^ 2;
  size_t k, l;
  for (size_t i = 0; i < count; ++i) {
    k = std::rand() % matrix.size();
    l = std::rand() % matrix[0].size();
    matrix[k][l] = random();
  }
}

template <typename T>
void PlusRavno(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
  for (size_t i = 0; i < matrix1.size(); ++i) {
    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      matrix1[i][j] += matrix2[i][j];
    }
  }
}

template <typename T>
void MinusRavno(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
  for (size_t i = 0; i < matrix1.size(); ++i) {
    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      matrix1[i][j] -= matrix2[i][j];
    }
  }
}

template <typename T>
void UmnojRavno(std::vector<std::vector<T>>& matrix1, std::vector<std::vector<T>>& matrix2) {
  for (size_t i = 0; i < matrix1.size(); ++i) {
    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      matrix1[i][j] *= matrix2[i][j];
    }
  }
}

template <typename T>
void StepjRavno(std::vector<std::vector<T>>& matrix1, int st) {
  std::vector<std::vector<int>> matrix2 = matrix1;
  for (size_t n = 0; n < st; ++n) {
    for (size_t i = 0; i < matrix1.size(); ++i) {
      for (size_t j = 0; j < matrix1[i].size(); ++j) {
        matrix1[i][j] *= matrix2[i][j];
      }
    }
  }
}

template <typename T>
void VectorTrans(std::vector<std::vector<T>>& matrix1) {
  std::vector<std::vector<int>> matrix(matrix1.size(), std::vector<int>(matrix1[0].size(), 0));
  for (size_t i = 0; i < matrix1.size(); ++i) {
    for (size_t j = 0; j < matrix1[i].size(); ++j) {
      matrix[i][j] += matrix1[j][i];
    }
  }
}

int main() {
  size_t h, w;

  std::cout << "Insert size ROW( max " << SettingSize << ") : ";
  std::cin >> h;
  Correct(h);

  std::cout << "Insert size COLUMN( max " << SettingSize << ") : ";
  std::cin >> w;
  Correct(w);

  Matrix2D<int> tab1(h, w);
  Matrix2D<int> tab2(h, w);

  tab1.Radomize();
  tab2.Radomize();

  // std::cout << "hesh mat1\n";
  // std::cout << tab1;

  // std::cout << "hesh mat2\n";
  // std::cout << tab2;

  std::vector<std::vector<int>> matrix1(h, std::vector<int>(w, 0));
  Radomize(matrix1);
  std::vector<std::vector<int>> matrix2(h, std::vector<int>(w, 0));
  Radomize(matrix2);

  {
    std::cout << "test + : \n";
    {
      {
        LogDuration n("hash +");
        tab1 += tab2;
      }
      {
        LogDuration n("vector +");
        PlusRavno(matrix1, matrix2);
      }
    }
  }

  std::cout << "test - \n";
  {
    {
      LogDuration n("hash -");
      tab1 -= tab2;
    }
    {
      LogDuration n("vector -");
      MinusRavno(matrix1, matrix2);
    }
  }

  std::cout << "test *\n";
  {
    {
      LogDuration n("hash * ");
      tab1 *= tab2;
    }
    {
      LogDuration n("vector *");
      UmnojRavno(matrix1, matrix2);
    }
  }

  std::cout << "test ^ 3\n";
  {
    {
      LogDuration n("hash ^ 3");
      tab1 ^=3;
    }
    // std::cout << tab1;

    {
      LogDuration n("vector ^ 3");
      StepjRavno(matrix1, 3);
    }
  }

  std::cout << "test transponir\n";
  {
    {
      LogDuration n("hash transponir ");
      tab1.transpon();
    }

    {
      LogDuration n("vector transponir ");
      VectorTrans(matrix1);
    }
  }
  std::cout << "Success !";

  return 0;
}
