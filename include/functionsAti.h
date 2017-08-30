//  ---------------------- Doxygen info ----------------------
//! \file functionsAti.h
//!
//! \brief
//! Header file for communicating with ATI force/torque sensor controllers
//!
//! \details
//! The declarations here are for the functionsAti.cpp 
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

#include <declsAti.h>

//  ---------------------- Doxygen info ----------------------
//! \fn void runAtiSensor(System::ComponentModel::BackgroundWorker^ workerAtiSensor, atiVec & atiVector, int cport_nr)
//!
//! \brief
//! This method read the sensor connected via ATI controller.
//!
//! \param workerAtiSensor
//! A seperate System Component Model Background Worker for ATI controller communications. 
//!
//! \param atiVector
//! A vecor containing the data from force/torque sensor.
//!
//! \param cport_nr
//! The serial port for communicating with ATI controller.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void runAtiSensor(System::ComponentModel::BackgroundWorker^ workerAtiSensor, atiVec & atiVector, int cport_nr);

//  ---------------------- Doxygen info ----------------------
//! \fn void killAti(int cport_nr)
//!
//! \brief
//! This method closes the serial port.
//!
//! \param cport_nr
//! The opened serial port to be closed.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void killAti(int cport_nr);

//  ---------------------- Doxygen info ----------------------
//! \fn void atiBias(int cport_nr)
//!
//! \brief
//! This method biases the sensor using the ATI controller.
//!
//! \param cport_nr
//! The serial port for communicating with ATI controller.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void atiBias(int cport_nr);