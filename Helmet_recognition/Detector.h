#include"stdafx.h"
#ifndef CLASS_DETECTOR_H
#define CLASS_DETECTOR_H
#include"SVMTraining.h"

class Detector {
private:
	//svmģ��
	SVMTraining svm_train_result;
	//hog�����
	cv::HOGDescriptor hogdescriptor;
	//ʹ�ñ�����ַ�
	//ÿһ�����
	cv::Mat background;
	
	PreProcess preprocess;

	cv::Mat helmet_red;
	cv::Mat helmet_blue;
	cv::Mat helmet_yellow;

public:
	//��������
	Detector();
	~Detector() {

	}
	void Load();
	//ʹ��hog�����������ͨɨ�裬���
	void HOGScan(cv::Mat & frame);

	void SetBackGround(cv::Mat background) {
		this->background = background;
	}

	//������ַ�����⶯̬����
	std::vector<cv::Rect> MoveDetect(cv::Mat frame);
	int Otsu(cv::Mat & src);
	double ColorSim(cv::Mat pic1, cv::Mat pic2);
};



#endif