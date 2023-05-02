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

  if (isWallLR(leftVLX)) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[0].first, yRobot + dir[0].second, floor));
  if (isWallCB(backwardVLX) || backRave) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[1].first, yRobot + dir[1].second, floor));
  if (isWallLR(rightVLX)) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[2].first, yRobot + dir[2].second, floor));
  if (isWallCB(centralVLX) || forwRave) smezh[smezh.size() - 1].push_back(Trio(xRobot + dir[3].first, yRobot + dir[3].second, floor));

  Serial << "SMEZH ===============================================================" << endl;
  for (int i = 0; i < smezh[smezh.size() - 1].size(); ++i) {
    Serial << smezh[smezh.size() - 1][i].first << " " << smezh[smezh.size() - 1][i].second << " ";
  }

  Serial << endl;
}

void coordFuture() {
  NNPair = pair();
  pair shift;

  switch (robotDirection) {
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

  NNPair = pair(xRobot + shift.first, yRobot + shift.second);
}

bool mvInUsedCells(bool mvNum) {
  for (int i = 0; i < mvCell.size(); ++i) {
    if (xRobot == mvCell[i][0].first && yRobot == mvCell[i][0].second && mvNum == mvNums[i]) {
      if (mvCell[i].size() > 1) {
        coordFuture();
        pair p = NNPair;

        if (p.first == mvCell[i][1].first && p.second == mvCell[i][1].second && mvNum == mvNums[i]) return true;
      } else return true;
    } else if (mvCell[i].size() > 1) {
      coordFuture();
      pair p = NNPair;

      if (p.first == mvCell[i][1].first && p.second == mvCell[i][1].second && mvNum == mvNums[i]) return true;
    }
  }

  return false;
}
