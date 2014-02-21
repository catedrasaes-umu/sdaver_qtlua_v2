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
 *   This file is part of the OHTu-Open Usability Evaluation Framework,
 *   http://sourceforge.net/projects/ohtu/
 */

#include "sw_movslidemessage.h"
#include "sw_slidemessage.h"

//FIXME UNDER DEVELOPMENT
namespace csu {
namespace qt {
namespace widgets {
namespace shadow_frame {

MOVSlideMessage::MOVSlideMessage(const QStringList * message,ShadowFrame* parent,QWidget *decorated )
: MouseOverShadowVanish(parent,decorated)
{
    SlideMessage *aux = new SlideMessage(message,parent,decorated);

    addMouseOverWidget(aux);

}

bool MOVSlideMessage::eventFilter(QObject *obj, QEvent *e)
{
    MouseOverShadowVanish::eventFilter(obj,e);

    return false;
}

} //shadow_frame
} //widgets
} //qt
} //csu
