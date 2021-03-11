#ifndef IMG_PROCESSING_H
#define IMG_PROCESSING_H

#include <opencv2/opencv.hpp>
#define BACK_THRESHOLD 1

#define YEL_HUE_MIN  20
#define YEL_HUE_MAX  38
#define YEL_SAT_MIN  100
#define YEL_SAT_MAX  255
#define YEL_VAL_MIN  100
#define YEL_VAL_MAX  255

#define GR_HUE_MIN  38
#define GR_HUE_MAX  75
#define GR_SAT_MIN  50
#define GR_SAT_MAX  255
#define GR_VAL_MIN  50
#define GR_VAL_MAX  255

// #define GR_HUE_MIN  38
// #define GR_HUE_MAX  90
// #define GR_SAT_MIN  40
// #define GR_SAT_MAX  255
// #define GR_VAL_MIN  50
// #define GR_VAL_MAX  255

#define WH_HUE_MIN  0
#define WH_HUE_MAX  255
#define WH_SAT_MIN  0
#define WH_SAT_MAX  60
#define WH_VAL_MIN  200
#define WH_VAL_MAX  255

struct field_point{
	int type;
	cv::Point position;
	double orientation[2];
	double confidence;
};

void remove_background(cv::Mat img, cv::Mat& field, cv::Mat& lines, std::vector<cv::Point> &background_border_points);
void remove_background(cv::Mat image, cv::Mat &lines, cv::Mat &posts, cv::Mat &ball, cv::vector<cv::Point> &goalRoot, double *hor_hist, int *ver_hist);
void extractFeaturesFromLines(std::vector<field_point>& result_intersections,  std::vector<cv::Vec4i> lines);
bool hsv_range(cv::Vec3b pixel, int h_min, int h_max, int s_min, int s_max, int v_min, int v_max);
bool hsv_range(cv::Vec3b pixel, cv::Scalar min, cv::Scalar max);
void ass_val_pixel(cv::Vec3b &pixel, cv::Scalar color);
void ass_val_pixel(cv::Vec3b &pixel, int h, int s, int v);
void ass_val_pixel2pixel(cv::Vec3b &src, cv::Vec3b &dst);

#endif

