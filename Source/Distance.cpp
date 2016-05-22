#include "..\Header\Distance.h"


// �S�̂̏�����
void Distance::init_Distance_array() {
	// �̈�̊m��
	Distance_array = new uchar*[node_num - 1];
	for (size_t s = 0; s < node_num - 1; s++) {
		Distance_array[s] = new uchar[node_num - 1 - s];
	}

	// ������
	if (PathFileExists(str_to_char(file_path))) {
		// ���Ƀt�@�C���v�Z���ʂ�ۑ��ς݂Ȃ�ǂݍ���
		cout << "n=" << dimension << "�̋������t�@�C������ǂݍ��݂܂�...";
		read_bin();
		cout << "ok" << endl;
	}
	else {
		// ������Όv�Z
		cout << "n=" << dimension << "�̋������v�Z���܂�\t" << getTime() << "...";
		calc_distance();
		cout << "ok" << endl;
		// ���łɃt�@�C���ɕۑ����Ă���
		cout << "n=" << dimension << "�̋������t�@�C���ۑ����܂�\t" << getTime() << "...";
		write_bin();
		cout << "ok" << endl;
	}
}

// �������t�@�C������ǂݍ���
void Distance::read_bin() {
	ifstream fin(file_path, ios::in | ios::binary);

	if (!fin) {
		cout << file_path << "���J���܂���" << endl;
		return;
	}
	
	for (size_t s = 0; s < node_num - 1; ++s) {
		fin.read((char *)Distance_array[s], sizeof(uchar) * (node_num - s - 1));
	}

	fin.close();  //�t�@�C�������
}

// �������v�Z
void Distance::calc_distance() {
	for (size_t s = 0; s < node_num - 1; ++s) {
		size_t row_size = node_num - s - 1;
		for (size_t d = 0; d < row_size; ++d) {
			uchar tmp = SPR::GetMinimalExpansion(s, d + s + 1, dimension).GetCount();
			Distance_array[s][d] = tmp;
		}
	}
}

// �t�@�C���ɕۑ�
void Distance::write_bin() {
	ofstream fout(file_path, ios::out | ios::binary | ios::trunc);

	if (!fout) {
		cout << file_path << "���J���܂���" << endl;
		return;
	}

	for (size_t s = 0; s < node_num - 1; ++s) {
		fout.write((char *)Distance_array[s], sizeof(uchar) * (node_num - s - 1));
	}

	fout.close();
}

// �R���X�g���N�^
Distance::Distance(size_t _dim) {
	dimension = _dim;
	node_num = 1 << dimension;
	diameter = static_cast<int>(ceil((double)dimension / 3) + 3);

	// �t�H���_�쐬(�������)
	string dir = "DistBin\\";
	char *dir_c = str_to_char(dir);
	if (!PathIsDirectoryEmpty(dir_c)) {
		CreateDirectory(dir_c, NULL);
	}

	file_path = dir + to_string(dimension) + ".bin";

	// dist_array���g����悤�ɂ���
	init_Distance_array();
}

// �f�X�g���N�^
Distance::~Distance() {
	// length_array�̉��
	if (Distance_array != NULL) {
		for (size_t s = 0; s < node_num - 1; s++)
		{
			delete[] Distance_array[s];
		}
		delete[] Distance_array;
	}
}

// dist_array��W���o��
void Distance::show_dist_array() {
	for (size_t s = 0; s < node_num; ++s) {
		for (size_t d = 0; d < node_num; ++d) {
			cout << get_distance(s, d) << ' ';
		}
		cout << endl;
	}
}

// 2���_�Ԃ̋�����\����Ԃ�
uchar Distance::get_distance(size_t s, size_t d) {
	if (s > d) {
		return Distance_array[d][s - d - 1];
	}
	else if (s < d){
		return Distance_array[s][d - s - 1];
	}
	else {
		return 0;
	}
}
