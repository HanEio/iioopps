#include "i18n.h"

I18n& I18n::getInstance() {
    static I18n instance;
    return instance;
}

I18n::I18n() : _lang(Lang::EN) {
    init();
    setLang(_lang);
}

void I18n::init() {
    _lang_packs[Lang::EN] = {
        {StringID::Title, "Sudoku"},
        {StringID::Menu_Start, "Start Game"},
        {StringID::Menu_Lang, "Switch Language"},
        {StringID::Menu_Exit, "Exit"}
    };
    _lang_packs[Lang::ZH] = {
        {StringID::Title, "数独"},
        {StringID::Menu_Start, "开始游戏"},
        {StringID::Menu_Lang, "切换语言"},
        {StringID::Menu_Exit, "退出"}
    };
}

void I18n::setLang(Lang lang) {
    _lang = lang;
    _strings = _lang_packs[_lang];
}

const std::string& I18n::get(StringID id) {
    return _strings[id];
} 