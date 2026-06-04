// //
// // Created by Kamil on 27.05.2026.
// //
//
// #include "AssetManager.h"
// #include "UIPanel.h"
//
// Interactable::Interactable(const UITransform rect, const int contentType, const int interactionType)
// {
//     CurrentColor = DefaultColor;
//     TargetColor = DefaultColor;
//
//     Rect = rect;
//     ContentType = contentType;
//     InteractionType = interactionType;
// }
//
// void Interactable::Update(const float deltaTime)
// {
//     CurrentColor = ColorLerp(CurrentColor, TargetColor, deltaTime * 15);
// }
//
// void Interactable::Render(const AssetManager& assetManager, const UIPanel& panel, const Rectangle rect) const
// {
//     DrawRectangleRec(rect, CurrentColor);
//     switch (ContentType)
//     {
//         case CONTENT_SPRITE:
//             RenderSprite(assetManager.Sprites, panel, rect);
//             break;
//         case CONTENT_ICON:
//             RenderIcon(assetManager.Icons, panel, rect);
//             break;
//         default:
//             break;
//     }
// }
//
// void Interactable::RenderSprite(const SpriteManager& spritesManager, const UIPanel& panel, const Rectangle rect) const
// {
//     const SpriteRenderData data = panel.SpritesData[DataIndex];
//     const SpriteData spriteData = spritesManager.FromId(data.SpriteId);
//     RenderTexture(spriteData, rect, data);
// }
//
// void Interactable::RenderIcon(const IconsManager& iconsManager, const UIPanel& panel, Rectangle rect) const
// {
//     const SpriteRenderData data = panel.SpritesData[DataIndex];
//     const SpriteData iconData = iconsManager.FromId(data.SpriteId);
//     RenderTexture(iconData, rect, data);
// }
//
// void Interactable::RenderTexture(const SpriteData& spriteData, const Rectangle rect,
//                                  const SpriteRenderData& renderData) const
// {
//     float widthRatio = 1;
//     float heightRatio = 1;
//
//     const float spriteWidth = static_cast<float>(spriteData.Tex.width) / static_cast<float>(spriteData.RowCountMax);
//     const float spriteHeight = static_cast<float>(spriteData.Tex.height) / static_cast<float>(spriteData.RowCounts.size());
//
//     if (spriteHeight > spriteWidth)
//     {
//         widthRatio = spriteWidth / spriteHeight;
//     } else
//     {
//         heightRatio = spriteHeight / spriteWidth;
//     }
//
//     constexpr float scale = 0.9f;
//
//
//     DrawTexturePro(spriteData.Tex, {
//                        static_cast<float>(renderData.TexX) * spriteWidth,
//                        static_cast<float>(renderData.TexY) * spriteHeight, spriteWidth, spriteHeight
//                    },
//                    {
//                        rect.x, rect.y,
//                        rect.width * widthRatio * scale, rect.height * heightRatio * scale
//                    }, {-rect.width * (1 - widthRatio * scale) / 2, -rect.height * (1 - heightRatio * scale) / 2},
//                    0, ColorTint(CurrentColor, renderData.Tint));
// }
//
// bool Interactable::Process(const float deltaTime, const Vector2 mousePosition, const AssetManager& assetManager,
//                            const UIPanel& panel, const Rectangle parent)
// {
//     const Rectangle rect = Rect.CalculateRect(parent);
//     if (!CheckCollisionPointRec(mousePosition, rect))
//     {
//         TargetColor = DefaultColor;
//         Update(deltaTime);
//         Render(assetManager, panel, rect);
//         return false;
//     }
//
//     TargetColor = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? ClickColor : HoverColor;
//
//     Update(deltaTime);
//     Render(assetManager, panel, rect);
//     return IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
// }
