#include <iostream>
#include <string>
#include "Board.h" // This chain-includes Pieces.h and Piece.h

using namespace std;

class ChessGame {
private:
    Board board;
    Color turn;
    bool isRunning;

public:
    ChessGame() : turn(WHITE), isRunning(true) {}

    // handleInput: Converts user strings (e.g. "b1c3") into array indices
    void handleInput() {
        string input;
        cout << (turn == WHITE ? "WHITE's Turn" : "BLACK's Turn") << " (e.g. b1a3 or 'quit'): ";
        cin >> input;

        if (input == "quit") { isRunning = false; return; }
        if (input.length() < 4) { cout << "Invalid format!" << endl; return; }

        // ASCII math: 'a' is 97. If input is 'b', 98 - 97 = index 1.
        int sC = input[0] - 'a';
        int sR = 8 - (input[1] - '0');
        int eC = input[2] - 'a';
        int eR = 8 - (input[3] - '0');

        processMove(sR, sC, eR, eC);
    }

    void processMove(int sR, int sC, int eR, int eC) {
        // Step 1: Boundary check (don't access memory outside the 8x8 array)
        if (sR < 0 || sR > 7 || sC < 0 || sC > 7 || eR < 0 || eR > 7 || eC < 0 || eC > 7) {
            cout << "Out of bounds!" << endl;
            return;
        }

        Piece* p = board.grid[sR][sC];

        // Step 2: Ownership check (must pick a piece of your own color)
        if (!p || p->color != turn) {
            cout << "Invalid piece selection!" << endl;
            return;
        }

        // Step 3: Rule check (calls the virtual isValidMove for Knight or Bishop)
        if (p->isValidMove(sR, sC, eR, eC, board.grid)) {

            // Step 4: Friendly fire check
            if (board.grid[eR][eC] != nullptr && board.grid[eR][eC]->color == turn) {
                cout << "Cannot capture your own piece!" << endl;
                return;
            }

            // Step 5: Execute move
            delete board.grid[eR][eC];   // Delete captured piece if it exists
            board.grid[eR][eC] = p;      // Move pointer to new square
            board.grid[sR][sC] = nullptr;// Clear old square

            // Step 6: Change turns
            turn = (turn == WHITE) ? BLACK : WHITE;
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