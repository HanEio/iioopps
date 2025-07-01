#pragma once
#include <map>
#include <string>

enum class Lang { EN, ZH };
enum class StringID {
    Title, Menu_Start, Menu_Lang, Menu_Exit
};

class I18n {
public:
    static I18n& getInstance();
    void setLang(Lang lang);
    const std::string& get(StringID id);
private:
    I18n();
    void init();
    Lang _lang;
    std::map<StringID, std::string> _strings;
    std::map<Lang, std::map<StringID, std::string>> _lang_packs;
}; 