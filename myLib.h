#ifndef _myLib_	
#define _myLib_
//------------------------------------------------------------------//
#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h> 
#include <stdio.h>
#include "cvui.h"
using namespace std;
using namespace cv;
//-------------------------------------------------------------------//
// ------------------------------------------------------------------//
void load_data();
void Run_Algorithm(Mat& imagen,double Red[3][3],double Blue[3][3],int Ball[3]);
void menu_Consola(bool flag);    // Declaración de nuestras funciones
void GUI_MENU_MAIN_ALL(bool Flag_MAIN_GUI);
int Read_file();
int Rewrite_file();
int detector_cir_rojos(Mat imagen,int k, double Datos_cr_r[3][3]);
int detector_cir_azules(Mat imagen, int k, double Datos_cr_B[3][3]);
void detector_Ball(Mat imagen, double Datos_Ball[3]);
Mat Roi_image(Mat imagen);
//------------------------------------------------------------------
//------------------------------------------------------------------
#endif

