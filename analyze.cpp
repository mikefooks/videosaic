#include "analyze.h"
#include "opencv2/opencv.hpp"
#include <string>


VideoSlice::VideoSlice (std::vector<cv::Mat>& cap, cv::Rect& roi)
{
  for (auto frame: cap) {
    cv::Mat cropped (frame, roi);
    frames_.push_back(cropped);
  }
}

VideoSlice::~VideoSlice () {}

TileVideo::TileVideo (long xSlices=40, long ySlices=40)
{
  slices_[0] = xSlices;
  slices_[1] = ySlices;
}

TileVideo::~TileVideo () {}

void TileVideo::acquire (const std::string filename)
{
  cv::VideoCapture cap;
  cap.open(filename);

  if (!cap.isOpened()) {
    std::cout << "file not successfully opened" << std::endl;
    return;
  }

  for (;;) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
      break;
    }
    capFrames_.push_back(frame);
    cv::waitKey(1);
  }

  dimensions_[0] = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  dimensions_[1] = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  return;
}

long TileVideo::slice ()
{
  long sliceWidth = dimensions_[0] / slices_[0];
  long sliceHeight = dimensions_[1] / slices_[1];

  for (int x = 0; x < slices_[0]; x++) {
    for (int y = 0; y < slices_[1]; y++) {
      cv::Rect roi (x, y, sliceWidth, sliceHeight);
      VideoSlice v_slice (capFrames_, roi);
      slicedFrames_.push_back(v_slice);
    }
  }

  return slicedFrames_.size();
}

long TileVideo::frameCount () const
{
  return capFrames_.size();
}

std::string TileVideo::slices () const
{
  std::string output = std::to_string(slices_[0]) +
    " " + std::to_string(slices_[1]);
  
  return output;
}

std::string TileVideo::dimensions () const
{
  std::string output = std::to_string(dimensions_[0])
    + " " + std::to_string(dimensions_[1]);

  return output;
}

