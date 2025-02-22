#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
 * Aplicaremos el cifrado de cesar que es a traves del siguiente modelo matematico
 * M + (K mod A) = C
 */
char* cifrar(char* mensaje, int llave, char* alfabeto) {

    char* mensaje_cifrado = malloc(strlen(mensaje));

    for(int i = 0; i < strlen(mensaje); i++) {

        int pos = buscar_letra(alfabeto, mensaje[i]);

        mensaje_cifrado[i] = alfabeto[pos + (llave % strlen(alfabeto))];

    }

    return mensaje_cifrado;

}
/***
 * Aplicaremos el inverso del cifrado que tambien hay un modelo matematico para esto
 * C - (K mod A) = M
 */
char* descifrar(char* mensaje_cifrado, int llave, char* alfabeto) {

    char* mensaje_descifrado = malloc(strlen(mensaje_cifrado));

    for(int i = 0; i < strlen(mensaje_cifrado); i++) {

        int pos = buscar_letra(alfabeto, mensaje_cifrado[i]);

        mensaje_descifrado[i] = alfabeto[pos - (llave % strlen(alfabeto))];

    }

    return mensaje_descifrado;

}

int main() {

    char mensaje[256],
        *alfabeto = malloc(26);

    srand(time(NULL));

    llenar_array(alfabeto);

    printf("Escriba un mensaje [solo letras y sin espacios]: ");
    fgets(mensaje, 256, stdin);

    int llave = 1 + rand() % ((30 + 1) - 1);

    char* mensaje_cifrado = cifrar(mensaje, llave, alfabeto);

    printf("\n\nMensaje encriptado: %s\n", mensaje_cifrado);

    char* mensaje_descifrado = descifrar(mensaje_cifrado, llave, alfabeto);

    printf("\n\nEl mensaje descifrado es: %s\n", mensaje_descifrado);

    liberar_memoria(alfabeto);
    liberar_memoria(mensaje_cifrado);
    liberar_memoria(mensaje_descifrado);

    return 0;

}