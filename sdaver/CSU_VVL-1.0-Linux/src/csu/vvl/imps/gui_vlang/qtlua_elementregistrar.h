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

#ifndef QTLUA_ELEMENTREGISTRAR_H
#define QTLUA_ELEMENTREGISTRAR_H

#include <csu/vvl/framework/vvl_genericelementregistrar.h>
#include <csu/vvl/imps/gui_vlang/qtlua_adapters.h>
#include <boost/any.hpp>

#include <map>
//#include <QApplication>

namespace csu {
namespace vvl {
namespace gui_vlang {
namespace qt_lua {

using namespace csu::vvl::framework;

class QtLua_ElementRegistrar : public GenericElementRegistrar
{
public:
    ///
    /// Constructor
    /// @param context is the verification context
    ///

    QtLua_ElementRegistrar(VerificationContextPtr context);
    virtual ~QtLua_ElementRegistrar();

    virtual boost::any registerGUIElements(boost::any& object);
    virtual boost::any updateGUIElementRegister();
private:
    lua_State * L_;  
};

} //qt_lua
} //gui_vlang
} //vvl
} //csu

#endif // QTLUA_ELEMENTREGISTRAR_H
