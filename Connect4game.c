#include <stdio.h>
#include <stdlib.h>

#define EMPTY ' '
#define PLAYER1 'X'
#define PLAYER2 'O'

void suzdavanePole(char** board, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            board[i][j] = EMPTY;
        }
    }
}

void printPole(char** board, int height, int width) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < width; ++j) {
        printf("--");
    }
    printf("-\n");
    for (int j = 0; j < width; ++j) {
        printf(" %d", j);
    }
    printf("\n");
}

int PoverkaHod(char** board, int column, int width) {
    if (column < 0 || column >= width) {
        return 0;
    }
    return board[0][column] == EMPTY;
}

int IzpulnenieHod(char** board, int height, int column, char player) {
    for (int i = height - 1; i >= 0; --i) {
        if (board[i][column] == EMPTY) {
            board[i][column] = player;
            return i;
        }
    }
    return -1; 
}

int checkWin(char** board, int height, int width, int row, int column, char player) {
    //horizontalno
        int count = 0;
        for (int j = 0; j < width; j++) {
            if (board[row][j] == player) {
                if (count++ == 4)
                {
                return 1;
                }
            } else {
                count = 0;
            }
        }
    //vertikalno
        count = 0;
        for (int i = 0; i < height; i++) {
            if (board[i][column] == player) {
                if (count++ == 4){
                return 1;
                }
            } else {
                count = 0;
            }
        }

    //diagonalno
        int start_row, start_col, count;


        if (row < column) {
            start_row = 0;
            start_col = column - row;
        } else {
            start_row = row - column;
            start_col = 0;
        }
        count = 0;
        while (start_row < height && start_col < width) {
            if (board[start_row][start_col] == player) {
                count++;
                if (count == 4) {
                    return 1; 
                }
            } else {
                count = 0; 
            }
            start_row++;
            start_col++;
}

            
            count = 0;

            
            if (row < width - 1 - column) {
                start_row = 0;
                start_col = column + row;
            } else {
                start_row = row - (width - 1 - column);
                start_col = width - 1;
            }

            
            while (start_row < height && start_col >= 0) {
                if (board[start_row][start_col] == player) {
                    count++;
                    if (count == 4) {
                        return 1; 
                    }
                } else {
                    count = 0; 
                }
                start_row++;
                start_col--;
            }

    return 0;
}

void playGame(int height, int width, char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Не може да се отвори файла за запис.\n");
        return;
    }

    char** board = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < height; ++i) {
        board[i] = (char*)malloc(width * sizeof(char));
    }
    initializeBoard(board, height, width);

    int currentPlayer = 0;
    char players[2] = {PLAYER1, PLAYER2};
    int totalMoves = 0;
    int maxMoves = height * width;

    while (1) {
        printBoard(board, height, width);
        fprintf(file, "Игрално поле:\n");
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                fprintf(file, "|%c", board[i][j]);
            }
            fprintf(file, "|\n");
        }
        for (int j = 0; j < width; ++j) {
            fprintf(file, "--");
        }
        fprintf(file, "-\n");
        for (int j = 0; j < width; ++j) {
            fprintf(file, " %d", j);
        }
        fprintf(file, "\n");

        int column;
        printf("Играч %d (%c), изберете колона: ", currentPlayer + 1, players[currentPlayer]);
        scanf("%d", &column);

        if (!isValidMove(board, column, width)) {
            printf("Невалиден ход. Опитайте отново.\n");
            continue;
        }

        int row = makeMove(board, height, column, players[currentPlayer]);
        totalMoves++;

        if (checkWin(board, height, width, row, column, players[currentPlayer])) {
            printBoard(board, height, width);
            fprintf(file, "Играч %d (%c) печели!\n", currentPlayer + 1, players[currentPlayer]);
            printf("Играч %d (%c) печели!\n", currentPlayer + 1, players[currentPlayer]);
            break;
        }

        if (totalMoves == maxMoves) {
            printBoard(board, height, width);
            fprintf(file, "Играта е равна!\n");
            printf("Играта е равна!\n");
            break;
        }

        currentPlayer = (currentPlayer + 1) % 2;
    }

    fclose(file);
    for (int i = 0; i < height; ++i) {
        free(board[i]);
    }
    free(board);
}