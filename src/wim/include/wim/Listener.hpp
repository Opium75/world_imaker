//
// Created by piptouque on 26/12/2019.
//

#ifndef WORLD_IMAKER_LISTENER_HPP
#define WORLD_IMAKER_LISTENER_HPP

#pragma once

#include <deque>
#include <algorithm>

#include "Exception.hpp"

namespace wim
{
    class Listenable;

    class Listener
    {
        friend class Listenable;
    protected:
        void subscribe(Listenable* listenable);
        void unsubscribe(Listenable* listenable) const;

        virtual void update() = 0;
    };

    typedef std::deque<Listener*> ListListenerPtr;

    class Listenable
    {
    private:
        ListListenerPtr _listeners;
    public:
        void addListener(Listener* listener) ;
        void removeListener(const Listener* listener) ;
    protected:
        Listenable() = default;
        void notify() const;
    private:
        void notify(Listener* listener) const;
    };
}
#endif //WORLD_IMAKER_LISTENER_HPP
