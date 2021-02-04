#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
    Mat img = imread("../img.jpg");
    Mat imgROI(img, Rect(400, 200, 400, 400));
    Mat imgGrayRoi(img, Rect(700, 700, 300, 300));

    cout << "Hello World" << endl;
    for(int i = 0; i < imgROI.rows; i++){
        for(int j = 0; j < imgROI.cols; j++){
            imgROI.at<Vec3b>(i, j)[0] = 255 - imgROI.at<Vec3b>(i,j)[0];
            imgROI.at<Vec3b>(i, j)[1] = 255 - imgROI.at<Vec3b>(i, j)[1];
            imgROI.at<Vec3b>(i, j)[2] = 255 - imgROI.at<Vec3b>(i, j)[2];
        }
    }
    imshow("Janela Imagem Invertida", img);
    waitKey(0);

    return 0;
}
