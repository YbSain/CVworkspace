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
    //����
    VideoCapture cap("5_lt_cw_100rpm_out.mp4");
    if (!cap.isOpened()) { cerr << "Video Open Failed!" << endl; return -1; }
    
    bool running = true;

    Mat frame, gray, thresh, labels, stats, centroids;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        //��ó��
        //Roi�������ϱ�
        int x = 0, y = 270, width = frame.cols, height = 90;
        Rect Roi(x, y, width, height);

        if (x + width > frame.cols || y + height > frame.rows) {
            cerr << "over frame" << endl; 
            break;
        }

        Mat Roiframe = frame(Roi);
        
        //grayScale ���ϱ�
        cvtColor(Roiframe, gray, COLOR_BGR2GRAY);
        ////������ �����
        //int num = (int)(gray.total() * 0.1);
        //for (int i = 0; i < num; i++) {
        //    int x = rand() % gray.cols;
        //    int y = rand() % gray.rows;
        //    gray.at<uchar>(y, x) = (i % 2) * 255;
        //}
        //Mat noiseremove;
        //medianBlur(gray, noiseremove, 3);
        //������ ��� ������ ���� ��� ��� �� ���ϱ�
        // �� ó���� ������ ��� �� ���
        Scalar meanValue = mean(gray);
        cout << "mean1:" << meanValue[0] << endl;
        // ��ǥ ���� ������ �� < �Է¿����� �ȼ��� + (���ϴ� ��� ��� �� - �Է¿����� ��� ���)
        double currentBrightness = meanValue[0];
        double targetBrightness = 100.0;
        double adjustment = (targetBrightness - currentBrightness);
        Mat fixbrightnessImg = gray.clone();
        //convertTo�� ����ؼ� -1�� ������ ������ Ÿ���� ���, 1�� ���Ͽ� �ȼ� ���� ������ ä��
        //adjustment �� ��ǥ�ϴ� ��⸦ ����� ���� ���� ����.(��ǥ ��� - ���� ��� ���) > ��ǥ ���ex..100  ���� ��� ex 89�� ���� ���̷� 11�� ������
        // ��Ⱑ 89�� �� 11��ŭ�� ���� 100���� �����ϴ� �����.
        fixbrightnessImg.convertTo(fixbrightnessImg, -1, 1, adjustment);

        Scalar meanValueAdjust = mean(fixbrightnessImg);
        double adjustedBrightness = meanValueAdjust[0];
        cout << "Adjust Average Brightness:" << adjustedBrightness << endl;
        //����ȭ
        threshold(fixbrightnessImg, thresh, 0, 255, THRESH_BINARY | THRESH_OTSU);
        //���� ����
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