//
// Created by Kamil on 04.06.2026.
//
#include "EditorComponentsUI.h"

#include <string>

#include "EditorScene.h"
#include "raygui.h"
#include "ComponentData.h"
#include "LevelManager.h"

float EditorComponentsUI::GetHeight(const EditorScene& editor, const float padding) const
{
    if (!editor.RenderersEditor.AnySelected)
    {
        return 20 + padding;
    }

    return 20 + padding;
}


#define X(e, v) #v ";"
constexpr const char* ComponentNames = {
    "NoComponent;"
    ComponentNamesMacro(X)
};
#undef X

void DrawRange(const char* name, Range& range, Rectangle rect, float padding)
{
    float value = range.Get();
    GuiSlider(rect, name, TextFormat("%s: %.2f", name, value), &value, range.Min, range.Max);
    range.Set(value);
}

void EditorComponentsUI::Draw(const float width, const float contentX, float contentY, const float padding,
                              const EditorScene& editor, LevelData& level) const
{
    if (!editor.RenderersEditor.AnySelected)
    {
        GuiLabel({contentX, contentY, width, 20}, "No Renderer Selected");
        return;
    }
    auto componentData = level.Components.GetComponent(editor.RenderersEditor.GetSelectedRenderer());
    int value = componentData.Type;
    std::string comboStr = ComponentNames;
    comboStr.pop_back();

    GuiComboBox({contentX, contentY, width, 20}, comboStr.c_str(), &value);

    if (value != componentData.Type)
    {
        level.Components.ChangeType(editor.RenderersEditor.GetSelectedRenderer(), value);
        componentData = level.Components.GetComponent(editor.RenderersEditor.GetSelectedRenderer());
    }


    contentY += 20 + padding;
    switch (componentData.Type)
    {
#define X(e,v) case ComponentData::e: \
        visit_struct::for_each(level.Components.Get##v##Data(componentData.Index), [&](const char* name, auto& fieldValue) \
        { \
            using t = std::decay_t<decltype(fieldValue)>; \
            if constexpr  (std::is_same_v<t, Range>) \
            { \
                DrawRange(name, fieldValue, {contentX, contentY, width, 20},padding); \
            } \
        }); \
        break;
            ComponentNamesMacro(X)
#undef X
        default:
            break;
    }
}
