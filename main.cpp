#include "map.h"
#include "analyze.h"
#include <iostream>

int main (int argc, char **argv)
{
  TileVideo v (32, 18);
  v.acquire("beacon.avi");
  v.slice();
  v.alterFrames();

  // v.printDebugInfo();

  v.writeOut("beacon_altered.avi");

  return 0;
}
