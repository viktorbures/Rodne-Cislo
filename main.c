#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN_YEAR 1954
#define MAX_YEAR 2026

#define MIN_MONTH 1
#define MAX_MONTH 12

#define MIN_DAY 1
#define MAX_DAY 31

#define MIN_POHLAVI 0
#define MAX_POHLAVI 1

#define MIN_TROJCISLI 0
#define MAX_TROJCISLI 999

int buffer() {
    int characters = 0;

    while (getchar() != '\n') {
        characters++;
    }
    if (characters != 0) {
        return 0;
    }
    return 1;
}

int zadaneCislo(int min, int max, const char *text) {
    int hodnota;
    int characters;

    do {
        printf("%s (%d - %d):\n", text, min, max);
        scanf("%d", &hodnota);

        characters = buffer();
        if (!characters) {
            printf("Invalidni input, zkus to znova. \n");
        } else if (hodnota > max || hodnota < min) {
            printf("Zadane cislo neni v intervalu od %d do %d. \n", min, max);
        }

    } while (hodnota > max || hodnota < min || !characters);

    return hodnota;
}

void rodneCislo(int rok, int mesic, int den, int pohlavi, int trojcisli, int posledniCislo, char * rc) {
    int r, m, d, p, t, pc;

    r = rok % 100;

    if(pohlavi == 0) {
        m = mesic + 50;
    }
    else {
        m = mesic;
    }

    d = den;
    t = trojcisli;
    pc = posledniCislo;

    sprintf(rc, "%02d%02d%02d/%03d%d", r, m, d, t, pc);
}

int main(void) {
    srand((unsigned) time(NULL));
    char again;
    char rc[20];

    do {
        int rok = zadaneCislo(MIN_YEAR, MAX_YEAR, "Zadej rok");
        int mesic = zadaneCislo(MIN_MONTH, MAX_MONTH, "Zadej mesic");
        int den = zadaneCislo(MIN_DAY, MAX_DAY, "Zadej den");
        int pohlavi = zadaneCislo(MIN_POHLAVI, MAX_POHLAVI, "Zadej pohlavi (0 - zena, 1 - muz)");
        int trojcisli = zadaneCislo(MIN_TROJCISLI, MAX_TROJCISLI, "Zadej trojcisli");
        int posledniCislo = rand() % 10;

        rodneCislo(rok, mesic, den, pohlavi, trojcisli, posledniCislo, rc);
        printf("Rodne cislo je: %s \n", rc);

        printf("Pro opakovani zadani rodneho cisla stiskni Enter: \n");
        scanf("%c", &again);
    } while(again == '\n');

    /* DODELAT:
        - Prestupny rok
        - Kazdy mesic ma jiny pocet dnu
        - Neco s delenim %11 idk
    */


    return 0;
}
