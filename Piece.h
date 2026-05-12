#ifndef PIECE_H
#define PIECE_H

// Enum helps avoid "magic numbers" (like 0, 1, 2)
enum Color { WHITE, BLACK, NONE };

class Piece {
public:
    Color color;
    char symbol; // Visual representation (e.g., 'N', 'b')

    Piece(Color c, char s) : color(c), symbol(s) {}

    // Virtual destructor: ensures that when we delete a Piece*, 
    // the correct child (Knight/Bishop) destructor is called.
    virtual ~Piece() {}

    // Pure Virtual Function (= 0): Makes this class "Abstract."
    // Every specific piece MUST implement its own version of this rule.
    virtual bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) = 0;
};

#endif