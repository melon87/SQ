#include "..\Header\Distance.h"


// dist_array�̃Z�b�g�A�b�v�{��
void Distance::init_Distinations() {
	// �̈�̊m��
	
	Distinations = new uchar*[node_num - 1];
	for (size_t s = 0; s < node_num - 1; s++){
		try {
			Distinations[s] = new uchar[node_num - 1 - s];
		}
		catch (const std::bad_alloc& e) {
			cout << (node_num - 1 - s) << e.what() << endl;
			int l;
			cin >> l;
		}
	}

	// ������
	if (PathFileExists(str_to_char(bin_filename))) {
		// ���Ƀt�@�C���v�Z���ʂ�ۑ��ς݂Ȃ�ǂݍ���
		cout << "n=" << dim << "�̋������t�@�C������ǂݍ��݂܂�...";
		load_file();
		cout << "ok" << endl;
	}
	else {
		// ������Όv�Z
		cout << "n=" << dim << "�̋������v�Z���܂�\t" << getTime() << "...";
		calc_distination();
		cout << "ok" << endl;
		// ���łɃt�@�C���ɕۑ����Ă���
		cout << "n=" << dim << "�̋������t�@�C���ۑ����܂�\t" << getTime() << "...";
		save_binary();
		cout << "ok" << endl;
	}
}

// �������t�@�C������ǂݍ���
void Distance::load_file() {
	ifstream fin(bin_filename, ios::in | ios::binary);

	if (!fin) {
		printf_s("%s���J���܂���\n", bin_filename.c_str());
		return;
	}
	
	for (size_t s = 0; s < node_num - 1; ++s) {
		fin.read((char *)Distinations[s], sizeof(uchar) * (node_num - s - 1));
	}

	fin.close();  //�t�@�C�������
}

// �������v�Z
void Distance::calc_distination() {
	for (size_t s = 0; s < node_num - 1; ++s) {
		for (size_t d = s + 1; d < node_num; ++d) {
			int tmp = SPR::GetMinimalExpansion(s, d, static_cast<int>(dim)).GetCount();
			Distinations[s][d - s - 1] = tmp;
		}
	}
}

// �t�@�C���ɕۑ�
void Distance::save_binary() {
	ofstream fout(bin_filename, ios::out | ios::binary | ios::trunc);

	if (!fout) {
		printf_s("%s���J���܂���\n", bin_filename.c_str());
		return;
	}

	for (size_t s = 0; s < node_num - 1; ++s) {
		fout.write((char *)Distinations[s], sizeof(uchar) * (node_num - s - 1));
	}

	fout.close();
}

// �R���X�g���N�^
Distance::Distance(size_t _dim) {
	dim = _dim;
	node_num = static_cast<int>(pow(2, dim));
	diameter = static_cast<int>(ceil((double)dim / 3) + 3);

	// �t�H���_�쐬
	string dir = "DistBin\\";
	char *dir_c = str_to_char(dir);
	if (!PathIsDirectoryEmpty(dir_c)) {
		CreateDirectory(dir_c, NULL);
	}

	bin_filename = dir + to_string(dim) + ".bin";

	// dist_array���g����悤�ɂ���
	init_Distinations();
}

// �f�X�g���N�^
Distance::~Distance() {
	// length_array�̉��
	if (Distinations != NULL) {
		for (size_t s = 0; s < node_num - 1; s++) {
			delete[] Distinations[s];
		}
		delete[] Distinations;
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
size_t Distance::get_distance(size_t s, size_t d) {
	int dist;
	if (s > d) {
		return Distinations[d][s - d - 1];
	}
	else if (s < d){
		return Distinations[s][d - s - 1];
	}
	else {
		return 0;
	}
}
