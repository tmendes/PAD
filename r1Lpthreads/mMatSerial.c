#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "readFiles.h"
#include "mMatSerial.h"

char *fileName_mat1, *fileName_mat2;
long int *mat1, *mat2, *matFinal;
struct timeval ini_ler_mtz1, end_ler_mtz1, ini_ler_mtz2, end_ler_mtz2, ini_mult, end_mult, tv;
unsigned int l_mat1, c_mat1, l_mat2, c_mat2;

struct timeval marcaTempo(struct timeval tv, time_t currenttime, char buffer[30]){
  gettimeofday(&tv, NULL); 
  currenttime=tv.tv_sec;
  strftime(buffer,30,"%d-%m-%Y %T.",localtime(&currenttime)); 
  printf("%s%ld;", buffer, tv.tv_usec);
  return tv; 
}

void calculaTempo(struct timeval starttime, struct timeval entime){
  printf("%ld;", (entime.tv_sec * 1000000 + entime.tv_usec)-(starttime.tv_sec * 1000000 + starttime.tv_usec));
}

long int *mMat(unsigned int linMat1, unsigned int colMat1, long int *mat1, unsigned int linMat2, unsigned int colMat2, long int *mat2){
	long int *matFinal = (long int *) malloc(sizeof(long int) * linMat1 * colMat2);	
	if (matFinal == NULL){
     		perror("I cannot allocate memory\n");
     		exit(EXIT_FAILURE);
     		return NULL;
 	}
	
	for (int i=0; i<linMat1; i++){
    	for(int j=0; j<colMat2; j++){
			for (int x=0; x<colMat1; x++){
				matFinal[i*colMat2 + j] += mat1[i*colMat1 + x] * mat2[x*colMat2 + j];
			}
 		}
	}
	return matFinal; 
}

int main (int argc, char **argv){

	char buffer[30];
	time_t curtime;

	l_mat1 			= atoi(	argv[1]	);
	c_mat1 			= atoi(	argv[2]	);	
	fileName_mat1 	= 		argv[3]	 ;
	l_mat2 			= atoi(	argv[4]	);
	c_mat2 			= atoi(	argv[5]	);
	fileName_mat2	= 		argv[6]  ;

    printf("Tipo;l_mat1;c_mat1;ini_leit_mat1;fim_leit_mat1;tmp_leit_mat1;l_mat2;c_mat2;ini_leit_mat2;fim_leit_mat2;tm_leit_mat2;ini_mult_mat;fim_mult_mat;tmp_mult;\n");
    printf("serial;%d;%d;",l_mat1,c_mat1);

	ini_ler_mtz1 	= marcaTempo(ini_ler_mtz1, curtime, buffer); 
	mat1 			= readFile(fileName_mat1, l_mat1, c_mat1);
	end_ler_mtz1 	= marcaTempo(end_ler_mtz1, curtime, buffer); 
	
	calculaTempo(ini_ler_mtz1, end_ler_mtz1);

    printf("%d;%d;",l_mat2,c_mat2);
	ini_ler_mtz2 	= marcaTempo(ini_ler_mtz2, curtime, buffer); 
	mat2 			= readFile(fileName_mat2, l_mat2, c_mat2);
	end_ler_mtz2 	= marcaTempo(end_ler_mtz2, curtime, buffer); 

	calculaTempo(ini_ler_mtz2, end_ler_mtz2);

	ini_mult 		= marcaTempo(ini_mult, curtime, buffer); 
	matFinal 		= mMat(l_mat1, c_mat1, mat1, l_mat2, c_mat2, mat2);
	end_mult 		= marcaTempo(end_mult, curtime, buffer); 
	
	calculaTempo(ini_mult, end_mult);
    printf("\n");

	free(mat1);
	free(mat2);
	free(matFinal);
	return 0;
}