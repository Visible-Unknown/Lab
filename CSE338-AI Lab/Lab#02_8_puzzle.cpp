//Reg. no: 2020331057
//Name: Al-Amin 
#include <bits/stdc++.h>
using namespace std;

#define N 3

vector<vector<int>> goalState = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string moveNames[] = {"UP", "DOWN", "LEFT", "RIGHT"};

struct PuzzleState {
    vector<vector<int>> board;
    int x, y; // Blank tile position
    int g, h; // Cost values: g(n) and h(n)
    string moves;

    PuzzleState(vector<vector<int>> b, int x, int y, int g, int h, string moves)
        : board(b), x(x), y(y), g(g), h(h), moves(moves) {}

    bool operator>(const PuzzleState& other) const {
        return (g + h) > (other.g + other.h);
    }
};

int misplacedTiles(const vector<vector<int>>& board) {
    int misplaced = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0 && board[i][j] != goalState[i][j]) {
                misplaced++;
            }
        }
    }
    return misplaced;
}

bool isGoalState(const vector<vector<int>>& board) {
    return board == goalState;
}

void solve8Puzzle(vector<vector<int>> startState) {
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> pq;
    set<vector<vector<int>>> visited;


    int startX, startY;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (startState[i][j] == 0)
                startX = i, startY = j;

    PuzzleState start(startState, startX, startY, 0, misplacedTiles(startState), "");

    pq.push(start);
    visited.insert(startState);

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        if (isGoalState(current.board)) {
            cout << "Solution found in " << current.g << " moves:\n";
            cout << current.moves << "\n";
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newBoard = current.board;
                swap(newBoard[current.x][current.y], newBoard[newX][newY]);

                if (visited.find(newBoard) == visited.end()) {
                    int newH = misplacedTiles(newBoard);
                    pq.push(PuzzleState(newBoard, newX, newY, current.g + 1, newH, current.moves + moveNames[i] + " "));
                    visited.insert(newBoard);
                }
            }
        }
    }

    cout << "No solution found!\n";
}

int32_t main() {
    vector<vector<int>> initialState = {
        {7, 2, 4},
        {5, 0, 6},
        {8, 3, 1}
    };

    solve8Puzzle(initialState);

    return 0;
}
