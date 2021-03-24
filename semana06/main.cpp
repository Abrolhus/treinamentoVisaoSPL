#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, const char** argv) {

    Mat img, blurredImg;
    img = imread(argv[1]);
    Mat grayImg;
    img.copyTo(blurredImg);
    cvtColor(img, grayImg, COLOR_BGR2GRAY);
    Mat grayBlurredImg;
    grayImg.copyTo(grayBlurredImg);
    // grayImg.copyTo(blurredImg);
    Mat kernel = (Mat_<uchar>(3, 3) << 1, 1, 1,
                                       1, 1, 1,
                                       1, 1, 1);
    int kernelSum = 9;

    for(int i = 1; i < img.rows-1; i++){
        for(int j = 1; j < img.cols-1; j++){
            Vec3i value = ((Vec3i)img.at<Vec3b>(i,j)*kernel.at<uchar>(1,1)
                        + kernel.at<uchar>(0,1)*(Vec3i)img.at<Vec3b>(i-1, j) + kernel.at<uchar>(2,1)*(Vec3i)img.at<Vec3b>(i+1, j) + kernel.at<uchar>(1,0)*(Vec3i)img.at<Vec3b>(i, j-1) + kernel.at<uchar>(1,2)*(Vec3i)img.at<Vec3b>(i, j+1)
                        + kernel.at<uchar>(0,0)*(Vec3i)img.at<Vec3b>(i-1, j-1) +kernel.at<uchar>(0,2)*(Vec3i)img.at<Vec3b>(i-1, j+1) +kernel.at<uchar>(2,0)*(Vec3i)img.at<Vec3b>(i+1, j-1) +kernel.at<uchar>(2,2)*(Vec3i)img.at<Vec3b>(i+1, j+1))
                        *(1/(float)kernelSum);
            Vec3b val = (Vec3b)value;
            blurredImg.at<Vec3b>(i,j) = val;
        }
    }
    // para imagens em preto e branco:
    for(int i = 1; i < grayImg.rows-1; i++){
        for(int j = 1; j < grayImg.cols-1; j++){
            int value = (int)(grayImg.at<uchar>(i,j)*(int)kernel.at<uchar>(1,1)
                        + kernel.at<uchar>(0,1)*(int)grayImg.at<uchar>(i-1, j)
                        + kernel.at<uchar>(2,1)*(int)grayImg.at<uchar>(i+1, j)
                        + kernel.at<uchar>(1,0)*(int)grayImg.at<uchar>(i, j-1)
                        + kernel.at<uchar>(1,2)*(int)grayImg.at<uchar>(i, j+1)
                        + kernel.at<uchar>(0,0)*(int)grayImg.at<uchar>(i-1, j-1)
                        + kernel.at<uchar>(0,2)*(int)grayImg.at<uchar>(i-1, j+1)
                        + kernel.at<uchar>(2,0)*(int)grayImg.at<uchar>(i+1, j-1)
                        + kernel.at<uchar>(2,2)*(int)grayImg.at<uchar>(i+1, j+1))
                        *(1/(float)kernelSum); // nao me orgulho dessas 9 linhas
            uchar val = (uchar)value;
            grayBlurredImg.at<uchar>(i,j) = val;
        }
    }
    imshow("vai1", img);
    imshow("vai", blurredImg);
    imshow("vai2", grayBlurredImg);
    imshow("vai3", grayImg);

    waitKey(0);
    return 0;
}
