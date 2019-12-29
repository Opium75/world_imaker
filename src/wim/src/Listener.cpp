//
// Created by piptouque on 26/12/2019.
//

#include "../include/wim/Listener.hpp"

#include <algorithm>

namespace wim {

    void Listener::subscribe(Listenable *listenable)
    {
        listenable->addListener(this);
    }

    void Listener::unsubscribe(Listenable *listenable) const
    {
        listenable->removeListener(this);
    }

    void Listenable::addListener(Listener *listener)
    {
        _listeners.push_back(listener);
        //we notify the listener
        this->notify(listener);
    }

    void Listenable::removeListener(const Listener *listener)
    {
        auto found = std::find(_listeners.begin(), _listeners.end(), listener);
        if( found == _listeners.end() )
        {
            //listerner is not in list
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Element not currently subscribed." );
        }
        _listeners.erase(found);
    }

    void Listenable::notify() const
    {
        std::for_each(_listeners.begin(),
                _listeners.end(),
                [this](Listener* listener)
                      {
                        this->notify(listener);
                      }
        );
    }

    void Listenable::notify(Listener* listener) const
    {
        listener->update();
    }
}