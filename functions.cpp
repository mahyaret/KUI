//  ---------------------- Doxygen info ----------------------
//! \file mainForm.cpp
//!
//! \brief
//! Implementation file for communicating with KUKA Fast Research Interface (FRI)
//!
//! \details
//! Implementation file for all methods for trajectory generation and communication 
//! with Kuka FRI using TypeIIRML library and FRI_Remote library, respectively. 
//! It also has the implementations for geometrical tool frame transformation.   
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
#include <friComm.h>
#include <FRIRemote.h>
#include <declsNi.h>
#include <declsPhidgets.h>
#include <declsAti.h>
#include <ReflexxesAPI.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace System::IO;
using namespace std;


void startLogging(System::ComponentModel::BackgroundWorker^ workerLog, System::Windows::Forms::TextBox^  txtAdr, tFriMsrData& msr, int selection, unsigned int& j, niVec & recVec, phidgetsVec & phiVec, float * calibratedPhidgets, atiVec & atiVector, float* ee){
	FILE *file_id;
	const char* fileName = (const char*)(void*)Marshal::StringToHGlobalAnsi(txtAdr->Text);
	file_id = fopen(fileName, "w");
	if (file_id == NULL) {
		MessageBox::Show("ERROR Openning log file");
	}
	else{
		while (!(workerLog->CancellationPending))
		{
			fprintf(file_id, "time\t%.3f\tiPose\t%d", (float)(clock()) / 1000, j);
			if (selection & CMDCARTPOS){
				fprintf(file_id, "\tcmdCartPos");
				for (int i = 0; i < sizeof(msr.data.cmdCartPos) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.cmdCartPos[i]);
				}
			}
			if (selection & CMDCARTPOSFRIOFFSET){
				fprintf(file_id, "\tcmdCartPosFriOffset");
				for (int i = 0; i < sizeof(msr.data.cmdCartPosFriOffset) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.cmdCartPosFriOffset[i]);
				}
			}
			if (selection & CMDJNTPOS){
				fprintf(file_id, "\tcmdJntPos");
				for (int i = 0; i < sizeof(msr.data.cmdJntPos) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.cmdJntPos[i]);
				}
			}
			if (selection & CMDJNTPOSFRIOFFSET){
				fprintf(file_id, "\tcmdJntPosFriOffset");
				for (int i = 0; i < sizeof(msr.data.cmdJntPosFriOffset) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.cmdJntPosFriOffset[i]);
				}
			}
			if (selection & ESTEXTJNTTRQ){
				fprintf(file_id, "\testExtJntTrq");
				for (int i = 0; i < sizeof(msr.data.estExtJntTrq) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.estExtJntTrq[i]);
				}
			}
			if (selection & ESTEXTTCPFT){
				fprintf(file_id, "\testExtTcpFT");
				for (int i = 0; i < sizeof(msr.data.estExtTcpFT) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.estExtTcpFT[i]);
				}
			}
			if (selection & GRAVITY){
				fprintf(file_id, "\tgravity");
				for (int i = 0; i < sizeof(msr.data.gravity) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.gravity[i]);
				}
			}
			if (selection & JACOBIAN){
				fprintf(file_id, "\tjacobian");
				for (int i = 0; i < sizeof(msr.data.jacobian) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.jacobian[i]);
				}
			}
			if (selection & MASSMATRIX){
				fprintf(file_id, "\tmassMatrix");
				for (int i = 0; i < sizeof(msr.data.massMatrix) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.massMatrix[i]);
				}
			}
			if (selection & MSRCARTPOS){
				fprintf(file_id, "\tmsrCartPos");
				for (int i = 0; i < sizeof(msr.data.msrCartPos) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.msrCartPos[i]);
				}
			}
			if (selection & MSRJNTPOS){
				fprintf(file_id, "\tmsrJntPos");
				for (int i = 0; i < sizeof(msr.data.msrJntPos) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.msrJntPos[i]);
				}
			}
			if (selection & MSRJNTTRQ){
				fprintf(file_id, "\tmsrJntTrq");
				for (int i = 0; i < sizeof(msr.data.msrJntTrq) / sizeof(fri_float_t); i++)
				{
					fprintf(file_id, "\t%2.4f", msr.data.msrJntTrq[i]);
				}
			}
			if (selection & NI){
				fprintf(file_id, "\tNI\t%2.4f",recVec.position);
			}
			if (selection & PHIDGETS){
				fprintf(file_id, "\tPhidgets\t%2.4f\t%2.4f\t%2.4f\t%2.4f",phiVec.ch0,phiVec.ch1,phiVec.ch2,phiVec.ch3);
			}
			if (selection & CALIBRATEDPHIDGETS){
				fprintf(file_id, "\tCalibratedPhidgets\t%2.4f\t%2.4f\t%2.4f\t%2.4f", *(calibratedPhidgets+0), *(calibratedPhidgets+1), *(calibratedPhidgets+2), *(calibratedPhidgets+3));
			}
			if (selection & ATISENSOR){
				fprintf(file_id, "\tAtiSensor\t%2.4f\t%2.4f\t%2.4f\t%2.4f\t%2.4f\t%2.4f", atiVector.fx,atiVector.fy,atiVector.fz,atiVector.tx,atiVector.ty,atiVector.tz);
			}
			if (selection & EE){
				fprintf(file_id, "\tEndEffectorPose");
				for (int i = 0; i < CART_COMP; i++)
				{
					fprintf(file_id, "\t%2.4f",ee[i]);
				}
			}
			fprintf(file_id, "\n");
			System::Threading::Thread::Sleep(10);
		}

		fclose(file_id);
	}
}
void saveToFile(System::String^ str, System::String ^Addr){
	FILE *file_id;
	const char* fileName = (const char*)(void*)Marshal::StringToHGlobalAnsi(Addr);
	file_id = fopen(fileName, "w");
	if (file_id == NULL) {
		MessageBox::Show("ERROR Openning log file");
	}
	else{
		fprintf(file_id, "%s", str);
		fclose(file_id);
	}//else if (file_id == NULL)
}
String ^readFromDataGridView(DataGridView ^DataView){
	String ^configStr;
	configStr = gcnew  System::String(configStr);
	for (int j = 0; j < DataView->Rows->Count; j++){
		for (int i = 0; i < DataView->Columns->Count; i++){
			configStr += Convert::ToString(DataView->Rows[j]->Cells[i]->Value);
			configStr += ",";
		}
		configStr += "\n";
	}
	return configStr;
}
System::String ^loadFromFile(System::String ^Addr, int &count){
	String^ string;
	try
	{
		//Console::WriteLine("trying to open file {0}...", Addr);
		StreamReader^ din = File::OpenText(Addr);
		String^ str;
		while ((str = din->ReadLine()) != nullptr)
		{
			count++;
			string += str;
			//Console::WriteLine("line {0}: {1}", count, str);
		}
		din->Close();
	}
	catch (Exception^ e)
	{
		MessageBox::Show("ERROR");
	}

	return string;
}
void writeToDataGridView(System::Windows::Forms::DataGridView ^DataView, System::String^ str, System::String^ delimiter){
	int i = 0, j = 0, pos = 0;
	System::String^ token;
	str = str->Trim();
	while ((pos = str->IndexOf(delimiter)) > 0) {
		token = str->Substring(0, pos);
		//Console::WriteLine("{0},{1} ", i,j);
		DataView->Rows[j]->Cells[i]->Value = token;
		i++;
		if (i == DataView->Columns->Count){
			j++;
			i = 0;
		}

		str = str->Substring(pos + delimiter->Length);
	}

}
void disp(float * rot, int row, int col){
	for (int i = row*col; i > 0; i--){
		printf("%1.2f,", rot[row*col - i]);
		if (i%col == 1) printf("\n");
	}
	printf("\n");
}
void disp(float * rot, int row, int col, char * name){
	printf(name);
	printf("\n");
	disp(rot, row, col);
}


