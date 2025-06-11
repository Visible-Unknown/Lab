// Description: This program solves a 9x9 Sudoku puzzle using backtracking.
// Name: Al Amin Hossain
// Reg: 2020331057

#include <bits/stdc++.h>
using namespace std;

const int N = 9;

void printGrid(vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}


bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& grid, int row, int col) {
    if (row == N - 1 && col == N) {
        return true;
    }

    if (col == N) {
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {
        return solveSudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }

            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}