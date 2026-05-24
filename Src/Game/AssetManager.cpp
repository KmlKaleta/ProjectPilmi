#include "AssetManager.h"

void AssetManager::LoadAll()
{
    Atlas = LoadTexture(RESOURCES_PATH "textures.png");
    SetTextureFilter(Atlas, TEXTURE_FILTER_POINT);

    Frame = LoadTexture(RESOURCES_PATH "frame.png");

    Sprites[SPRITE_GRASS].Load(RESOURCES_PATH "trawa.png", 0.5, {500, 35});
    Sprites[SPRITE_TREE1].Load(RESOURCES_PATH "drzewo 1.png", 0.2, {77, 190});
    Sprites[SPRITE_TREE2].Load(RESOURCES_PATH "drzewo 2.png", 0.2, {85, 194});
    Sprites[SPRITE_CLOUD_BACKGROUND].Load(RESOURCES_PATH "tlo.png", 1, {1220, 720});

    Atlases[ATLAS_FLOWER].Load(RESOURCES_PATH "kwiatki.png", 0.6, {21.6, 49}, 3, 1);

    Animations[ANIMATION_BEESHOP].Load(RESOURCES_PATH "BISCUP MAGIC.png", 0.150, {35, 111}, 4, 2, {4, 1});
    Animations[ANIMATION_NUN].Load(RESOURCES_PATH "NUN WALK.png", 0.150, {37, 107}, 4, 2, {4, 1});
    Animations[ANIMATION_BUNERO].Load(RESOURCES_PATH "bunero.png", 0.350, {28, 104}, 4, 1, {4});
}