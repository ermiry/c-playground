#include <stdlib.h>
#include <stdio.h>

int main (void) {

    size_t max_cols = 10;
    size_t max_rows = 5;
    int **hand_objects = (int **) calloc (max_cols, sizeof (int *));
    for (unsigned int i = 0; i < max_cols; i++)
        hand_objects[i] = (int *) calloc (max_rows, sizeof (int));

    int count = 0;
    for (unsigned int cols = 0; cols < max_cols; cols++) {
        for (unsigned int rows = 0; rows < max_rows; rows++) {
            hand_objects[cols][rows] = count;
            count++;
        }
    }

    for (unsigned int cols = 0; cols < max_cols; cols++) {
        for (unsigned int rows = 0; rows < max_rows; rows++) {
            printf ("%4d", hand_objects[cols][rows]);
        }

        printf ("\n");
    }

    for (unsigned int rows = 0; rows < max_rows; rows++) {
        for (unsigned int cols = 0; cols < max_cols; cols++) {
            printf ("%4d", hand_objects[cols][rows]);
        }

        printf ("\n");
    }

    

    for (unsigned int i = 0; i < max_cols; i++) free (hand_objects[i]);
    free (hand_objects);

    return 0;

}