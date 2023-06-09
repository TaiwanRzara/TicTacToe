#include <iostream>
#include <utility>
using std::cin;
using std::cout;
using std::pair;
typedef pair<unsigned long long, unsigned long long> pll;
const int len = 10;
int board[len][len];
pll hash() {
    int chance = (1 << 9) - 1;
    int cur;
    int type = -1;
    for (int j = 0; j < len; j++) {
        for (int i = 0; i < len; i++) {
            cur = 2;
            if (chance & 0b1) {  // 由左而右，由上而下
                if (board[i][j] < cur)
                    cur = board[i][j];
                else if (board[i][j] > cur)
                    chance ^= 0b1;
            }
            if (chance & 0b10) {  // 由上而下，由左而右
                if (board[j][i] < cur)
                    cur = board[j][i], chance &= 0b11111110;
                else if (board[j][i] > cur) {
                    chance ^= 0b10;
                }
            }
            if (chance & 0b100) {  // 由右而左，由上而下
                if (board[len - i - 1][j] < cur)
                    cur = board[len - i - 1][j], chance &= 0b11111100;
                else if (board[len - i - 1][j] > cur)
                    chance ^= 0b100;
            }
            if (chance & 0b1000) {  // 由上而下，由右而左
                if (board[len - j - 1][i] < cur)
                    cur = board[len - j - 1][i], chance &= 0b11111000;
                else if (board[len - j - 1][i] > cur)
                    chance ^= 0b1000;
            }
            if (chance & 0b10000) {  // 由左而右，由下而上
                if (board[i][len - j - 1] < cur)
                    cur = board[i][len - j - 1], chance &= 0b11110000;
                else if (board[i][len - j - 1] > cur)
                    chance ^= 0b10000;
            }
            if (chance & 0b100000) {  // 由下而上，由左而右
                if (board[j][len - i - 1] < cur)
                    cur = board[j][len - i - 1], chance &= 0b11100000;
                else if (board[j][len - i - 1] > cur)
                    chance ^= 0b100000;
            }
            if (chance & 0b1000000) {  // 由右而左，由下而上
                if (board[len - i - 1][len - j - 1] < cur)
                    cur = board[len - i - 1][len - j - 1], chance &= 0b11000000;
                else if (board[len - i - 1][len - j - 1] > cur)
                    chance ^= 0b1000000;
            }
            if (chance & 0b10000000) {  // 由下而上，由右而左
                if (board[len - j - 1][len - i - 1] < cur)
                    cur = board[len - j - 1][len - i - 1], chance &= 0b10000000;
                else if (board[len - j - 1][len - i - 1] > cur)
                    chance ^= 0b10000000;
            }
            for (int k = 1, l = 0; l < 8; l++, k <<= 1) {
                if (chance == k) {
                    type = l;
                    break;
                }
            }
            if (type != -1) break;
        }
    }
    return {0, 0};
}
int main() {
    return 0;
}