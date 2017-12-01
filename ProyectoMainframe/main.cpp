#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
class UFDS {
private:
	vector<int> p, rank, setSizes;
	int numSets;
public:
	//Constructor
	UFDS() {
		int p = {0};
		int rank = { 0 };
		int setSizes = { 0 };
		numSets = 0;
	}

	void makeSet(int N) {
		numSets = N;
		rank.assign(N, 0);
		p.assign(N, 0);
		for (int i = 0; i < N; i++)
			p[i] = i;
		setSizes.assign(N, 1);
	}

	int findSet(int i) {
		return (p[i] == i) ? i : p[i] = findSet(p[i]);
	}
	bool isSameSet(int i, int j) {
		return findSet(i) == findSet(j);
	}
	void unionSet(int i, int j) {
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
	int setSize(int i) {
		return setSizes[findSet(i)];
	}
	int numDisjointSets() {
		return numSets;
	}
};

int main() {
	UFDS us;
	us.makeSet(9);
	us.unionSet(1, 2);
	us.unionSet(3, 5);
	us.unionSet(5, 2);
	us.unionSet(8, 0);
	us.unionSet(7, 3);
	us.unionSet(4, 6);

	cout << us.findSet(7);
	cout << us.findSet(2);
	std::cout<<us.findSet(3);
	cout<<us.numDisjointSets();
	return 0;
}