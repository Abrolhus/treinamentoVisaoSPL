#include "img_processing.h"

using namespace cv;
using namespace std;
void remove_background(Mat img, Mat& field, Mat& lines, vector<Point> &background_border_points){
	lines = Mat::zeros(img.rows, img.cols, CV_8UC3);
	// auto ball = Mat::zeros(img.rows, img.cols, CV_8UC3);
	double hor_hist[img.cols];
	int ver_hist[img.rows];
	field = Mat::zeros(img.rows, img.cols, CV_8UC3);
	Mat background_border = Mat::zeros(img.rows, img.cols, CV_8UC1);
	background_border_points = vector<Point>();
	// boolean variable which declares if the current row pixel is above field
	// height...
	bool background, continuous;
	int counter;
	for (int j = 0; j < img.cols; j++)
	{
		hor_hist[j] = 0;
		background = true;
		counter = 0;
		for (int i = 0; i < img.rows; i++)
		{

			if (hsv_range(img.at<Vec3b>(i, j), YEL_HUE_MIN, YEL_HUE_MAX, YEL_SAT_MIN, YEL_SAT_MAX, YEL_VAL_MIN, YEL_VAL_MAX))
			{
				hor_hist[j]++;
				ver_hist[i]++;
			}
			// check for the horizontal start of the field
			if (background)
			{
				if (hsv_range(img.at<Vec3b>(i, j), GR_HUE_MIN, GR_HUE_MAX, GR_SAT_MIN, GR_SAT_MAX, GR_VAL_MIN, GR_VAL_MAX))
				{
					counter++;

					if (counter > BACK_THRESHOLD)
					{
						ass_val_pixel(field.at<Vec3b>(i - BACK_THRESHOLD, j), 255, 255, 255);
						background_border.at<uchar>(i - BACK_THRESHOLD, j) = 255;
						background_border_points.push_back(Point(j, i - BACK_THRESHOLD));
						for (int k = 0; k < BACK_THRESHOLD + 5; k++)
						{
							if ((i - k) >= 0)
							{
								field.at<Vec3b>(i - k, j) = img.at<Vec3b>(i - k, j);
							}
						}
						background = false;
					}
				}
				else
				{
					continuous = false;
					counter = 0;
				}
			}
			else
			{
				if (hsv_range(img.at<Vec3b>(i, j), WH_HUE_MIN, WH_HUE_MAX, WH_SAT_MIN, WH_SAT_MAX, WH_VAL_MIN, WH_VAL_MAX))
				{
					ass_val_pixel(lines.at<Vec3b>(i, j), 255, 255, 255);
				}
				else
				{
					ass_val_pixel(lines.at<Vec3b>(i, j), 0, 0, 0);
				}
				field.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
			}
		}
		hor_hist[j] /= img.rows;
	}
}

bool hsv_range(Vec3b pixel, int h_min, int h_max, int s_min, int s_max, int v_min, int v_max)
{
	bool isAtRange = true;
	if (pixel[0] < h_min || pixel[0] > h_max)
	{
		isAtRange = false;
	}
	if (pixel[1] < s_min || pixel[1] > s_max)
	{
		isAtRange = false;
	}
	if (pixel[2] < v_min || pixel[2] > v_max)
	{
		isAtRange = false;
	}
	return isAtRange;
}
bool hsv_range(Vec3b pixel, Scalar min, Scalar max){
	bool isAtRange = true;
	if (pixel[0] < min[0] || pixel[0] > max[0])
	{
		isAtRange = false;
	}
	if (pixel[1] < min[1] || pixel[1] > max[1])
	{
		isAtRange = false;
	}
	if (pixel[2] < min[2]  || pixel[2] > max[2])
	{
		isAtRange = false;
	}
	return isAtRange;
}
void ass_val_pixel(Vec3b &pixel, int h, int s, int v)
{
	pixel[0] = h;
	pixel[1] = s;
	pixel[2] = v;
	return;
}
void ass_val_pixel(Vec3b &pixel, Scalar color)
{
	pixel[0] = color[0];
	pixel[1] = color[1];
	pixel[2] = color[2];
	return;
}
void remove_background(Mat image, Mat &lines, Mat &posts, Mat &ball, vector<Point> &goalRoot, double *hor_hist, int *ver_hist)
{
	lines = Mat::zeros(image.rows, image.cols, CV_8UC3);
	posts = Mat::zeros(image.rows, image.cols, CV_8UC3);
	ball = Mat::zeros(image.rows, image.cols, CV_8UC3);
	Mat field = Mat::zeros(image.rows, image.cols, CV_8UC3);
	Mat background_border = Mat::zeros(image.rows, image.cols, CV_8UC1);
	vector<Vec2i> background_border_points = vector<Vec2i>();
	// boolean variable which declares if the current row pixel is above field
	// height...
	bool background, continuous;
	int counter;
	for (int j = 0; j < image.cols; j++)
	{
		hor_hist[j] = 0;
		background = true;
		counter = 0;
		for (int i = 0; i < image.rows; i++)
		{
			// check for the horizontal start of the field
			if (background)
			{
				if (hsv_range(image.at<Vec3b>(i, j), GR_HUE_MIN, GR_HUE_MAX, GR_SAT_MIN, GR_SAT_MAX, GR_VAL_MIN, GR_VAL_MAX))
				{
					counter++;
					ass_val_pixel(field.at<Vec3b>(i, j), 0, 0, 0);
					if (counter > BACK_THRESHOLD)
					{
						ass_val_pixel(field.at<Vec3b>(i - BACK_THRESHOLD, j), 255, 255, 255);
						background_border.at<uchar>(i - BACK_THRESHOLD, j) = 255;
						background_border_points.push_back(Vec2i(i - BACK_THRESHOLD, j));
						for (int k = 0; k < BACK_THRESHOLD + 5; k++)
						{
							if ((i - k) >= 0)
							{
								ass_val_pixel2pixel(field.at<Vec3b>(i - k, j), image.at<Vec3b>(i - k, j));
							}
						}
						background = false;
					}
				}
				else
				{
					continuous = false;
					counter = 0;
				}
			}
			else
			{
				if (hsv_range(image.at<Vec3b>(i, j), WH_HUE_MIN, WH_HUE_MAX, WH_SAT_MIN, WH_SAT_MAX, WH_VAL_MIN, WH_VAL_MAX))
				{
					ass_val_pixel(lines.at<Vec3b>(i, j), 255, 255, 255);
				}
				else
				{
					ass_val_pixel(lines.at<Vec3b>(i, j), 0, 0, 0);
				}
				ass_val_pixel2pixel(field.at<Vec3b>(i, j), image.at<Vec3b>(i, j));
			}
		}
		hor_hist[j] /= image.rows;
	}
	//imshow("va", field);
	std::cout << background_border_points.size() << endl;
}
void ass_val_pixel2pixel(Vec3b &src, Vec3b &dst)
{
	src[0] = dst[0];
	src[1] = dst[1];
	src[2] = dst[2];
}
