#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

static void symmetric();
static void diagonal();
static void identity();
static void multiplication();
static void transpose();
static void swaprow();

static void display(const matrix *m);
static void randomfill(matrix *m);

int main(int argc, char* argv[])
{
    srand(time(NULL));

    symmetric();
    diagonal();
    identity();
    multiplication();
    transpose();
    swaprow();

    return 0;
}

static void symmetric()
{
    matrix a;

    //create heap allocation for 3x3 matrix
    matrix_create(3, 3, &a);

    //first row
    MATRIX(a, 0, 0) = 2;
    MATRIX(a, 0, 1) = 3;
    MATRIX(a, 0, 2) = 6;

    //second row
    MATRIX(a, 1, 0) = 3;
    MATRIX(a, 1, 1) = 4;
    MATRIX(a, 1, 2) = 5;

    //second row
    MATRIX(a, 2, 0) = 6;
    MATRIX(a, 2, 1) = 5;
    MATRIX(a, 2, 2) = 9;

    //show matrix
    printf("\nMatrix is %s\n", matrix_is_symmetric(&a) ? "symmetric" : "not symmetric");
    display(&a);

    //free up heap allocation
    matrix_destroy(&a);
}

static void diagonal()
{
    matrix a, b;

    //create heap allocation for 3x3 matrix and set diagonal value to 9
    matrix_diagonal_create_buffer(3, 9, &a);
    //show matrix
    printf("\nDiagonal matrix\n");
    display(&a);

    //create heap allocation for 3x3 matrix
    matrix_create(3, 3, &b);
    randomfill(&b);
    //show matrix
    printf("Random matrix\n");
    display(&b);

    //zeroes out all member and set diagonal values to 5
    matrix_diagonal(&b, 5);
    //show matrix
    printf("Mofify random to diagonal matrix\n");
    display(&b);

    //free up heap allocation
    matrix_destroy(&a);
    matrix_destroy(&b);
}

static void identity()
{
    matrix a, b;

    //create heap allocation for 3x3 matrix and set diagonal value to 1
    matrix_identity_create_buffer(3, &a);
    //show matrix
    printf("\nIdentity matrix\n");
    display(&a);

    //create heap allocation for 3x3 matrix
    matrix_create(3, 3, &b);
    randomfill(&b);
    //show matrix
    printf("Random matrix\n");
    display(&b);
    //zeroes out all member and set diagonal values to 1
    matrix_identity(&b);
    //show matrix
    printf("Mofify random to identity matrix\n");
    display(&b);

    //free up heap allocation
    matrix_destroy(&a);
    matrix_destroy(&b);
}

static void multiplication()
{
    matrix a, b, c;

    matrix_create(3, 3, &a);
    randomfill(&a);
    //show matrix
    printf("\nRandom matrix A\n");
    display(&a);

    //multiply matrix with scalar number 2
    matrix_scalar_mul(&a, 2);
    //show matrix
    printf("Multply matrix A with scalar number 2\n");
    display(&a);

    matrix_create(3, 3, &b);
    randomfill(&b);
    //show matrix
    printf("Random matrix B\n");
    display(&b);

    matrix_mul(&a, &b, &c, true);
    //show matrix
    printf("Multply matrix A with B and save result into C\n");
    display(&c);

    //free up heap allocation
    matrix_destroy(&a);
    matrix_destroy(&b);
    matrix_destroy(&c);
}

static void transpose()
{
    matrix a, b;

    matrix_create(3, 2, &a);
    randomfill(&a);
    //show matrix
    printf("\nRandom matrix A\n");
    display(&a);

    //transpose matrix A and save the result to B
    matrix_transpose(&a, &b, true);
    //show matrix
    printf("Transpose matrix A and save the result into b\n");
    display(&b);

    //free up heap allocation
    matrix_destroy(&a);
    matrix_destroy(&b);
}

void swaprow()
{
    matrix a;

    matrix_create(3, 4, &a);
    randomfill(&a);
    //show matrix
    printf("\nRandom matrix A\n");
    display(&a);

    //swap row 0 and 2
    matrix_swap_row(&a, 0, 2);
    //show matrix
    printf("Swap row 0 and 2\n");
    display(&a);

    //free up heap allocation
    matrix_destroy(&a);
}

static void display(const matrix *m)
{
    int r, c;
    for(r=0; r<m->rows; r++)
    {
        for(c=0; c<m->cols; c++)
            printf("%s%.02f", c>0 ? "\t" : "", MATRIXP(m, r, c));
        printf("\n");
    }
}

void randomfill(matrix *m)
{
    int r, c;
    for(r=0; r<m->rows; r++)
    {
        for(c=0; c<m->cols; c++)
            MATRIXP(m, r, c) = round( 10 * ((float)rand()/RAND_MAX) );
    }
}
