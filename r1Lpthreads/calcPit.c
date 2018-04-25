#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

static long num_steps = 1000000;
double step, pi;
struct timeval starttime, entime;
int NTHR;

struct timeval marcaTempo(struct timeval tv, time_t currenttime, char buffer[30]){
  gettimeofday(&tv, NULL); 
  currenttime=tv.tv_sec;
  strftime(buffer,30,"%d-%m-%Y  %T.",localtime(&currenttime)); 
  printf("%s%ld;", buffer, tv.tv_usec);
  return tv; 
}

void calculaTempo(struct timeval starttime, struct timeval entime){
  printf("%ld;\n", (entime.tv_sec * 1000000 + entime.tv_usec)-(starttime.tv_sec * 1000000 + starttime.tv_usec));
}

void *calcPi(void *t){
  long idthr = (long)t;  
  int i, restante, stps_ini, stps_fim;
  double x, sum = 0.0;

  // caso o a divisao seja exata 
  if ((num_steps%NTHR)==0){
      stps_ini  =  idthr    * (num_steps/NTHR); 
      stps_fim  = (idthr+1) * (num_steps/NTHR);
  } else {
      restante = (int) ceil(num_steps/NTHR);
      stps_ini  =  idthr    * restante; 
      // caso seja a ultima thread assume o restante do processamento
      if (num_steps - (idthr+1)*restante > restante)  stps_fim  = (idthr+1)*restante;
      if ((idthr+1) == NTHR)                          stps_fim  =  num_steps;
    }

  step = 1.0/(double) num_steps;
  for (i=stps_ini; i<stps_fim; i++){
     x    = (i+0.5)*step;
     sum  = sum + 4.0/(1.0+x*x);
  }
  pi += step * sum;
  pthread_exit((void*) t);
}

int main (int argc, char **argv)
{
  char buffer[30];
  time_t currenttime;
  NTHR = atoi(argv[1]);

  if (NTHR<=num_steps){
    pthread_t       thread[NTHR]  ;
    pthread_attr_t  attr          ;
    int             rc            ;
    long            t             ;
    void            *status       ;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("%i;",NTHR);
    starttime = marcaTempo(starttime, currenttime, buffer);
    for(t=0; t<NTHR; t++) {
       rc = pthread_create(&thread[t], &attr, calcPi, (void *)t);  
       if (rc) exit(-1);
       }

    pthread_attr_destroy(&attr);
    for(t=0; t<NTHR; t++) {
       rc = pthread_join(thread[t], &status);
       if (rc) {
          printf("ERROR; Erro ao efetuar o join das threads %d\n", rc);
          exit(-1);
          }
       }
       entime = marcaTempo(entime, currenttime, buffer);
       calculaTempo(starttime, entime);
    pthread_exit(NULL);
  } else {
    pthread_exit(NULL);
  }
  return 0;
}