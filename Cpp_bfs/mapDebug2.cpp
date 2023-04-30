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
int countActionsGeneral(vector<pair<int, int> >, int);
int countActionsSituation(int, int);
void printCoords();


int main() {
    filling();
    printCoords();
    int s = smezh.size();
    bool used[s];
    int d[s];
    pair<int, int> way[s];

    vector<pair<int, int> > pointWayDop;
    vector<pair<int, int> > coordsRes;
    vector<int> distsMin;

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
        cout << cord.first << " " << cord.second << endl;
        //q.erase(q.begin(), q.begin() + 1);
        q.pop();

        for (int i = 1; i < smezh[inx].size(); ++i) {
            usInd = -1;

            for (int j = 0; j < s; ++j) {
                if (smezh[inx][i] == smezh[j][0]) {
                    /*cout << smezh[inx][i].first << " "
                    << smezh[inx][i].second << "           "
                    << smezh[j][0].first << " " << smezh[j][0].second << endl;
*/
                    usInd = j;
                    //cout << j << endl;
                    break;
                }
            }

            if (usInd == -1) {
                cout << "YES" << endl;
                if (distsMin.size() == 0) {
                    distsMin.push_back(d[inx] + 1);
                    coordsRes.push_back(smezh[inx][i]);
                    pointWayDop.push_back(cord);
                } else if (d[inx] + 1 <= distsMin[0]) {
                    distsMin.push_back(d[inx] + 1);
                    coordsRes.push_back(smezh[inx][i]);
                    pointWayDop.push_back(cord);
                }

                //cout << "YES" << endl;
            } else if (!used[usInd]) {
                q.push(usInd);
                used[usInd] = true;
                d[usInd] = d[inx] + 1;
                way[usInd] = cord;
            }
        }
    }

    for (int i = 0; i < distsMin.size(); ++i) {
        cout << "(" << coordsRes[i].first << ", " << coordsRes[i].second << "): ";
        cout << distsMin[i] << endl;
    }

    //DIRECTIONS
    //-> 0
    //^ 1
    //<- 2
    //down 3

//               (25; 24)
//    (24; 25)   (25; 25)
    int robotDirection = 2;
    vector<vector<pair<int, int> > > path;
    int min = -1, minInd;

    for (int i = 0; i < distsMin.size(); ++i) {
        path.push_back(vector<pair<int, int> >());

        path[i].push_back(coordsRes[i]);
        path[i].push_back(pointWayDop[i]);

        pair<int, int> now = pointWayDop[i];
        while (now != smezh[first][0]) {
            for (int i = 0; i < s; ++i) {
                if (smezh[i][0] == now) {
                    now = way[i];
                    path[i].push_back(way[i]);
                    break;
                }
            }
        }

        reverse(path[i].begin(), path[i].end());
        //cout << endl << "Shortest way: ";
        //cout << endl;

        //for (int ii = 0; ii < path[i].size(); ++ii) cout << "(" << path[i][ii].first << "; " << path[i][ii].second << "), ";

        int n = countActionsGeneral(path[i], robotDirection);
        if (n < min || min == -1) {
            min = n;
            minInd = i;
        }
    }

    cout << "Shortest way" << endl;
    for (int i = 0; i < path[minInd].size(); ++i) {
        cout << "(" << path[minInd][i].first << ", " << path[minInd][i].second << "); ";
    }

    //cout << "Shortest way" << endl;
    //for (int ii = 0; ii < s; ++ii) cout << "(" << way[ii].first << "; " << way[ii].second << "),  ";
    //cout << "Shortest way: " << endl;
    //cout << "(" << coordsRes.first << "; " << coordsRes.second << "), ";
    //cout << "(" << pointWayDop.first << "; " << pointWayDop.second << "), ";


    return 0;
}

int countActionsSituation(int to, int from) {
    int count = 1;

    if (abs(to - from) == 1 || abs(from - to) == 3) ++count;
    else if (abs(to - from) == 2) count += 2;

    return count;
}

int countActionsGeneral(vector<pair<int, int> > path, int dir) {
    int param, count = 0;

    for (int i = 1; i < path.size(); ++i) {
        if (path[i].first == path[i - 1].first && path[i].second == path[i - 1].second + 1) {
            param = 3;
        } else if (path[i].first == path[i - 1].first && path[i].second == path[i - 1].second - 1) {
            param = 1;
        } else if (path[i].first == path[i - 1].first + 1 && path[i].second == path[i - 1].second) {
            param = 0;
        } else if (path[i].first == path[i - 1].first - 1 && path[i].second == path[i - 1].second) {
            param = 2;
        }

        count += countActionsSituation(param, dir);
        dir = param;
    }

    return count;
}

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

void filling() {
/*    (25; 25): (24; 25)
(24; 25): (25; 25),(24; 24),(23; 25)
(23; 25): (24; 25),(23; 24)
(23; 24): (23; 25),(23; 23)
(23; 23): (23; 24),(24; 23),(23; 22)
(23; 22): (23; 23),(23; 21)
(23; 21): (23; 22),(24; 21)
(24; 21): (23; 21)*/

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(25, 25));
    smezh[smezh.size() - 1].push_back(make_pair(24, 25));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(24, 25));
    smezh[smezh.size() - 1].push_back(make_pair(25, 25));
    smezh[smezh.size() - 1].push_back(make_pair(24, 24));
    smezh[smezh.size() - 1].push_back(make_pair(23, 25));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(23, 25));
    smezh[smezh.size() - 1].push_back(make_pair(24, 25));
    smezh[smezh.size() - 1].push_back(make_pair(23, 24));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(23, 24));
    smezh[smezh.size() - 1].push_back(make_pair(23, 23));
    smezh[smezh.size() - 1].push_back(make_pair(23, 22));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(23, 23));
    smezh[smezh.size() - 1].push_back(make_pair(23, 24));
    smezh[smezh.size() - 1].push_back(make_pair(24, 23));
    smezh[smezh.size() - 1].push_back(make_pair(23, 22));

    /*(23; 22): (23; 23),(23; 21)
    (23; 21): (23; 22),(24; 21)
    (24; 21): (23; 21)*/

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(23, 22));
    smezh[smezh.size() - 1].push_back(make_pair(23, 23));
    smezh[smezh.size() - 1].push_back(make_pair(23, 21));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(23, 21));
    smezh[smezh.size() - 1].push_back(make_pair(23, 22));
    smezh[smezh.size() - 1].push_back(make_pair(24, 21));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(24, 21));
    smezh[smezh.size() - 1].push_back(make_pair(23, 21));
    //smezh.push_back(vector<pair<int, int> >());
    //smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2 - 1)); //25 24
    //smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2 - 1, SIZE / 2 - 1)); //25 25
    //smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2)); //24 24
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
