#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readFiles.h"

//char *strtok(char *s, const char *delim);

long int *readFile(char nameFile[30], int dim1, int dim2){

	    FILE * fp;
    	char * dim2e = NULL;
    	size_t len = 0;
    	ssize_t read;
    	char * pch;

    	long int *matz = (long int *) malloc(sizeof(long int) * dim1 * dim2);

	if (matz == NULL){
     		perror("Erro ao ler arquivo\n");
     		exit(EXIT_FAILURE);
	       	return NULL;
	}

    fp = fopen(nameFile, "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    int i=0, j=0;
    while ((read = getline(&dim2e, &len, fp)) != -1) {
        pch = strtok(dim2e,";");
        while (pch != NULL && pch != ""){
	   if (pch != NULL && j < dim1){ 
           	matz[i*dim1 + j] = atoi(pch);
		j++;		
	   }
	   pch = strtok(NULL, ";");
        }
	j=0; 	
        i++;
    }

    fclose(fp);
    if (dim2e) free(dim2e);
    return matz;
}