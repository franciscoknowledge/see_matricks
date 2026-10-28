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

/* creation */

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

/* utility */

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