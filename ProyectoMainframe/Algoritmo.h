#ifndef __ALGORITMO_H__
#define __ALGORITMO_H__

#include <iostream>
#include <vector>
#include <windows.h>
#pragma comment(lib, "user32.lib") 

using namespace std;
class UnionFind {
public:
	vector<int> nNodo, p, rank, setSizes, maxSizes, pinmediato;
	int numSets;
public:
	//Constructor
	UnionFind() {
		int nNodo = { 0 };
		int p = { 0 };
		int rank = { 0 };
		int setSizes = { 0 };
		int maxSizes = { 0 };
		int pinmediato = { 0 };
		numSets = 0;
	}

	//M�todos a ser usados en el algoritmo
	void makeSet(int N);
	int findSet(int i);
	int findSetPinmediato(int i);
	bool isSameSet(int i, int j);
	void unionSet(int i, int j);
	void unionSimple(int i, int j);
	int setSize(int i);
	int numDisjointSets();
	vector <int> getPadres();
	vector <int> getChildren(int i);
};

void UnionFind::makeSet(int N) {
	numSets = N;
	rank.assign(N, 0);
	p.assign(N, 0);
	pinmediato.assign(N, 0);
	nNodo.assign(N, 0);
	for (int i = 0; i < N; i++) {
		p[i] = i;
		pinmediato[i] = i;
		nNodo[i] = i;
	}
	setSizes.assign(N, 1);
}

int UnionFind::findSet(int i) {
	return (p[i] == i) ? i : p[i] = findSet(p[i]);
}

int UnionFind::findSetPinmediato(int i) {
	return (pinmediato[i] == i) ? i : findSetPinmediato(pinmediato[i]);
}
vector <int> UnionFind::getChildren(int padreinmediato) {
	vector <int> child;
	for (int i = 0; i<pinmediato.size(); i++) {
		if (padreinmediato == pinmediato[i] && padreinmediato != i) {
			child.push_back(i);
		}
	}
	return child;
}

bool UnionFind::isSameSet(int i, int j) {
	return findSet(i) == findSet(j);
}
void UnionFind::unionSet(int i, int j) {
	unionSimple(i, j);
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

void UnionFind::unionSimple(int i, int j) {
	int xRoot = findSetPinmediato(i);    //Obtengo la raiz de la componente del v�rtice X
	int yRoot = findSetPinmediato(j);    //Obtengo la raiz de la componente del v�rtice Y
	pinmediato[xRoot] = yRoot;   //Mezclo ambos arboles o conjuntos, actualizando su padre de alguno de ellos como la raiz de otro
}

int UnionFind::setSize(int i) {
	return setSizes[findSet(i)];
}
int UnionFind::numDisjointSets() {
	return numSets;
}
vector <int> UnionFind::getPadres() {
	vector <int> padres;
	for (int i = 0; i < pinmediato.size(); i++) {
		if (pinmediato[i] == i) {
			padres.push_back(i);
		}
	}
	return padres;
}

#endif