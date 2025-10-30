#include <stdio.h>
#include <stdlib.h>

// Definição do tabuleiro 8x8
char board[8][8];

// Função para inicializar o tabuleiro
void initializeBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = '.';
        }
    }
}

// Função para imprimir o tabuleiro
void printBoard() {
    printf("  0 1 2 3 4 5 6 7\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// MÓDULO NOVATO: Movimentos lineares com for, while, do-while
// Torre: Movimentos horizontais e verticais
void moveTorre(int row, int col) {
    board[row][col] = 'T';  // Posiciona a Torre
    
    // Movimentos horizontais (linha fixa, colunas variam) - usando for
    for (int j = col - 1; j >= 0; j--) {
        board[row][j] = '*';  // Esquerda
    }
    for (int j = col + 1; j < 8; j++) {
        board[row][j] = '*';  // Direita
    }
    
    // Movimentos verticais (coluna fixa, linhas variam) - usando while
    int i = row - 1;
    while (i >= 0) {
        board[i][col] = '*';  // Cima
        i--;
    }
    i = row + 1;
    while (i < 8) {
        board[i][col] = '*';  // Baixo
        i++;
    }
}

// Bispo: Movimentos diagonais
void moveBispo(int row, int col) {
    board[row][col] = 'B';  // Posiciona o Bispo
    
    // Diagonal principal (cima-esquerda e baixo-direita) - usando do-while
    int i = row - 1, j = col - 1;
    do {
        if (i >= 0 && j >= 0) board[i][j] = '*';
        i--; j--;
    } while (i >= 0 && j >= 0);
    
    i = row + 1; j = col + 1;
    do {
        if (i < 8 && j < 8) board[i][j] = '*';
        i++; j++;
    } while (i < 8 && j < 8);
    
    // Diagonal secundária (cima-direita e baixo-esquerda) - usando for
    for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
        board[i][j] = '*';
    }
    for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
        board[i][j] = '*';
    }
}

// Rainha: Combina movimentos de Torre e Bispo
void moveRainha(int row, int col) {
    board[row][col] = 'Q';  // Posiciona a Rainha
    
    // Movimentos horizontais e verticais (como Torre) - usando for e while
    for (int j = col - 1; j >= 0; j--) board[row][j] = '*';
    for (int j = col + 1; j < 8; j++) board[row][j] = '*';
    int i = row - 1;
    while (i >= 0) { board[i][col] = '*'; i--; }
    i = row + 1;
    while (i < 8) { board[i][col] = '*'; i++; }
    
    // Movimentos diagonais (como Bispo) - usando do-while e for
    i = row - 1; int j = col - 1;
    do { if (i >= 0 && j >= 0) board[i][j] = '*'; i--; j--; } while (i >= 0 && j >= 0);
    i = row + 1; j = col + 1;
    do { if (i < 8 && j < 8) board[i][j] = '*'; i++; j++; } while (i < 8 && j < 8);
    for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) board[i][j] = '*';
    for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) board[i][j] = '*';
}

// MÓDULO AVENTUREIRO: Movimento em "L" do Cavalo com loops aninhados
void moveCavalo(int row, int col) {
    board[row][col] = 'C';  // Posiciona o Cavalo
    
    // Loops aninhados para as 8 possibilidades de movimento em "L"
    // (2 em uma direção, 1 perpendicular)
    int deltas[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    
    for (int k = 0; k < 8; k++) {  // Loop externo para cada direção
        int newRow = row + deltas[k][0];
        int newCol = col + deltas[k][1];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            board[newRow][newCol] = '*';  // Marca movimento válido
        }
    }
}

// MÓDULO MESTRE: Recursividade e loops complexos
// Função recursiva para explorar movimentos diagonais (ex.: para Rainha ou Bispo avançado)
void exploreDiagonal(int row, int col, int dRow, int dCol, int steps) {
    if (steps == 0 || row < 0 || row >= 8 || col < 0 || col >= 8) return;
    board[row][col] = '*';
    exploreDiagonal(row + dRow, col + dCol, dRow, dCol, steps - 1);  // Recursão
}

