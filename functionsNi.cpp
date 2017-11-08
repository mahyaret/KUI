//  ---------------------- Doxygen info ----------------------
//! \file functionsNi.cpp
//!
//! \brief
//! Implementation file for communicating with the National instrument Data Acquisition Device 
//!
//! \details
//! Implementation file for all methods for communication with 
//! the National Instrument Data Acquisition Device. This file also 
//! constitutes the implementation of Kalman filter and a PID controller.
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

#include <defs.h>
#include <NIDAQmx.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <declsNi.h>
float e1 = 0, e2 = 0, esum = 0, Kp, Kd , Ki , pidout = 0, xhat =0, xhatp=0, xhat_1=0,p=0,pp=0,p_1=0,k=0,lastForce=0;
int lastCmd = 0;
bool forceErrorFlag = false;
void handleError(int error){
	char        errBuff[2048] = { '\0' };
	if (error)
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
	if (error)
		printf("DAQmx Error: %s\n", errBuff);
}
void init(TaskHandle & tsk){
	handleError(DAQmxCreateTask("", &tsk));
	handleError(DAQmxCreateAIVoltageChan(tsk, "Dev1/ai0", "", DAQmx_Val_RSE, -10.0, 10.0, DAQmx_Val_Volts, NULL));
	handleError(DAQmxStartTask(tsk));
}
void recNi(niVec& recVec, TaskHandle  tsk){
	int32       read;
	float64     data[1];
	handleError(DAQmxReadAnalogF64(tsk, 1, 10.0, DAQmx_Val_GroupByChannel, data, 1, &read, NULL));
	recVec.position = data[0];
}
void doCmd(niVec command, niVec recVec, niVec & sendVec, float& temp, float * feedbackForce,float * NiPID, bool & trajFlag){
	sendVec.currentLimit = command.currentLimit;
	if ((command.cmd == OPEN && command.position <= 3.2) || (command.cmd == CLOSE && command.force <= 50)){
		if (command.cmd != lastCmd || command.force != lastForce)
			e1 = 0, e2 = 0, esum = 0, xhat = 0, xhatp = 0, p = 0, pp = 0, k = 0;
		//printf("Last command = %d, current Command=%d \n", lastCmd, command.cmd);
		//printf("Last force = %2.5f, current force=%2.5f \n", lastForce, command.force);
		lastCmd = command.cmd;
		lastForce = command.force;
		e2 = e1;
		xhatp = xhat;
		pp = p + 0.1;
		
		switch (command.cmd){
		case OPEN:
			k = (pp) / (pp + 10);
			Kp = .02, Kd = 0.0002, Ki = .001;
			xhat = xhatp + k*(recVec.position - xhatp);
			p = pp*(1 - k);
			e1 = command.position - xhat;
			break;
		case CLOSE:
			k = (pp) / (pp + NiPID[4]);
			Kp = NiPID[1], Kd = NiPID[2], Ki = NiPID[3];
			xhat = xhatp + k*(feedbackForce[(int)(NiPID[0])] - xhatp);
			p = pp*(1 - k);
			e1 = xhat - command.force;
			break;
		default:
			break;
		}

		esum += e1;
		if (esum > __max_esum_val)
			esum = __max_esum_val;
		if (esum < -__max_esum_val)
			esum = -__max_esum_val;
		pidout = Kp*e1 + Kd*((e1 - e2) / recVec.dt) + Ki*esum*recVec.dt;
		if (pidout > 1)
			pidout = 1;
		if (pidout < -1)
			pidout = -1;
		sendVec.force = fabs(pidout);
		if (pidout > 0)
			sendVec.cmd = OPEN;
		if (pidout < 0)
			sendVec.cmd = CLOSE;
		if (fabs(e1) > FORCEERRORTOLERANCE && trajFlag){
			trajFlag = false;
			forceErrorFlag = true;
		}
		if (fabs(e1)<FORCEERRORTOLERANCE && forceErrorFlag){
			trajFlag = true;
			forceErrorFlag = false;
		}

		//printf("error= %2.5f,esum= %2.5f, control = %2.5f,xhat= %2.5f \n", e1, esum, pidout, xhat);
	}
	else{
		//sendVec.force = 2;
		//sendVec.cmd = command.cmd;

		command.cmd == OPEN;
		command.position = 3.2;

		//printf("force= %2.5f, rec= %2.5f, send = %2.5f \n", sendVec.force, command.force, sendVec.cmd);
	}
	
	
}
void sendNi(niVec sendVec){
	TaskHandle	taskHandleForce = 0;
	float64     force[1];
	force[0] = sendVec.force;
	if (sendVec.currentLimit == 1)
		if (force[0] > 0.035)
			force[0] = 0.035;
	handleError(DAQmxCreateTask("", &taskHandleForce));
	handleError(DAQmxCreateAOVoltageChan(taskHandleForce, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, ""));
	handleError(DAQmxStartTask(taskHandleForce));
	handleError(DAQmxWriteAnalogF64(taskHandleForce, 1, 1, 10.0, DAQmx_Val_GroupByChannel, force, NULL, NULL));
	DAQmxStopTask(taskHandleForce);
	DAQmxClearTask(taskHandleForce);



	TaskHandle	taskHandleClose = 0;
	uInt32      cmd;
	int32		written;
	cmd = (int)(sendVec.cmd);
	handleError(DAQmxCreateTask("", &taskHandleClose));
	handleError(DAQmxCreateDOChan(taskHandleClose, "Dev1/port0", "", DAQmx_Val_ChanForAllLines));
	handleError(DAQmxStartTask(taskHandleClose));
	handleError(DAQmxWriteDigitalU32(taskHandleClose, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &cmd, &written, NULL));
	DAQmxStopTask(taskHandleClose);
	DAQmxClearTask(taskHandleClose);

}
void stratNi(System::ComponentModel::BackgroundWorker^ workerNi, niVec & recVec, niVec & command, TaskHandle & tsk, float * feedbackForce,float * NiPID, bool & trajFlag){
	niVec sendVec;
	float temp=0;
	clock_t begin_time;
	init(tsk);
	while (!(workerNi->CancellationPending))
	{   
		begin_time = clock();
		recNi(recVec,tsk);
		doCmd(command, recVec, sendVec, temp, feedbackForce, NiPID, trajFlag);
		sendNi(sendVec);
		workerNi->ReportProgress(0);
		recVec.dt = float(clock() - begin_time) / CLOCKS_PER_SEC;
	}
}

void kill(TaskHandle & tsk){
	handleError(DAQmxStopTask(tsk));
	handleError(DAQmxClearTask(tsk));
}
