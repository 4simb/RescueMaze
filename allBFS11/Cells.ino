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

void coordFuture(int& x, int& y, int dir, bool change = false) {
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
  //if (change) x += shift.first; y += shift.second;
  //return NNPair;
}

bool mvInUsedCells(bool mvNum) {
  Serial << "IN_FUN_" << wasMV.size() << endl;
  for (int i = 0; i < wasMV.size(); ++i) {
    if (wasMV[i].isEqual(xRobot, yRobot, floors, robotDirection, centralVLX, backwardVLX, mvNum) 
        || wasMV[i].isEqual(xRobot, yRobot, floors, getOppositeDir(robotDirection), backwardVLX, centralVLX, !mvNum)) {
      return true;
    }

    Serial << wasMV[i].first << " " << wasMV[i].second << " " << wasMV[i].floor << " " << wasMV[i].dir << " "
           << wasMV[i].fvlx << " " << wasMV[i].bvlx << " " << wasMV[i].camera << endl;
    Serial << xRobot << " " << yRobot << " " << floors << " " << robotDirection << " "
           << centralVLX << " " << backwardVLX << " " << mvNum << endl;
    Serial << endl;
     
  }

  return false;
}
