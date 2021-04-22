#include <stdio.h>

// O implementare foarte simplă a copierii de fișiere
int main(int argc, const char *argv[])
{
    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("eroare la deschiderea fisierului de intrare\n");
        return -1;
    }
    FILE *fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        printf("eroare la deschidere fisierului de iesire\n");
        fclose(fin);
        return -1;
    }

    do
    {
        int c = fgetc(fin);
        if (c == EOF)
        {
            break;
        }
        //printf("%c", c);
        fputc(c, fout);
    } while (1);

    fclose(fin);
    fclose(fout);
    return 0;
}
