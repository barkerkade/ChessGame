// This is the blueprint for all chess pieces. 
class Piece {
public:
    Color color;
    char symbol; // 'P' for White Pawn, 'p' for Black Pawn, etc.

    Piece(Color c, char s) : color(c), symbol(s) {}
    virtual ~Piece() {}

    // VIRTUAL FUNCTION: This is the heart of Polymorphism.
    // Every piece class will provide its own version of this movement rule.
    virtual bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) = 0;
};