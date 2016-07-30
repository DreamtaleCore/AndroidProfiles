#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#define HsvType int
#define HSV   0
#define HSV_H 1
#define HSV_S 2
#define HSV_V 3

#define BGR   4
#define BGR_B 5
#define BGR_G 6
#define BGR_R 7

using namespace cv;
using namespace std;

class utilities{
public:
    utilities();
    Mat colorConversion(Mat img, HsvType hsvtype);
    Mat decectMarkerContour(Mat img);
    //void argParams();
};

Mat utilities::colorConversion(Mat img, HsvType imgtype){

    GaussianBlur(img, img, Size(5,5),0,0);

    if(imgtype==HSV||imgtype==HSV_H||imgtype==HSV_S||imgtype==HSV_V){
        Mat img_hsv, img_h, img_s, img_v;
        cvtColor(img, img_hsv, COLOR_BGR2HSV);
        vector<Mat> hsv_channels;
        split(img_hsv, hsv_channels);
        img_h = hsv_channels[0];
        img_s = hsv_channels[1];
        img_v = hsv_channels[2];
        switch (imgtype){
        case 0:
            return img_hsv;
        case 1:
            return img_h;
        case 2:
            return img_s;
        case 3:
            return img_v;
        }
    }

    if(imgtype==BGR||imgtype==BGR_B||imgtype==BGR_G||imgtype==BGR_R){
        Mat b_img, g_img, r_img;
        vector<Mat> bgr_channels;
        split(img,bgr_channels);
        b_img=bgr_channels[0];
        g_img=bgr_channels[1];
        r_img=bgr_channels[2];

        switch(imgtype){
        case 4:
            return img;
        case 5:
            return b_img;
        case 6:
            return g_img;
        case 7:
            return r_img;
        }
        return img;
    }
}
Mat utilities::decectMarkerContour(Mat img){

    Mat img_h, img_threshold, morph_img;
    Mat img_canny(514,386,CV_8UC3,Scalar(0,0,0));
    Mat img_show(514,386,CV_8UC3,Scalar(0,0,0));

    img_h=colorConversion(img, BGR_R);
    threshold(img_h,img_threshold,80,255,1);
    Canny(img_threshold,img_canny,30,90);

    //Mat element = getStructuringElement(MORPH_RECT,Size(5,5));
    //morphologyEx(img_threshold,morph_img,MORPH_CLOSE,element);

    vector<vector<Point>> contours;
    vector<vector<Point>> contours_poly;
    vector<Vec4i> hierarchy;

    //vector<Rect> box(contours.size());
    findContours(img_canny,contours,hierarchy,RETR_TREE,CHAIN_APPROX_NONE);

    contours_poly.resize(contours.size());
    for(unsigned int i=0; i<contours.size();i++){
        int contour_area=contourArea(contours[i]);
        if(contour_area>20000){
            //hierarchy[i][3]<0 &&
            //box[i]=boundingRect(Mat(contours[i]));
            approxPolyDP(Mat(contours[i]), contours_poly[i],4,0);
            drawContours(img_show,contours,i,Scalar(0,255,0),2,8);
            //rectangle(src_frame, boundRect[i], Scalar(0,0,255), 2,8,0);
        }
        imshow("img_show",img_show);
    }

    return img;
}



utilities::utilities()
{

}

int main(){
    VideoCapture capture("/home/nbzd/marker-detect/data/1.avi");
    //Mat src_img = imread("1.jpg");
    if (!capture.isOpened()){

        cout << "Can't open video"<<endl;
        return 0;
    }
    while (1)
    {
        Mat src_frame;
        capture >> src_frame;
        //Mat img_show(src_frame.size());
        if(!src_frame.data)
            break;
        Mat img_h, threshold_img;

        utilities test;
        //img_h=test.colorConversion(src_frame,3);
        Mat marker=test.decectMarkerContour(src_frame);

        imshow("test", src_frame);
        waitKey(10);
        //adaptiveThreshold(hsv_img_h,threshold_img,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,3,1);

    }
    return 0;
}
