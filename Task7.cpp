#include <iostream>
#include <list>

using namespace std;

class Graph {
    int nVertices;
    list<int>* adjLis;
    bool* vis;
    list<int> fin;

    public:

        Graph(int siOfGrph) {
            nVertices = siOfGrph;
            adjLis = new list<int>[siOfGrph];
            vis = new bool[siOfGrph];
        }

        void adEd(int vx1, int vx2) {
            adjLis[vx1].push_back(vx2);
        }

        void execDF() {
            for (int m = 0; m < nVertices; m++) {
                if (!vis[m]) {
                    depthFirstSearch(m);
                }
            }
           tranGrph();
            for (int x = 0; x < nVertices; x++) {
                vis[x] = false;
            }
            int c = 1;
            list<int>::reverse_iterator y;
            for (y = fin.rbegin(); y != fin.rend(); y++) {
                if (!vis[*y]) {
                    cout << "Group #" << c << ": {";
                    transDF(*y);
                    cout << "}\n";
                    c++;
                }
            }
        }

        void depthFirstSearch(int verx) {
            vis[verx] = true;
            list<int> adjList = adjLis[verx];
            list<int>::iterator abjver;
            for (abjver = adjList.begin(); abjver != adjList.end(); ++abjver) {
                if (!vis[*abjver]) {
                    depthFirstSearch(*abjver);
                }
            }
            fin.push_back(verx);
        }

        void transDF(int ve) {
            vis[ve] = true;
            list<int> adjList = adjLis[ve];
            cout << ve << " ";
            list<int>::iterator c;
            for (c = adjList.begin(); c != adjList.end(); ++c) {
                if (!vis[*c]) {
                    transDF(*c);
                }
            }
        }

        void tranGrph() {
            list<int>* nAjLis = new list<int>[nVertices];
            for (int m = 0; m < nVertices; m++) {
                list<int>::iterator s;
                for (s = adjLis[m].begin(); s != adjLis[m].end(); ++s) {
                   nAjLis[*s].push_front(m);
                }
            }
            for (int x = 0; x < nVertices; x++) {
                adjLis[x].clear();
                list<int>::iterator s;
                for (s = nAjLis[x].begin(); s != nAjLis[x].end(); ++s) {
                    adjLis[x].push_front(*s);
                }
            }
            delete[] nAjLis;
        }
};

int main() {
    Graph m(11);
    m.adEd(0, 1);
    m.adEd(1, 2);
    m.adEd(1, 3);
    m.adEd(3, 0);
    m.adEd(3, 4);
    m.adEd(4, 5);
    m.adEd(5, 3);
    m.adEd(6, 5);
    m.adEd(6, 7);
    m.adEd(6, 8);
    m.adEd(4, 5);
    m.adEd(9, 3);
    m.adEd(4, 5);
    m.execDF();
    return 0;
}
