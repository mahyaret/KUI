//  ---------------------- Doxygen info ----------------------
//! \file functionsAti.cpp
//!
//! \brief
//! Implementation file for communicating with ATI Force/Torque Sensor Controller
//!
//! \details
//! Implementation file for all methods required for communicating with ATI Force/Torque Sensor Controller. 
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
#include <serial.h>
#include <declsAti.h>

void killAti(int cport_nr){
	RS232_CloseComport(cport_nr-1);
}
void atiBias(int cport_nr){	
	cport_nr = cport_nr - 1;
	char cmd[54],buf[80], mode[] = { '8', 'N', '1', 0 };
	int count[6], n, i, j, bdrate = 115200;       
	sprintf(cmd, "SB\r\n");
	if (RS232_OpenComport(cport_nr, bdrate, mode))
	{
		printf("Can not open comport\n");
	}
	RS232_cputs(cport_nr, cmd);
	System::Threading::Thread::Sleep(30);
	killAti(cport_nr+1);
}
void runAtiSensor(System::ComponentModel::BackgroundWorker^ workerAtiSensor, atiVec & atiVector, int cport_nr)
{
	clock_t begin_time;
	char cmd[54], buf[80], mode[] = { '8', 'N', '1', 0 }, temp[8] = { 0 };
	int count[6],n,i,j,bdrate = 115200;      
	bool flag = TRUE;
	cport_nr = cport_nr - 1;
	sprintf(cmd, "qr\r\n");
	if (RS232_OpenComport(cport_nr, bdrate, mode))
	{
		killAti(cport_nr+1);
		workerAtiSensor->ReportProgress(1);
		workerAtiSensor->CancelAsync();
		//printf("Can not open comport\n");
	}
	else{
		while (!(workerAtiSensor->CancellationPending))
		{
			begin_time = clock();
			
			if (flag){
				RS232_cputs(cport_nr, cmd);
				System::Threading::Thread::Sleep(30);
				n = RS232_PollComport(cport_nr, buf, 54);
			}
			else{
				killAti(cport_nr+1);
				workerAtiSensor->ReportProgress(1);
				workerAtiSensor->CancelAsync();
			}
				
				if (buf[0]=='q' && buf[53] == '>'){
					if (n > 0)
					{
						buf[n] = 0;   /* always put a "null" at the end of a string! */

						for (i = 0; i < n; i++)
						{
							if (buf[i] < 32)  /* replace unreadable control-codes by dots */
							{
								buf[i] = ' ';
							}
						}
						
						//printf("received %i bytes: %s\n", n, buf);
					}
					
					for (j = 0; j < 6; j++){
						for (i = 0; i < 6; i++){
							temp[i] = buf[i + 7*(j+1)];
						}
						sscanf(temp, "%d", &count[j]);
					}
					atiVector.fx = float(count[0]) / (0.224808942443 * 80);
					atiVector.fy = float(count[1]) / (0.224808942443 * 80);
					atiVector.fz = float(count[2]) / (0.224808942443 * 80);
					atiVector.tx = float(count[3]) / (8.85074576738 * 80);
					atiVector.ty = float(count[4]) / (8.85074576738 * 80);
					atiVector.tz = float(count[5]) / (8.85074576738 * 80);
					flag = TRUE;
				}
				else{
					flag = FALSE;
				}
			workerAtiSensor->ReportProgress(0);
			atiVector.dt = float(clock() - begin_time) / CLOCKS_PER_SEC;
	}
	}
}

