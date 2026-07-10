/*
    InternGrow C++ Programming Track
    TASK 3: Intelligent Sudoku Solver & Generator
    Feature: 9x9 Sudoku grid solved via recursive backtracking.
    Upgrade: Puzzle generator engine that creates unique unsolved puzzles
             at Easy / Medium / Hard difficulty.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int N = 9;
typedef vector<vector<int>> Grid;

// ---------------- Printing ----------------
void printGrid(const Grid &grid) {
    for (int r = 0; r < N; r++) {
        if (r % 3 == 0 && r != 0) cout << "------+-------+------\n";
        for (int c = 0; c < N; c++) {
            if (c % 3 == 0 && c != 0) cout << "| ";
            cout << (grid[r][c] == 0 ? "." : to_string(grid[r][c])) << " ";
        }
        cout << "\n";
    }
}

// ---------------- Validity check ----------------
bool isSafe(const Grid &grid, int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[startRow + r][startCol + c] == num) return false;
        }
    }
    return true;
}

bool findEmptyCell(const Grid &grid, int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) return true;
        }
    }
    return false;
}

// ---------------- Core recursive backtracking solver ----------------
bool solveSudoku(Grid &grid) {
    int row, col;
    if (!findEmptyCell(grid, row, col)) return true; // solved

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) return true;
            grid[row][col] = 0; // backtrack
        }
    }
    return false;
}

// Counts solutions up to a limit (used to verify puzzle uniqueness)
void countSolutions(Grid &grid, int &count, int limit) {
    if (count >= limit) return;
    int row, col;
    if (!findEmptyCell(grid, row, col)) {
        count++;
        return;
    }
    for (int num = 1; num <= 9 && count < limit; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            countSolutions(grid, count, limit);
            grid[row][col] = 0;
        }
    }
}

bool hasUniqueSolution(Grid grid) {
    int count = 0;
    countSolutions(grid, count, 2); // stop early once 2 found
    return count == 1;
}

// ---------------- UPGRADE FEATURE: Puzzle Generator ----------------

// Fills the diagonal 3x3 boxes first (they're independent, speeds up generation)
void fillDiagonalBoxes(Grid &grid) {
    for (int box = 0; box < 3; box++) {
        int nums[9] = {1,2,3,4,5,6,7,8,9};
        int start = box * 3;
        // shuffle
        for (int i = 8; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(nums[i], nums[j]);
        }
        int idx = 0;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                grid[start + r][start + c] = nums[idx++];
            }
        }
    }
}

Grid generateFullSolution() {
    Grid grid(N, vector<int>(N, 0));
    fillDiagonalBoxes(grid);
    solveSudoku(grid); // fills the rest using backtracking
    return grid;
}

enum Difficulty { EASY, MEDIUM, HARD };

int cellsToRemoveFor(Difficulty d) {
    switch (d) {
        case EASY:   return 35; // ~46 clues remain
        case MEDIUM: return 45; // ~36 clues remain
        case HARD:   return 54; // ~27 clues remain
    }
    return 40;
}

Grid generatePuzzle(Difficulty difficulty) {
    Grid solution = generateFullSolution();
    Grid puzzle = solution;

    vector<pair<int,int>> cells;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            cells.push_back({r, c});

    // shuffle cell order
    for (int i = (int)cells.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(cells[i], cells[j]);
    }

    int toRemove = cellsToRemoveFor(difficulty);
    int removed = 0;

    for (auto &cell : cells) {
        if (removed >= toRemove) break;
        int r = cell.first, c = cell.second;
        int backup = puzzle[r][c];
        puzzle[r][c] = 0;

        // Only keep the removal if the puzzle still has a UNIQUE solution
        if (hasUniqueSolution(puzzle)) {
            removed++;
        } else {
            puzzle[r][c] = backup; // revert, keep it unique-solvable
        }
    }
    return puzzle;
}

string difficultyName(Difficulty d) {
    if (d == EASY) return "Easy";
    if (d == MEDIUM) return "Medium";
    return "Hard";
}

// ---------------- Input helpers ----------------
Grid inputGridFromUser() {
    Grid grid(N, vector<int>(N, 0));
    cout << "Enter the Sudoku grid row by row (use 0 for empty cells):\n";
    for (int r = 0; r < N; r++) {
        cout << "Row " << (r + 1) << " (9 numbers separated by spaces): ";
        for (int c = 0; c < N; c++) {
            cin >> grid[r][c];
        }
    }
    return grid;
}

int main() {
    srand((unsigned)time(nullptr));
    int choice;

    do {
        cout << "\n===== Intelligent Sudoku Solver & Generator =====\n";
        cout << "1. Solve my own Sudoku puzzle\n";
        cout << "2. Generate a new puzzle (Easy/Medium/Hard)\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            Grid grid = inputGridFromUser();
            cout << "\nYour puzzle:\n";
            printGrid(grid);

            if (solveSudoku(grid)) {
                cout << "\nSolved Sudoku:\n";
                printGrid(grid);
            } else {
                cout << "\nNo solution exists for this puzzle.\n";
            }
        } else if (choice == 2) {
            int diffChoice;
            cout << "Select difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoice: ";
            cin >> diffChoice;

            Difficulty d = EASY;
            if (diffChoice == 2) d = MEDIUM;
            else if (diffChoice == 3) d = HARD;

            cout << "\nGenerating a " << difficultyName(d) << " puzzle...\n";
            Grid puzzle = generatePuzzle(d);

            cout << "\nYour new " << difficultyName(d) << " Sudoku puzzle:\n";
            printGrid(puzzle);

            char showSolution;
            cout << "\nShow solution? (y/n): ";
            cin >> showSolution;
            if (showSolution == 'y' || showSolution == 'Y') {
                Grid solved = puzzle;
                solveSudoku(solved);
                cout << "\nSolution:\n";
                printGrid(solved);
            }
        } else if (choice == 3) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
