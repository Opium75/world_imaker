//
// Created by piptouque on 03/01/2020.
//

#include "../include/wim/Selection.hpp"

#include <algorithm>
#include <functional>

namespace wim
{


    static constexpr const FloatType DEFAULT_SELECTION_COLOUR[] = {0.1f, 7.f, 8.f};

    Selected::Selected(SelectablePtr& object, const Colour& colour) :
            Displayable(colour), _objectWeak(object)
    {

    }

    Selection::Selection() : _colour(DEFAULT_SELECTION_COLOUR) {}

    DisplayPattern Selected::getDisplayPattern() const
    {
        return DisplayPattern::WIREFRAME_CUBE;
    }

    SelectablePtr Selected::object() const
    {
        if(auto objectPtr = _objectWeak.lock() )
        {
            return objectPtr;
        }
        else
        {
            throw Exception(ExceptCode::BAD_POINTER, 1, "Quiery to deleted pointer of Selected.");
        }
    }

    const Point3Uint& Selected::position() const
    {
        return this->object()->position();
    }


    void Selection::clearSelected()
    {
        _selected.clear();
    }

    void Selection::clearDeleted()
    {
        SizeInt i=0;
        while( i<_selected.size() )
        {
            if( _selected.at(i)->isDeleted() )
                _selected.erase(_selected.begin() + i);
            else
                ++i;
        }
    }

    bool Selection::isSelected(const SelectablePtr& selectablePtr) const
    {
        return std::any_of(_selected.begin(), _selected.end(),
                    [&selectablePtr](const SelectedPtr& selectedPtr)
                    {
                        return selectedPtr->object() == selectablePtr;
                    }
        );
    }

    void Selection::select(SelectablePtr& selectablePtr)
    {
        //First checking if selectable is not already in the list
        if( !this->isSelected(selectablePtr) )
            this->addToList(selectablePtr);
    }


    void Selection::deselect(SelectablePtr& selectablePtr)
    {
        if( this->isSelected(selectablePtr) )
            this->removeFromList(selectablePtr);
    }

    void Selection::deselect(const SizeInt index)
    {
        this->removeFromList(index);
    }

    void Selection::addToList(SelectablePtr& selectablePtr)
    {
        _selected.push_back(std::make_unique<Selected>(selectablePtr, _colour));
    }

    void Selection::removeFromList(SelectablePtr& selectablePtr)
    {
        _selected.erase(
                std::find_if(_selected.begin(), _selected.end(),
                              [&selectablePtr](const SelectedPtr& selected)
                              {
                                   return selected->object() == selectablePtr;
                              })
        );
    }

    void Selection::removeFromList(const SizeInt index)
    {
        _selected.erase(_selected.begin() + index);
    }


    SelectedPtr& Selection::selected(const SizeInt index)
    {
        if( _selected.at(index)->isDeleted() )
        {
            //remove from list as sefety mesure
            this->removeFromList(index);
        }
        return _selected.at(index);
    }

    const ListSelectedPtr& Selection::selected() const
    {
        return _selected;
    }

    ListSelectedPtr& Selection::selected()
    {
        return _selected;
    }


}