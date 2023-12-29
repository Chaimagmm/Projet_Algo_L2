#include "raylib.h"
#include <time.h>
#define MAX_SIZE 50
#define CELL_WIDTH 40
#define CELL_HEIGHT 40
#define OFFSET_X 10
#define OFFSET_Y 40
#define SPEED 10

void DrawArray(int *array, int size, int highlightedIndex, int pivotIndex);
void QuickSort(int *array, int low, int high);
void Swap(int *array, int i, int j);
int BinarySearch(int *array, int low, int high, int value);
void DeleteFirst(int *array, int *size);
void DeleteLast(int *array, int *size);
void InsertFirst(int *array, int *size, int value);
void InsertLast(int *array, int *size, int value);

int main(void) {
const int screenWidth = 800;
const int screenHeight = 450;

InitWindow(screenWidth, screenHeight, "Tri Rapide avec Animation");

int array[MAX_SIZE]; // Déclarer le tableau comme un tableau statique
int size = 0;

SetTargetFPS(60);

while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // Afficher le tableau actuel
    DrawArray(array, size, -1, -1);

    // Afficher les options
    DrawText("Options:", 10, 80, 20, DARKGRAY);
    DrawText("1. Ajouter un nombre au debut", 10, 110, 20, DARKGRAY);
    DrawText("2. Ajouter un nombre a la fin", 10, 140, 20, DARKGRAY);
    DrawText("3. Supprimer le premier element", 10, 170, 20, DARKGRAY); // Corriger la faute de frappe
    DrawText("4. Supprimer le dernier element", 10, 200, 20, DARKGRAY);
    DrawText("5. Trier (QuickSort)", 10, 230, 20, DARKGRAY);
    DrawText("6. Rechercher (BinarySearch)", 10, 260, 20, DARKGRAY);
    DrawText("7. Quitter", 10, 290, 20, DARKGRAY);

    // Lire l'entrée utilisateur
    if (IsKeyPressed(KEY_ONE)) { // Utiliser IsKeyPressed de raylib
        if (size < MAX_SIZE) {
            int value = GetRandomValue(10, 200); // Utiliser GetRandomValue de raylib
            //InsertLast(array, &size, value); // Commenter cette ligne inutile
            InsertFirst(array, &size, value); // Ajouter un nombre au début
        }
    } else if (IsKeyPressed(KEY_TWO)) {

        if (size < MAX_SIZE) { // Ajouter cette condition
            int value = GetRandomValue(10, 200); // Utiliser GetRandomValue de raylib
            InsertLast(array, &size, value); // Ajouter un nombre à la fin
        }
    } else if (IsKeyPressed(KEY_THREE)) {
        if (size > 0) {
            DeleteFirst(array, &size); // Supprimer le premier élément
        }
    } else if (IsKeyPressed(KEY_FOUR)) {
        if (size > 0) {
            DeleteLast(array, &size); // Supprimer le dernier élément
        }
    } else if (IsKeyPressed(KEY_FIVE)) {
        if (size > 0) {
            QuickSort(array, 0, size - 1); // Trier le tableau
        }
    } else if (IsKeyPressed(KEY_SIX)) {
        if (size > 0) { // Ajouter cette condition
            int value = GetRandomValue(10, 200); // Utiliser GetRandomValue de raylib
            int index = BinarySearch(array, 0, size - 1, value); // Rechercher une valeur
            if (index != -1) {
                DrawText(TextFormat("L'element %d se trouve à l'index %d", value, index), 10, 320, 20, DARKGRAY);

            } else {
                DrawText(TextFormat("L'element %d n'existe pas dans le tableau", value), 10, 320, 20, DARKGRAY);

            }
        }
    } else if (IsKeyPressed(KEY_SEVEN)) {
        CloseWindow(); // Utiliser CloseWindow de raylib
    }

    EndDrawing();
}
return 0;
}

// Fonction pour dessiner le tableau avec les rectangles
void DrawArray(int *array, int size, int highlightedIndex, int pivotIndex) {
    DrawText("Tableau Actuel:", 10, 10, 20, DARKGRAY);

    for (int i = 0; i < size; i++) {
        if (i == highlightedIndex) {
            DrawRectangle(OFFSET_X + i * (CELL_WIDTH + 5), OFFSET_Y, CELL_WIDTH, CELL_HEIGHT, ORANGE);
        } else if (i == pivotIndex) {
            DrawRectangle(OFFSET_X + i * (CELL_WIDTH + 5), OFFSET_Y, CELL_WIDTH, CELL_HEIGHT, RED);
        } else {
            DrawRectangle(OFFSET_X + i * (CELL_WIDTH + 5), OFFSET_Y, CELL_WIDTH, CELL_HEIGHT, PINK);
        }

        DrawText(TextFormat("%d", array[i]), OFFSET_X + i * (CELL_WIDTH + 5) + CELL_WIDTH / 4,
                 OFFSET_Y + CELL_HEIGHT / 4, 20, DARKGRAY);
    }
}

