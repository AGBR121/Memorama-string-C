#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* CreateString(char cadena[], int counter, int number, char letter) {
    if (counter < number) {
        cadena[counter] = letter;
        return CreateString(cadena, counter + 1, number, letter);
    } else {
        cadena[counter] = '\0'; 
        return cadena;
    }
}

char* GenerateCadena(char cadena[], int counter, int counter2, int letter) {
    int num = rand() % 16;  
    
    if (counter < 16) {
        if (cadena[counter] != 'a') {
            return GenerateCadena(cadena, counter + 1, counter2, letter);
        } else {
            if (counter2 < 2) {
                if (cadena[num] == 'a') {
                    cadena[num] = letter; 
                    return GenerateCadena(cadena, 0, counter2 + 1, letter);
                } else {
                    return GenerateCadena(cadena, 0, counter2, letter);
                }
            } else {
                return GenerateCadena(cadena, 0, 0, letter + 1);  
            }
        }
    } else {
        return cadena; 
    }
}

void Game(int turn, char game[]) {
    int num = 0;
    printf("Escoja la casilla: ");
    scanf("%i", &num);
}

int main() {
    srand(time(NULL));

    char cadena[] = "aaaaaaaaaaaaaaaa";  
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    char player1[50];
    char player2[50];
    
    printf("\nEntre el nombre del jugador 1: ");
    scanf("%49s", player1); 
    
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%49s", player2);
    
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 12; 
    
    char espacios1[50]; 
    char espacios2[50]; 
    CreateString(espacios1, 0, nEspacios - longitud1, ' ');
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');

    printf("\n%s\n", game);
    printf("+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE\n| 1 | 2 | 3 | 4 |  Nombre jugador 01: %s%s0\n+---+---+---+---+  Nombre jugador 02: %s%s0\n", player1, espacios1, player2, espacios2);
    printf("| 5 | 6 | 7 | 8 |\n+---+---+---+---+\n| 9 |10 |11 |12 |\n+---+---+---+---+\n|13 |14 |15 |16 |\n+---+---+---+---+\n");
    
    return 0;
}
