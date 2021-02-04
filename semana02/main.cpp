#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, char** argv){

    cout << argv[0];
    Mat img = imread(argv[1]);








    Mat grayImg, binaryImg, blurredBinary;
    cvtColor(img, grayImg, CV_BGR2GRAY);




    Mat grayishImg(grayImg.rows, grayImg.cols, CV_8UC1, 255);
    // GaussianBlur(grayImg, grayImg, Size(3, 3), 0);
    // imshow("vai", grayImg);
    // waitKey(0);
    //threshold(grayImg, binaryImg, 125, 255, THRESH_OTSU);
    threshold(grayImg, binaryImg, 125, 255, THRESH_BINARY);


    // adaptiveThreshold(grayImg, binaryImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 7);
    adaptiveThreshold(grayImg, binaryImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 12);
    medianBlur(binaryImg, binaryImg, 3);

    imshow("imagem normal", img);
    imshow("imagem binarizada", binaryImg);
    waitKey();
    return 0;
    // medianBlur(binaryImg, blurredBinary, 3);
    // GaussianBlur(binaryImg, blurredBinary, Size(3, 3), 0);
    for(int i =0; i < binaryImg.rows; i++){
        for(int j =0; j < binaryImg.cols; j++){
            if(binaryImg.at<uchar>(i, j) == 0){
                grayishImg.at<uchar>(i,j) = grayImg.at<uchar>(i,j);
            }
        }
    }
    // imshow("Binary Img", binaryImg);
    // imshow("Blurred Img", blurredBinary);
    imshow("grayishImg", grayishImg);
    // imshow("Gray Img", grayImg);
    imshow("Original Img", img);
    int tecla = waitKey(0);

    return 0;
}
