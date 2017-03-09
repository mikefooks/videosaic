#include "analyze.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <cstdlib>
#include <ctime>


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

void TileVideo::slice ()
{
  long sliceWidth = dimensions_[0] / slices_[0];
  long sliceHeight = dimensions_[1] / slices_[1];

  for (int x = 0; x < slices_[0]; x++) {
    for (int y = 0; y < slices_[1]; y++) {
      cv::Rect roi (x, y, sliceWidth, sliceHeight);
      std::vector<cv::Mat> vSlice;
      
      for (auto frame: capFrames_) {
	cv::Mat cropped (frame, roi);
	vSlice.push_back(cropped);
      }

      slicedFrames_.push_back(vSlice);
    }
  }
}

void TileVideo::alterFrames ()
{
  std::srand(time(NULL));

  for (auto slice: slicedFrames_) {
    std::vector<cv::Mat> altered = slice;
    
    std::cout << altered.size() << std::endl;

    for (int i = std::rand() % frameCount(); i < frameCount(); i++) {
      altered.emplace(altered.begin(), altered.back());
      altered.pop_back();
    }

    alteredFrames_.push_back(altered);
  }   
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

