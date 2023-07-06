#ifndef DSU_H
#define DSU_H

#include <vector>
using namespace std;

class DisjointSet{
    public:
        vector<int> parent;
        vector<int> rank;
        DisjointSet() {};
        DisjointSet(int);
        int FindSet(int);
        void Union(int, int);
};

#endif