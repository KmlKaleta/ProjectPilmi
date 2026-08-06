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
    visit_struct::for_each(text, [&](const char* name, std::string& value)
    {
        value = GetLocatedString(j, name, name);
    });
}

void from_json(const JSON& j, LanguageList& text)
{
#define X(l, e) text.Value[static_cast<int>(Language::l)] = GetLocatedString(j, #l, #l);
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
    const char* languageExtension[] = {
#define X(l, e) #e,
        LanguageMacro(X)
#undef X
    };
    const std::string extension = languageExtension[static_cast<int>(language)];

    visit_struct::for_each(*this, [&](const char* name, auto& value)
    {
        value = ReadJson((RESOURCES_PATH + ("Lang/" + extension + "/" + name) + ".json").c_str());
    });

    CurrentLanguage = language;
}
