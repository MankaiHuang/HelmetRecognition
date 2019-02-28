#pragma once
#include<fstream>
#include<iostream>
#include<vector>

class TrainFiles 
{
public :
	TrainFiles();
	virtual ~TrainFiles();

public:
	bool Load();

	std::vector<std::string> getPosNames();
	std::vector<std::string> getNegNames();
	std::vector<std::string> getBackNames();
	std::vector<std::string> getHelmetNames();

	std::string getTrainRoot();

private:
	void loadPosNames(std::ifstream & fread);
	void loadNegNames(std::ifstream & fread);
	void loadBackNames(std::ifstream & fread);
	void loadHelmetNames(std::ifstream & fread);
private :
	//ѵ��ͼƬ�ĸ�Ŀ¼
	std::string TRAIN_ROOT;
	//�����������������ļ���-> ����ȫñ����
	std::vector<std::string> pos_names;
	//�������и��������ļ���-> ����
	std::vector<std::string> neg_names;
	//�������б������ļ���-> ����
	std::vector<std::string> back_names;
	//�������а�ȫñ�������ļ���-> ��ȫñ
	std::vector<std::string> helmet_names;
};