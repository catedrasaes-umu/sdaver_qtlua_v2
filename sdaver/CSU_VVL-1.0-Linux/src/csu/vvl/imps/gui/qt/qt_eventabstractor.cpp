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

#include "qt_eventabstractor.h"
#include <QApplication>
#include <QEvent>

#include <QDialog>
#include "qt_abstractionresult.h"
#include "qt_eventabstractionresult.h"
#include "qt_elementabstractor.h"

namespace csu {
namespace vvl {
namespace gui {
namespace qt {

Qt_EventAbstractor::Qt_EventAbstractor(VerificationContextPtr context)
    :GenericEventAbstractor(context)
{}

Qt_EventAbstractor::~Qt_EventAbstractor(){}

void Qt_EventAbstractor::install()
{
    mapEvents();
    winIdChange_=false;
    qApp->installEventFilter(this);
}

void Qt_EventAbstractor::uninstall()
{
    qApp->removeEventFilter(this);
}

void Qt_EventAbstractor::mapEvents()
{
    eventMap_[QEvent::MouseButtonPress]=VVL_EVENT_MOUSEPRESS;
    eventMap_[QEvent::MouseButtonRelease]=VVL_EVENT_MOUSECLICK;
    eventMap_[QEvent::FocusOut]=VVL_EVENT_FOCUSOUT;
    eventMap_[QEvent::FocusIn]=VVL_EVENT_FOCUSIN;
}

bool Qt_EventAbstractor::eventFilter(QObject *obj, QEvent *event)
{
    //Trigger Events are stored inside the context
    unsigned long triggerStopEvents = context_->triggerStopEvents();
    unsigned long triggerWatchEvents = context_->triggerWatchEvents();

    //QTipLabels, as tooltip text labels, triggers winidchange and close events, thats why it is necessary to
    //filter them. Now i insert a condition in order to make the comparision. In the future
    // maybe should be useful to make a global condition to avoid this class, but only if necessary,
    //beacuse maybe we dont want them to jam with the window creation process, but maybe we want to
    //check them against the srs document

    if ( (event->type() == QEvent::WinIdChange) && strcmp(obj->metaObject()->className(),"QTipLabel") != 0)
    {
        winIdChange_=true;
    }

    //Check if the event is a trigger event
    if ((((eventMap_[event->type()]&triggerStopEvents)!=0)
         || (eventMap_[event->type()]&triggerWatchEvents)!=0))
    {

        /// filter by widget
        //std::cout << "@@TRYING: " << obj->objectName().toStdString() << std::endl;
        QWidget* w = dynamic_cast<QWidget *>(obj);
        if (!w) return false;
        QtElementAbstractor* ea = dynamic_cast<QtElementAbstractor*>(context_->elementAbstractor.get());
        if (ea && !ea->filterWidget(w)) return false;
        //std::cout << "@@PASS "  << std::endl;

        /// Getting an abstract representation from a boost::any object
        GenericAbstractionResult * abres=const_cast<GenericAbstractionResult *>(context_->elementAbstractor->getElementAbstraction(obj));
        if (abres)
        {
            //Casting to qt an abstraction result object
            Qt_AbstractionResult * qtres=dynamic_cast<Qt_AbstractionResult *>(abres);

            //Getting the name of the object
            std::string objName;
            objName = qtres->name();

            _ilog::abs <<"(Qt_EventAbstractor::eventFilter) Trigger Event Generated by "<<objName<<std::endl;

            ///unlock object signals
            obj->blockSignals(false);

            //Event propagation depends on the Verification Engine validation result
            //verificationEngine.get()->handleEvent return true if every rule is accomplished
            //but a return true value will stop the event propagation
            //that's why the return value must be the opposite

            /// Performance and timing stuff
            ///take reference time
            timespec tS;
            tS.tv_sec = 0;
            tS.tv_nsec = 0;
            clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
            //
            boost::posix_time::ptime tstart = boost::posix_time::microsec_clock::local_time();


            ///handle the event
            bool result =
                    context_->verificationEngine->handleEvent(new Qt_EventAbstractionResult(event->type(),qtres));


            if (result) std::cout << "@@Interacted: " << objName << std::endl;

            ///get elapsed time
            boost::posix_time::ptime tend = boost::posix_time::microsec_clock::local_time();
            boost::posix_time::time_duration td = tend - tstart;

            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
            std::cout << "Elapsed time is: microsec = " << td << std::endl;
            timeList_.push_back(td.total_nanoseconds());

            TimeList::iterator it;
            unsigned long int average = 0;
            for (it = timeList_.begin();it != timeList_.end();it++)
            {
                average += *it;
            }
            std::cout << "Average elapsed time is: Nsecs = "<< average / timeList_.size() << std::endl;



            //If event belongs to the triggerStopEvents then the result will be the validation result
            if ((eventMap_[event->type()]&triggerStopEvents)!=0){
                //Blocking all signals if the validation result is false
                obj->blockSignals(!result);
            }
        }
    }
    else if ((event->type() == QEvent::ActivationChange && winIdChange_) || ((event->type()==QEvent::Close) && (strcmp(obj->metaObject()->className(),"QTipLabel")!=0))){
        //This condition control the creation and deletion of windows and dialogs inside the application
        winIdChange_=false;
        if (event->type()==QEvent::Close)
            dynamic_cast<QWidget *>(obj)->setHidden(true);
        else
            dynamic_cast<QWidget *>(obj)->setHidden(false);

        //Notifying that something has happened with the graphical composition
        notifyAll(obj->objectName().toStdString());
        std::cout << "@@Change in: " << obj->objectName().toStdString() << std::endl;
    }
    //Continue event propagation
    return false;
}

} //qt
} //gui
} //vvl
} //csu
