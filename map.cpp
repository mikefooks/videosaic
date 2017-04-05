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

std::array<unsigned, 2> LocationMatrix::getLocById (unsigned i,
						     unsigned j) const
{
  std::array<unsigned, 2> idx { i, j };
  return matrix_.at(idx);
}

std::ostream& operator<< (std::ostream& os, const LocationMatrix& locMat)
{
  for (unsigned i = 0; i < locMat.numX_; i++) {
    for (unsigned j = 0; j < locMat.numY_; j++) {
      std::array<unsigned, 2> loc = locMat.getLocById(i, j);
      std::cout << loc[0] << ", " << loc[1] << "\n";
    }
  }

  std::cout << std::endl;

  return os;
}
