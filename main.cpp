#include "map.h"
#include "analyze.h"
#include <iostream>

int main (int argc, char **argv)
{
  TileVideo v (40, 40);
  v.acquire("sahalie.mp4");
  v.slice();
  v.alterFrames();

  v.writeOut("sahalie_altered.avi");

  return 0;
}
