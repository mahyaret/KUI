//  ---------------------- Doxygen info ----------------------
//! \file serial.cpp
//!
//! \brief
//! Header file for serial communication.
//!
//! \date January 2015
//!
//! \author Teunis van Beelen <teuniz@gmail.com> \n
//!
//! \copyright Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015 Teunis van Beelen
//! \n
//! \n
//! <b>GNU Lesser General Public License</b>
//! \n
//! \n
//! This file is NOT part of the KUKA-UI.
//! \n\n
//! This program is free software; you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation version 2 of the License.
//! \n\n
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//! \n\n
//! You should have received a copy of the GNU General Public License along
//! with this program; if not, write to the Free Software Foundation, Inc.,
//! 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//! This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
/* For more info and how to use this library, visit: http://www.teuniz.net/RS-232/ */


#ifndef rs232_INCLUDED
#define rs232_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>



#if defined(__linux__) || defined(__FreeBSD__)

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#else

#include <windows.h>

#endif

	int RS232_OpenComport(int, int, const char *);
	int RS232_PollComport(int, char *, int);
	int RS232_SendByte(int, unsigned char);
	int RS232_SendBuf(int, unsigned char *, int);
	void RS232_CloseComport(int);
	void RS232_cputs(int, const char *);
	int RS232_IsDCDEnabled(int);
	int RS232_IsCTSEnabled(int);
	int RS232_IsDSREnabled(int);
	void RS232_enableDTR(int);
	void RS232_disableDTR(int);
	void RS232_enableRTS(int);
	void RS232_disableRTS(int);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif


