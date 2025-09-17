#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NUM_CARTAS 2

typedef struct { //estruturação em ponteiros para declarar as variaveis das cartas
    char estado[3],codigo[4],cidade[50];
    unsigned int populacao; 
    unsigned int pib;
    int pontos_turisticos;
    float area;
    float DensidadeDemografica,PIBpercapita,SuperPower;
} Cartas; 

void calcular_atributos(Cartas* carta) { //função para calcular os atributos derivados
    
    float area_divisor = (carta->area > 0) ? carta->area : 1;
    carta->DensidadeDemografica = (float)carta->populacao / area_divisor;
    
    float pop_divisor = (carta->populacao > 0) ? (float)carta->populacao : 1.0f;
    carta->PIBpercapita = (float)carta->pib / pop_divisor;
    
    float densidade_divisor = (carta->DensidadeDemografica != 0) ? carta->DensidadeDemografica : 1;
    carta->SuperPower = (carta->pib + carta->populacao + (carta->pontos_turisticos*1000) + carta->area + carta->DensidadeDemografica + (-1.0/densidade_divisor))/6.0;

}

void menu_atributos_control(int atributo_repetido) {
    printf("\n--- Escolha um Atributo ---\n");
    char nomes_atributos[7][50] = {"Populacao", "Area (km2)", "PIB (R$)", "Pontos Turisticos", "Densidade Demografica (menor vence)", "PIB per capita", "SuperPower"};
    for (int i = 1; i <= 7; i++) {
        if (i == atributo_repetido) {
            printf(" [%d] %s [ESCOLHIDO]\n", i, nomes_atributos[i-1]);
        } else {
            printf(" [%d] %s\n", i, nomes_atributos[i-1]);
        }}
} //menu dinâmico utilizando array para apontar e remover a opção já escolhida

void exibindo_carta(Cartas* carta) {
    printf("\n--------------------------\n");
    printf(" Cidade: %s - %s\n", carta->cidade, carta->estado);
    printf("--------------------------\n");
    printf(" [1] Populacao: %u\n", carta->populacao);
    printf(" [2] Area (km2): %.2f\n", carta->area);
    printf(" [3] PIB (R$): %u\n", carta->pib);
    printf(" [4] Pontos Turisticos: %d\n", carta->pontos_turisticos);
    printf(" [5] Densidade Demografica: %2.f\n", carta->DensidadeDemografica);
    printf(" [6] PIB per capita: %2.f\n", carta->PIBpercapita);
    printf("--------------------------\n");
} //função de exibição que será usada durante a execução do game.

float atributos_selecionados(Cartas* carta, int atributo) {
    switch (atributo) {
        case 1:
            return (float)carta->populacao; 
        case 2:
            return carta->area;
        case 3:
            return (float)carta->pib;
        case 4:
            return (float)(carta->pontos_turisticos*1000);
        case 5:
            return -(carta->DensidadeDemografica);
        case 6:
            return carta->PIBpercapita;
        default:
            return 0.0f;
    }
}


int main() { //inicio da função principal

    Cartas Baralho[NUM_CARTAS];
    strcpy(Baralho[0].estado, "RS");
    strcpy(Baralho[0].codigo, "001");
    strcpy(Baralho[0].cidade, "Soledade");
    Baralho[0].populacao = 30000;
    Baralho[0].area = 1215.0;
    Baralho[0].pib = 1400000000;
   Baralho[0].pontos_turisticos = 5;

    
    strcpy(Baralho[1].estado, "SC");
    strcpy(Baralho[1].codigo, "002");
    strcpy(Baralho[1].cidade, "Pomerode");
    Baralho[1].populacao = 30000;
    Baralho[1].area = 200.0;
    Baralho[1].pib = 280600000;
    Baralho[1].pontos_turisticos = 5; //armazenanmento dos dados das cartas

      for (int i = 0; i < NUM_CARTAS; i++) {
        calcular_atributos(&Baralho[i]);
    }//função para calcular os atributos

    int menu, player, cpu, atributo1, atributo2; //variaveis

    srand(time(0));
    printf("Bem-vindo ao Super Trunfo!\n");
    printf("Escolha seu destino:\n");
    printf("1 - duelar\n");
    printf("2 - correr\n");
    scanf("%d", &menu);
    switch (menu) {
        case 1:
            printf("HORA DO DUELO!\n");
            break;
        case 2:
            printf("Voce nunca foi digno!\n");
            return 0;
        default:
            printf("invalido, escolha 1 ou 2.\n");
            return 0;
    };

    cpu = rand() % NUM_CARTAS;
    player = rand() % NUM_CARTAS;
    
    while(cpu == player) { //evitar que a mesma carta seja repetida
        cpu = rand() % NUM_CARTAS;
    }

    printf("Seu card %s\n",Baralho[player].cidade);
    exibindo_carta(&Baralho[player]);


    printf("escolha o primeiro atributo para o duelo: 1 - 6\n");
    scanf("%d", &atributo1);
    printf("escolha seu segundo atributo(nao podera ser o mesmo)\n");
    scanf("%d",&atributo2);
    while (atributo1 == atributo2) {
        printf("Nao escolha o mesmo atributo!\n Digite sua nova escolha");
        scanf("%d", &atributo2);
    }; 

    float escolha1_player = atributos_selecionados(&Baralho[player], atributo1);
    float escolha2_player = atributos_selecionados(&Baralho[player], atributo2);
    float atributo_player = escolha1_player + escolha2_player;

    float escolha1_cpu = atributos_selecionados(&Baralho[cpu], atributo1);
    float escolha2_cpu = atributos_selecionados(&Baralho[cpu], atributo2);
    float atributo_cpu = escolha1_cpu + escolha2_cpu;

    char nomes_atributos[6][50] = {"Populacao", "Area (km2)", "PIB (R$)", "Pontos Turisticos", "Densidade Demografica", "PIB per capita",};

    printf("--------------------------\n");
    printf("HORA DO DUELO!\n");
    printf("--------------------------\n");
    printf("  Sua carta: %s\n", Baralho[player].cidade);
    printf("  Carta da CPU: %s\n", Baralho[cpu].cidade);
    printf("--------------------------\n");
    printf("Primeiro Atributo escolhido %s : %.2f\n",nomes_atributos[atributo1-1], escolha1_player);
    printf("Segundo atributo escohido %s : %.2f\n",nomes_atributos[atributo2-1], escolha2_player);
    printf("--------------------------\n");
    printf("Primeiro atributo do seu adversario %s :%.2f\n",nomes_atributos[atributo1-1], escolha1_cpu);
    printf("Primeiro atributo do seu adversario %s :%.2f\n",nomes_atributos[atributo2-1], escolha2_cpu);
    printf("--------------------------\n");
    if (atributo_player>atributo_cpu){
        printf("venceu!\n");
    } else if (atributo_player<atributo_cpu){
        printf("Esta derrotado!\n");
    } else { printf("houve um empate, INVOQUEM SEUS PODERES\n");
       printf("Seu SuperPower: %.2f\n | SuperPower da CPU: %.2f\n", Baralho[player].SuperPower, Baralho[cpu].SuperPower);
       if (Baralho[player].SuperPower > Baralho[cpu].SuperPower) {
            printf("--------------------------\n");
            printf("Finalmente voce venceu!\n");
        } else {
            printf("--------------------------\n");
            printf("Eu sou inevitavel!\n");
        }
    };
   return 0;
} //apresentou crash ao tentar usar no CMD tradicional do Windows, possivelmente erro com compiladores, várias outra versões tiveram o mesmo problema!