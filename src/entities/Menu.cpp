#include "Menu.h"
#include "Console.h"
#include <iostream>
#include <limits>

Menu::Menu(const std::string& title) : menuTitle(title) {}

Menu::~Menu() {}

void Menu::clearConsole() const
{
    clearScreen();
}

void Menu::draw() const
{
    clearConsole();
    std::cout << "=== " << menuTitle << " ===" << std::endl;
    std::cout << std::endl;
    for (size_t i = 0; i < options.size(); i++)
    {
        std::cout << (i + 1) << ". " << options[i].title << std::endl;
    }

    std::cout << "0. Выход" << std::endl;
    std::cout << std::endl;
    std::cout << "Выберите опцию: ";
}

void Menu::addOption(const std::string &title, MenuAction action)
{
    options.push_back(MenuItem(title, action));
}

void Menu::addOptions(const std::vector<MenuItem> &items)
{
    for (const auto &item : items)
    {
        options.push_back(item);
    }
}

int Menu::getInput()
{
    int choice;

    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }

    if (choice < 0 || static_cast<size_t>(choice) > options.size())
    {
        return -1;
    }

    return choice;
}

void Menu::run()
{
    while (true)
    {
        draw();
        int choice = getInput();

        if (choice == -1)
        {
            std::cout << "\nНеверный ввод! Нажмите Enter для продолжения...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            continue;
        }

        if (choice == 0)
        {
            break;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        options[choice - 1].action();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.get();
    }
}