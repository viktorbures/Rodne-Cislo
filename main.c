#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MIN_YEAR 1954
#define MAX_YEAR 2026

#define MIN_MONTH 1
#define MAX_MONTH 12

#define MIN_DAY 1

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

int prestupnyRok(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0;
}

int dniVMesici(int rok, int mesic) {
    switch (mesic) {
        case 1:
            return 31;
        case 2:
            return prestupnyRok(rok) ? 29 : 28;
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            return 0;
    }
}

int posledniCislo(long long int zaklad) {
    int zbytek = (zaklad * 10) % 11;

    return (11 - zbytek) % 11;
}

void rodneCislo(int rok, int mesic, int den, int pohlavi, int trojcisli, int posledniCislo, char *rc) {
    int r = rok % 100;
    int m;

    if (pohlavi == 0) {
        m = mesic + 50;
    } else {
        m = mesic;
    }

    sprintf(rc, "%02d%02d%02d/%03d%d", r, m, den, trojcisli, posledniCislo);
}

int main(void) {
    srand((unsigned) time(NULL));
    char again;
    char rc[20];
    char zakladStr[20];

    do {
        int rok = zadaneCislo(MIN_YEAR, MAX_YEAR, "Zadej rok");
        int mesic = zadaneCislo(MIN_MONTH, MAX_MONTH, "Zadej mesic");

        int maxDen = dniVMesici(rok, mesic);
        int den = zadaneCislo(MIN_DAY, maxDen, "Zadej den");

        int pohlavi = zadaneCislo(MIN_POHLAVI, MAX_POHLAVI, "Zadej pohlavi (0 - zena, 1 - muz)");
        int trojcisli = zadaneCislo(MIN_TROJCISLI, MAX_TROJCISLI, "Zadej trojcisli");


        sprintf(zakladStr, "%02d%02d%02d%03d", rok, mesic, den, trojcisli);
        long long int zaklad = atoll(zakladStr);

        int posledniNum = posledniCislo(zaklad);
        rodneCislo(rok, mesic, den, pohlavi, trojcisli, posledniNum, rc);
        printf("Rodne cislo je: %s \n", rc);

        printf("Pro opakovani zadani rodneho cisla stiskni Enter: \n");
        scanf("%c", &again);
    } while (again == '\n');

    return 0;
}
