// 3. PIECE SUBCLASSES
// ---------------------------------------------------------
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c, (c == WHITE ? 'N' : 'n')) {}

    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        // The Knight is the only piece that "jumps."
        // We only care if the landing square is an L-shape (2x1 or 1x2).
        int dRow = abs(sR - eR);
        int dCol = abs(sC - eC);
        return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
    }
};

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c, (c == WHITE ? 'B' : 'b')) {}

    bool isValidMove(int sR, int sC, int eR, int eC, Piece* grid[8][8]) override {
        // Bishop move: change in Row must equal change in Column (Diagonal).
        if (abs(sR - eR) != abs(sC - eC)) return false;

        // PATH CHECKING: Unlike Knights, Bishops can't jump over pieces.
        int rStep = (eR > sR) ? 1 : -1;
        int cStep = (eC > sC) ? 1 : -1;
        int currR = sR + rStep;
        int currC = sC + cStep;

        while (currR != eR && currC != eC) {
            if (grid[currR][currC] != nullptr) return false; // Path is blocked
            currR += rStep;
            currC += cStep;
        }
        return true;
    }
};