#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void Game(int turn,char stringTable[], char initialTable[], char actualTable[], char player1[], char player2[], int score1, int score2, int selection, int counter);

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


void ChangeChar(char str[], int pos, char newChar) {
    if (pos < 9) {
        str[pos] = newChar;
    } else {
        int index = (pos - 9) * 2 + 9;
        str[index] = ' ';
        str[index + 1] = newChar;
    }
}


void PrintTable(char table[], char player1[], char player2[], char player[], char winner1[], char winner2[], char status[]) {
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 12;
    char espacios1[50];
    char espacios2[50];

    CreateString(espacios1, 0, nEspacios - longitud1, ' '); 
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');
    printf("\n+---+---+---+---+  JUEGO DEL CONCENTRESE        SCORE\n");
    printf("| %c | %c | %c | %c |  Nombre jugador 01: %s%s0\n", table[0], table[1], table[2], table[3], player1, espacios1);
    printf("+---+---+---+---+  Nombre jugador 02: %s%s0\n", player2, espacios2);
    printf("| %c | %c | %c | %c |\n", table[4], table[5], table[6], table[7]);
    printf("+---+---+---+---+  Juega: %s\n", player);
    printf("| %c |%c%c |%c%c |%c%c |  Status: %s\n", table[8], table[9], table[10], table[11], table[12], table[13], table[14], status);
    printf("+---+---+---+---+\n");
    printf("|%c%c |%c%c |%c%c |%c%c |\n", table[15], table[16], table[17], table[18], table[19], table[20], table[21], table[22]);
    printf("+---+---+---+---+\n");
}

int main() {
    srand(time(NULL));

    char cadena[] = "aaaaaaaaaaaaaaaa";  
    char* game = GenerateCadena(cadena, 0, 0, 'A');
    char player1[50];
    char player2[50];
    char initialTable[] = "12345678910111213141516";
    printf("\nEntre el nombre del jugador 1: ");
    scanf("%49s", player1); 
    
    printf("\nEntre el nombre del jugador 2: ");
    scanf("%49s", player2);
    
    int longitud1 = strlen(player1);
    int longitud2 = strlen(player2);
    int nEspacios = 16; 
    
    char espacios1[50]; 
    char espacios2[50]; 
    CreateString(espacios1, 0, nEspacios - longitud1, ' ');
    CreateString(espacios2, 0, nEspacios - longitud2, ' ');

    printf("\n%s\n", game);
    PrintTable(initialTable, player1, player2, player1, "", "", "");
    //Game(1, game, initialTable, initialTable, player1, player2, 0, 0, 0, 1);
    return 0;
}
