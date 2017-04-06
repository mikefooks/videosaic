#include <vector>
#include <string>
#include <map>
#include "map.h"
#include "opencv2/opencv.hpp"

#ifndef ANALYZE_H
#define ANALYZE_H

typedef std::vector<std::vector<cv::Mat>> VideoSliceCollection;

class TileVideo {
 public:
  TileVideo (long, long);
  ~TileVideo ();
  void acquire (const std::string);
  void slice ();
  void alterFrames ();
  long frameCount () const;
  std::string slices () const;
  std::string dimensions() const;
  void printDebugInfo () const;
  void printLocMatrix () const;
  void writeOut (const std::string) const;
 private:
  LocationMatrix locMat_;
  std::vector<cv::Mat> capFrames_;
  VideoSliceCollection slicedFrames_;
  VideoSliceCollection alteredFrames_;
  long slices_[2];
  long dimensions_[2];
};

#endif
