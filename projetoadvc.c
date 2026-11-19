#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[50];
    int tentar;
} jogador;

void menureq() {
    printf("----- MENU -----\n");
    printf("1 - Jogar (humano adivinha)\n");
    printf("2 - Modo IA (computador adivinha)\n");
    printf("3 - Ver ranking\n");
    printf("0 - Sair\n");
}

void regisRank(char nome[], int tentativas) {

    FILE *arquivo = fopen("ranking.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s %d\n", nome, tentativas);

    fclose(arquivo);
}

void johuman() {
    int chute;
    int quant = 1;
    int ianuma;
    int acertou = 0;
    int dif;
    int max;
    int limita;

    char nome[50];

    printf("DIGITE O NIVEL DE DIFICULDADE : (1) = facil, (2) = normal, (3) = dificil\n");
    scanf("%d", &dif);

    srand(time(NULL));

    switch (dif){
    case 1:
        max = 100;
        limita = 7;
        break;
    case 2:
        max = 1000;
        limita = 12;
        break;
    case 3:
        max = 10000;
        limita = 16;
        break;
    }

    ianuma = rand() % max + 1;

    while (acertou == 0){
        printf("TENTE UM NUMERO : ");
        scanf("%d", &chute);

        if (chute == ianuma) {
            printf("PARABENS HUMANO, VOCE ACERTOU!!!\n");
            acertou++;

            printf("DIGITE SEU NOME : ");
            scanf("%49s", nome);

            regisRank(nome, quant);
        }
        else if (chute > ianuma) {
            printf("TENTE UM NUMERO MENOR\n");
            quant++;
        }
        else{
            printf("TENTE UM NUMERO MAIOR\n");
            quant++;
        }
    if (quant == limita) {
        printf("O NUMERO ERA %d\n", ianuma);
        break;
    }
    }
}


void jorobo() {
    char correto;
    int inicio = 1;
    int fim = 1000;
    int chutea;
    int tent = 0;

    printf("PENSE EM UM NUMERO DE 1 A 1000.\n");

    while (tent < 10) {

        chutea = (inicio + fim) / 2;
        tent++;

        printf("\nO NUMERO ESCOLHIDO FOI %d\n", chutea);
        printf("SE ACERTEI DIGITE (=), SE MENOR (<), SE MAIOR (>): ");

        scanf(" %c", &correto);

        if (correto == '=') {
            printf("GANHEI HAHAHA\n");
            printf("TENTEI APENAS %d VEZES!\n", tent);
            return;
        }

        if (correto == '<') {
            fim = chutea - 1;
        }
        else if (correto == '>') {
            inicio = chutea + 1;
        }
    }
    printf("NAO CONSEGUI ACERTAR EM 10 TENTATIVAS!\n");
}

void mosRank() {

    jogador jogadores[100];
    jogador temp;

    int quantidade = 0;

    FILE *arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL) {
        printf("Ranking vazio!\n");
        return;
    }

    while (quantidade < 100 &&
           fscanf(arquivo, "%49s %d",
                  jogadores[quantidade].nome,
                  &jogadores[quantidade].tentar) == 2) {

        quantidade++;
    }

    fclose(arquivo);

    for (int i = 0; i < quantidade - 1; i++) {

        for (int j = i + 1; j < quantidade; j++) {

            if (jogadores[i].tentar > jogadores[j].tentar) {

                temp = jogadores[i];
                jogadores[i] = jogadores[j];
                jogadores[j] = temp;

            }
        }
    }

    printf("= = = RANKING = = =\n");

    for (int i = 0; i < quantidade; i++) {

        printf("%d - Jogador: %s | Tentativas: %d\n",
               i + 1,
               jogadores[i].nome,
               jogadores[i].tentar);
    }
}


int main() {
    int menu;
    menureq();

    scanf("%d", &menu);

    switch (menu){
    case 1:
        johuman(); break;
    case 2:
        jorobo(); break;
    case 3:
        mosRank(); break;
    
    default:
        break;
    }

    return 0;
}