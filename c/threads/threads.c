/*This program calculates this equasion:  answer = (a * (b + 3)) / (c + 2) + ((3 + d * 2) ^ (1 + (d - 1) / e))
by using threads. 
All threads in a process are in the same address space, so sharing of data is much easier 
than with separate processes. Also, context switches between threads are much cheaper 
in terms of time than context switches between processes.*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

double a, b, c, d, e, ans, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
void thread1();
void thread2();
void thread3();
pthread_t tid1, tid2, tid3;

int main(int argc, char * args[]) {
  a = atof(args[1]);
  b = atof(args[2]);
  c = atof(args[3]);
  d = atof(args[4]);
  e = atof(args[5]);

  pthread_create(&tid1, NULL, (void *)thread1, NULL);
  pthread_create(&tid2, NULL, (void *)thread2, NULL);

  t9 = c + 2;    sleep(1);
  pthread_join(tid1, NULL);
  t10 = t2 / t9;  sleep(1);
  pthread_join(tid2, NULL);
  ans = t10 + t8; sleep(1);

  printf("(%.1f * (%.1f + 1)) / (%.1f + 2) + ((3 + %.1f * 2) ^ (1 + (%.1f - 1) / %.1f)) = %.3f\n",
         a,b,c,d,d,e,ans);
  return 0;
}

void thread1() {    /* thread  code for (((a+b)/4)^c)+t4 */
  t1 = b + 3;  sleep(1);
  t2 = a * t1; sleep(1);
}

void thread2() {    /* thread code for (d/2) */
  pthread_create(&tid3, NULL, (void *)thread3, NULL);
    t6 = d * 2;     sleep(1);
    t7 = 3 + t6;    sleep(1);
    pthread_join(tid3, NULL);
    t8 = pow(t7, t5); sleep(1);
}

void thread3() {    /* thread code for (3*a) */
  t3 = d - 1;  sleep(1);
  t4 = t3 / e; sleep(1);
  t5 = 1 + t4; sleep(1);
}
