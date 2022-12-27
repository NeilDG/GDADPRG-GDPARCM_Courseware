#pragma once
#include "MathUtils.h"
#include "ColorUtils.h"
#include "Camera.h"
#include "HittableList.h"
#include "Ray.h"
#include "AMaterial.h"
#include "IETThread.h"
#include "IETSemaphore.h"
#include "RTImage.h"

class RayTraceCore : public IETThread
{
public:
	RayTraceCore(int threadID);
	void setSemaphores(IETSemaphore* countingSem);
	void setAttributes(Camera* cam, HittableList world, int i, int j, int imageWidth, int imageHeight, int bounces, int raySamplesPerPixel);
	
	Color getFinalColor() const;

protected:
	void run() override;

private:
	Color rayColor(const Ray r, const HittableList world, int bounces);

	int threadID;
	float r, g, b;
	Camera* cam;
	HittableList world;
	int i, j;
	int imageWidth, imageHeight;
	int bounces;
	int raySamplesPerPixel;

	IETSemaphore* countingSem;
	RTImage* rtImage;
};

