#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h> 
#include <stdio.h>
#include "myLib.h"
#include "cvui.h"
// se hace llamado a las variables que contienen la configuracion para los filtros y valores de los umbrales de cada color
extern int Range_Red[3][2];
extern int Range_R_Color1[3][2];
extern int Range_R_Color2[3][2];
extern int Range_R_Color3[3][2];
extern int Set_Red[6],
    	   Set_R_Color1[6],
           Set_R_Color2[6],
           Set_R_Color3[6];

extern int Range_Blue[3][2];
extern int Range_B_Color1[3][2];
extern int Range_B_Color2[3][2];
extern int Range_B_Color3[3][2];
extern int Set_Blue[6],
    	   Set_B_Color1[6],
    	   Set_B_Color2[6],
    	   Set_B_Color3[6];

extern int Range_Ball[3][2],
	   Set_Ball[6];
extern bool Flag_Roi,Flag_imshow,Flag_printed;
vector<Vec3f>circlesB={0,0,0};
vector<Vec3f>circlesR={0,0,0};
vector<Vec3f>Ball={0,0,0};

int Sub_Cr_r_Color1[3]={0,0,0},
    Sub_Cr_r_Color2[3]={0,0,0},
    Sub_Cr_r_Color3[3]={0,0,0};

int Sub_Cr_b_Color1[3]={0,0,0},
    Sub_Cr_b_Color2[3]={0,0,0},
    Sub_Cr_b_Color3[3]={0,0,0};

int Sub_Cr_blue[3]={0,0,0};

int Sub_Cr_red[3]={0,0,0};
////////////////////////////////// Funcion filtro////////////////////////////////////////

/*

Esta funcion lo que hace es ocupar los valores del rango y set_value para encontra aglgun circulo existente dentro de la variable Roi_image

*/

int filtro(Mat Roi_image,int Rango[3][2],int Sub_cr[3],int Set_value[6]){


	Mat bin, salida,kernel, gray,Cap_clone=Roi_image.clone();
        vector<Vec3f>min_cr={0,0,0};       
	inRange( Roi_image , //variable de entreada de tres dimensiones 
		 Scalar(Rango[2][1],Rango[1][1],Rango[0][1]),//limite minimo   //B - G - R
		 Scalar(Rango[2][0],Rango[1][0],Rango[0][0]), // limite maximo //B - G - R
		 salida);// variable de salida tipo binaria
        cvtColor(salida, salida, CV_GRAY2BGR);// transformacion de binaria a una matriz de 3 dimensiones 
       	cvtColor(salida, salida, CV_BGR2GRAY); // transformacion a escala de grises
	
	kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
			
	cv::morphologyEx(salida, bin, MORPH_CLOSE, kernel);
	medianBlur(bin, bin , 5);
	GaussianBlur( bin, gray, Size(3, 3), 2, 2 );
	HoughCircles(gray,min_cr, CV_HOUGH_GRADIENT,Set_value[0],  gray.rows/Set_value[1], Set_value[2], Set_value[3],Set_value[4],Set_value[5]);
    	
	Sub_cr[0]=cvRound(min_cr[0][0]);
	Sub_cr[1]=cvRound(min_cr[0][1]);
	Sub_cr[2]=cvRound(min_cr[0][2]);
}
///////////////////////////////////////////////////////////////////////////////////////

/*###############################################################################################
  #########										#########
  #########                       	FILTRO ROJO					#########
  #########										#########
  ###############################################################################################
*/




