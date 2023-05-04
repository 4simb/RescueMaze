/*
  ERROR
  (25; 25): (25; 24),(24; 25)
  (25; 24): (24; 24),(25; 25)
*/

void bfs() {
  printCoords();
  Serial << endl;
  int s = smezh.size();
  Serial << "BFS_START BFS_START BFS_START BFS_START BFS_START " << s << endl;
  //int s = smezh.size();
  bool used[s];
  int d[s];
  Trio way[s];

  Vector<Trio> pointWayDop;
  Vector<Trio> coordsRes;
  Vector<int> distsMin;

  distsMin.clear();
  for (int i = 0; i < s; ++i) {
    way[i] = Trio(0, 0, 0);
    used[i] = false;
    d[i] = 0;
  }

  //BFS
  int first = s - 1;
  Serial << " FIRST: " << first << endl;
  Queue<int> q;
  q.push(first);
  Serial << "FRONT : " << q.peek() << endl;
  used[first] = true;
  Trio cord;
  int inx, usInd;
  bool nnState;

  while (q.count() != 0) {
    inx = q.peek();
    cord = smezh[inx][0];
    //q.erase(q.begin(), q.begin() + 1);

    //Serial << "INX: " << inx << endl;
    Serial << "INX: " << inx << " FIRST: " << first << endl;
    q.pop();

    for (int i = 1; i < smezh[inx].size(); ++i) {
      usInd = -1;
      Serial << "cringe" << endl;

      for (int j = 0; j < s; ++j) {
        if (smezh[inx][i].absEqual(smezh[j][0])
            ||  (smezh[inx][i].coordsEqual(smezh[j][0]) && smezh[inx][i].slideDetection(smezh[j][0]))) {
          Serial << "Base" << endl;
          Serial << smezh[inx][i].first << " " << smezh[inx][i].second << "           " << smezh[j][0].first << " " << smezh[j][0].second << endl;
          usInd = j;

          Serial << j << endl;
          break;
        }
      }

      if (usInd == -1) {
        Serial << "usInd == -1" << endl;
        if (distsMin.size() == 0) {
          Serial << "SIZE = 0" << endl;
          distsMin.push_back(d[inx] + 1);
          coordsRes.push_back(smezh[inx][i]);
          pointWayDop.push_back(cord);
        } else if (d[inx] + 1 <= distsMin[0]) {
          Serial << "d[inx] + 1 <= distsMin[0]" << endl;
          distsMin.push_back(d[inx] + 1);
          coordsRes.push_back(smezh[inx][i]);
          pointWayDop.push_back(cord);
        }

      } else if (!used[usInd]) {
        q.push(usInd);
        used[usInd] = true;
        d[usInd] = d[inx] + 1;
        way[usInd] = cord;
      }
    }
  }

  Serial << "END_Cycle" << endl;
  for (int i = 0; i < distsMin.size(); ++i) {
    Serial << "(" << coordsRes[i].first << ", " << coordsRes[i].second << "): ";
    Serial << distsMin[i] << endl;
  }
  Vector<Vector<Trio> > path;

  int min = -1, minInd;

  for (int i = 0; i < distsMin.size(); ++i) {
    Serial << "Cycle I" << endl;
    path.push_back(Vector<Trio>());

    path[i].push_back(coordsRes[i]);
    path[i].push_back(pointWayDop[i]);
    Trio now = pointWayDop[i];

    while (!now.absEqual(smezh[first][0])) {
      for (int ind = 0; ind < s; ++ind) {
        if (smezh[ind][0].absEqual(now)) {
          //Serial << "(" << way[i].first << "; " << way[i].second << "), ";
          now = way[ind];
          path[i].push_back(way[ind]);
          break;
        }
      }
    }

    Serial << endl;
    Serial << "REVERSE" << endl;
    path[i].reverse();
    Serial << "SW: ";

    for (int ii = 0; ii < path[i].size(); ++ii) Serial << "(" << path[i][ii].first << "; " << path[i][ii].second << "), ";
    Serial << endl;

    //int n = countActionsGeneral(path[i], robotDirection);
    int parametr = 0, counter = 0, dirNN = robotDirection;
    for (int ii = 1; ii < path[i].size(); ++ii) {
      if (path[i][ii].first == path[i][ii - 1].first && path[i][ii].second == path[i][ii - 1].second + 1) {
        parametr = 3;
      } else if (path[i][ii].first == path[i][ii - 1].first && path[i][ii].second == path[i][ii - 1].second - 1) {
        parametr = 1;
      } else if (path[i][ii].first == path[i][ii - 1].first + 1 && path[i][ii].second == path[i][ii - 1].second) {
        parametr = 0;
      } else if (path[i][ii].first == path[i][ii - 1].first - 1 && path[i][ii].second == path[i][ii - 1].second) {
        parametr = 2;
      }

      counter += countActionsSituation(parametr, dirNN);
      dirNN = parametr;
    }

    if (counter < min || min == -1) {
      min = counter;
      //=====================================================
      minInd = i; //i
    }
  }

  Serial << "Shortest Way: ";
  for (int ii = 0; ii < path[minInd].size(); ++ii) Serial << "(" << path[minInd][ii].first << "; " << path[minInd][ii].second << "), ";
  Serial << endl;

  int dirPro = robotDirection;
  int param = 0;
  for (int i = 1; i < path[minInd].size(); ++i) {
    Serial << "dirPro: " << dirPro << endl;
    if (path[minInd][i].first == path[minInd][i - 1].first && path[minInd][i].second == path[minInd][i - 1].second + 1) {
      //inDown
      param = 3;
    } else if (path[minInd][i].first == path[minInd][i - 1].first && path[minInd][i].second == path[minInd][i - 1].second - 1) {
      //inUp
      param = 1;
    } else if (path[minInd][i].first == path[minInd][i - 1].first + 1 && path[minInd][i].second == path[minInd][i - 1].second) {
      //inRight
      param = 0;
    } else if (path[minInd][i].first == path[minInd][i - 1].first - 1 && path[minInd][i].second == path[minInd][i - 1].second) {
      //inLeft
      param = 2;
    }

    whereGo(param, dirPro);

    dirPro = param;
  }

  if (path[minInd].size() == 0) {
    action.push(1);
    action.push(1);
  }

  //Serial << endl;
  Serial << "BFS_END" << endl;
}

//0 -- STATE_LEFT
//1 -- STATE_RIGHT
//2 -- STATE_FORWARD
//-> 0
//^ 1
//<- 2
//down 3

void whereGo(int to, int from) {
  if (to - from == 1) action.push(0);
  else if (from - to == 1) action.push(1);
  else if (abs(to - from) == 2) {
    action.push(1);
    action.push(1);
  } else if (to - from == 3) action.push(1);
  else if (from - to == 3) action.push(0);

  action.push(2);
}

int countActionsSituation(int to, int from) {
  int count = 1;

  if (abs(to - from) == 1 || abs(from - to) == 3) ++count;
  else if (abs(to - from) == 2) count += 2;

  return count;
}
