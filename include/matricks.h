#pragma once

/* error strings */
#define _MTK_STR_ROW_OOB "[%s] row provided is out of bounds: given [%d], max [%d]"
#define _MTK_STR_COL_OOB "[%s] col provided is out of bounds: given [%d], max [%d]"

#define _MTK_STR_ROW_NEG "[%s] row provided is out of bounds: given [%d], min [1]"
#define _MTK_STR_COL_NEG "[%s] col provided is out of bounds: given [%d], min [1]"

#define _MTK_STR_SUM_NOT_EQUAL "[%s] cannot sum matrickses of diff sizes [%d]x[%d] + [%d]x[%d]"
#define _MTK_STR_MULT_DIM "[%s] cannot mult matrickses of cols != rows [%d]x{%d} * {%d}x[%d]"

typedef struct {

    double* data;
    int rows, cols;

} Matricks;

/* ---- internal usage ---- */

void _mtk_check_bounds(const Matricks* m, int row, int col, const char* func_name);
void _mtk_check_sum_dimensions(const Matricks* m1, const Matricks* m2, const char* func_name);
void _mtk_check_mult_dimensions(const Matricks* m1, const Matricks* m2, const char* func_name);

/* ---- creation ---- */

Matricks* mtk_new_matricks(int rows, int cols);

/* ---- user usage ---- */

/* element access */

void mtk_set(Matricks* m, int row, int col, double value);
double mtk_get(const Matricks* m, int row, int col);

/* algebra */

Matricks* mtk_sum_matrickses(Matricks* m1, Matricks* m2);
Matricks* mtk_sub_matrickses(Matricks* m1, Matricks* m2);

Matricks* mtk_mult_scalar(Matricks* m1, double s);
Matricks* mtk_mult_matrickses(Matricks* m1, Matricks* m2);

/* matricks cool stuff */

Matricks* mtk_get_transpose(Matricks *m);

/* ---- utility ---- */

void mtk_free(Matricks* m);
void mtk_print(const Matricks* m);