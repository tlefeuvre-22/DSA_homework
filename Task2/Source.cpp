#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

void draw(int ROWS, int COLS, int start, int end, int p, int wall) {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLS; x++) {
			if (x == wall && y < ROWS / 2)
				cout << "*";
			else if (y * COLS + x == p)
				cout << "x";
			else if (y * COLS + x == start)
				cout << "A";
			else if (y * COLS + x == end)
				cout << "B";
			else
				cout << "-";
		}
		cout << endl;
	}
	cout << endl;
}

void find_path(int start, int end, vector<int> prev, int ROWS, int COLS, int wall) {
	vector<int> path;
	int s = end;
	while (start != s) {
		path.push_back(prev[s]);
		s = prev[s];
	}
	path.insert(path.begin(), end);
	for (int i = path.size() - 1; i > -1; --i) {
		draw(ROWS, COLS, start, end, path[i], wall);
		sleep_for(100ms);
	}


}

int main() {
	int ROWS = 40;
	int COLS = 20;
	int xA = 0; int yA = 0;
	int xB = 0; int yB = 0;
	cout << "A column: ";
	cin >> xA;
	cout << "A row: ";
	cin >> yA;
	cout << "B column: ";
	cin >> xB;
	cout << "B row: ";
	cin >> yB;
	xA = xA - 1 % COLS;
	yA = yA - 1 % ROWS;
	xB = xB - 1 % COLS;
	yB = yB - 1 % ROWS;
	int wall = 10;
	int start = xA + yA * COLS;
	int end = xB + yB * COLS;
	Graph g(start, ROWS, COLS);
	g.add_obstacle(wall);
	auto res = g.dijkstra();
	find_path(start, end, get<1>(res), ROWS, COLS, wall);

	return 0;
}