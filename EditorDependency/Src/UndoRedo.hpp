//
// Created by Kamil on 05.07.2026.
//

#ifndef SHEEP_GOES_DEVILE_UNDO_REDO_HPP
#define SHEEP_GOES_DEVILE_UNDO_REDO_HPP
#include <any>
#include <stack>
#include <utility>

struct UndoRedoAction
{
    std::any Data;

    explicit UndoRedoAction(std::any data) : Data(std::move(data))
    {
    }
};

struct UndoRedoData
{
    std::deque<UndoRedoAction> UndoStack;
    std::deque<UndoRedoAction> RedoStack;

    template<typename U>
    void AddAction(const U& data)
    {
        UndoStack.emplace_back(std::make_any<U>(data));
        RedoStack.clear();
        if (UndoStack.size() > 100)
        {
            UndoStack.pop_front();
        }
    }

    void AddAction(UndoRedoAction&& action)
    {
        UndoStack.emplace_back(std::move(action));
        RedoStack.clear();
        if (UndoStack.size() > 100)
        {
            UndoStack.pop_front();
        }
    }

    bool CanUndo() const
    {
        return !UndoStack.empty();
    }

    bool CanRedo() const
    {
        return !RedoStack.empty();
    }

    void Undo()
    {
        RedoStack.push_back(UndoStack.back());
        UndoStack.pop_back();
    }

    void Redo()
    {
        UndoStack.push_back(RedoStack.back());
        RedoStack.pop_back();
    }

    std::any& UndoData()
    {
        return UndoStack.back().Data;
    }

    std::any& RedoData()
    {
        return RedoStack.back().Data;
    }
};

template<typename TResolver, typename TArgs>
struct UndoRedo
{
    UndoRedoData Data;
    TResolver Resolver;

    bool CanUndo() const
    {
        return Data.CanUndo();
    }

    bool CanRedo() const
    {
        return Data.CanRedo();
    }

    void Undo(TArgs& args)
    {
        Resolver.Undo(Data.UndoData(), args);
        Data.Undo();
    }

    void Redo(TArgs& args)
    {
        Resolver.Redo(Data.RedoData(), args);
        Data.Redo();
    }

    template<typename U>
    void AddAction(const U& data)
    {
        Data.AddAction(data);
    }

    void AddAction(UndoRedoAction&& action)
    {
        Data.AddAction(std::move(action));
    }
};

#endif //SHEEP_GOES_DEVILE_UNDO_REDO_HPP
