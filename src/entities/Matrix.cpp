#include "Matrix.h"
#include "Console.h"
#include "Sort.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

Matrix::Matrix(int n) : size(n), data(n * n, 0)
{
  srand(static_cast<unsigned int>(time(nullptr)));
}

void Matrix::print() const
{
  const int *ptr = begin();
  const int *endPtr = end();
  int count = 0;

  while (ptr < endPtr)
  {
    std::cout << std::setw(4) << *ptr << " ";
    ptr++;
    count++;

    if (count % size == 0)
    {
      std::cout << std::endl;
    }
  }
}

void Matrix::printAt(int startRow, int startCol) const
{
  const int *ptr = begin();
  const int *endPtr = end();
  int offset = 0;

  while (ptr < endPtr)
  {
    int row = offset / size;
    int col = offset % size;

    setCursor(startRow + row, startCol + col * 5);
    std::cout << std::setw(4) << *ptr << " ";

    ptr++;
    offset++;
  }
  std::cout.flush();
}

void Matrix::updateCell(int row, int col, int value, int startRow, int startCol) const
{
  setCursor(startRow + row, startCol + col * 5);
  std::cout << std::setw(4) << value;
  std::cout.flush();
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Matrix::fillSpiral()
{
  clearScreen();
  hideCursor();

  std::cout << "Заполнение спиралью:" << std::endl << std::endl;
  printAt(2, 0);

  int top = 0, bottom = size - 1;
  int left = 0, right = size - 1;
  int num = 1;

  int *start = begin();

  while (top <= bottom && left <= right)
  {
    for (int j = left; j <= right; j++)
    {
      *(start + top * size + j) = num;
      updateCell(top, j, num, 2, 0);
      num++;
    }
    top++;

    for (int i = top; i <= bottom; i++)
    {
      *(start + i * size + right) = num;
      updateCell(i, right, num, 2, 0);
      num++;
    }
    right--;

    if (top <= bottom)
    {
      for (int j = right; j >= left; j--)
      {
        *(start + bottom * size + j) = num;
        updateCell(bottom, j, num, 2, 0);
        num++;
      }
      bottom--;
    }

    if (left <= right)
    {
      for (int i = bottom; i >= top; i--)
      {
        *(start + i * size + left) = num;
        updateCell(i, left, num, 2, 0);
        num++;
      }
      left++;
    }
  }

  showCursor();
  setCursor(2 + size + 1, 0);
}

void Matrix::fillSnake()
{
  clearScreen();
  hideCursor();

  std::cout << "Заполнение змейкой:" << std::endl << std::endl;
  printAt(2, 0);

  int num = 1;
  int *start = begin();

  for (int j = 0; j < size; j++)
  {
    if (j % 2 == 0)
    {
      for (int i = 0; i < size; i++)
      {
        *(start + i * size + j) = num;
        updateCell(i, j, num, 2, 0);
        num++;
      }
    }
    else
    {
      for (int i = size - 1; i >= 0; i--)
      {
        *(start + i * size + j) = num;
        updateCell(i, j, num, 2, 0);
        num++;
      }
    }
  }

  showCursor();
  setCursor(2 + size + 1, 0);
}

void Matrix::fillRandom(int minVal, int maxVal)
{
  clearScreen();
  hideCursor();

  std::cout << "Заполнение случайными числами от " << minVal << " до " << maxVal << ":" << std::endl << std::endl;
  printAt(2, 0);

  int *ptr = begin();
  int *endPtr = end();
  int offset = 0;

  while (ptr < endPtr)
  {
    *ptr = minVal + rand() % (maxVal - minVal + 1);

    int row = offset / size;
    int col = offset % size;
    updateCell(row, col, *ptr, 2, 0);

    ptr++;
    offset++;
  }

  showCursor();
  setCursor(2 + size + 1, 0);
}

void Matrix::swapBlocksA()
{
  std::cout << "Перестановка блоков (вариант A - циклическая)" << std::endl;

  int blockSize = size / 2;
  int *start = begin();
  
  int blockElements = blockSize * blockSize;
  int *temp = new int[blockElements * 4];
  
  int *block1 = temp;
  int *block2 = temp + blockElements;
  int *block3 = temp + blockElements * 2;
  int *block4 = temp + blockElements * 3;

  int *b1Ptr = block1;
  int *b2Ptr = block2;
  int *b3Ptr = block3;
  int *b4Ptr = block4;

  for (int i = 0; i < blockSize; i++)
  {
    int *row = start + i * size;
    
    for (int j = 0; j < blockSize; j++)
    {
      *b1Ptr++ = *(row + j);
      *b2Ptr++ = *(row + j + blockSize);
    }
  }

  for (int i = 0; i < blockSize; i++)
  {
    int *row = start + (i + blockSize) * size;
    
    for (int j = 0; j < blockSize; j++)
    {
      *b4Ptr++ = *(row + j);
      *b3Ptr++ = *(row + j + blockSize);
    }
  }

  b1Ptr = block1;
  b2Ptr = block2;
  b3Ptr = block3;
  b4Ptr = block4;

  for (int i = 0; i < blockSize; i++)
  {
    int *row = start + i * size;
    
    for (int j = 0; j < blockSize; j++)
    {
      *(row + j) = *b4Ptr++;
      *(row + j + blockSize) = *b1Ptr++;
    }
  }

  for (int i = 0; i < blockSize; i++)
  {
    int *row = start + (i + blockSize) * size;
    
    for (int j = 0; j < blockSize; j++)
    {
      *(row + j) = *b3Ptr++;
      *(row + j + blockSize) = *b2Ptr++;
    }
  }

  delete[] temp;
}

void Matrix::swapBlocksB()
{
  std::cout << "Перестановка блоков (вариант B - диагональная)" << std::endl;

  int blockSize = size / 2;
  int *start = begin();

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + i * size + j);
      *(start + i * size + j) = *(start + (i + blockSize) * size + j + blockSize);
      *(start + (i + blockSize) * size + j + blockSize) = temp;
    }
  }

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + i * size + j + blockSize);
      *(start + i * size + j + blockSize) = *(start + (i + blockSize) * size + j);
      *(start + (i + blockSize) * size + j) = temp;
    }
  }
}

