//
// Created by piptouque on 03/01/2020.
//

#include "../include/wim/Selection.hpp"

#include <algorithm>
#include <cmath>

namespace wim
{


    static constexpr FloatType DEFAULT_SELECTION_COLOUR[] = {0.9f, 0.9f, 0.1f};

    Selected::Selected(SelectablePtr& object, const FloatType weight, const Colour& colour) :
            Displayable(Selected::buildSelectedColour(weight,colour)), _objectWeak(object), _weight(weight)
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

    FloatType Selected::getWeight() const
    {
        return _weight;
    }


    void Selected::setWeight(const FloatType weight)
    {
        _weight = weight;
        //changing colour of the selection
        _material.colour() = buildSelectedColour(weight, Colour(DEFAULT_SELECTION_COLOUR));
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

    SizeInt Selection::getIndexSelected(const SelectablePtr& selectablePtr) const
    {
        SizeInt index = 0;
        bool found=false;
        for( const auto& selected : _selected )
        {
            if( selected->object() == selectablePtr )
            {
                found = true;
                break;
            }
            ++index;
        }
        if( !found )
        {
            throw Exception(ExceptCode::ILLIGAL, 1, "Object is not selected, cannot get index in selection.");
        }
        return index;
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


    void Selection::addToWeight(const SizeInt index, const FloatType add)
    {
        SelectedPtr& selected = this->selected(index);
        selected->setWeight(selected->getWeight()+add);
    }

    void Selection::addToList(SelectablePtr& selectablePtr)
    {
        FloatType weight = RandomScalar<FloatType>(-1,1);
        _selected.push_back(
                std::make_unique<Selected>(
                        selectablePtr,
                        weight,
                         _colour)
        );
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


    ListSelectedPtr& Selection::selected()
    {
        this->clearDeleted();
        return _selected;
    }


    Colour Selected::buildSelectedColour(const FloatType weight, const Colour& base)
    {
        Colour c;
        FloatType rate = std::atan(weight)/(std::sqrt(2)*2)+0.5;
        c.r() = (1 - rate)*base.r();
        c.g() = rate*base.g();
        c.b() = base.b();
        return c;
    }
}