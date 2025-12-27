#pragma once
#include <string>
#include <vector>
#include <functional>

typedef std::function<void()> MenuAction;

struct MenuItem
{
    std::string title;
    MenuAction action;
    MenuItem(const std::string &t, MenuAction a) : title(t), action(a) {}
};

class Menu
{
private:
    std::string menuTitle;
    std::vector<MenuItem> options;

public:
    Menu(const std::string &title);
    Menu(const Menu &) = delete;
    Menu &operator=(const Menu &) = delete;
    ~Menu();

    void clearConsole() const;

    void draw() const;

    void addOption(const std::string &title, MenuAction action);

    void addOptions(const std::vector<MenuItem> &items);

    int getInput();

    void run();
};