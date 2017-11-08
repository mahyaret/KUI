//  ---------------------- Doxygen info ----------------------
//! \file mainForm.cpp
//!
//! \brief
//! Implementation file for the graphical user interface (GUI)
//!
//! \details
//! Implementation file for all definitions related to the graphical user interface, 
//! initialization, and events method.
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

#pragma once
#include <string>
#include <defs.h>
#include "stdafx.h"
#include <FRIRemote.h>
#include <FRIUdp.cpp>
#include <FRIRemote.cpp>
#include <ReflexxesAPI.h>
#include <RMLPositionFlags.h>
#include <RMLPositionInputParameters.h>
#include <RMLPositionOutputParameters.h>
#include <NIDAQmx.h>
#include <functionsNi.h>
#include <phidget21.h>
#include <functionsPhidgets.h>
#include <functionsAti.h>
#include <functionsSimulink.h>
#include <functions.h>

namespace GuiCartTrajGrp {
	tFriMsrData msr;
	tFriCmdData cmd;
	friRemote friInst;

	TaskHandle  tsk = 0;
	niVec recVec, command;

	CPhidgetBridgeHandle bridge;
	phidgetsVec phiVec;

	atiVec atiVector;
	int comPort = 3;

	float NiPID[5];
	float calMatrix[CALMAT];
	float calibratedPhidgets[LOADCELLS];
	float ee[CART_COMP], eeRot[FRI_CART_FRM_DIM], toolRot[FRI_CART_FRM_DIM];

	bool trajFlag = false, phidgetsFlag = false;
	char kukaWriteCommand[80];
	float trg[CART_COMP], tool[CART_COMP], speed, stiff[CART_COMP], simulinkTrg[LBR_MNJ];
	unsigned int i = 0, j = 0, poseNum = 0;
	unsigned char cyclecounter = 3;

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	/// <summary>
	/// Summary for mainForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
    protected:
	private: System::ComponentModel::BackgroundWorker^  FRIThread;
	private: System::Windows::Forms::Button^  startStop;
	private: System::Windows::Forms::Label^  Quality;
	private: System::Windows::Forms::Label^  Motor;
	private: System::Windows::Forms::Label^  FRIState;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  testBoxStatistics;
	private: System::Windows::Forms::Label^  FRICtrlModeLabel;
	private: System::Windows::Forms::ProgressBar^  FRI_Life;
	private: System::Windows::Forms::SaveFileDialog^  saveLogFile;
	private: System::Windows::Forms::Button^  btnLogging;
	private: System::Windows::Forms::TextBox^  txtAdr;
	private: System::Windows::Forms::Button^  btnLog;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  lblTrackC;
	private: System::Windows::Forms::Label^  lblTrackB;
	private: System::Windows::Forms::Label^  lblTrackA;
	private: System::Windows::Forms::Label^  lblTrackZ;
	private: System::Windows::Forms::Label^  lblTrackY;
	private: System::Windows::Forms::Label^  lblTrackX;
	private: System::Windows::Forms::DataGridView^  msrCartPosDataView;
	private: System::Windows::Forms::Button^  btnGo;
	private: System::Windows::Forms::Label^  lblX;
	private: System::Windows::Forms::Label^  lblY;
	private: System::Windows::Forms::Label^  lblZ;
	private: System::Windows::Forms::Label^  lblA;
	private: System::Windows::Forms::Label^  lblB;
	private: System::Windows::Forms::Label^  lblC;
	private: System::Windows::Forms::Label^  lblSpeed;
	private: System::Windows::Forms::TrackBar^  trackBarSpeed;
	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Button^  btnSub;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnAbout;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  lblToolCMon;
	private: System::Windows::Forms::Label^  lblToolCm;
	private: System::Windows::Forms::Label^  lblToolBMon;
	private: System::Windows::Forms::Label^  lblToolBm;
	private: System::Windows::Forms::Label^  lblToolAMon;
	private: System::Windows::Forms::Label^  lblToolAm;
	private: System::Windows::Forms::Label^  lblToolZMon;
	private: System::Windows::Forms::Label^  lblToolZm;
	private: System::Windows::Forms::Label^  lblToolYMon;
	private: System::Windows::Forms::Label^  lblToolYm;
	private: System::Windows::Forms::Label^  lblToolXMon;
	private: System::Windows::Forms::Label^  lblToolXm;
	private: System::Windows::Forms::Button^  btnSaveTool;
	private: System::Windows::Forms::DataGridView^  toolDataView;
	private: System::Windows::Forms::Button^  btnRst;
	private: System::Windows::Forms::Button^  btnStartStopNi;
	private: System::Windows::Forms::Button^  btnOpenGripper;
	private: System::Windows::Forms::Button^  btnCloseGripper;
	private: System::Windows::Forms::Label^  lblPosition;
	private: System::ComponentModel::BackgroundWorker^  FRILogging;
	private: System::Windows::Forms::Button^  btnStartStopPhidgets;
	private: System::ComponentModel::BackgroundWorker^  phidgets;
	private: System::ComponentModel::BackgroundWorker^  atiSensor;
	private: System::ComponentModel::BackgroundWorker^  simulink;
	private: System::Windows::Forms::GroupBox^  grpNi;
	private: System::Windows::Forms::Label^  lblPositionLabel;
	private: System::Windows::Forms::GroupBox^  grpFri;
	private: System::Windows::Forms::GroupBox^  grpLoadCells;
	private: System::Windows::Forms::Label^  lblCh3;
	private: System::Windows::Forms::Label^  lblCh3Label;
	private: System::Windows::Forms::Label^  lblCh2;
	private: System::Windows::Forms::Label^  lblCh2Label;
	private: System::Windows::Forms::Label^  lblCh1;
	protected: System::Windows::Forms::Label^  lblCh1Label;
	private:
	private: System::Windows::Forms::Label^  lblCh0;
	protected:
	private: System::Windows::Forms::Label^  lblCh0Label;
	private: System::Windows::Forms::Label^  lblFreq;
	private: System::Windows::Forms::Label^  lblFreqLabel;
	private: System::Windows::Forms::Label^  lblFreqNi;
	private: System::Windows::Forms::Label^  lblFreqNiLabel;
	private: System::Windows::Forms::Button^  btnSaveClibration;
	private: System::Windows::Forms::DataGridView^  calDataView;




	private: System::Windows::Forms::GroupBox^  grpATI;
	private: System::Windows::Forms::Label^  lblTz;
	private: System::Windows::Forms::Label^  lblTy;
	private: System::Windows::Forms::Label^  lblTx;
	private: System::Windows::Forms::Label^  lblLabelTz;
	private: System::Windows::Forms::Label^  lblLabelTy;
	private: System::Windows::Forms::Label^  lblLabelTx;
	private: System::Windows::Forms::Label^  lblFreqATI;
	private: System::Windows::Forms::Label^  lblFreqATIlabel;
	private: System::Windows::Forms::Label^  lblFz;
	private: System::Windows::Forms::Label^  lblFy;
	private: System::Windows::Forms::Label^  lblFx;
	private: System::Windows::Forms::Label^  lblLabelFz;
	private: System::Windows::Forms::Label^  lblLabelFy;
	private: System::Windows::Forms::Label^  lblLabelFx;
	private: System::Windows::Forms::Button^  btnStartATI;
	private: System::Windows::Forms::TextBox^  txtCom;
	private: System::Windows::Forms::Label^  lblComLabel;
	private: System::Windows::Forms::Button^  btnBias;
	private: System::Windows::Forms::TextBox^  txtMaxForce;
	private: System::Windows::Forms::Label^  lblMaxForceLabel;
	private: System::Windows::Forms::TextBox^  txtMaxPos;
	private: System::Windows::Forms::Label^  lblMaxPosLabel;













	private: System::Windows::Forms::Button^  btnPose;
	private: System::Windows::Forms::OpenFileDialog^  openPoseFile;
	private: System::Windows::Forms::CheckBox^  chkManual;
	private: System::Windows::Forms::Label^  lblCurrentLabel;
	private: System::Windows::Forms::TrackBar^  trackBarCurrent;
	private: System::Windows::Forms::GroupBox^  grpLog;
	private: System::Windows::Forms::GroupBox^  grpSimulink;
	private: System::Windows::Forms::Button^  btnSimulinkStart;
	private: System::Windows::Forms::Button^  btnPIDSave;
	private: System::Windows::Forms::DataGridView^  PIDDataView;





