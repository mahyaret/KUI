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
//! <b>GNU  General Public License</b>
//! \n
//! \n
//! This file is part of the KUKA-UI.
//! \n\n
//! The KUKA-UI is free software: you can redistribute it and/or modify it
//! under the terms of the GNU  General Public License as published
//! by the Free Software Foundation, either version 3 of the License,
//! or (at your option) any later version.
//! \n\n
//! The KUKA-UI is distributed in the hope that it will be useful, 
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
//! the GNU  General Public License for more details.
//! \n\n
//! You should have received a copy of the GNU  General Public License
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
#define FORCEERRORTOLERANCE 0.6
#define __max_esum_val 1000

#define CALMAT 8
#define LOADCELLS 4

#define POSE "configuration/pose.txt"
#define TOOL "configuration/tool.txt"
#define CALIBRATION "configuration/calibration.txt"
#define PID "configuration/PID.txt"
#define SEPARATOR ","

#define KUKA_POSE_PAUSE "Pause"
#define KUKA_POSE_GO "Go!"
#define STATSTRING "timestamp = {0}; state = {1}; quality = {2}; desiredMsrSampleTime = {3}; desiredCmdSampleTime = {4}; safetyLimits = {5}; KUKA Command={6}"
#define FRI_CONTROL_MODE_NA "CTRL N/A"
#define FRI_CONTROL_MODE_POSITION "Position"
#define FRI_CONTROL_MODE_CARTIMP "CartImp"
#define FRI_CONTROL_MODE_JNTIMP "JntImp"
#define FRI_CONTROL_MODE_OTHER "Other"
#define FRI_CONTROL_MODE_UNKNOWN "Unknown"
#define START_LOGGING "Start Logging"
#define STOP_LOGGING "Stop Logging"

#define ATI_ERROR_00 "ERROR reading ATI. \n - Make sure controller buad rate is set to 115200. \n - Make sure the sensor is not saturated."
#define START_ATI "startATI"
#define STOP_ATI "stopATI"

#define START_NI "startNI"
#define STOP_NI "stopNI"

#define START_PHIDGETS "startPhidgets"
#define STOP_PHIDGETS "stopPhidgets"

#define START_SIMULINK "startSimulink"
#define STOP_SIMULINK "stopSimulink"

#define ABOUT "Author: Mahyar Abdeetedal\nCopyright(C) 2016 - 2017 Mahyar Abdeetedal\nEmail: mahyar.etedal@icloud.com\nFor more info and how to use this software, visit: http://www.etedal.net/p/kuka.html"