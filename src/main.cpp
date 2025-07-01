#include "input.h"
#include "scene.h"
#include "i18n.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001);
    auto& i18n = I18n::getInstance();
    i18n.setLang(Lang::EN); // 默认英文
    while (true) {
        int choice = show_main_menu();
        switch (choice) {
            case 1: {
                CScene scene;
                scene.generate();
                int erase_count = inputDifficulty();
                scene.eraseRandomGrids(erase_count);
                scene.play();
                break;
            }
            case 2:
                i18n.setLang(i18n.get(StringID::Title) == "Sudoku" ? Lang::ZH : Lang::EN);
                break;
            case 3:
                return 0;
        }
    }
    return 0;
}
