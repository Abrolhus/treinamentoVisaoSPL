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
    // cvtColor(img, grayImg, COLOR_BGR2GRAY);
    // grayImg.copyTo(blurredImg);
    Mat kernel = (Mat_<uchar>(3, 3) << 0, 1, 0,
                                       0, 1, 0,
                                       0, 1, 0);
    int kernelSum = 18;
    // Mat sample = Mat_<Vec3f>(3,3);
    // for(int i = 1; i < img.rows-1; i++){
        // for(int j = 1; j < img.cols-1; j++){
            // sample.at<Vec3f>(0 , 0) = (Vec3f)img.at<Vec3b>(i-1, j-1);
            // sample.at<Vec3f>(0 , 1) = (Vec3f)img.at<Vec3b>(i-1, j);
            // sample.at<Vec3f>(0 , 2) = (Vec3f)img.at<Vec3b>(i-1, j+1);
            // sample.at<Vec3f>(1 , 0) = (Vec3f)img.at<Vec3b>(i,   j-1);
            // sample.at<Vec3f>(1 , 1) =(Vec3f) img.at<Vec3b>(i,   j);
            // sample.at<Vec3f>(1 , 2) =(Vec3f) img.at<Vec3b>(i,   j+1);
            // sample.at<Vec3f>(2 , 0) =(Vec3f) img.at<Vec3b>(i+1, j-1);
            // sample.at<Vec3f>(2 , 1) =(Vec3f) img.at<Vec3b>(i+1, j);
            // sample.at<Vec3f>(2 , 2) =(Vec3f) img.at<Vec3b>(i+1, j+1);
            // // blurredImg.at<Vec3b>(i,j) = (Vec3b)sample.dot(kernel)*1/16;
            // //cout << sample.dot(kernel)*1/16 << endl;
            // for(int k = 0; k < 3; k++)
                // for(int l = 0; l < 3; l++){
                    //
//
                // }
        // }
//
    // }

    for(int i = 1; i < img.rows-1; i++){
        for(int j = 1; j < img.cols-1; j++){
            // if(i == 0 || j == 0 || j == img.rows -1 || i == img.cols -1)
                // continue;
            Vec3i value = ((Vec3i)img.at<Vec3b>(i,j)*kernel.at<uchar>(1,1)
                        + kernel.at<uchar>(0,1)*(Vec3i)img.at<Vec3b>(i-1, j) + kernel.at<uchar>(2,1)*(Vec3i)img.at<Vec3b>(i+1, j) + kernel.at<uchar>(1,0)*(Vec3i)img.at<Vec3b>(i, j-1) + kernel.at<uchar>(1,2)*(Vec3i)img.at<Vec3b>(i, j+1)
                        + kernel.at<uchar>(0,0)*(Vec3i)img.at<Vec3b>(i-1, j-1) +kernel.at<uchar>(0,2)*(Vec3i)img.at<Vec3b>(i-1, j+1) +kernel.at<uchar>(2,0)*(Vec3i)img.at<Vec3b>(i+1, j-1) +kernel.at<uchar>(2,2)*(Vec3i)img.at<Vec3b>(i+1, j+1))
                        *(1/(float)16);
            cout << value[0] << ", " << value[1] << ", " << value[2] << endl;
            Vec3b val = (Vec3b)value;
            blurredImg.at<Vec3b>(i,j) = val;
        }
    }
    resize(blurredImg, blurredImg, Size(0,0), 2, 2);
    resize(img, img, Size(0,0), 2, 2);
    imshow("vai1", img);
    imshow("vai", blurredImg);
    waitKey(0);
    return 0;
}
