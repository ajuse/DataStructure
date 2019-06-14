#include <stdio.h>
int main() {
    //a是一个二维数组
    int a[2][3] = {0};
    /*  1.a type is int(*)[3]
    **  2.&a tpye is int(*)[2][3]
    **  3.a[0] type is int(*)
	**  4.&a[0] type is int(*)[3]
    */
    printf("a = %x, &a = %x\n", a, &a);
    printf("sizeof(a) = %d, sizeof(&a) = %d\n", sizeof(a), sizeof(&a));
    printf("a + 1 = %x, &a + 1 = %x\n", a + 1, &a + 1);

    printf("a[0] = %x, &a[0] = %x\n", a[0], &a[0]);
    printf("sizeof(a[0]) = %d, sizeof(&a[0]) = %d\n", sizeof(a[0]), sizeof(&a[0]));
    printf("a[0] + 1 = %x, &a[0] + 1 = %x\n", a[0] + 1, &a[0] + 1);
}
