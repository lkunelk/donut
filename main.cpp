#include <iostream>
#include <math.h>
#include <algorithm>
#include <unistd.h>

void resetCursor() {
  std::cout << "\x1b[H";
}

char intensity[] = " .:-=+*#%@"; 

float xx = 0.750f, xy = 0.433f, xz = -0.50f;
float yx = -0.50f, yy = 0.866f, yz = 0.000f;
float zx = 0.433f, zy = 0.250f, zz = 0.866f;

void rotate(float step) {
  float new_xx = xx * cos(step) - xy * sin(step);
  float new_xy = xx * sin(step) + xy * cos(step);
  xx = new_xx;
  xy = new_xy;

  float new_yx = yx * cos(step) - yy * sin(step);
  float new_yy = yx * sin(step) + yy * cos(step);
  yx = new_yx;
  yy = new_yy;

  float new_zx = zx * cos(step) - zy * sin(step);
  float new_zy = zx * sin(step) + zy * cos(step);
  zx = new_zx;
  zy = new_zy;
}

char lumin(int x, int y) {
  // calculate intersection point
  float face_offset = 9;
  float tx = (face_offset - x * xy - y * xz) / (xx + .000001);
  float dist_x = pow(face_offset * xy - x, 2) + pow(face_offset * xz - y, 2) + pow(face_offset * xx - tx, 2);

  float ty = (face_offset - x * yy - y * yz) / (yx + .000001);
  float dist_y = pow(face_offset * yy - x, 2) + pow(face_offset * yz - y, 2) + pow(face_offset * yx - ty, 2);

  float tz = (face_offset - x * zy - y * zz) / (zx + .000001);
  float dist_z = pow(face_offset * zy - x, 2) + pow(face_offset * zz - y, 2) + pow(face_offset * zx - tz, 2);

  // does it fall on the object?
  float angle{0}, smallest{999};
  if (dist_x < pow(face_offset+3, 2)) if (tx < smallest) {angle = xx; smallest = tx;}
  if (dist_y < pow(face_offset+5, 2)) if (ty < smallest) {angle = yx; smallest = ty;}
  if (dist_z < pow(face_offset+9, 2)) if (tz < smallest) {angle = zx; smallest = tz;}

  return intensity[static_cast<int>(abs(angle) * 10)];
}

void drawDonut() {
  resetCursor();
  for (int h = 0; h < 40; h++) {
    for (int w = 0; w < 50; w++) {
      std::cout << lumin(w-25, h-20) << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::cout << "hello world";

  while(true){
    rotate(.1);
    drawDonut();
    usleep(100000);
  }

  return 0;
}
