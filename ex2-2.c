#include <stdio.h>
#include <time.h>
#include <stdlib.h>
long int re_fibo(int n){
  if (n == 0){
    return 0;
  } else if (n == 1){
    return 1;
  }
  return re_fibo(n-1)+re_fibo(n-2);
}

long int sq_fibo(int n){
  long int f1 = 0, f2 = 1, fibo = 0;
  int i;
  if (n == 0){
    return f1;
  } else if (n == 1){
    return f2 + f1;
  }
  for (i = 2; i <= n; i++){
    fibo = f2 + f1;
    f1 = f2;
    f2 = fibo;
  }
  return fibo;
}


int main(int argc, char **argv){
  time_t start, end;
  int n;

  if (argc != 2){
    printf("The number of argument should be two.\n");
    exit(1);
  }
  
  n = atoi(argv[1]);
  start = time(0);
  printf("recursive Fibonacci(n = %d) = %ld\n", n, re_fibo(n));
  end = time(0);
  printf("\n CPU time = %f [sec]\n", (double)(end - start));
  start = time(0);
  printf("sequential Fibonacci(n = %d) = %ld\n", n, sq_fibo(n));
  end = time(0);
  printf("\n CPU time = %f [sec]\n", (double)(end - start));
  return 0;
}