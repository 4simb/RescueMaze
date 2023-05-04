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
