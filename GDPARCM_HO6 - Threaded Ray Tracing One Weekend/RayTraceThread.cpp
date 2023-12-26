#include "RayTraceThread.h"

#include "ColorUtils.h"
#include "MathUtils.h"
#include "RayTraceCore.h"

RayTraceThread::RayTraceThread(int threadID, int lCol, int uCol, int lRow, int uRow)
{
	this->threadID = threadID;
    this->lCol = lCol;
    this->uCol = uCol;
    this->lRow = lRow;
    this->uRow = uRow;
}

RayTraceThread::~RayTraceThread()
{
	IETThread::~IETThread();
}

void RayTraceThread::setAttributes(FileStream* imageFile, Camera* cam, HittableList world, int bounces, int raySamplesPerPixel, int imageWidth, int imageHeight)
{
    this->cam = cam;
    this->world = world;
    this->bounces = bounces;
    this->raySamplesPerPixel = raySamplesPerPixel;
    this->imageFile = imageFile;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    
}

std::vector<Color> RayTraceThread::getComputedPixels()
{
    return this->pixelGroup;
}

void RayTraceThread::setSemaphores(IETSemaphore* countingSem, IETSemaphore* mutexSem)
{
    this->countingSem = countingSem;
    this->mutexSem = mutexSem;
}

void RayTraceThread::setImage(RTImage* rtImage)
{
    this->rtImage = rtImage;
}

void RayTraceThread::run()
{
    for (int j = this->uCol - 1; j >= this->lCol; j--) {
        //std::cerr << "\r Thread ID: " << this->threadID<< " Scanlines remaining: " << j << ' ' << std::flush;
        for (int i = this->lRow; i < this->uRow; i++) {

            Color pixels(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < raySamplesPerPixel; s++)
            {
                /*float u = (float(i) + MathUtils::randomFloat()) / (this->imageWidth - 1);
                float v = (float(j) + MathUtils::randomFloat()) / (this->imageHeight - 1);*/

                float u = (float(i) + MathUtils::randomFloat()) / (this->imageWidth - 1);
                float v = (float(j) + MathUtils::randomFloat()) / (this->imageHeight - 1);

                Ray r = cam->getRay(u, v);
                pixels = pixels + RayTraceThread::rayColor(r, world, bounces);
            }

            //this->mutexSem->acquire();
            //ColorUtils::writeColor(this->imageFile, pixels, raySamplesPerPixel);
            //pixelGroup.push_back(pixels);
            this->rtImage->setPixel(i, j, pixels.getX(), pixels.getY(), pixels.getZ(), this->raySamplesPerPixel);
            //this->mutexSem->release();
        }
    }

    this->countingSem->release();
}

Color RayTraceThread::rayColor(const Ray r, const HittableList world, int bounces)
{
    HitRecord rec;

    //If the ray bounce limit is exceeded, no more light needs to be gathered
    if (bounces <= 0)
    {
        return Color(0.0f, 0.0f, 0.0f);
    }

    if (world.hit(r, 0.001f, MathUtils::infinity(), rec)) {
        Ray scattered;
        Color attenuation;

        if (rec.refMaterial->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, world, bounces - 1);
        }
    }

    Vector3D unitDir = Vector3D::unitVector(r.getDirection());
    float t = 0.5f * (unitDir.getY() + 1.0f);
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - t) + Color(0.5f, 0.7f, 1.0f) * t;
}
