//
// Created by Kamil on 10.07.2026.
//
#include "TextManager.h"

std::string GetLocatedString(const JSON& j, const char* key, const char* defaultValue)
{
    std::string result;
#if PRODUCTION_BUILD
    ReadJsonValue(result, j, key, std::string(defaultValue));
#else
    ReadJsonValue(result, j, key, std::string("######"));
#endif
    return result;
}

void from_json(const JSON& j, MenuText& text)
{
    text.Play = GetLocatedString(j, "Play", "Play");
    text.Settings = GetLocatedString(j, "Settings", "Settings");
    text.Credits = GetLocatedString(j, "Credits", "Credits");
    text.Exit = GetLocatedString(j, "Exit", "Exit");
    text.Back = GetLocatedString(j, "Back", "Back");
}

void from_json(const JSON& j, LanguageList& text)
{
    int i = 0;
#define X(l) text.Value[i] = GetLocatedString(j, #l, #l); i++;
    LanguageMacro(X)
#undef X
}

void TextManager::LoadAll(const Language language)
{
    UnloadFont(Font);
    if (char* characters = LoadFileText(RESOURCES_PATH "Lang/Characters.txt"))
    {
        // 2. Pass this normal text to gather codepoints
        int codepointCount = 0;
        int* codepoints = LoadCodepoints(characters, &codepointCount);

        // 3. Load font (make sure Pangolin-Regular.ttf contains Polish characters, otherwise stick to Arial)
        Font = LoadFontEx(RESOURCES_PATH "Pangolin-Regular.ttf", 96, codepoints, codepointCount);
        UnloadCodepoints(codepoints);
        UnloadFileText(characters);
    } else
    {
        Font = LoadFont(RESOURCES_PATH "Pangolin-Regular.ttf");
    }

    Languages = ReadJson(RESOURCES_PATH "Lang/LanguageList.json");
    switch (language)
    {
        case Language::English:
        default:
            MainMenu = ReadJson(RESOURCES_PATH "Lang/EN/MainMenu.json");
            break;
        case Language::Polish:
            MainMenu = ReadJson(RESOURCES_PATH "Lang/PL/MainMenu.json");
            break;
    }
    CurrentLanguage = language;
}
