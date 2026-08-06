//
// Created by Kamil on 11.07.2026.
//
#include "LocationEditorWindow.h"

#include "imgui.h"
#include "ImGuiExtensions.h"
#include "misc/cpp/imgui_stdlib.h"
#include "TextManager.h"

bool LocationEditorWindow::Init()
{
#define X(l, e) Texts[static_cast<int>(Language::l)].LoadAll(Language::l);
    LanguageMacro(X)
#undef X
    return true;
}

bool LocationEditorWindow::Update()
{
    static int language = 0;

    const char* items[] = {
#define X(l, e) #l,
        LanguageMacro(X)
#undef X
    };

    const char* languageExtension[] = {
#define X(l, e) #e,
        LanguageMacro(X)
#undef X
    };

    TextManager& manager = Texts[language];

    visit_struct::for_each(manager, [&](const char* fName, auto& fValue)
    {
        ImGui::Begin(fName);
        ImGui::Combo("Language", &language, items, static_cast<int>(Language::COUNT));
        ImGui::Separator();
        visit_struct::for_each(fValue, [&](const char* name, auto& value)
        {
            using type = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<type, std::string>)
            {
                ImGui::InputText((name + (std::string("##") + fName)).c_str(), &value);
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    JSON j = JSON::object();
                    visit_struct::for_each(fValue, [&](const char* saveName, auto& saveValue)
                    {
                        j[saveName] = saveValue;
                    });
                    SaveJson(j, (RESOURCES_PATH + (std::string("Lang/") + languageExtension[language] + "/" + fName) + ".json").c_str());
                }
            }
        });
        ImGui::End();
    });

    return !WindowShouldClose();
}

void LocationEditorWindow::Close()
{
}
