#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void camera_in_video_out();

int main()
{
	camera_in_video_out();
	return 0;
}


void camera_in_video_out()
{
	VideoCapture cap(0); //카메라
	VideoCapture cap1("stopwatch.avi"); //스톱워치 영상
	
	cap.set(CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480); 
	cap1.set(CAP_PROP_FRAME_WIDTH, 640);
	cap1.set(CAP_PROP_FRAME_HEIGHT, 480);

	if (!cap.isOpened() && !cap1.isOpened()) {
		cerr << "Camera & Video open failed!" << endl;
		return;
	}

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH)); //cap의 가로
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)); //cap의 세로
	
	double fps = cap.get(CAP_PROP_FPS); //cap의 초당 프레임 수
	double fps1 = cap1.get(CAP_PROP_FPS); //cap1의 초당 프레임 수
	
	int delayfps = cvRound(1000 / fps); //fps의 매 프레임 사이의 시간 간격 계산
	int delayfps1 = cvRound(1000 / fps1); //fps1의 매 프레임 사이의 시간 간격

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X'); //fourcc 코드 생성
	
	
	VideoWriter output1("output.avi", fourcc, fps, Size(w, h));
	
	if (!output1.isOpened()) {
		cout << "File open failed!" << endl;
		return;
	}

	Mat frame, frame1, inversed;
	while (true) {
		
		cap1 >> frame;
		if (frame.empty())
			break;
		imshow("frame_file", frame);

		output1 << frame;

		if (waitKey(delayfps1) == 27) break;
		
		if (cap1.get(CAP_PROP_POS_FRAMES) == 60) {
			
			
			while (true) {



				cap >> frame1;
				if (frame1.empty())
					break;

				inversed = ~frame1;
				output1 << inversed;

				imshow("frame_camera", inversed);
				//waitKey(cap.get(CAP_PROP_FRAME_COUNT));

				if (waitKey(delayfps) == 27) {
					destroyWindow("frame_camera");
					break;
				}


			}
			
			cap1.set(CAP_PROP_POS_FRAMES, 120);
			
		}

		if (cap1.get(CAP_PROP_POS_FRAMES) == 180)
			break;
		
	}

	destroyAllWindows();

}