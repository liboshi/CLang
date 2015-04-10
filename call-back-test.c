#include <stdio.h>
#include <stdlib.h>

void print_two_numbers(int (*number_source) (void)) {
        printf("%d add %d\n", number_source(), number_source());
}

int over_nine_thousand(void) {
        return (rand() % 1000) + 9001;
}

int meaning_of_life(void) {
        return 29;
}

int main(void) {
        print_two_numbers(&rand);
        print_two_numbers(&over_nine_thousand);
        print_two_numbers(&meaning_of_life);
        return 0;
}
