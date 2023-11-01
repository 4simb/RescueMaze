void addCell(bool statusCell, int floor) {
  Serial << endl << "--------------------------ADD_CELL------------------------------" << endl;
  //int xRobotN = xRobot, yRobotN = yRobot;
  Vector<pair> dir;
  //Vector<pair> returnVec;
  maze.push_back(Vector<Trio>());

  //logical shift ->
  switch (robotDirection) {
    case 0: //->
      dir.push_back(pair(0, -1));
      dir.push_back(pair(-1, 0));
      dir.push_back(pair(0, 1));
      dir.push_back(pair(1, 0));
      break;
    case 1: //^
      dir.push_back(pair(-1, 0));
      dir.push_back(pair(0, 1));
      dir.push_back(pair(1, 0));
      dir.push_back(pair(0, -1));
      break;
    case 2: //<-
      dir.push_back(pair(0, 1));
      dir.push_back(pair(1, 0));
      dir.push_back(pair(0, -1));
      dir.push_back(pair(-1, 0));
      break;
    case 3: //down
      dir.push_back(pair(1, 0));
      dir.push_back(pair(0, -1));
      dir.push_back(pair(-1, 0));
      dir.push_back(pair(0, 1));
      break;
  }

  if (statusCell) { //ROBOT IS NOT AT THE START
    xRobot += dir[3].first;
    yRobot += dir[3].second;
  }

  maze[maze.size() - 1].push_back(Trio(xRobot, yRobot, floor));
  //LEFT BACK RIGHT FORW
  
  //for speed bump
  if (isWallCB(centralVLX) || (forwRave && floors == SECOND_FLOOR || isVLXGreat(centralVLX))) maze[maze.size() - 1].push_back(Trio(xRobot + dir[3].first, yRobot + dir[3].second, floor));
  if (isWallLR(leftVLX)) maze[maze.size() - 1].push_back(Trio(xRobot + dir[0].first, yRobot + dir[0].second, floor));
  if (isWallLR(rightVLX)) maze[maze.size() - 1].push_back(Trio(xRobot + dir[2].first, yRobot + dir[2].second, floor));
  if (isWallCB(backwardVLX) || (backRave && floors == SECOND_FLOOR || isVLXGreat(backwardVLX))) maze[maze.size() - 1].push_back(Trio(xRobot + dir[1].first, yRobot + dir[1].second, floor));

  Serial << "MAZE ===============================================================" << endl;
  for (int i = 0; i < maze[maze.size() - 1].size(); ++i) {
    Serial << maze[maze.size() - 1][i].first << " " << maze[maze.size() - 1][i].second << " ";
  }

  Serial << endl;
}

pair coordFuture(int8_t& x, int8_t& y, int8_t dir, bool change = false) {
  pair shift;

  switch (dir) {
    case 0: //->
      shift = pair(1, 0);
      break;
    case 1: //^
      shift = pair(0, -1);
      break;
    case 2: //<-
      shift = pair(-1, 0);
      break;
    case 3: //down
      shift = pair(0, 1);
      break;
  }

  return pair(x + shift.first, y + shift.second);
}

//    =============================== CRINGE ===============================

bool mvInUsedCells(bool mvNum) {
  Serial << "IN_FUN_" << wasMV.size() << endl;
  int x, y;

  for (int j = 0; j < 2; ++j) {
    if (j == 0) {
      x = xRobot + fEditor.first; y = yRobot + fEditor.second;
    } else {
      x = xRobot; y = yRobot;
    }

    for (int i = 0; i < wasMV.size(); ++i) {
      if (wasMV[i].isEqual(x, y, floors, robotDirection, mvNum)
          || wasMV[i].isEqual(x, y, floors, getOppositeDir(robotDirection), !mvNum)) {
        return true;
      }
    }
  }

  return false;
}

void deleteCell(int f, int s) {
  Vector<int> mazeNum;
  pair p(f, s);

  for (int i = 0; i < maze.size(); ++i) {
    for (int j = 1; j < maze[i].size(); ++j) {
      if (maze[i][j].first == p.first && maze[i][j].second == p.second
          && (maze[i][j].floor == floors || maze[i][j].floor == 1 || maze[i][j].floor == 2)) {
        mazeNum.push_back(i);
        Serial << "BLACK " << p.first << " " << p.second << " " << i << endl;
        break;
      }
    }
  }

  for (int j = 0; j < mazeNum.size(); ++j) {
    deleteThisCell(p.first, p.second, mazeNum[j]);
  }
}

void deleteThisCell(int fir, int sec, int j) {
  pair p = pair(fir, sec);
  Vector<pair> intermediate;

  int s = maze[j].size() - 1;
  while (s >= 1) {
    Serial << s << endl;
    Serial << p.first << " " << p.second << "      " << maze[j][s].first << " " << maze[j][s].second << endl;
    if (p.first == maze[j][s].first && p.second == maze[j][s].second) {
      maze[j].pop_back();
      Serial << "POP2" << endl;
      break;
    }
    else intermediate.push_back(pair(maze[j][s].first, maze[j][s].second));
    maze[j].pop_back();
    Serial << "POP1" << endl;
    s = maze[j].size() - 1;
  }

  for (int i = 0; i < intermediate.size(); ++i) {
    maze[j].push_back(Trio(intermediate[i].first, intermediate[i].second, floors));
  }
}

void changeCell(bool byBack, bool byForw, bool byEnc,
                int bvlx, int bvlxOld, int fvlx, int fvlxOld, int enc) {
  
  if ((byBack && changeCell(bvlx, bvlxOld, true))
      || (byForw && changeCell(fvlx, fvlxOld, false))
      || (byEnc && enc > angleEnc / 2)) {
    Serial << "CHANGE";

    switch (robotDirection) {
      case 0: //->
        fEditor = pair(1, 0);
        break;
      case 1: //^
        fEditor = pair(0, -1);
        break;
      case 2: //<-
        fEditor = pair(-1, 0);
        break;
      case 3: //down
        fEditor = pair(0, 1);
        break;
    }
  }
}
