#include "raylib.h"

#define MAX_SIZE 50
#define CELL_WIDTH 40
#define CELL_HEIGHT 40

void DrawArray(int *array, int size, int highlightedIndex);
void QuickSort(int *array, int low, int high);
void insererDansTableauTriee(int tableau[], int *taille, int valeur) {
    // Vérifier si le tableau a de la place pour la nouvelle valeur
    if (*taille >= MAX_SIZE) {
        printf("Tableau plein, impossible d'insérer la nouvelle valeur.\n");
        return;
    }

    // Trouver la position d'insertion en conservant l'ordre croissant
    int position = 0;
    while (position < *taille && tableau[position] < valeur) {
        position += 1;
    }

    // Décaler les éléments du tableau vers la droite à partir de la position d'insertion
    for (int i = *taille; i > position; i--) {
        tableau[i] = tableau[i - 1];
    }

    // Insérer la nouvelle valeur à la position spécifiée
    tableau[position] = valeur;

    // Augmenter la taille du tableau
    *taille = *taille + 1;
}
int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tri Rapide avec Interface");

    int *array = (int *)malloc(MAX_SIZE * sizeof(int));
    int size = 0;
    int highlightedIndex = -1;  // Index de l'élément en cours de traitement

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Afficher le tableau actuel
        DrawArray(array, size, highlightedIndex);

        // Afficher les options
        DrawText("Options:", 10, 80, 20, DARKGRAY);
        DrawText("1. Ajouter un nombre", 10, 110, 20, DARKGRAY);
        DrawText("2. Trier (QuickSort)", 10, 140, 20, DARKGRAY);
        DrawText("3. Quitter", 10, 170, 20, DARKGRAY);

        // Lire l'entrée utilisateur
        int choice = GetKeyPressed();

    int taille, val, tableau[MAX_SIZE];

    // Demander la taille du tableau
    printf("Donnez la taille du tableau : ");
    scanf("%d", &taille);

    // Demander les valeurs du tableau
    for (int i = 0; i < taille; i++) {
        printf("Donnez la valeur %d : ", i + 1);
        scanf("%d", &tableau[i]);
    }

               switch (choice) {
            case '2': // Trier (QuickSort)
                QuickSort(array, 0, size - 1);
                highlightedIndex = -1;
// Réinitialiser l'index en          surbrillance après le tri
                break;
          case '1':
     printf("Donnez la valeur que vous souhaitez insérer : ");
     scanf("%d", &val);
     insererDansTableauTriee(tableau, &taille, val);
highlightedIndex = -1;
     DrawArray(*tableau,taille,highlightedIndex);
     break;

            case '3': // Quitter
                CloseWindow();
                break;
            default:
                break;
        }

        EndDrawing();
    }

    free(array);

    return 0;
}

// Fonction pour dessiner le tableau avec les cases
void DrawArray(int *array, int size, int highlightedIndex) {
    DrawText("Tableau Actuel:", 10, 10, 20, DARKGRAY);

    for (int i = 0; i < size; i++) {
        if (i == highlightedIndex) {
            DrawRectangle(10 + i * (CELL_WIDTH + 5), 40, CELL_WIDTH, CELL_HEIGHT, ORANGE);
        } else {
            DrawRectangle(10 + i * (CELL_WIDTH + 5), 40, CELL_WIDTH, CELL_HEIGHT, PINK);
        }

        DrawText(TextFormat("%d", array[i]), 10 + i * (CELL_WIDTH + 5) + CELL_WIDTH / 4,
                 40 + CELL_HEIGHT / 4, 20, DARKGRAY);
    }
}

// Fonction pour le tri rapide (QuickSort)
void QuickSort(int *array, int low, int high) {
    if (low < high) {
        int pivotIndex = low;
        int pivotValue = array[pivotIndex];
        int i = low;
        int j = high;

        while (i < j) {
            while (array[i] <= pivotValue && i <= high) {
                i++;
            }

            while (array[j] > pivotValue && j >= low) {
                j--;
            }
if (i < j) {
                // Échanger array[i] et array[j]
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;

                // Mettre à jour l'index en surbrillance
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawArray(array, high + 1, i);
                EndDrawing();

                // Attendre un court instant pour voir le changement
                while (GetTime() < 0.1) {}  // Pause d'environ 0.1 seconde
            }
        }

        // Échanger array[low] et array[j]
        int temp = array[low];
        array[low] = array[j];
        array[j] = temp;

        // Mettre à jour l'index en surbrillance
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawArray(array, high + 1, j);
        EndDrawing();

        // Attendre un court instant pour voir le changement
        while (GetTime() < 0.1) {}  // Pause d'environ 0.1 seconde

        // Trier les sous-tableaux à gauche et à droite du pivot
        QuickSort(array, low, j - 1);
        QuickSort(array, j + 1, high);
    }
}
