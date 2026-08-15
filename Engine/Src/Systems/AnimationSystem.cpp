//
// Created by Kamil on 28.06.2026.
//
#include "AnimationSystem.h"

#include "Components.h"
#include "GameSystemsUpdateArgs.h"

void AnimationSystem::Update(GameSystemsUpdateArgs& args) const
{
    const auto& view = args.Registry.view<AnimatorComponent, RendererComponent>();

    for (const auto& entity : view)
    {
        const auto& tuple = view.get<AnimatorComponent, RendererComponent>(entity);
        auto& [animator, renderer] = tuple;

        animator.Data.Value.TMax = animator.FrameTime.Get();
        animator.Data.Value.SetAnimation(animator.Animation);
        animator.Data.Value.Update(args.DeltaTime,
                             args.Assets.Sprites.FromId(renderer.Data.Sprite).RowCounts[animator.Animation]);
        renderer.Data.TexX = animator.Data.Value.Frame;
        renderer.Data.TexY = animator.Animation;
    }
}
