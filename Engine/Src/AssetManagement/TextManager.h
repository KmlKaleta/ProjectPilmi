//
// Created by Kamil on 10.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_TEXT_MANAGER_H
#define SHEEP_GOES_DEVILE_TEXT_MANAGER_H
#include "JSON.h"
#include "raylib.h"
#include "include/visit_struct/visit_struct.hpp"

#define LanguageMacro(X) \
    X(English, EN) \
    X(Polish, PL)

enum class Language
{
#define X(l, e) l,
    LanguageMacro(X)
#undef X
    COUNT
};

enum class LanguageExtension
{
#define X(l, e) e,
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

VISITABLE_STRUCT(MenuText, Play, Settings, Credits, Exit, Back);

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

VISITABLE_STRUCT(TextManager, MainMenu);

#endif //SHEEP_GOES_DEVILE_TEXT_MANAGER_H
