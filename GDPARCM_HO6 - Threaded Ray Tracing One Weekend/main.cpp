#include <iostream>
#include <fstream>
#include "ColorUtils.h"
#include "HittableList.h"
#include "MathUtils.h"
#include "Sphere.h"
#include "Camera.h"
#include "DiffuseMaterial.h"
#include "MetalMaterial.h"
#include "DielectricMaterial.h"
#include <thread>
#include <algorithm>
#include "IETSemaphore.h"
#include "RayTraceThread.h"
#include "RayTraceCore.h"

Color rayColor(const Ray r, const HittableList world, int bounces)
{
    HitRecord rec;

	//If the ray bounce limit is exceeded, no more light needs to be gathered
	if(bounces <= 0)
	{
        return Color(0.0f, 0.0f, 0.0f);
	}
	
    if (world.hit(r, 0.001f, MathUtils::infinity(), rec)) {
        Ray scattered;
        Color attenuation;

    	if(rec.refMaterial->scatter(r, rec, attenuation, scattered))
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

HittableList generateRandomScene()
{
    HittableList world;
    std::shared_ptr<DiffuseMaterial> groundMat = make_shared<DiffuseMaterial>(Color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(Point3D(0.0f, -1000.0f, 0.0f), 1000.0f, groundMat));

    for (int repeats = 0; repeats < 5; repeats++)
    {
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                float matVal = MathUtils::randomFloat();
                Point3D center(a + 0.9f * MathUtils::randomFloat(), 0.2, b + 0.9 * MathUtils::randomFloat());

                if ((center - Point3D(4.0, 0.2f, 0.0f)).length() > 0.9f)
                {
                    shared_ptr<AMaterial> refMaterial;

                    if (matVal < 0.8)
                    {
                        Color albedo = static_cast<Color> (Vector3D::random() * Vector3D::random());
                        refMaterial = make_shared<DiffuseMaterial>(albedo);
                        world.add(make_shared<Sphere>(center, 0.2f, refMaterial));
                    }
                    else if (matVal < 0.95)
                    {
                        Color albedo = static_cast<Color> (Vector3D::random() * Vector3D::random());
                        float fuzziness = MathUtils::randomFloat(0.0f, 0.5f);
                        refMaterial = make_shared<MetalMaterial>(albedo, fuzziness);
                        world.add(make_shared<Sphere>(center, 0.2f, refMaterial));
                    }
                    else
                    {
                        refMaterial = make_shared<DielectricMaterial>(1.5f);
                        world.add(make_shared<Sphere>(center, 0.2f, refMaterial));
                    }
                }
            }
        }
    }
	
    return world;
}

void multiCoreWindowRT(HittableList world, Camera cam, int imageWidth, int raySamplesPerPixel, int bounces, int numCores)
{
    std::cout << "Running multicore ray tracing by sliding window." << std::endl;

    // Image
    const float aspectRatio = 3.0f / 2.0f;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Render
    /*typedef std::ofstream FileStream;
    FileStream* imageFile = new FileStream();
    imageFile->open("D:/Documents/GithubProjects/GDGRAP2-Workspace/Part 2 - Ray Tracing One Weekend/ImageRender.ppm");
    *imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";*/
    cv::String fileName = "D:/Documents/GithubProjects/GDGRAP2-Workspace/Part 2 - Ray Tracing One Weekend/ImageRender.png";

    std::vector<RayTraceThread*> rtCores;
    IETSemaphore* countingSem = new IETSemaphore(0);
    IETSemaphore* mutexSem = new IETSemaphore(1);

    //const int widthWindow = rint(imageWidth / (numCores / 2));
    //const int heightWindow = rint(imageHeight / (numCores / 2));
    const int widthWindow = rint(imageWidth / numCores);
    const int heightWindow = imageHeight;

    int lRow = 0;
    int uRow = widthWindow;

    RTImage* rtImage = new RTImage(imageWidth, imageHeight);

    for(int i = 0; i < numCores; i++)
    {
        std::cout << " " << lRow << " " << uRow << std::endl;

        RayTraceThread* rtCompute = new RayTraceThread(i, 0, imageHeight, lRow, uRow);
        rtCompute->setAttributes(nullptr, &cam, world, bounces, raySamplesPerPixel, imageWidth, imageHeight);
        rtCompute->setSemaphores(countingSem, mutexSem);
        rtCompute->setImage(rtImage);
        rtCompute->start();

        rtCores.push_back(rtCompute);

        lRow = lRow + widthWindow;
        uRow = uRow + widthWindow;
    }
    

    countingSem->acquire(numCores);

    ////format pixels to write
    /*for (int i = 0; i < rtCores.size(); i++)
    {
        std::vector<Color> pixelGroup = rtCores[i]->getComputedPixels();
        std::cout << "Thread ID: " << i << " Computed pixel size: " << pixelGroup.size() << std::endl;
        for (int j = 0; j < pixelGroup.size(); j++)
        {
            ColorUtils::writeColor(imageFile, pixelGroup[j], raySamplesPerPixel);
        }

        pixelGroup.clear();
    }*/

    std::cout << "Writing pixels " << std::endl;
    rtImage->saveImage(fileName);
    /*for (int j = imageHeight - 1; j >= 0; j--)
    {
	    for(int i = 0; i < imageWidth; i++)
	    {
            ColorUtils::writeColor(imageFile, rtImage->returnImage()[i][j], raySamplesPerPixel);
	    }
    }*/

    //clean up
    for (int i = 0; i < rtCores.size(); i++)
    {
        delete rtCores[i];
    }
    delete countingSem;
    delete mutexSem;
    rtCores.clear();


    //imageFile->close();
    std::cout << "Rendered scene saved to file." << std::endl;
}

