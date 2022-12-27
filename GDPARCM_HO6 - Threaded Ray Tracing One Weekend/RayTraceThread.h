#pragma once
#include "Camera.h"
#include "HittableList.h"
#include "IETThread.h"
#include "IETSemaphore.h"
#include "RTImage.h"

class RayTraceThread :    public IETThread
{
public:
	RayTraceThread(int threadID, int lCol, int uCol, int lRow, int uRow);
	~RayTraceThread();


protected:
	void run() override;

private:
	static Color rayColor(const Ray r, const HittableList world, int bounces);

	int threadID = 0;
	int lCol = 0;
	int uCol = 99999;
	int lRow = 0;
	int uRow = 99999;

	float r, g, b;
	Camera* cam;
	HittableList world;
	int j;
	int imageWidth, imageHeight;
	int bounces;
	int raySamplesPerPixel;

	typedef std::ofstream FileStream;
	FileStream* imageFile;
	IETSemaphore* countingSem;
	IETSemaphore* mutexSem;
	RTImage* rtImage;

	std::vector<Color> pixelGroup;

public:
	void setAttributes(FileStream* imageFile, Camera* cam, HittableList world, int bounces, int raySamplesPerPixel, int imageWidth, int imageHeight);
	void setSemaphores(IETSemaphore* countingSem, IETSemaphore* mutexSem);
	void setImage(RTImage* rtImage);
	std::vector<Color> getComputedPixels();


	
};

