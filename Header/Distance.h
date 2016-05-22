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
	size_t dimension;
	size_t diameter;
	size_t node_num;

	uchar **Distance_array;
	string file_path;

	/*******************************
		dist_array�̃Z�b�g�A�b�v
	 *******************************/
	void init_Distance_array();	// �{��

	void calc_distance();	// �������v�Z

	void read_bin();	// �t�@�C������ǂݍ���
	void write_bin();	// �t�@�C���ɕۑ�


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