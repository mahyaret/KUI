//  ---------------------- Doxygen info ----------------------
//! \file functions.h
//!
//! \brief
//! Header file for communicating with KUKA, trajectory generations, and geometrical transformations
//!
//! \details
//! The declarations here are for the functions.cpp 
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

//  ---------------------- Doxygen info ----------------------
//! \fn float * rot2angle(float* rot)
//!
//! \brief
//! This method obtains Euler angles from the transformation matrix.
//!
//! \param rot
//! This is the pointer containing the rotation matrix.
//!
//! \return
//! A float array of the Euler angles.
//!
//  ----------------------------------------------------------
float * rot2angle(float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn float * angle2rot(float* angle)
//!
//! \brief
//! This method constructs the transformation matrix using the Euler angles.
//!
//! \param angle
//! This is the pointer containing the Euler angles.
//!
//! \return
//! A float array of the transformation matrix.
//!
//  ----------------------------------------------------------
float * angle2rot(float* angle);

//  ---------------------- Doxygen info ----------------------
//! \fn float deg2rad(float deg)
//!
//! \brief
//! This method converts a float degree value to a float radian value.
//!
//! \param deg
//! A float degree value.
//!
//! \return
//! A float radian value.
//!
//  ----------------------------------------------------------
float deg2rad(float deg);

//  ---------------------- Doxygen info ----------------------
//! \fn float rad2deg(float rad)
//!
//! \brief
//! This method converts a float radian value to a float degree value.
//!
//! \param rad
//! A float radian value.
//!
//! \return
//! A float degree value.
//!
//  ----------------------------------------------------------
float rad2deg(float rad);

//  ---------------------- Doxygen info ----------------------
//! \fn float mm2m(float mm)
//!
//! \brief
//! This method converts a float millimeter value to a float meter value.
//!
//! \param mm
//! A float millimeter value.
//!
//! \return
//! A float meter value.
//!
//  ----------------------------------------------------------
float mm2m(float mm);

//  ---------------------- Doxygen info ----------------------
//! \fn float m2mm(float m)
//!
//! \brief
//! This method converts a float meter value to a float millimeter value.
//!
//! \param m
//! A float meter value.
//!
//! \return
//! A float millimeter value.
//!
//  ----------------------------------------------------------
float m2mm(float m);

//  ---------------------- Doxygen info ----------------------
//! \fn void saveToFile(System::String^ str, System::String ^Addr)
//!
//! \brief
//! This method saves a string in a file.
//!
//! \param str
//! A System String containing the line to be saved into the file.
//!
//! \param Addr
//! A System String containing the desired address for the file.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void saveToFile(System::String^ str, System::String ^Addr);

//  ---------------------- Doxygen info ----------------------
//! \fn System::String ^readFromDataGridView(System::Windows::Forms::DataGridView ^DataView)
//!
//! \brief
//! This method creates a savable line out of a Data Grid View.
//!
//! \param DataView
//! System Windows Forms Data Grid View element.
//!
//! \return
//! A String that can be saved into a file.
//!
//  ----------------------------------------------------------
System::String ^readFromDataGridView(System::Windows::Forms::DataGridView ^DataView);

//  ---------------------- Doxygen info ----------------------
//! \fn System::String ^loadFromFile(System::String ^Addr,int &count)
//!
//! \brief
//! This method loads the string from a file.
//!
//! \param Addr
//! System String of the location of the file.
//!
//! \param count
//! The integer number of lines loaded from the file.
//!
//! \return
//! System String that is loaded from the file.
//!
//  ----------------------------------------------------------
System::String ^loadFromFile(System::String ^Addr,int &count);

//  ---------------------- Doxygen info ----------------------
//! \fn void writeToDataGridView(System::Windows::Forms::DataGridView ^DataView, System::String^ str, System::String^ delimiter)
//!
//! \brief
//! This method writes elements in the System String in the System windows Froms Data Grid View.
//!
//! \param DataView
//! The name of the System windows Forms Data Grid View.
//!
//! \param str
//! System string to be parsed and written in the Data Grid View.
//!
//! \param delimiter
//! System String for distinguishing each element in the string. 
//! 
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void writeToDataGridView(System::Windows::Forms::DataGridView ^DataView, System::String^ str, System::String^ delimiter);

//  ---------------------- Doxygen info ----------------------
//! \fn void compoundTrans(float* eeRot, float* toolRot, float* rot)
//!
//! \brief
//! This method compounds two matrices. 
//! rot = eeRot*toolRot;
//!
//! \param eeRot
//! Float array of the left matrix operand.
//!
//! \param toolRot
//! Float array of the right matrix operand.
//!
//! \param rot
//! Float output array of the result.  
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void compoundTrans(float* eeRot, float* toolRot, float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn void rot2angle(float* rot,float* angle)
//!
//! \brief
//! This method obtains Euler angles from the transformation matrix.
//!
//! \param rot
//! This is the pointer containing the rotation matrix.
//!
//! \param angle
//! A float output array of the Euler angles.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void rot2angle(float* rot,float* angle);

//  ---------------------- Doxygen info ----------------------
//! \fn void angle2rot(float* angle,float* rot)
//!
//! \brief
//! This method constructs the transformation matrix using the Euler angles.
//!
//! \param angle
//! This is the pointer containing the Euler angles.
//!
//! \param rot
//! A float output array of the transformation matrix.
//! 
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void angle2rot(float* angle,float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn void inverseTrans(float* eeRot, float* toolRot, float* rot)
//!
//! \brief
//! This method constructs the KUKA rotation matrix considering the tool attached to the end-effector.\n
//! rToolRot = toolRot(1:3,1:3);\n
//! pToolRot = toolRot(1:3, 4);\n
//! invToolRot = [transpose(rToolRot), -transpose(rToolRot)*pToolRot;0, 0, 0, 1];\n
//! rot = eeRot*invToolRot;
//!
//! \param eeRot
//! Float array of the KUKA end-effector rotation matrix.
//!
//! \param toolRot
//! Float array of the Tool rotation matrix.
//!
//! \param rot
//! Float output array of the rotation matrix to be fed into KUKA.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void inverseTrans(float* eeRot, float* toolRot, float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn void disp(float* rot,int row, int col)
//!
//! \brief
//! This method is an auxiliary function for displaying a matrix.
//!
//! \param rot
//! A float array of the matrix to be displayed.
//!
//! \param row
//! An integer specifying the number of rows.
//!
//! \param col
//! An integer specifying the number of columns.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void disp(float* rot,int row, int col);

//  ---------------------- Doxygen info ----------------------
//! \fn void disp(float* rot, int row, int col, char * name)
//!
//! \brief
//! This method is an auxiliary function for displaying a matrix as well as its name.
//!
//! \param rot
//! A float array of the matrix to be displayed.
//!
//! \param row
//! An integer specifying the number of rows.
//!
//! \param col
//! An integer specifying the number of columns
//!
//! \param name
//! A character array of matrix's name.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void disp(float* rot, int row, int col, char * name);

//  ---------------------- Doxygen info ----------------------
//! \fn void rot2quat(float* rot, float* quat)
//!
//! \brief
//! This method obtains the quaternions from the transformation matrix.
//!
//! \param rot
//! A float array of the transformation matrix.
//!
//! \param quat
//! This is the output pointer containing the quaternions.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void rot2quat(float* rot, float* quat);

//  ---------------------- Doxygen info ----------------------
//! \fn void quat2rot(float* quat, float* rot)
//!
//! \brief
//! This method constructs the transformation matrix using the quaternions.
//!
//! \param quat
//! This is the pointer containing the quaternions.
//!
//! \param rot
//! A float output array of the transformation matrix.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void quat2rot(float* quat, float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn void startLogging(System::ComponentModel::BackgroundWorker^ workerLog, System::Windows::Forms::TextBox^  txtAdr, tFriMsrData& msr, int selection, unsigned int& j, niVec & recVec, phidgetsVec & phiVec, float * calibratedPhidgets, atiVec & atiVector, float* ee)
//!
//! \brief
//! This method selects desired variable using "selection" and logs their values.
//!
//! \param workerLog
//! A seperate System Component Model Background Worker for logging. 
//!
//! \param txtAdr
//! A String of address for saving the log file.
//!
//! \param msr
//! The msr variable containing all KUKA parameters.
//!
//! \param selection
//! An integer variable that is used to perform a bitwise logical AND operation. The bitwise operator performs a bitwise logical AND between this variable and the constant assigned to the desired variable for logging. It takes each corresponding bit for both expressions. The bits in the result are set to 1 if and only if both bits in the input expressions have a value of 1; otherwise, the bit in the result is set to 0. For example,  the binary representation of 170 (selection) is 0000 0000 1010 1010. The binary representation of 2 (a constant assigned for representing a variable to be logged or B) is 0000 0000 0000 0010. Performing the bitwise AND operation on these two values produces the binary result 0000 0000 0000 0010, which is decimal 2.
//! \n
//! (A & B)\n
//! 0000 0000 1010 1010\n
//! 0000 0000 0000 0010\n
//! -------------------\n
//! 0000 0000 0000 0010\n
//!
//! \param j
//! An unsigned integer showing the current KUKA pose command number.
//!
//! \param recVec
//! A vector containing all variables read from NI DAQ.
//!
//! \param phiVec
//! A vector containing variables read from Phidgets.
//!
//! \param calibratedPhidgets
//! A float array containing calibrated values for Phidgets data.
//!
//! \param atiVector
//! A vector containing force/torque data read from ATI controller.
//!
//! \param rot
//! A float array of the transformation matrix.
//!
//! \param ee
//! A float array of the transformation matrix with the attached tool considered.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void startLogging(System::ComponentModel::BackgroundWorker^ workerLog, System::Windows::Forms::TextBox^  txtAdr, tFriMsrData& msr, int selection, unsigned int& j, niVec & recVec, phidgetsVec & phiVec, float * calibratedPhidgets, atiVec & atiVector, float* ee);

//  ---------------------- Doxygen info ----------------------
//! \fn void rot2vec(float* rot, float* vec)
//!
//! \brief
//! This method rearranges the rotation matrix into a new float array to be fed into the trajectory generator. The new arrangement is meant for a better physical meaning of convergence.  
//!
//! \param rot
//! A float array of the transformation matrix.
//!
//! \param vec
//! A float output array of the new arrangement.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void rot2vec(float* rot, float* vec);

//  ---------------------- Doxygen info ----------------------
//! \fn void vec2rot(float* vec, float* rot)
//!
//! \brief
//! This method arranges the new vector back to the transformation matrix.
//!
//! \param vec
//! A float array of the new arrangement.
//!
//! \param rot
//! A float output array of the transformation matrix.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void vec2rot(float* vec, float* rot);

//  ---------------------- Doxygen info ----------------------
//! \fn void startFri(System::ComponentModel::BackgroundWorker^ worker, tFriMsrData &msr, tFriCmdData &cmd, friRemote &friInst, bool& trajFlag, unsigned int & j, unsigned int & poseNum, char * kukaWriteCommand, float * tool, float* trg, float & speed, float * cartStiffVals,float *simulinkTrg)
//!
//! \brief
//! This is the main method responsible for starting the FRI communications and sending the commands to KUKA and receiving data from KUKA.
//!
//! \param worker
//!  A seperate System Component Model Background Worker for FRI communications. 
//!
//! \param msr
//! The msr variable containing KUKA parameters.
//!
//! \param cmd
//! The cmd variable containing KUKA commands.
//!
//! \param friInst
//! The friInst variable containing KUKA parameters.
//!
//! \param trajFlag
//! A flag for indicating if KUKA UI is in middle of trajectory planned for a specific pose. If trajFlag is true, it shows that KUKA UI is busy applying a trajectory for reaching to a particular pose.
//!
//! \param j
//! An index for the pose that currently is being done. 
//!
//! \param poseNum
//! poseNum is the number of Cartesian poses set for KUKA to reach.
//!
//! \param kukaWriteCommand
//! A string of KUKA command for displaying purposes.
//!
//! \param tool
//! A float array of the attached tool Euler angles.
//!
//! \param trg
//! A float array of the attached the target pose Euler angles.
//!
//! \param speed
//! A float for setting the maximum velocity and acceleration for trajectory generation.
//!
//! \param cartStiffVals
//! A KUKA parameter for setting the robot stiffness for the Cartesian mode.
//!
//! \param simulinkTrg
//! A float array of the target joint variables sent from MATLAB Simulink.
//!
//! \return
//! The output is a void.
//!
//  ----------------------------------------------------------
void startFri(System::ComponentModel::BackgroundWorker^ worker, tFriMsrData &msr, tFriCmdData &cmd, friRemote &friInst, bool& trajFlag,  unsigned int & j, unsigned int & poseNum, char * kukaWriteCommand, float * tool, float* trg, float & speed, float * cartStiffVals,float *simulinkTrg);