// Movimentos avançados com loops complexos e múltiplas condições
void moveRainhaAvancada(int row, int col) {
    board[row][col] = 'Q';  // Posiciona a Rainha
    
    // Loops complexos com múltiplas condições para horizontais/verticais
    for (int dir = 0; dir < 4; dir++) {  // 4 direções: cima, baixo, esquerda, direita
        int dRow = (dir == 0) ? -1 : (dir == 1) ? 1 : 0;
        int dCol = (dir == 2) ? -1 : (dir == 3) ? 1 : 0;
        int steps = 7;  // Máximo de passos
        int r = row + dRow, c = col + dCol;
        while (steps > 0 && r >= 0 && r < 8 && c >= 0 && c < 8) {  // Condições múltiplas
            board[r][c] = '*';
            r += dRow;
            c += dCol;
            steps--;
        }
    }
    
    // Recursividade para diagonais (explora até 7 passos)
    exploreDiagonal(row - 1, col - 1, -1, -1, 7);  // Diagonal principal cima-esquerda
    exploreDiagonal(row + 1, col + 1, 1, 1, 7);   // Diagonal principal baixo-direita
    exploreDiagonal(row - 1, col + 1, -1, 1, 7);   // Diagonal secundária cima-direita
    exploreDiagonal(row + 1, col - 1, 1, -1, 7);   // Diagonal secundária baixo-esquerda
}

// Função para submenu do Modo Novato
void modoNovato() {
    int choice, row, col;
    printf("\n--- MODO NOVATO ---\n");
    printf("Escolha a peca:\n");
    printf("1. Torre\n");
    printf("2. Bispo\n");
    printf("3. Rainha\n");
    printf("0. Voltar ao menu principal\n");
    scanf("%d", &choice);
    
    if (choice == 0) return;
    
    printf("Digite a linha (0-7) e coluna (0-7): ");
    scanf("%d %d", &row, &col);
    
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        printf("Posicao invalida!\n");
        return;
    }
    
    initializeBoard();
    switch (choice) {
        case 1: moveTorre(row, col); break;
        case 2: moveBispo(row, col); break;
        case 3: moveRainha(row, col); break;
        default: printf("Opcao invalida!\n"); return;
    }
    
    printf("\nTabuleiro com movimentos possiveis:\n");
    printBoard();
}

// Função para submenu do Modo Aventureiro
void modoAventureiro() {
    int row, col;
    printf("\n--- MODO AVENTUREIRO ---\n");
    printf("Peca disponivel: Cavalo\n");
    printf("Digite a linha (0-7) e coluna (0-7): ");
    scanf("%d %d", &row, &col);
    
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        printf("Posicao invalida!\n");
        return;
    }
    
    initializeBoard();
    moveCavalo(row, col);
    
    printf("\nTabuleiro com movimentos possiveis:\n");
    printBoard();
}

// Função para submenu do Modo Mestre
void modoMestre() {
    int row, col;
    printf("\n--- MODO MESTRE ---\n");
    printf("Peca disponivel: Rainha Avancada\n");
    printf("Digite a linha (0-7) e coluna (0-7): ");
    scanf("%d %d", &row, &col);
    
    if (row < 0 || row > 7 || col < 0 || col > 7) {
        printf("Posicao invalida!\n");
        return;
    }
    
    initializeBoard();
    moveRainhaAvancada(row, col);
    
    printf("\nTabuleiro com movimentos possiveis:\n");
    printBoard();
}

// Função principal
int main() {
    int mode;
    
    while (1) {
        printf("\n=== JOGO DE XADREZ VIRTUAL ===\n");
        printf("Escolha o modo:\n");
        printf("1. Modo Novato (Torre, Bispo, Rainha)\n");
        printf("2. Modo Aventureiro (Cavalo)\n");
        printf("3. Modo Mestre (Rainha Avancada)\n");
        printf("0. Sair\n");
        scanf("%d", &mode);
        
        switch (mode) {
            case 1: modoNovato(); break;
            case 2: modoAventureiro(); break;
            case 3: modoMestre(); break;
            case 0: printf("Saindo...\n"); return 0;
            default: printf("Modo invalido! Tente novamente.\n");
        }
    }
    
    return 0;
}
