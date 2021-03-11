#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "img_processing.h"
using namespace std;
using namespace cv;


int main(int argc, const char** argv) {

    Mat img, cannyImg, drawImgSegs;
    Mat field, linhas;
    Mat hsvImg, grayImg;
    vector<cv::Point> borderPoints;
    img = imread(argv[1]);
    resize(img, img, Size(0,0), 3, 3);
    cvtColor(img, hsvImg, COLOR_BGR2HSV);
    remove_background(hsvImg, field, linhas, borderPoints);
    imshow("field", field);

    waitKey();
    // cvtColor(field, grayImg, COLOR_HSV2BGR);
    // cvtColor(grayImg, grayImg, COLOR_BGR2GRAY);
    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    grayImg.copyTo(cannyImg);
    img.copyTo(drawImgSegs);


    GaussianBlur(cannyImg, cannyImg, Size(3,3), 0);
    Canny(cannyImg, cannyImg, 50, 200);

    vector<Vec4i> linesP;
    // HoughLinesP(cannyImg, linesP, 1, CV_PI/180, 30, 50, 20);
    vector<Vec2f> lines;
    HoughLines(cannyImg, lines, 1, CV_PI/180, 100, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( drawImgSegs, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
    // Draw the lines
    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        if(field.at<Vec3b>(Point(l[0], l[1])) == Vec3b{0, 0, 0} || field.at<Vec3b>(Point(l[2], l[3])) == Vec3b{0, 0, 0}){
            cout << "uai ";
            continue;
        }
        circle(drawImgSegs, Point(l[0], l[1]), 8, Scalar(255, 0, 0), 1);
        circle(drawImgSegs, Point(l[2], l[3]), 8, Scalar(0, 255, 0), 1);
        line(drawImgSegs, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
    }
    for(int i = 0; i < img.cols; i++){
        for(int j = 0;  j < img.rows; j++){
            if(field.at<Vec3b>(j, i) == Vec3b{0, 0, 0}){
                drawImgSegs.at<Vec3b>(j, i) = {0,0,0};
            }
        }
    }
    // Display
    imshow("Original Line Image", img);
    imshow("Canny Img", cannyImg);
    imshow("linhas Detection", drawImgSegs);
    waitKey(0);
    return 0;
}
