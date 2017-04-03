#include "map.h"
#include <map>
#include <iostream>
#include <array>

LocationMatrix::LocationMatrix ()
{
  numX_ = 0;
  numY_ = 0;
  dimX_ = 0;
  dimY_ = 0;
}

LocationMatrix::LocationMatrix (unsigned numX,
				unsigned numY,
				unsigned dimX,
				unsigned dimY) :
  numX_ (numX), numY_ (numY), dimX_ (dimX), dimY_ (dimY)
{
  sliceDimX_ = dimX / numX;
  sliceDimY_ = dimY / numY;

  for (unsigned i = 0; i < numX; i++) {
    for (unsigned j = 0; j < numY; j++) {
      std::array<unsigned, 2> idx = { i, j };
      std::array<unsigned, 2> loc = { (i * sliceDimX_),
				      (j * sliceDimY_) };
      
      matrix_[idx] = loc;
    }
  }
}

LocationMatrix::~LocationMatrix () {}

std::ostream& operator<< (std::ostream& os, const LocationMatrix& locMat)
{
  for (unsigned i = 0; i < locMat.numX_; i++) {
    for (unsigned j = 0; j < locMat.numY_; j++) {
      std::array<unsigned, 2> idx = { i, j };
      std::cout << locMat.matrix_.at(idx)[0] << ", "
		<< locMat.matrix_.at(idx)[1] << "\n";
    }
  }

  return os;
}