int detector_cir_rojos(Mat imagen, double Datos_cr_r[3][3]){

Mat bin,gray,salida,kernel, Rojo_c=imagen.clone(); // variables a ocupar y clonacion de imagen para mantener muestra original
//////////////////////filtro//////////////////////////////////////////////////////////
	 inRange(Rojo_c,//variable de entreada de tres dimensiones 
		Scalar(Range_Red[2][1],Range_Red[1][1],Range_Red[0][1]),//limite minimo   //B - G - R
		Scalar(Range_Red[2][0],Range_Red[1][0],Range_Red[0][0]), // limite maximo //B - G - R
		salida);// variable de salida tipo binaria
         cvtColor(salida, salida, CV_GRAY2BGR);// transformacion de binaria a una matriz de 3 dimensiones 
/////////////////////conversion///////////////////////////////////////////////////////
        
	 cvtColor(salida, salida, CV_BGR2GRAY); // transformacion a escala de grises
////////////////////difuminacion/////////////////////////////////////////////////////
	kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
			
	cv::morphologyEx(salida, bin, MORPH_CLOSE, kernel);
	medianBlur(bin, bin , 5);
	 GaussianBlur( bin, gray, Size(3, 3), 2, 2 );

/////////////////////deteccion////////////////////////////////////////////////////////
	HoughCircles(gray, circlesR, CV_HOUGH_GRADIENT,2, gray.rows/45, 40, 36,14,22);
     	for ( int i = 0; i < circlesR.size(); i++ ) {
		Point center(cvRound(circlesR[i][0]),
	      	             cvRound(circlesR[i][1]));
	        int radius = cvRound(circlesR[i][2]);
	
////////////////////// RECORTAR ///////////////////////////////////////////////////////
/*para  cada circulo encontrado dentro de la iteracion este sera recortado por un ciero diametro
y se generara una nueva imagen llamada roi*/
	if(cvRound(circlesR[i][0])>15&&cvRound(circlesR[i][1])>15&&cvRound(circlesR[i][2])>5){
	Rect myRoi(circlesR[i][0]-circlesR[i][2]-4,
	 	     circlesR[i][1]-circlesR[i][2]-4,
		     circlesR[i][2]*2+10,
		     circlesR[i][2]*2+10);
        Mat roi= Rojo_c(myRoi);	
////////////////// DETECTAR COLOR Y POSICION////////////////////////////////////////////
/*al momento de obtener la imagen recortada lo que procede es encontrar el color 
del circulo pequeño que se encuntra dentro del circulo mas grande, cada funcion 
filtro retornara un vector vacio en el caso de que no se encuentre ningun circulo pequeño*/
      	filtro(roi,Range_Red,Sub_Cr_red,Set_Red);
	filtro(roi,Range_R_Color1,Sub_Cr_r_Color1,Set_R_Color1);
	filtro(roi,Range_R_Color2,Sub_Cr_r_Color2,Set_R_Color2);
	filtro(roi,Range_R_Color3,Sub_Cr_r_Color3,Set_R_Color3);
	double Pendiente=0;
//////////////////Asiganacion de jugador////////////////////////////////////////////////
/* Lo que se hace en los siguentes if es generar condiciones para asignar el jugador 
a su casilla respectiva en las matriz Datos_cr_r 
*/
	if(0<Sub_Cr_r_Color1[0] && 0<Sub_Cr_r_Color1[1]){	 
         Pendiente = Sub_Cr_r_Color1[1]-Sub_Cr_red[1] /
//		    ----------------------------
		    Sub_Cr_r_Color1[0]-Sub_Cr_red[0];	 
	Datos_cr_r[0][0] = cvRound(circlesR[i][0]);
	Datos_cr_r[1][0] = cvRound(circlesR[i][1]);	
	Datos_cr_r[2][0] = Pendiente;
	
	}

	if(0<Sub_Cr_r_Color2[0] && 0<Sub_Cr_r_Color2[1]){
    	Pendiente = Sub_Cr_r_Color2[1]-Sub_Cr_red[1] /
//		    ----------------------------
		    Sub_Cr_r_Color2[0]-Sub_Cr_red[0];
	Datos_cr_r[0][1] = cvRound(circlesR[i][0]);
	Datos_cr_r[1][1] = cvRound(circlesR[i][1]);	
	Datos_cr_r[2][1] = Pendiente;

	}

	if(0<Sub_Cr_r_Color3[0]&& 0<Sub_Cr_r_Color3[1]){
 	Pendiente = Sub_Cr_r_Color3[1]-Sub_Cr_red[1] /
//		     ----------------------------
		    Sub_Cr_r_Color3[0]-Sub_Cr_red[0];
	Datos_cr_r[0][2] = cvRound(circlesR[i][0]);
	Datos_cr_r[1][2] = cvRound(circlesR[i][1]);	
	Datos_cr_r[2][2] = Pendiente;
	}
	}
	}//fin del for

}


/*###############################################################################################
  #########										#########
  #########                       	FILTRO AZUL					#########
  #########										#########
  ###############################################################################################
*/

