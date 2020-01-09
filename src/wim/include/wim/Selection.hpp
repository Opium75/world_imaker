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

#include "Cube.hpp"

namespace wim
{

    /*Shadowing Selectable class
     * We will simply use Cubes
     * Because we need every attributes of Cubes
     * for procedural generation
     */
    typedef std::shared_ptr<Cube> SelectablePtr;
    typedef std::weak_ptr<Cube> SelectableWeakPtr;

    class Selected : public Displayable
    {
    private:

        SelectableWeakPtr _objectWeak;
        FloatType _weight;
    public:
        Selected(SelectablePtr& object, const FloatType weight, const Colour& colour);
        SelectablePtr object() const;

        const Point3Uint& position() const;
        FloatType getWeight() const;
        void setWeight(const FloatType weight);

        ///brief: returns true if object is deleted
        ///Does not guarantee that the object is usable if it returns false, do NOT use like so : !isDeleted()
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

        void addToWeight(const SizeInt index, const FloatType add);

        void clearSelected();
        void clearDeleted();

        bool isSelected(const SelectablePtr& selectablePtr) const;
        SizeInt getIndexSelected(const SelectablePtr& selectablePtr) const;

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