void Matrix::swapBlocksC()
{
  std::cout << "Перестановка блоков (вариант C - вертикальная)" << std::endl;

  int blockSize = size / 2;
  int *start = begin();

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + i * size + j);
      *(start + i * size + j) = *(start + (i + blockSize) * size + j);
      *(start + (i + blockSize) * size + j) = temp;
    }
  }

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + i * size + j + blockSize);
      *(start + i * size + j + blockSize) = *(start + (i + blockSize) * size + j + blockSize);
      *(start + (i + blockSize) * size + j + blockSize) = temp;
    }
  }
}

void Matrix::swapBlocksD()
{
  std::cout << "Перестановка блоков (вариант D - горизонтальная)" << std::endl;

  int blockSize = size / 2;
  int *start = begin();

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + i * size + j);
      *(start + i * size + j) = *(start + i * size + j + blockSize);
      *(start + i * size + j + blockSize) = temp;
    }
  }

  for (int i = 0; i < blockSize; i++)
  {
    for (int j = 0; j < blockSize; j++)
    {
      int temp = *(start + (i + blockSize) * size + j);
      *(start + (i + blockSize) * size + j) = *(start + (i + blockSize) * size + j + blockSize);
      *(start + (i + blockSize) * size + j + blockSize) = temp;
    }
  }
}

void Matrix::sortElements(int sortType)
{
  int *start = begin();
  int *finish = end();

  switch (sortType)
  {
  case 1:
    std::cout << "Сортировка Shaker Sort..." << std::endl;
    shakerSort(start, finish);
    break;
  case 2:
    std::cout << "Сортировка Comb Sort..." << std::endl;
    combSort(start, finish);
    break;
  case 3:
    std::cout << "Сортировка Insertion Sort..." << std::endl;
    insertionSort(start, finish);
    break;
  case 4:
    std::cout << "Сортировка Quick Sort..." << std::endl;
    quickSort(start, finish);
    break;
  default:
    std::cout << "Неверный тип сортировки!" << std::endl;
    return;
  }

  std::cout << "Сортировка завершена!" << std::endl;
  print();
}

void Matrix::applyOperation(char op, int value)
{
  int *endPtr = end();

  for (int *ptr = begin(); ptr < endPtr; ptr++)
  {
    switch (op)
    {
    case '+':
      *ptr += value;
      break;
    case '-':
      *ptr -= value;
      break;
    case '*':
      *ptr *= value;
      break;
    case '/':
      if (value != 0)
        *ptr /= value;
      break;
    }
  }

  std::cout << "Операция '" << op << "' применена к матрице" << std::endl;
  print();
}

double Matrix::calculateAverage() const
{
  std::cout << "=== Вычисление среднего арифметического ===" << std::endl << std::endl;

  std::cout << "Текущая матрица:" << std::endl;
  print();
  std::cout << std::endl;

  const int *ptr = begin();
  const int *endPtr = end();

  long long sum = 0;
  int count = 0;
  int elementsPerRow = 6;

  std::cout << "Процесс суммирования (показаны первые элементы):" << std::endl;

  while (ptr < endPtr)
  {
    sum += *ptr;
    count++;

    if (count <= 12)
    {
      std::cout << *ptr;
      if (count < endPtr - begin() && count < 12)
        std::cout << " + ";

      if (count % elementsPerRow == 0)
        std::cout << std::endl;
    }
    else if (count == 13)
    {
      std::cout << "..." << std::endl;
    }

    ptr++;
  }

  std::cout << std::endl;
  std::cout << "Промежуточные результаты:" << std::endl;
  std::cout << "  Сумма всех элементов: " << sum << std::endl;
  std::cout << "  Количество элементов: " << count << std::endl;
  std::cout << "  Формула: среднее = сумма / количество" << std::endl;
  std::cout << "  Вычисление: " << sum << " / " << count << " = ";

  double average = static_cast<double>(sum) / count;

  std::cout << std::fixed << std::setprecision(2) << average << std::endl;
  std::cout << std::endl;
  std::cout << "Среднее арифметическое: " << average << std::endl;

  return average;
}