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

bool operator == (Trio& t1, Trio& t2) {
    return t1.first == t2.first && t1.second == t2.second && t1.floor == t2.floor;
}

bool operator != (Trio& t1, Trio& t2) {
    return !(t1.first == t2.first && t1.second == t2.second && t1.floor == t2.floor);
}

bool operator ^ (Trio& t1, Trio& t2) {
    return t1.first == t2.first && t1.second == t2.second;
}

bool slideDetection(Trio t1, Trio t2) {
    return t1.floor == 1 || t1.floor == 2 || t2.floor == 1 || t2.floor == 2;
}

vector<vector<Trio> > smezh;
void filling();
int countActionsGeneral(vector<Trio>, int);
int countActionsSituation(int, int);
void printCoords();
void printPair(Trio p) {
    cout << "(" << p.first << ", " << p.second << ") ";
}

int main() {
    filling();
    printCoords();
    int s = smezh.size();
    bool used[s];
    int d[s];
    Trio way[s];

    vector<Trio> pointWayDop;
    vector<Trio> coordsRes;
    vector<int> distsMin;

    for (int i = 0; i < s; ++i) {
        way[i] = Trio(0, 0, 0);
        used[i] = false;
        d[i] = 0;
    }

    //BFS
    int first = s - 1;

    queue<int> q;
    q.push(first);
    used[first] = true;
    Trio cord;
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
                if (smezh[inx][i] == smezh[j][0]
                    || (smezh[inx][i] ^ smezh[j][0] && slideDetection(smezh[inx][i], smezh[j][0]))) {
                    usInd = j;
                    break;
                }
            }

            if (usInd == -1) {
                if (distsMin.size() == 0) {
                    cout << "YES" << endl;
                    distsMin.push_back(d[inx] + 1);
                    coordsRes.push_back(smezh[inx][i]);
                    pointWayDop.push_back(cord);
                } else {//if (d[inx] + 1 <= distsMin[0]) {
                    //cout << "WOW" << endl;
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
    vector<vector<Trio> > path;
    int min = -1, minInd;

    for (int i = 0; i < distsMin.size(); ++i) {
        cout << "IN CYCLE" << endl;
        path.push_back(vector<Trio>());

        path[i].push_back(coordsRes[i]);
        path[i].push_back(pointWayDop[i]);

        Trio now = pointWayDop[i];
        while (now != smezh[first][0]) {
            printPair(now);
            cout << endl;
            for (int ii = 0; ii < s; ++ii) {
                if (smezh[ii][0] == now) {
                    printPair(now);
                    cout << endl;
                    now = way[ii];
                    path[i].push_back(way[ii]);
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

int countActionsGeneral(vector<Trio> path, int dir) {
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
   //cout << endl;
   for (int i = 0; i < smezh.size(); ++i) {
     for (int j = 0; j < smezh[i].size(); ++j) {
       //cout << "(" << smezh[i][j].first << "; " << smezh[i][j].second << ")";
        printPair(smezh[i][j]);

        if (j == 0) cout << ": ";
        else if (j != smezh[i].size() - 1) cout << ", ";
    }

    cout << endl;
  }
}

// 0 -- FIRST FLOOR
// 1 -- SLIDE_UP
// 2 -- SLIDE_DOWN
// 128 -- SECOND FLOOR

void filling() {
    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(25, 25, 0));
    smezh[smezh.size() - 1].push_back(Trio(26, 25, 0));
    smezh[smezh.size() - 1].push_back(Trio(25, 24, 0));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(24, 25, 1)); //1
    smezh[smezh.size() - 1].push_back(Trio(23, 25, 1));
    smezh[smezh.size() - 1].push_back(Trio(25, 25, 1));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(23, 25, 128)); //128
    smezh[smezh.size() - 1].push_back(Trio(22, 25, 128));
    smezh[smezh.size() - 1].push_back(Trio(24, 25, 128));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(22, 25, 128)); //128
    smezh[smezh.size() - 1].push_back(Trio(21, 25, 128));
    smezh[smezh.size() - 1].push_back(Trio(23, 25, 128));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(21, 25, 128)); //128
    smezh[smezh.size() - 1].push_back(Trio(22, 25, 128));
    smezh[smezh.size() - 1].push_back(Trio(21, 26, 128));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(21, 26, 2)); //2
    smezh[smezh.size() - 1].push_back(Trio(21, 25, 2));
    smezh[smezh.size() - 1].push_back(Trio(21, 27, 2));

    smezh.push_back(vector<Trio>());
    smezh[smezh.size() - 1].push_back(Trio(21, 27, 0));
    smezh[smezh.size() - 1].push_back(Trio(21, 26, 0));
    //smezh[smezh.size() - 1].push_back(Trio(21, 28, 0));
}
