#include <Distance.h>

// dist_array�̃Z�b�g�A�b�v�{��
void Distance::init_dist_array() {
	// �̈�̊m��
	dist_array = new uchar*[node_num];
	for (size_t i = 0; i < node_num; i++)
	{
		dist_array[i] = new uchar[node_num];
	}

	// ������
	if (PathFileExists(str_to_wchar(bin_filename))) {
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
	for (int s = 0; s < node_num; ++s) {
		for (int d = 0; d < node_num; ++d) {
			fin.read((char *)&dist_array[s][d], sizeof(uchar));
		}
	}
	fin.close();  //�t�@�C�������
}

// �������v�Z
void Distance::calc_distination() {
	for (int s = 0; s < node_num; ++s) {
		for (int d = 0; d < node_num; ++d) {
			// �����m�[�h���m�E�����m�[�h�̑g�͌v�Z���Ȃ�
			if (s <= d) {
				if (s == d) dist_array[s][d] = 0;
				continue;
			}

			int tmp = SPR::GetMinimalExpansion(s, d, static_cast<int>(dim)).GetCount();
			dist_array[s][d] = tmp;
			dist_array[d][s] = tmp;
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
	for (int s = 0; s < node_num; ++s) {
		for (int d = 0; d < node_num; ++d) {
			fout.write((char *)&dist_array[s][d], sizeof(uchar));
		}
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
	wchar_t *dir_w = str_to_wchar(dir);
	if (!PathIsDirectoryEmpty(dir_w)) {
		CreateDirectory(dir_w, NULL);
	}

	bin_filename = dir + to_string(dim) + ".bin";

	// dist_array���g����悤�ɂ���
	init_dist_array();
}

// �f�X�g���N�^
Distance::~Distance() {
	// length_array�̉��
	if (dist_array != NULL) {
		for (size_t i = 0; i < node_num; i++)
		{
			delete[] dist_array[i];
		}
		delete[] dist_array;
	}
}

// dist_array��W���o��
void Distance::show_dist_array() {
	for (int s = 0; s < node_num; ++s) {
		for (int d = 0; d < node_num; ++d) {

			cout << static_cast<int>(dist_array[s][d]) << ' ';
		}
		cout << endl;
	}
}

// 2���_�Ԃ̋�����\����Ԃ�
uchar Distance::get_distance(size_t s, size_t d) {
	return dist_array[s][d];
}