void compoundTrans(float* eeRot, float* toolRot, float* rot){
	*(rot + 0) = *(eeRot + 0)**(toolRot + 0) + *(eeRot + 1)**(toolRot + 4) + *(eeRot + 2)**(toolRot + 8);
	*(rot + 1) = *(eeRot + 0)**(toolRot + 1) + *(eeRot + 1)**(toolRot + 5) + *(eeRot + 2)**(toolRot + 9);
	*(rot + 2) = *(eeRot + 0)**(toolRot + 2) + *(eeRot + 1)**(toolRot + 6) + *(eeRot + 2)**(toolRot + 10);
	*(rot + 3) = *(eeRot + 3) + *(eeRot + 0)**(toolRot + 3) + *(eeRot + 1)**(toolRot + 7) + *(eeRot + 2)**(toolRot + 11);
	*(rot + 4) = *(eeRot + 4)**(toolRot + 0) + *(eeRot + 5)**(toolRot + 4) + *(eeRot + 6)**(toolRot + 8);
	*(rot + 5) = *(eeRot + 4)**(toolRot + 1) + *(eeRot + 5)**(toolRot + 5) + *(eeRot + 6)**(toolRot + 9);
	*(rot + 6) = *(eeRot + 4)**(toolRot + 2) + *(eeRot + 5)**(toolRot + 6) + *(eeRot + 6)**(toolRot + 10);
	*(rot + 7) = *(eeRot + 7) + *(eeRot + 4)**(toolRot + 3) + *(eeRot + 5)**(toolRot + 7) + *(eeRot + 6)**(toolRot + 11);
	*(rot + 8) = *(eeRot + 8)**(toolRot + 0) + *(eeRot + 9)**(toolRot + 4) + *(eeRot + 10)**(toolRot + 8);
	*(rot + 9) = *(eeRot + 8)**(toolRot + 1) + *(eeRot + 9)**(toolRot + 5) + *(eeRot + 10)**(toolRot + 9);
	*(rot + 10) = *(eeRot + 8)**(toolRot + 2) + *(eeRot + 9)**(toolRot + 6) + *(eeRot + 10)**(toolRot + 10);
	*(rot + 11) = *(eeRot + 11) + *(eeRot + 8)**(toolRot + 3) + *(eeRot + 9)**(toolRot + 7) + *(eeRot + 10)**(toolRot + 11);
}
void rot2angle(float* rot, float* angle){
	if (*(rot + 8) != 1 || *(rot + 8) != -1){
		*(angle + 4) = atan2(-*(rot + 8), sqrt(*(rot + 0)**(rot + 0) + *(rot + 4)**(rot + 4))); //since kuka does not provide angle larger than 180 and it gives - 180 this calculation is valid
		*(angle + 5) = atan2(*(rot + 9) / cos(*(angle + 4)), *(rot + 10) / cos(*(angle + 4)));
		*(angle + 3) = atan2(*(rot + 4) / cos(*(angle + 4)), *(rot + 0) / cos(*(angle + 4)));
	}
	else{
		*(angle + 5) = 0;
		if (*(rot + 8) == -1){
			*(angle + 4) = PI / 2;
			*(angle + 5) = *(angle + 3) + atan2(*(rot + 1), *(rot + 2));
		}
		else{
			*(angle + 4) = -PI / 2;
			*(angle + 5) = -*(angle + 3) + atan2(-*(rot + 1), -*(rot + 2));
		}
	}
	*(angle) = *(rot + 3);
	*(angle + 1) = *(rot + 7);
	*(angle + 2) = *(rot + 11);
}
void angle2rot(float* angle, float* rot){
	*(rot + 0) = cos(*(angle + 3))*cos(*(angle + 4));
	*(rot + 1) = cos(*(angle + 3))*sin(*(angle + 4))*sin(*(angle + 5)) - cos(*(angle + 5))*sin(*(angle + 3));
	*(rot + 2) = sin(*(angle + 3))*sin(*(angle + 5)) + cos(*(angle + 3))*cos(*(angle + 5))*sin(*(angle + 4));
	*(rot + 3) = *(angle);
	*(rot + 4) = cos(*(angle + 4))*sin(*(angle + 3));
	*(rot + 5) = cos(*(angle + 3))*cos(*(angle + 5)) + sin(*(angle + 3))*sin(*(angle + 4))*sin(*(angle + 5));
	*(rot + 6) = cos(*(angle + 5))*sin(*(angle + 3))*sin(*(angle + 4)) - cos(*(angle + 3))*sin(*(angle + 5));
	*(rot + 7) = *(angle + 1);
	*(rot + 8) = -sin(*(angle + 4));
	*(rot + 9) = cos(*(angle + 4))*sin(*(angle + 5));
	*(rot + 10) = cos(*(angle + 4))*cos(*(angle + 5));
	*(rot + 11) = *(angle + 2);
}

