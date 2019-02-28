#pragma once

#include "TrainFiles.h"
#include "PreProcess.h"

class Mysvm : public CvSVM
{
public:
	static bool s_bTrain;

public:
	int get_alpha_count();
	int get_sv_dim();
	int get_sv_count();
	double* get_alpha();
	float** get_sv();
	float get_rho();
};

class SVMTraining 
{
public:
	//svmѵ�������캯��������������
	SVMTraining();

	virtual ~SVMTraining();

public:
	//svm��ʼѵ��
	bool train();

	//ͨ��svm���д�ż��
	void detect(cv::Mat & frame);

	//��������������ת��Ϊ����ʹ��ѵ���õ�svmģ�ͽ���Ԥ��
	cv::Mat sampleToConfig(cv::Rect r, cv::Mat src);

	//����ѵ�����������ļ���Ϊ������֤�����ռ�
	void loadTrainFilesAndExploreSpace();

	//����Ԥ������
	void loadPreProcess();

	//����HOG�����
	void loadHOGer();

	//ѵ��ʱ�����������ֵ�������ѵ���������У������ϱ�ǩ
	void withdrawFeatureAndLabel(int nums, std::vector<std::string> & filenames, int start, float label);

	//װ��ѵѵ������
	void LoadTrainSamples();

	//svmѵ����������ʼ��
	cv::SVMParams & SVMTrainorInitial();

public:

	//��ȡsvmѵ����
	Mysvm & getMysvm() {
		return this->svm_general;
	}

	//��ȡ���������
	cv::HOGDescriptor & getHOGDescriptor() {
		return this->hogdescriptor;
	}

private:
	//ѵ���ļ�
	TrainFiles trainfiles;

	//��������
	int Pos_Nums;
	//��������
	int Neg_Nums;
	//����������
	int Back_Nums;
	//ñ������
	int Helmet_Nums;

	//�������ļ���
	std::vector<std::string> PosNames;
	//�������ļ���
	std::vector<std::string> NegNames;
	//���������ļ���
	std::vector<std::string> BackNames;
	//ñ�������ļ���
	std::vector<std::string> HelmetNames;

	//������Ŀ¼
	std::string Train_File_Root;

	//HOG���������
	cv::HOGDescriptor hogdescriptor;

	//Ԥ������
	PreProcess preprocess;

	//SVMѵ����������->������-1������ñ�ˣ�1����δ��ñ�ˣ�2����ñ�ӣ�3��
	Mysvm svm_general;
	//��������������
	cv::Mat fetureOfSample_General;
	//��ǩ������
	cv::Mat labelOfSample_General;

};
