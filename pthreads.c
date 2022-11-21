#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CORE 4 // Value dependent on system core
#define MAX 4  // Matrix Size

// Maximum threads is equal to total core of system
pthread_t thread[CORE * 2];
int mat_A[MAX][MAX], mat_B[MAX][MAX], sum[MAX][MAX], sub[MAX][MAX], mul[MAX][MAX], s = 0;

// Addition of a Matrix
void *addition(void *arg)
{
    int i, j;
    int core = (int)arg;

    // Each thread computes 1/4th of matrix addition
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)
        for (j = 0; j < MAX; j++)
            sum[i][j] = mat_A[i][j] + mat_B[i][j]; // Compute Sum Row wise
}

// Subtraction of a Matrix
void *subtraction(void *arg)
{
    int i, j;
    int core = (int)arg;

    // Each thread computes 1/4th of matrix subtraction
    for (i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)
        for (j = 0; j < MAX; j++)
            sub[i][j] = mat_A[i][j] - mat_B[i][j]; // Compute Subtract row wise
}

// Multiplication of a Matrix
void *multi(void *arg)
{
    int i = s++; // i denotes row number of resultant multiplication matrix

    for (int j = 0; j < MAX; j++)
        for (int k = 0; k < MAX; k++)
            mul[i][j] += mat_A[i][k] * mat_B[k][j];
}

// Driver Code
int main()
{
    int i, j, step = 0;

    // Generating random values in mat_A and mat_B
    srand(time(0));
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            mat_A[i][j] = rand() % 10;
            mat_B[i][j] = rand() % 10;
        }
    }

    // Displaying mat_A
    printf("\nMatrix A:\n");
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", mat_A[i][j]);
        printf("\n");
    }

    // Displaying mat_B
    printf("\nMatrix B:\n");
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", mat_B[i][j]);
        printf("\n");
    }

    // Creating threads equal to core size and compute matrix row
    for (i = 0; i < CORE; i++)
    {
        pthread_create(&thread[i], NULL, &addition, (void *)step);
        pthread_create(&thread[i + CORE], NULL, &subtraction, (void *)step);
        pthread_create(&thread[i], NULL, multi, (void *)(step));
        step++;
    }

    // Waiting for join threads after compute
    for (i = 0; i < CORE * 2; i++)
        pthread_join(thread[i], NULL);

    // Display Addition of mat_A and mat_B
    printf("\nAddition of Matrix A and B:\n");
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", sum[i][j]);
        printf("\n");
    }

    // Display Subtraction of mat_A and mat_B
    printf("\nSubtraction of Matrix A and B:\n");

    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", sub[i][j]);
        printf("\n");
    }

    // Display Multiplication of mat_A and mat_B
    printf("\nMultiplication of Matrix A and B:\n");

    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            printf("%d ", mul[i][j]);
        printf("\n");
    }

    return 0;
}
