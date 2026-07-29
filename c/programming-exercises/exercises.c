/*This rogram reads a sequence of positive integers from the user, 
until the sentinel value -1 is entered or the user has entered 10 
integers in total, and then outputs the maximum, minimum, average 
and standard deviation of the numbers. */


#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main() {
  int i=0, n=0, N, min, max, sum=0, a[100];
  double avg, stdDev, sumsqs;
  char name[50];

  printf("Please enter your first name: ");
  scanf("%s", name);

  while(n!=-1 && i<10) {
    printf("%s, enter a positive integer (or -1 to quit): ",name);
    scanf("%d",&n);
    if(n != -1) {
      if(!i) min = max = n;
      if(n<min) min = n;
      if(n>max) max = n;
      sum += n;
      a[i++] = n;
    }
  }
  avg = 1.0*sum/i;
  printf("The maximum is: %11.2f\n", 1.0*max);
  printf("The minimum is: %8d\n", min);
  printf("The average is: %12.3f\n", avg);

  N = i;
  sumsqs = 0;
  for(i=0; i<N; i++) sumsqs += (a[i] - avg) * (a[i] - avg);
  stdDev = sqrt(sumsqs)/N;

  printf("The standard deviation is: %.3f\n", stdDev);

  return 0;
}
