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
*   http://sourceforge.net/projects/ohtplus/
*
*/

#ifndef ABSTRACT_UI_GENERATOR_H
#define ABSTRACT_UI_GENERATOR_H

//#include <csu/base/ui/abstract_ui_datamodel/abs_ui_datamodel.h>

namespace csu{
namespace base{
namespace ui{
namespace abstract_ui_generator{

    using namespace csu::base::ui::abstract_ui_datamodel;

    class AbstractUiGenerator
    {
    public:

        /// /////////////////////////////////
        /// constructor
        /// /////////////////////////////////
        //virtual ~AbstractUiGenerator(){}

    public:
        /// /////////////////////////////////
        /// abstract ui generation method
        /// /////////////////////////////////
        virtual void generateAbstractUI() = 0;
        virtual AUI::AbstractUI* getGeneratedAbstractUI() = 0;
    };

}//
}//
}//
}//csu

#endif // ABSTRACT_UI_GENERATOR_H
