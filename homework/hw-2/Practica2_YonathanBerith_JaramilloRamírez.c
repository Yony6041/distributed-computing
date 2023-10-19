#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NODES 10
#define MAX_ROUNDS 5
#define TRAITORS 3
#define LOYAL (NODES - TRAITORS)

typedef enum { ATTACK, RETREAT } Plan;

typedef struct {
    Plan plan;
    bool isTraitor;
} Node;

// Enviar el plan desde el nodo emisor al receptor
void sendPlan(Node *sender, Plan *receiver) {
    if (sender->isTraitor) {
        *receiver = rand() % 2 == 0 ? ATTACK : RETREAT; // El traidor envía un plan aleatorio
    } else {
        *receiver = sender->plan; // El leal envía su plan actual
    }
}

// Comprobar si se ha alcanzado un consenso
bool reachConsensus(Plan plans[], int threshold) {
    int attackCount = 0, retreatCount = 0;
    for (int i = 0; i < NODES; i++) {
        if (plans[i] == ATTACK) attackCount++;
        else retreatCount++;
    }
    return (attackCount >= threshold || retreatCount >= threshold);
}

// Determinar el plan de la mayoría
Plan majorityPlan(Plan plans[]) {
    int attackCount = 0, retreatCount = 0;
    for (int i = 0; i < NODES; i++) {
        if (plans[i] == ATTACK) attackCount++;
        else retreatCount++;
    }
    return (attackCount > retreatCount) ? ATTACK : RETREAT;
}

int main() {
    srand(time(NULL));

    Node nodes[NODES];
    Plan currentRoundPlans[NODES];
    int kingIndex = 0;
    int round = 0;
    bool consensusReached = false;

    // Inicializar nodos con planes aleatorios y establecer traidores
    for (int i = 0; i < NODES; i++) {
        nodes[i].plan = rand() % 2 == 0 ? ATTACK : RETREAT;
        nodes[i].isTraitor = (i < TRAITORS);
    }

    printf("\n################### INICIO DE LA SIMULACIÓN ###################\n");

    while (round < MAX_ROUNDS && !consensusReached) {
        // El rey envía el plan a todos los nodos
        for (int i = 0; i < NODES; i++) {
            sendPlan(&nodes[kingIndex], &currentRoundPlans[i]);
        }

        // Comprobar si se ha alcanzado un consenso
        consensusReached = reachConsensus(currentRoundPlans, LOYAL);

        // Imprimir el estado de la ronda actual
        printf("\n------- Ronda %d -------\n", round + 1);
        for (int i = 0; i < NODES; i++) {
            printf("Nodo %d (%s) recibió el plan: %s\n", i, nodes[i].isTraitor ? "Traidor" : "Leal",
                   currentRoundPlans[i] == ATTACK ? "ATACAR" : "RETIRARSE");
        }

        // Seleccionar nuevo rey para la siguiente ronda
        kingIndex = (kingIndex + 1) % NODES;

        // Incrementar la ronda
        round++;
    }

    printf("\n################### FIN DE LA SIMULACIÓN ###################\n");

    // Decisión final
    if (consensusReached) {
        Plan finalPlan = majorityPlan(currentRoundPlans);
        printf("\nSe alcanzó un consenso en %s.\n", finalPlan == ATTACK ? "ATACAR" : "RETIRARSE");
    } else {
        printf("\nSe alcanzaron las rondas máximas. No se logró un consenso.\n");
    }

    return 0;
}
