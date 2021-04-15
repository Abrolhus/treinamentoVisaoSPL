#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>
#include <algorithm>

using namespace std;
using namespace cv;


int main(int argc, const char** argv) {

  Mat img, sobelImg;
  img = imread(argv[1]);
  Mat grayImg, coloredSobel;
  cvtColor(img, grayImg, COLOR_BGR2GRAY);
  cvtColor(img, coloredSobel, COLOR_BGR2HSV);
  grayImg.copyTo(sobelImg);
  GaussianBlur(grayImg, grayImg, Size(3,3), 0);
  // cvtColor(img, grayImg, COLOR_BGR2GRAY);
  // grayImg.copyTo(blurredImg);
  Mat kernelX = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);

  Mat kernelY = (Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
  for (int i = 1; i < grayImg.rows - 1; i++) {
    for (int j = 1; j < grayImg.cols - 1; j++) {
      Mat quadradinho3por3 = grayImg(Rect(j-1, i-1, 3, 3));
      int xGrad=0;
      int yGrad=0;
      for(int x = 0; x < 3; x++)
          for(int y =0; y < 3; y++){
              xGrad += (int)quadradinho3por3.at<uchar>(x, y) * kernelX.at<int>(x,y);
              yGrad += (int)quadradinho3por3.at<uchar>(x, y) * kernelY.at<int>(x,y);
          }
      sobelImg.at<uchar>(i, j) = (uchar)min((int)hypot(xGrad, yGrad), 255);
      double ang = atan2(yGrad, xGrad);
      //coloredSobel.at<Vec3b>(i, j) ={(uchar)(255*cos(ang)), (uchar)(255*cos(ang + CV_PI*2/3)), (uchar)(255*cos(ang - CV_PI*2/3))};
      // cout << ang << " ";
      // cout << ang << endl;
      // cout << (int)(((ang + CV_PI)/(2*CV_PI))*255) << " ";
      // if(sobelImg.at<uchar>(i,j) >= 70)
        // cout << ((ang + CV_PI)/(2*CV_PI))*255 << " ";
      if(sobelImg.at<uchar>(i,j) >= 70)
        coloredSobel.at<Vec3b>(i, j) = { (uchar)(((ang + CV_PI)/(2*CV_PI))*255), 255, 255};
      else
        coloredSobel.at<Vec3b>(i, j) = { 0, 0, 0};
    }
    }
    // resize(sobelImg, sobelImg, Size(0, 0), 2, 2);
    // resize(img, img, Size(0,0), 2, 2);
    Mat sobel;
    imshow("vai1", grayImg);
    imshow("vai", sobelImg);
    // imshow("vai2", coloredSobel);
    waitKey(0);
    return 0;
}
