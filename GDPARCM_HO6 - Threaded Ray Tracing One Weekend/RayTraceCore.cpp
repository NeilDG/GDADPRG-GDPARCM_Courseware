#include "RayTraceCore.h"
#include <iostream>
#include <fstream>

RayTraceCore::RayTraceCore(int threadID)
{
    this->threadID = threadID;
}

void RayTraceCore::setSemaphores(IETSemaphore* countingSem)
{
    this->countingSem = countingSem;
}

void RayTraceCore::setAttributes(Camera* cam, HittableList world, int i, int j, int imageWidth, int imageHeight, int bounces, int raySamplesPerPixel)
{
    this->cam = cam;
    this->world = world;
    this->i = i;
    this->j = j;
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    this->bounces = bounces;
    this->raySamplesPerPixel = raySamplesPerPixel;
}

Color RayTraceCore::getFinalColor() const
{
    return Color(this->r, this->g, this->b);
}

void RayTraceCore::run()
{
    Color pixels(0.0f, 0.0f, 0.0f);
    //std::cout << "Calculating ray assigned at thread ID " << threadID << std::endl;
    for (int s = 0; s < raySamplesPerPixel; s++)
    {
        float u = (float(i) + MathUtils::randomFloat()) / (imageWidth - 1);
        float v = (float(j) + MathUtils::randomFloat()) / (imageHeight - 1);

        Ray r = cam->getRay(u, v);
        pixels = pixels + rayColor(r, world, bounces);
    }

    //pixels = pixels / raySamplesPerPixel;
    this->r = pixels.getX();
    this->g = pixels.getY();
    this->b = pixels.getZ();

    this->countingSem->release();
}

Color RayTraceCore::rayColor(const Ray r, const HittableList world, int bounces)
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
        // Point3D target = rec.p + rec.normal + Vector3D::randomInHemisphere(rec.normal);
        // return rayColor(Ray(rec.p, target - rec.p), world, bounces - 1) * 0.5f;
    }

    Vector3D unitDir = Vector3D::unitVector(r.getDirection());
    float t = 0.5f * (unitDir.getY() + 1.0f);
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - t) + Color(0.5f, 0.7f, 1.0f) * t;
}
