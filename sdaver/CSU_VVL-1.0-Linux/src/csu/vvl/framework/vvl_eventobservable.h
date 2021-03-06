// -*- mode: c++; c-basic-offset: 4; c-basic-style: bsd; -*-
/*
*   This program is free software; you can redistribute it and/or
*   modify
*   it under the terms of the GNU Lesser General Public License as
*   published by the Free Software Foundation; either version 3.0 of
*   the License, or (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public
*   License along with this library; if not, write to the Free Software
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
*   02111-1307 USA
*
*   This file is part of the Aspect-Oriented GUI Verification Library,
*   http://sourceforge.net/projects/guiverification/
*
*/

#ifndef VVL_EVENTOBSERVABLE_H
#define VVL_EVENTOBSERVABLE_H

//log
//#include <csu/vvl/config/log_config_internal.h>

#include <boost/shared_ptr.hpp>
//#include <list>
#include <boost/ptr_container/ptr_list.hpp>

#include "vvl_eventobserver.h"
#include <QEvent>

namespace csu {
namespace vvl {
namespace framework {


class EventObservable
{
public:
    void registerObserver(EventObserver * o)
    {
        eventObList_.push_back(o);
    }

    void notifyAll(const std::string & windowName)
    {        
        for (EventObserverList::iterator it = eventObList_.begin();it!=eventObList_.end();it++)
        {
            (it)->updateElements(windowName);
        }
    }

    void notifyCreate(const std::string & windowName)
    {
        for (EventObserverList::iterator it = eventObList_.begin();it!=eventObList_.end();it++)
        {
            (it)->updateCreateElements(windowName);
        }
    }

    void notifyDelete(const std::string & windowName)
    {
        for (EventObserverList::iterator it = eventObList_.begin();it!=eventObList_.end();it++)
        {
            (it)->updateDeleteElements(windowName);
        }
    }

private:

    typedef boost::ptr_list<EventObserver> EventObserverList;
    EventObserverList eventObList_;
};

} //framework
} //validation
} //csu


#endif // VVL_EVENTOBSERVABLE_H
