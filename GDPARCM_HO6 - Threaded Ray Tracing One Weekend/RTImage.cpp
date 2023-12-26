#include "RTImage.h"

#include <iostream>

#include "ColorUtils.h"
#include <opencv2/imgcodecs.hpp>

RTImage::RTImage(int imageWidth, int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));

	/*for(int i = 0; i < this->imageWidth; i++)
	{
		std::vector<Color> rows;
		this->pixels.push_back(rows);
		for(int j = 0; j < this->imageHeight; j++)
		{
			this->pixels[i].push_back(Color(0.0f, 0.0f, 0.0f));
		}
	}*/
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplesPerPixel)
{
	//gamma correction
	float scale = 1.0f / samplesPerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int rInt = static_cast<uchar>(256 * ColorUtils::clamp(r, 0.0, 0.999f));
	int gInt = static_cast<uchar>(256 * ColorUtils::clamp(g, 0.0, 0.999f));
	int bInt = static_cast<uchar>(256 * ColorUtils::clamp(b, 0.0, 0.999f));

	cv::Mat imgChannels[3];
	cv::split(*this->pixels, imgChannels);

	//std::cout << "Pixels: " << this->pixels->size << " " << this->pixels->channels() << " " << x << " " << y << std::endl;

	imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = bInt;
	imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = gInt;
	imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = rInt;

	cv::merge(imgChannels, 3, *this->pixels);
}

//std::vector <std::vector<Color>> RTImage::returnImage()
//{
//	return this->pixels;
//}

void RTImage::saveImage(cv::String &fileName) const
{
	cv::imwrite(fileName, *this->pixels);
}
