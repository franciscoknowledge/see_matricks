#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* error strings */
#define _MTK_STR_ROW_OOB "[%s] row provided is out of bounds: given [%d], max [%d]"
#define _MTK_STR_COL_OOB "[%s] col provided is out of bounds: given [%d], max [%d]"

#define _MTK_STR_ROW_NEG "[%s] row provided is out of bounds: given [%d], min [1]"
#define _MTK_STR_COL_NEG "[%s] col provided is out of bounds: given [%d], min [1]"

/* TODO: maybe switch over rows, cols in the struct for size_t since negative input handling would be valuable here */

/* using double cuz ig maths leads to crazy decimal places */
typedef struct {

    double* data;
    int rows, cols;

} Matricks;

Matricks* mtk_new_matricks(int rows, int cols) {

    size_t allocate_for_array = rows * cols * sizeof(double);

    Matricks* new = malloc(sizeof(Matricks));
    new->rows = rows;
    new->cols = cols;
    new->data = malloc(allocate_for_array);

    memset((void*) new->data, 0, allocate_for_array);
    return new;

}

void _mtk_check_bounds(const Matricks* m, int row, int col, const char* func_name) {

    bool error = false;

    if (row > m->rows) {

        fprintf(stderr, _MTK_STR_ROW_OOB, func_name, row, m->rows);
        error = true;

    } else if (col > m->cols) {

        fprintf(stderr, _MTK_STR_COL_OOB, func_name, col, m->cols);
        error = true;
    
    }

    if (row <= 0) {

        fprintf(stderr, _MTK_STR_ROW_NEG, func_name, row);
        error = true;

    } else if (col <= 0) {

        fprintf(stderr, _MTK_STR_COL_NEG, func_name, col);
        error = true;

    }

    if (error)
        exit(EXIT_FAILURE);

}

void mtk_set(Matricks* m, int row, int col, double value) {

    _mtk_check_bounds(m, row, col, __func__);

    row--;
    col--;
    m->data[(row * m->cols) + col] = value;

}

double mtk_get(const Matricks* m, int row, int col) {

    _mtk_check_bounds(m, row, col, __func__);

    row--;
    col--;
    
    return m->data[(row * m->cols) + col];

}

/* ------------------ */

void mtk_print(const Matricks* m) {

    int r, c;
    for (r = 1; r <= m->rows; r++) {

        printf("[ ");
        for (c = 1; c <= m->cols; c++) {

            printf("%f ", mtk_get(m, r, c));
            if (c == m->cols)
                printf("]");

        }

        printf("\n");

    }

}

int main(void) {

    Matricks* m = mtk_new_matricks(2, 2);

    mtk_set(m, 1, 1, 11.25);
    mtk_set(m, 1, 2, 0.67);
    mtk_set(m, 2, 1, 99.38492);
    mtk_set(m, 2, 2, 0.00019);

    printf("hi\n");
    mtk_print(m);
    printf("endd\n");
    mtk_get(m, 1, 0);
    
}