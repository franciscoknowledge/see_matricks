#pragma once

/* error strings */
#define _MTK_STR_ROW_OOB "[%s] row provided is out of bounds: given [%d], max [%d]"
#define _MTK_STR_COL_OOB "[%s] col provided is out of bounds: given [%d], max [%d]"

#define _MTK_STR_ROW_NEG "[%s] row provided is out of bounds: given [%d], min [1]"
#define _MTK_STR_COL_NEG "[%s] col provided is out of bounds: given [%d], min [1]"

typedef struct {

    double* data;
    int rows, cols;

} Matricks;

/* internal usage */

void _mtk_check_bounds(const Matricks* m, int row, int col, const char* func_name);

/* creation */

Matricks* mtk_new_matricks(int rows, int cols);

/* user usage */

void mtk_set(Matricks* m, int row, int col, double value);
double mtk_get(const Matricks* m, int row, int col);

/* utility */

void mtk_print(const Matricks* m);