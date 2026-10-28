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

    Matricks* m = mtk_new_matricks(3, 3);
    populate_matricks(m);

    printf("hi\n");
    mtk_print(m);
    printf("endd\n");
    
}