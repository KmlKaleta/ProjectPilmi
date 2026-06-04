// //
// // Created by Kamil on 27.05.2026.
// //
//
// #ifndef SHEEP_GOES_DEVILE_UI_PANEL_H
// #define SHEEP_GOES_DEVILE_UI_PANEL_H
// #include "raylib.h"
//
// #include <cstdint>
// #include <string>
// #include <vector>
//
// struct UIPanel;
// struct AssetManager;
// struct SpriteManager;
// struct IconsManager;
// struct SpriteData;
//
// struct UITransform
// {
//     Rectangle Rect = {};
//
//     UITransform() = default;
//
//     explicit UITransform(const Rectangle rect) : Rect(rect)
//     {
//     }
//
//     UITransform(const float x, const float y, const float width, const float height) : Rect({x, y, width, height})
//     {
//     }
//
//     Rectangle CalculateRect(const Rectangle parent) const
//     {
//         Rectangle rect;
//
//         rect.x = Rect.x < 0 ? parent.x + parent.width + Rect.x - Rect.width : parent.x + Rect.x;
//         rect.width = Rect.width;
//
//         rect.y = Rect.y < 0 ? parent.y + parent.height + Rect.y - Rect.height : parent.y + Rect.y;
//         rect.height = Rect.height;
//
//         return rect;
//     }
// };
//
// struct SpriteRenderData
// {
//     uint64_t SpriteId = 0;
//     float Scale = 1;
//     int TexX = 0;
//     int TexY = 0;
//     Color Tint = WHITE;
// };
//
// struct Interactable
// {
//     Color CurrentColor = {};
//     Color TargetColor = {};
//     UITransform Rect = {};
//
//     Color DefaultColor = {240, 240, 240, 255};
//     Color HoverColor = {150, 150, 150, 255};
//     Color ClickColor = {110, 110, 110, 255};
//
//     size_t DataIndex = 0;
//     int ContentType = 0;
//     int InteractionType = 0;
//
//     Interactable(UITransform rect, int contentType, int interactionType = 0);
//
//     void Update(float deltaTime);
//
//     void Render(const AssetManager& assetManager, const UIPanel& panel, Rectangle parent) const;
//
//     bool Process(float deltaTime, Vector2 mousePosition, const AssetManager& assetManager, const UIPanel& panel,
//                  Rectangle parent);
//
//     enum
//     {
//         CONTENT_NONE,
//         CONTENT_SPRITE,
//         CONTENT_ICON,
//         CONTENT_TEXT,
//     };
//
// private:
//     void RenderSprite(const SpriteManager& spritesManager, const UIPanel& panel, Rectangle rect) const;
//
//     void RenderIcon(const IconsManager& iconsManager, const UIPanel& panel, Rectangle rect) const;
//
//     void RenderTexture(const SpriteData& spriteData, Rectangle rect, const SpriteRenderData& renderData) const;
// };
//
// struct Label
// {
//     std::string Text = {};
//     Font Font = GetFontDefault();
//     Vector2 Position = {};
//     float FontSize = 20;
//
//     void Render(const Rectangle parent) const
//     {
//         Vector2 position = Position;
//         const float spacing = std::max(FontSize, 10.f) / 10;
//         const auto [textWidth, textHeight] = MeasureTextEx(Font, Text.c_str(), FontSize, spacing);
//
//         if (position.x < 0)
//         {
//             position.x = parent.x + parent.width + position.x - textWidth;
//         } else
//         {
//             position.x = parent.x + position.x;
//         }
//
//         if (position.y < 0)
//         {
//             position.y = parent.y - parent.height - position.y + textHeight;
//         } else
//         {
//             position.y = parent.y + position.y;
//         }
//
//         DrawTextEx(Font, Text.c_str(), position, FontSize, spacing, WHITE);
//     }
// };
//
// struct UIPanel
// {
//     UITransform Rect = {100, 100, 100, 100};
//     Color Color = {255, 255, 255, 255};
//
//     std::vector<Interactable> Interactables = {};
//     std::vector<SpriteRenderData> SpritesData = {};
//     std::vector<std::string> Texts = {};
//
//     std::vector<Label> Labels;
//
//     Rectangle Render(const float screenWidth, const float screenHeight) const
//     {
//         const Rectangle rect = Rect.CalculateRect({0, 0, screenWidth, screenHeight});
//         DrawRectangleRec(rect, Color);
//
//         for (const auto& label : Labels)
//         {
//             label.Render(rect);
//         }
//
//         return rect;
//     }
//
//     void AddInteractable(const Rectangle rect, int id)
//     {
//         Interactables.emplace_back(UITransform(rect), Interactable::CONTENT_NONE, id);
//     }
//
//     void AddInteractable(const Rectangle rect, const SpriteRenderData& sprite, const bool isIcon, const int id)
//     {
//         Interactable interactable(UITransform(rect), isIcon ? Interactable::CONTENT_ICON : Interactable::CONTENT_SPRITE,
//                                   id);
//         interactable.DataIndex = SpritesData.size();
//
//         Interactables.push_back(interactable);
//         SpritesData.push_back(sprite);
//     }
// };
//
// #endif //SHEEP_GOES_DEVILE_UI_PANEL_H
