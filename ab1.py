import copy
char = ['.', 'O', 'X']
value = [100, 2, 2]


class TicTacToe:
    Broad = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    Put = 0

    def __init__(self):
        for i in self.Broad:
            for j in i:
                j = 0
        self.Put = 0

    def Winner(self) -> int:
        for i in range(3):
            if (self.Broad[i][0] == self.Broad[i][1] == self.Broad[i][2]):
                return self.Broad[i][0]
            if (self.Broad[0][i] == self.Broad[1][i] == self.Broad[2][i]):
                return self.Broad[0][i]
        if (self.Broad[0][0] == self.Broad[1][1] == self.Broad[2][2] or self.Broad[2][0] == self.Broad[1][1] == self.Broad[0][2]):
            return self.Broad[1][1]
        if (self.Put == 9):
            return -1
        return 0

    def put(self, x: int, y: int, player: int) -> bool:
        if (self.Broad[x][y] != 0):
            return False
        self.Broad[x][y] = player
        self.Put += 1
        return True

    def pick(self, x: int, y: int, player: int) -> bool:
        if (self.Broad[x][y] != player):
            return False
        self.Broad[x][y] = 0
        self.Put -= 1

    def __str__(self) -> str:
        outputstring = ""
        for y in range(3):
            for x in range(3):
                outputstring += char[self.Broad[x][y]]
            outputstring += '\n'
        return outputstring

    def evaluate(self) -> int:
        score: int = 0
        Winner = self.Winner()
        if (Winner > 0):
            return 100 if Winner == 1 else -100
        for i in range(2):
            for j in range(3):
                if (self.Broad[j][i] == self.Broad[j][i+1] != 0 and self.Broad[j][2-2*(i % 2)] == 0):
                    score += (1 if self.Broad[i][j] == 1 else -1)*value[1]
                if (self.Broad[i][j] == self.Broad[i+1][j] != 0 and self.Broad[2-2*(i % 2)][j] == 0):
                    score += (1 if self.Broad[i][j] == 1 else -1)*value[1]
            if (self.Broad[i*2][0] == self.Broad[1][1] != 0 and self.Broad[2-2*(i % 2)][2] == 0):
                score += (1 if self.Broad[i][j] == 1 else -1)*value[1]
            if (self.Broad[i*2][2] == self.Broad[1][1] != 0 and self.Broad[2][2-2*(i % 2)] == 0):
                score += (1 if self.Broad[i][j] == 1 else -1)*value[1]
        for i in range(3):
            if (self.Broad[i][0] == self.Broad[i][2] != 0 and self.Broad[i][1] == 0):
                score += (1 if self.Broad[i][0] == 1 else -1)*value[2]
            if (self.Broad[0][i] == self.Broad[2][i] != 0 and self.Broad[1][i] == 0):
                score += (1 if self.Broad[1][i] == 1 else -1)*value[2]
        if (self.Broad[0][0] == self.Broad[2][2] != 0 and self.Broad[1][1] == 0):
            score += (1 if self.Broad[0][0] == 1 else -1)*value[2]
        if (self.Broad[0][2] == self.Broad[2][0] != 0 and self.Broad[1][1] == 0):
            score += (1 if self.Broad[0][2] == 1 else -1)*value[2]

        return score


def AlphaBeta(G: TicTacToe, a: int, b: int):
    Copy = copy.deepcopy(G)
    player = Copy.Put % 2+1
    s = -1
    winner = G.Winner()
    first = True
    if (winner == player):
        return [100, -1]
    elif (winner == player % 2+1):
        return [-100, -1]
    if (G.Put == 9):
        return [G.evaluate(), -1]
    for y in range(3):
        for x in range(3):
            if (Copy.Broad[x][y] != 0):
                continue
            Copy.put(x, y, player)
            temp = AlphaBeta(copy.deepcopy(Copy), int(-b), int(-a))
            temp[0] = -temp[0]
            Copy.pick(x, y, player)
            if (temp[0] > a):
                a = temp[0]
                s = x+y*3
            if (temp[0] >= b):
                b = temp[0]
                if (b > a):
                    return [temp[0], x+y*3]

    # print(f"{Copy}{a} {s} return a\n")
    return [a, s]


def AB(G: TicTacToe, depth: int, a: int, b: int, isMaxPlayer: bool):
    if (G.Put == 9):
        w = G.Winner()
        if (w == 1 and isMaxPlayer):
            return [100, -1]
        elif (w == 1):
            return [-100, -1]
        elif (w == 2 and isMaxPlayer):
            return [-100, -1]
        else:
            return [100, -1]
    if (depth == 0):
        return [G.evaluate(), -1]
    if (isMaxPlayer == True):
        for x in range(3):
            for y in range(3):
                if (G.Broad[x][y] != 0):
                    continue
                New = copy.deepcopy(G)
                New.put(x, y, 2)
                temp = AB(New, depth-1, int(a), int(b), False)
                if (temp[0] > a):
                    s = x+y*3
                    a = temp[0]
                if (a > b):
                    return [int(a), x+y*3]
        return [int(a), s]
    else:
        for x in range(3):
            for y in range(3):
                if (G.Broad[x][y] != 0):
                    continue
                New = copy.deepcopy(G)
                New.put(x, y, 1)
                temp = AB(New, depth-1, int(a), int(b), True)
                if (temp[0] < b):
                    s = x+y*3
                    b = temp[0]
                if (a > b):
                    return [int(b), x+y*3]
        return [int(b), s]


def Play_computerSecond():
    G = TicTacToe()
    while (G.Winner() == 0):
        while True:
            print(G)
            data = input("請輸入要放入位置")
            data = data.split(" ")
            if (len(data) == 2):
                if (data[0].isdigit() and data[1].isdigit()):
                    if (0 <= int(data[0]) < 3 and 0 <= int(data[1]) < 3):
                        successInput = True
                        G.put(int(data[0]), int(data[1]), 1)
                        break
            print("輸入錯誤")
        print(G)
        if (G.Winner() != 0):
            break
        temp = AlphaBeta(copy.deepcopy(G), -10000, 10000)
        print(G)
        G.put(temp[1] % 3, temp[1]//3, 2)
        print(f"電腦放({temp[1]%3},{temp[1]//3})  {temp[1]}")
        print(G)


Play_computerSecond()
