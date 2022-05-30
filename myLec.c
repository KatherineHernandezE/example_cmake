#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h> 
#include <stdio.h>
#include "myLib.h"
#include "cvui.h"
using namespace std;
using namespace cv;
int N_Cam;

int WIDTH;

int HEIGHT; 

bool Flag_imshow,Flag_printed,Flag_Roi;
int x,y,w,h;

int Set_Red[6],
    Set_R_Color1[6],
    Set_R_Color2[6],
    Set_R_Color3[6];

int Range_Red[3][2],
    Range_R_Color1[3][2],
    Range_R_Color2[3][2],
    Range_R_Color3[3][2];

int Set_Blue[6],
    Set_B_Color1[6],
    Set_B_Color2[6],
    Set_B_Color3[6];

int Range_Blue[3][2],
    Range_B_Color1[3][2],
    Range_B_Color2[3][2],
    Range_B_Color3[3][2];

int Range_Ball[3][2],
    Set_Ball[6];
  
///////////////////lectura de archivos ///////////////////////////
int Read_file(){
	FILE* fd;
	int c;
	fd = fopen("filtro.txt","rt");
	if(fd==NULL){
		printf("error al abrir archivo\n");
		return 0;
	}
	char pinta[2],
	     clase[2],
	     color[2];
	int  rango, valor;
	while((c=fgetc(fd))!=EOF){
	    fscanf(fd,"%s %s %s %d %d;",pinta ,clase,color,&rango,&valor);
    	switch (pinta[0]){
  		
		case 'P':
			switch(color[0]){
  				case 'R':
  					if(rango==1){
					Range_Ball[0][0]= valor;
					}
					else{
					Range_Ball[0][1]= valor;
					}  
  				break;
				case 'G':
					if(rango==1){
					Range_Ball[1][0]= valor;
					}
					else{
					Range_Ball[1][1]= valor;
					}
  				break;	
				case 'B':
					if(rango==1){
					Range_Ball[2][0]= valor;
					}
					else{
					Range_Ball[2][1]= valor;
					}
  				break;
				}
		break;

		case 'R':
  			switch(color[0]){
  				case 'R':
  					if(rango==1){
					Range_Red[0][0]= valor;
					}
					else{
					Range_Red[0][1]= valor;
					}  
  				break;
				case 'G':
					if(rango==1){
					Range_Red[1][0]= valor;
					}
					else{
					Range_Red[1][1]= valor;
					}
  				break;	
				case 'B':
					if(rango==1){
					Range_Red[2][0]= valor;
					}
					else{
					Range_Red[2][1]= valor;
					}
  				break;
			}
		break;
		case 'B':
  			switch(color[0]){
  				case 'R':
  					if(rango==1){
					Range_Blue[0][0]= valor;
					}
					else{
					Range_Blue[0][1]= valor;
					}  
  				break;
				case 'G':
					if(rango==1){
					Range_Blue[1][0]= valor;
					}
					else{
					Range_Blue[1][1]= valor;
					}
  				break;	
				case 'B':
					if(rango==1){
					Range_Blue[2][0]= valor;
					}
					else{
					Range_Blue[2][1]= valor;
					}
  				break;
			}
		break;

		
		case 'r':
		switch (clase[0]){
  		/**/	case '1':
  		/**/		switch(color[0]){
  		/**/		case 'R':
  		/**/			if(rango==1){
		/**/			Range_R_Color1[0][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color1[0][1]= valor;
		/**/			}  
  		/**/		break;
		/**/		case 'G':
		/**/			if(rango==1){
		/**/			Range_R_Color1[1][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color1[1][1]= valor;
		/**/			}
  		/**/		break;	
		/**/		case 'B':
		/**/			if(rango==1){
		/**/			Range_R_Color1[2][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color1[2][1]= valor;
		/**/			}
  		/**/		break;
		/**/		}
  		/**/	break;
		/**/
	  	/**/	case '2':
	  	/**/	    switch(color[0]){
  		/**/		case 'R':
  		/**/			if(rango==1){
		/**/			Range_R_Color2[0][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color2[0][1]= valor;
		/**/			}  
  		/**/		break;
		/**/		case 'G':
		/**/			if(rango==1){
		/**/			Range_R_Color2[1][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color2[1][1]= valor;
		/**/			}
  		/**/		break;	
		/**/		case 'B':
		/**/			if(rango==1){
		/**/			Range_R_Color2[2][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_R_Color2[2][1]= valor;
		/**/			}
  		/**/		break;
		/**/	}
		/**/	break;
	  	/**/	
		/**/	case '3':
		/**/	switch(color[0]){
  		/**/	/**/	case 'R':
  		/**/	/**/		if(rango==1){
		/**/	/**/		Range_R_Color3[0][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/	/**/		Range_R_Color3[0][1]= valor;
		/**/	/**/		}  
  		/**/	/**/	break;
		/**/	/**/	case 'G':
		/**/	/**/		if(rango==1){
		/**/	/**/		Range_R_Color3[1][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/	/**/		Range_R_Color3[1][1]= valor;
		/**/	/**/		}
  		/**/	/**/	break;	
		/**/	/**/	case 'B':
		/**/	/**/		if(rango==1){
		/**/	/**/		Range_R_Color3[2][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/   	/**/		Range_R_Color3[2][1]= valor;
		/**/   	/**/			}
  		/**/   	/**/	break;
		/**/	}//fin color c
  		/**/	break;
		}//fin clase
		break;		

		case 'b':
		switch (clase[0]){
  		/**/	case '1':
  		/**/		switch(color[0]){
  		/**/		case 'R':
  		/**/			if(rango==1){
		/**/			Range_B_Color1[0][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color1[0][1]= valor;
		/**/			}  
  		/**/		break;
		/**/		case 'G':
		/**/			if(rango==1){
		/**/			Range_B_Color1[1][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color1[1][1]= valor;
		/**/			}
  		/**/		break;	
		/**/		case 'B':
		/**/			if(rango==1){
		/**/			Range_B_Color1[2][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color1[2][1]= valor;
		/**/			}
  		/**/		break;
		/**/		}
  		/**/	break;
		/**/
	  	/**/	case '2':
	  	/**/	    switch(color[0]){
  		/**/		case 'R':
  		/**/			if(rango==1){
		/**/			Range_B_Color2[0][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color2[0][1]= valor;
		/**/			}  
  		/**/		break;
		/**/		case 'G':
		/**/			if(rango==1){
		/**/			Range_B_Color2[1][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color2[1][1]= valor;
		/**/			}
  		/**/		break;	
		/**/		case 'B':
		/**/			if(rango==1){
		/**/			Range_B_Color2[2][0]= valor;
		/**/			}
		/**/			else{
		/**/			Range_B_Color2[2][1]= valor;
		/**/			}
  		/**/		break;
		/**/	}
		/**/	break;
	  	/**/	
		/**/	case '3':
		/**/	switch(color[0]){
  		/**/	/**/	case 'R':
  		/**/	/**/		if(rango==1){
		/**/	/**/		Range_B_Color3[0][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/	/**/		Range_B_Color3[0][1]= valor;
		/**/	/**/		}  
  		/**/	/**/	break;
		/**/	/**/	case 'G':
		/**/	/**/		if(rango==1){
		/**/	/**/		Range_B_Color3[1][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/	/**/		Range_B_Color3[1][1]= valor;
		/**/	/**/		}
  		/**/	/**/	break;	
		/**/	/**/	case 'B':
		/**/	/**/		if(rango==1){
		/**/	/**/		Range_B_Color3[2][0]= valor;
		/**/	/**/		}
		/**/	/**/		else{
		/**/   	/**/		Range_B_Color3[2][1]= valor;
		/**/   	/**/			}
  		/**/   	/**/	break;
		/**/	}//fin color c
  		/**/	break;
		}//fin clase
		break;		


	}//switch
    } //while
	fclose(fd);
//---------------------------------------------------------------------------//
	FILE* set;
	int s;
	set = fopen("previous_setting.txt","rt");
	if(set==NULL){
		printf("error al abrir archivo \n");
		return 0;
	}
	char Team[5];
	int  N_jugador,dat1,dat2,dat3,dat4,dat5,dat6;
	while((s=fgetc(set))!=EOF){
fscanf(set,"%s >> %d >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;",	Team,&N_jugador,&dat1,&dat2,&dat3 ,&dat4,&dat5,&dat6);
		switch (Team[0]){
			case 'C':
				N_Cam = N_jugador;
				WIDTH = dat1;
				HEIGHT= dat2;
				x=dat3;
				y=dat4;
				w=dat5;
				h=dat6;

		//--------------------------------//
			case'R':	
				switch(N_jugador){
					case 0:
					Set_Red[0]=dat1;
					Set_Red[1]=dat2;
					Set_Red[2]=dat3;
					Set_Red[3]=dat4;
					Set_Red[4]=dat5;
					Set_Red[5]=dat6;
					break;
					case 1:
					Set_R_Color1[0]=dat1;
					Set_R_Color1[1]=dat2;
					Set_R_Color1[2]=dat3;
					Set_R_Color1[3]=dat4;
					Set_R_Color1[4]=dat5;
					Set_R_Color1[5]=dat6;
					break;
					case 2:
					Set_R_Color2[0]=dat1;
					Set_R_Color2[1]=dat2;
					Set_R_Color2[2]=dat3;
					Set_R_Color2[3]=dat4;
					Set_R_Color2[4]=dat5;
					Set_R_Color2[5]=dat6;
					break;
					case 3:
					Set_R_Color3[0]= dat1;
					Set_R_Color3[1]= dat2;
					Set_R_Color3[2]= dat3;
					Set_R_Color3[3]= dat4;
					Set_R_Color3[4]= dat5;
					Set_R_Color3[5]= dat6;
					break;
				}			
			break;
		//-------------------------------//
			case'A':	
				switch(N_jugador){
					case 0:
					Set_Blue[0]=dat1;
					Set_Blue[1]=dat2;
					Set_Blue[2]=dat3;
					Set_Blue[3]=dat4;
					Set_Blue[4]=dat5;
					Set_Blue[5]=dat6;					
					break;
					case 1:
					Set_B_Color1[0]=dat1;
					Set_B_Color1[1]=dat2;
					Set_B_Color1[2]=dat3;
					Set_B_Color1[3]=dat4;
					Set_B_Color1[4]=dat5;
					Set_B_Color1[5]=dat6;
					break;
					case 2:
					Set_B_Color2[0]=dat1;
					Set_B_Color2[1]=dat2;
					Set_B_Color2[2]=dat3;
					Set_B_Color2[3]=dat4;
					Set_B_Color2[4]=dat5;
					Set_B_Color2[5]=dat6;
					break;
					case 3:
					Set_B_Color3[0]=dat1;
					Set_B_Color3[1]=dat2;
					Set_B_Color3[2]=dat3;
					Set_B_Color3[3]=dat4;
					Set_B_Color3[4]=dat5;
					Set_B_Color3[5]=dat6;
					break;
				}	
			break;	
			case 'B':
				 Set_Ball[0]= dat1;
				 Set_Ball[1]= dat2;
				 Set_Ball[2]= dat3;
				 Set_Ball[3]= dat4;
				 Set_Ball[4]= dat5;
				 Set_Ball[5]= dat6;
			break;
			case 'S':
				Flag_imshow = N_jugador;
				Flag_printed = dat1;
				Flag_Roi=  dat2;
			break;
		}//fin del switch
	}//fin del while=
fclose(set);
//----------------------------------------------------------------//

}

/*
Recordar que el valor de las variables de los filtros estan ordenados 
         0 - 1 - 2
   |////////////////| 
   | 0 ->RM  GM  BM |->maximo
   | 1 ->RN  GN  BN |->minimo 
   |////////////////|
*/


////////////////////////////////////sobre escritura///////////////////
/*

esta funcion se ocupa en el caso ocurra alguna modificacion en alguna de las variables 
dentro de la UI

*/
int Rewrite_file(){

remove("filtro.txt");

FILE* fp;
fp = fopen("filtro.txt","a");
if(fp==NULL){
	printf("error al escribir archivo\n");
	return 0;
}

//------------------------------------------------------------------------------//
//										//
//										//
//				ONLY BALL					//
//										//
//										//
//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "P P R %d %d;\n",county+1,Range_Ball[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "P P G %d %d;\n",county+1,Range_Ball[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "P P B %d %d;\n",county+1,Range_Ball[countx][county]);}
	}

}
fprintf(fp,"\n");




//------------------------------------------------------------------------------//
//										//
//										//
//				ONLY BLUE					//
//										//
//										//
//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "B B R %d %d;\n",county+1,Range_Blue[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "B B G %d %d;\n",county+1,Range_Blue[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "B B B %d %d;\n",county+1,Range_Blue[countx][county]);}
	}
}
fprintf(fp,"\n");

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 1 R %d %d;\n",county+1,Range_B_Color1[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 1 G %d %d;\n",county+1,Range_B_Color1[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 1 B %d %d;\n",county+1,Range_B_Color1[countx][county]);}
	}
}
fprintf(fp,"\n");

//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 2 R %d %d;\n",county+1,Range_B_Color2[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 2 G %d %d;\n",county+1,Range_B_Color2[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 2 B %d %d;\n",county+1,Range_B_Color2[countx][county]);}
	}
}
fprintf(fp,"\n");

//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 3 R %d %d;\n",county+1,Range_B_Color3[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 3 G %d %d;\n",county+1,Range_B_Color3[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "b 3 B %d %d;\n",county+1,Range_B_Color3[countx][county]);}
	}
}
fprintf(fp,"\n");



//------------------------------------------------------------------------------//
//										//
//										//
//				ONLY RED					//
//										//
//										//
//------------------------------------------------------------------------------//
for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "R R R %d %d;\n",county+1,Range_Red[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "R R G %d %d;\n",county+1,Range_Red[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "R R B %d %d;\n",county+1,Range_Red[countx][county]);}
	}
}
fprintf(fp,"\n");

//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 1 R %d %d;\n",county+1,Range_R_Color1[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 1 G %d %d;\n",county+1,Range_R_Color1[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 1 B %d %d;\n",county+1,Range_R_Color1[countx][county]);}
	}
}
fprintf(fp,"\n");

//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 2 R %d %d;\n",county+1,Range_R_Color2[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 2 G %d %d;\n",county+1,Range_R_Color2[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 2 B %d %d;\n",county+1,Range_R_Color2[countx][county]);}
	}
}


fprintf(fp,"\n");

//------------------------------------------------------------------------------//

for(int countx =0;countx<3;countx++){
	if(countx == 0){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 3 R %d %d;\n",county+1,Range_R_Color1[countx][county]);}
	}
	if(countx == 1){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 3 G %d %d;\n",county+1,Range_R_Color2[countx][county]);}
	}
	if(countx == 2){
	for(int county = 0; county <2;county++){
		fprintf(fp, "r 3 B %d %d;\n",county+1,Range_R_Color3[countx][county]);}
	}

}


fclose(fp);

remove("previous_setting.txt");

FILE* Set_prev;
Set_prev = fopen("previous_setting.txt","a");
if(Set_prev==NULL){
	printf("error al escribir archivo\n");
	return 0;
}

fprintf(Set_prev,"\nCam >> %d >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",N_Cam,WIDTH,HEIGHT,x,y,w,h);
fprintf(Set_prev, "Ball >> 0 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_Ball[0],Set_Ball[1],Set_Ball[2],Set_Ball[3],Set_Ball[4],Set_Ball[5]);

fprintf(Set_prev, "Rojo >> 0 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_Red[0],Set_Red[1],Set_Red[2],Set_Red[3],Set_Red[4],Set_Red[5]);
fprintf(Set_prev, "Rojo >> 1 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_R_Color1[0],Set_R_Color1[1],Set_R_Color1[2],Set_R_Color1[3],Set_R_Color1[4],Set_R_Color1[5]);
fprintf(Set_prev, "Rojo >> 2 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_R_Color2[0],Set_R_Color2[1],Set_R_Color2[2],Set_R_Color2[3],Set_R_Color2[4],Set_R_Color2[5]);

fprintf(Set_prev, "Rojo >> 3 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_R_Color3[0],Set_R_Color3[1],Set_R_Color3[2],Set_R_Color3[3],Set_R_Color3[4],Set_R_Color3[5]);

fprintf(Set_prev, "Azul >> 0 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_Blue[0],Set_Blue[1],Set_Blue[2],Set_Blue[3],Set_Blue[4],Set_Blue[5]);
fprintf(Set_prev, "Azul >> 1 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_B_Color1[0],Set_B_Color1[1],Set_B_Color1[2],Set_B_Color1[3],Set_B_Color1[4],Set_B_Color1[5]);
fprintf(Set_prev, "Azul >> 2 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_B_Color2[0],Set_B_Color2[1],Set_B_Color2[2],Set_B_Color2[3],Set_B_Color2[4],Set_B_Color2[5]);
fprintf(Set_prev, "Azul >> 3 >> dp %d >> Min %d >> P1 %d >> P2 %d >> Rm %d >> Rx %d;\n",Set_B_Color3[0],Set_B_Color3[1],Set_B_Color3[2],Set_B_Color3[3],Set_B_Color3[4],Set_B_Color3[5]);
fprintf(Set_prev, "Set >> %d >> dp %d >> Min %d >> P1 0 >> P2 0 >> Rm 0 >> Rx 0;\n",Flag_imshow,Flag_printed,Flag_Roi);
fclose(Set_prev);
}







