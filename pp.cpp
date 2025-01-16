#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>			
#define MAX_RODADAS 20
#define MAX_JOGADORES 2
#define ARQUIVO_JOGO "jogo_salvo.dat"

typedef struct {
    char nome[50];
    int pontuacoes[20]; // -1 para inutilizada, 0 para não usada, >0 para usada
    int totalPontos;
    int bonus;
} Jogador;

typedef struct {
    Jogador jogadores[MAX_JOGADORES];
    int rodadaAtual;
    int dados[5];
    int reservados[5];
} Jogo;

// Funções de inicialização
void exibirAutores() {
    printf("----------------------------------------------------\n");
    printf("  Jogo de Dados                                     \n");
    printf("  Desenvolvido por: JOANA TEIXEIRA                  \n");
    printf("----------------------------------------------------\n");
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
}

void exibirRegras() {
    printf("\n--- Regras do Jogo ---\n");
    printf("1. Cada jogador tem 20 turnos para pontuar.\n");
    printf("2. Em cada turno, pode lançar até 3 vezes 5 dados.\n");
    printf("3. Pode reservar dados e relançar os restantes.\n");
    printf("4. A pontuação é calculada com base nos números NÃO visíveis nos dados.\n");
    printf("5. Complete grupos de pontuações para ganhar bónus!\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getchar();
}

void inicializarJogo(Jogo *jogo) {
    printf("\n--- Novo Jogo ---\n");
    jogo->rodadaAtual = 1;
    for (int i = 0; i < MAX_JOGADORES; i++) {
        printf("Digite o nome do jogador %d: ", i + 1);
        scanf(" %[^\n]", jogo->jogadores[i].nome);
        for (int j = 0; j < 20; j++) {
            jogo->jogadores[i].pontuacoes[j] = 0; // Todas pontuações começam disponíveis
        }
        jogo->jogadores[i].totalPontos = 0;
        jogo->jogadores[i].bonus = 0;
    }
}

// Funções para gravação e carregamento
void salvarJogo(Jogo *jogo) {
    FILE *arquivo = fopen(ARQUIVO_JOGO, "wb");
    if (arquivo == NULL) {
        printf("Erro ao salvar o jogo.\n");
        return;
    }
    fwrite(jogo, sizeof(Jogo), 1, arquivo);
    fclose(arquivo);
    printf("Jogo salvo com sucesso.\n");
}

int carregarJogo(Jogo *jogo) {
    FILE *arquivo = fopen(ARQUIVO_JOGO, "rb");
    if (arquivo == NULL) {
        printf("Nenhum jogo salvo encontrado.\n");
        return 0;
    }
    fread(jogo, sizeof(Jogo), 1, arquivo);
    fclose(arquivo);
    printf("Jogo carregado com sucesso.\n");
    return 1;
}

// Lançamento e exibição dos dados
void lancarDados(int dados[], int reservados[]) {
    for (int i = 0; i < 5; i++) {
        if (!reservados[i]) {
            dados[i] = (rand() % 6) + 1;
        }
    }
}

void mostrarDados(int dados[], int reservados[]) {
    printf("Dados: ");
    for (int i = 0; i < 5; i++) {
        if (reservados[i]) {
            printf("[%d] ", dados[i]); // Dados reservados
        } else {
            printf("%d ", dados[i]); // Dados normais
        }
    }
    printf("\n");
}

// Calcula pontuação baseada nos números não visíveis
int calcularPontuacao(int dados[]) {
    int visiveis[6] = {0};
    for (int i = 0; i < 5; i++) {
        visiveis[dados[i] - 1] = 1;
    }
    int pontuacao = 0;
    for (int i = 0; i < 6; i++) {
        if (!visiveis[i]) {
            pontuacao += i + 1;
        }
    }
    return pontuacao;
}

// Turno do jogador
void jogarTurno(Jogo *jogo, Jogador *jogador) {
    int lancamentos = 0;
    int pontuacaoAtual;

    for (int i = 0; i < 5; i++) {
        jogo->reservados[i] = 0;
    }

    while (lancamentos < 3) {
        lancarDados(jogo->dados, jogo->reservados);
        mostrarDados(jogo->dados, jogo->reservados);

        pontuacaoAtual = calcularPontuacao(jogo->dados);
        printf("Pontuação atual: %d\n", pontuacaoAtual);

        if (lancamentos < 2) {
            char opcao;
            printf("Deseja (R)eservar dados, (L)ançar novamente, ou (T)erminar turno? ");
            scanf(" %c", &opcao);

            if (opcao == 'T' || opcao == 't') {
                break;
            } else if (opcao == 'R' || opcao == 'r') {
                printf("Digite 1 para reservar ou 0 para não reservar cada dado:\n");
                for (int i = 0; i < 5; i++) {
                    printf("Dado %d (%d): ", i + 1, jogo->dados[i]);
                    scanf("%d", &jogo->reservados[i]);
                }
            }
        }
        lancamentos++;
    }

    printf("Escolha uma pontuação para marcar ou inutilizar (1-20): ");
    int escolha;
    scanf("%d", &escolha);

    if (jogador->pontuacoes[escolha - 1] == 0) {
        jogador->pontuacoes[escolha - 1] = pontuacaoAtual;
        jogador->totalPontos += pontuacaoAtual;
    } else {
        printf("Essa pontuação já foi usada. Será inutilizada.\n");
        jogador->pontuacoes[escolha - 1] = -1;
    }

    salvarJogo(jogo);
}

// Verificação de bónus
void verificarBonus(Jogador *jogador) {
    int grupos[3] = {0, 0, 0};
    for (int i = 0; i < 20; i++) {
        if (jogador->pontuacoes[i] > 0) {
            if (i < 5) grupos[0]++;
            else if (i < 15) grupos[1]++;
            else grupos[2]++;
        }
    }
    jogador->bonus = (grupos[0] == 5) * 50 + (grupos[1] == 10) * 50 + (grupos[2] == 5) * 50;
    jogador->totalPontos += jogador->bonus;
}

// Exibição do resultado
void exibirResultado(Jogo *jogo) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        verificarBonus(&jogo->jogadores[i]);
        printf("Jogador: %s, Pontos: %d, Bónus: %d\n",
               jogo->jogadores[i].nome, jogo->jogadores[i].totalPontos, jogo->jogadores[i].bonus);
    }

    if (jogo->jogadores[0].totalPontos > jogo->jogadores[1].totalPontos) {
        printf("Vencedor: %s\n", jogo->jogadores[0].nome);
    } else if (jogo->jogadores[1].totalPontos > jogo->jogadores[0].totalPontos) {
        printf("Vencedor: %s\n", jogo->jogadores[1].nome);
    } else {
        printf("Empate!\n");
    }
}

int main() {
    srand(time(NULL));
    Jogo jogo;
    int opcao;

    exibirAutores();

    while (1) {
        printf("\n--- Menu Principal ---\n");
        printf("1. Apresentar as regras do jogo\n");
        printf("2. Começar um novo jogo\n");
        printf("3. Carregar jogo salvo\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirRegras();
        } else if (opcao == 2) {
            inicializarJogo(&jogo);
            break;
        } else if (opcao == 3) {
            if (!carregarJogo(&jogo)) {
                continue;
            }
            break;
        } else if (opcao == 4) {
            printf("Saindo do jogo...\n");
            return 0;
        } else {
            printf("Opção inválida!\n");
        }
    }

    while (jogo.rodadaAtual <= MAX_RODADAS) {
        printf("\nRodada %d\n", jogo.rodadaAtual);
        for (int i = 0; i < MAX_JOGADORES; i++) {
            printf("\nTurno do jogador %s\n", jogo.jogadores[i].nome);
            jogarTurno(&jogo, &jogo.jogadores[i]);
        }
        jogo.rodadaAtual++;
    }

    exibirResultado(&jogo);
    return 0;
}
