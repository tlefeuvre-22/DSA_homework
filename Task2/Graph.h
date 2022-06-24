#pragma once
#include <vector>
#include <set>
#include <tuple>
using namespace std;
class Graph
{
public:
	void add_edge(vector<vector<int>> adj, int u, int v);
	vector<vector<int>> adj;
	tuple<vector<int>, vector<int>> dijkstra();
	Graph(int start, int ROWS, int COLS);
	void add_obstacle(int x);
private:
	void init_graph();
	int find_min();
	vector<int> dist;
	vector<int> prev;
	set<int> q;
	int ROWS;
	int COLS;
	int start;
};