#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#define SIZE 20

using namespace std;

vector<vector<pair<int, int> > > smezh;
void filling();

int main() {
    filling();
    int s = smezh.size();
    bool used[s];
    int d[s];
    pair<int, int> way[s];

    vector<int> distDop;
    vector<pair<int, int> > wayDop;
    vector<pair<int, int> > coordsDop;

    for (int i = 0; i < s; ++i) {
        used[i] = false;
        d[i] = 0;
    }

    //BFS
    vector<int> q;
    q.push_back(0);
    used[0] = true;
    pair<int, int> cord;
    int inx, usInd;
    bool nnState;

    while (!q.empty()) {
        inx = q[0];
        cord = smezh[inx][0];
        q.erase(q.begin(), q.begin() + 1);

        for (int i = 1; i < smezh[inx].size(); ++i) {
            usInd = -1;

            for (int j = 0; j < s; ++j) {
                if (smezh[inx][i] == smezh[j][0]) {
                    usInd = j;
                    break;
                }
            }

            if (usInd == -1) {
                nnState = false;

                for (int ii = 0; ii < coordsDop.size(); ++ii) {
                    if (coordsDop[ii] == smezh[inx][i]) {
                        nnState = true;
                        break;
                    }
                }

                if (!nnState) {
                    coordsDop.push_back(smezh[inx][i]);
                    distDop.push_back(d[inx] + 1);
                    wayDop.push_back(cord);
                }
            } else if (!used[usInd]) {
                q.push_back(usInd);
                used[usInd] = true;
                d[usInd] = d[inx] + 1;
                way[usInd] = cord;
            }
        }
    }

    for (int i = 0; i < coordsDop.size(); ++i) {
        cout << "(" << coordsDop[i].first << "; " << coordsDop[i].second << ")" << endl;
        cout << "FROM: (" << wayDop[i].first << "; " << wayDop[i].second << ")" << endl;
        cout << "DIST: " << distDop[i] << endl;
        cout << endl;
    }

    vector<pair<int, int> > path;
    pair<int, int> to;
    bool st;
    int jOld;

    for (int i = 0; i < coordsDop.size(); ++i) {
        path.clear();
        to = coordsDop[i];
        path.push_back(to);
        path.push_back(wayDop[i]);

        while (true) {
            st = false;

            for (int j = 0; j < s; ++j) {
                if (path[path.size() - 1] == smezh[j][0]) {
                    path.push_back(way[j]);
                    jOld = j;
                    st = true;
                    break;
                }
            }

            //} else {
            //    if (jOld - 1 >= 0 && path[path.size() - 1] == smezh[jOld - 1][0]) {
            //        path.push_back(way[jOld - 1]);
            //        jOld--;
            //    } else {
            //        break;
            //    }
            //}

            if (!st) {
                path.pop_back();
                break;
            }
        }

        reverse(path.begin(), path.end());

        cout << "Shortest way to (" << to.first << "; " << to.second << ") from (" << smezh[0][0].first << "; " << smezh[0][0].second << "): ";
        for (int ii = 0; ii < path.size(); ++ii) cout << "(" << path[ii].first << "; " << path[ii].second << ") ";
        cout << endl;
    }

    return 0;
}

void filling() {
    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
    smezh[smezh.size() - 1].push_back(make_pair(2 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(1 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, SIZE / 2));

    smezh.push_back(vector<pair<int, int> >());
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
    smezh[smezh.size() - 1].push_back(make_pair(3 + SIZE / 2, 3 + SIZE / 2));
}
