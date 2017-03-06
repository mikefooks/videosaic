#ifndef ANALYZE_H
#define ANALYZE_H

#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

class VideoSlice {
 public:
  VideoSlice (std::vector<cv::Mat>&, cv::Rect&);
  ~VideoSlice ();
 private:
  std::vector<cv::Mat> frames_;
};

class TileVideo {
 public:
  TileVideo (long, long);
  ~TileVideo ();
  void acquire (const std::string);
  long slice ();
  long frameCount () const;
  std::string slices () const;
  std::string dimensions() const;
 private:
  std::vector<cv::Mat> capFrames_;
  std::vector<VideoSlice> slicedFrames_;
  long slices_[2];
  long dimensions_[2];
};

#endif
  
