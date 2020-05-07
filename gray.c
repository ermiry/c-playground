#include <stdio.h>
#include <math.h>
 
int gray (int bin) {

    int a, b, result = 0, i = 0;
 
    while (bin != 0) {
        a = bin % 10;
        bin = bin / 10;
        b = bin % 10;
        if ((a && !b) || (!a && b)) {
            result = result + pow(10, i);
        }

        i++;
    }

    return result;

}
 
int main (void) {

    int bin;
    printf("Enter a binary number: ");
    scanf("%d", &bin);
    printf("The gray code of %d is %d\n", bin, gray (bin));

    return 0;

}