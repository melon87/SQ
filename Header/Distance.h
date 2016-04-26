#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <atltime.h>

#include "Common.h"
#include "SPR.h"

using namespace std;




class Distance {
private:
	size_t dim;
	size_t diameter;
	size_t node_num;

	uchar **dist_array;
	string bin_filename;

	/*******************************
		dist_array�̃Z�b�g�A�b�v
	 *******************************/
	void init_dist_array();	// �{��

	void load_file();	// �t�@�C������ǂݍ���

	void calc_distination();	// �������v�Z

	void save_binary();	// �t�@�C���ɕۑ�


public:
	/***********************************
		�R���X�g���N�^�E�f�X�g���N�^
	************************************/
	Distance() {};

	Distance(size_t _dim);

	~Distance();


	/*************
		���̑�
	**************/
	// dist_array��W���o��
	void show_dist_array();

	// 2���_�Ԃ̋�����\����Ԃ�
	uchar get_distance(size_t s, size_t d);
};