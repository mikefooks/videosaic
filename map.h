#include <map>
#include <array>
#include <iostream>

#ifndef MAP_TESTS_H
#define MAP_TESTS_H

class LocationMatrix
{
 public:
  LocationMatrix ();
  LocationMatrix (unsigned, unsigned, unsigned, unsigned);
  ~LocationMatrix ();
  std::array<unsigned, 2> getLocById (unsigned, unsigned) const;
  friend std::ostream& operator<< (std::ostream&, const LocationMatrix&);
 private:
  std::map<std::array<unsigned, 2>, std::array<unsigned, 2>> matrix_;
  unsigned numX_;
  unsigned numY_;
  unsigned dimX_;
  unsigned dimY_;
  unsigned sliceDimX_;
  unsigned sliceDimY_;
};

#endif