void multiCoreSampleRT(HittableList world, Camera cam, int imageWidth, int raySamplesPerPixel, int bounces, int numCores)
{
    std::cout << "Running multicore ray tracing by sample." << std::endl;
    // Image
    const float aspectRatio = 3.0f / 2.0f;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Render
    typedef std::ofstream FileStream;
    FileStream* imageFile = new FileStream();
    imageFile->open("D:/Documents/GithubProjects/GDGRAP2-Workspace/Part 2 - Ray Tracing One Weekend/ImageRender.ppm");
    *imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    std::vector<RayTraceCore*> rtCores;
    IETSemaphore* countingSem = new IETSemaphore(0);
    IETSemaphore* mutexSem = new IETSemaphore(1);

    const int raySamplesPerCore = raySamplesPerPixel / numCores;
    for (int j = imageHeight - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {

            Color pixels(0.0f, 0.0f, 0.0f);
            for(int threadID = 0; threadID < numCores; threadID++)
            {
                RayTraceCore* rtCore = new RayTraceCore(threadID);
                rtCore->setSemaphores(countingSem);
                rtCore->setAttributes(&cam, world, i, j, imageWidth, imageHeight, bounces, raySamplesPerCore);
                rtCore->start();

                rtCores.push_back(rtCore);
            }

            countingSem->acquire(numCores);
            Color pixel(0.0f, 0.0f, 0.0f);
            for (int threadID = 0; threadID < numCores; threadID++)
            {
                pixel = pixel + rtCores[threadID]->getFinalColor();
                delete rtCores[threadID];
            }
            rtCores.clear();
            //pixel = pixel / 4.0f;
            ColorUtils::writeColor(imageFile, pixel, raySamplesPerPixel);

        }
    }

}

int main()
{
    // Image
    const float aspectRatio = 3.0f / 2.0f;
    const int imageWidth = 1440;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int raySamplesPerPixel = 100;
    const int bounces = 50;
    const int numCores = 24;

	//World
    HittableList world;

    /*std::shared_ptr<DiffuseMaterial> groundMat = make_shared<DiffuseMaterial>(Color(0.8f, 0.8f, 0.0f));
    std::shared_ptr<DiffuseMaterial> centerCircleMat = make_shared<DiffuseMaterial>(Color(0.4f, 0.2f, 0.1f));
    std::shared_ptr<DielectricMaterial> leftCircleMat = make_shared<DielectricMaterial>(1.5f);
    std::shared_ptr<MetalMaterial> rightCircleMat = make_shared<MetalMaterial>(Color(0.7f, 0.9f, 0.9f), 0.0f);*/

    std::shared_ptr<DiffuseMaterial> groundMat = make_shared<DiffuseMaterial>(Color(Vector3D::random() * Vector3D::random()));
    std::shared_ptr<DiffuseMaterial> centerCircleMat = make_shared<DiffuseMaterial>(Color(0.4f, 0.2f, 0.1f));
    std::shared_ptr<DielectricMaterial> leftCircleMat = make_shared<DielectricMaterial>(1.5f);
    std::shared_ptr<MetalMaterial> rightCircleMat = make_shared<MetalMaterial>(Color(0.7f, 0.9f, 0.9f), 0.0f);

    world = generateRandomScene();
	
    world.add(make_shared<Sphere>(Point3D(-4.0f, 1.0f, 0.0f), 1.0f, groundMat));
    world.add(make_shared<Sphere>(Point3D(0.0f, 1.0f, 0.0f), 1.0f, leftCircleMat));
    world.add(make_shared<Sphere>(Point3D(0.0f, 1.0f, 0.0f), -0.9f, leftCircleMat));
    world.add(make_shared<Sphere>(Point3D(4.0f, 1.0f, 0.0f), 1.0f, rightCircleMat));
	
	//Camera
    Point3D lookFrom(13.0f, 2.0f, 3.0f);
    Point3D lookAt(0.0f, 0.0f, 0.0f);
    Vector3D vUp(0.0f, 1.0f, 0.0f);
    float distToFocus = (lookFrom - lookAt).length();
    float aperture = 0.1f;
	
    Camera cam(lookFrom, lookAt, vUp, 20, aspectRatio, aperture, distToFocus); //far view
    //Camera cam(Point3D(-2.0f, 2.0f, 1.0f), Point3D(0.0f, 0.0f, -1.0f), Vector3D(0.0f, 1.0f, 0.0f), 20, aspectRatio); //zoom view

    multiCoreWindowRT(world, cam, imageWidth, raySamplesPerPixel, bounces, numCores);
    //multiCoreSampleRT(world, cam, imageWidth, raySamplesPerPixel, bounces, numCores);

    
}