/*
    InternGrow C++ Programming Track - Task 3
    Intelligent Sudoku Solver & Generator
    ---------------------------------------------------------------
    Features:
    - Represent Sudoku grid as a 2D array (9x9)
    - Recursive backtracking algorithm to solve empty board cells
    - Upgrade Feature: Puzzle generator engine that creates unique
      unsolved Sudoku configurations based on difficulty
      (Easy, Medium, Hard)
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

// Global random engine (replaces deprecated std::random_shuffle)
static mt19937 rng((unsigned int)time(0));

const int SIZE = 9;
const int EMPTY = 0;

// -----------------------------------------------------------------
// SudokuBoard class - handles grid storage, validation, solving,
// and puzzle generation
// -----------------------------------------------------------------
class SudokuBoard {
private:
    int grid[SIZE][SIZE];

    // Check if placing 'num' at grid[row][col] is valid
    bool isSafe(int row, int col, int num) const {
        // Check row
        for (int c = 0; c < SIZE; c++)
            if (grid[row][c] == num) return false;

        // Check column
        for (int r = 0; r < SIZE; r++)
            if (grid[r][col] == num) return false;

        // Check 3x3 sub-box
        int boxRowStart = row - row % 3;
        int boxColStart = col - col % 3;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                if (grid[boxRowStart + r][boxColStart + c] == num) return false;

        return true;
    }

    // Find the next empty cell; returns false if board is full
    bool findEmptyCell(int& row, int& col) const {
        for (row = 0; row < SIZE; row++)
            for (col = 0; col < SIZE; col++)
                if (grid[row][col] == EMPTY) return true;
        return false;
    }

    // Recursive backtracking solver (core algorithm)
    bool solveInternal() {
        int row, col;
        if (!findEmptyCell(row, col)) return true; // solved

        // Try numbers 1-9 in randomized order for varied puzzle generation
        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int num : nums) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solveInternal()) return true;

                grid[row][col] = EMPTY; // backtrack
            }
        }
        return false; // trigger backtracking
    }

    // Randomized version used for generating a fresh solved board
    bool fillBoardRandomly() {
        int row, col;
        if (!findEmptyCell(row, col)) return true;

        vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        shuffle(nums.begin(), nums.end(), rng);

        for (int num : nums) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                if (fillBoardRandomly()) return true;
                grid[row][col] = EMPTY;
            }
        }
        return false;
    }

    // Count number of solutions (used to ensure uniqueness while generating)
    int countSolutions(int limit = 2) {
        int row, col;
        if (!findEmptyCell(row, col)) return 1;

        int count = 0;
        for (int num = 1; num <= 9 && count < limit; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                count += countSolutions(limit - count);
                grid[row][col] = EMPTY;
            }
        }
        return count;
    }

public:
    SudokuBoard() {
        clearBoard();
        srand((unsigned int)time(0));
    }

    void clearBoard() {
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                grid[r][c] = EMPTY;
    }

    void setCell(int row, int col, int value) {
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE)
            grid[row][col] = value;
    }

    int getCell(int row, int col) const {
        return grid[row][col];
    }

    // Public solve function - wraps recursive backtracking
    bool solve() {
        return solveInternal();
    }

    void printBoard() const {
        for (int r = 0; r < SIZE; r++) {
            if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
            for (int c = 0; c < SIZE; c++) {
                if (c % 3 == 0 && c != 0) cout << "| ";
                if (grid[r][c] == EMPTY) cout << ". ";
                else cout << grid[r][c] << " ";
            }
            cout << "\n";
        }
    }

    void loadFromInput() {
        cout << "Enter the Sudoku grid row by row (use 0 for empty cells):\n";
        for (int r = 0; r < SIZE; r++) {
            cout << "Row " << (r + 1) << " (9 numbers separated by spaces): ";
            for (int c = 0; c < SIZE; c++) {
                cin >> grid[r][c];
            }
        }
    }

    // -----------------------------------------------------------
    // UPGRADE FEATURE: Puzzle Generator
    // Generates a fully solved board, then removes cells based
    // on difficulty while checking the puzzle remains uniquely
    // solvable.
    // -----------------------------------------------------------
    void generatePuzzle(const string& difficulty) {
        clearBoard();
        fillBoardRandomly(); // step 1: generate a complete valid solution

        int cellsToRemove;
        if (difficulty == "Easy") cellsToRemove = 35;
        else if (difficulty == "Medium") cellsToRemove = 45;
        else if (difficulty == "Hard") cellsToRemove = 54;
        else cellsToRemove = 40; // default fallback

        // Build a shuffled list of all cell positions
        vector<pair<int,int>> cells;
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                cells.push_back({r, c});
        shuffle(cells.begin(), cells.end(), rng);

        int removed = 0;
        for (auto& cell : cells) {
            if (removed >= cellsToRemove) break;

            int r = cell.first, c = cell.second;
            int backup = grid[r][c];
            grid[r][c] = EMPTY;

            // Verify the puzzle still has a UNIQUE solution
            SudokuBoard temp = *this;
            int solutions = temp.countSolutions(2);

            if (solutions != 1) {
                grid[r][c] = backup; // revert - removing this cell breaks uniqueness
            } else {
                removed++;
            }
        }

        cout << "\n" << difficulty << " puzzle generated! ("
             << removed << " cells removed, " << (81 - removed) << " clues remaining)\n";
    }
};

// -----------------------------------------------------------------
// Menu-driven interface
// -----------------------------------------------------------------
void printMenu() {
    cout << "\n===================================\n";
    cout << "  InternGrow Sudoku Solver & Generator\n";
    cout << "===================================\n";
    cout << "1. Enter Your Own Puzzle & Solve\n";
    cout << "2. Generate a New Puzzle (Easy/Medium/Hard)\n";
    cout << "3. Solve the Currently Generated Puzzle\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    SudokuBoard board;
    int choice;
    bool hasGeneratedPuzzle = false;

    cout << "Welcome to InternGrow Intelligent Sudoku Solver & Generator\n";

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                board.clearBoard();
                board.loadFromInput();
                cout << "\nYour Puzzle:\n";
                board.printBoard();

                if (board.solve()) {
                    cout << "\nSolved Puzzle:\n";
                    board.printBoard();
                } else {
                    cout << "\nNo solution exists for this puzzle.\n";
                }
                hasGeneratedPuzzle = false;
                break;
            }
            case 2: {
                cout << "\nSelect Difficulty:\n";
                cout << "1. Easy\n2. Medium\n3. Hard\n";
                cout << "Enter choice (1-3): ";
                int diffChoice;
                cin >> diffChoice;

                string difficulty;
                if (diffChoice == 1) difficulty = "Easy";
                else if (diffChoice == 2) difficulty = "Medium";
                else if (diffChoice == 3) difficulty = "Hard";
                else {
                    cout << "Invalid choice. Defaulting to Medium.\n";
                    difficulty = "Medium";
                }

                board.generatePuzzle(difficulty);
                cout << "\nGenerated Puzzle:\n";
                board.printBoard();
                hasGeneratedPuzzle = true;
                break;
            }
            case 3: {
                if (!hasGeneratedPuzzle) {
                    cout << "\nNo puzzle generated yet. Please use option 2 first.\n";
                    break;
                }
                cout << "\nSolving current puzzle...\n";
                if (board.solve()) {
                    cout << "\nSolved Puzzle:\n";
                    board.printBoard();
                } else {
                    cout << "\nNo solution exists.\n";
                }
                break;
            }
            case 0:
                cout << "Thank you for using InternGrow Sudoku Solver & Generator!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
