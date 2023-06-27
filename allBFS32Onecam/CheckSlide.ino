//0 -- back
//1 -- forw
int8_t checkSlide() {
  bool back = false, forw = false;
  int8_t dirOpp;
  
  for (int8_t i = 0; i < 2; ++i) {
    if (i == 0) dirOpp = getOppositeDir(robotDirection);
    else dirOpp = robotDirection;

    int8_t x = xRobot, y = yRobot;
    while (true) {
      coordFuture(x, y, dirOpp, true);
      pair smth = NNPair; // = coordFuture(x, y, dirOpp, true);
      x = smth.first;
      y = smth.second;
      
      int8_t finder = findInMaze(smth.first, smth.second);
      
      if (finder == 0) break;
      else if (finder == 1) {
        if (i == 0) back = true;
        else forw = true;

        break;
      }
    }

    if (back) break;
  }

  if (!back && !forw) return 0;
  else if (back) return 1;
  else return 2;
}

int8_t getOppositeDir(int8_t dir) {
  if (dir + 2 > 3) return dir - 2;
  else return dir + 2;
}

int8_t findInMaze(int x, int y) {
  for (int i = 0; i < maze.size(); ++i) {
    if (maze[i][0].first == x && maze[i][0].second == y) {
      if (maze[i][0].floor == 1 || maze[i][0].floor == 2) {
        return 1; //SLIDE
      } else return 2; //NEXT
    }
  }

  return 0; //END
}
