#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<Point2f> poligono;
vector<Point2f> dst;

int main(int argc, char** argv){
    void onMouse(int event, int x, int y, int, void* j);
    Mat img = imread(argv[1]);
    if(img.empty()){
        return -1;
    }
    resize(img, img, Size(0,0), 2, 2);

    string nomeDaJanela = "Janela com a imagem";
    namedWindow(nomeDaJanela);
    setMouseCallback(nomeDaJanela, onMouse);
    imshow(nomeDaJanela, img);
    waitKey(0);
// x:257 y:109
// x:829 y:94
// x:127 y:717
// x:999 y:674
//
    vector<Point2f> origem = {Point2f(257,109), Point2f(829,94), Point2f(127,717), Point2f(999,674)};
    dst = {Point2f(0,0), Point2f(800,0), Point2f(0,800), Point2f(800,800)};
    cout << poligono.size() << endl;
    Mat matrizDeTransformacao = getPerspectiveTransform(poligono, dst);
    warpPerspective(img, img, matrizDeTransformacao, Size(800, 800));
    imshow("janela com warped Image", img);
    waitKey(0);
    return 0;
}
void onMouse(int event, int x, int y, int flags, void*){
    if(event != EVENT_LBUTTONDOWN
            ){
        return;
    }
    if(poligono.size() < 4){
        poligono.push_back(Point(x, y));
    }

    cout << "x:" << x << " y:" << y << endl;


}


