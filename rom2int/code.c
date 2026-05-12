#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

int converterCharInt( const char c ){
    //printf("Caractere: %c\n", c);
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default:
            printf("ERRO: caractere inválido");
            exit(1);
    }
}

int rom2int(const char *romano) {
   
    int i = 0;
    int resultado = 0;
 
    while (romano[i] != '\0') {
        
        int valorAtual = converterCharInt(romano[i]);
        int valorProximo = 0;
     
        if (romano[i + 1] != '\0') {
            valorProximo = converterCharInt(romano[i + 1]);
        }
        if (valorAtual < valorProximo) {
            resultado -= valorAtual;
        } else {
            resultado += valorAtual;
        }
        i++;
    }
    return resultado;
}

int main()
{
    
    char romano [] = "XIV";
    printf("\n%s -> %d", romano, rom2int(romano));
    
return 0;
}