void inverseTrans(float* eeRot, float* toolRot, float* rot){
	*(rot + 0) = *(eeRot + 0)**(toolRot + 0) + *(eeRot + 1)**(toolRot + 1) + *(eeRot + 2)**(toolRot + 2);
	*(rot + 1) = *(eeRot + 0)**(toolRot + 4) + *(eeRot + 1)**(toolRot + 5) + *(eeRot + 2)**(toolRot + 6);
	*(rot + 2) = *(eeRot + 0)**(toolRot + 8) + *(eeRot + 1)**(toolRot + 9) + *(eeRot + 2)**(toolRot + 10);
	*(rot + 3) = *(eeRot + 3) - *(eeRot + 0)*(*(toolRot + 0)**(toolRot + 3) + *(toolRot + 4)**(toolRot + 7) + *(toolRot + 8)**(toolRot + 11)) - *(eeRot + 1)*(*(toolRot + 1)**(toolRot + 3) + *(toolRot + 5)**(toolRot + 7) + *(toolRot + 9)**(toolRot + 11)) - *(eeRot + 2)*(*(toolRot + 2)**(toolRot + 3) + *(toolRot + 6)**(toolRot + 7) + *(toolRot + 10)**(toolRot + 11));
	*(rot + 4) = *(eeRot + 4)**(toolRot + 0) + *(eeRot + 5)**(toolRot + 1) + *(eeRot + 6)**(toolRot + 2);
	*(rot + 5) = *(eeRot + 4)**(toolRot + 4) + *(eeRot + 5)**(toolRot + 5) + *(eeRot + 6)**(toolRot + 6);
	*(rot + 6) = *(eeRot + 4)**(toolRot + 8) + *(eeRot + 5)**(toolRot + 9) + *(eeRot + 6)**(toolRot + 10);
	*(rot + 7) = *(eeRot + 7) - *(eeRot + 4)*(*(toolRot + 0)**(toolRot + 3) + *(toolRot + 4)**(toolRot + 7) + *(toolRot + 8)**(toolRot + 11)) - *(eeRot + 5)*(*(toolRot + 1)**(toolRot + 3) + *(toolRot + 5)**(toolRot + 7) + *(toolRot + 9)**(toolRot + 11)) - *(eeRot + 6)*(*(toolRot + 2)**(toolRot + 3) + *(toolRot + 6)**(toolRot + 7) + *(toolRot + 10)**(toolRot + 11));
	*(rot + 8) = *(eeRot + 8)**(toolRot + 0) + *(eeRot + 9)**(toolRot + 1) + *(eeRot + 10)**(toolRot + 2);
	*(rot + 9) = *(eeRot + 8)**(toolRot + 4) + *(eeRot + 9)**(toolRot + 5) + *(eeRot + 10)**(toolRot + 6);
	*(rot + 10) = *(eeRot + 8)**(toolRot + 8) + *(eeRot + 9)**(toolRot + 9) + *(eeRot + 10)**(toolRot + 10);
	*(rot + 11) = *(eeRot + 11) - *(eeRot + 8)*(*(toolRot + 0)**(toolRot + 3) + *(toolRot + 4)**(toolRot + 7) + *(toolRot + 8)**(toolRot + 11)) - *(eeRot + 9)*(*(toolRot + 1)**(toolRot + 3) + *(toolRot + 5)**(toolRot + 7) + *(toolRot + 9)**(toolRot + 11)) - *(eeRot + 10)*(*(toolRot + 2)**(toolRot + 3) + *(toolRot + 6)**(toolRot + 7) + *(toolRot + 10)**(toolRot + 11));
}

