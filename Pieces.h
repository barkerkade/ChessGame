#ifndef PIECES_H
#define PIECES_H

#include "Piece.h"
#include <cmath>

// KNIGHT: Moves in an "L" shape. It is the only piece that can jump.
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, (c == WHITE ? 'N' : 'n')) {}

    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        int dRow = std::abs(sR - eR); // Difference in Rows
        int dCol = std::abs(sC - eC); // Difference in Columns

        // Knight move is valid if it moves 2 squares one way and 1 square the other
        return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
    }
};

// BISHOP: Moves diagonally any number of squares.
class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c, (c == WHITE ? 'B' : 'b')) {}

    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        // Diagonal check: vertical change must equal horizontal change
        if (std::abs(sR - eR) != std::abs(sC - eC)) return false;

        // Determine direction of movement (1 or -1)
        int rStep = (eR > sR) ? 1 : -1;
        int cStep = (eC > sC) ? 1 : -1;

        int currR = sR + rStep;
        int currC = sC + cStep;

        // Path checking: ensure no pieces are blocking the diagonal path
        while (currR != eR && currC != eC) {
            if (grid[currR][currC] != nullptr) return false; // Path blocked
            currR += rStep;
            currC += cStep;
        }
        return true;
    }
};
// ROOK: Moves straight (horizontal or vertical)
class Rook : public Piece {
public:
    Rook(Color c) : Piece(c, (c == WHITE ? 'R' : 'r')) {}
    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        if (sR != eR && sC != eC) return false; // Must be same row or same col

        int rStep = (eR == sR) ? 0 : (eR > sR ? 1 : -1);
        int cStep = (eC == sC) ? 0 : (eC > sC ? 1 : -1);
        int currR = sR + rStep;
        int currC = sC + cStep;

        while (currR != eR || currC != eC) {
            if (grid[currR][currC] != nullptr) return false;
            currR += rStep;
            currC += cStep;
        }
        return true;
    }
};

// QUEEN: Combination of Rook and Bishop
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c, (c == WHITE ? 'Q' : 'q')) {}
    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        // Queens move like Rooks OR Bishops
        bool rookMove = (sR == eR || sC == eC);
        bool bishopMove = (abs(sR - eR) == abs(sC - eC));
        if (!rookMove && !bishopMove) return false;

        int rStep = (eR == sR) ? 0 : (eR > sR ? 1 : -1);
        int cStep = (eC == sC) ? 0 : (eC > sC ? 1 : -1);
        int currR = sR + rStep;
        int currC = sC + cStep;

        while (currR != eR || currC != eC) {
            if (grid[currR][currC] != nullptr) return false;
            currR += rStep;
            currC += cStep;
        }
        return true;
    }
};

// KING: Moves one square in any direction
class King : public Piece {
public:
    King(Color c) : Piece(c, (c == WHITE ? 'K' : 'k')) {}
    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        return (abs(sR - eR) <= 1 && abs(sC - eC) <= 1);
    }
};

// PAWN: Moves forward, captures diagonally (simplified version)
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c, (c == WHITE ? 'P' : 'p')) {}

    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        int direction = (color == WHITE) ? -1 : 1; // White moves up (-1), Black moves down (+1)
        int startRow = (color == WHITE) ? 6 : 1;   // Standard starting rows

        // 1. Single space forward
        if (sC == eC && eR == sR + direction) {
            return grid[eR][eC] == nullptr;
        }

        // 2. Double space forward (First move only)
        if (sC == eC && sR == startRow && eR == sR + (2 * direction)) {
            // Check that BOTH the target square and the square the pawn jumps over are empty
            int middleRow = sR + direction;
            return grid[eR][eC] == nullptr && grid[middleRow][sC] == nullptr;
        }

        // 3. Diagonal capture
        if (abs(sC - eC) == 1 && eR == sR + direction) {
            // Target must contain an enemy piece
            return grid[eR][eC] != nullptr && grid[eR][eC]->color != color;
        }

        return false;
    }
};

#endif