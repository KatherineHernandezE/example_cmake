
//###############################################################################################
//#########										#########
//#########                       	Libreria para interfaz grafica          	#########
//#########										#########
//###############################################################################################
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h> 
#include <stdio.h>
#include "videoio.hpp"
#include "myLib.h"
#include "cvui.h"
#include "EnhancedWindow.h"
#define WINDOW_NAME0	"Ajustes"
#define WINDOW_NAME1	"Presentacion de proyecto"
#define WINDOW_NAME2	"Configuracion"
#define WINDOW_NAME	"Ajustes de valores RGB maximos y minimos"
#define CAM_SET_DEfAULT_WIDTH 640
#define CAM_SET_DEfAULT_HEIGHT 480
#define	CAM_SET_DEfAULT_NUMBER 0
#define COLOR_BLANCO 0xffffff
#define SIZE  0.4
using namespace std;
using namespace cv;


cv::Mat lab = cv::imread("labsei.png", cv::IMREAD_COLOR);
cv::Mat logo = cv::imread("logofacu.jpg", cv::IMREAD_COLOR);

bool flag_IG = true;
extern int WIDTH;
extern int HEIGHT;
extern int N_Cam;

extern int Range_Red[3][2];
extern int Range_Blue[3][2];

extern int Set_Red[6],
    	   Set_R_Color1[6],
           Set_R_Color2[6],
           Set_R_Color3[6];


extern int Range_R_Color1[3][2];
extern int Range_R_Color2[3][2];
extern int Range_R_Color3[3][2];

extern int Set_Blue[6],
    	   Set_B_Color1[6],
    	   Set_B_Color2[6],
    	   Set_B_Color3[6];

extern int Range_B_Color1[3][2];
extern int Range_B_Color2[3][2];
extern int Range_B_Color3[3][2];

extern int Range_Ball[3][2],Set_Ball[6];



int isWindowOpen(const cv::String &name) {
	return cv::getWindowProperty(name, cv::WND_PROP_AUTOSIZE) != -1;
}
void closeWindow(const cv::String &name) {
	cv::destroyWindow(name);
	cv::waitKey(1);
}

int NumberCam;
void config(){
int select;
system("clear");
printf("Declare que camara quiere conectar:\n 0---> DEFAULT\n 1--->USB1\n 2--->USB2\n\n");
printf("---> ");
scanf("%d",&NumberCam);
system("clear");
if(NumberCam == 0){

printf("se asignara valores predefinidos para la webcam ...\n resolucion: 640x480 \n");
WIDTH =CAM_SET_DEfAULT_WIDTH;
HEIGHT = CAM_SET_DEfAULT_HEIGHT;
printf("configurando camara espere...\n ingrese un valor en la consola para continuar\n");
bool flag = true;;
while(flag){if(getchar() != '\n') flag = false;}

}
else{
printf("Seleccione con que resolucion quiere trabajar: \n 1--->800x600\n 2--->1280x720\n");
scanf("%d",&select);
switch(select){
case 1:{
system("clear");
printf("usted ha seleccionado la resolucion 800x600\n");
WIDTH =800;
HEIGHT = 600;
printf("configurando camara espere...\n ingrese un valor en la consola para continuar\n");
bool flag = true;;
while(flag){if(getchar() != '\n') flag = false;}
}
break;
case 2:{
system("clear");
printf("usted ha seleccionado la resolucion 1280x720\n");
WIDTH =1280;
HEIGHT = 720;
printf("configurando camara espere...\n ingrese un valor en la consola para continuar");
bool flag = true;;
while(flag){if(getchar() != '\n') flag = false;}
}
break;
}
}
}

void menu_Consola(bool flag_consola){
	if(flag_consola){	
	int count;
	system("clear");
	printf("Seleccione una de las alternativas :\n 1-Ejecutar programa sin interfaz Grafica\n 2-Ejecutar programa con interfaz grafica y calibracion\n 3-Version del programa \n");
	printf("---> ");
	scanf("%d",&count);
	switch(count){
		case 1 :{
			config();
			flag_IG = false;
			system("clear");
			}
		break;
		//--------------------------------------\\//----------//
		case 2 :{
			flag_IG = true;
			system("clear");}
		break;
		//--------------------------------------\\//----------//
		case 3 :{
			bool flag = true;	
			system("clear");
			printf("\ncvui v.%s\n\n", cvui::VERSION);
			printf("Ultima modificacion: Octubre----2018\n\n");
			printf("Desarrollado por: Miguel Gozalez 2018\n\n");
			printf("Ingrese cualquier valor para continuar: ...\n ");
			printf("-->");	
			while(flag){if(getchar() != '\n') flag = false;}
			menu_Consola(flag_consola);	
			}
		break;
}
}
	 else{flag_IG=true;}
}



