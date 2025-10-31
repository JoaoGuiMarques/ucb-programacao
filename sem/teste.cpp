#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep()

// Estados possíveis dos semáforos
#define VERMELHO 0
#define VERDE 1
#define AMARELO 2

// Tempo de cada fase (em segundos)
#define TEMPO_VERDE_P 20
#define TEMPO_AMARELO 3
#define TEMPO_VERDE_S 20
#define TEMPO_PEDESTRE 5
#define TEMPO_MAX_FECHADO_P 60

// Estrutura para semáforo
typedef struct {
    int carro;     // 0 vermelho, 1 verde, 2 amarelo
    int pedestre;  // 0 vermelho, 1 verde
} Semaforo;

// Função para imprimir estado
void mostrarEstado(Semaforo P, Semaforo S) {
    printf("\n=== ESTADO ATUAL ===\n");
    printf("Via P: Carro[%s] | Pedestre[%s]\n",
           P.carro == VERDE ? "VERDE" :
           P.carro == AMARELO ? "AMARELO" : "VERMELHO",
           P.pedestre == VERDE ? "VERDE" : "VERMELHO");
    printf("Via S: Carro[%s] | Pedestre[%s]\n",
           S.carro == VERDE ? "VERDE" :
           S.carro == AMARELO ? "AMARELO" : "VERMELHO",
           S.pedestre == VERDE ? "VERDE" : "VERMELHO");
}

// Função para simular tempo com atualização
void esperarSegundos(int segundos) {
    for (int i = segundos; i > 0; i--) {
        printf("Tempo restante: %d segundos\r", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

int main() {
    Semaforo viaP = {VERDE, VERMELHO};
    Semaforo viaS = {VERMELHO, VERMELHO};

    int botao[4] = {0, 0, 0, 0}; // 4 botões de pedestre
    int tempoFechadaP = 0;

    while (1) {
        // ======== FASE 1: Via P Verde ========
        viaP.carro = VERDE; viaP.pedestre = VERMELHO;
        viaS.carro = VERMELHO; viaS.pedestre = VERMELHO;
        mostrarEstado(viaP, viaS);

        for (int t = 0; t < TEMPO_VERDE_P; t++) {
            // Simular botões
            printf("Digite numero do botao pressionado (0 nenhum): ");
            int entrada;
            scanf("%d", &entrada);
            if (entrada >= 1 && entrada <= 4) {
                botao[entrada - 1] = 1;
            }
            sleep(1);
        }
        tempoFechadaP = 0; // zera contador quando via P está verde

        // ======== FASE 2: Via P Amarelo ========
        viaP.carro = AMARELO; viaP.pedestre = VERMELHO;
        mostrarEstado(viaP, viaS);
        esperarSegundos(TEMPO_AMARELO);

        // ======== FASE 3: Via S Verde ========
        viaP.carro = VERMELHO; viaP.pedestre = VERMELHO;
        viaS.carro = VERDE; viaS.pedestre = VERMELHO;
        mostrarEstado(viaP, viaS);

        for (int t = 0; t < TEMPO_VERDE_S; t++) {
            tempoFechadaP++;
            // Se pedestre solicitou na via P (botões 1 ou 2)
            if ((botao[0] || botao[1]) && t == 0) {
                // Dá verde para pedestres
                viaP.pedestre = VERDE;
                mostrarEstado(viaP, viaS);
                esperarSegundos(TEMPO_PEDESTRE);
                viaP.pedestre = VERMELHO;
                botao[0] = botao[1] = 0;
            }

            if (tempoFechadaP >= TEMPO_MAX_FECHADO_P) break; // garante limite
            sleep(1);
        }

        // ======== FASE 4: Via S Amarelo ========
        viaS.carro = AMARELO; viaS.pedestre = VERMELHO;
        mostrarEstado(viaP, viaS);
        esperarSegundos(TEMPO_AMARELO);

        // ======== PEDESTRE na via S se solicitado ========
        if (botao[2] || botao[3]) {
            viaS.carro = VERMELHO;
            viaS.pedestre = VERDE;
            mostrarEstado(viaP, viaS);
            esperarSegundos(TEMPO_PEDESTRE);
            viaS.pedestre = VERMELHO;
            botao[2] = botao[3] = 0;
        }
    }

    return 0;
}
