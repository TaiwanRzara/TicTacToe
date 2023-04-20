#include <iostream>
#include <string>
using namespace std;
char board[3][3];
inline char opp(char ox) {
    return ox == 'O' ? 'X' : 'O';
}
inline void print() {
    string tempstr;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tempstr += board[j][i];
        }
        tempstr += '\n';
    }
    cout << tempstr;
    return;
}
inline bool is_full() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '.')
                return false;
        }
    }
    return true;
}
inline int assess() {
    // 0:O 1:X
    int row[3][2] = {0}, column[3][2] = {0}, slides[2][2] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == 'O')
                row[i][0]++;
            else if (board[j][i] == 'X')
                row[i][1]++;
            if (board[i][j] == 'O')
                column[j][0]++;
            else if (board[i][j] == 'X')
                column[j][1]++;
        }
        if (board[i][i] == 'O')
            slides[0][0]++;
        else if (board[i][i] == 'X')
            slides[0][1]++;
        if (board[i][2 - i] == 'O')
            slides[1][0]++;
        else if (board[i][2 - i] == 'X')
            slides[1][1]++;
    }
    int result = 0;
    for (int i = 0; i < 3; i++) {
        if (row[i][0] == 3 || column[i][0] == 3)
            return 1000000;
        if (row[i][1] == 3 || column[i][1] == 3)
            return -1000000;
        // O
        if (row[i][1] == 0) {
            if (row[i][0] == 2)
                result += 10000;
            else if (row[i][0] == 1)
                result += 100;
        }
        // X
        if (column[i][0] == 0) {
            if (column[i][1] == 2)
                result -= 10000;
            else if (column[i][1] == 1)
                result -= 100;
        }
        // O
        if (column[i][1] == 0) {
            if (column[i][0] == 2)
                result += 10000;
            else if (column[i][0] == 1)
                result += 100;
        }
        // X
        if (column[i][0] == 0) {
            if (column[i][1] == 2)
                result -= 10000;
            else if (column[i][1] == 1)
                result -= 100;
        }
    }
    if (slides[0][0] == 3 || slides[1][0] == 3)
        return 1000000;
    if (slides[0][1] == 3 || slides[1][1] == 3)
        return -1000000;
    for (int i = 0; i < 2; i++) {
        // O
        if (slides[i][1] == 0) {
            if (slides[i][0] == 2)
                result += 10000;
            else if (slides[i][0] == 1)
                result += 100;
        }
        // X
        if (slides[i][0] == 0) {
            if (slides[i][1] == 2)
                result -= 10000;
            else if (slides[i][1] == 1)
                result -= 100;
        }
    }
    return result;
}
int ab(int a, int b, int x, int y, int depth, char ox) {
    int result = assess(), score;
    if (!--depth || result == 1000000 || result == -1000000)
        return result;
    if (is_full())
        return 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == '.') {
                board[j][i] = ox;
                score = -ab(-b, -a, j, i, depth, opp(ox));
                board[j][i] = '.';
                if (score >= b)
                    return b;
                if (score > a)
                    a = score;
            }
        }
    }
    return a;
}
int best() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == '.') {
                board[j][i] = 'O';
                if (assess() == 1000000) {
                    board[j][i] = '.';
                    return j * 3 + i;
                }
                board[j][i] = '.';
            }
        }
    }
    int best_x, best_y, score, a = -10000000, b = 10000000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[j][i] == '.') {
                board[j][i] = 'O';
                score = -ab(-b, -a, j, i, 6, 'X');
                board[j][i] = '.';
                if (score >= b)
                    return b;
                if (score > a) {
                    a = score;
                    best_x = j;
                    best_y = i;
                }
            }
        }
    }
    // hash
    return best_x * 3 + best_y;
}
int main() {
    // set the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '.';
        }
    }
    char ox = 'X';
    // we are 'X', the computer is 'O'
    while (!is_full() && assess() != 1000000 && assess() != -1000000) {
        int x, y;
        print();
        cin >> x >> y;
        board[x][y] = 'X';
        if (assess() == -1000000) {
            print();
            cout << "you win";
            return 0;
        }
        int bests = best();
        board[bests / 3][bests % 3] = 'O';
        if (assess() == 1000000) {
            print();
            cout << "you lose";
            return 0;
        }
    }
    cout << "tie";
    return 0;
}