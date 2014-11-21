#include <stdio.h>

int main(int argc, char *argv[])
{
        FILE *fp;
        char c;
        char buff[1024 * 1024];
        int i = 0;
        fp = fopen(argv[1], "r");
        while (!feof(fp)) {
                c = fgetc(fp);
                buff[i++] = c;
        }
        fclose(fp);
        buff[i - 1] = '\0';
        for (int j = 0;;j++) {
                if (buff[j] != '\0') {
                        printf("%c", buff[j]);
                } else {
                        break;
                }
        }
}
