#include "analyze.h"
#include <iostream>

int main (int argc, char **argv)
{
  TileVideo v (40, 40);
  v.acquire("sahalie.mp4");
  v.slice();
  v.alterFrames();

  return 0;
}
