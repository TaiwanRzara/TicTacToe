#include <iostream>
#include <utility>
#include <vector>
using std::cin;
using std::cout;
using std::pair;
using std::vector;
typedef pair<unsigned long long, unsigned long long> pll;
const int len = 10;
int board[len][len];
typedef pair<int, int> pos;
typedef pair<int, int> dpos;
const dpos fdx = {1, 0}, bdx = {-1, 0}, fdy = {0, 1}, bdy = {0, -1};
const pos lu = {0, 0}, ru = {len - 1, 0}, lb = {0, len - 1}, rb = {len - 1, len - 1};
const pair<dpos, dpos> mov[] = {
    {fdx, fdy},
    {fdy, fdx},
    {bdx, fdy},
    {fdy, bdx},
    {fdx, bdy},
    {bdy, fdx},
    {bdx, bdy},
    {bdy, bdx}};
const pos start[] = {lu, lu, ru, ru, lb, lb, rb, rb};
pll hash() {
    int chance = (1 << 9) - 1;
    pos cur_pos[8];
    int cur, flag;
    for (int i = 0; i < 8; i++) cur_pos[i] = start[i];
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cur = 2;
            flag = 0;
            for (int k = 0; k < 8; k++) {
                if (!(chance & (1 << k))) continue;
                flag++;
                if (board[cur_pos[k].first][cur_pos[k].second] < cur)
                    chance &= (1 << 9) - 1 ^ ((1 << k) - 1);
                else if (board[cur_pos[k].first][cur_pos[k].second] > cur)
                    chance ^= 1 << k;
            }
            for (int k = 0; k < 8; k++) {
                cur_pos[k].first += mov[k].first.first;
                cur_pos[k].second += mov[k].first.second;
            }
            if (flag <= 1) break;
        }
        if (flag <= 1) break;
        for (int k = 0; k < 8; k++) {
            cur_pos[k].first += mov[k].second.first;
            cur_pos[k].second += mov[k].second.second;
        }
    }
}
int main() {
    return 0;
}