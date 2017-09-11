#include <stdio.h>
#include <stdlib.h>

void
remove_whitespaces(char *s) {
        char *i = s;
        do {
                *i = *s;
                if (*i != ' ') i++;
        } while (*s++ != '\0');
}

int
main() {
        char s[] = "a bc d e f       g";
        remove_whitespaces(s);
        printf("The string is: %s\n", s);
        return 0;
}
