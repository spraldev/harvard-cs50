#include <stdio.h>
#include <cs50.h>


int main (void) {
    int height;

    do {
        height = get_int("Height: ");
    } while(height < 1);
    int tempheight = height - 2;


    int counter = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= (tempheight); j++) {
            printf(" ");

        }
        for (int j = 0; j <= i; j++) {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j <= i; j++) {
            printf("#");
        }

        printf("\n");
        tempheight -= 1;

    }


}
