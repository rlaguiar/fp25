#include<stdio.h>
#include<strings.h>

#define NUM_CHAPAS 100
#define TAM_NOME 50
#define NUM_ELEITORES 100

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

// A função recebe um ponteiro (*candidatos) para um array de TAM_NOME caracteres.
int cadastrarChapas(char (*candidatos)[TAM_NOME], char (*vices)[TAM_NOME], int *numChapas)
{
    char op;
    int i=0;
    do{
        printf("entre com o número da chapa: ");
        scanf("%d", &numChapas[i]);
        limparBuffer();

        printf("entre com o nome do candidato: ");
        fgets(candidatos[i], TAM_NOME, stdin);
        candidatos[i][strcspn(candidatos[i], "\n")] = '\0';

        printf("entre com o nome do vice: ");
        fgets(vices[i], TAM_NOME, stdin);
        vices[i][strcspn(vices[i], "\n")] = '\0';

        printf("\ndeseja cadastrar mais chapas? s para sim: ");
        scanf(" %c", &op);
        limparBuffer();
        i++;
    } while(op=='s' && i<100);
    return i;
}

void exibirChapa(char candidato[], char vice[], int num){
    printf("candidato: %s\n", candidato);
    printf("vice: %s\n", vice);
    printf("número da chapa: %d\n\n", num);
}

void imprimirChapas(char candidato[][TAM_NOME],
                    char vices [][TAM_NOME],
                    int numChapas[], int totalChapas)
{
    for(int i=0; i<totalChapas; i++){
        exibirChapa(candidato[i], vices[i], numChapas[i]);
    }
}

int buscarVoto(int numChapas[],
                int num, int totalChapas)
{
    for(int i=0; i<totalChapas; i++){
        if(num==numChapas[i]) return i;
    }
    return -1;
}

void votar(char candidatos[][TAM_NOME],
            char vices[][TAM_NOME],
            int numChapas[], int numVotos[],
            int totalChapas, int *brancos, int *nulos)
{
    int voto;
    imprimirChapas(candidatos, vices,numChapas, totalChapas);
    printf("entre com o número da chapa desejada ou zero para votar em branco: ");
    scanf("%d", &voto);
    limparBuffer();
    if (voto==0) (*brancos)++;
    else {
        int idx = buscarVoto(numChapas, voto, totalChapas);
        if (idx<0) (*nulos)++;
        else numVotos[idx]++;
    }
}

void iniciarVotacao(char candidatos[][TAM_NOME],
            char vices[][TAM_NOME],
            int numChapas[], int numVotos[],
            int totalChapas, int *brancos, int *nulos)
{
    char op;
    puts("INICIANDO VOTAÇÃO!\n\n");
    for(int i=0; i<NUM_ELEITORES; i++){
        votar(candidatos, vices, numChapas,
            numVotos, totalChapas, brancos, nulos);
        printf("continuar votação? s para sim: ");
        scanf(" %c", &op);
        limparBuffer();
        if(op!='s'){
            break;
        }
    }

}

void imprimirBoletimUrna(char candidatos[][TAM_NOME],
            char vices[][TAM_NOME],
            int numChapas[], int numVotos[],
            int totalChapas, int *brancos, int *nulos)
{
    for(int i=0; i<totalChapas; i++){
        puts(candidatos[i]);
        puts(vices[i]);
        printf("número: %d\n",numChapas[i]);
        printf("votos: %d\n\n", numVotos[i]);
    }
    printf("votos em branco: %d\n", *brancos);
    printf("votos nulos: %d\n\n", *nulos);
}

int main(){
    char candidatos[NUM_CHAPAS][TAM_NOME];
    char vices[NUM_CHAPAS][TAM_NOME];
    int numChapas[NUM_CHAPAS];
    int votos[NUM_CHAPAS] = {0};
    int totalChapas = cadastrarChapas(candidatos, vices, numChapas);
    //imprimirChapas(candidatos, vices, numChapas, totalChapas);
    puts("\n");
    int votosBrancos = 0;
    int votosNulos = 0;
    iniciarVotacao(candidatos, vices, numChapas, votos,
        totalChapas, &votosBrancos, &votosNulos);
    imprimirBoletimUrna(candidatos, vices, numChapas, votos,
        totalChapas, &votosBrancos, &votosNulos);
    return 0;
}