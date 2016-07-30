#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat src = imread("/home/yf/Pictures/fub1.jpg");
    vector<Mat> bgrArray, hsvArray;
    split(src, bgrArray);
    Mat hsvImg;
    cvtColor(src,hsvImg, CV_RGB2HSV);
    split(hsvImg, hsvArray);


    for(int i = 0; i < bgrArray.size(); i++)
    {
        stringstream ss;
        ss << "bgr_" << i;
        imshow(ss.str(), bgrArray[i]);
    }

    for(int i = 0; i < hsvArray.size(); i++)
    {
        stringstream ss;
        ss << "hsv_" << i;
        imshow(ss.str(), hsvArray[i]);
    }

    waitKey();
    return 0;
}
