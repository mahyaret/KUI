//  ---------------------- Doxygen info ----------------------
//! \file functionsNi.h
//!
//! \brief
//! Header file for communicating with National Instruments DAQ
//!
//! \details
//! The declarations for the functionsNi.cpp 
//!
//! \date July 2017
//!
//! \version 0.1
//!
//! \author Mahyar Abdeetedal, <mahyar.etedal@icloud.com> \n
//!
//! \copyright Copyright (C) 2016 - 2017 Mahyar Abdeetedal
//! \n
//! \n
//! <b>GNU Lesser General Public License</b>
//! \n
//! \n
//! This file is part of the KUKA-UI.
//! \n\n
//! The KUKA-UI is free software: you can redistribute it and/or modify it
//! under the terms of the GNU Lesser General Public License as published
//! by the Free Software Foundation, either version 3 of the License,
//! or (at your option) any later version.
//! \n\n
//! The KUKA-UI is distributed in the hope that it will be useful, 
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
//! the GNU Lesser General Public License for more details.
//! \n\n
//! You should have received a copy of the GNU Lesser General Public License
//! along with the KUKA-UI. If not, see
//! <http://www.gnu.org/licenses/>.

/* For more info and how to use this software, visit: http://www.etedal.net/p/kuka.html */

#include <declsNi.h>


//  ---------------------- Doxygen info ----------------------
//! \fn void stratNi(System::ComponentModel::BackgroundWorker^ workerNi, niVec & recVec, niVec & command, TaskHandle & tsk,float * feedbackForce,float * NiPID, bool & trajFlag)
//!
//! \brief
//! This method is the constant running of the following cycle:\n
//! -reading the values\n
//! - producing PID control signal\n
//! - sending the commands
//!
//! \param workerNi
//! A seperate System Component Model Background Worker for NI DAQ communications. 
//!
//! \param recVec
//! A vector containing all read signals.
//!
//! \param command
//! A vector containing all command signals.
//!
//! \param tsk
//! The real-time NI DAQ task.
//!
//! \param feedbackForce
//! A float for the force that is being fed back from the Phidgets loadcells.
//!
//! \param NiPID
//! PID parameters.
//!
//! \param trajFlag
//! A flag for indicating if KUKA UI is in middle of trajectory planned for a specific pose. If trajFlag is true, it shows that KUKA UI is busy applying a trajectory for reaching to a particular pose. This flag is for making sure that the PID controller reached a low error.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void stratNi(System::ComponentModel::BackgroundWorker^ workerNi, niVec & recVec, niVec & command, TaskHandle & tsk,float * feedbackForce,float * NiPID, bool & trajFlag);



//  ---------------------- Doxygen info ----------------------
//! \fn void kill(TaskHandle & tsk)
//!
//! \brief
//! This method stops NI DAQ Real-Time Task
//!
//! \param tsk
//! The NI Task ID.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void kill(TaskHandle & tsk);