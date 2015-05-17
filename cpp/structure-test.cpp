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
        infob *c = new infob[2];
        c[0].a.name = "Boush";
        printf("Your english name is :%s\n", c[0].a.name);
        return 0;
}
