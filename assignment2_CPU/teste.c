#include <stdio.h>

main(){
char a[2];
a[0] = 1;
a[1] = 0;

printf("%d\n", (a[0] & !a[1]));

}
