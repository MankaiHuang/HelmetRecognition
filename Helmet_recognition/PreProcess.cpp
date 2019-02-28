#include "stdafx.h"
#include "PreProcess.h"

PreProcess::PreProcess() 
{
	
}

bool PreProcess::Load()
{
	Gamma = 0.5;
	//��ʼ��GammaУ׼��
	for (int i = 0; i < 256; i++) 
	{
		this->Gamma_Chart[i] = cv::saturate_cast<uchar>( pow((double)(i / 255.0), Gamma) * 255 );
	}
	return true;
}

//�ҶȻ�ͬʱ����GammaУ׼
cv::Mat PreProcess::GrayAndGammaCoreect(cv::Mat & src)
{
	//��ȡͨ����
	int channels = src.channels();
	//��ȡ����������������
	int rows = src.rows;
	int cols = src.cols;

	//���ͼ�񣬲���ԭͼ����в���
	cv::Mat result(rows,cols,CV_8UC1);

	if (channels == 1) {
		for (int j = 0; j < rows; j++) {
			//��ȡԴͼ��Ŀ��ͼ��ָ��
			uchar * result_data = result.ptr<uchar>(j);
			uchar * src_data = src.ptr<uchar>(j);
			for (int i = 0; i < cols; i++) {
				//�����������ת��
				result_data[i] = this->Gamma_Chart[src_data[i]];
			}
		}
	}
	else if (channels == 3) {
		for (int j = 0; j < rows; j++) {
			//��ȡԴͼ��Ŀ��ͼ��ָ��
			uchar * result_data = result.ptr<uchar>(j);
			uchar * src_data = src.ptr<uchar>(j);
			for (int i = 0; i < cols; i++) {
				//�����������ת��
				result_data[i] = (uchar)(src_data[i * channels + 0]*0.11 + src_data[i * channels + 1]*0.59 + src_data[i * channels + 2]*0.30);
				result_data[i] = this->Gamma_Chart[result_data[i]];
			}
		}
	}
	else {
		//��ͨ�����Ƚ��лҶ�ת��
		cv::cvtColor(src, result, CV_RGBA2GRAY);
		for (int j = 0; j < rows; j++) {
			//��ȡ��ָ��
			uchar * result_data = result.ptr<uchar>(j);
			for (int i = 0; i < cols; i++) {
				//�����������ת��
				result_data[i] = this->Gamma_Chart[result_data[i]];
			}
		}
	}
	return result;
}

