#include "analyze.h"
#include <iostream>

int main (int argc, char **argv)
{
  TileVideo v (80, 80);
  v.acquire("sahalie.mp4");

  long num_slices = v.slice();

  std::cout << num_slices << std::endl;

  return 0;
}
