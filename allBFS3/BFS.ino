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
  pair way[s];

  pair pointWayDop;
  pair coordsRes;

  for (int i = 0; i < s; ++i) {
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
  pair cord;
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
        if (smezh[inx][i].isEqual(smezh[j][0])) {
          Serial << "Base" << endl;
          Serial << smezh[inx][i].first << " " << smezh[inx][i].second << "           " << smezh[j][0].first << " " << smezh[j][0].second << endl;
          usInd = j;

          Serial << j << endl;
          break;
        }
      }

      if (usInd == -1) {
        //q.clear();
        Serial << "go_in" << endl;
        coordsRes.first = smezh[inx][i].first;
        coordsRes.second = smezh[inx][i].second;
        pointWayDop = cord;
        q.clear();
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
  Serial << "(" << coordsRes.first << "; " << coordsRes.second << ")" << endl;
  Serial << "FROM: (" << smezh[first][0].first << "; " << smezh[first][0].second << ")" << endl;
  Serial << endl;
  //}

  //Serial << "Shortest way" << endl;
  //for (int ii = 0; ii < s; ++ii) Serial << "(" << way[ii].first << "; " << way[ii].second << "),  ";
  Vector<pair> path;
  Serial << "Shortest way: " << endl;
  Serial << "(" << coordsRes.first << "; " << coordsRes.second << "), ";
  Serial << "(" << pointWayDop.first << "; " << pointWayDop.second << "), ";

  
  path.push_back(coordsRes);
  path.push_back(pointWayDop);
  pair now = pointWayDop;
  while (!now.isEqual(smezh[first][0])) {
    for (int i = 0; i < s; ++i) {
      if (smezh[i][0].isEqual(now)) {
        Serial << "(" << way[i].first << "; " << way[i].second << "), ";
        now = way[i];
        path.push_back(way[i]);
        break;
      }
    }
  }

  Serial << endl;
  Serial << "REVERSE" << endl;
  path.reverse();
  Serial << "Shortest way: ";
  Serial.println();

  for (int i = 0; i < path.size(); ++i) Serial << "(" << path[i].first << "; " << path[i].second << "), ";
  //(23; 27), (23; 26), (24; 26),
  Serial << endl;

  short int dirPro = robotDirection;
  short int param = 0;
  for (int i = 1; i < path.size(); ++i) {
    Serial << "dirPro: " << dirPro << endl;
    if (path[i].first == path[i - 1].first && path[i].second == path[i - 1].second + 1) {
      //inDown
      //whereGo(3, dirPro);
      param = 3;
    } else if (path[i].first == path[i - 1].first && path[i].second == path[i - 1].second - 1) {
      //inUp
      //whereGo(1, dirPro);
      param = 1;
    } else if (path[i].first == path[i - 1].first + 1 && path[i].second == path[i - 1].second) {
      //inRight
      //whereGo(0, dirPro);
      param = 0;    
    } else if (path[i].first == path[i - 1].first - 1 && path[i].second == path[i - 1].second) {
      //inLeft
      //whereGo(2, dirPro);
      param = 2;
    }

    whereGo(param, dirPro);
    
    dirPro = param;
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

void whereGo(short int to, short int from) {
  if (to - from == 1) action.push(0);
  else if (from - to == 1) action.push(1);
  else if (abs(to - from) == 2) {
    action.push(1);
    action.push(1);
  } else if (to - from == 3) action.push(1);
  else if (from - to == 3) action.push(0);
  
  action.push(2);
}
