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

#ifndef QT_EVENTABSTRACTIONRESULT_H
#define QT_EVENTABSTRACTIONRESULT_H
#include <csu/vvl/framework/vvl_genericeventabstractionresult.h>
#include "qt_abstractionresult.h"

namespace csu {
namespace vvl {
namespace gui {
namespace qt {

class Qt_EventAbstractionResult : public csu::vvl::framework::GenericEventAbstractionResult
{
public:
    Qt_EventAbstractionResult(unsigned long event, const Qt_AbstractionResult *);
    const std::string & name();

};

} //qt
} //gui
} //vvl
} //csu
#endif // QT_EVENTABSTRACTIONRESULT_H
