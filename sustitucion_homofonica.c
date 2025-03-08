#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/***
 * Liberamos la memoria que usaremos con calloc.
*/
void liberar_memoria(char* cadena) {

    free(cadena);

}

/***
 * Vamos a llenar un arreglo con las letras del abecedario.
 */
void llenar_array(char* alfabeto) {

    for(int i = 0; i < 26; i++) {

        alfabeto[i] = ((char) 97 + i);

    }

}

/***
 * Buscaremos una letra, para conocer en la posicion en la que se encuentra.
 */
int buscar_letra(char* alfabeto, char letra) {

    int i = 0, bandera = 0;

    int pos = 0;

    while(i < strlen(alfabeto) && ! bandera) {

        if(alfabeto[i] == tolower(letra)) { pos = i; bandera = 1; }

        else i++;

    }

    if(bandera) return pos;

}
/***
 *  Realizamos el cifrado, lo haremos mediante la matriz que creamos
 *  anteriormente, ya que de esta forma con las letras que mas se repiten
 *  dentro de una frase, seran las que tendran una variacion en el
 *  simbolo que se mostrara para cifrarlo.    
 */
char* cifrar(char* mensaje, char matriz[][3], char* alfabeto) {

    char* mensaje_cifrado = malloc(strlen(mensaje));

    srand(time(NULL));

    for(int i = 0; i < strlen(mensaje); i++) {

        int pos = buscar_letra(alfabeto, mensaje[i]);

        mensaje_cifrado[i] = matriz[pos][rand() % 3];

    }

    return mensaje_cifrado;

}
/***
 * Buscaremos un simbolo, para conocer en la posicion en la que se encuentra.
 */
int busca_matriz(char matriz[][3], char caracter) {

    int i = 0, j = 0, bandera = 0;

    int pos = 0;

    while(i < 26) {

        j = 0;

        while(j  < 3 && ! bandera) {

            if(matriz[i][j] == caracter) { pos = i; bandera = 1; }

            else j++;

        }

        i++;

    }

    return pos;

}
/***
 * Desciframos el mensaje pero debemos buscar el simbolo que esta
 * dentro de la matriz, y obteniendo la posicion, cambiaremos el simbolo
 * por la letra que este dentro del alfabeto y de esta forma estara completo
 * el descifrado.
 */
char* descifrar(char* mensaje_cifrado, char matriz[][3], char* alfabeto) {

    char* mensaje_descifrado = malloc(strlen(mensaje_cifrado));

    for(int i = 0; i < strlen(mensaje_cifrado); i++) {

        int pos = busca_matriz(matriz, mensaje_cifrado[i]);

        mensaje_descifrado[i] = alfabeto[pos];

    }

    return mensaje_descifrado;

}

int main() {

    /***
     * Construimos una matriz, para realizar el cifrado 
     * , dependiendo de la letra que mas se repita, tendra
     * 3 opciones para cambiar el digito.
     */
    char a[26][3] = {

        {'1', '@', '!'}, //a
        {'2', '2', '2'}, //b
        {'n', 'n', 'n'}, //c
        {'4', '4', '4'}, //d
        {'%', '.', ':'}, //e
        {'3', '3', '3'}, //f
        {'a', 'a', 'a'}, //g
        {'#', '"', '$'}, //h
        {'=', '{', '-'}, //i
        {'c', 'c', 'c'}, //j
        {'d', 'd', 'd'}, //k
        {'?', '}', '*'}, //l
        {'r', 'r', 'r'}, //m
        {'/', '+', '^'}, //n
        {'|', 'F', '['}, //o
        {'h', 'h', 'h'}, //p
        {'x', 'x', 'x'}, //q
        {')', '(', '&'}, //r
        {';', ',', '_'}, //s
        {'<', '>', ']'}, //t
        {'p', 'p', 'p'}, //u
        {'5', '5', '5'}, //v
        {'7', '7', '7'}, //w
        {'v', 'v', 'v'}, //x
        {'s', 's', 's'}, //y
        {'0', '0', '0'}  //z
    
    };
    
    char *alfabeto = malloc(26);

    llenar_array(alfabeto);   

    char mensaje[256];

    printf("Escriba un mensaje [solo letras y sin espacios]: ");
    if (fgets(mensaje, 256, stdin)) mensaje[strcspn(mensaje, "\n")] = 0; 
    
    
    char* mensaje_cifrado = cifrar(mensaje, a, alfabeto);

    printf("Mensaje cifrado: %s\n", mensaje_cifrado);

    
    char* mensaje_descifrado = descifrar(mensaje_cifrado, a, alfabeto);

    printf("Mensaje descifrado: %s", mensaje_descifrado);


    printf("\n\n");

    liberar_memoria(alfabeto);
    liberar_memoria(mensaje_cifrado);
    liberar_memoria(mensaje_descifrado);

    return 0;

}