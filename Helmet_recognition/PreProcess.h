#pragma once

#include <math.h>

class PreProcess 
{
public:
	PreProcess();

public:
	bool Load();
	//�ҶȻ�ͬʱ����GammaУ׼
	cv::Mat GrayAndGammaCoreect(cv::Mat & src);

private :
	double Gamma;
	uchar Gamma_Chart[256];
};