//--------------------------------------------------------------------------//


void GUI_presentacion(const cv::String &Windows, bool flag_GUI){
if(flag_GUI){
cvui::init(Windows);
Mat frame_present = cv::Mat(185, 450, CV_8UC3); 
while(true){
	frame_present = cv::Scalar(49, 52, 49);
	cvui::image(frame_present, 10, 20, lab);
	cvui::image(frame_present, 310, 10, logo);
	cvui::text(frame_present, 10, 75, "Bienvenido al programa detector de circulos", SIZE, COLOR_BLANCO);
	cvui::text(frame_present, 10, 100, "desarrollado por: ", SIZE, COLOR_BLANCO);
	cvui::text(frame_present, 10, 125, "Miguel Gonzalez", SIZE, COLOR_BLANCO);

	char c=(char)waitKey(25);
	if(c==27||cvui::button(frame_present, 190, 140, "&Siguiente")||c==32)
	break;
	cvui::update();
	cv::imshow(Windows, frame_present);
}
closeWindow(Windows);}

}
//--------------------------------------------------------------------------//

void GUI_set_cam(const cv::String &Windows_Set,bool flag_SetCam){
if(flag_SetCam){
	Mat frame_set = cv::Mat(185, 450, CV_8UC3);
	cvui::init(Windows_Set);
bool R1=true,R2=false ,R3=false;
	while(true){
		frame_set = cv::Scalar(49, 52, 49);
		cvui::image(frame_set, 10, 20, lab);
		char c=(char)waitKey(25);	
		if(c==27||c==32||cvui::button(frame_set, 190, 140, "&Continuar"))break;
		cvui::counter(frame_set, 10,95, &N_Cam);
		cvui::text(frame_set, 100, 100, " <- Escoga que camara quiere conectar", SIZE, COLOR_BLANCO);
		cvui::text(frame_set, 110, 120, "recuerde que los valores varian entre 0 y 3", SIZE, COLOR_BLANCO);
		cvui::text(frame_set, 140, 15, "Escoga una resolucion para la camara", SIZE, COLOR_BLANCO);
		if(N_Cam<1){if(cvui::checkbox(frame_set, 150, 35, "640x480(default para webcam PC)", &R1)){
					WIDTH =640;
					HEIGHT = 480;
				R2=false;R3=false;	
					}}
		if(N_Cam>=1){
			R1=false;
			
			if(cvui::checkbox(frame_set, 160, 55, "800x600", &R2)){
					WIDTH =800;
					HEIGHT = 600;
					R3=false;}
			if(cvui::checkbox(frame_set, 170, 75, "1280x720", &R3)){
					WIDTH =1280;
					HEIGHT = 720;
					R2=false;}   
		
		}
						
		cvui::update();
		cv::imshow(Windows_Set, frame_set);
	}
	closeWindow(Windows_Set);
	}
}
//---------------------------------------------------------------------//


