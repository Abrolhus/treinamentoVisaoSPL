#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

// Dimensoes do tabuleiro, só que uma unidade a menos, j[a que o que interessa são as intercesoes entre os quadradinhos
int dimensoesDoTabuleiro[2]{24,17};

int main()
{
  // armazena os pontos em 3d para cada tabuleiro.
  std::vector<std::vector<cv::Point3f> > objpoints;

  // armazena os pontos em 2d na imagem de cada tabuleiro, cada imagem
  std::vector<std::vector<cv::Point2f> > imgpoints;

  // cria objeto formado pelos pontos (intercesoes) do tabuleiro "ideal" em 3d,
  std::vector<cv::Point3f> objp;
  for(int i=0; i<dimensoesDoTabuleiro[1]; i++)
  {
    for(int j=0; j<dimensoesDoTabuleiro[0]; j++)
      objp.push_back(cv::Point3f(j,i,0));
  }


  std::vector<cv::String> images;
  std::string path = "../images/*.png";

  cv::glob(path, images);

  cv::Mat frame, gray;
  // vetor com as corners/pontos encontradas
  std::vector<cv::Point2f> cornersFound;
  bool success;

  // percorrendo o vetor de paths de imagens
  for(int i=0; i<images.size(); i++)
  {
    frame = cv::imread(images[i]);
    cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);

    // procurando as corners
    // se encontrar as corners, retorna true
    success = cv::findChessboardCorners(gray,cv::Size(dimensoesDoTabuleiro[0],dimensoesDoTabuleiro[1]), cornersFound, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);

    /*
     * If desired number of corner are detected,
     * we refine the pixel coordinates and display
     * them on the images of checker board
    */
    if(success)
    {
      cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::MAX_ITER, 30, 0.001);

      // refinando as cordenadas dos corners
      cv::cornerSubPix(gray,cornersFound,cv::Size(11,11), cv::Size(-1,-1),criteria);

      // mostrando os corners na imagem
      cv::drawChessboardCorners(frame, cv::Size(dimensoesDoTabuleiro[0],dimensoesDoTabuleiro[1]), cornersFound,success);

      objpoints.push_back(objp);
      imgpoints.push_back(cornersFound);
    }

    // cv::imshow("Image",frame);
    // cv::waitKey(0);
  }

  cv::destroyAllWindows();

  std::vector<cv::Mat> R,T;
  cv::Mat cameraMatrix = cv::Mat::eye(3,3, CV_64F);
  cv::Mat distCoeffs = cv::Mat::zeros(8,1, CV_64F);

  /*
   * Performing camera calibration by
   * passing the value of known 3D points (objpoints)
   * and corresponding pixel coordinates of the
   * detected corners (imgpoints)
  */
  cv::calibrateCamera(objpoints, imgpoints,cv::Size(gray.rows,gray.cols),cameraMatrix,distCoeffs,R,T);

  std::cout << "cameraMatrix : " << cameraMatrix << std::endl;
  std::cout << "distCoeffs : " << distCoeffs << std::endl;
  // std::cout << "Rotation vector : " << R << std::endl;
  // std::cout << "Translation vector : " << T << std::endl;
  cv::Mat mapX, mapY;
  // usando os coeficientes obtidos para achar mapas x e y q remapeiam a imagem
  cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Mat(), cameraMatrix,
      gray.size(), CV_16SC2, mapX, mapY);
  // cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, cv::Matx33f::eye(), cameraMatrix, cv::Size(dimensoesDoTabuleiro[0],dimensoesDoTabuleiro[1]), CV_32FC1,
                              // mapX, mapY);
  for(int i=0; i<images.size(); i++){
    frame = cv::imread(images[i]);
    cv::Mat imgCorrigida;
    cv::remap(frame, imgCorrigida, mapX, mapY, cv::INTER_LINEAR);
    cv::resize(imgCorrigida, imgCorrigida, cv::Size(0,0), 0.5, 0.5);
    cv::imshow("img corrigida", imgCorrigida);
    cv::imshow("img ", frame);
    cv::waitKey();
  }

  return 0;
}
