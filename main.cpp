#include "map.h"
#include "analyze.h"
#include <iostream>

int main (int argc, char **argv)
{
  TileVideo v (32, 18);
  v.acquire("sahalie_cut.avi");
  v.slice();
  v.alterFrames();

  // v.printDebugInfo();

  v.writeOut("sahalie_altered.avi");

  return 0;
}
