#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída.
#include <unistd.h>  // Inclui a biblioteca para a função 'sleep()'.

int main() {
    // Inicia um loop infinito para simular o ciclo do semáforo.
    while (1) {
        // ------------------------------------------------------------------
        // FASE 1: VIA PRINCIPAL (P) VERDE
        // Permite que o tráfego da via principal flua.
        // ------------------------------------------------------------------
        printf("\n============================================\n");
        printf("       FASE 1: FLUXO NA VIA PRINCIPAL\n");
        printf("============================================\n");

        printf("\n- Semáforo para carros da VIA PRINCIPAL: VERDE\n");
        printf("- Semáforo para carros da VIA SECUNDÁRIA: VERMELHO\n");
        // Quando carros na Via Principal se movem, pedestres de ambas as vias esperam.
        printf("- Semáforo para pedestres que atravessam a VIA PRINCIPAL: VERMELHO\n");
        printf("- Semáforo para pedestres que atravessam a VIA SECUNDÁRIA: VERDE\n");
        printf("\n--> Carros da via principal podem seguir ou virar. Pedestres devem esperar.\n");

        for (int i = 45; i > 0; i--) {
            printf("\rTempo para o sinal da via principal fechar: %d segundos ", i);
            fflush(stdout);
            sleep(1);
        }

        // ------------------------------------------------------------------
        // TRANSIÇÃO (AMARELO e ALL-RED CURTO)
        // Intervalo de segurança para limpeza do cruzamento antes de outra fase começar.
        // ------------------------------------------------------------------
        printf("\n\n--- MUDANCA DE SINAL ---\n");
        printf("Semáforo da VIA PRINCIPAL: AMARELO\n");
        sleep(5); // Sinal amarelo por 5 segundos.

        // Período de ALL-RED (vermelho total) curto para segurança dos carros.
        printf("Semáforos de CARROS: VERMELHO em todas as direções (LIMPEZA)\n");
        sleep(2);

        // ------------------------------------------------------------------
        // FASE 2: FASE EXCLUSIVA DE PEDESTRES E VIA SECUNDÁRIA
        // Esta fase é o momento de travessia para pedestres da Via Principal e para carros da Via Secundária.
        // ------------------------------------------------------------------
        printf("\n============================================\n");
        printf(" FASE 2: FLUXO SECUNDÁRIO E PEDESTRES\n");
        printf("============================================\n");

        printf("\n- Semáforo para carros da VIA PRINCIPAL: VERMELHO\n");
        printf("- Semáforo para carros da VIA SECUNDÁRIA: VERDE\n");
        // O semáforo de pedestres da Via Principal fica verde porque todos os carros daquela via estão parados.
        printf("- Semáforo para pedestres que atravessam a VIA PRINCIPAL: VERDE\n");
        printf("- Semáforo para pedestres que atravessam a VIA SECUNDÁRIA: VERMELHO\n");
        printf("\n--> Carros da via secundária podem seguir. Pedestres da via PRINCIPAL podem atravessar.\n");

        for (int i = 30; i > 0; i--) {
            printf("\rTempo para o sinal da via secundária fechar: %d segundos ", i);
            fflush(stdout);
            sleep(1);
        }

        // ------------------------------------------------------------------
        // TRANSIÇÃO PARA O PRÓXIMO CICLO (AMARELO)
        // ------------------------------------------------------------------
        printf("\n\n--- MUDANCA DE SINAL ---\n");
        printf("Semáforo da VIA SECUNDARIA: AMARELO\n");
        sleep(5);

        // O ciclo retorna ao início.
    }

return 0;
}