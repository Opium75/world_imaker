//
// Created by piptouque on 03/01/2020.
//

#ifndef WORLD_IMAKER_SELECTION_HPP
#define WORLD_IMAKER_SELECTION_HPP

#pragma once


#include <memory>

#include "Types.hpp"
#include "Colour.hpp"

#include "Displayable.hpp"
#include "Selectable.hpp"


namespace wim
{

    class Selected : public Displayable
    {
    private:
        SelectableWeakPtr _objectWeak;
        FloatType _weight;
    public:
        Selected(SelectablePtr& object, const FloatType weight, const Colour& colour);
        SelectablePtr object() const;

        const Point3Uint& position() const;
        FloatType weight() const;

        bool isDeleted() const {return _objectWeak.expired();}
        DisplayPattern getDisplayPattern() const override;
    private:
        static Colour buildSelectedColour(const FloatType weight, const Colour& base);
    };

    typedef std::unique_ptr<Selected> SelectedPtr;
    typedef std::deque<SelectedPtr> ListSelectedPtr;

    class Selection
    {
    private:
        ListSelectedPtr _selected;
        Colour _colour;
    public:
        Selection();

        SelectedPtr& selected(const SizeInt index);
        ///brief: returns pointer to selection cleared of all deleted selected items.
        ListSelectedPtr& selected();

        SizeInt getNumber() const {return _selected.size();}

        void clearSelected();
        void clearDeleted();


        bool isSelected(const SelectablePtr& selectablePtr) const;

        void select(SelectablePtr& selectablePtr);
        void deselect(const SizeInt index);
        void deselect(SelectablePtr& selectablePtr);


    private:
        void addToList(SelectablePtr& selectablePtr);
        void removeFromList(const SizeInt index);
        void removeFromList(SelectablePtr& selectablePtr);


    };

    typedef std::unique_ptr<Selection> SelectionPtr;
}

#endif //WORLD_IMAKER_SELECTION_HPP
