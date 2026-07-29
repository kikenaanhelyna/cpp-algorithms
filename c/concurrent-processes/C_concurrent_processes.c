/*
This program calculates the following equation:

    answer = (a * (b + 3)) / (c + 2) + ((3 + d * 2) ^ (1 + (d - 1) / e))

The program demonstrates parallel processing by splitting the computation
into independent parts. Each sub-expression is calculated in a separate
process using fork(), and the results are communicated through pipes.

This approach maximizes concurrency by allowing multiple parts of the
expression to be evaluated simultaneously instead of sequentially.
*/
#include <stdio.h>
#include <stdlib.h>    // For atoi, atof
#include <math.h>      // For pow
#include <unistd.h>    // For fork(), pipe(), read(), write()

int main(int argc, char* args[]) {
  double a, b, c, d, e, ans, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
  int p[2], q[2], r[2];
  int bufsize;

  a = atof(args[1]);
  b = atof(args[2]);
  c = atof(args[3]);
  d = atof(args[4]);
  e = atof(args[5]);
  pipe(p);  pipe(q);  pipe(r);
  bufsize = sizeof(double);

  if(!fork()) {
    t1 = b + 3;  sleep(1);
    t2 = a * t1; sleep(1);
    write(p[1], &t2, bufsize);
    return 0;
  }
  if(!fork()) {
    if(!fork()) {
      t3 = d - 1;  sleep(1);
      t4 = t3 / e; sleep(1);
      t5 = 1 + t4; sleep(1);
      write(q[1], &t5, bufsize);
      return 0;
    }
    t6 = d * 2;     sleep(1);
    t7 = 3 + t6;    sleep(1);
    read(q[0], &t5, bufsize);
    t8 = pow(t7, t5); sleep(1);
    write(r[1], &t8, bufsize);
    return 0;
  }
  t9 = c + 2;    sleep(1);
  read(p[0], &t2, bufsize);
  t10 = t2 / t9;  sleep(1);
  read(r[0], &t8, bufsize);
  ans = t10 + t8; sleep(1);

  printf("(%.1f * (%.1f + 1)) / (%.1f + 2) + ((3 + %.1f * 2) ^ (1 + (%.1f - 1) / %.1f)) = %.3f\n",
         a,b,c,d,d,e,ans);
  return 0;
}
