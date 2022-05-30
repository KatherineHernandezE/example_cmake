/////librerias de opencv y de c++
#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>  
#include <stdio.h>  

/////librerias de algoritmo y UI

#include "myLib.h"
#include "myGui.c"
#include "myLec.c"
#include "myAlgorithm.c"
#define CVUI_IMPLEMENTATION
#include "cvui.h"

using namespace std;
using namespace cv;
///////////////////////////////////////////////////////////////////////
//                         x y &
double Datos_cr_R[3][3] = {0,0,0, //1 
            	           0,0,0, // 2		se inicializan las variables para el algoritmo
			   0,0,0};// 3		en los cuales se ocuparan dos matrices de 3x3 		
//                         x y &		para guardar la poscion y orientacion  para los dos equipos.
double Datos_cr_B[3][3] = {0,0,0,  // 1		
       	                   0,0,0,  // 2		Para la pelota solo se ocupara un vector de 3 dimensiones para 
			   0,0,0,};// 3		guardar posicion y radio.
//		     X Y R			
int Datos_Ball[3] = {0,0,0};
/////////////////////////////////////////////////////////////////////////


int main(int argc, char **argv){

load_data();// load_data() es una funcion en la cual se hace lectura de los txt en donde se encuentran las configuraciones de la camara y los filtros

VideoCapture cap(N_Cam);         //se inicializa el objeto "cap" en la cual hara lectura a del dispositivo señalado         		                         en "N_cam" el cual esta guardado en el archivo "previous_setting.txt"

cap.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);// cap.set hace referencio a la configuracion de la camara en la cual cap.set
(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);     //"CV_CAP_PROP_FRAME_WIDTH" y "CV_CAP_PROP_FRAME_HEIGHT" es una referencia a la 					       //direccion de memoria de la camara para cambiar los valores de resolucion en el 				       //ancho y largo.


///////////////////////////// inicio de bucle ///////////////////////////////////////////////////////////
while(true){
Mat imagen;
cap >> imagen;
Run_Algorithm(imagen,Datos_cr_R,Datos_cr_B,Datos_Ball);
		//Primero creamos una matriz llamada "imagen" en la cual sera rellenado por una matriz de 3  		          dimenciones (BGR) que sera la imagen capturada por la webcam en el objeto "cap".                         	       	  Ahora bien Run_Algorithm es una fucion que se encuentra en myAlgorithm y se compone de la sgt forma       			  Run_Algorithm(Mat Imagen,double Red[3][3],double Blue[3][3]) esta funcion necesita una variable Mat que 			  debe contener una matriz de 3 dimenciones la cual sera modificada segun lo que se especifique en 			  "previous_setting.txt" ahora las otra dos variables double red y blue se les rellenara con informacion de 			  posicion y direccion, donde el numero del jugador sera indicado por el llamado en la direccion de de la  			matriz por ejemplo:  	                
printf("X:%f Y:%f &:%f \n",Datos_cr_R[0][0],Datos_cr_R[0][1],Datos_cr_R[0][2]);
				// En donde la posicion en de la fila hace referencia al numero de jugador y la posicion en 					   de las columnas hace referencia al dato X en "0", Y en "1" y angulo(&) en "2" y esto 				   ocurre para ambas variables 											

imshow("Imagem", imagen);// se muestra la imagen capturada y modificada por Run_Algorithm


if (waitKey(20) == 27){break;}// un break para terminar el bucle apretando esc.
 
}/// fin del while
    
  return 0;
}
