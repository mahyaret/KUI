//  ---------------------- Doxygen info ----------------------
//! \file defs.h
//!
//! \brief
//! Header file for all the definitions 
//!
//! \details
//! Header file for all the definitions used throughout the entire project
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

#define PI 3.141592653589793238462643383279
#define CYCLE_TIME_IN_SECONDS 2
#define NUMBER_OF_JOINTS 7
#define CART_COMP 6
#define QUAT 7
#define ACC 10000

#define CULUMNS 6
#define ELEMENTS 12

#define CMDCARTPOS 1
#define CMDCARTPOSFRIOFFSET 2
#define CMDJNTPOS 4
#define CMDJNTPOSFRIOFFSET 8
#define ESTEXTJNTTRQ 16
#define ESTEXTTCPFT 32
#define GRAVITY 64
#define JACOBIAN 128
#define MASSMATRIX 256
#define MSRCARTPOS 512
#define MSRJNTPOS 1024
#define MSRJNTTRQ 2048
#define NI 4096
#define PHIDGETS 8192
#define CALIBRATEDPHIDGETS 16384 
#define ATISENSOR 32768
#define EE 65536

#define VEC 9

#define OPEN 2
#define CLOSE 1
#define FORCEERRORTOLERANCE 0.5
#define __max_esum_val 1000

#define CALMAT 8
#define LOADCELLS 4
