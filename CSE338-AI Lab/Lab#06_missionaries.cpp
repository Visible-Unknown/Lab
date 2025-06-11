// Description: Missionaries and Cannibals problem
// Name:  Al Amin Hossain
// Reg: 2020331057

#include<bits/stdc++.h>
using namespace std;

struct State {
    int leftM, leftC;
    int rightM, rightC;
    bool boat; // false = left, true = right
    vector<string> path;

    State(int lm, int lc, int rm, int rc, bool b, vector<string> p)
        : leftM(lm), leftC(lc), rightM(rm), rightC(rc), boat(b), path(p) {}
};


bool isValid(int mLeft, int cLeft, int mRight, int cRight) {
    if (mLeft < 0 || cLeft < 0 || mRight < 0 || cRight < 0)
        return false;
    if (mLeft > 0 && mLeft < cLeft)
        return false;
    if (mRight > 0 && mRight < cRight)
        return false;
    return true;
}

void printPeople(int count, char person) {
    for (int i = 0; i < count; i++) {
        cout << person << " ";
    }
}

void printState(const State& s, const string& boatMove) {
    stringstream leftSide, rightSide;

    for (int i = 0; i < s.leftM; i++) leftSide << "M ";
    for (int i = 0; i < s.leftC; i++) leftSide << "C ";

    for (int i = 0; i < s.rightM; i++) rightSide << "M ";
    for (int i = 0; i < s.rightC; i++) rightSide << "C ";

    cout << leftSide.str();
    int spaceCount = 20 - leftSide.str().length();
    for (int i = 0; i < spaceCount; i++) cout << " ";

    if (!s.boat)
        cout << "BOAT-L[" << setw(3) << boatMove << "]------------";
    else
        cout << "------------BOAT-R[" << setw(3) << boatMove << "]";

    cout << "   " << rightSide.str() << endl;
}

void solve() {
    cout << "Missionneries and Cannibals problem" << endl;
    cout << "===================================" << endl << endl;

    queue<State> q;
    set<string> visited;

    State start(3, 3, 0, 0, false, {});
    q.push(start);

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        string stateId = to_string(curr.leftM) + to_string(curr.leftC) +
                         to_string(curr.rightM) + to_string(curr.rightC) +
                         to_string(curr.boat);

        if (visited.count(stateId)) continue;
        visited.insert(stateId);

        if (curr.leftM == 0 && curr.leftC == 0 && curr.rightM == 3 && curr.rightC == 3) {
            State dummy = start;
            printState(dummy, " , ");
            for (auto move : curr.path) {
                dummy.boat = !dummy.boat;

                int m = 0, c = 0;
                if (move.find('M') != string::npos) m++;
                if (move.find("M,M") != string::npos) m++;
                if (move.find('C') != string::npos) c++;
                if (move.find("C,C") != string::npos) c++;

                if (dummy.boat) { // Move to right
                    dummy.leftM -= m;
                    dummy.leftC -= c;
                    dummy.rightM += m;
                    dummy.rightC += c;
                } else { // Move to left
                    dummy.leftM += m;
                    dummy.leftC += c;
                    dummy.rightM -= m;
                    dummy.rightC -= c;
                }

                printState(dummy, move);
            }

            return;
        }

        vector<pair<int, int>> moves = {
            {2, 0}, {0, 2}, {1, 0}, {0, 1}, {1, 1}
        };

        for (auto move : moves) {
            int m = move.first;
            int c = move.second;

            int lm = curr.leftM;
            int lc = curr.leftC;
            int rm = curr.rightM;
            int rc = curr.rightC;
            bool boatPos = curr.boat;

            vector<string> newPath = curr.path;

            string moveDesc;
            if (m == 2) moveDesc = "M,M";
            else if (m == 1 && c == 1) moveDesc = "C,M";
            else if (c == 2) moveDesc = "C,C";
            else if (m == 1) moveDesc = "M, ";
            else if (c == 1) moveDesc = "C, ";

            if (!boatPos) { 
                lm -= m;
                lc -= c;
                rm += m;
                rc += c;
            } else { 
                lm += m;
                lc += c;
                rm -= m;
                rc -= c;
            }

            if (isValid(lm, lc, rm, rc)) {
                newPath.push_back(moveDesc);
                q.push(State(lm, lc, rm, rc, !boatPos, newPath));
            }
        }
    }

}

int main() {
    solve();
    return 0;
}
