//#include "Arduino_AVRSTL.h"
#include <Streaming.h>
#include "L.h"
#include "Queue.h"
#define SIZE 20

//using namespace std;

class pair {
public:
  int first, second;

  pair() {
    first = 0;
    second = 0;
  }

  pair(int a, int b) {
    first = a;
    second = b;
  }

  bool isEqual(pair p1) {
    return this->first == p1.first && this->second == p1.second;
  }
};

Vector<Vector<pair> > smezh;
void filling() {
    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(1 + SIZE / 2, SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(1 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(1 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(2 + SIZE / 2, SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(2 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(1 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    //Serial << "a";
    //Serial << smezh[smezh.size() - 1].capacity();
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, SIZE / 2));
    //Serial << "b";
    //Serial << smezh[smezh.size() - 1].capacity();
    smezh[smezh.size() - 1].push_back(pair(2 + SIZE / 2, SIZE / 2));
    //Serial << "c";
    //Serial << smezh[smezh.size() - 1].capacity();
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 1 + SIZE / 2));
    
    //Serial << "d";
    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 2 + SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(4 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 1 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 3 + SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(4 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(5 + SIZE / 2, 2 + SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(5 + SIZE / 2, 2 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(4 + SIZE / 2, 2 + SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 3 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(2 + SIZE / 2, 3 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 4 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 2 + SIZE / 2));

    //Serial << smezh.size() - 1;

    smezh.push_back(Vector<pair>());
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 4 + SIZE / 2));
    smezh[smezh.size() - 1].push_back(pair(3 + SIZE / 2, 3 + SIZE / 2));

    //Serial << smezh.size() - 1;
}

void setup() {
  Serial.begin(115200);
  //Serial << "OMG";
  
    filling();
    Serial << "CRINGE";
    int s = smezh.size();
    bool used[s];
    int d[s];
    pair way[s];

    Vector<int> distDop;
    Vector<pair> wayDop;
    Vector<pair> coordsDop;

    for (int i = 0; i < s; ++i) {
        used[i] = false;
        d[i] = 0;
    }

    //BFS
    //Vector<int> q;
    Queue<int> q;
    q.push(0);
    used[0] = true;
    pair cord;
    int inx, usInd;
    bool nnState;

    while (q.count() != 0) {
        inx = q.front();
        cord = smezh[inx][0];
        //q.erase(q.begin(), q.begin() + 1);
        q.pop();

        for (int i = 1; i < smezh[inx].size(); ++i) {
            usInd = -1;

            for (int j = 0; j < s; ++j) {
                if (smezh[inx][i].isEqual(smezh[j][0])) {
                    usInd = j;
                    break;
                }
            }

            if (usInd == -1) {
                nnState = false;

                for (int ii = 0; ii < coordsDop.size(); ++ii) {
                    if (coordsDop[ii].isEqual(smezh[inx][i])) {
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
                q.push(usInd);
                used[usInd] = true;
                d[usInd] = d[inx] + 1;
                way[usInd] = cord;
            }
        }
    }

    for (int i = 0; i < coordsDop.size(); ++i) {
        //Serial.begin()
        Serial << "(" << coordsDop[i].first << "; " << coordsDop[i].second << ")";
        Serial.println();
        Serial << "FROM: (" << wayDop[i].first << "; " << wayDop[i].second << ")";
        Serial.println();
        Serial << "DIST: " << distDop[i];
        Serial.println();
        Serial.println();
    }

    Vector<pair> path;
    pair to;
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
                if (path[path.size() - 1].isEqual(smezh[j][0])) {
                    path.push_back(way[j]);
                    jOld = j;
                    st = true;
                    break;
                }
            }
            
            if (!st) {
                path.pop_back();
                break;
            }
        }

        //reverse(path.begin(), path.end());

        Serial << "NORMAL Shortest way to (" << to.first << "; " << to.second << ") from (" << smezh[0][0].first << "; " << smezh[0][0].second << "):  ";
        for (int ii = 0; ii < path.size(); ++ii) Serial << "(" << path[ii].first << "; " << path[ii].second << ") ";
        Serial.println();

        /*path.reverse();
        Serial << "CRINGE Shortest way to (" << to.first << "; " << to.second << ") from (" << smezh[0][0].first << "; " << smezh[0][0].second << "):  ";
        for (int ii = 0; ii < path.size(); ++ii) Serial << "(" << path[ii].first << "; " << path[ii].second << ") ";
        Serial.println();
        Serial.println();*/
    }
}

void loop() {
}