int detector_cir_azules(Mat imagen, double Datos_cr_B[3][3]){

	Mat bin,gray,salida, Azul_c=imagen.clone(),kernel; // variables a ocupar y clonacion de imagen para mantener muestra original
//////////////////////filtro//////////////////////////////////////////////////////////
	 inRange(Azul_c,//variable de entreada de tres dimensiones 
		Scalar(Range_Blue[2][1],Range_Blue[1][1],Range_Blue[0][1]),//limite minimo   //B - G - R
		Scalar(Range_Blue[2][0],Range_Blue[1][0],Range_Blue[0][0]), // limite maximo //B - G - R
		salida);// variable de salida tipo binaria
         cvtColor(salida, salida, CV_GRAY2BGR);// transformacion de binaria a una matriz de 3 dimensiones 
/////////////////////conversion///////////////////////////////////////////////////////
        
	 cvtColor(salida, salida, CV_BGR2GRAY); // transformacion a escala de grises
////////////////////difuminacion/////////////////////////////////////////////////////

	kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
			
	cv::morphologyEx(salida, bin, MORPH_CLOSE, kernel);
	medianBlur(bin, bin , 5);
	GaussianBlur( bin, gray, Size(3, 3), 2, 2 );

/////////////////////deteccion////////////////////////////////////////////////////////
	HoughCircles(gray, circlesB, CV_HOUGH_GRADIENT,2, gray.rows/45, 40, 36,14,20);
     	for ( int i = 0; i < circlesB.size(); i++ ) {
		Point center(cvRound(circlesB[i][0]),
	      	             cvRound(circlesB[i][1]));
	        int radius = cvRound(circlesB[i][2]);
/////////////////////RECORTAR/////////////////////////////////////////////////////////
/*para  cada circulo encontrado dentro de la iteracion este sera recortado por un ciero diametro
y se generara una nueva imagen llamada roi*/
	if(cvRound(circlesR[i][0])>15&&cvRound(circlesR[i][1])>15&&cvRound(circlesR[i][2])>5){
	 
	 Rect myRoi(circlesB[i][0]-circlesB[i][2]-4,
	 	     circlesB[i][1]-circlesB[i][2]-4,
		     circlesB[i][2]*2+10,
		     circlesB[i][2]*2+10);
          Mat roi= Azul_c(myRoi);

//////////// DETECTAR COLOR Y POSICION/////////////////////////////////////////////////////
/*al momento de obtener la imagen recortada lo que procede es encontrar el color 
del circulo pequeño que se encuntra dentro del circulo mas grande, cada funcion 
filtro retornara un vector vacio en el caso de que no se encuentre ningun circulo pequeño*/	
      	filtro(roi,Range_Blue,Sub_Cr_blue,Set_Blue);
	filtro(roi,Range_B_Color1,Sub_Cr_b_Color1,Set_B_Color1);
	filtro(roi,Range_B_Color2,Sub_Cr_b_Color2,Set_B_Color2);
	filtro(roi,Range_B_Color3,Sub_Cr_b_Color3,Set_B_Color3);
 
     	int Xo= Sub_Cr_blue[0],Yo= Sub_Cr_blue[1];
	float Pendiente=0;
	

//////////////////Asiganacion de jugador////////////////////////////////////////////////
/* Lo que se hace en los siguentes if es generar condiciones para asignar el jugador 
a su casilla respectiva en las matriz Datos_cr_B 
*/
	if(0<Sub_Cr_b_Color1[0] && 0<Sub_Cr_b_Color1[1]){	 
         Pendiente = Sub_Cr_b_Color1[1]-Yo /
//		     ----------------------------
		     Sub_Cr_b_Color1[0]-Xo;
	Datos_cr_B[0][0] = cvRound(circlesB[i][0]);
	Datos_cr_B[1][0] = cvRound(circlesB[i][1]);	
	Datos_cr_B[2][0] = Pendiente;
	}
	
	if(0<Sub_Cr_b_Color2[0] && 0<Sub_Cr_b_Color2[1]){ 
         Pendiente = Sub_Cr_b_Color2[1]-Yo /
//		     ----------------------------
		     Sub_Cr_b_Color2[0]-Xo;      
	Datos_cr_B[0][1] = cvRound(circlesB[i][0]);
	Datos_cr_B[1][1] = cvRound(circlesB[i][1]);	
	Datos_cr_B[2][1] = Pendiente;

	}
	if(0<Sub_Cr_b_Color3[0] && 0<Sub_Cr_b_Color3[1]){ 
         Pendiente = Sub_Cr_b_Color3[1]-Yo /
//		     ----------------------------
		     Sub_Cr_b_Color3[0]-Xo;      
	Datos_cr_B[0][2] = cvRound(circlesB[i][0]);
	Datos_cr_B[1][2] = cvRound(circlesB[i][1]);	
	Datos_cr_B[2][2] = Pendiente;
	}
	}
	}//fin del for
	
	
}

//------------------------------------------------//
///////// Ajuste de margen//////////////
/* Esta seccion sirve para generar un margen a la imagen que queremos procesar como hay casos en los cuales no se ocupara toda la imgen bruta obtenida por la camara se creo esta instancia para poder recortar solo la seccion de interes esta funcion es de tipo Mat por lo cual retorna la imagen ya recortada
*/
Rect2d r ;
Rect interes; 
extern int x,y,w,h;

