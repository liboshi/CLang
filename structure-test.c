#include <stdio.h>
#include <stdlib.h>


typedef struct {
        char *name;
        int age;
} infoa;

typedef struct {
        infoa a;
        char *sex;
        int grade;
} infob;

int
main() {
        infob *b = (infob *)malloc(sizeof(infob));
        b->a.name = "LiBoshi";
        printf("Your name is :%s\n", b->a.name);
        return 0;
}
