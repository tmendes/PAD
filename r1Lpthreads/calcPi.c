#include <math.h>
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

void calculaTempo(struct timeval starttimetime, struct timeval entime){
  printf("%ld;\n", (entime.tv_sec * 1000000 + entime.tv_usec)-(starttimetime.tv_sec * 1000000 + starttimetime.tv_usec));
}

int main ()
{
  char buffer[30];
  int i;
  time_t currenttime;
  double x, pi, sum = 0.0;
  printf("Serial;");
  step = 1.0/(double) num_steps;
  starttime = marcaTempo(starttime, currenttime, buffer);
  for (i=0; i<num_steps; i++)
  {
     x = (i+0.5)*step;
     sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
       entime = marcaTempo(entime, currenttime, buffer);
       calculaTempo(starttime, entime);
  
  // printf(">>>PI: %.30f\n", pi);
  return 0;
}