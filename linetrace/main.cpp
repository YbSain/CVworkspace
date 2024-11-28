#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}
int main(void) {
    TickMeter tm;
    //원본
    VideoCapture cap("7_lt_ccw_100rpm_in.mp4");

    if (!cap.isOpened()) { cerr << "Video Open Failed!" << endl; return -1; }

    Mat frame, gray, thresh, labels, stats, centroids;
    Rect targetBoundingBox;
    Point2d targetCenter;
    bool isTarget = false;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        //전처리
        //Roi범위구하기
        int x = 0, y = 270, width = frame.cols, height = 90;
        Rect Roi(x, y, width, height);
        if (x + width > frame.cols || y + height > frame.rows) {
            cerr << "over frame" << endl;
            break;
        }
        Mat Roiframe = frame(Roi);

        cvtColor(Roiframe, gray, COLOR_BGR2GRAY);
        Scalar meanValue = mean(gray);
        double currentBrightness = meanValue[0];
        double targetBrightness = 100.0;
        double adjustment = (targetBrightness - currentBrightness);
        Mat fixbrightnessImg = gray.clone();
        fixbrightnessImg.convertTo(fixbrightnessImg, -1, 1, adjustment);

        Scalar meanValueAdjust = mean(fixbrightnessImg);
        double adjustedBrightness = meanValueAdjust[0];
        //이진화
        threshold(fixbrightnessImg, thresh, 165, 255, THRESH_BINARY);
        //라인 검출

        //모폴로지 / 노이즈
        Mat morph;
        morphologyEx(thresh, morph, MORPH_OPEN, Mat(), Point(-1, -1));
        erode(morph, morph, Mat(), Point(-1, -1), 2);
        Mat displaymorph;
        cvtColor(gray, displaymorph, COLOR_GRAY2BGR);
        static Point2d firstCenter(morph.cols / 2, morph.rows / 2);
        int cnt = connectedComponentsWithStats(morph, labels, stats, centroids);
        for (int i = 1; i < cnt; i++) {
            int* p = stats.ptr<int>(i);
            double* c = centroids.ptr<double>(i);
            if (p[4] < 20) continue;
            Rect currentBoundingBox(p[0], p[1], p[2], p[3]);
            Point2d currentCenter(c[0], c[1]);
            int error = morph.cols / 2 - (int)c[0];
            rectangle(displaymorph, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
            double xdistance = targetCenter.x - c[0];
            if (!isTarget) {
                targetCenter = firstCenter;
                isTarget = true;
            }
            else {
                if ((xdistance <= 80 && xdistance >= -80)) {
                    rectangle(displaymorph, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255), 2);
                    circle(displaymorph, targetCenter, 3, Scalar(0, 255, 0), 2);
                    circle(displaymorph, currentCenter, 5, Scalar(0, 255, 0), FILLED);
                    targetBoundingBox = currentBoundingBox;
                    targetCenter = currentCenter;
                    cout << "error" << error << endl;
                }

            }

        }



        imshow("morph", displaymorph);
        imshow("cap", frame);
        if (waitKey(30) == 27) break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
