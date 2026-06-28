//
// Created by Kamil on 26.06.2026.
//
#include "SpritesExplorer.h"

#include "raylib.h"
#include "UUIDFactory.hpp"


void SpritesExplorer::Reset()
{
    for (auto& path : Paths)
    {
        UnloadTexture(path.Sprite.Tex);
        path.Sprite.Tex = {};
    }

    Paths = {};
    Directories = {};
    Ids = {};
}

std::string SpritePath::GetFileName() const
{
    return Name + Extension;
}

void SpritesExplorer::Refresh()
{
    Reset();
    const std::filesystem::path path = RESOURCES_PATH "Sprites/";
    const SpriteDirectory Root{path.string(), "Sprites", {}};
    const size_t index = Directories.size();
    Directories.push_back(Root);
    UUIDFactory factory{};
    IterateDirectory(factory, index);
}

void SpritesExplorer::IterateDirectory(UUIDFactory& factory, size_t parentIndex)
{
    for (const auto& entry : std::filesystem::directory_iterator(Directories[parentIndex].Path))
    {
        const auto& entryPath = entry.path();
        auto entryName = entryPath.stem().string();
        if (entry.is_directory())
        {
            SpriteDirectory dir{};
            dir.Path = entryPath.string();
            dir.Name = entryName;
            std::size_t index = Directories.size();
            SpriteDirectory& parent = Directories[parentIndex];
            parent = Directories[parentIndex];
            parent.Children.push_back({index, true});
            Directories.push_back(dir);
            IterateDirectory(factory, index);
            continue;
        }

        std::string pathStr = entryPath.string();
        const Texture2D texture = LoadTexture(pathStr.c_str());
        if (!IsTextureValid(texture))
        {
            UnloadTexture(texture);
            continue;
        }

        SpriteData sprite{};
        UUID uuid = factory.Get();

        if (std::string configPath = pathStr + ".config.json"; std::filesystem::exists(configPath))
        {
            JSON j = ReadJson(configPath.c_str());
            ReadJsonValue(uuid, j, "id", uuid);
            ReadJsonValue(sprite, j, "sprite", sprite);
        }

        SpritePath child{};
        child.Path = entryPath.string();
        child.Name = entryName;
        child.Extension = entryPath.extension().string();
        child.Sprite = sprite;
        child.Sprite.Tex = texture;
        child.Id = uuid;
        child.Parent = parentIndex;
        size_t spriteIndex = Paths.size();
        Directories[parentIndex].Children.push_back({spriteIndex, false});
        Paths.push_back(child);
        Ids[uuid] = spriteIndex;
    }
}

void SpritesExplorer::Save(const size_t index) const
{
    assert(index < Paths.size());
    const SpritePath& file = Paths[index];
    JSON j{};
    j["id"] = file.Id;
    j["sprite"] = file.Sprite;

    SaveJson(j, (file.Path + ".config.json").c_str());
}

const SpriteDirectory& SpritesExplorer::GetRoot() const
{
    return Directories[0];
}

void SpritesExplorer::Move(const UUID id, const size_t index)
{
    SpritePath& sprite = Paths[Ids[id]];
    SpriteDirectory& dir = Directories[index];
    const auto fileName = sprite.GetFileName();
    std::filesystem::copy_file(sprite.Path, dir.Path + "/" + fileName);
    std::filesystem::copy_file(sprite.Path + ".config.json",
                               dir.Path + "/" + fileName + ".config.json");
    std::filesystem::remove(sprite.Path);
    std::filesystem::remove(sprite.Path + ".config.json");

    SpriteDirectory& currentParent = Directories[sprite.Parent];
    for (size_t i = 0; i < currentParent.Children.size(); i++)
    {
        const SpritePathIndex pathIndex = currentParent.Children[i];

        if (pathIndex.IsDirectory)
        {
            continue;
        }

        if (SpritePath& path = Paths[pathIndex.Index]; path.Id == sprite.Id)
        {
            currentParent.Children.erase(currentParent.Children.begin() + i);
            Ids[id] = pathIndex.Index;
            dir.Children.push_back(pathIndex);
            sprite.Path = dir.Path + "/" + fileName;
            sprite.Parent = index;
            break;
        }
    }
}

void SpritesExplorer::Rename(const UUID id, const std::string& newName)
{
    SpritePath& sprite = Paths[Ids[id]];
    sprite.Name = newName;
    const auto directory = Directories[sprite.Parent];
    std::filesystem::rename(sprite.Path, directory.Path + "/" + newName + sprite.Extension);
    std::filesystem::rename(sprite.Path + ".config.json", directory.Path + "/" + newName + sprite.Extension + ".config.json");
    sprite.Path = directory.Path + "/" + newName + sprite.Extension;
}
