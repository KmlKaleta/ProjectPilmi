// //
// // Created by Kamil on 30.05.2026.
// //
//
// #ifndef SHEEP_GOES_DEVILE_UI_ELEMENT_H
// #define SHEEP_GOES_DEVILE_UI_ELEMENT_H
// #include "AssetManager.h"
//
// struct UIElement
// {
//     Rectangle Rect = {};
//     int Anchor = TOP_LEFT;
//     int XUnits = PIXELS;
//     int YUnits = PIXELS;
//     int WidthUnits = PIXELS;
//     int HeightUnits = PIXELS;
//     UIElement* Parent = nullptr;
//     Color Color = {255, 255, 255, 255};
//     float Padding = 10;
//
//     void Render(Rectangle rect) const;
//
//     Rectangle CalculateRect() const;
//
//     enum RectUnits
//     {
//         PIXELS,
//         PERCENTAGE,
//         Aspect
//     };
//
//     enum AnchorType
//     {
//         TOP_LEFT,
//         TOP_CENTER,
//         TOP_RIGHT,
//         CENTER_LEFT,
//         CENTER,
//         CENTER_RIGHT,
//         BOTTOM_LEFT,
//         BOTTOM_CENTER,
//         BOTTOM_RIGHT,
//     };
// };
//
// struct UIIterator
// {
//     explicit UIIterator(std::vector<std::unique_ptr<UIElement>>& data) : _data(data)
//     {
//     }
//
//     UIElement* Current() const;
//
//     size_t CurrentIndex() const;
//
//     void Reset();
//
//     bool MoveNext();
//
// private:
//     size_t _current = 0;
//     std::vector<std::unique_ptr<UIElement>>& _data;
// };
//
// struct UIPanel
// {
//     UIIterator GetIterator();
//
//     UIElement* AddElement(const UIElement& element);
//
//     UIElement* GetElement(size_t i) const;
//
// private:
//     std::vector<std::unique_ptr<UIElement>> Elements;
// };
//
// struct SpriteRenderData
// {
//     uint64_t SpriteId = 0;
//     float Scale = 1;
//     int TexX = 0;
//     int TexY = 0;
//     Color Tint = WHITE;
//     bool IsIcon = false;
// };
//
// struct SpriteButton
// {
//     Color TargetColor = {};
//
//     Color DefaultColor = {240, 240, 240, 255};
//     Color HoverColor = {150, 150, 150, 255};
//     Color ClickColor = {110, 110, 110, 255};
//
//     SpriteRenderData Data;
//     UIElement* Element = nullptr;
//
//     static SpriteButton AddToPanel(const UIElement& element, const SpriteRenderData& renderData, UIPanel& panel);
//
//     void Update(UIElement* element, float deltaTime) const;
//
//     void Render(const UIElement* element, Rectangle rect, const AssetManager& assetManager) const;
//
//     bool Process(Vector2 mousePosition, bool isPressed, bool isReleased, float deltaTime, const UIIterator& iterator,
//                  const AssetManager& assetManager);
//
// private:
//     void RenderTexture(const SpriteData& spriteData, Rectangle rect, const SpriteRenderData& renderData,
//                        const UIElement* element) const;
// };
//
// struct SpriteSelector
// {
//     int SelectedIndex = -1;
//     int ElementsInRow = 3;
//
//     Color DefaultColor = {240, 240, 240, 255};
//     Color HoverColor = {150, 150, 150, 255};
//     Color ClickColor = {110, 110, 110, 255};
//
//     Color SelectedDefaultColor = {170, 220, 170, 255};
//     Color SelectedHoverColor = {150, 210, 150, 255};
//     Color SelectedClickColor = {120, 195, 120, 255};
//
//     UIElement* Element = nullptr;
//
//     std::vector<SpriteButton> Buttons;
//     UIPanel ButtonsPanel;
//
//     static SpriteSelector AddToPanel(UIElement& element, int elementsInRow, const SpriteManager& sprites,
//                                      UIPanel& panel);
//
//     bool Process(Vector2 mousePosition, bool isPressed, bool isReleased, float deltaTime, const UIIterator& iterator,
//                  const AssetManager& assetManager);
//
//     void SetTextureX(int x, const SpriteManager& sprites);
//
//     void SetTextureY(int y, const SpriteManager& sprites);
// };
//
// struct Label
// {
//     std::string Text = {};
//     Font Font = GetFontDefault();
//     float FontSize = 20;
//     Color Color = {255, 255, 255, 255};
//     int Anchor = UIElement::CENTER;
//
//     void Render(Rectangle rect) const;
//
//     UIElement* Element = nullptr;
//
//     bool Process(const UIIterator& iterator) const;
//
//     static Label AddToPanel(const UIElement& element, const char* label, UIPanel& panel);
// };
//
// struct IntSelector
// {
//     UIElement* Element = nullptr;
//
//     UIPanel Panel;
//
//     Label Name;
//     Label Number;
//     SpriteButton Decrement;
//     SpriteButton Increment;
//
//
//     static IntSelector AddToPanel(UIElement& element, const char* label, UIPanel& panel);
//
//     bool Process(int& value, Vector2 mousePosition, bool isPressed, bool isReleased, float deltaTime,
//                  const UIIterator& iterator, const AssetManager& assetManager);
// };
//
//
// #endif //SHEEP_GOES_DEVILE_UI_ELEMENT_H
