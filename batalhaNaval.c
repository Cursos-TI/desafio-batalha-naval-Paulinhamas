#include <stdio.h>

#define TAM 10         // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3    // Cada navio ocupa 3 posições
#define NAVIO 3        // Valor para navios
#define HABILIDADE 5   // Valor para área afetada por habilidade
#define TAM_HAB 5      // Tamanho das matrizes de habilidades (5x5)

// ==================== FUNÇÕES DO TABULEIRO ====================

// Inicializa o tabuleiro com zeros
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

// Exibe o tabuleiro com diferentes símbolos
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");   // Água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");   // Navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");   // Área de habilidade
            else
                printf("? ");   // Outros valores inesperados
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se uma posição está dentro dos limites do tabuleiro
int dentroDoTabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Verifica se a posição está livre
int posicaoLivre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (!dentroDoTabuleiro(linha, coluna))
        return 0;
    return tabuleiro[linha][coluna] == 0;
}

// Posiciona navio horizontalmente
int posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    if (colunaInicial + TAM_NAVIO > TAM) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linha, colunaInicial + i)) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha][colunaInicial + i] = NAVIO;
    return 1;
}

// Posiciona navio verticalmente
int posicionarVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    if (linhaInicial + TAM_NAVIO > TAM) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linhaInicial + i, coluna)) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    return 1;
}

// Posiciona navio diagonal principal
int posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial + TAM_NAVIO > TAM) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linhaInicial + i, colunaInicial + i)) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;
    return 1;
}

// Posiciona navio diagonal secundária
int posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial - (TAM_NAVIO - 1) < 0) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        if (!posicaoLivre(tabuleiro, linhaInicial + i, colunaInicial - i)) return 0;
    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;
    return 1;
}

// ==================== FUNÇÕES DAS HABILIDADES ====================

// Cria matriz de habilidade em forma de cone
void criarMatrizCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = 0;
            int meio = TAM_HAB / 2;
            // Expande o cone conforme a linha aumenta
            if (j >= meio - i && j <= meio + i && i <= meio)
                matriz[i][j] = 1;
        }
    }
}

// Cria matriz de habilidade em forma de cruz
void criarMatrizCruz(int matriz[TAM_HAB][TAM_HAB]) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = (i == meio || j == meio) ? 1 : 0;
        }
    }
}

// Cria matriz de habilidade em forma de octaedro (losango)
void criarMatrizOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    int meio = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            matriz[i][j] = (abs(i - meio) + abs(j - meio) <= meio) ? 1 : 0;
        }
    }
}

// Aplica matriz de habilidade no tabuleiro centrada em (linhaOrigem, colunaOrigem)
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int linhaOrigem, int colunaOrigem) {
    int offset = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (matriz[i][j] == 1) {
                int linha = linhaOrigem + (i - offset);
                int coluna = colunaOrigem + (j - offset);

                if (dentroDoTabuleiro(linha, coluna) && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

// ==================== FUNÇÃO PRINCIPAL ====================

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posiciona 4 navios
    if (!posicionarHorizontal(tabuleiro, 1, 2))
        printf("Erro ao posicionar navio horizontal!\n");
    if (!posicionarVertical(tabuleiro, 5, 6))
        printf("Erro ao posicionar navio vertical!\n");
    if (!posicionarDiagonalPrincipal(tabuleiro, 3, 3))
        printf("Erro ao posicionar navio diagonal principal!\n");
    if (!posicionarDiagonalSecundaria(tabuleiro, 0, 9))
        printf("Erro ao posicionar navio diagonal secundaria!\n");

    // Cria matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    criarMatrizCone(cone);
    criarMatrizCruz(cruz);
    criarMatrizOctaedro(octaedro);

    // Aplica habilidades em posições fixas
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 8);   // Octaedro em (7,8)

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}