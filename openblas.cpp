#include "cblas.h"
void matmul_openblas(float * c,  float * a,  float * b, int m, int k, int n)
{
  cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0, a, m, b,k, 0.0, c, m);
}