void rot2quat(float* rot, float* quat){
	*(quat + 0) = 0.5*sqrt(1 + *(rot + 0) + *(rot + 5) + *(rot + 10));
	*(quat + 1) = (*(rot + 9) - *(rot + 6)) / (4 * *(quat + 0));
	*(quat + 2) = (*(rot + 2) - *(rot + 8)) / (4 * *(quat + 0));
	*(quat + 3) = (*(rot + 4) - *(rot + 1)) / (4 * *(quat + 0));
	*(quat + 4) = *(rot + 3);
	*(quat + 5) = *(rot + 7);
	*(quat + 6) = *(rot + 11);
}
void quat2rot(float* quat, float* rot){
	*(rot + 0) = 1 - 2 * (pow(*(quat + 2), 2) + pow(*(quat + 3), 2));
	*(rot + 1) = 2 * (*(quat + 1)**(quat + 2) - *(quat + 0)**(quat + 3));
	*(rot + 2) = 2 * (*(quat + 1)**(quat + 3) + *(quat + 0)**(quat + 2));
	*(rot + 3) = *(quat + 4);
	*(rot + 4) = 2 * (*(quat + 1)**(quat + 2) + *(quat + 0)**(quat + 3));
	*(rot + 5) = 1 - 2 * (pow(*(quat + 1), 2) + pow(*(quat + 3), 2));
	*(rot + 6) = 2 * (*(quat + 2)**(quat + 3) - *(quat + 0)**(quat + 1));
	*(rot + 7) = *(quat + 5);
	*(rot + 8) = 2 * (*(quat + 1)**(quat + 3) - *(quat + 0)**(quat + 2));
	*(rot + 9) = 2 * (*(quat + 2)**(quat + 3) + *(quat + 0)**(quat + 1));
	*(rot + 10) = 1 - 2 * (pow(*(quat + 1), 2) + pow(*(quat + 2), 2));
	*(rot + 11) = *(quat + 6);
}

