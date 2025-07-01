#include "input.h"
#include <iostream>
#include "i18n.h"

// 返回需要挖掉的格子数量
int inputDifficulty()
{
    std::cout << "Select difficulty: 1 Easy  2 Normal  3 Hard" << std::endl;

    int choice = 0;
    int grids_to_erase = 0;
    while (true) // 循环直到获得有效输入
    {
        std::cout << "> ";
        std::cin >> choice;

        // 根据选择设置挖洞数量
        switch (static_cast<Difficulty>(choice))
        {
        case Difficulty::EASY:
            grids_to_erase = 20;
            break;
        case Difficulty::NORMAL:
            grids_to_erase = 35;
            break;
        case Difficulty::HARD:
            grids_to_erase = 50;
            break;
        default:
            grids_to_erase = 0; // 无效选择
        }

        if (grids_to_erase > 0)
            break; // 输入有效，跳出循环

        std::cout << "Invalid input, please try again." << std::endl;
        // 清理错误的输入流
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return grids_to_erase;
}

int show_main_menu() {
    auto& i18n = I18n::getInstance();
    while (true) {
        system("cls");
        std::cout << i18n.get(StringID::Title) << std::endl;
        std::cout << "1. " << i18n.get(StringID::Menu_Start) << std::endl;
        std::cout << "2. " << i18n.get(StringID::Menu_Lang) << std::endl;
        std::cout << "3. " << i18n.get(StringID::Menu_Exit) << std::endl;
        std::cout << "> ";
        int choice;
        std::cin >> choice;
        if (choice >= 1 && choice <= 3) {
            return choice;
        }
        std::cout << "Invalid input, please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}