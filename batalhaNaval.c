#include <stdio.h>

#define TAM 10      // Tamanho fixo do tabuleiro (10x10)
#define TAM_NAVIO 3 // Tamanho fixo dos navios (3 posições)

// Função para inicializar o tabuleiro com 0 (representando água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]); // Espaço entre colunas para melhor visualização
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar um navio horizontalmente
int posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    // Verifica se o navio cabe dentro dos limites
    if (colunaInicial + TAM_NAVIO > TAM)
        return 0; // Falha no posicionamento

    // Verifica se há sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][colunaInicial + i] != 0)
            return 0;
    }

    // Posiciona o navio (marca com 3)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][colunaInicial + i] = 3;
    }

    return 1; // Sucesso
}

// Função para posicionar um navio verticalmente
int posicionarNavioVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    // Verifica se o navio cabe dentro dos limites
    if (linhaInicial + TAM_NAVIO > TAM)
        return 0;

    // Verifica se há sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaInicial + i][coluna] != 0)
            return 0;
    }

    // Posiciona o navio (marca com 3)
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaInicial + i][coluna] = 3;
    }

    return 1; // Sucesso
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas iniciais dos navios
    int linhaHorizontal = 2; // Linha do navio horizontal
    int colunaHorizontal = 4; // Coluna inicial do navio horizontal
    int linhaVertical = 5; // Linha inicial do navio vertical
    int colunaVertical = 1; // Coluna do navio vertical

    // Posiciona os navios
    if (!posicionarNavioHorizontal(tabuleiro, linhaHorizontal, colunaHorizontal)) {
        printf("Erro ao posicionar o navio horizontal!\n");
        return 1;
    }

    if (!posicionarNavioVertical(tabuleiro, linhaVertical, colunaVertical)) {
        printf("Erro ao posicionar o navio vertical!\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
