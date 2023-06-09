#include <bitset>
#include <iostream>
#include <utility>
#include <vector>
using std::bitset;
using std::cin;
using std::cout;
using std::pair;
using std::vector;
typedef pair<__uint128_t, __uint128_t> pll;
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
    int cur, flag = 0;
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
            if (mov[k].first.first) cur_pos[k].first = start[k].first;
            if (mov[k].first.second) cur_pos[k].second = start[k].second;
        }
        for (int k = 0; k < 8; k++) {
            cur_pos[k].first += mov[k].second.first;
            cur_pos[k].second += mov[k].second.second;
        }
    }
    int type = 0;
    for (int k = 1; type < 8; type++, k <<= 1)
        if (chance & k) break;
    pos ans_curpos = start[type];
    pll ans = {0, 0};
    if (len >= 5) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < len; j++) {
                ans.first &= board[ans_curpos.first][ans_curpos.second] * (1 << ((i * len + j) << 1));
                ans_curpos.first += mov[type].first.first;
                ans_curpos.second += mov[type].first.second;
            }
            if (mov[type].first.first) ans_curpos.first = start[type].first;
            if (mov[type].first.second) ans_curpos.second = start[type].second;
            ans_curpos.first += mov[type].second.first;
            ans_curpos.second += mov[type].second.second;
        }
        for (int i = 5; i < len; i++) {
            for (int j = 0; j < len; j++) {
                ans.second &= board[ans_curpos.first][ans_curpos.second] * (1 << (((i - 5) * len + j) << 1));
                ans_curpos.first += mov[type].first.first;
                ans_curpos.second += mov[type].first.second;
            }
            if (mov[type].first.first) ans_curpos.first = start[type].first;
            if (mov[type].first.second) ans_curpos.second = start[type].second;
            ans_curpos.first += mov[type].second.first;
            ans_curpos.second += mov[type].second.second;
        }
    } else {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                ans.first &= board[ans_curpos.first][ans_curpos.second] * (1 << ((i * len + j) << 1));
                ans_curpos.first += mov[type].first.first;
                ans_curpos.second += mov[type].first.second;
            }
            if (mov[type].first.first) ans_curpos.first = start[type].first;
            if (mov[type].first.second) ans_curpos.second = start[type].second;
            ans_curpos.first += mov[type].second.first;
            ans_curpos.second += mov[type].second.second;
        }
    }
    return ans;
}
int main() {
    return 0;
}