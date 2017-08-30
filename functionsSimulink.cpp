//  ---------------------- Doxygen info ----------------------
//! \file functionsSimulink.cpp
//!
//! \brief
//! Implementation file for communicating with the MATLAB/Simulink in realtime
//!
//! \details
//! Implementation file for the MATLAB/Simulink Realtime connection 
//! using UDP protocol. This file is still under development. 
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <defs.h>
#include <friComm.h>
#include <FRIRemote.h>
#include <declsNi.h>
#include <declsPhidgets.h>
#include <declsAti.h>
#include <functions.h>
void int2char(int inte,char *chr) {
	chr[0] = (char)((inte >> 24) & 0xFF);
	chr[1] = (char)((inte >> 16) & 0xFF);
	chr[2] = (char)((inte >> 8) & 0XFF);
	chr[3] = (char)((inte & 0XFF));
	//printf("int2char %d, %d, %d, %d\n", chr[0], chr[1], chr[2], chr[3]);
}
void char2int(char *chr,int &inte) {
	int tmpInt = int((unsigned char)(chr[0]) << 24 |
		(unsigned char)(chr[1]) << 16 |
		(unsigned char)(chr[2]) << 8 |
		(unsigned char)(chr[3]));
	inte = tmpInt;
}
void pushInSend(float *var, char *SendBuf) {
	char tmpChar[4] = { 0,0,0,0 };
	int varInt[NUMBER_OF_JOINTS];
	for (int i = 0; i < NUMBER_OF_JOINTS; i++)
	{
		varInt[i] = (int)(round(100* rad2deg(var[i])));
		int2char(varInt[i], tmpChar);
		SendBuf[4*i+0] = tmpChar[0];
		SendBuf[4*i+1] = tmpChar[1];
		SendBuf[4*i+2] = tmpChar[2];
		SendBuf[4*i+3] = tmpChar[3];
	}
}
void pullOutReceive(char *ReceiveBuf,float *var) {
	char tmpChar[4] = { 0,0,0,0 };
	int varInt[NUMBER_OF_JOINTS];
	for (int i = 0; i < NUMBER_OF_JOINTS; i++)
	{
		tmpChar[0] = ReceiveBuf[4 * i + 0];
		tmpChar[1] = ReceiveBuf[4 * i + 1];
		tmpChar[2] = ReceiveBuf[4 * i + 2];
		tmpChar[3] = ReceiveBuf[4 * i + 3];
		char2int(tmpChar, varInt[i]);
		var[i] = deg2rad((float)(varInt[i])/10000);
	}
}
void startSimulink(System::ComponentModel::BackgroundWorker^ workerSimulink, tFriMsrData& msr, niVec & recVec, phidgetsVec & phiVec, atiVec & atiVector, float *simulinkTrg)
{
	WSADATA            wsaData;
	SOCKET             SRSocket;
	SOCKADDR_IN        ReceiverAddr;
	int                recPort = 5150, sndPort = 5151;
	char			   ReceiveBuf[28], SendBuf[28];
	int                BufLength = 28;
	SOCKADDR_IN        SenderAddr;
	int                SenderAddrSize = sizeof(SenderAddr), ReceiverAddrSize = sizeof(ReceiverAddr);
	int                ByteReceived = 5, ByteSent = 5;


	

	// Initialize Winsock version 2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Server: WSAStartup failed with error %ld\n", WSAGetLastError());
	}
	else
		printf("Server: The Winsock DLL status is %s.\n", wsaData.szSystemStatus);



	// Create a new socket to receive datagrams on.
	SRSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SRSocket == INVALID_SOCKET)
	{
		printf("Server: Error at socket(): %ld\n", WSAGetLastError());
		// Clean up
		WSACleanup();
	}
	else
		printf("Server: socket() is OK!\n");

	// Set up a SOCKADDR_IN structure that will tell bind that we
	// want to receive datagrams from all interfaces using port 5150.
	// The IPv4 family
	ReceiverAddr.sin_family = AF_INET;
	// Port no. 5150
	ReceiverAddr.sin_port = htons(recPort);
	// From all interface (0.0.0.0)
	ReceiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	SenderAddr.sin_family = AF_INET;
	SenderAddr.sin_port = htons(sndPort);
	SenderAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Associate the address information with the socket using bind.
	// At this point you can receive datagrams on your bound socket.
	if (bind(SRSocket, (SOCKADDR *)&ReceiverAddr, sizeof(ReceiverAddr)) == SOCKET_ERROR)
	{
		printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
		// Close the socket
		closesocket(SRSocket);
		// Do the clean up
		WSACleanup();
		// and exit with error
	}
	else
		printf("Server: bind() is OK!\n");

	// Some info on the receiver side...
	//getsockname(SRSocket, (SOCKADDR *)&ReceiverAddr, (int *)sizeof(ReceiverAddr));
	printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(ReceiverAddr.sin_addr));
	printf("Server: Receiving port used: %d\n", htons(ReceiverAddr.sin_port));
	printf("Server: Sending IP used: %s\n", inet_ntoa(SenderAddr.sin_addr));
	printf("Server: Sending port used: %d\n", htons(SenderAddr.sin_port));
	printf("Server: Simulink is ready to send\\receive a datagram...\n");

	// At this point you can receive datagrams on your bound socket.
	while (ByteReceived > 0 && ByteSent > 0 && !(workerSimulink->CancellationPending)) {
		

		ByteReceived = recvfrom(SRSocket, ReceiveBuf, BufLength, 0,
			(SOCKADDR *)&ReceiverAddr, &ReceiverAddrSize);

		if (ByteReceived > 0)
		{
			//printf("Server: Total Bytes received: %d\n", ByteReceived);
			//printf("Server: Total Bytes sent: %d\n", ByteSent);
		}
		else if (ByteReceived <= 0)
			printf("Server: Connection closed with error code: %ld\n", WSAGetLastError());
		else
			printf("Server: recvfrom() failed with error code: %d\n", WSAGetLastError());
		pullOutReceive(ReceiveBuf, simulinkTrg);
		printf("Server: Total Bytes sent: %5.8f and %5.8f and %5.8f and %5.8f and %5.8f and %5.8f and %5.8f\n", simulinkTrg[0], simulinkTrg[1], simulinkTrg[2], simulinkTrg[3], simulinkTrg[4], simulinkTrg[5], simulinkTrg[6]);



		pushInSend(msr.data.msrJntPos, SendBuf);
		ByteSent = sendto(SRSocket, SendBuf, BufLength, 0,
			(SOCKADDR *)&SenderAddr, SenderAddrSize);	
		if (ByteSent > 0)
		{
			//printf("Server: Total Bytes sent: %d\n", ByteSent);
		}
		else if (ByteSent <= 0)
			printf("Server: Connection closed with error code: %ld\n", WSAGetLastError());
		else
			printf("Server: recvfrom() failed with error code: %d\n", WSAGetLastError());
	}
}


