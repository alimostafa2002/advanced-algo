#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void ttWr( vector<string> wrds, int lWidth) {
    int x = 0;
    int linm = 1;
    int ln = 0;
    cout << "line 1: ";
    while (x < wrds.size()) {
        ln += wrds[x].length();
        if (ln > lWidth) {
           linm++;
            cout << "\nline " << linm << ": " << wrds[x] << " ";
            ln = wrds[x].length() + 1;
        }
        else {
            cout << wrds[x] << " ";
            ln++;
        }
        x++;
    }
}

int main() {
    string s;
    int linewid;
    cout << "text : ";
    getline(cin, s);
    cout << "line width : ";
    cin >> linewid;
    string ter;
    istringstream iss(s);
    vector<string> x;
    while (iss >> ter) {
        x.push_back(ter);
	}
    ttWr(x, linewid);
    return 0;
}
