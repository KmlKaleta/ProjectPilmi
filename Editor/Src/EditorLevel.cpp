//
// Created by Kamil on 28.06.2026.
//
#include "EditorLevel.h"
#include "AssetManager.h"
#include "EntitySelection.h"
#include "Systems/GameSystemsUpdateArgs.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include "src/ImGuizmo.h"

void EditorLevel::Init()
{
    Camera.target = {0, 0};
    Camera.rotation = 0;
    Camera.zoom = 1;
}

void TransformEdition(EntityStorage& storage, const EntitySelection& selection, const Camera2D& camera)
{
    const WorldScreenBounds screenBounds{camera};
    if (selection.SelectedEntity == 0)
    {
        return;
    }

    RendererComponent* renderer = storage.Registry.try_get<RendererComponent>(
        storage.GetEntity(selection.SelectedEntity));
    if (renderer == nullptr)
    {
        return;
    }

    auto model = glm::mat4(1.0f);
    const Vector2 position = renderer->Data.Position.GetRelative(screenBounds);
    model = glm::translate(model, glm::vec3(position.x,
                                            position.y,
                                            0.0f));

    model = glm::scale(model, glm::vec3(renderer->Data.LocalScale,
                                        renderer->Data.LocalScale,
                                        1.0f));

    const auto screenWidth = static_cast<float>(GetScreenWidth());
    const auto screenHeight = static_cast<float>(GetScreenHeight());

    auto view = glm::mat4(1.0f);
    auto projection = glm::ortho(
        0.0f, screenWidth,
        screenHeight, 0.0f,
        -1.0f, 1.0f
    );
    projection = glm::translate(projection, glm::vec3(camera.offset.x, camera.offset.y, 0.0f));
    // Step B: Apply rotation (around Z-axis)
    projection = glm::rotate(projection, glm::radians(camera.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    // Step C: Apply camera zoom factor
    projection = glm::scale(projection, glm::vec3(camera.zoom, camera.zoom, 1.0f));
    // Step D: Center the camera back over the world coordinate target
    projection = glm::translate(projection, glm::vec3(-camera.target.x, -camera.target.y, 0.0f));

    ImGuizmo::BeginFrame();

    ImGuizmo::SetOrthographic(true);

    ImGuizmo::SetRect(
        0,
        0,
        screenWidth,
        screenHeight
    );

    ImGuizmo::Manipulate(
        glm::value_ptr(view),
        glm::value_ptr(projection),
        ImGuizmo::TRANSLATE,
        ImGuizmo::WORLD,
        glm::value_ptr(model)
    );

    if (ImGuizmo::IsUsing())
    {
        renderer->Data.Position.SetRelative({model[3][0], model[3][1]}, screenBounds);
    }
}

void EditorLevel::Update(AssetManager& assetManager, const EntitySelection& selection)
{
    ClearBackground(ORANGE);

    Camera.offset = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    BeginMode2D(Camera);

    LevelData& level = assetManager.Levels.CurrentLevel();

    const ImGuiIO& io = ImGui::GetIO();

    GameSystemsUpdateArgs args(assetManager, Camera, !io.WantCaptureMouse, !io.WantCaptureKeyboard);

    Systems.Update(args);

    if (WindowShouldClose())
    {
        return;
    }

    TransformEdition(level.Entities, selection, Camera);
    EndMode2D();
}
