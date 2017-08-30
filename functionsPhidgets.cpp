//  ---------------------- Doxygen info ----------------------
//! \file functionsPhidgets.cpp
//!
//! \brief
//! Implementation file for communicating with Phidgets
//!
//! \details
//! Implementation file for all methods for reading from 
//! Phidgets PhidgetBridge Wheatstone Bridge Sensor Interface.
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

#include <stdio.h>
#include <time.h>
#pragma managed(push, off)
#include <declsPhidgets.h>
#pragma managed(pop)
#include <phidget21.h>


//! A normal member taking two arguments and returning an integer value.
/*!
\param a an integer argument.
\param s a constant character pointer.
\return The test results
\sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
*/
int CCONV AttachHandler(CPhidgetHandle phid, void *userptr)
{
	CPhidgetBridgeHandle bridge = (CPhidgetBridgeHandle)phid;

	CPhidgetBridge_setEnabled(bridge, 0, PTRUE);
	CPhidgetBridge_setEnabled(bridge, 1, PTRUE);
	CPhidgetBridge_setEnabled(bridge, 2, PTRUE);
	CPhidgetBridge_setEnabled(bridge, 3, PTRUE);

	CPhidgetBridge_setGain(bridge, 0, PHIDGET_BRIDGE_GAIN_128);
	CPhidgetBridge_setGain(bridge, 1, PHIDGET_BRIDGE_GAIN_1);
	CPhidgetBridge_setGain(bridge, 2, PHIDGET_BRIDGE_GAIN_1);
	CPhidgetBridge_setGain(bridge, 3, PHIDGET_BRIDGE_GAIN_128);
	CPhidgetBridge_setDataRate(bridge, 1);

	printf("Attach handler ran!\n");
	return 0;
}

int CCONV DetachHandler(CPhidgetHandle phid, void *userptr)
{
	printf("Detach handler ran!\n");
	return 0;
}

int CCONV ErrorHandler(CPhidgetHandle phid, void *userptr, int ErrorCode, const char *errorStr)
{
	printf("Error event: %s\n",errorStr);
	return 0;
}

#define FREQS_SIZE 20
double bridges[FREQS_SIZE] = {0};
int CCONV data(CPhidgetBridgeHandle phid, void *userPtr, int index, double val)
{
	CPhidgetBridgeHandle bridge = (CPhidgetBridgeHandle)phid;
	switch (index)
	{
	case 0:
		((phidgetsVec*)userPtr)->ch0 = val;
	case 1:
		((phidgetsVec*)userPtr)->ch1 = val;
	case 2:
		((phidgetsVec*)userPtr)->ch2 = val;
	case 3:
		((phidgetsVec*)userPtr)->ch3 = val;
	default:
		break;
	}
	//printf("Data Event (%d) %lf\n",index,val);

	return 0;
}

void display_generic_properties(CPhidgetHandle phid)
{
	int sernum, version;
	const char *deviceptr;
	CPhidget_getDeviceType(phid, &deviceptr);
	CPhidget_getSerialNumber(phid, &sernum);
	CPhidget_getDeviceVersion(phid, &version);

	printf("%s\n", deviceptr);
	printf("Version: %8d SerialNumber: %10d\n", version, sernum);
	return;
}
void calibrate(float * calMatrix, phidgetsVec phiVec,float * calibratedPhidgets){
	calibratedPhidgets[0] = phiVec.ch0*calMatrix[0] + calMatrix[4];
	calibratedPhidgets[1] = phiVec.ch1*calMatrix[1] + calMatrix[5];
	calibratedPhidgets[2] = phiVec.ch2*calMatrix[2] + calMatrix[6];
	calibratedPhidgets[3] = phiVec.ch3*calMatrix[3] + calMatrix[7];
}
void runPhidgets(System::ComponentModel::BackgroundWorker^ workerPhidgets, float * calMatrix, float * calibratedPhidgets, CPhidgetBridgeHandle &bridge, phidgetsVec & phiVec)
{
    const char *err;	
	int result;
	clock_t begin_time;

	CPhidgetBridge_create(&bridge);
	CPhidget_set_OnAttach_Handler((CPhidgetHandle)bridge, AttachHandler, NULL);
	CPhidget_set_OnDetach_Handler((CPhidgetHandle)bridge, DetachHandler, NULL);
	CPhidget_set_OnError_Handler((CPhidgetHandle)bridge, ErrorHandler, NULL);
	CPhidget_open((CPhidgetHandle)bridge, -1);

		//Wait for 10 seconds, otherwise exit
		if(result = CPhidget_waitForAttachment((CPhidgetHandle)bridge, 10000))
		{
			CPhidget_getErrorDescription(result, &err);
			printf("Problem waiting for attachment: %s\n", err);
			return;
		}
		display_generic_properties((CPhidgetHandle)bridge);
	while (!(workerPhidgets->CancellationPending))
	{
		begin_time = clock();
		CPhidgetBridge_set_OnBridgeData_Handler(bridge, data, &phiVec);
		calibrate(calMatrix, phiVec,calibratedPhidgets);
		System::Threading::Thread::Sleep(1);
		workerPhidgets->ReportProgress(0);
		phiVec.dt = float(clock() - begin_time) / CLOCKS_PER_SEC;
		//printf("time:%f\n",);
		
	}
}
void killPhidgets(CPhidgetBridgeHandle & bridge){
	CPhidget_close((CPhidgetHandle)bridge);
	CPhidget_delete((CPhidgetHandle)bridge);
	return;
}