//---------------------------------------------------------------------//
void threshold_Trackbar(int RGB_RANGE[3][2],int Set_value[6]){
	
	cv::Mat frame = cv::Mat(350, 700, CV_8UC3);
	cvui::init(WINDOW_NAME);
	VideoCapture cap(N_Cam);
	cap.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
	vector<Vec3f>circles={0,0,0}; 
	EnhancedWindow Set_high(220, 140, 250, 140, "Ajuste avanzado");
	EnhancedWindow Set_Algorithm(220, 170, 250, 160, "Ajuste de algoritmo");

	int large_stick = 150, Div = 45, Max = 50,Min = 0,dp=1;  
	bool flag_bin=false,flag_ImageOr=false, flag_Algoritmo=false,value_dp=true,flag_dp=false,flag_image=false;
	
	
	while (true) {
		cvui::context(WINDOW_NAME);
		frame = cv::Scalar(49, 52, 49);
cvui::text(frame, 70, 15, "Ajusta los valores maximos y minimos hasta que el algoritmo detecte los tres circulos", SIZE, COLOR_BLANCO);
		if (waitKey(20) == 27|| cvui::button(frame,400, 300, "Volver")) {
			if(isWindowOpen("blur")){closeWindow("blur");}
			if(isWindowOpen("Cam01")){closeWindow("Cam01");}
			cap.release();			
			break;
			
		}
		Set_Algorithm.begin(frame,false);
		if(!Set_Algorithm.isMinimized()){
		cvui::beginRow(-1,-1,5);
		cvui::text("Dp:              ");
		cvui::counter(&Set_value[0]);
		cvui::endRow();
		cvui::space(5);		
		cvui::beginRow(-1,-1,5);
		cvui::text("Canny Ths:");
		cvui::trackbar(large_stick,&Set_value[2], 1, 200,3,"%0.0Lf",0,1);		
		cvui::endRow();
		cvui::space(5);		
		cvui::beginRow(-1,-1,5);
		cvui::text("Ths center:");
		cvui::trackbar(large_stick,&Set_value[3], 1, 100,3,"%0.0Lf",0,1);		
		cvui::endRow();
		}
		Set_Algorithm.end();
		Set_high.begin(frame,false);
           	if (!Set_high.isMinimized()) {
		cvui::beginRow(-1,-1,5);
		cvui::text("Distancia minima:  ");  		
		cvui::counter(&Set_value[1]);
		cvui::endRow();
	
		cvui::space(10);
		cvui::beginRow(-1,-1,5);  
		cvui::text("Radio maximo:     ");  		
		cvui::counter( &Set_value[5]);
		cvui::endRow();

		cvui::space(10);
		cvui::beginRow(-1,-1,4);
		cvui::text("Radio minimo:      ");  		
		cvui::counter(&Set_value[4]);		
		cvui::endRow();
		}
		Set_high.end();


	
		if(cvui::checkbox(frame, 220, 55, "Conectar camara", &flag_image)){
			cvui::checkbox(frame, 230, 75, "mostrar imagen actual", &flag_ImageOr);
			cvui::checkbox(frame, 240, 95, "Bin", &flag_bin);
			cvui::checkbox(frame, 250, 115, "aplicar algoritmo", &flag_Algoritmo);}	
		

		cvui::window(frame, 20, 50, 180, 280, "Ajuste RGB valor minimo");
		cvui::beginColumn(frame, 35, 80, -1, -1, 10);
		cvui::printf(0.35, 0xcccccc, "RED: %d", RGB_RANGE[0][1]);
		if (cvui::trackbar(large_stick, &RGB_RANGE[0][1], 0, 255,3,"%0.0Lf")) {
			}
		cvui::printf(0.35, 0xcccccc, "GREEN: %d",RGB_RANGE[1][1]);
			if (cvui::trackbar(large_stick, &RGB_RANGE[1][1], 0, 255,3,"%0.0Lf")) {
			}
		cvui::printf(0.35, 0xcccccc, "BLUE: %d",RGB_RANGE[2][1]);
			if (cvui::trackbar(large_stick, &RGB_RANGE[2][1], 0, 255,3,"%0.0Lf")) {
			}
		cvui::printf(0.35, 0xcccccc, "RGB: %d,%d,%d", RGB_RANGE[0][1], RGB_RANGE[1][1], RGB_RANGE[2][1]);

		cvui::endColumn();

		cvui::window(frame, 500, 50, 180, 280, "Ajuste RGB valor maximo");
		cvui::beginColumn(frame, 515, 80, -1, -1, 10);
		cvui::printf(0.35, 0xcccccc, "RED: %d", RGB_RANGE[0][0]);
			if (cvui::trackbar(large_stick, &RGB_RANGE[0][0], 0,255, 3, "%0.0Lf")) {
			}
		cvui::printf(0.35, 0xcccccc, "GREEN: %d", RGB_RANGE[1][0]);
			if (cvui::trackbar(large_stick, &RGB_RANGE[1][0], 0,255, 3, "%0.0Lf")) {
			}
		cvui::printf(0.35, 0xcccccc, "BLUE: %d", RGB_RANGE[2][0]);
			if (cvui::trackbar(large_stick, &RGB_RANGE[2][0], 0,255, 3, "%0.0Lf")) {
			}			
		cvui::printf(0.35, 0xcccccc, "RGB: %d,%d,%d", RGB_RANGE[0][0], RGB_RANGE[1][0], RGB_RANGE[2][0]);
		cvui::endColumn();
			
		cvui::update();
		
		if(isWindowOpen("blur")&&!flag_bin){closeWindow("blur");}
		if(isWindowOpen("Cam01")&&!flag_ImageOr){closeWindow("Cam01");}

		if(flag_image){	
			Mat cam;
                	cap >> cam;
				
			Mat bin,gray,kernel,salida;
			inRange( cam , //variable de entreada de tres dimensiones 
				 Scalar(RGB_RANGE[2][1],RGB_RANGE[1][1],RGB_RANGE[0][1]),//limite minimo   //B - G - R
				 Scalar(RGB_RANGE[2][0],RGB_RANGE[1][0],RGB_RANGE[0][0]), // limite maximo //B - G - R
				 bin);// variable de salida tipo binaria
	        
			cvtColor(bin, bin, CV_GRAY2BGR);//
			cvtColor(bin, bin, CV_BGR2GRAY);
			kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
			cv::morphologyEx(bin, salida, MORPH_CLOSE, kernel);
			medianBlur(salida, salida , 5);
			GaussianBlur( salida, gray, Size(3, 3), 2, 2 );
			if(flag_bin)imshow("blur",gray);
			if(flag_Algoritmo){
			HoughCircles(gray,circles, CV_HOUGH_GRADIENT,Set_value[0], gray.rows/Set_value[1],Set_value[2], Set_value[3],Set_value[4],Set_value[5]);
			
			for( size_t i = 0; i < circles.size(); i++ )
				{
				Point center(cvRound(circles[i][0]), 
					         cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);

				circle( cam, center, 3, Scalar(0,255,0), 3);
				circle( cam, center, radius, Scalar(0,0,255), 3);
				char myString[20];
				sprintf(myString,"x:%d y:%d",cvRound(circles[i][0]),cvRound(circles[i][1]));
				putText(cam,myString,center, FONT_HERSHEY_SIMPLEX, 1, CV_RGB(0,0,0), 1);}}
			if(flag_ImageOr)imshow("Cam01",cam);
			
		}
		else{flag_ImageOr =false;
			flag_bin= false;			
			flag_Algoritmo=false;
			}
		cv::imshow(WINDOW_NAME, frame);	
	}
	cap.release();
	closeWindow(WINDOW_NAME);
	Rewrite_file();

}
//---------------------------------------------------------------------//
void GUI_Set_filter(int mainColor[3][2], int Set_Main[6],
		    int color1[3][2], int Set_color1[6],
		    int color2[3][2], int Set_color2[6],
		    int color3[3][2], int Set_color3[6],
		    int i){
cv::Mat frame = cv::Mat(220, 200, CV_8UC3);
char cat[30];
if(i == 1){
sprintf(cat,"Ajustes color rojo");
}
else{
sprintf(cat,"Ajustes color Azul");

}
cvui::init("Ajustes de equipo");
	while(1){
	cvui::context("Ajustes de equipo");	
	frame = cv::Scalar(49, 52, 49); 
        if (cvui::button(frame, 10, 10, cat)) {
	threshold_Trackbar(mainColor,Set_Main);}
	if (cvui::button(frame, 10, 50, "Ajuste filtro &juador 1")) {
	threshold_Trackbar(color1,Set_color1);}
	if (cvui::button(frame, 10, 90, "Ajuste filtro &juador 2")) {
	threshold_Trackbar(color2,Set_color2);}
	if (cvui::button(frame, 10, 130, "Ajuste filtro &juador 3")) {
	threshold_Trackbar(color3,Set_color3);}
	cvui::update();	
	char c=(char)waitKey(25);
	if(c==27 ||cvui::button(frame,10, 170, "&Volver"))break;
	cv::imshow("Ajustes de equipo", frame);
	}
	closeWindow("Ajustes de equipo");
}


