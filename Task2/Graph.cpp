#include "Graph.h"
#include <List>
#include <limits>
#include <algorithm>
void Graph::add_edge(vector<vector<int>> adj, int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

Graph::Graph(int start, int ROWS, int COLS) {
	this->COLS = COLS;
	this->ROWS = ROWS;
	this->start = start;
	dist = vector<int>(COLS * ROWS);
	for (int i = 0; i < COLS * ROWS; i++) {
		dist[i] = numeric_limits<int>::max();;
		q.insert(i);
	}
	dist[start] = 0;
	init_graph();
}

void Graph::init_graph() {

	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLS; i++) {
			auto l = vector<int>();
			adj.push_back(l);
			if (i > 0)
				adj[i + j * COLS].push_back(i + j * COLS - 1);
			if (i + 1 < COLS)
				adj[i + j * COLS].push_back(i + j * COLS + 1);
			if (i + (j - 1) * COLS > 0)
				adj[i + j * COLS].push_back(i + (j - 1) * COLS);
			if (i + (j + 1) * COLS < COLS * ROWS)
				adj[i + j * COLS].push_back(i + (j + 1) * COLS);
		}
	}
}
void clear(vector<int>& v, int x) {
	vector<int>::iterator position = std::find(v.begin(), v.end(), x);
	if (position != v.end())
		v.erase(position);
}
void Graph::add_obstacle(int x) {
	for (int j = 0; j < ROWS / 2; j++) {
		if (x > 0)
			clear(adj[x - 1 + j * COLS], x);
		if (x + 1 < COLS)
			clear(adj[x + 1 + j * COLS], x);
		if (x + (j - 1) * COLS > 0)
			clear(adj[x + (j - 1) * COLS], x);
		if (x + (j + 1) * COLS < COLS * ROWS)
			clear(adj[x + (j + 1) * COLS], x);
		q.erase(x + j * COLS);
	}
}
int  Graph::find_min() {
	int min = numeric_limits<int>::max();;
	int node = -1;
	for (auto it = q.begin(); it != q.end(); ++it) {
		if (dist[*it] < min) {
			min = dist[*it];
			node = *it;
		}
	}
	return node;
}

tuple<vector<int>, vector<int>> Graph::dijkstra() {
	prev = vector<int>(ROWS * COLS);
	while (!q.empty()) {
		int s1 = find_min();
		q.erase(s1);
		for (auto it = adj[s1].begin(); it != adj[s1].end(); ++it) {
			if (dist[s1] > dist[*it] + 1)
			{
				dist[*it] = dist[s1] + 1;
				prev[*it] = s1;
			}
		}
	}
	return { dist, prev };
}
