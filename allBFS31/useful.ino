int sign(int a) {
  if (a > 0) return 1;
  else if (a < 0) return -1;
  else return 0;
}

int adduction(int a) {
  while (a > 180) a -= 360;
  while (a < -180) a += 360;

  return a;
}

int normalize(int y) {
  if (y < 0) y += 360;
  else if (y > 360) y -= 360;
  return y;
}

short int signYaw(double y1, double y2) {
  if (y1 - y2 == 0) return 0;
  else if (abs(y1 - y2) < 180) {
    if (y2 > y1) return -1;
    else return 1;
  } else {
    if (y2 > y1) return 1;
    else return -1;
  }
}

double differenceYaw(double y1, double y2) {
  if (abs(y1 - y2) <= 180) return abs(y1 - y2);
  else if (y2 > 180 && y1 < 180) {
    return y1 + 360 - y2;
  } else {
    return y2 + 360 - y1;
  }
}

float higherYaw(float y) {
  float mini = min(min(differenceYaw(y, 0), differenceYaw(y, 90)), min(differenceYaw(y, 180), differenceYaw(y, 270)));
  if (mini == differenceYaw(y, 0)) return 0;
  else if (mini == differenceYaw(y, 90)) return 90;
  else if (mini == differenceYaw(y, 180)) return 180;
  else return 270;
}
