// Reg. no: 2020331057
// Name: Al-Amin

#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, steps;
    vector<string> path;
};

bool isVisited(set<pair<int, int>> &visited, int x, int y) {
    return visited.count({x, y});
}

void solveWaterJug(int X, int Y, int Z) {
    queue<State> q;
    set<pair<int, int>> visited;

    q.push({0, 0, 0, {}});  // Start with both jugs empty
    visited.insert({0, 0});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int a = current.x, b = current.y;

        if (a == Z || b == Z) {
            cout << "Steps: " << current.steps << endl;
            for (string step : current.path) {
                cout << step << endl;
            }
            return;
        }

        vector<State> nextStates = {
            {X, b, current.steps + 1, current.path}, // Fill Jug X
            {a, Y, current.steps + 1, current.path}, // Fill Jug Y
            {0, b, current.steps + 1, current.path}, // Empty Jug X
            {a, 0, current.steps + 1, current.path}, // Empty Jug Y
            {a - min(a, Y - b), b + min(a, Y - b), current.steps + 1, current.path}, // Pour X -> Y
            {a + min(b, X - a), b - min(b, X - a), current.steps + 1, current.path}  // Pour Y -> X
        };

        vector<string> actions = {
            "Fill Jug X",
            "Fill Jug Y",
            "Empty Jug X",
            "Empty Jug Y",
            "Pour Jug X -> Jug Y",
            "Pour Jug Y -> Jug X"
        };

        for (int i = 0; i < nextStates.size(); i++) {
            int newX = nextStates[i].x, newY = nextStates[i].y;
            if (!isVisited(visited, newX, newY)) {
                nextStates[i].path.push_back(actions[i]);
                q.push(nextStates[i]);
                visited.insert({newX, newY});
            }
        }
    }

    cout << "No solution possible." << endl;
}


int32_t main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1, cs = 0;
    // cin >> t;
    // cin.ignore();
    while (t--) {
        // case;
        int X = 3, Y = 4, Z = 2;
        solveWaterJug(X, Y, Z);
    }

    return 0;
}