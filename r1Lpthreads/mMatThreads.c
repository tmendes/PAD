#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mMatThreads.h"
#include "readFiles.h"

struct timeval ini_ler_matz1, end_ler_matz1, ini_ler_matz2, end_ler_matz2, ini_mult, end_mult, tv;
unsigned int ln_mat1, c_mat1, ln_mat2, c_mat2, i, j;
char *fileName_mat1, *fileName_mat2;
long int *mat1, *mat2, *matFinal;
int NTHR;

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

void *mMult(void *t) {

  	long tid = (long)t;   
  	int ln_inicial, ln_final, col_from, col_to, restante;
  	col_from 	= 0 ;
  	col_to 		= c_mat2; 

  	if ((ln_mat1%NTHR)==0){
  		ln_inicial 	=  tid 	  * (ln_mat1/NTHR); 
  		ln_final 	= (tid+1) * (ln_mat1/NTHR);
  	} else {
  		restante = (int) round(ln_mat1/NTHR);
        ln_inicial 	=  tid 	  * restante;
        if (ln_mat1 - (tid+1)*restante > restante)   ln_final = (tid+1) * restante;
  		if ((tid+1) == NTHR						 )   ln_final =  ln_mat1;	
  	}

    int sum = 0;
    for (i=ln_inicial; i<ln_final; i++){
		for(j=col_from; j<col_to; j++){
			for (int x=0; x<c_mat1; x++){
				matFinal[i*c_mat2 + j] += mat1[i*c_mat1 + x] * mat2[x*c_mat2 + j];
			}
		}
    }
	//printf("Thread %ld done.\n------------------------------------------\n",tid);
	pthread_exit((void*) t);
}

//long int *mMultMatrix(long int *matFinal){
void *mMultMatrix(long int *matFinal){

	if (NTHR<=ln_mat1){
		pthread_t 		thread[NTHR];
	    pthread_attr_t 	attr;
	    int 			rc;
	    long 			t;
	    void *status;

	    /* Initialize and set thread detached attribute */
	    pthread_attr_init(&attr);
	    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	    for(t=0; t<NTHR; t++) {
	       //printf("Main: creating thread %ld\n", t);
	       rc = pthread_create(&thread[t], &attr, mMult, (void *)t);  
	       if (rc) {
	          printf("ERROR; return code from pthread_create() is %d\n", rc);
	          exit(-1);
	          }
	       }

	    /* Free attribute and wait for the other threads */
	    pthread_attr_destroy(&attr);
	    for(t=0; t<NTHR; t++) {
	       rc = pthread_join(thread[t], &status);
	       if (rc) {
	          printf("ERROR; return code from pthread_join() is %d\n", rc);
	          exit(-1);
	          }
	       }
	} else {
		pthread_exit(NULL);
	}
}

int main (int argc, char **argv){

	char buffer[30];
	time_t curtime;

	NTHR 			= atoi(argv[1]);
	ln_mat1 		= atoi(argv[2]);
	c_mat1 			= atoi(argv[3]);	
	fileName_mat1 	=      argv[4];
	ln_mat2 		= atoi(argv[5]);
	c_mat2 			= atoi(argv[6]);
	fileName_mat2 	=      argv[7];
	matFinal = (long int *) malloc(sizeof(long int) * ln_mat1 * c_mat2);

	if (matFinal == NULL){
		perror("I cannot allocate memory\n");
		exit(EXIT_FAILURE);
		return 0;
	}

    printf("Tipo;ln_mat1;c_mat1;ini_leit_mat1;fim_leit_mat1;tmp_leit_mat1;ln_mat2;c_mat2;ini_leit_mat2;fim_leit_mat2;tm_leit_mat2;ini_mult_mat;fim_mult_mat;tmp_mult;\n");
    printf("THREADS.%d;%d;%d;",NTHR,ln_mat1,c_mat1);
	ini_ler_matz1 = marcaTempo(ini_ler_matz1, curtime, buffer); 
	mat1 = readFile(fileName_mat1, ln_mat1, c_mat1);
	//printMatrix(ln_mat1, c_mat1, mat1);

	end_ler_matz1 = marcaTempo(end_ler_matz1, curtime, buffer); 
	calculaTempo(ini_ler_matz1, end_ler_matz1);
    
    printf("%d;%d;",ln_mat2,c_mat2);
	ini_ler_matz2 = marcaTempo(ini_ler_matz2, curtime, buffer); 
	mat2 = readFile(fileName_mat2, ln_mat2, c_mat2);
	end_ler_matz2 = marcaTempo(end_ler_matz2, curtime, buffer); 
	calculaTempo(ini_ler_matz2, end_ler_matz2);

	ini_mult = marcaTempo(ini_mult, curtime, buffer); 
	mMultMatrix(matFinal);
	
	end_mult = marcaTempo(end_mult, curtime, buffer); 
	calculaTempo(ini_mult, end_mult);
	printf("\n\n");
	
	free(mat1);
	free(mat2);
	free(matFinal);

	return 0;
}