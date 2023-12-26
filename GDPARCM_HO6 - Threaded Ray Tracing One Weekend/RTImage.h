#pragma once
#include <vector>
#include "opencv2/core.hpp"

class RTImage
{
public:
	RTImage(const int imageWidth, const int imageHeight);
	void setPixel(int x, int y, float r, float g, float b, int samplesPerPixel);
	//std::vector <std::vector<Color>> returnImage();
	void saveImage(cv::String &fileName) const;
private:
	//std::vector <std::vector<Color>> pixels;
	std::unique_ptr<cv::Mat> pixels;
	int imageWidth;
	int imageHeight;
	
};

