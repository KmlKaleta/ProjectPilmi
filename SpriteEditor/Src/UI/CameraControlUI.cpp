//
// Created by Kamil on 27.06.2026.
//
#include "CameraControlUI.h"

#include "imgui.h"
#include "../SpriteEditorScene.h"

void CameraControlUI::Draw(SpriteEditorScene& scene) const
{
    ImGui::Begin("Camera Control");

    ImGui::DragFloat("Zoom", &scene.Camera.zoom, 0.005f, 0.001f, 100.0f);
    ImGui::DragFloat2("Position", &scene.Camera.target.x);
    if (ImGui::Button("Reset"))
    {
        scene.Camera.zoom = 1.0f;
        scene.Camera.target = {0.0f, 0.0f};
    }

    ImGui::End();
}
