#include "Matrix.h"
#include "Menu.h"
#include "Console.h"
#include <iostream>
#include <limits>
#include <memory>

int main()
{
    std::unique_ptr<Matrix> matrix = std::make_unique<Matrix>(6);

    Menu mainMenu("Главное меню");

    Menu fillMenu("Заполнение матрицы");
    fillMenu.addOption("Заполнить спиралью", [&matrix]() {
        matrix->fillSpiral();
    });
    fillMenu.addOption("Заполнить змейкой", [&matrix]() {
        matrix->fillSnake();
    });
    fillMenu.addOption("Заполнить случайными числами (1 до N*N)", [&matrix]() {
        int size = matrix->getSize();
        matrix->fillRandom(1, size * size);
    });
    fillMenu.addOption("Заполнить случайными числами (1 до 100)", [&matrix]() {
        matrix->fillRandom(1, 100);
    });

    Menu swapMenu("Перестановка блоков");
    swapMenu.addOption("Вариант A (циклическая)", [&matrix]() {
        matrix->swapBlocksA();
        matrix->print();
    });
    swapMenu.addOption("Вариант B (диагональная)", [&matrix]() {
        matrix->swapBlocksB();
        matrix->print();
    });
    swapMenu.addOption("Вариант C (вертикальная)", [&matrix]() {
        matrix->swapBlocksC();
        matrix->print();
    });
    swapMenu.addOption("Вариант D (горизонтальная)", [&matrix]() {
        matrix->swapBlocksD();
        matrix->print();
    });

    Menu sortMenu("Сортировка элементов");
    sortMenu.addOption("Shaker Sort", [&matrix]() {
        matrix->sortElements(1);
    });
    sortMenu.addOption("Comb Sort", [&matrix]() {
        matrix->sortElements(2);
    });
    sortMenu.addOption("Insertion Sort", [&matrix]() {
        matrix->sortElements(3);
    });
    sortMenu.addOption("Quick Sort", [&matrix]() {
        matrix->sortElements(4);
    });

    Menu operationMenu("Операции с матрицей");
    operationMenu.addOption("Прибавить число ко всем элементам", [&matrix]() {
        int value;
        std::cout << "Введите число: ";
        std::cin >> value;
        matrix->applyOperation('+', value);
    });
    operationMenu.addOption("Вычесть число из всех элементов", [&matrix]() {
        int value;
        std::cout << "Введите число: ";
        std::cin >> value;
        matrix->applyOperation('-', value);
    });
    operationMenu.addOption("Умножить все элементы на число", [&matrix]() {
        int value;
        std::cout << "Введите число: ";
        std::cin >> value;
        matrix->applyOperation('*', value);
    });
    operationMenu.addOption("Разделить все элементы на число", [&matrix]() {
        int value;
        std::cout << "Введите число (не 0): ";
        std::cin >> value;
        if (value == 0)
        {
            std::cout << "Ошибка! Деление на ноль невозможно." << std::endl;
            return;
        }
        matrix->applyOperation('/', value);
    });

    mainMenu.addOption("Изменить размер матрицы (N)", [&matrix]() {
        int size;
        std::cout << "Текущий размер: " << matrix->getSize() << std::endl;
        std::cout << "Введите новый размер (6, 8 или 10): ";
        
        if (std::cin >> size && (size == 6 || size == 8 || size == 10))
        {
            matrix = std::make_unique<Matrix>(size);
            std::cout << "Матрица пересоздана с размером " << size << "x" << size << std::endl;
        }
        else
        {
            std::cout << "Ошибка! Размер должен быть 6, 8 или 10." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    });
    mainMenu.addOption("Заполнить матрицу", [&fillMenu]() {
        fillMenu.run();
    });
    mainMenu.addOption("Переставить блоки", [&swapMenu]() {
        swapMenu.run();
    });
    mainMenu.addOption("Сортировать элементы", [&sortMenu]() {
        sortMenu.run();
    });
    mainMenu.addOption("Применить операцию", [&operationMenu]() {
        operationMenu.run();
    });
    mainMenu.addOption("Показать текущую матрицу", [&matrix]() {
        std::cout << "Текущая матрица (размер " << matrix->getSize() << "x" << matrix->getSize() << "):" << std::endl;
        matrix->print();
    });

    mainMenu.run();

    return 0;
}