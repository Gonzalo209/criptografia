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
    printf("\n\n");
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
 * Verificamos si las cadenas son de la misma longitud o no.
 */
int verificar_longitud(char* mensaje, char* llave) {

    return strlen(mensaje) == strlen(llave);

}
/***
 * En caso de que las cadenas no sean de la misma longitud,
 * debemos conocer cual es la menor de ellas.
 */
int obtener_menor(char* mensaje, char* llave) {

    return (strlen(mensaje) < strlen(llave) ? strlen(mensaje): strlen(llave));

}
/***
 * Y al obtener la menor cadena, debemos obtener el dato de por cuanto
 * es mayor la otra cadena, es decir, por 1, 2 o n caracteres.
 */
long int obtener_diferencia(char* mensaje, char* llave) {

    return (strlen(mensaje) < strlen(llave) ? strlen(llave) - strlen(mensaje): 
    strlen(mensaje) - strlen(llave));

}
/***
 * Al tener las condiciones, debemos aumentar los caracteres a la cadena menor
 * para que asi tengan la misma longitud y poder aplicar el cifrado.
 */
char* aumentar_caracteres(char* caracter, int n) {

    char* nuevo_caracter = malloc(256);

    strcpy(nuevo_caracter, caracter);

    char* a = malloc(n);

    for(int i = 0; i < n; i++) {

        a[i] = caracter[i % strlen(caracter)];

    }

    strcat(nuevo_caracter, a);

    liberar_memoria(a);

    return nuevo_caracter;

}
/***
 * Aplicaremos el cifrado de vigenere que es a traves del siguiente modelo matematico
 * (M + K) mod A) = C
 */
char* cifrar(char* mensaje, char* llave, char* alfabeto) {

    char* mensaje_cifrado = malloc(strlen(mensaje));

    for(int i = 0; i < strlen(mensaje); i++) {

        int pos = buscar_letra(alfabeto, mensaje[i]);
        int pos2 = buscar_letra(alfabeto, llave[i]);


        mensaje_cifrado[i] = alfabeto[(pos + pos2) % strlen(alfabeto)];
    
    }

    return mensaje_cifrado;

}
/***
 * Aplicaremos el inverso del cifrado que tambien hay un modelo matematico para esto
 * (C - K) mod A) = M
 */
char* descifrar(char* mensaje_cifrado, char* llave, char* alfabeto, long int total) {

    char* mensaje_descifrado = malloc(strlen(mensaje_cifrado));

    for(int i = 0; i < total; i++) {

        int pos = buscar_letra(alfabeto, mensaje_cifrado[i]);
        int pos2 = buscar_letra(alfabeto, llave[i]);

         
        if((pos - pos2) < 0) mensaje_descifrado[i] = alfabeto[(pos - pos2) + strlen(alfabeto)];
        else mensaje_descifrado[i] = alfabeto[(pos - pos2) % strlen(alfabeto)];
        
    }

    return mensaje_descifrado;
    
}
/***
 * Como comentamos anteriormente en los modulos de arriba, para poder aplicar este cifrado, 
 * debemos seguir estos pasos.
 * 1. Que tengan la misma longitud.
 * 2. En caso de que no tengan la misma longitud, conocer la diferencia de caracteres.
 * 3. Aumentar los caracteres a la llave o mensaje.
 * 4. Aplicar el cifrado y descifrado.
 */
void verificar(char* mensaje, char* llave, char* alfabeto) {

    char* mensaje_cifrado = malloc(256);
    char* mensaje_descifrado = malloc(256);

    if(verificar_longitud(mensaje, llave)) {

        mensaje_cifrado = cifrar(mensaje, llave, alfabeto);

        printf("El mensaje cifrado es: %s", mensaje_cifrado);

        mensaje_descifrado = descifrar(mensaje_cifrado, llave, alfabeto,
         strlen(mensaje_cifrado));
    
        printf("\nEl mensaje descifrado es: %s\n", mensaje_descifrado);

    } else {

        if(obtener_menor(mensaje, llave) == strlen(mensaje)) {

            char* mensaje_aum = aumentar_caracteres(mensaje, obtener_diferencia(mensaje, llave));

            mensaje_cifrado = cifrar(mensaje_aum, llave, alfabeto);
        
            printf("El mensaje cifrado es: %s", mensaje_cifrado);
        
            mensaje_descifrado = descifrar(mensaje_cifrado, llave, alfabeto, 
            strlen(mensaje_cifrado) / 2);    
            printf("\nEl mensaje descifrado es: %s\n", mensaje_descifrado);

        } else {

            char* llave_aum = aumentar_caracteres(llave, obtener_diferencia(mensaje, llave));

            mensaje_cifrado = cifrar(mensaje, llave_aum, alfabeto);
        
            printf("El mensaje cifrado es: %s", mensaje_cifrado);
        
            mensaje_descifrado = descifrar(mensaje_cifrado, llave_aum, alfabeto,
             strlen(mensaje_cifrado));
        
            printf("\nEl mensaje descifrado es: %s\n", mensaje_descifrado);
        
        }

    }

    liberar_memoria(mensaje_cifrado);
    liberar_memoria(mensaje_descifrado);

}

int main() {

    char mensaje[256], llave[256];

    char *alfabeto = malloc(26);

    llenar_array(alfabeto);

    printf("Escriba un mensaje [solo letras y sin espacios]:: ");
    if (fgets(mensaje, 256, stdin)) mensaje[strcspn(mensaje, "\n")] = 0;   
   

    printf("Escriba una llave [solo letras y sin espacios]: ");
    if (fgets(llave, 256, stdin)) llave[strcspn(llave, "\n")] = 0;  
   

    verificar(mensaje, llave, alfabeto);

    liberar_memoria(alfabeto);

    return 0;

}