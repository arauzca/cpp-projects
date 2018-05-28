#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void read_images_and_times(vector<Mat> &, vector<float> &);

int main()
{
	vector<Mat>		images;
	vector<float>	times;

	read_images_and_times(images, times);

	// Align input images
	Ptr<AlignMTB> alignMTB = createAlignMTB();
	alignMTB->process(images, images);

	// Obtain Camera Response Function (CRF)
	Mat responseDebevec;
	Ptr<CalibrateDebevec> calibrateDebevec = createCalibrateDebevec();
	calibrateDebevec->process(images, responseDebevec, times);

	// Merge images into an HDR linear image
	Mat hdrDebevec;
	Ptr<MergeDebevec> mergeDebevec = createMergeDebevec();
	mergeDebevec->process(images, hdrDebevec, times, responseDebevec);
	// Save HDR image.
	imwrite("hdrDebevec.hdr", hdrDebevec);
 
    // Tonemap using Drago's method to obtain 8-bit/channel color image
    Mat ldrDrago;
    Ptr<TonemapDrago> tonemapDrago = createTonemapDrago(1.0f, 0.7f);
    tonemapDrago->process(hdrDebevec, ldrDrago);
    ldrDrago *= 3 * 255;
    imwrite("ldr-Drago.jpg", ldrDrago);
    
    // Tonemap using Durand's method to obtain 8-bit/channel color image
    Mat ldrDurand;
    Ptr<TonemapDurand> tonemapDurand = createTonemapDurand(1.5f, 4.0f, 1.0f, 1.0f, 1.0f);
    tonemapDurand->process(hdrDebevec, ldrDurand);
    ldrDurand *= 3 * 255;
    imwrite("ldr-Durand.jpg", ldrDurand);
    
    // Tonemap using Reinhard's method to obtain 8-bit/channel color image
    Mat ldrReinhard;
    Ptr<TonemapReinhard> tonemapReinhard = createTonemapReinhard(2.2f, 0.0f, 0.0f, 0.0f);
    tonemapReinhard->process(hdrDebevec, ldrReinhard);
    ldrReinhard *= 255;
    imwrite("ldr-Reinhard.jpg", ldrReinhard);
    
    // Tonemap using Mantiuk's method to obtain 8-bit/channel color image
    Mat ldrMantiuk;
    Ptr<TonemapMantiuk> tonemapMantiuk = createTonemapMantiuk(2.2f, 0.85f, 1.2f);
    tonemapMantiuk->process(hdrDebevec, ldrMantiuk);
    ldrMantiuk *= 3 * 255;
    imwrite("ldr-Mantiuk.jpg", ldrMantiuk);
    
    // resizing and displaying all 4 tone mapped images
    Size size(1024,768);
    Mat im_ldrDrago    = imread("ldr-Drago.jpg");
    Mat im_ldrDurand   = imread("ldr-Durand.jpg");
    Mat im_ldrReinhard = imread("ldr-Reinhard.jpg");
    Mat im_ldrMantiuk  = imread("ldr-Mantiuk.jpg");
    
    resize(im_ldrDrago,    im_ldrDrago,    size);
    resize(im_ldrDurand,   im_ldrDurand,   size);
    resize(im_ldrReinhard, im_ldrReinhard, size);
    resize(im_ldrMantiuk,  im_ldrMantiuk,  size);
    
    imshow("LDR-Drago",    im_ldrDrago);
    imshow("LDR-Durand",   im_ldrDurand);
    imshow("LDR-Reinhard", im_ldrReinhard);
    imshow("LDR-Mantiuk",  im_ldrMantiuk);
    
    // press any key to end the programm
    waitKey(0);

	return 0;
}

void read_images_and_times(vector<Mat> &images, vector<float> &times)
{
	int number_images = 4;

	// List of exposures times
	static const float a_times[] = {1.0f/30.0f, 0.25f, 2.5f, 15.0f};
	times.assign(a_times, a_times + number_images);

	// List of image filename
	static const char* a_filenames[] = {"img_0.033.jpg", "img_0.25.jpg" ,"img_2.5.jpg" ,"img_15.jpg"};
	for (int i = 0; i < number_images; i++)
	{
		Mat img = imread(a_filenames[i]);
		images.push_back(img);
	}
}
