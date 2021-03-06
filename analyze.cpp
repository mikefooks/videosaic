#include "analyze.h"
#include "map.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cmath>


TileVideo::TileVideo (long xSlices, long ySlices)
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

  dimensions_[0] = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  dimensions_[1] = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  locMat_ = LocationMatrix(slices_[0],
			   slices_[1],
			   dimensions_[0],
			   dimensions_[1]);

  return;
}

void TileVideo::slice ()
{
  long sliceWidth = dimensions_[0] / slices_[0];
  long sliceHeight = dimensions_[1] / slices_[1];

  for (int x = 0; x < slices_[0]; x++) {
    for (int y = 0; y < slices_[1]; y++) {
      cv::Rect roi (x*sliceWidth, y*sliceHeight, sliceWidth, sliceHeight);
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


void TileVideo::printDebugInfo () const
{
  for (unsigned i = 0; i < slices_[0]; i ++) {
    for (unsigned j = 0; j < slices_[1]; j++) {
      std::array<unsigned, 2> loc = locMat_.getLocById(i, j);
      std::cout << loc[0] << ", " << loc[1] << "\n";
    }
  }
}

void TileVideo::printLocMatrix () const
{
  std::cout << locMat_;
}

void TileVideo::writeOut (const std::string fileName) const
{
  cv::VideoWriter writer;
  int sliceWidth = dimensions_[0] / slices_[0];
  int sliceHeight = dimensions_[1] / slices_[1];
  cv::Size size (dimensions_[0], dimensions_[1]);
  writer.open(fileName, CV_FOURCC('M', 'J', 'P', 'G'), 30, size);

  for (unsigned f = 0; f < frameCount(); f++) {
    cv::Mat frame (size, CV_8UC3);
    
    for (unsigned i = 0; i < slices_[0]; i++) {
      for (unsigned j = 0; j < slices_[1]; j++) {	
	std::array<unsigned, 2> loc = locMat_.getLocById(i, j);
	cv::Rect roi (loc[0], loc[1], sliceWidth, sliceHeight);

	alteredFrames_[i*slices_[1] + j][f].copyTo(frame(roi));
      }
    }

    writer << frame;
    cv::waitKey(1);
  }

  writer.release();
}
