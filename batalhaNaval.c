#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3   // Cada navio ocupa 3 posições
#define NAVIO 3       // Valor usado para marcar partes do navio

// Inicializa o tabuleiro preenchendo todas as posições com 0

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro com 0 (água) e 3 (navio)

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


// Verifica se a posição está livre e dentro do tabuleiro

int posicaoLivre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha < 0 linha >= TAM coluna < 0 coluna >= TAM)
    
    return 0; 
    
    if (tabuleiro[linha][coluna] != 0)
    
    return 0; 
    
    return 1;
}

// Posiciona um navio horizontalmente

int posicionarHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    if (colunaInicial + TAM_NAVIO > TAM)
    
    return 0;

    for (int i = 0; i < TAM_NAVIO; i++)
        if (posicaoLivre(tabuleiro, linha, colunaInicial + i))
        
    return 0; 

    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linha][colunaInicial + i] = NAVIO;

    return 1;
}


// Posiciona um navio verticalmente

int posicionarVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    if (linhaInicial + TAM_NAVIO > TAM)
    
    return 0; 
    
    for (int i = 0; i < TAM_NAVIO; i++)
        if (posicaoLivre(tabuleiro, linhaInicial + i, coluna))
        
    return 0;

    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][coluna] = NAVIO;

    return 1;
}


// Posiciona um navio na diagonal principal 

int posicionarDiagonalPrincipal(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial + TAM_NAVIO > TAM)
    
    return 0; 

    for (int i = 0; i < TAM_NAVIO; i++)
        if (posicaoLivre(tabuleiro, linhaInicial + i, colunaInicial + i))
            
    return 0;

    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][colunaInicial + i] = NAVIO;

    return 1;
}

// Posiciona um navio na diagonal secundária

int posicionarDiagonalSecundaria(int tabuleiro[TAM][TAM], int linhaInicial, int colunaInicial) {
    if (linhaInicial + TAM_NAVIO > TAM || colunaInicial - (TAM_NAVIO - 1) < 0)
        
    return 0; 

    for (int i = 0; i < TAM_NAVIO; i++)
        if (posicaoLivre(tabuleiro, linhaInicial + i, colunaInicial - i))
            
    return 0;

    for (int i = 0; i < TAM_NAVIO; i++)
        tabuleiro[linhaInicial + i][colunaInicial - i] = NAVIO;

    return 1;
}

// Função principal

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // ==== Posiciona os 4 navios ====
    // 1 horizontal, 1 vertical, 2 diagonais

    // Navio horizontal em (linha=1, coluna inicial=2)
    if (posicionarHorizontal(tabuleiro, 1, 2))
        printf("Erro ao posicionar navio horizontal!\n");

    // Navio vertical em (linha inicial=5, coluna=6)
    if (posicionarVertical(tabuleiro, 5, 6))
        printf("Erro ao posicionar navio vertical!\n");

    // Navio diagonal principal começando em (linha=3, coluna=3)
    if (posicionarDiagonalPrincipal(tabuleiro, 3, 3))
        printf("Erro ao posicionar navio diagonal principal!\n");

    // Navio diagonal secundária começando em (linha=0, coluna=9)
    if (posicionarDiagonalSecundaria(tabuleiro, 0, 9))
        printf("Erro ao posicionar navio diagonal secundaria!\n");

    // ==== Exibe o resultado final ====
    exibirTabuleiro(tabuleiro);

    return 0;
}