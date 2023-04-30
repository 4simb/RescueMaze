#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>
#include <cmath>
#define SIZE 50

using namespace std;

vector<vector<pair<int, int> > > smezh;
void filling();

void printCoords() {
  cout << endl;
  for (int i = 0; i < smezh.size(); ++i) {
    for (int j = 0; j < smezh[i].size(); ++j) {
       cout << "(" << smezh[i][j].first << "; " << smezh[i][j].second << ")";

       if (j == 0) cout << ": ";
       else if (j != smezh[i].size() - 1) cout << ",";
    }

    cout << endl;
  }
}

int main() {
    filling();
    printCoords();
    int s = smezh.size();
    bool used[s];
    int d[s];
    pair<int, int> way[s];

    pair<int, int> pointWayDop;
    pair<int, int> coordsRes;

    for (int i = 0; i < s; ++i) {
        used[i] = false;
        d[i] = 0;
    }

    //BFS
    int first = s - 1;

    queue<int> q;
    q.push(first);
    used[first] = true;
    pair<int, int> cord;
    int inx, usInd;
    bool nnState;

    while (!q.empty()) {
        inx = q.front();
        cord = smezh[inx][0];

        cout << "INX: " << inx << " FIRST: " << first << endl;
        //q.erase(q.begin(), q.begin() + 1);
        q.pop();

        for (int i = 1; i < smezh[inx].size(); ++i) {
            usInd = -1;

            for (int j = 0; j < s; ++j) {
                if (smezh[inx][i] == smezh[j][0]) {
                    cout << smezh[inx][i].first << " "
                    << smezh[inx][i].second << "           "
                    << smezh[j][0].first << " " << smezh[j][0].second << endl;

                    usInd = j;
                    cout << j << endl;
                    break;
                }
            }

            if (usInd == -1) {
                //q.clear();
                coordsRes.first = smezh[inx][i].first;
                coordsRes.second = smezh[inx][i].second;
                pointWayDop = cord;
                queue<int> qEmpty;
                q = qEmpty;
                break;
            } else if (!used[usInd]) {
                q.push(usInd);
                used[usInd] = true;
                d[usInd] = d[inx] + 1;
                way[usInd] = cord;
            }
        }
    }

    //for (int i = 0; i < coordsDop.size(); ++i) {
    cout << "(" << coordsRes.first << "; " << coordsRes.second << ")" << endl;
    cout << "FROM: (" << smezh[first][0].first << "; " << smezh[first][0].second << ")" << endl;
    cout << endl;
    //}

    //cout << "Shortest way" << endl;
    //for (int ii = 0; ii < s; ++ii) cout << "(" << way[ii].first << "; " << way[ii].second << "),  ";
    vector<pair<int, int> > path;
    //cout << "Shortest way: " << endl;
    //cout << "(" << coordsRes.first << "; " << coordsRes.second << "), ";
    //cout << "(" << pointWayDop.first << "; " << pointWayDop.second << "), ";

    path.push_back(coordsRes);
    path.push_back(pointWayDop);
    pair<int, int> now = pointWayDop;
    while (now != smezh[first][0]) {
        for (int i = 0; i < s; ++i) {
            if (smezh[i][0] == now) {
                //cout << "(" << way[i].first << "; " << way[i].second << "), ";
                now = way[i];
                path.push_back(way[i]);
                break;
            }
        }
    }

    reverse(path.begin(), path.end());
    cout << "Shortest way: ";
    cout << endl;

    for (int i = 0; i < path.size(); ++i) cout << "(" << path[i].first << "; " << path[i].second << "), ";


    return 0;
}

//DIRECTIONS
//-> 0
//^ 1
//<- 2
//down 3
void filling() {
    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2)); //25 25
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2 - 1)); //25 24
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2 - 1, SIZE / 2)); //24 25

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2 - 1)); //25 24
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2 - 1, SIZE / 2 - 1)); //25 25
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2)); //24 24
/*
    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2)); //26 25
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2)); //25 25
    //smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2)); //27 25

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2)); //27 25
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2)); //26 25
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2)); //28 25
    //smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, 1 + SIZE / 2)); //27 26

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2)); //28 25
    //smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2)); //26 25
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2)); //27 25
    //smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2));
*/
    /*smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 1 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 2 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(4 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 3 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(4 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(5 + SIZE / 2, 2 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(5 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(4 + SIZE / 2, 2 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 3 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, 3 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 4 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 2 + SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 4 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 3 + SIZE / 2));*/
}
