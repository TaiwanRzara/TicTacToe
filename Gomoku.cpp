#include <bits/stdc++.h>

using namespace std;
const string BC[] = {".", "O", "X"};
const int value[] = {0, 1, 100, 10000, 1000000, 10000000};
const int mod = 1e9 + 7;
const int len = 10;
const int depth_limit = 5;
const int line = 5;
int t;
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
				if (!Board[i][j]) cntR = winnerR = 0;
				else if (winnerR != Board[i][j])
					cntR = 1, winnerR = Board[i][j];
				else
					cntR++;
				if (cntR >= line) return winnerR;
				// Judge column
				if (!Board[j][i]) cntC = winnerC = 0;
				else if (winnerC != Board[j][i])
					cntC = 1, winnerC = Board[j][i];
				else
					cntC++;
				if (cntC >= line) return winnerC;
			}
		}
		int winnerS1, cntS1, winnerS2, cntS2;
		// Judge slides   \         /
		for (int x = -len + 1; x < len; x++) {
			winnerS1 = 0, cntS1 = 0;
			winnerS2 = 0, cntS2 = 0;
			for (int j = 0; j < len; j++) {
				if (x + j < 0) continue;
				if (Board[x + j][j] == 0) cntS1 = winnerS1 = 0;
				else if (winnerS1 != Board[x + j][j])
					cntS1 = 1, winnerS1 = Board[x + j][j];
				else
					cntS1++;
				if (cntS1 >= line) return cntS1;
				if (Board[x + j][len - j - 1] == 0) cntS2 = winnerS2 = 0;
				else if (winnerS2 != Board[x + j][len - j - 1])
					cntS2 = 1, winnerS2 = Board[x + j][len - j - 1];
				else
					cntS2++;
				if (cntS2 >= line) return cntS2;
			}
		}
		return -1;
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
	int score = 0, cnt[3] = {0, 0, 0};
	for (int y = 0; y < len; y++, cnt[0] = cnt[1] = cnt[2] = 0) {
		for (int x = 0; x < line; x++) cnt[G.Board[x][y]]++;
		for (int x = line; x < len; x++) {
			if (cnt[1] == 0) score += people(2) * value[cnt[2]];
			else if (cnt[2] == 0) score += people(1) * value[cnt[1]];
			cnt[G.Board[x][y]]++;		  // add
			cnt[G.Board[x - line][y]]--;  // remove
		}
		if (cnt[1] == 0) score += people(2) * value[cnt[2]];
		else if (cnt[2] == 0) score += people(1) * value[cnt[1]];
	}
	for (int x = 0; x < len; x++, cnt[0] = cnt[1] = cnt[2] = 0) {
		for (int y = 0; y < line; y++) cnt[G.Board[x][y]]++;
		for (int y = line; y < len; y++) {
			if (cnt[1] == 0) score += people(2) * value[cnt[2]];
			else if (cnt[2] == 0) score += people(1) * value[cnt[1]];
			cnt[G.Board[x][y]]++;		  // add
			cnt[G.Board[x][y - line]]--;  // remove
		}
		if (cnt[1] == 0) score += people(2) * value[cnt[2]];
		else if (cnt[2] == 0) score += people(1) * value[cnt[1]];
	}
	int cntS1[3], cntS2[3], _cnt;
	// Judge slides   \         /
	for (int x = -len + 1; x < len; x++) {
		_cnt = cntS1[0] = cntS1[1] = cntS1[2] = 0;
		cntS2[0] = cntS2[1] = cntS2[2] = 0;
		for (int j = 0; j < len; j++) {
			if (x + j < 0 || x + j >= len) continue;
			if (_cnt < line) {
				_cnt++;
				cntS1[G.Board[x + j][j]]++;
				cntS2[G.Board[x + j][len - j - 1]]++;
				continue;
			}
			if (cntS1[1] == 0) score += people(2) * value[cntS1[2]];
			else if (cntS1[2] == 0) score += people(1) * value[cntS1[1]];
			if (cntS2[1] == 0) score += people(2) * value[cntS2[2]];
			else if (cntS2[2] == 0) score += people(1) * value[cntS2[1]];
			cntS1[G.Board[x + j][j]]++;
			cntS1[G.Board[x + j - line][j - line]]--;
			cntS2[G.Board[x + j][len - j - 1]]++;
			cntS2[G.Board[x + j - line][len + len - j - 1]]--;
		}
		if (cntS1[1] == 0) score += people(2) * value[cntS1[2]];
		else if (cntS1[2] == 0) score += people(1) * value[cntS1[1]];
		if (cntS2[1] == 0) score += people(2) * value[cntS2[2]];
		else if (cntS2[2] == 0) score += people(1) * value[cntS2[1]];
	}
	return score;
}

pair<int, int> AB(GMK &G, int player, int depth = depth_limit, int a = -mod, int b = mod) {
	int winner = G.Winner();
	if (winner >= 0)	  // game end;
		return {-1, people(winner) * people(player) * value[line]};
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

	if (time(NULL) - t > 1) cout << depth << endl, t = time(NULL);
	if (bx == -1) return {-1, a};
	return {bx + by * len, a};
}
void test() {
	GMK Gomoku;
	while (cin >> Gomoku) {
		cout << evaluate(Gomoku) << endl;
	}
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