//---------------------------------------------------------------------//
void GUI_settings(bool flag_settings){
if(flag_settings){
cv::Mat frame = cv::Mat(200, 250, CV_8UC3);
bool flagcam = false;

cvui::init(WINDOW_NAME0);
	  while(1){
		 frame = cv::Scalar(49, 52, 49);
	        // Capture frame-by-frame
	    	  bool eco = true;
	  	  bool flag = false;
		  cvui::context(WINDOW_NAME0);
		if (cvui::button(frame, 10, 10, "Ajuste jugadores &Rojos")) {
		GUI_Set_filter(Range_Red,Set_Red,
			       Range_R_Color1,Set_R_Color1,
			       Range_R_Color2,Set_R_Color2,
			       Range_R_Color3,Set_R_Color3,
			       1);}
		if (cvui::button(frame, 10, 50, "Ajuste jugadores &Azules")) {
		GUI_Set_filter(Range_Blue,Set_Blue,
			       Range_B_Color1,Set_B_Color1,
			       Range_B_Color2,Set_B_Color2,
			       Range_B_Color3,Set_B_Color3,
			       2);}
		if (cvui::button(frame, 10, 90, "Ajuste filtro pelota")) {
		threshold_Trackbar(Range_Ball,Set_Ball);}		
		cvui::update();
	    	char c=(char)waitKey(25);
		if(c==27 ||cvui::button(frame,10, 140, "&Iniciar Algoritmo"))break;
		cv::imshow(WINDOW_NAME0, frame);
		 }
	closeWindow(WINDOW_NAME0);
	}//fin del while

}

//-------------------------------------------------------------------------------------//
/*
De forma resumudad si llamamos esta funcion en el main del codigo accederemos a la interfaz grafica para poder modificar los valores de las variables para cada equipo 
*/
void GUI_MENU_MAIN_ALL(bool Flag_MAIN_GUI){


GUI_presentacion(WINDOW_NAME1,Flag_MAIN_GUI);//flag_ig es una variable asignada en myLib


GUI_set_cam(WINDOW_NAME2,Flag_MAIN_GUI);

GUI_settings(Flag_MAIN_GUI);

Rewrite_file();
}

//---------------------------------------------------------------------//
void load_data(){
Read_file();
}