Mat Roi_image(Mat imagen,bool flag){
if (x==0 || y ==0 ||flag==1){
r = selectROI(imagen);
 x=(int)r.x;
 y=(int)r.y;
 w=(int)r.width;
 h=(int)r.height;
destroyAllWindows(); 
Rewrite_file();
}
interes = Rect(x,y,w,h);
Mat ROI=imagen(interes);
return ROI;
}


//------------------------------------------------//
////Se hace llamado la funcion de filtro para encontrar la pelota
void detector_Ball(Mat imagen, int Datos_Ball[3]){
filtro(imagen,Range_Ball,Datos_Ball,Set_Ball);
}
//------------------------------------------------//
/*
Esta funcion como su nombre lo dice muestra en consola los valores 
de la posicion de cada jugador y los dibuja en la imagen */
void Printed(bool printed_circles,double Rd[3][3],double Bl[3][3],int ball[3],Mat& imagen){

int Red[3][3];
int Blue[3][3];
for(int county =0;county<3;county++){
	for(int countx =0;countx<3;countx++){
		Red[countx][county]= (int)Rd[countx][county];}
}

for(int county =0;county<3;county++){
	for(int countx =0;countx<3;countx++){
		Blue[countx][county]= (int)Bl[countx][county];}
}
if(Flag_printed){
system("clear");
printf("team Red \n");
printf("Player 1-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n",Red[0][0],Red[1][0],Red[2][0],Sub_Cr_r_Color1[0],Sub_Cr_r_Color1[1]);
printf("Player 2-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n",Red[0][1],Red[1][1],Red[2][1],Sub_Cr_r_Color2[0],Sub_Cr_r_Color2[1]);
printf("Player 3-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n\n",Red[0][2],Red[1][2],Red[2][2],Sub_Cr_r_Color3[0],Sub_Cr_r_Color3[1]);
printf("team Blue \n");
printf("Player 1-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n",Blue[0][0],Blue[1][0],Blue[2][0],Sub_Cr_b_Color1[0],Sub_Cr_b_Color1[1]);
printf("Player 2-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n",Blue[0][1],Blue[1][1],Blue[2][1],Sub_Cr_b_Color2[0],Sub_Cr_b_Color2[1]);
printf("Player 3-->x :%d , y:%d ,P:%d\nsub Circle: x: %d , y: %d \n\n",Blue[0][2],Blue[1][2],Blue[2][2],Sub_Cr_b_Color3[0],Sub_Cr_b_Color3[1]);
printf("Ball: x: %d, y:%d\n\n",ball[0],ball[1]);
}
if(Flag_printed){
	Point center0(Red[0][0],Red[1][0]);
	
	circle( imagen, center0, 20, Scalar(0,0,255), 3);
	
	putText(imagen, "R1", center0, FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,0,255), 2);	

	Point center(Red[0][1],Red[1][1]);
	circle( imagen, center, 20, Scalar(0,0,255), 3);
	putText(imagen, "R2", center, FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(255,255,0), 2);

	Point center1(Red[0][2],Red[1][2]);	
	circle( imagen, center1, 20, Scalar(0,0,255), 3);
	putText(imagen, "R3", center1, FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,255,0), 2);
	
	Point centerB0(Blue[0][0],Blue[1][0]);
	circle(imagen, centerB0, 20, Scalar(255,0,0), 3);
	putText(imagen, "B1", centerB0, FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,0,255), 2);

	Point centerB1(Blue[0][1],Blue[1][1]);
	circle(imagen, centerB1, 20, Scalar(255,0,0), 3);
	putText(imagen, "B2", centerB1, FONT_HERSHEY_SIMPLEX,0.5, CV_RGB(255,255,0), 2);

	Point centerB2(Blue[0][2],Blue[1][2]);
	circle(imagen, centerB2, 20, Scalar(255,0,0), 3);
	putText(imagen, "B3", centerB2, FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0,255,0), 2);
   	
	Point Ball(ball[0],ball[1]);
	circle(imagen, Ball, 5, Scalar(0,0,255), 3);
	
}
}
//---------------------------------------------------------------------------------///

void Run_Algorithm(Mat& imagen,double Red[3][3],double Blue[3][3],int Ball[3]){
	if(imagen.empty()){
	printf("ERROR /// funcion Run_Algorithm --> no contiene imagen para procesar\n");
	}
	else{	
	imagen=Roi_image(imagen,Flag_Roi);
	Flag_Roi=0;
	detector_cir_rojos(imagen,Red);
	detector_cir_azules(imagen,Blue);
	detector_Ball(imagen,Ball);
	Printed(Flag_printed,Red,Blue,Ball,imagen);
	if(Flag_imshow){
	imshow("Picture",imagen);}
	}		
}	


