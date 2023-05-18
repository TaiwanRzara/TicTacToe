#include <bits/stdc++.h>

using namespace std;
const string BC[] = {".", "O", "X"};
const int value[] = {1000, 1, 11, 121, 1331};
const int mod = 1e9 + 7;
const int len = 4;
const int depth_limit = 10000;
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

struct TTT {
	int Board[len][len] = {0};
	int filled = 0;
	TTT() {
		for (auto &x : Board)
			for (int &b : x) b = 0;
		filled = 0;
		return;
	}
	int Winner() {
		int winner;
		for (int y = 0; y < len; y++) {
			winner = Board[0][y];
			for (int x = 1; x < len && winner; x++) {
				if (winner != Board[x][y]) winner = 0;
			}
			if (winner) return winner;
		}
		for (int x = 0; x < len; x++) {
			winner = Board[x][0];
			for (int y = 1; y < len && winner; y++) {
				if (winner != Board[x][y]) winner = 0;
			}
			if (winner) return winner;
		}
		winner = Board[0][0];
		for (int s = 1; s < len && winner; s++) {
			if (winner != Board[s][s]) winner = 0;
		}
		if (winner) return winner;
		winner = Board[len - 1][0];
		for (int s = 1; s < len; s++) {
			if (winner != Board[len - 1 - s][s]) winner = 0;
		}
		if (winner) return winner;
		if (filled == len * len) return 0;
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
};
ostream &operator<<(ostream &s, const TTT &T) {
	string str = "";
	for (int y = 0; y < len; y++) {
		for (int x = 0; x < len; x++) {
			str += BC[T.Board[x][y]];
		}
		str += "\n";
	}
	s << str;
	return s;
}
istream &operator>>(istream &s, TTT &T) {
	const int len2 = len * len;
	char w[len2];
	for (char &i : w) s >> i;
	for (int p = 0; p < len2; p++) {
		if (w[p] == 'O') T.put(p % len, p / len, 1);
		else if (w[p] == 'X') T.put(p % len, p / len, 2);
		else if (w[p] == '.')
			;
		else {
			ERROR();
			return s;
		}
	}
	return s;
}
inline int evaluate(TTT T) {
	int score = 0, winner = T.Winner();
	if (winner >= 0) return value[0] * people(winner);
	else if (winner == 0) return 0;
	for (int count[2] = {0, 0}, y = 0; y < len; y++, count[0] = count[1] = 0) {
		for (int x = 0; x < len; x++) {
			if (T.Board[x][y]) count[T.Board[x][y] & 1]++;
		}
		if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
			score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
	}
	for (int count[2] = {0, 0}, x = 0; x < len; x++, count[0] = count[1] = 0) {
		for (int y = 0; y < len; y++) {
			if (T.Board[x][y]) count[T.Board[x][y] & 1]++;
		}
		if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
			score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
	}
	int count[2] = {0, 0};
	if (T.Board[0][0]) count[T.Board[0][0] & 1]++;
	if (T.Board[1][1]) count[T.Board[1][1] & 1]++;
	if (T.Board[2][2]) count[T.Board[2][2] & 1]++;
	if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
		score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);

	count[0] = count[1] = 0;
	if (T.Board[0][2]) count[T.Board[0][2] & 1]++;
	if (T.Board[1][1]) count[T.Board[1][1] & 1]++;
	if (T.Board[2][0]) count[T.Board[2][0] & 1]++;
	if ((count[0] == 0 || count[1] == 0) && count[0] + count[1])
		score += value[max(count[0], count[1])] * (count[0] ? -1 : 1);
	if (score > value[0]) score = value[0];

	return score;
}

pair<int, int> AB(TTT &T, int player, int depth = depth_limit, int a = -mod, int b = mod) {
	int winner = T.Winner();
	if (winner >= 0)	  // game end;
		return {-1, people(winner) * people(player) * value[0]};
	else if (depth == 1)  // lowest depth
		return {-1, evaluate(T) * people(player)};
	int bx = -1, by = -1, score = 0;
	for (int y = 0; y < len; y++)
		for (int x = 0; x < len; x++) {
			if (T.Board[x][y]) continue;
			T.put(x, y, player);
			score = -AB(T, change_player(player), depth - 1, -b, -a).second;
			if (T.pick(x, y, player))
				;
			if (score >= b) return {-1, b};
			if (score > a) a = score, bx = x, by = y;
		}
	if (bx == -1) return {-1, a};
	return {bx + by * len, a};
}

void play() {
	TTT TicTacToe;
	int mode, move, mx, my, len2 = len * len;
	cout << "please input [0:player&player,1:computer&player,2:player&computer] ";
	cin >> mode;
	for (int x, y, player = 1; TicTacToe.filled < len2; player = change_player(player)) {
		cout << TicTacToe << endl;
		if (TicTacToe.Winner() >= 0) {
			cout << "game end" << endl;
			break;
		}
		cout << player << endl;
		if (player & mode) {
			move = AB(TicTacToe, player).first;
			if (move == -1) cout << "ERROR\n";
			if (!TicTacToe.put(move % len, move / len, player)) cout << "ERROR" << endl;
		} else {
			cout << "player " << BC[player] << " input" << endl;
			cin >> mx >> my;
			if (mx == -1 && my == -1) return;
			while (!TicTacToe.put(mx, my, player)) {
				cout << "ERROR please input again" << endl;
				cin >> mx >> my;
			}
		}
	}
	cout << "============================\n";
	cout << TicTacToe;
	cout << "Winner" << TicTacToe.Winner() << endl;
}