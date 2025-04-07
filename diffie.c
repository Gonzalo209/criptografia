#include <stdio.h>
#include <stdlib.h>
//Utilizamos esta biblioteca para poder hacer uso del algoritmo de diffie helman, y usar numeros grandes.
#include <gmp.h> 

//Validamos que el numero que ingresemos no sea mayor a p.
mpz_t* validar_numero(mpz_t p) {
    
    mpz_t* n = malloc(sizeof(mpz_t));
    
    mpz_init(*n);
    
    do {
        
        printf("Ingresa un numero: ");
        mpz_inp_str(*n, stdin, 10);
        
        if(mpz_cmp(*n, p) > 0) printf("Tu numero debe ser menor\n");
        
    } while(mpz_cmp(*n, p) > 0);
    
    return n;
    
}

int main() {
    
    //Declaramos las variables
    mpz_t p, g, llave_publica1, llave_publica2, a, b, llave_privada1, llave_privada2;

    /*
        Explicacion de las variables que use,
        p = un numero primo.
        g = generador.
        a = el numero de la persona que quiere intercambiar su llave.
        b = el numero de la otra persona que quiere intercambiar su llave.
    */

    //Las inicializamos
    mpz_init(p);
    mpz_init(g);
    mpz_init(a);
    mpz_init(b);
    mpz_init(llave_publica1);
    mpz_init(llave_publica2);
    mpz_init(llave_privada1);
    mpz_init(llave_privada2);

    //Leemos los datos
    mpz_inp_str(p, stdin, 10);
    mpz_inp_str(g, stdin, 10);
    
    mpz_set(a, *validar_numero(p));
    mpz_set(b, *validar_numero(p));

    //Realizamos el calculo para obtener las llaves publicas
    mpz_powm(llave_publica1, g, a, p);
    
    mpz_powm(llave_publica2, g, b, p);

    //Imprimimos el valor de las llaves publicas
    gmp_printf("Llave publica 1: %Zd\nLlave publica 2: %Zd\n", llave_publica1, llave_publica2);
    
    //Ahora hacemos el calculo para obtener las llaves privadas    
    mpz_powm(llave_privada1, llave_publica2, a, p);
    
    mpz_powm(llave_privada2, llave_publica1, b, p);

    //Imprimimos su valor
    gmp_printf("Llave privada 1: %Zd\nLlave privada 2: %Zd\n", llave_privada1, llave_privada2);

    //Liberamos la memoria
    mpz_clear(p);
    mpz_clear(g);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(llave_publica1);
    mpz_clear(llave_publica2);
    mpz_clear(llave_privada1);
    mpz_clear(llave_privada2);
    
    return 0;

}