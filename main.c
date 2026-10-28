#include <stdio.h>
#include "include/matricks.h"

void populate_matricks(Matricks* m) {

    int r, c;
    double n = 1;

    for (r = 1; r <= m->rows; r++) {

        for (c = 1; c <= m->cols; c++) {

            mtk_set(m, r, c, n);
            n++;

        }

    }

}

int main(void) {

    Matricks* matrickses[] = {

        mtk_new_matricks(3, 3),
        mtk_new_matricks(3, 3),
        mtk_new_matricks(2, 2),
        mtk_new_matricks(3, 5),
        mtk_new_matricks(5, 1),
        mtk_new_matricks(1, 5),
        mtk_new_matricks(2, 3),

    };

    for (size_t i = 0; i < sizeof(matrickses) / sizeof(Matricks*); i++) {

        populate_matricks(matrickses[i]);

    }

    Matricks* sum = mtk_sum_matrickses(matrickses[0], matrickses[1]);
    mtk_print(sum);
    
}