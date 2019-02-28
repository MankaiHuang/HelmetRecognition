#include "stdafx.h"
#include "TrainFiles.h"

TrainFiles::TrainFiles() 
{
	//
}

TrainFiles::~TrainFiles()
{

}

// ��δ��벻Ҫ���ڹ��캯����,��Ҫʱ�ٵ��ã��������·����Ҫ���ɶ�̬�ģ����ߴ������ļ��ж�ȡ��
bool TrainFiles::Load()
{
	//���ظ�Ŀ¼
	this->TRAIN_ROOT = "D:\\WalkerDetect\\";
	//��ȡ�����������ļ�
	std::ifstream pos_index_load(this->TRAIN_ROOT + "pos.txt");
	//��ȡ�����������ļ�
	std::ifstream neg_index_load(this->TRAIN_ROOT + "neg.txt");
	//��ȡ�������������ļ�
	std::ifstream back_index_load(this->TRAIN_ROOT + "back.txt");
	//��ȡñ�����������ļ�
	std::ifstream helmet_index_load(this->TRAIN_ROOT + "helmet.txt");
	//�����������������ļ�����
	loadPosNames(pos_index_load);
	loadNegNames(neg_index_load);
	loadBackNames(back_index_load);
	loadHelmetNames(helmet_index_load);

	return true;
}


std::vector<std::string> TrainFiles::getPosNames() {
	return this->pos_names;
}
std::vector<std::string> TrainFiles::getNegNames() {
	return this->neg_names;
}
std::vector<std::string> TrainFiles::getBackNames() {
	return this->back_names;
}
std::vector<std::string> TrainFiles::getHelmetNames() {
	return this->helmet_names;
}
std::string TrainFiles::getTrainRoot() {
	return this->TRAIN_ROOT;
}

void TrainFiles::loadPosNames(std::ifstream & fread) {
	//��ʱ�ļ���
	std::string buffer;
	while (!fread.eof()) {
		std::getline(fread, buffer);
		if (!buffer.empty()) {
			pos_names.push_back(buffer);
		}
	}
}
void TrainFiles::loadNegNames(std::ifstream & fread) {
	//��ʱ�ļ���
	std::string buffer;
	while (!fread.eof()) {
		std::getline(fread, buffer);
		if (!buffer.empty()) {
			neg_names.push_back(buffer);
		}
	}
}
void TrainFiles::loadBackNames(std::ifstream & fread) {
	//��ʱ�ļ���
	std::string buffer;
	while (!fread.eof()) {
		std::getline(fread, buffer);
		if (!buffer.empty()) {
			back_names.push_back(buffer);
		}
	}
}
void TrainFiles::loadHelmetNames(std::ifstream & fread) {
	//��ʱ�ļ���
	std::string buffer;
	while (!fread.eof()) {
		std::getline(fread, buffer);
		if (!buffer.empty()) {
			helmet_names.push_back(buffer);
		}
	}
}
