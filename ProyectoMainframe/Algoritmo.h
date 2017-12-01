#ifndef __ALGORITMO_H__
#define __ALGORITMO_H__

#include <iostream>
#include <vector>
#include <windows.h>
#pragma comment(lib, "user32.lib") 

using namespace std;
class UnionFind {
public:
	vector<int> p, rank, setSizes, maxSizes;
	int numSets;
public:
	//Constructor
	UnionFind() {
		int p = { 0 };
		int rank = { 0 };
		int setSizes = { 0 };
		numSets = 0;
	}

	//Métodos a ser usados en el algoritmo
	void makeSet(int N);
	int findSet(int i);
	bool isSameSet(int i, int j);
	void unionSet(int i, int j);
	int setSize(int i);
	int numDisjointSets();
	vector <int> getPadres();
};

	void UnionFind::makeSet(int N) {
		numSets = N;
		rank.assign(N, 0);
		p.assign(N, 0);
		for (int i = 0; i < N; i++)
			p[i] = i;
		setSizes.assign(N, 1);
	}

	int UnionFind::findSet(int i) {
		return (p[i] == i) ? i : p[i] = findSet(p[i]);
	}
	bool UnionFind::isSameSet(int i, int j) {
		return findSet(i) == findSet(j);
	}
	void UnionFind::unionSet(int i, int j) {
		if (!isSameSet(i, j)) {
			int x = findSet(i), y = findSet(j);
			if (rank[x] > rank[y]) {
				setSizes[findSet(x)] += setSizes[findSet(y)];
				p[y] = x;
			}
			else {
				setSizes[findSet(y)] += setSizes[findSet(x)];
				p[x] = y;
				if (rank[x] == rank[y])
					rank[y]++;
			}
			numSets--;
		}
	}
	int UnionFind::setSize(int i) {
		return setSizes[findSet(i)];
	}
	int UnionFind::numDisjointSets() {
		return numSets;
	}
	vector <int> UnionFind::getPadres() {
		vector <int> padres;
		for (int i = 0; i < p.size(); i++) {
			if (p[i] == i) {
				padres.push_back(i);
			}
		}
		return padres;
	}
	
#endif