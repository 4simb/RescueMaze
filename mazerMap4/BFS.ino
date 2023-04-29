void mapProcessing() {
  printCoords();
  Serial << endl;
  int s = smezh.size();
  Serial << "CRINGE " << s << endl;
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

      for (int j = 0; j < s; ++j) {
        if (smezh[inx][i].isEqual(smezh[j][0])) {
          Serial << smezh[inx][i].first << " " << smezh[inx][i].second << "           " << smezh[j][0].first << " " << smezh[j][0].second << endl;
          usInd = j;

          Serial << j << endl;
          break;
        }
      }

      if (usInd == -1) {
        //q.clear();
        coordsRes.first = smezh[inx][i].first;
        coordsRes.second = smezh[inx][i].second;
        pointWayDop = cord;
        Queue<int> qEmpty;
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

  path.reverse();
  Serial << "Shortest way: ";
  Serial.println();

  for (int i = 0; i < path.size(); ++i) Serial << "(" << path[i].first << "; " << path[i].second << "), ";
}
