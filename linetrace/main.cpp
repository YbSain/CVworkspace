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
    
    bool running = true;

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
        
        //grayScale 구하기
        cvtColor(Roiframe, gray, COLOR_BGR2GRAY);
        ////노이즈 지우기
        //int num = (int)(gray.total() * 0.1);
        //for (int i = 0; i < num; i++) {
        //    int x = rand() % gray.cols;
        //    int y = rand() % gray.rows;
        //    gray.at<uchar>(y, x) = (i % 2) * 255;
        //}
        //Mat noiseremove;
        //medianBlur(gray, noiseremove, 3);
        //일정한 밝기 조절을 위한 평균 밝기 값 구하기
        // 블러 처리한 영상의 평균 값 밝기
        Scalar meanValue = mean(gray);
        cout << "mean1:" << meanValue[0] << endl;
        // 목표 값을 지정한 뒤 < 입력영상의 픽셀값 + (원하는 평균 밝기 값 - 입력영상의 평균 밝기)
        double currentBrightness = meanValue[0];
        double targetBrightness = 100.0;
        double adjustment = (targetBrightness - currentBrightness);
        Mat fixbrightnessImg = gray.clone();
        //convertTo를 사용해서 -1로 원본과 동일한 타입을 사용, 1을 곱하여 픽셀 값을 유지한 채로
        //adjustment 즉 목표하는 밝기를 만들기 위한 값을 더함.(목표 밝기 - 현재 평균 밝기) > 목표 밝기ex..100  현재 밝기 ex 89면 둘의 차이로 11이 나오며
        // 밝기가 89일 때 11만큼을 더해 100으로 유지하는 방법임.
        fixbrightnessImg.convertTo(fixbrightnessImg, -1, 1, adjustment);

        Scalar meanValueAdjust = mean(fixbrightnessImg);
        double adjustedBrightness = meanValueAdjust[0];
        cout << "Adjust Average Brightness:" << adjustedBrightness << endl;
        //이진화
        threshold(fixbrightnessImg, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);
        //라인 검출
        int cnt = connectedComponentsWithStats(thresh, labels, stats, centroids);

        Mat connected = gray.clone();
        for (int i = 1; i < cnt; i++) {
            int* p = stats.ptr<int>(i);

            if(p[4]<20) continue;

            rectangle(connected, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
        }




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
