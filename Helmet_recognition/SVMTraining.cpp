#include "stdafx.h"
#include"SVMTraining.h"
#include<time.h>

bool Mysvm::s_bTrain = false;

int Mysvm::get_alpha_count()
{
	return this->sv_total;
}

int Mysvm::get_sv_dim()
{
	return this->var_all;
}

int Mysvm::get_sv_count()
{
	return this->decision_func->sv_count;
}

double* Mysvm::get_alpha()
{
	return this->decision_func->alpha;
}

float** Mysvm::get_sv()
{
	return this->sv;
}

float Mysvm::get_rho()
{
	return this->decision_func->rho;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

SVMTraining::SVMTraining() {
	//Ĭ��ѵ��ģ��xml�ļ��Ѿ����غã�����ѵ��
	loadPreProcess();
	loadHOGer();
}

SVMTraining::~SVMTraining()
{
	
}
//����ѵ�����������ļ���Ϊ������֤�����ռ�
void SVMTraining::loadTrainFilesAndExploreSpace() {
	//�ж��Ƿ���Ҫ����ѵ��
	if (Mysvm::s_bTrain) {
		this->trainfiles.Load();
		//����������Ŀ¼
		this->Train_File_Root = this->trainfiles.getTrainRoot();
		//����������
		this->PosNames = this->trainfiles.getPosNames();
		this->NegNames = this->trainfiles.getNegNames();
		this->BackNames = this->trainfiles.getBackNames();
		this->HelmetNames = this->trainfiles.getHelmetNames();
		//������������
		this->Pos_Nums = this->PosNames.size();
		this->Neg_Nums = this->NegNames.size();
		this->Back_Nums = this->BackNames.size();
		this->Helmet_Nums = this->HelmetNames.size();

		//����������
		this->fetureOfSample_General = cv::Mat::zeros(this->Pos_Nums +
			this->Neg_Nums +
			this->Back_Nums +
			this->Helmet_Nums,
			3780,
			CV_32FC1);
		//��ǩ������
		this->labelOfSample_General = cv::Mat::zeros(this->Pos_Nums +
			this->Neg_Nums +
			this->Back_Nums +
			this->Helmet_Nums,
			1,
			CV_32FC1);
	}
}
//����Ԥ������
void SVMTraining::loadPreProcess() {
	this->preprocess = PreProcess();
}
//����HOG�����
void SVMTraining::loadHOGer() {
	this->hogdescriptor = cv::HOGDescriptor(cv::Size(64, 128), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);
}


//��ѵ���������ϱ�ǩ
void SVMTraining::withdrawFeatureAndLabel(int nums, std::vector<std::string> & filenames, int start, float label) {
	//ԴͼƬsrc�;���Ԥ�����ͼƬtemp
	cv::Mat src, temp;
	//��ʱ��ͼƬ����ֵ
	std::vector<float> descriptors;
	//���㴦��ʱ��
	double begin_time;
	double end_time;
	double elapse_ms;
	//��ʼ����������ȡ����
	for (int i = 0; i < nums; i++) {
		//����ͼƬ
		src = cv::imread(this->Train_File_Root + filenames[i]);
		if (src.empty()) {
			std::cout << "�ļ���ȡ����" << this->Train_File_Root + filenames[i] << std::endl;
			continue;
		}
		//������ʼʱ��
		begin_time = (double)cv::getTickCount();
		//��һ����64��128
		cv::resize(src, src, cv::Size(64, 128));
		//ͼƬԤ����
		temp = preprocess.GrayAndGammaCoreect(src);
		//����ֵ����
		this->hogdescriptor.compute(temp, descriptors);
		//�������ʱ��
		end_time = (double)cv::getTickCount();
		//��ʾʱ��
		elapse_ms = (end_time - begin_time) * 1000 / cv::getTickFrequency();
		//���浽����������
		for (int j = 0; j < descriptors.size(); j++) {
			this->fetureOfSample_General.at<float>(start + i, j) = descriptors[j];
		}
		//���ϱ�ǩ
		this->labelOfSample_General.at<float>(start + i, 0) = label;
	}
}
//����ѵ������
void SVMTraining::LoadTrainSamples()
{
	if (Mysvm::s_bTrain) {
		//����ͼƬ����-1��ǩ
		this->withdrawFeatureAndLabel(this->Back_Nums, this->BackNames, 0, -1.0);
		//��ñ�˴���1��ǩ
		this->withdrawFeatureAndLabel(this->Pos_Nums, this->PosNames, this->Back_Nums, 1.0);
		//δ��ñ�˴���2��ǩ
		this->withdrawFeatureAndLabel(this->Neg_Nums, this->NegNames, this->Back_Nums + this->Pos_Nums, 2.0);
		//ñ�Ӵ���3��ǩ
		this->withdrawFeatureAndLabel(this->Helmet_Nums, this->HelmetNames, this->Back_Nums + this->Pos_Nums + this->Neg_Nums, 3.0);

		//SVMѵ�������ò���
		cv::SVMParams params = this->SVMTrainorInitial();

		//��ʼѵ��
		this->svm_general.train(this->fetureOfSample_General, this->labelOfSample_General, cv::Mat(), cv::Mat(), params);
		//����ѵ��ģ��
		this->svm_general.save(".\\xml\\Classifier_General.xml");
	}
	else {
		//����ѵ��ģ��
		this->svm_general.load(".\\xml\\Classifier_General.xml");
	}
}
//��ʼ��SVM����
cv::SVMParams & SVMTraining::SVMTrainorInitial()
{
	cv::SVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 2000, FLT_EPSILON);
	params.C = 0.01;
	return params;
}

