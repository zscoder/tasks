#include "coprobber.h"
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int, int> Position;

const int MAX_N = 1001, COP = 0, ROBBER = 1;
vector<int> Neighbours[MAX_N];
int LeftToWin[2][MAX_N][MAX_N];

void markAsWinning(int turn, int cop, int robber) {
	LeftToWin[turn][cop][robber] = 0;
	queue<Position> q;
	q.push(Position(turn, cop, robber));
	//printf("mark as winning\n");
	while (!q.empty()) {
		int t, c, r;
		tie(t, c, r) = q.front();
		q.pop();
		//printf("position: turn=%d  cop=%d  robber=%d\n", t, c, r);
		
		if (t == COP) {
			for (int n : Neighbours[r])
				if (c != n && LeftToWin[ROBBER][c][n] > 0 && (--LeftToWin[ROBBER][c][n]) == 0)
					q.push(Position(ROBBER, c, n));
		} else if (t == ROBBER) {
			for (int n : Neighbours[c])
				if (r != n && LeftToWin[COP][n][r] > 0 && (--LeftToWin[COP][n][r]) == 0)
					q.push(Position(COP, n, r));
			if (LeftToWin[COP][c][r] > 0 && (--LeftToWin[COP][c][r]) == 0)
				q.push(Position(COP, c, r));
		}
	}
}

int Start(int N, int M, int U[], int V[]) {
	for (int i = 0; i < M; i++) {
		Neighbours[U[i]].push_back(V[i]);
		Neighbours[V[i]].push_back(U[i]);
	}

	for (int c = 1; c <= N; c++) {
		for (int r = 1; r <= N; r++) {
			LeftToWin[COP][c][r] = 1;
			LeftToWin[ROBBER][c][r] = Neighbours[r].size();
		}
	}
	for (int i = 1; i <= N; i++) {
		markAsWinning(COP, i, i);
		markAsWinning(ROBBER, i, i);
	}
	/*for (int t = 0; t < 2; t++) {
		for (int c = 1; c <= N; c++) {
			for (int r = 1; r <= N; r++) {
				printf("%3d", LeftToWin[t][c][r]);
			}
			printf("\n");
		}
		printf("\n");
	}*/
	bool can_win = true;	
	for (int c = 1; c <= N; c++)
		for (int r = 1; r <= N; r++)
			can_win &= LeftToWin[COP][c][r] == 0;
	return can_win;
}

int NextMove(int robber) {
	
}