	private: System::Windows::Forms::CheckBox^  chkLoop;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewX;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewY;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewZ;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewA;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewB;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewC;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  msrCartPosDataViewOpenClose;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewX;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewY;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewZ;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewA;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewB;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  toolDataViewC;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PIDDataViewLoadCell;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PIDDataViewKp;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PIDDataViewKd;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PIDDataViewKi;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  PIDDataViewQ;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  calDataViewLoadCell0;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  calDataViewLoadCell1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  calDataViewLoadCell2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  calDataViewLoadCell3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  calDataViewSerialNumber;











































	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->FRIThread = (gcnew System::ComponentModel::BackgroundWorker());
			this->startStop = (gcnew System::Windows::Forms::Button());
			this->Quality = (gcnew System::Windows::Forms::Label());
			this->Motor = (gcnew System::Windows::Forms::Label());
			this->FRIState = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->FRICtrlModeLabel = (gcnew System::Windows::Forms::Label());
			this->testBoxStatistics = (gcnew System::Windows::Forms::TextBox());
			this->FRI_Life = (gcnew System::Windows::Forms::ProgressBar());
			this->saveLogFile = (gcnew System::Windows::Forms::SaveFileDialog());
			this->FRILogging = (gcnew System::ComponentModel::BackgroundWorker());
			this->ni = (gcnew System::ComponentModel::BackgroundWorker());
			this->phidgets = (gcnew System::ComponentModel::BackgroundWorker());
			this->atiSensor = (gcnew System::ComponentModel::BackgroundWorker());
			this->simulink = (gcnew System::ComponentModel::BackgroundWorker());
			this->btnLogging = (gcnew System::Windows::Forms::Button());
			this->txtAdr = (gcnew System::Windows::Forms::TextBox());
			this->btnLog = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->lblC = (gcnew System::Windows::Forms::Label());
			this->lblB = (gcnew System::Windows::Forms::Label());
			this->lblA = (gcnew System::Windows::Forms::Label());
			this->lblZ = (gcnew System::Windows::Forms::Label());
			this->lblTrackC = (gcnew System::Windows::Forms::Label());
			this->lblTrackZ = (gcnew System::Windows::Forms::Label());
			this->lblY = (gcnew System::Windows::Forms::Label());
			this->lblTrackY = (gcnew System::Windows::Forms::Label());
			this->lblTrackB = (gcnew System::Windows::Forms::Label());
			this->lblX = (gcnew System::Windows::Forms::Label());
			this->lblTrackX = (gcnew System::Windows::Forms::Label());
			this->lblTrackA = (gcnew System::Windows::Forms::Label());
			this->msrCartPosDataView = (gcnew System::Windows::Forms::DataGridView());
			this->msrCartPosDataViewX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewA = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewB = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewC = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->msrCartPosDataViewOpenClose = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnGo = (gcnew System::Windows::Forms::Button());
			this->lblSpeed = (gcnew System::Windows::Forms::Label());
			this->trackBarSpeed = (gcnew System::Windows::Forms::TrackBar());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnSub = (gcnew System::Windows::Forms::Button());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnAbout = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lblToolCMon = (gcnew System::Windows::Forms::Label());
			this->lblToolCm = (gcnew System::Windows::Forms::Label());
			this->lblToolBMon = (gcnew System::Windows::Forms::Label());
			this->lblToolBm = (gcnew System::Windows::Forms::Label());
			this->lblToolAMon = (gcnew System::Windows::Forms::Label());
			this->lblToolAm = (gcnew System::Windows::Forms::Label());
			this->lblToolZMon = (gcnew System::Windows::Forms::Label());
			this->lblToolZm = (gcnew System::Windows::Forms::Label());
			this->lblToolYMon = (gcnew System::Windows::Forms::Label());
			this->lblToolYm = (gcnew System::Windows::Forms::Label());
			this->lblToolXMon = (gcnew System::Windows::Forms::Label());
			this->lblToolXm = (gcnew System::Windows::Forms::Label());
			this->btnSaveTool = (gcnew System::Windows::Forms::Button());
			this->toolDataView = (gcnew System::Windows::Forms::DataGridView());
			this->toolDataViewX = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolDataViewY = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolDataViewZ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolDataViewA = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolDataViewB = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->toolDataViewC = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnRst = (gcnew System::Windows::Forms::Button());
			this->btnStartStopNi = (gcnew System::Windows::Forms::Button());
			this->btnOpenGripper = (gcnew System::Windows::Forms::Button());
			this->btnCloseGripper = (gcnew System::Windows::Forms::Button());
			this->lblPosition = (gcnew System::Windows::Forms::Label());
			this->btnStartStopPhidgets = (gcnew System::Windows::Forms::Button());
			this->grpNi = (gcnew System::Windows::Forms::GroupBox());
			this->PIDDataView = (gcnew System::Windows::Forms::DataGridView());
			this->PIDDataViewLoadCell = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PIDDataViewKp = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PIDDataViewKd = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PIDDataViewKi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PIDDataViewQ = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnPIDSave = (gcnew System::Windows::Forms::Button());
			this->lblCurrentLabel = (gcnew System::Windows::Forms::Label());
			this->chkManual = (gcnew System::Windows::Forms::CheckBox());
			this->trackBarCurrent = (gcnew System::Windows::Forms::TrackBar());
			this->txtMaxPos = (gcnew System::Windows::Forms::TextBox());
			this->lblMaxPosLabel = (gcnew System::Windows::Forms::Label());
			this->txtMaxForce = (gcnew System::Windows::Forms::TextBox());
			this->lblMaxForceLabel = (gcnew System::Windows::Forms::Label());
			this->lblFreqNi = (gcnew System::Windows::Forms::Label());
			this->lblFreqNiLabel = (gcnew System::Windows::Forms::Label());
			this->lblPositionLabel = (gcnew System::Windows::Forms::Label());
			this->grpFri = (gcnew System::Windows::Forms::GroupBox());
			this->chkLoop = (gcnew System::Windows::Forms::CheckBox());
			this->btnPose = (gcnew System::Windows::Forms::Button());
			this->grpLoadCells = (gcnew System::Windows::Forms::GroupBox());
			this->btnSaveClibration = (gcnew System::Windows::Forms::Button());
			this->calDataView = (gcnew System::Windows::Forms::DataGridView());
			this->calDataViewLoadCell0 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->calDataViewLoadCell1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->calDataViewLoadCell2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->calDataViewLoadCell3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->calDataViewSerialNumber = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->lblFreq = (gcnew System::Windows::Forms::Label());
			this->lblFreqLabel = (gcnew System::Windows::Forms::Label());
			this->lblCh3 = (gcnew System::Windows::Forms::Label());
			this->lblCh3Label = (gcnew System::Windows::Forms::Label());
			this->lblCh2 = (gcnew System::Windows::Forms::Label());
			this->lblCh2Label = (gcnew System::Windows::Forms::Label());
			this->lblCh1 = (gcnew System::Windows::Forms::Label());
			this->lblCh1Label = (gcnew System::Windows::Forms::Label());
			this->lblCh0 = (gcnew System::Windows::Forms::Label());
			this->lblCh0Label = (gcnew System::Windows::Forms::Label());
			this->grpATI = (gcnew System::Windows::Forms::GroupBox());
			this->btnBias = (gcnew System::Windows::Forms::Button());
			this->txtCom = (gcnew System::Windows::Forms::TextBox());
			this->lblComLabel = (gcnew System::Windows::Forms::Label());
			this->lblTz = (gcnew System::Windows::Forms::Label());
			this->lblTy = (gcnew System::Windows::Forms::Label());
			this->lblTx = (gcnew System::Windows::Forms::Label());
			this->lblLabelTz = (gcnew System::Windows::Forms::Label());
			this->lblLabelTy = (gcnew System::Windows::Forms::Label());
			this->lblLabelTx = (gcnew System::Windows::Forms::Label());
			this->lblFreqATI = (gcnew System::Windows::Forms::Label());
			this->lblFreqATIlabel = (gcnew System::Windows::Forms::Label());
			this->lblFz = (gcnew System::Windows::Forms::Label());
			this->lblFy = (gcnew System::Windows::Forms::Label());
			this->lblFx = (gcnew System::Windows::Forms::Label());
			this->lblLabelFz = (gcnew System::Windows::Forms::Label());
			this->lblLabelFy = (gcnew System::Windows::Forms::Label());
			this->lblLabelFx = (gcnew System::Windows::Forms::Label());
			this->btnStartATI = (gcnew System::Windows::Forms::Button());
			this->openPoseFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->grpLog = (gcnew System::Windows::Forms::GroupBox());
			this->grpSimulink = (gcnew System::Windows::Forms::GroupBox());
			this->btnSimulinkStart = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->msrCartPosDataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpeed))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->toolDataView))->BeginInit();
			this->grpNi->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIDDataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarCurrent))->BeginInit();
			this->grpFri->SuspendLayout();
			this->grpLoadCells->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->calDataView))->BeginInit();
			this->grpATI->SuspendLayout();
			this->grpLog->SuspendLayout();
			this->grpSimulink->SuspendLayout();
			this->SuspendLayout();
			// 
			// FRIThread
			// 
			this->FRIThread->WorkerReportsProgress = true;
			this->FRIThread->WorkerSupportsCancellation = true;
			this->FRIThread->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::FRIThread_DoWork);
			this->FRIThread->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &mainForm::FRIThread_ProgressChanged);
			// 
			// startStop
			// 
			this->startStop->Location = System::Drawing::Point(4, 17);
			this->startStop->Margin = System::Windows::Forms::Padding(2);
			this->startStop->Name = L"startStop";
			this->startStop->Size = System::Drawing::Size(76, 26);
			this->startStop->TabIndex = 1;
			this->startStop->Text = L"startStopFRI";
			this->startStop->UseVisualStyleBackColor = true;
			this->startStop->Click += gcnew System::EventHandler(this, &mainForm::button1_Click);
			// 
			// Quality
			// 
			this->Quality->AutoSize = true;
			this->Quality->Location = System::Drawing::Point(11, 13);
			this->Quality->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Quality->Name = L"Quality";
			this->Quality->Size = System::Drawing::Size(39, 13);
			this->Quality->TabIndex = 3;
			this->Quality->Text = L"Quality";
			// 
			// Motor
			// 
			this->Motor->AutoSize = true;
			this->Motor->Location = System::Drawing::Point(69, 13);
			this->Motor->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->Motor->Name = L"Motor";
			this->Motor->Size = System::Drawing::Size(34, 13);
			this->Motor->TabIndex = 4;
			this->Motor->Text = L"Motor";
			// 
			// FRIState
			// 
			this->FRIState->AutoSize = true;
			this->FRIState->Location = System::Drawing::Point(122, 13);
			this->FRIState->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->FRIState->Name = L"FRIState";
			this->FRIState->Size = System::Drawing::Size(49, 13);
			this->FRIState->TabIndex = 5;
			this->FRIState->Text = L"FRIState";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->FRICtrlModeLabel);
			this->groupBox1->Controls->Add(this->Quality);
			this->groupBox1->Controls->Add(this->Motor);
			this->groupBox1->Controls->Add(this->FRIState);
			this->groupBox1->Location = System::Drawing::Point(90, 12);
			this->groupBox1->Margin = System::Windows::Forms::Padding(2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(2);
			this->groupBox1->Size = System::Drawing::Size(260, 31);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"status";
			// 
			// FRICtrlModeLabel
			// 
			this->FRICtrlModeLabel->AutoSize = true;
			this->FRICtrlModeLabel->Location = System::Drawing::Point(176, 13);
			this->FRICtrlModeLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->FRICtrlModeLabel->Name = L"FRICtrlModeLabel";
			this->FRICtrlModeLabel->Size = System::Drawing::Size(79, 13);
			this->FRICtrlModeLabel->TabIndex = 6;
			this->FRICtrlModeLabel->Text = L"FRICTRLMode";
			// 
			// testBoxStatistics
			// 
			this->testBoxStatistics->Location = System::Drawing::Point(390, 12);
			this->testBoxStatistics->Margin = System::Windows::Forms::Padding(2);
			this->testBoxStatistics->Multiline = true;
			this->testBoxStatistics->Name = L"testBoxStatistics";
			this->testBoxStatistics->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->testBoxStatistics->Size = System::Drawing::Size(373, 192);
			this->testBoxStatistics->TabIndex = 8;
			// 
			// FRI_Life
			// 
			this->FRI_Life->Location = System::Drawing::Point(4, 47);
			this->FRI_Life->Margin = System::Windows::Forms::Padding(2);
			this->FRI_Life->Name = L"FRI_Life";
			this->FRI_Life->Size = System::Drawing::Size(76, 15);
			this->FRI_Life->TabIndex = 19;
			// 
			// FRILogging
			// 
			this->FRILogging->WorkerReportsProgress = true;
			this->FRILogging->WorkerSupportsCancellation = true;
			this->FRILogging->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::FRILogging_DoWork);
			// 
			// ni
			// 
			this->ni->WorkerReportsProgress = true;
			this->ni->WorkerSupportsCancellation = true;
			this->ni->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::ni_DoWork);
			this->ni->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &mainForm::ni_ProgressChanged);
			// 
			// phidgets
			// 
			this->phidgets->WorkerReportsProgress = true;
			this->phidgets->WorkerSupportsCancellation = true;
			this->phidgets->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::phidgets_DoWork);
			this->phidgets->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &mainForm::phidgets_ProgressChanged);
			// 
			// atiSensor
			// 
			this->atiSensor->WorkerReportsProgress = true;
			this->atiSensor->WorkerSupportsCancellation = true;
			this->atiSensor->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::atiSensor_DoWork);
			this->atiSensor->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &mainForm::atiSensor_ProgressChanged);
			// 
			// simulink
			// 
			this->simulink->WorkerReportsProgress = true;
			this->simulink->WorkerSupportsCancellation = true;
			this->simulink->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &mainForm::simulink_DoWork);
			this->simulink->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &mainForm::simulink_ProgressChanged);
			// 
			// btnLogging
			// 
			this->btnLogging->Location = System::Drawing::Point(191, 48);
			this->btnLogging->Name = L"btnLogging";
			this->btnLogging->Size = System::Drawing::Size(99, 27);
			this->btnLogging->TabIndex = 31;
			this->btnLogging->Text = L"Start Logging";
			this->btnLogging->UseVisualStyleBackColor = true;
			this->btnLogging->Click += gcnew System::EventHandler(this, &mainForm::btnLogging_Click);
			// 
			// txtAdr
			// 
			this->txtAdr->Location = System::Drawing::Point(6, 19);
			this->txtAdr->Name = L"txtAdr";
			this->txtAdr->Size = System::Drawing::Size(179, 20);
			this->txtAdr->TabIndex = 30;
			this->txtAdr->Text = L"log.txt";
			// 
			// btnLog
			// 
			this->btnLog->Location = System::Drawing::Point(191, 15);
			this->btnLog->Name = L"btnLog";
			this->btnLog->Size = System::Drawing::Size(99, 27);
			this->btnLog->TabIndex = 29;
			this->btnLog->Text = L"Change Path";
			this->btnLog->UseVisualStyleBackColor = true;
			this->btnLog->Click += gcnew System::EventHandler(this, &mainForm::btnLog_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->lblC);
			this->groupBox3->Controls->Add(this->lblB);
			this->groupBox3->Controls->Add(this->lblA);
			this->groupBox3->Controls->Add(this->lblZ);
			this->groupBox3->Controls->Add(this->lblTrackC);
			this->groupBox3->Controls->Add(this->lblTrackZ);
			this->groupBox3->Controls->Add(this->lblY);
			this->groupBox3->Controls->Add(this->lblTrackY);
			this->groupBox3->Controls->Add(this->lblTrackB);
			this->groupBox3->Controls->Add(this->lblX);
			this->groupBox3->Controls->Add(this->lblTrackX);
			this->groupBox3->Controls->Add(this->lblTrackA);
			this->groupBox3->Location = System::Drawing::Point(4, 67);
			this->groupBox3->Margin = System::Windows::Forms::Padding(2);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(2);
			this->groupBox3->Size = System::Drawing::Size(189, 102);
			this->groupBox3->TabIndex = 28;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"CartPose";
			// 
			// lblC
			// 
			this->lblC->AutoSize = true;
			this->lblC->Location = System::Drawing::Point(78, 80);
			this->lblC->Name = L"lblC";
			this->lblC->Size = System::Drawing::Size(0, 13);
			this->lblC->TabIndex = 43;
			// 
			// lblB
			// 
			this->lblB->AutoSize = true;
			this->lblB->Location = System::Drawing::Point(78, 67);
			this->lblB->Name = L"lblB";
			this->lblB->Size = System::Drawing::Size(0, 13);
			this->lblB->TabIndex = 42;
			// 
			// lblA
			// 
			this->lblA->AutoSize = true;
			this->lblA->Location = System::Drawing::Point(78, 54);
			this->lblA->Name = L"lblA";
			this->lblA->Size = System::Drawing::Size(0, 13);
			this->lblA->TabIndex = 41;
			// 
			// lblZ
			// 
			this->lblZ->AutoSize = true;
			this->lblZ->Location = System::Drawing::Point(78, 41);
			this->lblZ->Name = L"lblZ";
			this->lblZ->Size = System::Drawing::Size(0, 13);
			this->lblZ->TabIndex = 40;
			// 
			// lblTrackC
			// 
			this->lblTrackC->AutoSize = true;
			this->lblTrackC->Location = System::Drawing::Point(5, 80);
			this->lblTrackC->Name = L"lblTrackC";
			this->lblTrackC->Size = System::Drawing::Size(41, 13);
			this->lblTrackC->TabIndex = 26;
			this->lblTrackC->Text = L"C (deg)";
			// 
			// lblTrackZ
			// 
			this->lblTrackZ->AutoSize = true;
			this->lblTrackZ->Location = System::Drawing::Point(5, 41);
			this->lblTrackZ->Name = L"lblTrackZ";
			this->lblTrackZ->Size = System::Drawing::Size(39, 13);
			this->lblTrackZ->TabIndex = 23;
			this->lblTrackZ->Text = L"Z (mm)";
			// 
			// lblY
			// 
			this->lblY->AutoSize = true;
			this->lblY->Location = System::Drawing::Point(78, 28);
			this->lblY->Name = L"lblY";
			this->lblY->Size = System::Drawing::Size(0, 13);
			this->lblY->TabIndex = 39;
			// 
			// lblTrackY
			// 
			this->lblTrackY->AutoSize = true;
			this->lblTrackY->Location = System::Drawing::Point(5, 28);
			this->lblTrackY->Name = L"lblTrackY";
			this->lblTrackY->Size = System::Drawing::Size(39, 13);
			this->lblTrackY->TabIndex = 22;
			this->lblTrackY->Text = L"Y (mm)";
			// 
			// lblTrackB
			// 
			this->lblTrackB->AutoSize = true;
			this->lblTrackB->Location = System::Drawing::Point(5, 67);
			this->lblTrackB->Name = L"lblTrackB";
			this->lblTrackB->Size = System::Drawing::Size(41, 13);
			this->lblTrackB->TabIndex = 25;
			this->lblTrackB->Text = L"B (deg)";
			// 
			// lblX
			// 
			this->lblX->AutoSize = true;
			this->lblX->Location = System::Drawing::Point(78, 15);
			this->lblX->Name = L"lblX";
			this->lblX->Size = System::Drawing::Size(0, 13);
			this->lblX->TabIndex = 38;
			// 
			// lblTrackX
			// 
			this->lblTrackX->AutoSize = true;
			this->lblTrackX->Location = System::Drawing::Point(5, 15);
			this->lblTrackX->Name = L"lblTrackX";
			this->lblTrackX->Size = System::Drawing::Size(39, 13);
			this->lblTrackX->TabIndex = 21;
			this->lblTrackX->Text = L"X (mm)";
			// 
			// lblTrackA
			// 
			this->lblTrackA->AutoSize = true;
			this->lblTrackA->Location = System::Drawing::Point(5, 54);
			this->lblTrackA->Name = L"lblTrackA";
			this->lblTrackA->Size = System::Drawing::Size(41, 13);
			this->lblTrackA->TabIndex = 24;
			this->lblTrackA->Text = L"A (deg)";
			// 
			// msrCartPosDataView
			// 
			this->msrCartPosDataView->AllowUserToAddRows = false;
			this->msrCartPosDataView->AllowUserToDeleteRows = false;
			this->msrCartPosDataView->AllowUserToResizeColumns = false;
			this->msrCartPosDataView->AllowUserToResizeRows = false;
			this->msrCartPosDataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->msrCartPosDataView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->msrCartPosDataView->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->msrCartPosDataView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->msrCartPosDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->msrCartPosDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {
				this->msrCartPosDataViewX,
					this->msrCartPosDataViewY, this->msrCartPosDataViewZ, this->msrCartPosDataViewA, this->msrCartPosDataViewB, this->msrCartPosDataViewC,
					this->msrCartPosDataViewOpenClose
			});
			this->msrCartPosDataView->Location = System::Drawing::Point(4, 282);
			this->msrCartPosDataView->Margin = System::Windows::Forms::Padding(2);
			this->msrCartPosDataView->Name = L"msrCartPosDataView";
			this->msrCartPosDataView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->msrCartPosDataView->RowTemplate->Height = 28;
			this->msrCartPosDataView->Size = System::Drawing::Size(759, 114);
			this->msrCartPosDataView->TabIndex = 27;
			// 
			// msrCartPosDataViewX
			// 
			this->msrCartPosDataViewX->HeaderText = L"X (mm)";
			this->msrCartPosDataViewX->Name = L"msrCartPosDataViewX";
			this->msrCartPosDataViewX->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewY
			// 
			this->msrCartPosDataViewY->HeaderText = L"Y (mm)";
			this->msrCartPosDataViewY->Name = L"msrCartPosDataViewY";
			this->msrCartPosDataViewY->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewZ
			// 
			this->msrCartPosDataViewZ->HeaderText = L"Z (mm)";
			this->msrCartPosDataViewZ->Name = L"msrCartPosDataViewZ";
			this->msrCartPosDataViewZ->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewA
			// 
			this->msrCartPosDataViewA->HeaderText = L"A (deg)";
			this->msrCartPosDataViewA->Name = L"msrCartPosDataViewA";
			this->msrCartPosDataViewA->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewB
			// 
			this->msrCartPosDataViewB->HeaderText = L"B (deg)";
			this->msrCartPosDataViewB->Name = L"msrCartPosDataViewB";
			this->msrCartPosDataViewB->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewC
			// 
			this->msrCartPosDataViewC->HeaderText = L"C (deg)";
			this->msrCartPosDataViewC->Name = L"msrCartPosDataViewC";
			this->msrCartPosDataViewC->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// msrCartPosDataViewOpenClose
			// 
			this->msrCartPosDataViewOpenClose->HeaderText = L"open/close";
			this->msrCartPosDataViewOpenClose->Name = L"msrCartPosDataViewOpenClose";
			this->msrCartPosDataViewOpenClose->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// btnGo
			// 
			this->btnGo->Location = System::Drawing::Point(4, 174);
			this->btnGo->Name = L"btnGo";
			this->btnGo->Size = System::Drawing::Size(130, 30);
			this->btnGo->TabIndex = 25;
			this->btnGo->Text = L"Go!";
			this->btnGo->UseVisualStyleBackColor = true;
			this->btnGo->Click += gcnew System::EventHandler(this, &mainForm::btnGo_Click);
			// 
			// lblSpeed
			// 
			this->lblSpeed->AutoSize = true;
			this->lblSpeed->Location = System::Drawing::Point(140, 183);
			this->lblSpeed->Name = L"lblSpeed";
			this->lblSpeed->Size = System::Drawing::Size(38, 13);
			this->lblSpeed->TabIndex = 32;
			this->lblSpeed->Text = L"Speed";
			// 
			// trackBarSpeed
			// 
			this->trackBarSpeed->Location = System::Drawing::Point(173, 173);
			this->trackBarSpeed->Maximum = 4;
			this->trackBarSpeed->Minimum = 1;
			this->trackBarSpeed->Name = L"trackBarSpeed";
			this->trackBarSpeed->Size = System::Drawing::Size(78, 45);
			this->trackBarSpeed->TabIndex = 33;
			this->trackBarSpeed->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBarSpeed->Value = 2;
			// 
			// btnAdd
			// 
			this->btnAdd->Location = System::Drawing::Point(91, 247);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(30, 30);
			this->btnAdd->TabIndex = 34;
			this->btnAdd->Text = L"+";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &mainForm::btnAdd_Click);
			// 
			// btnSub
			// 
			this->btnSub->Location = System::Drawing::Point(127, 247);
			this->btnSub->Name = L"btnSub";
			this->btnSub->Size = System::Drawing::Size(30, 30);
			this->btnSub->TabIndex = 35;
			this->btnSub->Text = L"-";
			this->btnSub->UseVisualStyleBackColor = true;
			this->btnSub->Click += gcnew System::EventHandler(this, &mainForm::btnSub_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(163, 247);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(81, 30);
			this->btnSave->TabIndex = 37;
			this->btnSave->Text = L"Save Pose";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &mainForm::btnSave_Click);
			// 
			// btnAbout
			// 
			this->btnAbout->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnAbout->Location = System::Drawing::Point(1121, 442);
			this->btnAbout->Margin = System::Windows::Forms::Padding(2);
			this->btnAbout->Name = L"btnAbout";
			this->btnAbout->Size = System::Drawing::Size(62, 26);
			this->btnAbout->TabIndex = 38;
			this->btnAbout->Text = L"About";
			this->btnAbout->UseVisualStyleBackColor = true;
			this->btnAbout->Click += gcnew System::EventHandler(this, &mainForm::btnAbout_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->lblToolCMon);
			this->groupBox2->Controls->Add(this->lblToolCm);
			this->groupBox2->Controls->Add(this->lblToolBMon);
			this->groupBox2->Controls->Add(this->lblToolBm);
			this->groupBox2->Controls->Add(this->lblToolAMon);
			this->groupBox2->Controls->Add(this->lblToolAm);
			this->groupBox2->Controls->Add(this->lblToolZMon);
			this->groupBox2->Controls->Add(this->lblToolZm);
			this->groupBox2->Controls->Add(this->lblToolYMon);
			this->groupBox2->Controls->Add(this->lblToolYm);
			this->groupBox2->Controls->Add(this->lblToolXMon);
			this->groupBox2->Controls->Add(this->lblToolXm);
			this->groupBox2->Location = System::Drawing::Point(197, 67);
			this->groupBox2->Margin = System::Windows::Forms::Padding(2);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(2);
			this->groupBox2->Size = System::Drawing::Size(189, 102);
			this->groupBox2->TabIndex = 39;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"ToolPose";
			// 
			// lblToolCMon
			// 
			this->lblToolCMon->AutoSize = true;
			this->lblToolCMon->Location = System::Drawing::Point(78, 80);
			this->lblToolCMon->Name = L"lblToolCMon";
			this->lblToolCMon->Size = System::Drawing::Size(0, 13);
			this->lblToolCMon->TabIndex = 43;
			// 
			// lblToolCm
			// 
			this->lblToolCm->AutoSize = true;
			this->lblToolCm->Location = System::Drawing::Point(5, 80);
			this->lblToolCm->Name = L"lblToolCm";
			this->lblToolCm->Size = System::Drawing::Size(41, 13);
			this->lblToolCm->TabIndex = 26;
			this->lblToolCm->Text = L"C (deg)";
			// 
			// lblToolBMon
			// 
			this->lblToolBMon->AutoSize = true;
			this->lblToolBMon->Location = System::Drawing::Point(78, 67);
			this->lblToolBMon->Name = L"lblToolBMon";
			this->lblToolBMon->Size = System::Drawing::Size(0, 13);
			this->lblToolBMon->TabIndex = 42;
			// 
			// lblToolBm
			// 
			this->lblToolBm->AutoSize = true;
			this->lblToolBm->Location = System::Drawing::Point(5, 67);
			this->lblToolBm->Name = L"lblToolBm";
			this->lblToolBm->Size = System::Drawing::Size(41, 13);
			this->lblToolBm->TabIndex = 25;
			this->lblToolBm->Text = L"B (deg)";
			// 
			// lblToolAMon
			// 
			this->lblToolAMon->AutoSize = true;
			this->lblToolAMon->Location = System::Drawing::Point(78, 54);
			this->lblToolAMon->Name = L"lblToolAMon";
			this->lblToolAMon->Size = System::Drawing::Size(0, 13);
			this->lblToolAMon->TabIndex = 41;
			// 
			// lblToolAm
			// 
			this->lblToolAm->AutoSize = true;
			this->lblToolAm->Location = System::Drawing::Point(5, 54);
			this->lblToolAm->Name = L"lblToolAm";
			this->lblToolAm->Size = System::Drawing::Size(41, 13);
			this->lblToolAm->TabIndex = 24;
			this->lblToolAm->Text = L"A (deg)";
			// 
			// lblToolZMon
			// 
			this->lblToolZMon->AutoSize = true;
			this->lblToolZMon->Location = System::Drawing::Point(78, 41);
			this->lblToolZMon->Name = L"lblToolZMon";
			this->lblToolZMon->Size = System::Drawing::Size(0, 13);
			this->lblToolZMon->TabIndex = 40;
			// 
			// lblToolZm
			// 
			this->lblToolZm->AutoSize = true;
			this->lblToolZm->Location = System::Drawing::Point(5, 41);
			this->lblToolZm->Name = L"lblToolZm";
			this->lblToolZm->Size = System::Drawing::Size(39, 13);
			this->lblToolZm->TabIndex = 23;
			this->lblToolZm->Text = L"Z (mm)";
			// 
			// lblToolYMon
			// 
			this->lblToolYMon->AutoSize = true;
			this->lblToolYMon->Location = System::Drawing::Point(78, 28);
			this->lblToolYMon->Name = L"lblToolYMon";
			this->lblToolYMon->Size = System::Drawing::Size(0, 13);
			this->lblToolYMon->TabIndex = 39;
			// 
			// lblToolYm
			// 
			this->lblToolYm->AutoSize = true;
			this->lblToolYm->Location = System::Drawing::Point(5, 28);
			this->lblToolYm->Name = L"lblToolYm";
			this->lblToolYm->Size = System::Drawing::Size(39, 13);
			this->lblToolYm->TabIndex = 22;
			this->lblToolYm->Text = L"Y (mm)";
			// 
			// lblToolXMon
			// 
			this->lblToolXMon->AutoSize = true;
			this->lblToolXMon->Location = System::Drawing::Point(78, 15);
			this->lblToolXMon->Name = L"lblToolXMon";
			this->lblToolXMon->Size = System::Drawing::Size(0, 13);
			this->lblToolXMon->TabIndex = 38;
			// 
			// lblToolXm
			// 
			this->lblToolXm->AutoSize = true;
			this->lblToolXm->Location = System::Drawing::Point(5, 15);
			this->lblToolXm->Name = L"lblToolXm";
			this->lblToolXm->Size = System::Drawing::Size(39, 13);
			this->lblToolXm->TabIndex = 21;
			this->lblToolXm->Text = L"X (mm)";
			// 
			// btnSaveTool
			// 
			this->btnSaveTool->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->btnSaveTool->Location = System::Drawing::Point(163, 209);
			this->btnSaveTool->Name = L"btnSaveTool";
			this->btnSaveTool->Size = System::Drawing::Size(81, 30);
			this->btnSaveTool->TabIndex = 52;
			this->btnSaveTool->Text = L"Save Tool";
			this->btnSaveTool->UseVisualStyleBackColor = true;
			this->btnSaveTool->Click += gcnew System::EventHandler(this, &mainForm::btnSaveTool_Click);
			// 
			// toolDataView
			// 
			this->toolDataView->AllowUserToAddRows = false;
			this->toolDataView->AllowUserToDeleteRows = false;
			this->toolDataView->AllowUserToResizeColumns = false;
			this->toolDataView->AllowUserToResizeRows = false;
			this->toolDataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->toolDataView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->toolDataView->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->toolDataView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->toolDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->toolDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
				this->toolDataViewX,
					this->toolDataViewY, this->toolDataViewZ, this->toolDataViewA, this->toolDataViewB, this->toolDataViewC
			});
			this->toolDataView->Location = System::Drawing::Point(256, 207);
			this->toolDataView->Margin = System::Windows::Forms::Padding(2);
			this->toolDataView->Name = L"toolDataView";
			this->toolDataView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->toolDataView->RowTemplate->Height = 28;
			this->toolDataView->Size = System::Drawing::Size(507, 71);
			this->toolDataView->TabIndex = 53;
			// 
			// toolDataViewX
			// 
			this->toolDataViewX->HeaderText = L"X (mm)";
			this->toolDataViewX->Name = L"toolDataViewX";
			this->toolDataViewX->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// toolDataViewY
			// 
			this->toolDataViewY->HeaderText = L"Y (mm)";
			this->toolDataViewY->Name = L"toolDataViewY";
			this->toolDataViewY->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// toolDataViewZ
			// 
			this->toolDataViewZ->HeaderText = L"Z (mm)";
			this->toolDataViewZ->Name = L"toolDataViewZ";
			this->toolDataViewZ->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// toolDataViewA
			// 
			this->toolDataViewA->HeaderText = L"A (deg)";
			this->toolDataViewA->Name = L"toolDataViewA";
			this->toolDataViewA->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// toolDataViewB
			// 
			this->toolDataViewB->HeaderText = L"B (deg)";
			this->toolDataViewB->Name = L"toolDataViewB";
			this->toolDataViewB->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// toolDataViewC
			// 
			this->toolDataViewC->HeaderText = L"C (deg)";
			this->toolDataViewC->Name = L"toolDataViewC";
			this->toolDataViewC->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// btnRst
			// 
			this->btnRst->Location = System::Drawing::Point(256, 174);
			this->btnRst->Name = L"btnRst";
			this->btnRst->Size = System::Drawing::Size(130, 30);
			this->btnRst->TabIndex = 54;
			this->btnRst->Text = L"Reset";
			this->btnRst->UseVisualStyleBackColor = true;
			this->btnRst->Click += gcnew System::EventHandler(this, &mainForm::btnRst_Click);
			// 
			// btnStartStopNi
			// 
			this->btnStartStopNi->Location = System::Drawing::Point(7, 17);
			this->btnStartStopNi->Margin = System::Windows::Forms::Padding(2);
			this->btnStartStopNi->Name = L"btnStartStopNi";
			this->btnStartStopNi->Size = System::Drawing::Size(76, 26);
			this->btnStartStopNi->TabIndex = 55;
			this->btnStartStopNi->Text = L"startNI";
			this->btnStartStopNi->UseVisualStyleBackColor = true;
			this->btnStartStopNi->Click += gcnew System::EventHandler(this, &mainForm::btnStartStopNi_Click);
			// 
			// btnOpenGripper
			// 
			this->btnOpenGripper->Enabled = false;
			this->btnOpenGripper->Location = System::Drawing::Point(7, 67);
			this->btnOpenGripper->Margin = System::Windows::Forms::Padding(2);
			this->btnOpenGripper->Name = L"btnOpenGripper";
			this->btnOpenGripper->Size = System::Drawing::Size(76, 26);
			this->btnOpenGripper->TabIndex = 56;
			this->btnOpenGripper->Text = L"openGripper";
			this->btnOpenGripper->UseVisualStyleBackColor = true;
			this->btnOpenGripper->Click += gcnew System::EventHandler(this, &mainForm::btnOpenGripper_Click);
			// 
			// btnCloseGripper
			// 
			this->btnCloseGripper->Enabled = false;
			this->btnCloseGripper->Location = System::Drawing::Point(7, 97);
			this->btnCloseGripper->Margin = System::Windows::Forms::Padding(2);
			this->btnCloseGripper->Name = L"btnCloseGripper";
			this->btnCloseGripper->Size = System::Drawing::Size(76, 26);
			this->btnCloseGripper->TabIndex = 57;
			this->btnCloseGripper->Text = L"closeGripper";
			this->btnCloseGripper->UseVisualStyleBackColor = true;
			this->btnCloseGripper->Click += gcnew System::EventHandler(this, &mainForm::btnCloseGripper_Click);
			// 
			// lblPosition
			// 
			this->lblPosition->AutoSize = true;
			this->lblPosition->Location = System::Drawing::Point(182, 17);
			this->lblPosition->Name = L"lblPosition";
			this->lblPosition->Size = System::Drawing::Size(0, 13);
			this->lblPosition->TabIndex = 58;
			// 
			// btnStartStopPhidgets
			// 
			this->btnStartStopPhidgets->Location = System::Drawing::Point(7, 20);
			this->btnStartStopPhidgets->Margin = System::Windows::Forms::Padding(2);
			this->btnStartStopPhidgets->Name = L"btnStartStopPhidgets";
			this->btnStartStopPhidgets->Size = System::Drawing::Size(76, 26);
			this->btnStartStopPhidgets->TabIndex = 59;
			this->btnStartStopPhidgets->Text = L"startPhidgets";
			this->btnStartStopPhidgets->UseVisualStyleBackColor = true;
			this->btnStartStopPhidgets->Click += gcnew System::EventHandler(this, &mainForm::btnStartStopPhidgets_Click);
			// 
			// grpNi
			// 
			this->grpNi->Controls->Add(this->PIDDataView);
			this->grpNi->Controls->Add(this->btnPIDSave);
			this->grpNi->Controls->Add(this->lblCurrentLabel);
			this->grpNi->Controls->Add(this->chkManual);
			this->grpNi->Controls->Add(this->trackBarCurrent);
			this->grpNi->Controls->Add(this->txtMaxPos);
			this->grpNi->Controls->Add(this->lblMaxPosLabel);
			this->grpNi->Controls->Add(this->txtMaxForce);
			this->grpNi->Controls->Add(this->lblMaxForceLabel);
			this->grpNi->Controls->Add(this->lblFreqNi);
			this->grpNi->Controls->Add(this->lblFreqNiLabel);
			this->grpNi->Controls->Add(this->lblPositionLabel);
			this->grpNi->Controls->Add(this->lblPosition);
			this->grpNi->Controls->Add(this->btnCloseGripper);
			this->grpNi->Controls->Add(this->btnOpenGripper);
			this->grpNi->Controls->Add(this->btnStartStopNi);
			this->grpNi->Location = System::Drawing::Point(776, 3);
			this->grpNi->Margin = System::Windows::Forms::Padding(2);
			this->grpNi->Name = L"grpNi";
			this->grpNi->Padding = System::Windows::Forms::Padding(2);
			this->grpNi->Size = System::Drawing::Size(407, 147);
			this->grpNi->TabIndex = 60;
			this->grpNi->TabStop = false;
			this->grpNi->Text = L"Gripper";
			// 
			// PIDDataView
			// 
			this->PIDDataView->AllowUserToAddRows = false;
			this->PIDDataView->AllowUserToDeleteRows = false;
			this->PIDDataView->AllowUserToResizeColumns = false;
			this->PIDDataView->AllowUserToResizeRows = false;
			this->PIDDataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->PIDDataView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->PIDDataView->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->PIDDataView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PIDDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->PIDDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->PIDDataViewLoadCell,
					this->PIDDataViewKp, this->PIDDataViewKd, this->PIDDataViewKi, this->PIDDataViewQ
			});
			this->PIDDataView->Location = System::Drawing::Point(90, 92);
			this->PIDDataView->Margin = System::Windows::Forms::Padding(2);
			this->PIDDataView->Name = L"PIDDataView";
			this->PIDDataView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->PIDDataView->RowTemplate->Height = 28;
			this->PIDDataView->Size = System::Drawing::Size(313, 51);
			this->PIDDataView->TabIndex = 72;
			// 
			// PIDDataViewLoadCell
			// 
			this->PIDDataViewLoadCell->HeaderText = L"Load Cell";
			this->PIDDataViewLoadCell->Name = L"PIDDataViewLoadCell";
			this->PIDDataViewLoadCell->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// PIDDataViewKp
			// 
			this->PIDDataViewKp->HeaderText = L"Kp";
			this->PIDDataViewKp->Name = L"PIDDataViewKp";
			this->PIDDataViewKp->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// PIDDataViewKd
			// 
			this->PIDDataViewKd->HeaderText = L"Kd";
			this->PIDDataViewKd->Name = L"PIDDataViewKd";
			this->PIDDataViewKd->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// PIDDataViewKi
			// 
			this->PIDDataViewKi->HeaderText = L"Ki";
			this->PIDDataViewKi->Name = L"PIDDataViewKi";
			this->PIDDataViewKi->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// PIDDataViewQ
			// 
			this->PIDDataViewQ->HeaderText = L"Q";
			this->PIDDataViewQ->Name = L"PIDDataViewQ";
			this->PIDDataViewQ->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// btnPIDSave
			// 
			this->btnPIDSave->Location = System::Drawing::Point(315, 57);
			this->btnPIDSave->Margin = System::Windows::Forms::Padding(2);
			this->btnPIDSave->Name = L"btnPIDSave";
			this->btnPIDSave->Size = System::Drawing::Size(76, 26);
			this->btnPIDSave->TabIndex = 93;
			this->btnPIDSave->Text = L"Save";
			this->btnPIDSave->UseVisualStyleBackColor = true;
			this->btnPIDSave->Click += gcnew System::EventHandler(this, &mainForm::btnPIDSave_Click);
			// 
			// lblCurrentLabel
			// 
			this->lblCurrentLabel->AutoSize = true;
			this->lblCurrentLabel->Location = System::Drawing::Point(286, 30);
			this->lblCurrentLabel->Name = L"lblCurrentLabel";
			this->lblCurrentLabel->Size = System::Drawing::Size(41, 13);
			this->lblCurrentLabel->TabIndex = 74;
			this->lblCurrentLabel->Text = L"Current";
			// 
			// chkManual
			// 
			this->chkManual->AutoSize = true;
			this->chkManual->Location = System::Drawing::Point(7, 49);
			this->chkManual->Name = L"chkManual";
			this->chkManual->Size = System::Drawing::Size(61, 17);
			this->chkManual->TabIndex = 84;
			this->chkManual->Text = L"Manual";
			this->chkManual->UseVisualStyleBackColor = true;
			this->chkManual->CheckedChanged += gcnew System::EventHandler(this, &mainForm::chkManual_CheckedChanged);
			// 
			// trackBarCurrent
			// 
			this->trackBarCurrent->Location = System::Drawing::Point(333, 22);
			this->trackBarCurrent->Maximum = 2;
			this->trackBarCurrent->Minimum = 1;
			this->trackBarCurrent->Name = L"trackBarCurrent";
			this->trackBarCurrent->Size = System::Drawing::Size(58, 45);
			this->trackBarCurrent->TabIndex = 75;
			this->trackBarCurrent->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->trackBarCurrent->Value = 2;
			// 
			// txtMaxPos
			// 
			this->txtMaxPos->Enabled = false;
			this->txtMaxPos->Location = System::Drawing::Point(168, 44);
			this->txtMaxPos->Name = L"txtMaxPos";
			this->txtMaxPos->Size = System::Drawing::Size(40, 20);
			this->txtMaxPos->TabIndex = 83;
			this->txtMaxPos->Text = L"3";
			// 
			// lblMaxPosLabel
			// 
			this->lblMaxPosLabel->AutoSize = true;
			this->lblMaxPosLabel->Enabled = false;
			this->lblMaxPosLabel->Location = System::Drawing::Point(109, 47);
			this->lblMaxPosLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblMaxPosLabel->Name = L"lblMaxPosLabel";
			this->lblMaxPosLabel->Size = System::Drawing::Size(45, 13);
			this->lblMaxPosLabel->TabIndex = 82;
			this->lblMaxPosLabel->Text = L"MaxPos";
			// 
			// txtMaxForce
			// 
			this->txtMaxForce->Enabled = false;
			this->txtMaxForce->Location = System::Drawing::Point(168, 67);
			this->txtMaxForce->Name = L"txtMaxForce";
			this->txtMaxForce->Size = System::Drawing::Size(40, 20);
			this->txtMaxForce->TabIndex = 81;
			this->txtMaxForce->Text = L"-2";
			// 
			// lblMaxForceLabel
			// 
			this->lblMaxForceLabel->AutoSize = true;
			this->lblMaxForceLabel->Enabled = false;
			this->lblMaxForceLabel->Location = System::Drawing::Point(109, 70);
			this->lblMaxForceLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblMaxForceLabel->Name = L"lblMaxForceLabel";
			this->lblMaxForceLabel->Size = System::Drawing::Size(54, 13);
			this->lblMaxForceLabel->TabIndex = 80;
			this->lblMaxForceLabel->Text = L"MaxForce";
			// 
			// lblFreqNi
			// 
			this->lblFreqNi->AutoSize = true;
			this->lblFreqNi->Location = System::Drawing::Point(342, 12);
			this->lblFreqNi->Name = L"lblFreqNi";
			this->lblFreqNi->Size = System::Drawing::Size(0, 13);
			this->lblFreqNi->TabIndex = 71;
			// 
			// lblFreqNiLabel
			// 
			this->lblFreqNiLabel->AutoSize = true;
			this->lblFreqNiLabel->Location = System::Drawing::Point(286, 12);
			this->lblFreqNiLabel->Name = L"lblFreqNiLabel";
			this->lblFreqNiLabel->Size = System::Drawing::Size(50, 13);
			this->lblFreqNiLabel->TabIndex = 70;
			this->lblFreqNiLabel->Text = L"Freq (Hz)";
			// 
			// lblPositionLabel
			// 
			this->lblPositionLabel->AutoSize = true;
			this->lblPositionLabel->Location = System::Drawing::Point(109, 17);
			this->lblPositionLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblPositionLabel->Name = L"lblPositionLabel";
			this->lblPositionLabel->Size = System::Drawing::Size(44, 13);
			this->lblPositionLabel->TabIndex = 3;
			this->lblPositionLabel->Text = L"Position";
			// 
			// grpFri
			// 
			this->grpFri->Controls->Add(this->chkLoop);
			this->grpFri->Controls->Add(this->btnPose);
			this->grpFri->Controls->Add(this->startStop);
			this->grpFri->Controls->Add(this->groupBox1);
			this->grpFri->Controls->Add(this->btnRst);
			this->grpFri->Controls->Add(this->btnSaveTool);
			this->grpFri->Controls->Add(this->testBoxStatistics);
			this->grpFri->Controls->Add(this->toolDataView);
			this->grpFri->Controls->Add(this->FRI_Life);
			this->grpFri->Controls->Add(this->btnGo);
			this->grpFri->Controls->Add(this->groupBox2);
			this->grpFri->Controls->Add(this->msrCartPosDataView);
			this->grpFri->Controls->Add(this->groupBox3);
			this->grpFri->Controls->Add(this->btnSave);
			this->grpFri->Controls->Add(this->lblSpeed);
			this->grpFri->Controls->Add(this->btnAdd);
			this->grpFri->Controls->Add(this->btnSub);
			this->grpFri->Controls->Add(this->trackBarSpeed);
			this->grpFri->Location = System::Drawing::Point(5, 3);
			this->grpFri->Margin = System::Windows::Forms::Padding(2);
			this->grpFri->Name = L"grpFri";
			this->grpFri->Padding = System::Windows::Forms::Padding(2);
			this->grpFri->Size = System::Drawing::Size(767, 400);
			this->grpFri->TabIndex = 61;
			this->grpFri->TabStop = false;
			this->grpFri->Text = L"KUKA";
			// 
			// chkLoop
			// 
			this->chkLoop->AutoSize = true;
			this->chkLoop->Location = System::Drawing::Point(5, 207);
			this->chkLoop->Name = L"chkLoop";
			this->chkLoop->Size = System::Drawing::Size(50, 17);
			this->chkLoop->TabIndex = 85;
			this->chkLoop->Text = L"Loop";
			this->chkLoop->UseVisualStyleBackColor = true;
			// 
			// btnPose
			// 
			this->btnPose->Location = System::Drawing::Point(4, 247);
			this->btnPose->Name = L"btnPose";
			this->btnPose->Size = System::Drawing::Size(81, 30);
			this->btnPose->TabIndex = 73;
			this->btnPose->Text = L"Open Pose";
			this->btnPose->UseVisualStyleBackColor = true;
			this->btnPose->Click += gcnew System::EventHandler(this, &mainForm::btnPose_Click);
			// 
			// grpLoadCells
			// 
			this->grpLoadCells->Controls->Add(this->btnSaveClibration);
			this->grpLoadCells->Controls->Add(this->calDataView);
			this->grpLoadCells->Controls->Add(this->lblFreq);
			this->grpLoadCells->Controls->Add(this->lblFreqLabel);
			this->grpLoadCells->Controls->Add(this->lblCh3);
			this->grpLoadCells->Controls->Add(this->lblCh3Label);
			this->grpLoadCells->Controls->Add(this->lblCh2);
			this->grpLoadCells->Controls->Add(this->lblCh2Label);
			this->grpLoadCells->Controls->Add(this->lblCh1);
			this->grpLoadCells->Controls->Add(this->lblCh1Label);
			this->grpLoadCells->Controls->Add(this->lblCh0);
			this->grpLoadCells->Controls->Add(this->lblCh0Label);
			this->grpLoadCells->Controls->Add(this->btnStartStopPhidgets);
			this->grpLoadCells->Location = System::Drawing::Point(776, 250);
			this->grpLoadCells->Margin = System::Windows::Forms::Padding(2);
			this->grpLoadCells->Name = L"grpLoadCells";
			this->grpLoadCells->Padding = System::Windows::Forms::Padding(2);
			this->grpLoadCells->Size = System::Drawing::Size(407, 153);
			this->grpLoadCells->TabIndex = 61;
			this->grpLoadCells->TabStop = false;
			this->grpLoadCells->Text = L"Load Cells";
			// 
			// btnSaveClibration
			// 
			this->btnSaveClibration->Location = System::Drawing::Point(7, 50);
			this->btnSaveClibration->Margin = System::Windows::Forms::Padding(2);
			this->btnSaveClibration->Name = L"btnSaveClibration";
			this->btnSaveClibration->Size = System::Drawing::Size(76, 26);
			this->btnSaveClibration->TabIndex = 71;
			this->btnSaveClibration->Text = L"Save Calibration";
			this->btnSaveClibration->UseVisualStyleBackColor = true;
			this->btnSaveClibration->Click += gcnew System::EventHandler(this, &mainForm::btnSaveClibration_Click);
			// 
			// calDataView
			// 
			this->calDataView->AllowUserToAddRows = false;
			this->calDataView->AllowUserToDeleteRows = false;
			this->calDataView->AllowUserToResizeColumns = false;
			this->calDataView->AllowUserToResizeRows = false;
			this->calDataView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->calDataView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->calDataView->BackgroundColor = System::Drawing::SystemColors::ButtonFace;
			this->calDataView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->calDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->calDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->calDataViewLoadCell0,
					this->calDataViewLoadCell1, this->calDataViewLoadCell2, this->calDataViewLoadCell3, this->calDataViewSerialNumber
			});
			this->calDataView->Location = System::Drawing::Point(7, 80);
			this->calDataView->Margin = System::Windows::Forms::Padding(2);
			this->calDataView->Name = L"calDataView";
			this->calDataView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->calDataView->RowTemplate->Height = 28;
			this->calDataView->Size = System::Drawing::Size(396, 73);
			this->calDataView->TabIndex = 70;
			// 
			// calDataViewLoadCell0
			// 
			this->calDataViewLoadCell0->HeaderText = L"Load Cell 0";
			this->calDataViewLoadCell0->Name = L"calDataViewLoadCell0";
			this->calDataViewLoadCell0->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// calDataViewLoadCell1
			// 
			this->calDataViewLoadCell1->HeaderText = L"Load Cell 1";
			this->calDataViewLoadCell1->Name = L"calDataViewLoadCell1";
			this->calDataViewLoadCell1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// calDataViewLoadCell2
			// 
			this->calDataViewLoadCell2->HeaderText = L"Load Cell 2";
			this->calDataViewLoadCell2->Name = L"calDataViewLoadCell2";
			this->calDataViewLoadCell2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// calDataViewLoadCell3
			// 
			this->calDataViewLoadCell3->HeaderText = L"Load Cell 3";
			this->calDataViewLoadCell3->Name = L"calDataViewLoadCell3";
			this->calDataViewLoadCell3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// calDataViewSerialNumber
			// 
			this->calDataViewSerialNumber->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->calDataViewSerialNumber->HeaderText = L"Serial Number";
			this->calDataViewSerialNumber->Name = L"calDataViewSerialNumber";
			this->calDataViewSerialNumber->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->calDataViewSerialNumber->Width = 79;
			// 
			// lblFreq
			// 
			this->lblFreq->AutoSize = true;
			this->lblFreq->Location = System::Drawing::Point(342, 15);
			this->lblFreq->Name = L"lblFreq";
			this->lblFreq->Size = System::Drawing::Size(0, 13);
			this->lblFreq->TabIndex = 69;
			// 
			// lblFreqLabel
			// 
			this->lblFreqLabel->AutoSize = true;
			this->lblFreqLabel->Location = System::Drawing::Point(286, 15);
			this->lblFreqLabel->Name = L"lblFreqLabel";
			this->lblFreqLabel->Size = System::Drawing::Size(50, 13);
			this->lblFreqLabel->TabIndex = 68;
			this->lblFreqLabel->Text = L"Freq (Hz)";
			// 
			// lblCh3
			// 
			this->lblCh3->AutoSize = true;
			this->lblCh3->Location = System::Drawing::Point(182, 54);
			this->lblCh3->Name = L"lblCh3";
			this->lblCh3->Size = System::Drawing::Size(0, 13);
			this->lblCh3->TabIndex = 67;
			// 
			// lblCh3Label
			// 
			this->lblCh3Label->AutoSize = true;
			this->lblCh3Label->Location = System::Drawing::Point(109, 54);
			this->lblCh3Label->Name = L"lblCh3Label";
			this->lblCh3Label->Size = System::Drawing::Size(60, 13);
			this->lblCh3Label->TabIndex = 63;
			this->lblCh3Label->Text = L"Load Cell 3";
			// 
			// lblCh2
			// 
			this->lblCh2->AutoSize = true;
			this->lblCh2->Location = System::Drawing::Point(182, 41);
			this->lblCh2->Name = L"lblCh2";
			this->lblCh2->Size = System::Drawing::Size(0, 13);
			this->lblCh2->TabIndex = 66;
			// 
			// lblCh2Label
			// 
			this->lblCh2Label->AutoSize = true;
			this->lblCh2Label->Location = System::Drawing::Point(109, 41);
			this->lblCh2Label->Name = L"lblCh2Label";
			this->lblCh2Label->Size = System::Drawing::Size(60, 13);
			this->lblCh2Label->TabIndex = 62;
			this->lblCh2Label->Text = L"Load Cell 2";
			// 
			// lblCh1
			// 
			this->lblCh1->AutoSize = true;
			this->lblCh1->Location = System::Drawing::Point(182, 28);
			this->lblCh1->Name = L"lblCh1";
			this->lblCh1->Size = System::Drawing::Size(0, 13);
			this->lblCh1->TabIndex = 65;
			// 
			// lblCh1Label
			// 
			this->lblCh1Label->AutoSize = true;
			this->lblCh1Label->Location = System::Drawing::Point(109, 28);
			this->lblCh1Label->Name = L"lblCh1Label";
			this->lblCh1Label->Size = System::Drawing::Size(60, 13);
			this->lblCh1Label->TabIndex = 61;
			this->lblCh1Label->Text = L"Load Cell 1";
			// 
			// lblCh0
			// 
			this->lblCh0->AutoSize = true;
			this->lblCh0->Location = System::Drawing::Point(182, 15);
			this->lblCh0->Name = L"lblCh0";
			this->lblCh0->Size = System::Drawing::Size(0, 13);
			this->lblCh0->TabIndex = 64;
			// 
			// lblCh0Label
			// 
			this->lblCh0Label->AutoSize = true;
			this->lblCh0Label->Location = System::Drawing::Point(109, 15);
			this->lblCh0Label->Name = L"lblCh0Label";
			this->lblCh0Label->Size = System::Drawing::Size(60, 13);
			this->lblCh0Label->TabIndex = 60;
			this->lblCh0Label->Text = L"Load Cell 0";
			// 
			// grpATI
			// 
			this->grpATI->Controls->Add(this->btnBias);
			this->grpATI->Controls->Add(this->txtCom);
			this->grpATI->Controls->Add(this->lblComLabel);
			this->grpATI->Controls->Add(this->lblTz);
			this->grpATI->Controls->Add(this->lblTy);
			this->grpATI->Controls->Add(this->lblTx);
			this->grpATI->Controls->Add(this->lblLabelTz);
			this->grpATI->Controls->Add(this->lblLabelTy);
			this->grpATI->Controls->Add(this->lblLabelTx);
			this->grpATI->Controls->Add(this->lblFreqATI);
			this->grpATI->Controls->Add(this->lblFreqATIlabel);
			this->grpATI->Controls->Add(this->lblFz);
			this->grpATI->Controls->Add(this->lblFy);
			this->grpATI->Controls->Add(this->lblFx);
			this->grpATI->Controls->Add(this->lblLabelFz);
			this->grpATI->Controls->Add(this->lblLabelFy);
			this->grpATI->Controls->Add(this->lblLabelFx);
			this->grpATI->Controls->Add(this->btnStartATI);
			this->grpATI->Location = System::Drawing::Point(776, 154);
			this->grpATI->Margin = System::Windows::Forms::Padding(2);
			this->grpATI->Name = L"grpATI";
			this->grpATI->Padding = System::Windows::Forms::Padding(2);
			this->grpATI->Size = System::Drawing::Size(407, 92);
			this->grpATI->TabIndex = 72;
			this->grpATI->TabStop = false;
			this->grpATI->Text = L"ATI Force Sensor";
			// 
			// btnBias
			// 
			this->btnBias->Location = System::Drawing::Point(7, 67);
			this->btnBias->Margin = System::Windows::Forms::Padding(2);
			this->btnBias->Name = L"btnBias";
			this->btnBias->Size = System::Drawing::Size(76, 26);
			this->btnBias->TabIndex = 80;
			this->btnBias->Text = L"Bias";
			this->btnBias->UseVisualStyleBackColor = true;
			this->btnBias->Click += gcnew System::EventHandler(this, &mainForm::btnBias_Click);
			// 
			// txtCom
			// 
			this->txtCom->Location = System::Drawing::Point(43, 45);
			this->txtCom->Name = L"txtCom";
			this->txtCom->Size = System::Drawing::Size(40, 20);
			this->txtCom->TabIndex = 79;
			this->txtCom->Text = L"4";
			// 
			// lblComLabel
			// 
			this->lblComLabel->AutoSize = true;
			this->lblComLabel->Location = System::Drawing::Point(7, 48);
			this->lblComLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblComLabel->Name = L"lblComLabel";
			this->lblComLabel->Size = System::Drawing::Size(31, 13);
			this->lblComLabel->TabIndex = 78;
			this->lblComLabel->Text = L"COM";
			// 
			// lblTz
			// 
			this->lblTz->AutoSize = true;
			this->lblTz->Location = System::Drawing::Point(182, 74);
			this->lblTz->Name = L"lblTz";
			this->lblTz->Size = System::Drawing::Size(0, 13);
			this->lblTz->TabIndex = 77;
			// 
			// lblTy
			// 
			this->lblTy->AutoSize = true;
			this->lblTy->Location = System::Drawing::Point(182, 61);
			this->lblTy->Name = L"lblTy";
			this->lblTy->Size = System::Drawing::Size(0, 13);
			this->lblTy->TabIndex = 76;
			// 
			// lblTx
			// 
			this->lblTx->AutoSize = true;
			this->lblTx->Location = System::Drawing::Point(182, 48);
			this->lblTx->Name = L"lblTx";
			this->lblTx->Size = System::Drawing::Size(0, 13);
			this->lblTx->TabIndex = 75;
			// 
			// lblLabelTz
			// 
			this->lblLabelTz->AutoSize = true;
			this->lblLabelTz->Location = System::Drawing::Point(109, 74);
			this->lblLabelTz->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelTz->Name = L"lblLabelTz";
			this->lblLabelTz->Size = System::Drawing::Size(19, 13);
			this->lblLabelTz->TabIndex = 74;
			this->lblLabelTz->Text = L"Tz";
			// 
			// lblLabelTy
			// 
			this->lblLabelTy->AutoSize = true;
			this->lblLabelTy->Location = System::Drawing::Point(109, 61);
			this->lblLabelTy->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelTy->Name = L"lblLabelTy";
			this->lblLabelTy->Size = System::Drawing::Size(19, 13);
			this->lblLabelTy->TabIndex = 73;
			this->lblLabelTy->Text = L"Ty";
			// 
			// lblLabelTx
			// 
			this->lblLabelTx->AutoSize = true;
			this->lblLabelTx->Location = System::Drawing::Point(109, 48);
			this->lblLabelTx->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelTx->Name = L"lblLabelTx";
			this->lblLabelTx->Size = System::Drawing::Size(19, 13);
			this->lblLabelTx->TabIndex = 72;
			this->lblLabelTx->Text = L"Tx";
			// 
			// lblFreqATI
			// 
			this->lblFreqATI->AutoSize = true;
			this->lblFreqATI->Location = System::Drawing::Point(342, 12);
			this->lblFreqATI->Name = L"lblFreqATI";
			this->lblFreqATI->Size = System::Drawing::Size(0, 13);
			this->lblFreqATI->TabIndex = 71;
			// 
			// lblFreqATIlabel
			// 
			this->lblFreqATIlabel->AutoSize = true;
			this->lblFreqATIlabel->Location = System::Drawing::Point(286, 12);
			this->lblFreqATIlabel->Name = L"lblFreqATIlabel";
			this->lblFreqATIlabel->Size = System::Drawing::Size(50, 13);
			this->lblFreqATIlabel->TabIndex = 70;
			this->lblFreqATIlabel->Text = L"Freq (Hz)";
			// 
			// lblFz
			// 
			this->lblFz->AutoSize = true;
			this->lblFz->Location = System::Drawing::Point(182, 35);
			this->lblFz->Name = L"lblFz";
			this->lblFz->Size = System::Drawing::Size(0, 13);
			this->lblFz->TabIndex = 63;
			// 
			// lblFy
			// 
			this->lblFy->AutoSize = true;
			this->lblFy->Location = System::Drawing::Point(182, 22);
			this->lblFy->Name = L"lblFy";
			this->lblFy->Size = System::Drawing::Size(0, 13);
			this->lblFy->TabIndex = 62;
			// 
			// lblFx
			// 
			this->lblFx->AutoSize = true;
			this->lblFx->Location = System::Drawing::Point(182, 9);
			this->lblFx->Name = L"lblFx";
			this->lblFx->Size = System::Drawing::Size(0, 13);
			this->lblFx->TabIndex = 61;
			// 
			// lblLabelFz
			// 
			this->lblLabelFz->AutoSize = true;
			this->lblLabelFz->Location = System::Drawing::Point(109, 35);
			this->lblLabelFz->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelFz->Name = L"lblLabelFz";
			this->lblLabelFz->Size = System::Drawing::Size(18, 13);
			this->lblLabelFz->TabIndex = 59;
			this->lblLabelFz->Text = L"Fz";
			// 
			// lblLabelFy
			// 
			this->lblLabelFy->AutoSize = true;
			this->lblLabelFy->Location = System::Drawing::Point(109, 22);
			this->lblLabelFy->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelFy->Name = L"lblLabelFy";
			this->lblLabelFy->Size = System::Drawing::Size(18, 13);
			this->lblLabelFy->TabIndex = 6;
			this->lblLabelFy->Text = L"Fy";
			// 
			// lblLabelFx
			// 
			this->lblLabelFx->AutoSize = true;
			this->lblLabelFx->Location = System::Drawing::Point(109, 9);
			this->lblLabelFx->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblLabelFx->Name = L"lblLabelFx";
			this->lblLabelFx->Size = System::Drawing::Size(18, 13);
			this->lblLabelFx->TabIndex = 5;
			this->lblLabelFx->Text = L"Fx";
			// 
			// btnStartATI
			// 
			this->btnStartATI->Location = System::Drawing::Point(7, 17);
			this->btnStartATI->Margin = System::Windows::Forms::Padding(2);
			this->btnStartATI->Name = L"btnStartATI";
			this->btnStartATI->Size = System::Drawing::Size(76, 26);
			this->btnStartATI->TabIndex = 55;
			this->btnStartATI->Text = L"startATI";
			this->btnStartATI->UseVisualStyleBackColor = true;
			this->btnStartATI->Click += gcnew System::EventHandler(this, &mainForm::btnStartATI_Click);
			// 
			// openPoseFile
			// 
			this->openPoseFile->FileName = L"pose.txt";
			// 
			// grpLog
			// 
			this->grpLog->Controls->Add(this->txtAdr);
			this->grpLog->Controls->Add(this->btnLog);
			this->grpLog->Controls->Add(this->btnLogging);
			this->grpLog->Location = System::Drawing::Point(5, 404);
			this->grpLog->Name = L"grpLog";
			this->grpLog->Size = System::Drawing::Size(298, 91);
			this->grpLog->TabIndex = 73;
			this->grpLog->TabStop = false;
			this->grpLog->Text = L"Logging";
			// 
			// grpSimulink
			// 
			this->grpSimulink->Controls->Add(this->btnSimulinkStart);
			this->grpSimulink->Location = System::Drawing::Point(314, 404);
			this->grpSimulink->Name = L"grpSimulink";
			this->grpSimulink->Size = System::Drawing::Size(803, 91);
			this->grpSimulink->TabIndex = 74;
			this->grpSimulink->TabStop = false;
			this->grpSimulink->Text = L"Simulink Desktop Real-Time";
			// 
			// btnSimulinkStart
			// 
			this->btnSimulinkStart->Location = System::Drawing::Point(5, 18);
			this->btnSimulinkStart->Margin = System::Windows::Forms::Padding(2);
			this->btnSimulinkStart->Name = L"btnSimulinkStart";
			this->btnSimulinkStart->Size = System::Drawing::Size(76, 26);
			this->btnSimulinkStart->TabIndex = 56;
			this->btnSimulinkStart->Text = L"startSimulink";
			this->btnSimulinkStart->UseVisualStyleBackColor = true;
			this->btnSimulinkStart->Click += gcnew System::EventHandler(this, &mainForm::btnSimulinkStart_Click);
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1194, 502);
			this->Controls->Add(this->grpSimulink);
			this->Controls->Add(this->grpLog);
			this->Controls->Add(this->grpATI);
			this->Controls->Add(this->grpLoadCells);
			this->Controls->Add(this->grpFri);
			this->Controls->Add(this->grpNi);
			this->Controls->Add(this->btnAbout);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2);
			this->MaximumSize = System::Drawing::Size(1210, 540);
			this->MinimumSize = System::Drawing::Size(545, 540);
			this->Name = L"mainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"KUKA UI";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->msrCartPosDataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarSpeed))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->toolDataView))->EndInit();
			this->grpNi->ResumeLayout(false);
			this->grpNi->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PIDDataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarCurrent))->EndInit();
			this->grpFri->ResumeLayout(false);
			this->grpFri->PerformLayout();
			this->grpLoadCells->ResumeLayout(false);
			this->grpLoadCells->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->calDataView))->EndInit();
			this->grpATI->ResumeLayout(false);
			this->grpATI->PerformLayout();
			this->grpLog->ResumeLayout(false);
			this->grpLog->PerformLayout();
			this->grpSimulink->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		mainForm()
		{
			InitializeComponent();
			int listCount = 0;
			System::String ^listItem;
			listItem = loadFromFile(POSE, listCount);
			for (i = 0; i < listCount; i++) {
				addRowsToDataView();
			}
			writeToDataGridView(msrCartPosDataView, listItem, SEPARATOR);

			listItem = loadFromFile(TOOL, listCount);
			for (i = 0; i < listCount; i++) {
				this->toolDataView->Rows->Add();
			}
			writeToDataGridView(toolDataView, listItem, SEPARATOR);

			listItem = loadFromFile(CALIBRATION, listCount);
			for (i = 0; i < listCount; i++) {
				this->calDataView->Rows->Add();
			}
			writeToDataGridView(calDataView, listItem, SEPARATOR);

			listItem = loadFromFile(PID, listCount);
			for (i = 0; i < listCount; i++) {
				this->PIDDataView->Rows->Add();
			}
			writeToDataGridView(PIDDataView, listItem, SEPARATOR);

			resetFri(false);
		}
	private: System::ComponentModel::BackgroundWorker^  ni;
	protected:
		void addRowsToDataView()
		{
			this->msrCartPosDataView->Rows->Add();
			poseNum++;
		}
		void subRowsFromDataView()
		{
			if (poseNum > 0) {
				poseNum--;
				this->msrCartPosDataView->Rows->RemoveAt(poseNum);
			}
		}
	protected:
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
		
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {


		if (this->FRIThread->IsBusy)
		{
			// stop it
			this->FRIThread->CancelAsync();
			this->startStop->BackColor = System::Drawing::Color::Red;
			resetFri(false);
		}
		else
		{
			this->FRIThread->RunWorkerAsync();
			this->startStop->BackColor = System::Drawing::Color::Green;
		}

	}
			 void resetFri(bool connectPending)
			 {
				 /* Fixme -- reset colors etc... */
				 if (connectPending)
					 this->startStop->BackColor = System::Drawing::Color::Beige;

				 else
					 this->startStop->BackColor = System::Drawing::Color::Gray;
				 this->Motor->BackColor = System::Drawing::Color::Gray;
				 this->Quality->BackColor = System::Drawing::Color::Gray;
				 this->FRIState->BackColor = System::Drawing::Color::Gray;



				 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_NA;


			 }

			 void updateFri(tFriMsrData &msr,
				 tFriCmdData &cmd)
			 {
				 if (chkLoop->Checked & j == poseNum) {
					 trajFlag = true;
					 j = 0;
				 }

				 speed = Convert::ToDouble(trackBarSpeed->Value) / 8000;

				 if (trajFlag) {
					 btnGo->Text = KUKA_POSE_PAUSE;
				 }
				 else {
					 btnGo->Text = KUKA_POSE_GO;
				 }



				 if (j < poseNum) {
					 for (i = 0; i < CART_COMP; i++) {
						 if (i < 3) {
							 trg[i] = mm2m(Convert::ToDouble(msrCartPosDataView->Rows[j]->Cells[i]->Value));
							 tool[i] = mm2m(Convert::ToDouble(toolDataView->Rows[0]->Cells[i]->Value));
						 }
						 if (i > 2) {
							 trg[i] = deg2rad(Convert::ToDouble(msrCartPosDataView->Rows[j]->Cells[i]->Value));
							 tool[i] = deg2rad(Convert::ToDouble(toolDataView->Rows[0]->Cells[i]->Value));
						 }
						 stiff[i] = Convert::ToDouble(toolDataView->Rows[1]->Cells[i]->Value);
					 }
				 }


				 bool updateRequired = false;
				 {
					 static int lastState = -1;
					 // just detect change // update neccessary for high speeds 
					 if (lastState != msr.intf.state)
					 {
						 updateRequired = true;
					 }
					 lastState = msr.intf.state;
				 }
				 {
					 static int lastQuality = -1;
					 if (lastQuality != msr.intf.quality)
					 {
						 updateRequired = true;
					 }
					 lastQuality = msr.intf.quality;
				 }
				 {
					 static int lastMotor = -1;
					 if (lastMotor != msr.robot.power)
					 {
						 updateRequired = true;
					 }
					 lastMotor = msr.robot.power;
				 }
				 int divisor = (int)Math::Ceiling(0.1 / msr.intf.desiredCmdSampleTime);
				 if (msr.head.sendSeqCount % divisor == 0)
				 {
					 updateRequired = true;
				 }
				 // return, if no update required
				 if (!updateRequired) { return; }

				 {
					 System::String ^statString;
					 statString = gcnew  System::String("");
					 String ^kukaCmdStr;
					 kukaCmdStr = gcnew  System::String(kukaWriteCommand);
					 statString = System::String::Format(STATSTRING,
						 msr.intf.timestamp, msr.intf.state, msr.intf.quality, msr.intf.desiredMsrSampleTime, msr.intf.desiredCmdSampleTime, msr.intf.safetyLimits, kukaCmdStr);
					 statString->Empty;
					 this->testBoxStatistics->Text = statString;
				 }
				 /* Quality */
				 switch (msr.intf.quality)
				 {
				 case FRI_QUALITY_BAD:
					 this->Quality->BackColor = Color::Red;
					 break;
				 case FRI_QUALITY_UNACCEPTABLE:
					 this->Quality->BackColor = Color::OrangeRed;
					 break;
				 case FRI_QUALITY_OK:
					 this->Quality->BackColor = Color::Yellow;
					 break;
				 case FRI_QUALITY_PERFECT:
					 this->Quality->BackColor = Color::Green;
					 break;
				 default:
					 this->Quality->BackColor = Color::Transparent;
					 break;
				 }


				 /* Motor */
				 if (msr.robot.power)
				 {
					 this->Motor->BackColor = Color::Green;
				 }
				 else
				 {
					 this->Motor->BackColor = Color::Red;
				 }


				 /* FRI State */
				 switch (msr.intf.state)
				 {
				 case FRI_STATE_OFF:  // No State at all
					 this->FRIState->BackColor = Color::Red;
					 break;
				 case FRI_STATE_MON:
					 this->FRIState->BackColor = Color::Yellow;
					 break;
				 case FRI_STATE_CMD:
					 this->FRIState->BackColor = Color::Green;
					 break;
				 default:
					 this->FRIState->BackColor = Color::Transparent;
					 break;
				 }


				 switch (msr.robot.control)
				 {
				 case FRI_CTRL_POSITION: // 1
					 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_POSITION;
					 break;
				 case FRI_CTRL_CART_IMP: // 2
					 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_CARTIMP;
					 break;
				 case FRI_CTRL_JNT_IMP: //3 
					 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_JNTIMP;
					 break;
				 case FRI_CTRL_OTHER: // 0
					 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_OTHER;
					 break;
				 default:
					 this->FRICtrlModeLabel->Text = FRI_CONTROL_MODE_UNKNOWN;

				 }


				 this->lblX->Text = Convert::ToString(round(m2mm(rot2angle(msr.data.msrCartPos)[0]) * ACC) / ACC);
				 this->lblY->Text = Convert::ToString(round(m2mm(rot2angle(msr.data.msrCartPos)[1]) * ACC) / ACC);
				 this->lblZ->Text = Convert::ToString(round(m2mm(rot2angle(msr.data.msrCartPos)[2]) * ACC) / ACC);
				 this->lblA->Text = Convert::ToString(round(rad2deg(rot2angle(msr.data.msrCartPos)[3]) * ACC) / ACC);
				 this->lblB->Text = Convert::ToString(round(rad2deg(rot2angle(msr.data.msrCartPos)[4]) * ACC) / ACC);
				 this->lblC->Text = Convert::ToString(round(rad2deg(rot2angle(msr.data.msrCartPos)[5]) * ACC) / ACC);



				 angle2rot(tool, toolRot);
				 //disp(toolRot, 3, 4,"7T8");
				 compoundTrans(msr.data.msrCartPos, toolRot, eeRot);
				 //disp(msr.data.cmdCartPos, 3, 4, "0T7");
				 //disp(eeRot, 3, 4, "0T8");
				 rot2angle(eeRot, ee);
				 this->lblToolXMon->Text = Convert::ToString(round(m2mm(ee[0])* ACC) / ACC);
				 this->lblToolYMon->Text = Convert::ToString(round(m2mm(ee[1])* ACC) / ACC);
				 this->lblToolZMon->Text = Convert::ToString(round(m2mm(ee[2])* ACC) / ACC);
				 this->lblToolAMon->Text = Convert::ToString(round(rad2deg(ee[3])* ACC) / ACC);
				 this->lblToolBMon->Text = Convert::ToString(round(rad2deg(ee[4])* ACC) / ACC);
				 this->lblToolCMon->Text = Convert::ToString(round(rad2deg(ee[5])* ACC) / ACC);


				 int boolData = 0;

				 cmd.krl.boolData = boolData;

			 }
			 void updateNi() {
				 lblPosition->Text = Convert::ToString(recVec.position);
				 lblFreqNi->Text = Convert::ToString(round(1 / (recVec.dt)));

				 NiPID[0] = Convert::ToDouble(PIDDataView->Rows[0]->Cells[0]->Value);
				 NiPID[1] = Convert::ToDouble(PIDDataView->Rows[0]->Cells[1]->Value);
				 NiPID[2] = Convert::ToDouble(PIDDataView->Rows[0]->Cells[2]->Value);
				 NiPID[3] = Convert::ToDouble(PIDDataView->Rows[0]->Cells[3]->Value);
				 NiPID[4] = Convert::ToDouble(PIDDataView->Rows[0]->Cells[4]->Value);

				 command.currentLimit = Convert::ToInt16(trackBarCurrent->Value);

				 if (this->chkManual->Checked) {
					 command.position = Convert::ToDouble(txtMaxPos->Text);
					 command.force = -Convert::ToDouble(txtMaxForce->Text);
				 }
				 else if(j < poseNum){ 
						 if (Convert::ToDouble(msrCartPosDataView->Rows[j]->Cells[6]->Value) > 0) {
							 command.cmd = OPEN;
							 command.position = Convert::ToDouble(msrCartPosDataView->Rows[j]->Cells[6]->Value);
						 }
						 else {
							 command.cmd = CLOSE;
							 command.force = -Convert::ToDouble(msrCartPosDataView->Rows[j]->Cells[6]->Value);
						 }			 
				 }
				 this->btnOpenGripper->Enabled = this->chkManual->Checked;
				 this->btnCloseGripper->Enabled = this->chkManual->Checked;
				 this->lblMaxPosLabel->Enabled = this->chkManual->Checked;
				 this->lblMaxForceLabel->Enabled = this->chkManual->Checked;
				 this->txtMaxForce->Enabled = this->chkManual->Checked;
				 this->txtMaxPos->Enabled = this->chkManual->Checked;
				 //printf("mahyar:%d", j);
			 }
			 void updatePhidgets() {
				 calMatrix[0] = Convert::ToDouble(calDataView->Rows[0]->Cells[0]->Value);
				 calMatrix[1] = Convert::ToDouble(calDataView->Rows[0]->Cells[1]->Value);
				 calMatrix[2] = Convert::ToDouble(calDataView->Rows[0]->Cells[2]->Value);
				 calMatrix[3] = Convert::ToDouble(calDataView->Rows[0]->Cells[3]->Value);
				 calMatrix[4] = Convert::ToDouble(calDataView->Rows[1]->Cells[0]->Value);
				 calMatrix[5] = Convert::ToDouble(calDataView->Rows[1]->Cells[1]->Value);
				 calMatrix[6] = Convert::ToDouble(calDataView->Rows[1]->Cells[2]->Value);
				 calMatrix[7] = Convert::ToDouble(calDataView->Rows[1]->Cells[3]->Value);

				 lblCh0->Text = Convert::ToString(calibratedPhidgets[0]);
				 lblCh1->Text = Convert::ToString(calibratedPhidgets[1]);
				 lblCh2->Text = Convert::ToString(calibratedPhidgets[2]);
				 lblCh3->Text = Convert::ToString(calibratedPhidgets[3]);
				 lblFreq->Text = Convert::ToString(round((1 / phiVec.dt)));
			 }
			 void updateAtiSensor() {
				 comPort = Convert::ToInt16(txtCom->Text);
				 lblFx->Text = Convert::ToString(atiVector.fx);
				 lblFy->Text = Convert::ToString(atiVector.fy);
				 lblFz->Text = Convert::ToString(atiVector.fz);
				 lblTx->Text = Convert::ToString(atiVector.tx);
				 lblTy->Text = Convert::ToString(atiVector.ty);
				 lblTz->Text = Convert::ToString(atiVector.tz);
				 lblFreqATI->Text = Convert::ToString(round(1 / atiVector.dt));
			 }
			 void updateSimulink() {

			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		this->Size.Width = 800;
		this->Size.Height = 690;
	}

	private: System::Void btnLog_Click(System::Object^  sender, System::EventArgs^  e) {
		saveLogFile->FileName = txtAdr->Text;
		if (saveLogFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			txtAdr->Text = saveLogFile->FileName;
		}
	}

	private: System::Void btnLogging_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->FRILogging->IsBusy)
		{
			// stop it
			btnLogging->Text = START_LOGGING;
			this->FRILogging->CancelAsync();
		}
		else
		{

			btnLogging->Text = STOP_LOGGING;
			this->FRILogging->RunWorkerAsync();

		}
	}
	private: System::Void FRIThread_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs ^  e)
	{
		// update the internal gui with measurements
		if (e->ProgressPercentage >= 9) // worker is successful
			updateFri(msr, cmd);
		else
			resetFri(true);
		this->FRI_Life->Value = e->ProgressPercentage;
	}
	private: System::Void FRIThread_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
	{
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		startFri(FRIThread, msr, cmd, friInst, trajFlag, j, poseNum, kukaWriteCommand, tool, trg, speed, stiff, simulinkTrg);
	}
	private: System::Void FRILogging_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		startLogging(FRILogging, txtAdr, msr, EE + NI + CALIBRATEDPHIDGETS + ATISENSOR + ESTEXTTCPFT, j, recVec, phiVec, calibratedPhidgets, atiVector, ee);
	}
	private: System::Void ni_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		stratNi(ni, recVec, command, tsk, calibratedPhidgets, NiPID, trajFlag);
	}
	private: System::Void ni_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs ^  e)
	{
		updateNi();
	}
	private: System::Void phidgets_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		runPhidgets(phidgets, calMatrix, calibratedPhidgets, bridge, phiVec);
	}
	private: System::Void phidgets_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs ^  e)
	{
		updatePhidgets();
	}
	private: System::Void atiSensor_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		runAtiSensor(atiSensor, atiVector, comPort);
	}
	private: System::Void atiSensor_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs ^  e)
	{
		updateAtiSensor();
		if (e->ProgressPercentage == 1) {
			MessageBox::Show(ATI_ERROR_00);
			btnStartATI->Text = START_ATI;
		}
	}
	private: System::Void simulink_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::Highest;
		startSimulink(simulink, msr, recVec, phiVec, atiVector, simulinkTrg);
	}
	private: System::Void simulink_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs ^  e)
	{
		updateSimulink();
	}
	private: System::Void btnGo_Click(System::Object^  sender, System::EventArgs^  e) {
		trajFlag = !trajFlag;
	}

	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e) {
		addRowsToDataView();
	}

	private: System::Void btnSub_Click(System::Object^  sender, System::EventArgs^  e) {
		subRowsFromDataView();
	}

	private: System::Void btnSave_Click(System::Object^  sender, System::EventArgs^  e) {
		saveToFile(readFromDataGridView(msrCartPosDataView), POSE);
	}

	private: System::Void btnAbout_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show(ABOUT);
	}
	private: System::Void btnSaveTool_Click(System::Object^  sender, System::EventArgs^  e) {
		saveToFile(readFromDataGridView(toolDataView), TOOL);
	}
	private: System::Void btnRst_Click(System::Object^  sender, System::EventArgs^  e) {
		trajFlag = false;
		j = 0;
	}


	private: System::Void btnStartStopNi_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->ni->IsBusy)
		{
			// stop it
			kill(tsk);
			btnStartStopNi->Text = START_NI;
			this->ni->CancelAsync();
		}
		else
		{

			btnStartStopNi->Text = STOP_NI;
			this->ni->RunWorkerAsync();
		}

	}
	private: System::Void btnOpenGripper_Click(System::Object^  sender, System::EventArgs^  e) {
		command.position = Convert::ToDouble(txtMaxPos->Text);
		command.cmd = OPEN;
	}
	private: System::Void btnCloseGripper_Click(System::Object^  sender, System::EventArgs^  e) {
		command.force = Convert::ToDouble(txtMaxForce->Text);
		command.cmd = CLOSE;
	}
	private: System::Void btnStartStopPhidgets_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->phidgets->IsBusy)
		{
			// stop it
			killPhidgets(bridge);
			btnStartStopPhidgets->Text = START_PHIDGETS;
			this->phidgets->CancelAsync();
		}
		else
		{

			btnStartStopPhidgets->Text = STOP_PHIDGETS;
			this->phidgets->RunWorkerAsync();

		}
	}


	private: System::Void btnSaveClibration_Click(System::Object^  sender, System::EventArgs^  e) {
		saveToFile(readFromDataGridView(calDataView), CALIBRATION);
	}
	private: System::Void btnStartATI_Click(System::Object^  sender, System::EventArgs^  e) {

		if (this->atiSensor->IsBusy)
		{
			// stop it
			killAti(comPort);
			btnStartATI->Text = START_ATI;
			btnBias->Enabled = TRUE;
			this->atiSensor->CancelAsync();
		}
		else
		{

			btnStartATI->Text = STOP_ATI;
			btnBias->Enabled = FALSE;
			this->atiSensor->RunWorkerAsync();

		}
	}
	private: System::Void btnBias_Click(System::Object^  sender, System::EventArgs^  e) {
		atiBias(comPort);
	}
	private: System::Void btnPose_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openPoseFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			while (poseNum) {
				subRowsFromDataView();
			}
			int count = 0;
			loadFromFile(openPoseFile->FileName, count);
			for (i = 0; i < count; i++) {
				addRowsToDataView();
			}
			writeToDataGridView(msrCartPosDataView, loadFromFile(openPoseFile->FileName, count), SEPARATOR);

		}
	}
	private: System::Void chkManual_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		trajFlag != trajFlag;
	}
	private: System::Void btnSimulinkStart_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->simulink->IsBusy)
		{
			// stop it
			btnSimulinkStart->Text = START_SIMULINK;
			this->simulink->CancelAsync();
		}
		else
		{

			btnSimulinkStart->Text = STOP_SIMULINK;
			this->simulink->RunWorkerAsync();

		}
	}

	private: System::Void btnPIDSave_Click(System::Object^  sender, System::EventArgs^  e) {
		saveToFile(readFromDataGridView(PIDDataView), PID);
	}

};


	[STAThreadAttribute]
	int main(cli::array<System::String ^> ^args)
	{
		// Enabling Windows XP visual effects before any controls are created
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		// Set priority
		System::Threading::Thread::CurrentThread->Priority = System::Threading::ThreadPriority::AboveNormal;
		//System.Diagnostics.Process.GetCurrentProcess().PriorityClass = System.Diagnostics.ProcessPriorityClass.High;

		System::Diagnostics::Process::GetCurrentProcess()->PriorityClass = System::Diagnostics::ProcessPriorityClass::RealTime;
		//System::Diagnostics::Process::GetCurrentProcess()->BasePriority  = System::Diagnostics::ProcessPriorityClass::RealTime;


		GuiCartTrajGrp::mainForm^ theMainForm = gcnew mainForm();
		// Create the main window and run it
		Application::Run(theMainForm);


		return 0;
	}
};