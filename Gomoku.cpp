#include <bits/stdc++.h>

using namespace std;
const string BC[] = {".", "O", "X"};
const int value[] = {1000, 1, 11, 121, 1331};
const int mod = 1e9 + 7;
const int len = 4;
const int depth_limit = 10000;
const int line = 4;
inline int change_player(int n) {
    return n ^ 3;
}
inline int people(int n) {
    return (n == 2) ? -1 : (n == 1 ? 1 : 0);
}
inline void ERROR(void) {
    cout << "\nERROR\n\n\n";
    return;
}

struct GMK {
    int Board[len][len] = {0};
    int filled = 0;
    GMK() {
        for (auto &x : Board)
            for (int &b : x) b = 0;
        filled = 0;
        return;
    }
    int Winner() {
        int winnerR, cntR, winnerC, cntC;  // cnt: count, R: row, C: column
        // Judge Rows ans Column
        for (int i = 0; i < len; i++) {
            winnerR = 0, cntR = 0;
            winnerC = 0, cntC = 0;
            for (int j = 0; j < len; j++) {
                // Judge row
                if (winnerR != Board[i][j])
                    cntR = 0, winnerR = Board[i][j];
                else
                    cntR++;
                if (cntR >= line) return winnerR;
                // Judge column
                if (winnerC != Board[i][j])
                    cntC = 0, winnerC = Board[i][j];
                else
                    cntC++;
                if (cntC >= line) return winnerC;
            }
        }
        int winnerS1, cntS1, winnerS2, cntS2;
        // Judge slides
        for (int x = -len; x < len; x++) {
            winnerS1 = 0, cntS1 = 0;
            winnerS2 = 0, cntS2 = 0;
            for (int j = 0; j < len; j++) {
                if (x + j < 0) continue;
                if (winnerS1 != Board[x + j][j])
                    cntS1 = 0, winnerS1 = Board[x + j][j];
                else
                    cntS1++;
                if (winnerS2 != Board[x + j][len - j - 1])
                    cntS2 - 0, winnerS2 = Board[x + j][len - j - 1];
                else
                    cntS2++;
            }
        }
    }
    bool put(int x, int y, int player) {
        if (x >= len || y >= len || x < 0 || y < 0 || player < 1 || player > 2) return false;
        if (Board[x][y] != 0) return false;
        Board[x][y] = player;
        filled++;
        return true;
    }
    void clear(void) {
        for (auto &row : Board)
            for (int &i : row) i = 0;
        filled = 0;
        return;
    }
    bool pick(int x, int y, int player) {
        if (x >= len || y >= len || x < 0 || y < 0 || player < 1 || player > 2) return false;
        if (Board[x][y] != player) return false;
        Board[x][y] = 0;
        filled--;
        return true;
    }
    friend ostream &operator<<(ostream &s, const GMK &G) {
        string str = "";
        for (int y = 0; y < len; y++) {
            for (int x = 0; x < len; x++) {
                str += BC[G.Board[x][y]];
            }
            str += "\n";
        }
        s << str;
        return s;
    }
    friend istream &operator>>(istream &s, GMK &G) {
        const int len2 = len * len;
        char w[len2];
        for (char &i : w) s >> i;
        for (int p = 0; p < len2; p++) {
            if (w[p] == 'O')
                G.put(p % len, p / len, 1);
            else if (w[p] == 'X')
                G.put(p % len, p / len, 2);
            else if (w[p] == '.')
                ;
            else {
                ERROR();
                return s;
            }
        }
        return s;
    }
};

inline int evaluate(GMK G) {
    int score = 0, winner = G.Winner();
    if (winner >= 0)
        return value[0] * people(winner);
    else if (winner == 0)
        return 0;
    for (int count[2] = {0, 0}, y = 0; y < len; y++, count[0] = count[1] = 0) {
        for (int x = 0; x < len; x++) {
            if (G.Board[x][y]) count[G.Board[x][y] & 1]++;
        }
        if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
            score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
    }
    for (int count[2] = {0, 0}, x = 0; x < len; x++, count[0] = count[1] = 0) {
        for (int y = 0; y < len; y++) {
            if (G.Board[x][y]) count[G.Board[x][y] & 1]++;
        }
        if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
            score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
    }
    int count[2] = {0, 0};
    if (G.Board[0][0]) count[G.Board[0][0] & 1]++;
    if (G.Board[1][1]) count[G.Board[1][1] & 1]++;
    if (G.Board[2][2]) count[G.Board[2][2] & 1]++;
    if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
        score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);

    count[0] = count[1] = 0;
    if (G.Board[0][2]) count[G.Board[0][2] & 1]++;
    if (G.Board[1][1]) count[G.Board[1][1] & 1]++;
    if (G.Board[2][0]) count[G.Board[2][0] & 1]++;
    if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
        score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
    if (score > value[0]) score = value[0];

    return score;
}

pair<int, int> AB(GMK &G, int player, int depth = depth_limit, int a = -mod, int b = mod) {
    int winner = G.Winner();
    if (winner >= 0)  // game end;
        return {-1, people(winner) * people(player) * value[0]};
    else if (depth == 1)  // lowest depth
        return {-1, evaluate(G) * people(player)};
    int bx = -1, by = -1, score = 0;
    for (int y = 0; y < len; y++)
        for (int x = 0; x < len; x++) {
            if (G.Board[x][y]) continue;
            G.put(x, y, player);
            score = -AB(G, change_player(player), depth - 1, -b, -a).second;
            if (G.pick(x, y, player))
                ;
            if (score >= b) return {-1, b};
            if (score > a) a = score, bx = x, by = y;
        }
    if (bx == -1) return {-1, a};
    return {bx + by * len, a};
}

void play() {
    GMK Gomoku;
    int mode, move, mx, my, len2 = len * len;
    cout << "please input [0:player&player,1:computer&player,2:player&computer] ";
    cin >> mode;
    for (int x, y, player = 1; Gomoku.filled < len2; player = change_player(player)) {
        cout << Gomoku << endl;
        if (Gomoku.Winner() >= 0) {
            cout << "game end" << endl;
            break;
        }
        cout << player << endl;
        if (player & mode) {
            move = AB(Gomoku, player).first;
            if (move == -1) cout << "ERROR\n";
            if (!Gomoku.put(move % len, move / len, player)) cout << "ERROR" << endl;
        } else {
            cout << "player " << BC[player] << " input" << endl;
            cin >> mx >> my;
            if (mx == -1 && my == -1) return;
            while (!Gomoku.put(mx, my, player)) {
                cout << "ERROR please input again" << endl;
                cin >> mx >> my;
            }
        }
    }
    cout << "============================\n";
    cout << Gomoku;
    cout << "Winner" << Gomoku.Winner() << endl;
}