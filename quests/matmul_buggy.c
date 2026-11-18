/* Intentionally buggy matrix multiplication for the bonus quest.
 * Compile: cc -O0 -o matmul quests/matmul_buggy.c
 * Usage:   ./matmul
 */
#include <stdio.h>
#include <stdlib.h>

#define N 4

/* Fill A and B with simple values so a correct implementation is easy to check. */
static void fill(double *A, double *B, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i * n + j] = (double)(i + 1);
            B[i * n + j] = (double)(j + 1);
        }
    }
}

static void matmul(const double *A, const double *B, double *C, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            /* Bug: k goes to n inclusive, so this reads one past each row. */
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

static void print_matrix(const char *name, const double *M, int n)
{
    printf("%s =\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("  %8.2f", M[i * n + j]);
        }
        printf("\n");
    }
}

int main(void)
{
    double *A = malloc((size_t)N * N * sizeof(*A));
    double *B = malloc((size_t)N * N * sizeof(*B));
    double *C = calloc((size_t)N * N, sizeof(*C));
    if (!A || !B || !C) {
        fprintf(stderr, "allocation failed\n");
        return 1;
    }

    fill(A, B, N);
    matmul(A, B, C, N);
    print_matrix("C", C, N);

    /* For a correct matmul, C[i,j] would be (i+1) * (j+1) * N. */
    free(A);
    free(B);
    free(C);
    return 0;
}