bool SVMTraining::train() {

	LoadTrainSamples();

	Mysvm svm_temp;
	svm_temp.load(".\\xml\\Classifier_Back_Human.xml");

	int support_vector_num = svm_temp.get_support_vector_count();
	//��������ά��
	int var_count = svm_temp.get_var_count();
	//֧����������
	cv::Mat support_vector = cv::Mat::zeros(support_vector_num, var_count, CV_32FC1);
	//alpha
	cv::Mat alpha = cv::Mat::zeros(1, support_vector_num, CV_32FC1);
	//result
	cv::Mat result = cv::Mat::zeros(1, var_count, CV_32FC1);

	//���support_vector
	for (int i = 0; i < support_vector_num; i++) {
		const float * pSVDATA = svm_temp.get_support_vector(i);
		for (int j = 0; j < var_count; j++) {
			support_vector.at<float>(i, j) = pSVDATA[j];
		}
	}
	//���alpha
	double * pALPHADATA = svm_temp.get_alpha();
	for (int i = 0; i < support_vector_num; i++) {
		alpha.at<float>(0, i) = (float)pALPHADATA[i];
	}
	//���
	result = -1 * alpha * support_vector;
	//result = alpha * support_vector;
	//������γ�
	std::vector<float> mydetector;
	for (int i = 0; i < var_count; i++) {
		mydetector.push_back(result.at<float>(0, i));
	}
	//������ƫ����
	mydetector.push_back(svm_temp.get_rho());

	this->hogdescriptor.setSVMDetector(mydetector);

	return true;
}

void SVMTraining::detect(cv::Mat & frame) {
	std::vector<cv::Rect> found;
	cv::Mat temp = preprocess.GrayAndGammaCoreect(frame);
	hogdescriptor.detectMultiScale(temp, found, 0, cv::Size(16, 16));//��ͼƬ���ж�߶����˼��
	cv::Mat middle;
	int judge;

	for (int i = 0; i < found.size(); i++) {
		cv::Rect r = found[i];
		judge = -1;
		middle = sampleToConfig(r, temp);
		judge = (int)svm_general.predict(middle);
		cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 0, 255), 1);
		std::cout << judge << std::endl;
		switch (judge)
		{
		case 1:
			cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(255, 255, 255), 1);
			break;
		case 2:
			cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 0, 255), 1);
			break;
		case 3:
			cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 1);
			break;
		default:
			cv::rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 0, 255), 1);
			break;
		}
	}
}

cv::Mat SVMTraining::sampleToConfig(cv::Rect r, cv::Mat src)
{
	cv::Mat ROI = src(r);
	cv::Mat temp;
	cv::resize(ROI, temp, cv::Size(64, 128));
	std::vector<float> descriptors;
	hogdescriptor.compute(temp, descriptors);
	cv::Mat result(1, descriptors.size(), CV_32FC1);
	for (int i = 0; i < descriptors.size(); i++) {
		result.at<float>(0, i) = descriptors[i];
	}
	return result;
}