void rot2vec(float* rot, float* vec){
	float angle[CART_COMP];
	rot2angle(rot, angle);
	*(vec + 0) = angle[0];
	*(vec + 1) = angle[1];
	*(vec + 2) = angle[2];
	*(vec + 3) = cos(angle[5]);
	*(vec + 4) = sin(angle[5]);
	*(vec + 5) = cos(angle[4]);
	*(vec + 6) = sin(angle[4]);
	*(vec + 7) = cos(angle[3]);
	*(vec + 8) = sin(angle[3]);
}
void vec2rot(float* vec, float* rot){
	*(rot + 0) = *(vec + 7)**(vec + 5);
	*(rot + 1) = -*(vec + 8)**(vec + 3) + *(vec + 7)**(vec + 6)**(vec + 4);
	*(rot + 2) = *(vec + 4)**(vec + 8) + *(vec + 3)**(vec + 6)**(vec + 7);
	*(rot + 3) = *(vec + 0);
	*(rot + 4) = *(vec + 8)**(vec + 5);
	*(rot + 5) = *(vec + 7)**(vec + 3) + *(vec + 8)**(vec + 6)**(vec + 4);
	*(rot + 6) = -*(vec + 4)**(vec + 7) + *(vec + 3)**(vec + 6)**(vec + 8);
	*(rot + 7) = *(vec + 1);
	*(rot + 8) = -*(vec + 6);
	*(rot + 9) = *(vec + 5)**(vec + 4);
	*(rot + 10) = *(vec + 3)**(vec + 5);
	*(rot + 11) = *(vec + 2);
}
float deg2rad(float deg){
	return ((deg*PI) / 180);
}
float rad2deg(float rad){
	return ((rad * 180) / PI);
}
float mm2m(float mm){
	return (mm / 1000);
}
float m2mm(float m){
	return (m * 1000);
}
void startFri(System::ComponentModel::BackgroundWorker^ worker, tFriMsrData &msr, tFriCmdData &cmd, friRemote &friInst, bool& trajFlag, unsigned int & j, unsigned int & poseNum, char * kukaWriteCommand, float * tool, float* trg, float &speed, float *cartStiffVals,float *simulinkTrg){
	float newCartVals[FRI_CART_FRM_DIM], newForceTorqueAdd[FRI_CART_VEC], MeasuredPose[FRI_CART_FRM_DIM], toolRot[FRI_CART_FRM_DIM], trgRot[FRI_CART_FRM_DIM], toolTrgRot[FRI_CART_FRM_DIM], newCartValsQuat[QUAT], newCartValsAngle[CART_COMP], newCartValsVec[VEC], toolTrgVec[VEC], MeasuredPoseVec[VEC];
	ReflexxesAPI                *RML = NULL;
	RMLPositionInputParameters  *IP = NULL;
	RMLPositionOutputParameters *OP = NULL;
	RMLPositionFlags            Flags;
	int                         ResultValue = 0;
	unsigned int i = 0;
	RML = new ReflexxesAPI(VEC, CYCLE_TIME_IN_SECONDS);
	IP = new RMLPositionInputParameters(VEC);
	OP = new RMLPositionOutputParameters(VEC);
	while (!(worker->CancellationPending))
	{
		if (friInst.doReceiveData() >= 0)
		{
			msr = friInst.getMsrBuf();
			friInst.getCmdBuf() = cmd;
			if (msr.robot.control == FRI_CTRL_CART_IMP)
			{
				for (i = 0; i < FRI_CART_FRM_DIM; i++)
				{
					newCartVals[i] = msr.data.msrCartPos[i];
				}

				if (trajFlag) {
					if (ResultValue == ReflexxesAPI::RML_FINAL_STATE_REACHED){
						angle2rot(tool, toolRot);
						angle2rot(trg, trgRot);
						inverseTrans(trgRot, toolRot, toolTrgRot);
						rot2vec(toolTrgRot, toolTrgVec);
						//disp(toolRot, 3, 4, "tool");
						//disp(toolTrgRot, 3, 4, "target");

						for (int i = 0; i < FRI_CART_VEC; i++)
						{
							newForceTorqueAdd[i] = 0.0;
						}
						rot2vec(msr.data.msrCartPos, MeasuredPoseVec);
						for (i = 0; i < VEC; i++)
						{
							IP->TargetPositionVector->VecData[i] = (double)(toolTrgVec[i]);
							IP->CurrentPositionVector->VecData[i] = (double)(MeasuredPoseVec[i]);
							IP->MaxVelocityVector->VecData[i] = (speed * 3);
							IP->MaxAccelerationVector->VecData[i] = speed;
							IP->SelectionVector->VecData[i] = true;
						}

						//Flags.SynchronizationBehavior = RMLPositionFlags::ONLY_TIME_SYNCHRONIZATION;
						Flags.SynchronizationBehavior = RMLPositionFlags::PHASE_SYNCHRONIZATION_IF_POSSIBLE;
						//Flags.SynchronizationBehavior = RMLPositionFlags::ONLY_PHASE_SYNCHRONIZATION;
						//Flags.SynchronizationBehavior = RMLPositionFlags::NO_SYNCHRONIZATION;

						ResultValue = ReflexxesAPI::RML_WORKING;
					}

					if (ResultValue != ReflexxesAPI::RML_FINAL_STATE_REACHED && msr.intf.state == FRI_STATE_CMD && friInst.isPowerOn())
					{
						ResultValue = RML->RMLPosition(*IP
							, OP
							, Flags);
						if ((ResultValue != ReflexxesAPI::RML_WORKING) && (ResultValue != ReflexxesAPI::RML_FINAL_STATE_REACHED))
						{
							printf("CartTraj: ERROR during trajectory generation (%d).", ResultValue);
						}

						*IP->CurrentPositionVector = *OP->NewPositionVector;
						*IP->CurrentVelocityVector = *OP->NewVelocityVector;
						*IP->CurrentAccelerationVector = *OP->NewAccelerationVector;

						for (int i = 0; i < VEC; i++)
						{
							newCartValsVec[i] = (float)(OP->NewPositionVector->VecData[i]);
						}

						vec2rot(newCartValsVec, newCartVals);
						//disp(newCartVals, 3, 4, "kuka");
						//printf("mahyar:%d", ResultValue);
						rot2angle(newCartVals, newCartValsAngle);
						sprintf(kukaWriteCommand, "pose %d X: %1.2f Y: %1.2f Z: %1.2f A: %1.2f B: %1.2f C: %1.2f", j, m2mm(newCartValsAngle[0]), m2mm(newCartValsAngle[1]), m2mm(newCartValsAngle[2]), rad2deg(newCartValsAngle[3]), rad2deg(newCartValsAngle[4]), rad2deg(newCartValsAngle[5]));

					}
					if (ResultValue == ReflexxesAPI::RML_FINAL_STATE_REACHED) {
						if (j == poseNum) {
							trajFlag = false;
							j = 0;
						}
						if (j<poseNum)
							j++;
					}

				}
				friInst.doCartesianImpedanceControl(newCartVals, cartStiffVals, NULL, NULL, NULL, false);
			}
			if (msr.robot.control == FRI_CTRL_POSITION || msr.robot.control == FRI_CTRL_JNT_IMP) {
				float newJntVals[LBR_MNJ];
				for (int i = 0; i < LBR_MNJ; i++)
				{
					newJntVals[i] = msr.data.cmdJntPos[i];//friInst.getMsrCmdJntPosition()[i]+ friInst.getMsrCmdJntPositionOffset()[i];
				}

				/* Sample - if in command mode - and motor on -
				perform some sort of sinewave motion */
				if (friInst.getState() == FRI_STATE_CMD)
				{
					if (friInst.isPowerOn())
					{
						for (int i = 0; i < LBR_MNJ; i++)
						{
							// perform some sort of sine wave motion
							newJntVals[i] = msr.data.cmdJntPos[i]+simulinkTrg[i];
						}
					}
				}
				// Call to data exchange - and the like 
				//friInst.doJntImpedanceControl(newJntVals, cartStiffVals, NULL, NULL, false);
				friInst.doPositionControl(newJntVals,false);
			}
			friInst.doSendData();
			worker->ReportProgress(friInst.getSequenceCount() % 90 + 10);
		}
		else
		{
			worker->ReportProgress(0);
		}
	}
}
float * rot2angle(float* rot){
	float angle[CULUMNS];
	rot2angle(rot, angle);
	return angle;
}
float * angle2rot(float* angle){
	float kukaRot[ELEMENTS];
	angle2rot(angle, kukaRot);
	return kukaRot;
}
