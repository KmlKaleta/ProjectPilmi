// //
// // Created by Kamil on 30.05.2026.
// //
//
// #include "UIElement.h"
//
// void UIElement::Render(const Rectangle rect) const
// {
//     DrawRectangleRec(rect, Color);
// }
//
// Rectangle UIElement::CalculateRect() const
// {
//     const auto [parentX, parentY, parentWidth, parentHeight] = Parent == nullptr
//                                                                    ? Rectangle{
//                                                                        0, 0, static_cast<float>(GetScreenWidth()),
//                                                                        static_cast<float>(GetScreenHeight())
//                                                                    }
//                                                                    : Parent->CalculateRect();
//
//     auto [x, y, width, height] = Rect;
//
//     if (XUnits == PERCENTAGE)
//     {
//         x = parentWidth * x / 100;
//     }
//
//     if (YUnits == PERCENTAGE)
//     {
//         y = parentHeight * y / 100;
//     }
//
//     if (WidthUnits == PERCENTAGE)
//     {
//         width = parentWidth * width / 100;
//     }
//
//     if (HeightUnits == PERCENTAGE)
//     {
//         height = parentWidth * height / 100;
//     }
//
//     if (WidthUnits == Aspect)
//     {
//         width = height;
//     }
//
//     if (HeightUnits == Aspect)
//     {
//         height = width;
//     }
//
//
//     width -= Padding;
//     height -= Padding;
//
//     const float halfPadding = Padding / 2.f;
//
//     switch (Anchor)
//     {
//         case TOP_LEFT:
//             x += parentX + halfPadding;
//             y += parentY + halfPadding;
//             break;
//         case TOP_CENTER:
//             x += parentX + parentWidth / 2.f - width / 2.f + halfPadding;
//             y += parentY + halfPadding;
//             break;
//         case TOP_RIGHT:
//             x += parentX + parentWidth - width - halfPadding;
//             y += parentY + halfPadding;
//             break;
//         case CENTER_LEFT:
//             x += parentX + halfPadding;
//             y += parentY + parentHeight / 2.f - height / 2.f + halfPadding;
//             break;
//         case CENTER:
//             x += parentX + parentWidth / 2.f - width / 2.f + halfPadding;
//             y += parentY + parentHeight / 2.f - height / 2.f + halfPadding;
//             break;
//         case CENTER_RIGHT:
//             x += parentX + parentWidth - width - halfPadding;
//             y += parentY + parentHeight / 2.f - height / 2.f + halfPadding;
//             break;
//         case BOTTOM_LEFT:
//             x += parentX + halfPadding;
//             y += parentY + parentHeight - height - halfPadding;
//             break;
//         case BOTTOM_CENTER:
//             x += parentX + parentWidth / 2.f - width / 2.f + halfPadding;
//             y += parentY + parentHeight - height - halfPadding;
//             break;
//         case BOTTOM_RIGHT:
//             x += parentX + parentWidth - width - halfPadding;
//             y += parentY + parentHeight - height - halfPadding;
//             break;
//         default:
//             break;
//     }
//
//     return {x, y, width, height};
// }
//
// bool UIIterator::MoveNext()
// {
//     _current++;
//     return _current <= _data.size();
// }
//
// UIElement* UIIterator::Current() const
// {
//     return _data[_current - 1].get();
// }
//
// void UIIterator::Reset()
// {
//     _current = 0;
// }
//
// UIIterator UIPanel::GetIterator()
// {
//     return UIIterator(Elements);
// }
//
// UIElement* UIPanel::AddElement(const UIElement& element)
// {
//     const size_t index = Elements.size();
//     Elements.push_back(std::make_unique<UIElement>(element));
//     return Elements[index].get();
// }
//
// UIElement* UIPanel::GetElement(const size_t i) const
// {
//     assert(i < Elements.size());
//     return Elements[i].get();
// }
//
// void SpriteButton::RenderTexture(const SpriteData& spriteData, const Rectangle rect,
//                                  const SpriteRenderData& renderData, const UIElement* element) const
// {
//     float widthRatio = 1;
//     float heightRatio = 1;
//
//     const float spriteWidth = static_cast<float>(spriteData.Tex.width) / static_cast<float>(spriteData.RowCountMax);
//     const float spriteHeight = static_cast<float>(spriteData.Tex.height) / static_cast<float>(spriteData.RowCounts.
//                                    size());
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
//                    0, ColorTint(element->Color, renderData.Tint));
// }
//
// SpriteSelector SpriteSelector::AddToPanel(UIElement& element, int elementsInRow, const SpriteManager& sprites,
//                                           UIPanel& panel)
// {
//     SpriteSelector selector;
//     selector.Element = panel.AddElement(element);
//     selector.ElementsInRow = elementsInRow;
//
//     for (const auto& [first, _] : sprites.Ids)
//     {
//         UIElement btnElement;
//         btnElement.Parent = selector.Element;
//
//         SpriteButton btn = SpriteButton::AddToPanel(btnElement, {first}, selector.ButtonsPanel);
//         selector.Buttons.push_back(btn);
//     }
//
//     return selector;
// }
//
// bool SpriteSelector::Process(const Vector2 mousePosition, const bool isPressed, const bool isReleased,
//                              const float deltaTime,
//                              const UIIterator& iterator, const AssetManager& assetManager)
// {
//     const UIElement* size = iterator.Current();
//     if (size != Element)
//     {
//         return false;
//     }
//
//     UIIterator it = ButtonsPanel.GetIterator();
//     int x = 0;
//     int y = 0;
//     const float width = size->CalculateRect().width / static_cast<float>(ElementsInRow);
//
//     while (it.MoveNext())
//     {
//         it.Current()->Rect = {static_cast<float>(x) * width, static_cast<float>(y) * width, width, width};
//
//         x++;
//         if (x >= ElementsInRow)
//         {
//             x = 0;
//             y++;
//         }
//
//         for (int i = 0; i < Buttons.size(); i++)
//         {
//             SpriteButton& btn = Buttons[i];
//             if (!btn.Process(mousePosition, isPressed, isReleased, deltaTime, it, assetManager))
//             {
//                 continue;
//             }
//
//             if (SelectedIndex >= 0)
//             {
//                 SpriteButton& lastButton = Buttons[SelectedIndex];
//                 lastButton.DefaultColor = DefaultColor;
//                 lastButton.HoverColor = HoverColor;
//                 lastButton.ClickColor = ClickColor;
//             }
//
//             if (SelectedIndex == i)
//             {
//                 SelectedIndex = -1;
//                 break;
//             }
//
//             btn.DefaultColor = SelectedDefaultColor;
//             btn.HoverColor = SelectedHoverColor;
//             btn.ClickColor = SelectedClickColor;
//             SelectedIndex = i;
//             break;
//         }
//     }
//
//     return true;
// }
//
// void SpriteSelector::SetTextureX(const int x, const SpriteManager& sprites)
// {
//     for (auto& btn : Buttons)
//     {
//         btn.Data.TexX = std::abs(x) % sprites.FromId(btn.Data.SpriteId).RowCountMax;
//     }
// }
//
// void SpriteSelector::SetTextureY(const int y, const SpriteManager& sprites)
// {
//     for (auto& btn : Buttons)
//     {
//         btn.Data.TexY = std::abs(y) % static_cast<int>(sprites.FromId(btn.Data.SpriteId).RowCounts.size());
//     }
// }
//
// void Label::Render(const Rectangle rect) const
// {
//     const float spacing = std::max(FontSize, 10.f) / 10;
//     const auto [textWidth, textHeight] = MeasureTextEx(Font, Text.c_str(), FontSize, spacing);
//
//     const auto [x, y, width, height] = rect;
//
//     Vector2 position = {rect.x, rect.y};
//
//     switch (Anchor)
//     {
//         case UIElement::TOP_CENTER:
//             position.x += width / 2.f - textWidth / 2.f;
//             break;
//         case UIElement::TOP_RIGHT:
//             position.x += width - textWidth;
//             break;
//         case UIElement::CENTER_LEFT:
//             position.y += height / 2.f - textHeight / 2.f;
//             break;
//         case UIElement::CENTER:
//             position.x += width / 2.f - textWidth / 2.f;
//             position.y += height / 2.f - textHeight / 2.f;
//             break;
//         case UIElement::CENTER_RIGHT:
//             position.x += width - textWidth;
//             position.y += height / 2.f - textHeight / 2.f;
//             break;
//         case UIElement::BOTTOM_LEFT:
//             position.y += height - textHeight;
//             break;
//         case UIElement::BOTTOM_CENTER:
//             position.x += width / 2.f - textWidth / 2.f;
//             position.y += height - textHeight;
//             break;
//         case UIElement::BOTTOM_RIGHT:
//             position.x += width - textWidth;
//             position.y += height - textHeight;
//             break;
//         default:
//             break;
//     }
//
//     DrawTextEx(Font, Text.c_str(), position, FontSize, spacing, Color);
// }
//
// bool Label::Process(const UIIterator& iterator) const
// {
//     const UIElement* element = iterator.Current();
//     if (element != Element)
//     {
//         return false;
//     }
//
//     Render(element->CalculateRect());
//     return true;
// }
//
// Label Label::AddToPanel(const UIElement& element, const char* label, UIPanel& panel)
// {
//     Label labelElement;
//     labelElement.Element = panel.AddElement(element);
//     labelElement.Text = label;
//     return labelElement;
// }
//
// IntSelector IntSelector::AddToPanel(UIElement& element, const char* label, UIPanel& panel)
// {
//     IntSelector selector;
//     selector.Element = panel.AddElement(element);
//
//     UIElement nameElement;
//     nameElement.Parent = selector.Element;
//     nameElement.Rect = {0, 0, 20, 20};
//     nameElement.WidthUnits = UIElement::PERCENTAGE;
//     selector.Name = Label::AddToPanel(nameElement, label, selector.Panel);
//     selector.Name.Text = label;
//     selector.Name.Anchor = UIElement::TOP_LEFT;
//
//     const uint64_t arrowsId = StringToHash("Arrows");
//
//     UIElement decrementElement;
//     decrementElement.Parent = selector.Element;
//     decrementElement.Rect = {60, 0, 20, 20};
//     decrementElement.XUnits = UIElement::PERCENTAGE;
//     decrementElement.Anchor = UIElement::CENTER_LEFT;
//     selector.Decrement = SpriteButton::AddToPanel(decrementElement, {arrowsId, 1, 1, 0, GRAY, true}, selector.Panel);
//
//     UIElement incrementElement;
//     incrementElement.Parent = selector.Element;
//     incrementElement.Rect = {90, 0, 20, 20};
//     incrementElement.XUnits = UIElement::PERCENTAGE;
//     incrementElement.Anchor = UIElement::CENTER_LEFT;
//     selector.Increment = SpriteButton::AddToPanel(incrementElement, {arrowsId, 1, 2, 0, GRAY, true}, selector.Panel);
//
//     UIElement valueElement;
//     valueElement.Parent = selector.Element;
//     valueElement.Rect = {70, 0, 20, 20};
//     valueElement.XUnits = UIElement::PERCENTAGE;
//     valueElement.WidthUnits = UIElement::PERCENTAGE;
//     selector.Number = Label::AddToPanel(valueElement, label, selector.Panel);
//     selector.Number.Text = "0";
//     selector.Number.Anchor = UIElement::TOP_CENTER;
//
//     return selector;
// }
//
// bool IntSelector::Process(int& value, const Vector2 mousePosition, const bool isPressed, const bool isReleased,
//                           const float deltaTime,
//                           const UIIterator& iterator, const AssetManager& assetManager)
// {
//     if (const UIElement* element = iterator.Current(); element != Element)
//     {
//         return false;
//     }
//
//     UIIterator it = Panel.GetIterator();
//     while (it.MoveNext())
//     {
//         if (Name.Process(it))
//         {
//             continue;
//         }
//
//         if (Number.Process(it))
//         {
//             continue;
//         }
//
//         if (Decrement.Process(mousePosition, isPressed, isReleased, deltaTime, it, assetManager))
//         {
//             Number.Text = std::to_string(--value);
//             continue;
//         }
//
//         if (Increment.Process(mousePosition, isPressed, isReleased, deltaTime, it, assetManager))
//         {
//             Number.Text = std::to_string(++value);
//         }
//     }
//
//     return true;
// }
//
// SpriteButton SpriteButton::AddToPanel(const UIElement& element, const SpriteRenderData& renderData, UIPanel& panel)
// {
//     SpriteButton button;
//     button.Element = panel.AddElement(element);
//     button.Data = renderData;
//     return button;
// }
//
// void SpriteButton::Update(UIElement* element, const float deltaTime) const
// {
//     element->Color = ColorLerp(element->Color, TargetColor, deltaTime * 15);
// }
//
// void SpriteButton::Render(const UIElement* element, const Rectangle rect, const AssetManager& assetManager) const
// {
//     element->Render(rect);
//     const SpriteData sprite = Data.IsIcon
//                                   ? assetManager.Icons.FromId(Data.SpriteId)
//                                   : assetManager.Sprites.FromId(Data.SpriteId);
//     RenderTexture(sprite, rect, Data, element);
// }
//
// bool SpriteButton::Process(const Vector2 mousePosition, const bool isPressed, const bool isReleased,
//                            const float deltaTime,
//                            const UIIterator& iterator, const AssetManager& assetManager)
// {
//     UIElement* element = iterator.Current();
//     if (element != Element)
//     {
//         return false;
//     }
//
//     const Rectangle rect = element->CalculateRect();
//     if (!CheckCollisionPointRec(mousePosition, rect))
//     {
//         TargetColor = DefaultColor;
//         Update(element, deltaTime);
//         Render(element, rect, assetManager);
//         return false;
//     }
//
//     TargetColor = isPressed ? ClickColor : HoverColor;
//
//     Update(element, deltaTime);
//     Render(element, rect, assetManager);
//     return isReleased;
// }
