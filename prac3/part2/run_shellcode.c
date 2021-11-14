#include <stdio.h>

int main()
{
    char buffer[1024];
    FILE *fp;

    fp = fopen("a.out", "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp); /* same as rewind(f); */
    fread(buffer, 1, fsize, fp);
    fclose(fp);

    void (*func)() = (void (*)())buffer;
    func();
}
