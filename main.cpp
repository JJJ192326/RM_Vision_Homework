#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img1 = imread("../images/task1_rects.png");
    if (img1.empty()) return -1;

    Mat hsv, mask_red, mask_blue;
    cvtColor(img1, hsv, COLOR_BGR2HSV);

    Mat mask_r1, mask_r2;
    inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask_r1);
    inRange(hsv, Scalar(160, 100, 100), Scalar(180, 255, 255), mask_r2);
    bitwise_or(mask_r1, mask_r2, mask_red);
    inRange(hsv, Scalar(100, 100, 100), Scalar(130, 255, 255), mask_blue);

    vector<vector<Point>> contours_red, contours_blue;
    findContours(mask_red, contours_red, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(mask_blue, contours_blue, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours_red.size(); i++) {
        if (contourArea(contours_red[i]) > 500) {
            Rect rect = boundingRect(contours_red[i]);
            rectangle(img1, rect, Scalar(0, 255, 0), 3);
        }
    }
    for (size_t i = 0; i < contours_blue.size(); i++) {
        if (contourArea(contours_blue[i]) > 500) {
            Rect rect = boundingRect(contours_blue[i]);
            rectangle(img1, rect, Scalar(0, 255, 255), 3);
        }
    }

    imwrite("../images/result1.jpg", img1);
    imshow("Task 1", img1);
    waitKey(0);

    Mat img2 = imread("../images/task2_armor.jpg");
    if (img2.empty()) return -1;

    Mat gray, mask_bright;
    cvtColor(img2, gray, COLOR_BGR2GRAY);
    threshold(gray, mask_bright, 180, 255, THRESH_BINARY);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 5));
    morphologyEx(mask_bright, mask_bright, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours_armor;
    findContours(mask_bright, contours_armor, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours_armor.size(); i++) {
        double area = contourArea(contours_armor[i]);
        Rect rect = boundingRect(contours_armor[i]);
        float ratio = (float)rect.height / rect.width;

        if (area > 50 && ratio > 2.0) {
            rectangle(img2, rect, Scalar(0, 255, 0), 2);
        }
    }

    imwrite("../images/result2.jpg", img2);
    imshow("Task 2", img2);
    waitKey(0);

    return 0;
}