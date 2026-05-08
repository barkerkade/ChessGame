// 4. THE BOARD CLASS
// Manages the 8x8 array of Piece pointers and handles visual output.
class Board {
public:
    Piece* grid[8][8];

    Board() {
        // Initialize the board to be completely empty (null pointers).
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++) grid[i][j] = nullptr;
        setup();
    }

    // Manual setup for a small demo.
    void setup() {
        grid[0][1] = new Knight(BLACK);
        grid[0][2] = new Bishop(BLACK);
        grid[7][1] = new Knight(WHITE);
        grid[7][2] = new Bishop(WHITE);
    }

    void display() {
        cout << "\n  a b c d e f g h\n";
        for (int i = 0; i < 8; i++) {
            cout << 8 - i << " "; // Rank numbers (8 down to 1)
            for (int j = 0; j < 8; j++) {
                if (grid[i][j]) cout << grid[i][j]->symbol << " ";
                else cout << ". ";
            }
            cout << 8 - i << endl;
        }
        cout << "  a b c d e f g h\n";
    }
};