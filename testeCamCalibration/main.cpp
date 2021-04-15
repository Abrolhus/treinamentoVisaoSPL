#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
int main(int argc, char **argv) {

  std::vector<cv::String> fileNames;
  cv::glob("../calibration/Image*.png", fileNames, false);
  cv::Size patternSize(25 - 1, 18 - 1);
  std::vector<std::vector<cv::Point2f>> allCorners(fileNames.size()); // posicao de todos os pontos encontrados

  std::vector<std::vector<cv::Point3f>> Q;

  Size dimensoesDoTabuleiro(6,9);
  float tamanhoDoQuadradinho = 5.0f;
  cv::Size frameSize(1440, 1080);
  // os pontos de intersecao (corners) ideais do tabuleiro
    std::vector<cv::Point3f> objPoints;
    for(int i = 0; i<dimensoesDoTabuleiro.height; i++){
      for(int j = 0; j<dimensoesDoTabuleiro.width; j++){
        objPoints.push_back(cv::Point3f(j*tamanhoDoQuadradinho ,i*tamanhoDoQuadradinho,0));
      }
    }

  std::vector<cv::Point2f> imgPoint;
  // Detect feature points
  std::size_t i = 0;
  for (auto const &f : fileNames) {
    std::cout << std::string(f) << std::endl;

    cv::Mat img = cv::imread(fileNames[i]);
    frameSize = img.size();
    cv::Mat grayImg;

    cv::cvtColor(img, grayImg, cv::COLOR_RGB2GRAY);

    vector<Point2f> foundCorners;
    bool found = cv::findChessboardCorners(grayImg, patternSize, foundCorners, cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE + cv::CALIB_CB_FAST_CHECK);

    // 2. Use cv::cornerSubPix() to refine the found corner detections
    if(found){
        cv::cornerSubPix(grayImg, foundCorners,cv::Size(11,11), cv::Size(-1,-1), cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 30, 0.1));
        allCorners.push_back(foundCorners);
    }

    // Display
    cv::drawChessboardCorners(img, patternSize, foundCorners, found);
    // cv::imshow("chessboard detection", img);
    // cv::waitKey(0);

  }


  Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
  // cv::Vec<float, 5> k(0, 0, 0, 0, 0); // distortion coefficients
  Mat distCoefficients = Mat::zeros(8, 1, CV_64F);

  std::vector<cv::Mat> rvecs, tvecs;
  std::vector<vector<Point3f>> objWorldPoints(1);
  objWorldPoints[0] = objPoints;
  objWorldPoints.resize(allCorners.size(), objWorldPoints[0]);

  int flags = cv::CALIB_FIX_ASPECT_RATIO + cv::CALIB_FIX_K3 +
              cv::CALIB_ZERO_TANGENT_DIST + cv::CALIB_FIX_PRINCIPAL_POINT;

  std::cout << "Calibrating..." << std::endl;
  // 4. Call "float error = cv::calibrateCamera()" with the input coordinates
  // and output parameters as declared above...

  float error = cv::calibrateCamera(objWorldPoints, allCorners, frameSize, cameraMatrix, distCoefficients, rvecs, tvecs);

  std::cout << "Reprojection error = " << error << "\ncamera Matrix =\n"
            << cameraMatrix << "\ndistance Coefficients =\n"
            << distCoefficients << std::endl;

  return 0;
  // Precompute lens correction interpolation
  cv::Mat mapX, mapY;
  cv::initUndistortRectifyMap(cameraMatrix, distCoefficients, cv::Matx33f::eye(), cameraMatrix, frameSize, CV_32FC1,
                              mapX, mapY);

  // Show lens corrected images
  for (auto const &f : fileNames) {
    std::cout << std::string(f) << std::endl;

    cv::Mat img = cv::imread(f, cv::IMREAD_COLOR);

    cv::Mat imgUndistorted;
    // 5. Remap the image using the precomputed interpolation maps.
    cv::remap(img, imgUndistorted, mapX, mapY, cv::INTER_LINEAR);

    // Display
    cv::imshow("undistorted image", imgUndistorted);
    cv::waitKey(0);
  }

  return 0;
}
