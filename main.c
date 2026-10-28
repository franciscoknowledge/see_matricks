#include <stdio.h>
#include "include/matricks.h"

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