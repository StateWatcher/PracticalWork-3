#pragma once
#include <iostream>
#include <vector>

class Matrix
{
private:
  std::vector<int> data;
  int size;

public:
  Matrix(int n);
  Matrix(const Matrix &) = delete;
  Matrix &operator=(const Matrix &) = delete;

  void print() const;
  void printAt(int startRow, int startCol) const;
  void updateCell(int row, int col, int value, int startRow, int startCol) const;

  void fillSpiral();
  void fillSnake();
  void fillRandom(int minVal = 1, int maxVal = 100);

  void swapBlocksA();
  void swapBlocksB();
  void swapBlocksC();
  void swapBlocksD();

  void sortElements(int sortType);

  void applyOperation(char op, int value);

  double calculateAverage() const;

  int *begin() { return data.data(); }
  int *end() { return data.data() + data.size(); }
  const int *begin() const { return data.data(); }
  const int *end() const { return data.data() + data.size(); }

  int getSize() const { return size; }
  int *operator[](int index) { return data.data() + index * size; }
  const int *operator[](int index) const { return data.data() + index * size; }
};