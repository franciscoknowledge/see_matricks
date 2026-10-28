#include "include/matricks.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* internal usage */

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

void _mtk_check_sum_dimensions(const Matricks* m1, const Matricks* m2, const char* func_name) {

    if (m1->rows == m2->rows && m1->cols == m2->cols)
        return;

    fprintf(stderr, _MTK_STR_SUM_NOT_EQUAL, func_name, m1->rows, m1->cols, m2->rows, m2->cols);
    exit(EXIT_FAILURE);

}

void _mtk_check_mult_dimensions(const Matricks* m1, const Matricks* m2, const char* func_name) {

    if (m1->cols == m2->rows)
        return;

    fprintf(stderr, _MTK_STR_MULT_DIM, func_name, m1->rows, m1->cols, m2->rows, m2->cols);
    exit(EXIT_FAILURE);

}

/* creation */

/* starts from 1 */
Matricks* mtk_new_matricks(int rows, int cols) {

    size_t allocate_for_array = rows * cols * sizeof(double);

    Matricks* new = malloc(sizeof(Matricks));
    new->rows = rows;
    new->cols = cols;
    new->data = malloc(allocate_for_array);

    memset((void*) new->data, 0, allocate_for_array);
    return new;

}

/* user usage */

/* goes from 1 to limit */
void mtk_set(Matricks* m, int row, int col, double value) {

    _mtk_check_bounds(m, row, col, __func__);

    row--;
    col--;
    m->data[(row * m->cols) + col] = value;

}

/* goes from 1 to limit */
double mtk_get(const Matricks* m, int row, int col) {

    _mtk_check_bounds(m, row, col, __func__);

    row--;
    col--;
    
    return m->data[(row * m->cols) + col];

}

/* caller must free */
Matricks* mtk_sum_matrickses(Matricks* m1, Matricks* m2) {

    /* dimensions have to be the same, using m1 as reference */

    _mtk_check_sum_dimensions(m1, m2, __func__);
    
    Matricks* sum = mtk_new_matricks(m1->rows, m1->cols);
    size_t slots = m1-> rows * m1->cols;

    for (size_t i = 0; i < slots; i++) {

        sum->data[i] = m1->data[i] + m2->data[i];

    }

    return sum;

}

/* caller must free */
Matricks* mtk_sub_matrickses(Matricks* m1, Matricks* m2) {

    _mtk_check_sum_dimensions(m1, m2, __func__);
    
    Matricks* sub = mtk_new_matricks(m1->rows, m1->cols);
    size_t slots = m1-> rows * m1->cols;

    for (size_t i = 0; i < slots; i++) {

        sub->data[i] = m1->data[i] - m2->data[i];

    }

    return sub;

}

/* caller must free */
Matricks* mtk_mult_scalar(Matricks* m, double s) {

    Matricks* mult = mtk_new_matricks(m->rows, m->cols);
    size_t slots = m-> rows * m->cols;

    for (size_t i = 0; i < slots; i++) {

        mult->data[i] = m->data[i] * s;

    }

    return mult;

}

/* caller must free */
Matricks* mtk_mult_matrickses(Matricks* m1, Matricks* m2) {

    _mtk_check_mult_dimensions(m1, m2, __func__);

    Matricks* mult = mtk_new_matricks(m1->rows, m2->cols);

    /* most of these variables could prob be done away with although theyre here for clearer meaning */

    size_t result_rows, result_cols, shared_dim;
    size_t row, col, k;

    double sum;

    result_rows = mult->rows;
    result_cols = mult->cols;
    shared_dim = m1->cols; /* same as m2's rows */

    for (row = 0; row < result_rows; row++) {

        for (col = 0; col < result_cols; col++) {

            sum = 0.0;

            for (k = 0; k < shared_dim; k++)
                sum += m1->data[row * shared_dim + k] * m2->data[k * result_cols + col];

            mult->data[row * result_cols + col] = sum;

        }

    }

    return mult;

}

/* utility */

void mtk_free(Matricks* m) {

    if (m == NULL)
        return;

    free(m->data);
    free(m);

}

void mtk_print(const Matricks* m) {

    size_t slots = m-> rows * m->cols;
    int col;

    for (size_t i = 0; i < slots; i++) {

        col = i % m->cols;

        if (col == 0)
            printf("[");

        printf("%f", m->data[i]);
        printf(col == (m->cols - 1) ? "]\n" : " ");

    }

}