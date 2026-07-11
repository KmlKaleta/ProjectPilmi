//
// Created by Kamil on 10.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_TEXT_MANAGER_H
#define SHEEP_GOES_DEVILE_TEXT_MANAGER_H
#include "JSON.h"
#include "raylib.h"

#define LanguageMacro(X) \
    X(English) \
    X(Polish)

enum class Language
{
#define X(l) l,
    LanguageMacro(X)
#undef X
    COUNT
};

struct MenuText
{
    std::string Play;
    std::string Settings;
    std::string Credits;
    std::string Exit;
    std::string Back;
};

void from_json(const JSON& j, MenuText& text);

struct LanguageList
{
    std::string Value[static_cast<int>(Language::COUNT)]{};
};

void from_json(const JSON& j, LanguageList& text);

struct TextManager
{
    Font Font{};
    LanguageList Languages;
    MenuText MainMenu;
    Language CurrentLanguage = Language::English;

    void LoadAll(Language language);
};
#endif //SHEEP_GOES_DEVILE_TEXT_MANAGER_H