// Fonction pour le tri rapide (QuickSort)
void QuickSort(int *array, int low, int high) {
    if (low < high) {
        int pivotIndex = low;
        int pivotValue = array[pivotIndex];
        int i = low;
        int j = high;

        // Afficher le tableau avant la partition
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawArray(array, high + 1, -1, pivotIndex);
        DrawText("Avant la partition : \n", 10, 200, 20, DARKGRAY);
        for (int k = low; k <= high; k++) {
            DrawText(TextFormat("%d ", array[k]), 180 + k * 40, 200, 20, DARKGRAY);
        }
        EndDrawing();

        // Attendre un court instant pour voir le changement
        double startTime = GetTime(); // Enregistrer le temps de départ
        while (GetTime() - startTime < 2) {} // Attendre 2 seconde

        while (i < j) {
            while (array[i] <= pivotValue && i <= high) {
                i++;
            }

            while (array[j] > pivotValue && j >= low) {
                j--;
            }

            if (i < j) {
                // Échanger array[i] et array[j]
                Swap(array, i, j);

                // Mettre à jour l'index en surbrillance
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawArray(array, high + 1, i, pivotIndex);
                EndDrawing();

                // Attendre un court instant pour voir le changement
                startTime = GetTime(); // Enregistrer le temps de départ
                while (GetTime() - startTime < 2) {} // Attendre 2 seconde
            }
        }

        // Échanger array[low] et array[j]
        Swap(array, low, j);

        // Mettre à jour l'index en surbrillance
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawArray(array, high + 1, j, -1);
        EndDrawing();

        // Attendre un court instant pour voir le changement
        startTime = GetTime(); // Enregistrer le temps de départ
        while (GetTime() - startTime < 2) {} // Attendre 2 seconde

        // Afficher le tableau après la partition
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawArray(array, high + 1, -1, -1);
        DrawText("Apres la partition : \n", 10, 230, 20, DARKGRAY);
        for (int k = low; k <= high; k++) {
            DrawText(TextFormat("%d ", array[k]), 180 + k * 40, 230, 20, DARKGRAY);
        }

        // Afficher la valeur et l'index du pivot
        DrawText(TextFormat("Pivot : %d (index : %d)", array[j], j), 10, 260, 20, DARKGRAY);
        EndDrawing();

        // Attendre un court instant pour voir le changement
        startTime = GetTime(); // Enregistrer le temps de départ
        while (GetTime() - startTime < 2) {} // Attendre 2 seconde

        // Trier les sous-tableaux à gauche et à droite du pivot
        QuickSort(array, low, j - 1);
        QuickSort(array, j + 1, high);
    }
}
// Fonction pour la recherche dichotomique (BinarySearch)
int BinarySearch(int *array, int low, int high, int value) {
    // Si l'intervalle de recherche est vide, la valeur n'est pas dans le tableau
    if (low > high) {
        return -1;
    }
    // Sinon, on calcule l'indice du milieu de l'intervalle
    int mid = (low + high) / 2;
    // Si la valeur du milieu est égale à la valeur recherchée, on la renvoie
    if (array[mid] == value) {
        return mid;
    }
    // Sinon, si la valeur du milieu est plus grande que la valeur recherchée, on cherche dans la partie gauche du tableau
    else if (array[mid] > value) {
        return BinarySearch(array, low, mid - 1, value);
    }
    // Sinon, on cherche dans la partie droite du tableau
    else {
        return BinarySearch(array, mid + 1, high, value);
    }
}

// Fonction qui échange deux éléments du tableau
void Swap(int *array, int i, int j) {
    // Stocker la valeur du tableau à l'index i dans une variable temporaire
    int temp = array[i];
    // Affecter la valeur du tableau à l'index j au tableau à l'index i
    array[i] = array[j];
    // Affecter la valeur de la variable temporaire au tableau à l'index j
    array[j] = temp;
}


// Fonction qui supprime le premier élément du tableau
void DeleteFirst(int *array, int *size) {
    // Si la taille du tableau est supérieure à 0
    if (*size > 0) {
        // Parcourir le tableau avec une boucle for
        for (int i = 0; i < *size - 1; i++) {
            // Affecter la valeur du tableau à l'index i+1 au tableau à l'index i
            array[i] = array[i + 1];
        }
        // Diminuer la taille du tableau de 1
        (*size)--;
    }
}
// Fonction qui supprime le dernier élément du tableau
void DeleteLast(int *array, int *size) {
    // Si la taille du tableau est supérieure à 0
    if (*size > 0) {
        // Diminuer la taille du tableau de 1
        (*size)--;
    }
}
// Fonction qui ajoute un élément au début du tableau
void InsertFirst(int *array, int *size, int value) {
    // Si la taille du tableau est inférieure à la taille maximale
    if (*size < MAX_SIZE) {
        // Parcourir le tableau à l'envers avec une boucle for
        for (int i = *size - 1; i >= 0; i--) {
            // Affecter la valeur du tableau à l'index i au tableau à l'index i+1
            array[i + 1] = array[i];
        }
        // Affecter la valeur à ajouter au tableau à l'index 0
        array[0] = value;
        // Augmenter la taille du tableau de 1
        (*size)++;
    }
}

// Fonction qui ajoute un élément à la fin du tableau
void InsertLast(int *array, int *size, int value) {
    // Si la taille du tableau est inférieure à la taille maximale
    if (*size < MAX_SIZE) {
        // Affecter la valeur à ajouter au tableau à l'index de la taille actuelle
        array[*size] = value;
        // Augmenter la taille du tableau de 1
        (*size)++;
    }
}
