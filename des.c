#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sbox[8][4][16] = {
    
    {   {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
    },
	{   {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
    },
	{   {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
    },
	{   {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
    },
	{   {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
    },
	{	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
    },
	{	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
    },
	{	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Tablas del algoritmo DES
int initial_perm[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

int final_perm[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

int exp_d[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

int per[32] = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

int keyp[56] = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};

int key_comp[48] = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};

int shift_table[16] = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

const char mapa_hex[16][5] = {
    "0000", "0001", "0010", "0011",
    "0100", "0101", "0110", "0111",
    "1000", "1001", "1010", "1011",
    "1100", "1101", "1110", "1111"
};

char* hex_a_binario(char* hex) {
    char* binario = malloc(strlen(hex) * 4 + 1);
    binario[0] = '\0';
    for (int i = 0; hex[i]; i++) {
        int valor = (hex[i] >= '0' && hex[i] <= '9') ? hex[i] - '0' : hex[i] - 'A' + 10;
        strcat(binario, mapa_hex[valor]);
    }
    return binario;
}

char* binario_a_hex(char* bin) {
    int longitud = strlen(bin);
    char* hex = malloc(longitud / 4 + 1);
    for (int i = 0; i < longitud; i += 4) {
        int valor = 0;
        for (int j = 0; j < 4; j++)
            valor = valor * 2 + (bin[i + j] - '0');
        hex[i / 4] = (valor < 10) ? valor + '0' : valor - 10 + 'A';
    }
    hex[longitud / 4] = '\0';
    return hex;
}

char* permutar(char* bits, int* tabla, int tamaño) {
    char* resultado = malloc(tamaño + 1);
    for (int i = 0; i < tamaño; i++)
        resultado[i] = bits[tabla[i] - 1];
    resultado[tamaño] = '\0';
    return resultado;
}

char* rotar_izquierda(char* k, int desplazamientos) {
    char* resultado = malloc(29);
    strncpy(resultado, k + desplazamientos, 28 - desplazamientos);
    strncpy(resultado + 28 - desplazamientos, k, desplazamientos);
    resultado[28] = '\0';
    return resultado;
}

char* xor(char* a, char* b) {
    int len = strlen(a);
    char* resultado = malloc(len + 1);
    for (int i = 0; i < len; i++)
        resultado[i] = (a[i] == b[i]) ? '0' : '1';
    resultado[len] = '\0';
    return resultado;
}

int binario_a_decimal(char* s) {
    int val = 0;
    for (int i = 0; s[i]; i++)
        val = val * 2 + (s[i] - '0');
    return val;
}

char* decimal_a_binario(int num) {
    char* bin = malloc(5);
    for (int i = 3; i >= 0; i--) {
        bin[i] = (num % 2) + '0';
        num /= 2;
    }
    bin[4] = '\0';
    return bin;
}

// Función f
char* funcion_f(char* mitad_derecha, char* clave_redonda) {
    char* mitad_expandida = permutar(mitad_derecha, exp_d, 48);
    char* mitad_xor = xor(mitad_expandida, clave_redonda);
    free(mitad_expandida);

    char* salida = malloc(33);
    salida[0] = '\0';

    for (int i = 0; i < 8; i++) {
        char fila[3] = {mitad_xor[i * 6], mitad_xor[i * 6 + 5], '\0'};
        char columna[5] = {mitad_xor[i * 6 + 1], mitad_xor[i * 6 + 2], mitad_xor[i * 6 + 3], mitad_xor[i * 6 + 4], '\0'};

        int f = binario_a_decimal(fila);
        int c = binario_a_decimal(columna);
        int valor = sbox[i][f][c];

        char* bin = decimal_a_binario(valor);
        strcat(salida, bin);
        free(bin);
    }

    free(mitad_xor);

    char* resultado = permutar(salida, per, 32);
    free(salida);
    return resultado;
}

/*Generamos las claves*/
void generar_claves(char* clave, char rkb[16][49], char rk[16][13]) {

    char* clave_bin = hex_a_binario(clave);
    char* clave_permutada = permutar(clave_bin, keyp, 56);  
    free(clave_bin);

    char C[17][29], D[17][29];
    strncpy(C[0], clave_permutada, 28); C[0][28] = '\0';
    strncpy(D[0], clave_permutada + 28, 28); D[0][28] = '\0';
    free(clave_permutada);

    for (int i = 0; i < 16; i++) {
        char* tmpC = rotar_izquierda(C[i], shift_table[i]);  // Cambio aquí
        strcpy(C[i + 1], tmpC);
        free(tmpC);

        char* tmpD = rotar_izquierda(D[i], shift_table[i]);  // Cambio aquí
        strcpy(D[i + 1], tmpD);
        free(tmpD);

        char CD[57];
        snprintf(CD, sizeof(CD), "%s%s", C[i + 1], D[i + 1]);

        char* clave_round = permutar(CD, key_comp, 48); 
        strcpy(rkb[i], clave_round);
        strcpy(rk[i], binario_a_hex(clave_round));
        free(clave_round);
    }
}

// Función de cifrado
char* cifrar(char* texto_plano, char rkb[16][49], char rk[16][13]) {
    char* binario = hex_a_binario(texto_plano);
    char* texto_permutado = permutar(binario, initial_perm, 64);
    free(binario);

    char L[17][33], R[17][33];
    strncpy(L[0], texto_permutado, 32); L[0][32] = '\0';
    strncpy(R[0], texto_permutado + 32, 32); R[0][32] = '\0';
    free(texto_permutado);

    for (int i = 0; i < 16; i++) {
        strcpy(L[i + 1], R[i]);
        char* f_out = funcion_f(R[i], rkb[i]);
        char* resultado = xor(L[i], f_out);
        strcpy(R[i + 1], resultado);
        free(f_out);
        free(resultado);
    }

    char combinado[65];
    snprintf(combinado, sizeof(combinado), "%s%s", R[16], L[16]);
    char* texto_cifrado = permutar(combinado, final_perm, 64);
    char* resultado = binario_a_hex(texto_cifrado);
    free(texto_cifrado);
    return resultado;
}

int main() {
    char texto_plano[] = "123456ABCD132536";
    char clave[] = "AABB09182736CCDD";

    char rkb[16][49]; // Claves redondas en binario
    char rk[16][13];  // Claves redondas en hexadecimal

    generar_claves(clave, rkb, rk);

    printf("CIFRADO:\n");
    char* cifrado = cifrar(texto_plano, rkb, rk);
    printf("Texto Cifrado: %s\n", cifrado);

    // Invertir claves para descifrado
    for (int i = 0; i < 8; i++) {
        char temp[49];
        strcpy(temp, rkb[i]);
        strcpy(rkb[i], rkb[15 - i]);
        strcpy(rkb[15 - i], temp);

        char temp_hex[13];
        strcpy(temp_hex, rk[i]);
        strcpy(rk[i], rk[15 - i]);
        strcpy(rk[15 - i], temp_hex);
    }

    printf("\nDESCIFRADO:\n");
    char* texto_descifrado = cifrar(cifrado, rkb, rk);
    printf("Texto Descifrado: %s\n", texto_descifrado);

    free(cifrado);
    free(texto_descifrado);

    return 0;
}
