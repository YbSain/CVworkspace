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
    VideoCapture cap("5_lt_cw_100rpm_out.mp4");
    if (!cap.isOpened()) { cerr << "Video Open Failed!" << endl; return -1; }

    Mat frame, gray, thresh, labels, stats, centroids;
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
        cout << "Adjust Average Brightness:" << adjustedBrightness << endl;
        //이진화
        threshold(fixbrightnessImg, thresh, 165, 255, THRESH_BINARY);
        //라인 검출
        Mat connected = Roiframe.clone();
        //모폴로지 / 노이즈
        Mat mopho;
        morphologyEx(thresh, mopho, MORPH_OPEN, Mat(), Point(-1, -1), 3);
        int cnt = connectedComponentsWithStats(mopho, labels, stats, centroids);

        for (int i = 1; i < cnt; i++) {
            int* p = stats.ptr<int>(i);
            double* c = centroids.ptr<double>(i);
            if (p[4] < 20) continue;

            circle(connected, Point((int)c[0], (int)c[1]), 5, Scalar(0, 255, 0), FILLED);
            rectangle(connected, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
        }
        
        imshow("mopho", mopho);


        imshow("connected", connected);
        imshow("thresh", thresh);
        imshow("Adjustimg", fixbrightnessImg);
        imshow("gray", gray);
        imshow("cap", frame);
        if (waitKey(30) == 27) break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
