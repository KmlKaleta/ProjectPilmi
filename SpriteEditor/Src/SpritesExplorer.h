//
// Created by Kamil on 24.06.2026.
//

#ifndef SHEEP_GOES_DEVILE_SPRITES_EXPLORER_H
#define SHEEP_GOES_DEVILE_SPRITES_EXPLORER_H
#include <string>
#include <vector>
#include <filesystem>
#include "SpriteData.h"
#include "UUID.hpp"

struct UUIDFactory;

struct SpritePathIndex
{
    size_t Index;
    bool IsDirectory;
};

struct SpriteDirectory
{
    std::string Path;
    std::string Name;
    std::vector<SpritePathIndex> Children;
};

struct SpritePath
{
    UUID Id;
    std::string Path;
    std::string Name;
    std::string Extension;
    SpriteData Sprite;
    size_t Parent;

    std::string GetFileName() const;
};

struct SpritesExplorer
{
    std::vector<SpritePath> Paths;
    std::vector<SpriteDirectory> Directories;

    std::unordered_map<UUID, size_t> Ids;

    UUID Selected{};
    bool AnySelected = false;

    void Refresh();

    void Save(size_t index) const;

    const SpriteDirectory& GetRoot() const;

    void Move(UUID id, size_t index);

    void Rename(UUID id, const std::string& newName);
private:
    void IterateDirectory(UUIDFactory& factory, size_t parentIndex);

    void Reset();
};

#endif //SHEEP_GOES_DEVILE_SPRITES_EXPLORER_H
