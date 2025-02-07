#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void solveNQUtil(vector<vector<int>>& board, int col, int N, vector<vector<vector<int>>>& solutions) {
    if (col >= N) {
        solutions.push_back(board);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;
            solveNQUtil(board, col + 1, N, solutions);
            board[i][col] = 0; // Backtrack
        }
    }
}

void solveNQ(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    vector<vector<vector<int>>> solutions;

    solveNQUtil(board, 0, N, solutions);

    for (const auto& solution : solutions) {
        printSolution(solution, N);
    }

    cout << "Total solutions: " << solutions.size() << endl;
}

int main() {
    int N = 5; // You can change the value of N
    solveNQ(N);
    return 0;
}
