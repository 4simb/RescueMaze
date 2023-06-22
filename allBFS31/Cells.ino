void addCell(bool statusCell, int floor) {
  //int xRobotN = xRobot, yRobotN = yRobot;
  Vector<pair> dir;
  //Vector<pair> returnVec;
  smezh.push_back(Vector<Trio>());

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

  smezh[smezh.size() - 1].push_back(Trio(xRobot, yRobot, floor));
  //LEFT BACK RIGHT FORW

  if (isWallCB(centralVLX) || forwRave) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[3].first, yRobot + dir[3].second, floor));
  if (isWallLR(leftVLX)) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[0].first, yRobot + dir[0].second, floor));
  if (isWallLR(rightVLX)) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[2].first, yRobot + dir[2].second, floor));
  if (isWallCB(backwardVLX) || backRave) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[1].first, yRobot + dir[1].second, floor));

  Serial << "SMEZH ===============================================================" << endl;
  for (int i = 0; i < smezh[smezh.size() - 1].size(); ++i) {
    Serial << smezh[smezh.size() - 1][i].first << " " << smezh[smezh.size() - 1][i].second << " ";
  }

  Serial << endl;
}

void coordFuture(int8_t& x, int8_t& y, int8_t dir, bool change = false) {
  NNPair = pair();
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

  NNPair = pair(x + shift.first, y + shift.second);
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
  Vector<int> smezhNum;
  pair p(f, s);

  for (int i = 0; i < smezh.size(); ++i) {
    for (int j = 1; j < smezh[i].size(); ++j) {
      if (smezh[i][j].first == p.first && smezh[i][j].second == p.second
          && (smezh[i][j].floor == floors || smezh[i][j].floor == 1 || smezh[i][j].floor == 2)) {
        smezhNum.push_back(i);
        Serial << "BLACK " << p.first << " " << p.second << " " << i << endl;
        break;
      }
    }
  }

  for (int j = 0; j < smezhNum.size(); ++j) {
    deleteThisCell(p.first, p.second, smezhNum[j]);
  }
}

void deleteThisCell(int fir, int sec, int j) {
  pair p = pair(fir, sec);
  Vector<pair> intermediate;

  int s = smezh[j].size() - 1;
  while (s >= 1) {
    Serial << s << endl;
    Serial << p.first << " " << p.second << "      " << smezh[j][s].first << " " << smezh[j][s].second << endl;
    if (p.first == smezh[j][s].first && p.second == smezh[j][s].second) {
      smezh[j].pop_back();
      Serial << "POP2" << endl;
      break;
    }
    else intermediate.push_back(pair(smezh[j][s].first, smezh[j][s].second));
    smezh[j].pop_back();
    Serial << "POP1" << endl;
    s = smezh[j].size() - 1;
  }

  for (int i = 0; i < intermediate.size(); ++i) {
    smezh[j].push_back(Trio(intermediate[i].first, intermediate[i].second, floors));
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
