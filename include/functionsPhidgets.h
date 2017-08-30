//  ---------------------- Doxygen info ----------------------
//! \file functionsPhidgets.h
//!
//! \brief
//! Header file for communicating with Phidgets
//!
//! \details
//! The declarations here are for the functionsPhidgets.cpp 
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

#include <declsPhidgets.h>

//  ---------------------- Doxygen info ----------------------
//! \fn void runPhidgets(System::ComponentModel::BackgroundWorker^ workerPhidgets, float * calMatrix, float *calibratedPhidgets, CPhidgetBridgeHandle & bridge, phidgetsVec & phiVec)
//!
//! \brief
//! This method reads data from Phidgets.
//!
//! \param workerPhidgets
//! A seperate System Component Model Background Worker for Phidgets communications. 
//!
//! \param calMatrix
//! The matrix of Calibration for each bridge input.
//!
//! \param calibratedPhidgets
//! The calibrated data read from Phidgets.
//!
//! \param bridge
//! The Phidget Bridge ID.
//!
//! \param phiVec
//! The vector of raw data read from Phidgets.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void runPhidgets(System::ComponentModel::BackgroundWorker^ workerPhidgets, float * calMatrix, float *calibratedPhidgets, CPhidgetBridgeHandle & bridge, phidgetsVec & phiVec);

//  ---------------------- Doxygen info ----------------------
//! \fn void killPhidgets(CPhidgetBridgeHandle & bridge)
//!
//! \brief
//! This method stops the Phidgets.
//!
//! \param bridge
//! The Phidget Bridge ID.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void killPhidgets(CPhidgetBridgeHandle & bridge);

