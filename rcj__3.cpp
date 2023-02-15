#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#define SIZE 20

using namespace std;

vector<pair<short int, short int> > coords;
vector<short int> cell; //byte

bool open(short int indI, short int indJ, pair<short int, short int> cord, short int num) {
    short int i = cord.first;
    short int j = cord.second;

    if (indI == i + 1 && indJ == j) {
        if (num >= 8) return true;
        else return false;
    } else if (indI == i - 1 && indJ == j) {
        if (!(num % 4 == 0 || num % 4 == 1)) return true;
        else return false;
    } else if (indI == i && indJ == j - 1) {
        if (num % 8 > 3) return true;
        else return false;
    } else if (indI == i && indJ == j + 1) {
        if (num % 2 == 1) return true;
        else return false;
    }
}

bool neighbours(pair<short, short> p1, pair<short, short> p2) {
    return (abs(p1.first - p2.first) + abs(p1.second - p2.second)) == 1;
}

int main() {
    pair<short int, short int> pp;
    //short int dist[SIZE][SIZE];
    //bool used[SIZE][SIZE];
    //for (short int i = 0; i < SIZE; ++i) {
    //   for (int j = 0; j < SIZE; ++j) {
            //cell[i][j] = 0;
    //        used[i][j] = false;
    //        dist[i][j] = 0;
    //    }
    //}

    //cell[SIZE / 2][SIZE / 2] = 1;
    cell.push_back(1);
    pp.first = SIZE / 2;
    pp.second = SIZE / 2;
    coords.push_back(pp);

    //cell[SIZE / 2][SIZE / 2 + 1] = 7;
    cell.push_back(7);
    pp.first = SIZE / 2;
    pp.second = SIZE / 2 + 1;
    coords.push_back(pp);

    //cell[SIZE / 2][SIZE / 2 + 2] = 6;
    cell.push_back(6);
    pp.first = SIZE / 2;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    //cell[SIZE / 2 - 1][SIZE / 2 + 2] = 11;
    cell.push_back(11);
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    //cell[SIZE / 2 - 1][SIZE / 2 + 3] = 5;
    cell.push_back(5);
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 3;
    coords.push_back(pp);

    //cell[SIZE / 2 - 1][SIZE / 2 + 4] = 4;
    cell.push_back(4);
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 4;
    coords.push_back(pp);

    //cell[SIZE / 2 - 2][SIZE / 2 + 2] = 14;
    cell.push_back(14);
    pp.first = SIZE / 2 - 2;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    //cell[SIZE / 2 - 3][SIZE / 2 + 2] = 9;
    cell.push_back(9);
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    //cell[SIZE / 2 - 3][SIZE / 2 + 3] = 7;
    cell.push_back(7);
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 3;
    coords.push_back(pp);

    //cell[SIZE / 2 - 3][SIZE / 2 + 4] = 4;
    cell.push_back(4);
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 4;
    coords.push_back(pp);

    short s = coords.size();
    vector<pair<short int, short int> > canGo;
    bool uCan[4];

    short int fi, se;
    for (short int i = s - 1; i >= 0; --i) {
        fi = coords[i].first;
        se = coords[i].second;
        uCan[0] = false;
        uCan[1] = false;
        uCan[2] = false;
        uCan[3] = false;

        for (short int jj = 0; jj < s; ++jj) { //byte {
            if (jj != i) {
                if (coords[jj].first == fi - 1 && coords[jj].second == se) uCan[0] = true;
                if (coords[jj].first == fi + 1 && coords[jj].second == se) uCan[1] = true;
                if (coords[jj].first == fi && coords[jj].second == se - 1) uCan[2] = true;
                if (coords[jj].first == fi && coords[jj].second == se + 1) uCan[3] = true;
            }
        }

        if (open(fi - 1, se, coords[i], cell[i]) && !uCan[0]) coords.push_back(make_pair(fi - 1, se));
        if (open(fi + 1, se, coords[i], cell[i]) && !uCan[1]) coords.push_back(make_pair(fi + 1, se));
        if (open(fi, se - 1, coords[i], cell[i]) && !uCan[2]) coords.push_back(make_pair(fi, se - 1));
        if (open(fi, se + 1, coords[i], cell[i]) && !uCan[3]) coords.push_back(make_pair(fi, se + 1));
    }

    for (short int i = 0; i < s; ++i) {
        cout << "(" << coords[i].first << "; " << coords[i].second << "): " << cell[i] << endl;
    }

    short newS = coords.size();
    for (short int i = s; i < newS; ++i) {
        cout << "(" << coords[i].first << "; " << coords[i].second << "): " << -1 << endl;
    }

    deque<short> q;
    pair<short int, short int> way[newS];
    bool used[newS];

    for (short int i = 0; i < newS; ++i) {
        used[i] = false;
    }

    short int el = s - 1, now;
    short int fiNow, seNow;
    q.push_front(el);
    used[el] = true;

    while (!q.empty()) {
        now = q.front();
        q.pop_front();

        for (short i = 0; i < newS; ++i) {
            if (!used[i] && neighbours(coords[i], coords[now])) {
                fi = coords[i].first;
                se = coords[i].second;
                fiNow = coords[now].first;
                seNow = coords[now].second;

                if ((fiNow == fi - 1 && open(fi - 1, se, coords[i], cell[i]))
                    || (fiNow == fi + 1 && open(fi + 1, se, coords[i], cell[i]))
                    || (seNow == se - 1 && open(fi, se - 1, coords[i], cell[i]))
                    || (seNow == se + 1 && open(fi, se + 1, coords[i], cell[i]))) {

                    if (i < s) q.push_back(i);
                    cout << fiNow << ", " << seNow << endl;
                    way[i] = coords[now];
                    used[i] = true;
                }
            }
        }
    }

    for (short i = 0; i < newS; ++i) cout << used[i];
    cout << endl;

    for (short i = 0; i < newS; ++i) {
        cout << "(" << way[i].first << "; " << way[i].second << ")";
        cout << endl;
    }
    /*
    queue<pair<short int, short int> > q;
    pair<short int, short int> way[SIZE][SIZE];
    //way[coords[0].first][coords[0].second] = make_pair(-1, -1);

    used[coords[s - 1].first][coords[s - 1].second] = true;
    q.push(coords[s - 1]);
    //dist.push_back(make_pair(0, 0));
    //short int ii, jj;
    while (!q.empty()) {
        pp = q.front();
        q.pop();
        fi = pp.first;
        se = pp.second;

        for (short int i = -1; i <= 1; i++) {
            for (short int j = -1; j <= 1; j++) {
                if (abs(i - j) == 1) {
                    if (!used[fi + i][se + j] && open(fi + i, se + j, pp, cell[fi][se]) && cell[fi + i][se + j] != 0) {
                        q.push(make_pair(fi + i, se + j));
                        way[fi + i][se + j] = pp;
                        used[fi + i][se + j] = true;
                        dist[fi + i][se + j] = 1 + dist[pp.first][pp.second];
                    }
                }
            }
        }
    }

    //cout <<

    for (short int i = 0; i < SIZE; ++i) {
        for (short int j = 0; j < SIZE; ++j) {
            cout << setw(3);
            cout << dist[i][j];
            //cout << getCell(way[i][j]);
        }

        cout << endl;
    }

    vector<pair<short int, short int> > path;
    pair<short int, short int> to;
    for (short int ii = 0; ii < canGo.size(); ++ii) {
        path.clear();
        to = make_pair(canGo[ii].first, canGo[ii].second);
        path.push_back(to);
        pp = to;
        while (true) {
            pp = way[pp.first][pp.second];
            path.push_back(pp);


            if (way[pp.first][pp.second].first == 0 && way[pp.first][pp.second].second == 0) break;
        }

        reverse(path.begin(), path.end());

        cout << "SHORTEST WAY FOR (" << coords[coords.size() - 1].first << ", " << coords[coords.size() - 1].second;
        cout << "): " << getCell(coords[coords.size() - 1]) << " and (" << to.first << ", " << to.second << "): ";
        cout << getCell(to) << " is: " << endl;

        for (pair<short int, short int> noname: path) {
            cout << "(" << noname.first << ", " << noname.second << "): " << getCell(noname) << endl;
        }
    }*/
    /*pp = way[pp.first][pp.second];
            path.push_back(pp);


            if (way[pp.first][pp.second].first == 0 && way[pp.first][pp.second].second == 0) break;
        }

        reverse(path.begin(), path.end());

        cout << "SHORTEST WAY FOR (" << coords[coords.size() - 1].first << ", " << coords[coords.size() - 1].second;
        cout << "): " << getCell(coords[coords.size() - 1]) << " and (" << to.first << ", " << to.second << "): ";
        cout << getCell(to) << " is: " << endl;

        for (pair<short int, short int> noname: path) {
            cout << "(" << noname.first << ", " << noname.second << "): " << getCell(noname) << endl;
        }
    }*/

    return 0;
}
