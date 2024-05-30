#include <stdio.h>  //biblioteca standard de intrare/ieșire
#include <string.h>  //biblioteca pentru manipularea șirurilor de caractere
#include <stdlib.h>  //biblioteca standard

// Funcție pentru a găsi valoarea minimă dintre trei numere
int min(int a, int b, int c) {
    // Returnează cel mai mic număr dintre a, b și c
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

// Aceasta este funcția principală care calculează distanța Levenshtein între două șiruri de caractere
int levenshtein_distance(const char *s1, const char *s2) {
    // Lungimea șirului s1
    int m = strlen(s1);
    // Lungimea șirului s2
    int n = strlen(s2);
    // Alocare memorie pentru o matrice bidimensională pentru a stoca rezultatele intermediare
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));  //Matricea dp este inițializată cu dimensiunea (m+1)x(n+1), unde m și n sunt lungimile celor două șiruri.
    }

    // Inițializare matrice
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;  // Inserare a j caractere
            } else if (j == 0) {
                dp[i][j] = i;  // Ștergere a i caractere
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];  // Nicio operație
            } else {
                dp[i][j] = 1 + min(dp[i][j - 1],    // Inserare
                                   dp[i - 1][j],    // Ștergere
                                   dp[i - 1][j - 1]); // Substituire
            }
        }
    }

    // Calculare rezultat final
    int result = dp[m][n];

    // Eliberare memorie
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    // Șirurile pentru care se calculează distanța Levenshtein
    const char *s1 = "fnuc(myFuncion ";
    const char *s2 = "func(myFunction)";

    // Calcularea distanței Levenshtein
    int distanta = levenshtein_distance(s1, s2);
    // Afisare rezultat
    printf("Numarul minim de operatii necesare: %d\n", distanta);

    return 0;
}
