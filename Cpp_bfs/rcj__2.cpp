#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

#define SIZE 100

using namespace std;

vector<pair<short int, short int> > coords;
short int cell[SIZE][SIZE];

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

int getCell(pair<int, int> p) {
    return cell[p.first][p.second];
}

int main() {
    pair<short int, short int> pp;
    short int dist[SIZE][SIZE];
    bool used[SIZE][SIZE];
    for (short int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cell[i][j] = 0;
            used[i][j] = false;
            dist[i][j] = 0;
        }
    }

    cell[SIZE / 2][SIZE / 2] = 1;
    pp.first = SIZE / 2;
    pp.second = SIZE / 2;
    coords.push_back(pp);

    cell[SIZE / 2][SIZE / 2 + 1] = 7;
    pp.first = SIZE / 2;
    pp.second = SIZE / 2 + 1;
    coords.push_back(pp);

    cell[SIZE / 2][SIZE / 2 + 2] = 6;
    pp.first = SIZE / 2;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    cell[SIZE / 2 - 1][SIZE / 2 + 2] = 11;
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    cell[SIZE / 2 - 1][SIZE / 2 + 3] = 5;
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 3;
    coords.push_back(pp);

    cell[SIZE / 2 - 1][SIZE / 2 + 4] = 4;
    pp.first = SIZE / 2 - 1;
    pp.second = SIZE / 2 + 4;
    coords.push_back(pp);

    cell[SIZE / 2 - 2][SIZE / 2 + 2] = 14;
    pp.first = SIZE / 2 - 2;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    cell[SIZE / 2 - 3][SIZE / 2 + 2] = 9;
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 2;
    coords.push_back(pp);

    cell[SIZE / 2 - 3][SIZE / 2 + 3] = 7;
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 3;
    coords.push_back(pp);

    cell[SIZE / 2 - 3][SIZE / 2 + 4] = 4;
    pp.first = SIZE / 2 - 3;
    pp.second = SIZE / 2 + 4;
    coords.push_back(pp);

    short s = coords.size();
    vector<pair<short int, short int> > canGo;

    short int fi, se;
    for (short int i = s - 1; i >= 0; --i) {
        fi = coords[i].first;
        se = coords[i].second;
        if (open(fi - 1, se, coords[i], cell[fi][se]) && !cell[fi - 1][se]) {
            cell[fi - 1][se] = -1;
            canGo.push_back(make_pair(fi - 1, se));
        }

        if (open(fi + 1, se, coords[i], cell[fi][se]) && !cell[fi + 1][se]) {
            cell[fi + 1][se] = -1;
            canGo.push_back(make_pair(fi + 1, se));
        }

        if (open(fi, se - 1, coords[i], cell[fi][se]) && !cell[fi][se - 1]) {
            cell[fi][se - 1] = -1;
            canGo.push_back(make_pair(fi, se - 1));
        }

        if (open(fi, se + 1, coords[i], cell[fi][se]) && !cell[fi][se + 1]) {
            cell[fi][se + 1] = -1;
            canGo.push_back(make_pair(fi, se + 1));
        }

        cout << cell[fi][se] << endl;

        /*if (cell[fi - 1][se] == -1 || cell[fi + 1][se] == -1 || cell[fi][se - 1] == -1 || cell[fi][se + 1] == -1) {
            canGo.push_back();
        }*/
    }

    for (short int i = 0; i < SIZE; ++i) {
        for (short int j = 0; j < SIZE; ++j) {
            cout << setw(7) << cell[i][j];
            if (cell[i][j] != 0) cout << "(" << i << ", " << j << ")";
        }
        cout << endl;
    }

    cout << endl;
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
    }

    return 0;
}
