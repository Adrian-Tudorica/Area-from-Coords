#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 500000    // Grid = 500000 x 500000 patratele
#define ZECIMALE 10.0      // Pentru numere rationale

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    } // De revizuit si revizitat

    printf("\n");

    const char *filename = argv[1];

    // Alocare dinamica pentru grid
    int *grid = calloc(MAX_SIZE * MAX_SIZE, sizeof(int));
    if (grid == NULL) {                     // Verificare alocare
        printf("Eroare alocare memorie\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");      // Fisierul text se deschide in read only
    if (file == NULL) {                     // Se verifica daca fisierul s-a deschis
        printf("Eroare deschidere fisier\n");
        free(grid);
        return 1;
    }

    int n;
    fscanf(file, "%d", &n); // Citeste numarul de dreptunghiuri din fisier

    for (int i = 0; i < n; i++) {
        double xmin, ymin, xmax, ymax;
        fscanf(file, "%lf %lf %lf %lf", &xmin, &ymin, &xmax, &ymax);

        // Pentru convertire float - int, pe grid
        int z_xmin = (int)floor(xmin * ZECIMALE);
        int z_ymin = (int)floor(ymin * ZECIMALE);
        int z_xmax = (int)ceil(xmax * ZECIMALE);
        int z_ymax = (int)ceil(ymax * ZECIMALE);

        // Fiecare patratica de 1x1
        for (int x = z_xmin; x < z_xmax; x++) {
            for (int y = z_ymin; y < z_ymax; y++) {
                grid[x * MAX_SIZE + y] = 1; // Se marcheaza spatiul ocupat
            }
        }
    }

    fclose(file);

    // Calcul arie
    int total_arie_counter = 0;
    for (int i = 0; i < MAX_SIZE * MAX_SIZE; i++) {
        if (grid[i] == 1) {
            total_arie_counter++;
        }
    }

    double total_arie = total_arie_counter / (ZECIMALE * ZECIMALE);

    printf("Aria totala este de: %lf\n", total_arie);

    free(grid);

    return 0;
}
