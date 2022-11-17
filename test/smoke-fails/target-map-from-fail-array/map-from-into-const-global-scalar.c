//#include "omp.h"
#include "stdio.h"

/** Problem is map clause tries to read value
 * from N from the device and write it into
 * constant memory (constant generated by LLVM)
 */
const int N = 128;
const int A[128] = {0};
int M = 1;

const int B[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};


int main(int argc, char **argv) {
  int tmp = 0;
  int tmp2 = 0;

#if 0
  for (int i =0; i < N; ++i) {
    tmp2 += 1;
  }


#pragma omp target teams distribute parallel for reduction(+:tmp) map(N) map(M)
  for (int i = 0; i < N; i++) {
    tmp += 1;
    M = 42;
  }

  fprintf(stderr, "tmp: %u == %u\n", tmp, tmp2);
  fprintf(stderr, "M: %u == 42\n", M);
  tmp2 = tmp = 0;
  
#endif
  for (int i =0; i < N; ++i) {
    tmp2 += A[i] + 1;
  }

//#pragma omp target teams distribute parallel for reduction(+:tmp) map(to: N) map(tofrom:M) map(to: A)
#pragma omp target teams distribute parallel for reduction(+:tmp) map(N) map(tofrom:M) map(A)
  for (int i = 0; i < N; i++) {
    tmp += B[i%15] + 1;
    M = 42;
  }

  fprintf(stderr, "tmp: %u == %u\n", tmp, tmp2);
  fprintf(stderr, "M: %u == 42\n", M);

#if 0

  tmp2 = tmp = 0;

  for (int i = 0; i < 15; ++i) {
    tmp2 += B[i] + 1;
  }

#pragma omp target teams distribute parallel for reduction(+:tmp) map(M) map(to: B)
  for (int i = 0; i < 15; i++) {
    tmp += B[i] + 1;
    M = 42;
  }

  fprintf(stderr, "tmp: %u == %u\n", tmp, tmp2);
  fprintf(stderr, "M: %u == 42\n", M);


#pragma omp target teams distribute parallel for private(tmp) map(N) map(A)
  for (int i = 0; i < N; i++) {
    tmp += A[i];
    M = 42;
  }

#pragma omp target teams distribute parallel for private(tmp) map(tofrom:N) map(tofrom:A)
  for (int i = 0; i < N; i++) {
    tmp += i;
  }

#pragma omp target teams distribute parallel for private(tmp) map(to:N) map(to:M)
  for (int i = 0; i < N; i++) {
    tmp += i;
  }

#pragma omp target teams distribute parallel for private(tmp) map(N, M)
  for (int i = 0; i < N; i++) {
    tmp += i;
  }

#pragma omp target teams distribute parallel for private(tmp) map(N, M)
  for (int i = 0; i < N; i++) {
    tmp += i;
  }
#endif 

  //fprintf(stderr, "Passed\n");

  return tmp-tmp2;
}