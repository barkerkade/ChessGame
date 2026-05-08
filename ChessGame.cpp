#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// 1. DATA STRUCTURES
// Using an enum makes the code more readable than using magic numbers like 0 or 1.
enum Color { WHITE, BLACK, NONE };

// 5. THE GAME CONTROLLER (The Main Class)
// This orchestrates the flow: Input -> Validation -> Execution -> Turn Swap.
class ChessGame {
private:
    Board board;
    Color turn;
    bool isRunning;

public:
    ChessGame() : turn(WHITE), isRunning(true) {}

    // Converts notation like "b1c3" into array coordinates (7,1 to 5,2)
    void handleInput() {
        string input;
        cout << (turn == WHITE ? "WHITE's Turn" : "BLACK's Turn") << " (e.g. b1a3 or 'quit'): ";
        cin >> input;

        if (input == "quit") { isRunning = false; return; }
        if (input.length() < 4) { cout << "Invalid format!" << endl; return; }

        // Logic: 'a' is ASCII 97. If input[0] is 'b' (98), 98-97 = 1 (Column 1).
        int sC = input[0] - 'a';
        int sR = 8 - (input[1] - '0');
        int eC = input[2] - 'a';
        int eR = 8 - (input[3] - '0');

        processMove(sR, sC, eR, eC);
    }

    void processMove(int sR, int sC, int eR, int eC) {
        // 1. Boundary Check: Ensure move is within the 8x8 grid
        if (sR < 0 || sR > 7 || sC < 0 || sC > 7 || eR < 0 || eR > 7 || eC < 0 || eC > 7) {
            cout << "Out of bounds!" << endl;
            return;
        }

        Piece* p = board.grid[sR][sC];

        // 2. Selection Check: Did they pick a piece? Is it their color?
        if (!p || p->color != turn) {
            cout << "Invalid piece selection!" << endl;
            return;
        }

        // 3. Rule Check: Does the specific piece allow this movement?
        if (p->isValidMove(sR, sC, eR, eC, board.grid)) {

            // 4. Friendly Fire Check: Cannot land on your own piece.
            if (board.grid[eR][eC] != nullptr && board.grid[eR][eC]->color == turn) {
                cout << "Cannot capture your own piece!" << endl;
                return;
            }

            // 5. Execute Move: Update the grid pointers
            delete board.grid[eR][eC];   // Memory cleanup if a piece was captured
            board.grid[eR][eC] = p;      // Move the pointer to the new square
            board.grid[sR][sC] = nullptr;// Clear the old square

            turn = (turn == WHITE) ? BLACK : WHITE; // Swap turns
        }
        else {
            cout << "That piece cannot move that way!" << endl;
        }
    }

    void start() {
        cout << "Welcome to C++ Chess!" << endl;
        while (isRunning) {
            board.display();
            handleInput();
        }
    }
};

int main() {
    ChessGame game;
    game.start();
    return 0;
}