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

	waitKey(0);

	return 0;
}

void read_images_and_times(vector<Mat> &images, vector<float> &times)
{
	int number_images = 1;

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