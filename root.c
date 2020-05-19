#include <stdlib.h>
#include <stdio.h>

int isqrt (int a) {

    int m = 1 << sizeof(int) * 4 -1;
    int rxr, r = 0;

    for (int i = 0; m != 0; i++, m >>= 1) {
        // printf ("m: %d\n", m);
        r |= m;
        // printf ("r: %d\n", r);
        rxr = r*r;
        if (rxr == a) { return r; }
        if (rxr > a) { 
            r &= ~m;
            // printf ("r &= ~m -> %d\n", r);
            // printf ("m: %d\n", m);
        }

        else {
            // printf ("\n\nNEG!\n\n");
        }
    }

    // printf ("\n\nm: %d\n\n", m);

    return r;

}

int main (void) {

    printf ("\nresult: %d\n", isqrt (25));

    return 0;

}