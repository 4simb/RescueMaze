Queue<long int> q;
long int s;
Vector<Trio> pointWayDop;
Vector<Trio> coordsRes;
Vector<long int> distsMin;
long int first;
Trio cord;
long int inx, usInd;
bool nnState;
long long timeBFS;

void bfs() {
  setMotors(0, 0);
  leftMotorValue = 0;
  rightMotorValue = 0;

  printCoords();
  Serial << endl;
  s = smezh.size();
  Serial << "BFS_START BFS_START BFS_START BFS_START BFS_START " << s << endl;
  //int s = smezh.size();
  bool used[s];
  long int d[s];
  Trio way[s];

  pointWayDop.clear();
  coordsRes.clear();
  distsMin.clear();

  for (long int i = 0; i < s; ++i) {
    way[i] = Trio(0, 0, 0);
    used[i] = false;
    d[i] = 0;
  }

  //BFS
  first = s - 1;

  q.push(first);

  used[first] = true;
  cord = Trio(0, 0, 0);
  inx = 0;
  usInd = 0;
  nnState = false;

  timeBFS = millis();
  while (q.count() != 0) {
    inx = q.peek();
    Serial << inx << endl;
    cord = smezh[inx][0];

    q.pop();

    for (long int i = 1; i < smezh[inx].size(); ++i) {
      usInd = -1;
      Serial << "cringe " << i << endl;

      for (long int j = 0; j < s; ++j) {
        if (smezh[inx][i].absEqual(smezh[j][0])
            ||  (smezh[inx][i].coordsEqual(smezh[j][0]) && smezh[inx][i].slideDetection(smezh[j][0]))) {
          usInd = j;
          Serial << usInd << endl;

          break;
        }
      }

      if (usInd == -1) {
        if (distsMin.size() == 0) {
          distsMin.push_back(d[inx] + 1);
          coordsRes.push_back(smezh[inx][i]);
          pointWayDop.push_back(cord);
        } else if (d[inx] + 1 <= distsMin[0]) {
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

      if (millis() - timeBFS > 6000) {
        Serial << "YES" << endl;
        addCell(false, 0);
        q.clear();
        //return 0;
        //bfs();
      }
    }
  }

  if (distsMin.size() == 0) {
    distsMin.push_back(d[0] + 1);
    coordsRes.push_back(smezh[0][0]);
    pointWayDop.push_back(way[0]);
    Serial << "TO START";
    afterAll = true;
  }
  
  byte ran = random(2);

  bool can = false;
  if (ran == 1) can = true;

  Vector<Vector<Trio> > path;

  int min = -1, minInd;

  for (int i = 0; i < distsMin.size(); ++i) {
    //Serial << "Cycle I" << endl;
    path.push_back(Vector<Trio>());

    path[i].push_back(coordsRes[i]);
    path[i].push_back(pointWayDop[i]);
    Trio now = pointWayDop[i];

    while (!now.absEqual(smezh[first][0])) {
      for (long int ind = 0; ind < s; ++ind) {
        if (smezh[ind][0].absEqual(now)) {
          ////Serial << "(" << way[i].first << "; " << way[i].second << "), ";
          now = way[ind];
          path[i].push_back(way[ind]);
          break;
        }
      }
    }

    //Serial << endl;
    //Serial << "REVERSE" << endl;
    path[i].reverse();
    //Serial << "SW: ";

    //for (int ii = 0; ii < path[i].size(); ++ii) //Serial << "(" << path[i][ii].first << "; " << path[i][ii].second << "), ";
    //Serial << endl;

    //int n = countActionsGeneral(path[i], robotDirection);
    int parametr = 0, counter = 0;
    int8_t dirNN = robotDirection;
    for (long int ii = 1; ii < path[i].size(); ++ii) {
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

    if (counter < min || min == -1 || can) {
      min = counter;
      //=====================================================
      minInd = i; //i
    }

    if (can) break;
  }

  Serial << "Shortest Way: ";
  for (int ii = 0; ii < path[minInd].size(); ++ii) Serial << "(" << path[minInd][ii].first << "; " << path[minInd][ii].second << "), ";
  Serial << endl;

  int dirPro = robotDirection;
  int param = 0;
  for (long int i = 1; i < path[minInd].size(); ++i) {
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

  centralOld = centralVLX;
  backwardOld = backwardVLX;
  l0 = left;
  r0 = right;
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
