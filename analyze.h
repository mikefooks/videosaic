#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

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
 private:
  std::vector<cv::Mat> capFrames_;
  VideoSliceCollection slicedFrames_;
  VideoSliceCollection alteredFrames_;
  long slices_[2];
  long dimensions_[2];
};

#endif
  
