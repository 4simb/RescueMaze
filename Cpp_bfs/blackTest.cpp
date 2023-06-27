#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <cmath>

#define SIZE 50

using namespace std;

class Trio {
public:
    int first;
    int second;
    int floor;

    Trio(int first, int second, int floor) {
        this->first = first;
        this->second = second;
        this->floor = floor;
    }

    Trio() {
        this->first = 0;
        this->second = 0;
        this->floor = 0;
    }
};

vector<vector<Trio> > smezh;

void filling();

int main() {
    int floors = 0;

    vector<int> smezhNum;
    pair<int, int> p = make_pair(24, 24);
    filling();

    for (int i = 0; i < smezh.size(); ++i) {
        for (int j = 1; j < smezh[i].size(); ++j) {
            if (smezh[i][j].first == p.first && smezh[i][j].second == p.second
                && (smezh[i][j].floor == floors || smezh[i][j].floor == 1 || smezh[i][j].floor == 2)) {
                smezhNum.push_back(i);
                cout << j << endl;
                break;
            }
        }
    }

    for (int j = 0; j < smezhNum.size(); ++j) {
      cout << "YES" << endl;
      vector<pair<int, int> > intermediate;
      int jj = smezhNum[j];


      int s = smezh[jj].size() - 1;
      //cout << "GET: ";

      //cout << smezhNum[]
      //cout << smezh[1][0].first << " " << smezh[1][0].second << endl;
      //for (int ii = 0; ii < s + 1; ++ii) {
      //  cout << smezh[jj][ii].first << ", " << smezh[jj][ii].second << "  ";
      //}
      //cout << endl;

      while (s >= 1) {
        //cout << s << endl;
        //cout << p.first << " " << p.second << "        " << smezh[j][s].first << " " << smezh[j][s].second << endl;
        if (p.first == smezh[jj][s].first && p.second == smezh[jj][s].second) {
          smezh[jj].pop_back();
          break;
        } else intermediate.push_back(make_pair(smezh[jj][s].first, smezh[jj][s].second));

        smezh[jj].pop_back();
        s = smezh[jj].size() - 1;
      }

      for (int i = 0; i < intermediate.size(); ++i) {
        smezh[jj].push_back(Trio(intermediate[i].first, intermediate[i].second, floors));
      }
    }

    for (int i = 0; i < smezh.size(); ++i) {
        for (int j = 0; j < smezh[i].size(); ++j) {
            cout << smezh[i][j].first << " " << smezh[i][j].second << ", ";
        }

        cout << endl;
    }

    return 0;
}


//                     (25; 25)   (26; 25)
//         (24; 24)    (25; 24)   (26; 24)
//                     (25; 23)   (26; 23)

void filling() {
    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(25, 25, 0));
    smezh[smezh.size() - 1].push_back(Trio(26, 25, 0));
    smezh[smezh.size() - 1].push_back(Trio(24, 25, 0)); //FOR DELETE

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(24, 25, 0)); //1
    smezh[smezh.size() - 1].push_back(Trio(24, 24, 0));
    smezh[smezh.size() - 1].push_back(Trio(25, 25, 0));

/*
    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(25, 23, 0)); //1
    smezh[smezh.size() - 1].push_back(Trio(25, 24, 0));
    smezh[smezh.size() - 1].push_back(Trio(26, 23, 0));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(26, 24, 0)); //1
    smezh[smezh.size() - 1].push_back(Trio(25, 24, 0));

*/
}

