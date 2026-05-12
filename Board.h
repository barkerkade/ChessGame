#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"
#include <iostream>

class Board {
public:
    Piece* grid[8][8];

    Board() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) grid[i][j] = nullptr;
        setup();
    }

    void setup() {
        // 1. Setup Pawns (Rows 1 and 6)
        for (int i = 0; i < 8; i++) {
            grid[1][i] = new Pawn(BLACK);
            grid[6][i] = new Pawn(WHITE);
        }

        // 2. Setup Rooks (Corners)
        grid[0][0] = new Rook(BLACK); grid[0][7] = new Rook(BLACK);
        grid[7][0] = new Rook(WHITE); grid[7][7] = new Rook(WHITE);

        // 3. Setup Knights
        grid[0][1] = new Knight(BLACK); grid[0][6] = new Knight(BLACK);
        grid[7][1] = new Knight(WHITE); grid[7][6] = new Knight(WHITE);

        // 4. Setup Bishops
        grid[0][2] = new Bishop(BLACK); grid[0][5] = new Bishop(BLACK);
        grid[7][2] = new Bishop(WHITE); grid[7][5] = new Bishop(WHITE);

        // 5. Setup Queens
        grid[0][3] = new Queen(BLACK);
        grid[7][3] = new Queen(WHITE);

        // 6. Setup Kings
        grid[0][4] = new King(BLACK);
        grid[7][4] = new King(WHITE);
    }

    void display() {
        std::cout << "\n    a b c d e f g h\n";
        for (int i = 0; i < 8; i++) {
            std::cout << 8 - i << " [ ";
            for (int j = 0; j < 8; j++) {
                if (grid[i][j]) std::cout << grid[i][j]->symbol << " ";
                else std::cout << ". ";
            }
            std::cout << "] " << 8 - i << std::endl;
        }
        std::cout << "    a b c d e f g h\n";
    }
};

#endif