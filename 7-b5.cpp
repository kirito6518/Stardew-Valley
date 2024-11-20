/* 2351134 ��06 ������ */

/* ���������ϵͳ�ĺ궨�塢��Ҫ��ͷ�ļ��� */
#include <iostream>
#include <iomanip>
#include <cstring>
#include "read_stulist.h"
using namespace std;

#define MAX_FILENAME_LEN		512	//�����ļ�������󳤶�

class stu_list;
/* stu_metge ����ÿ��ѧ������Ϣ������ѧ�š�������������Ҫ��˽����Ϣ���������ݲ�׼�����ɼ����������Ҫ��������� */
class stu_merge {
private:
	int  stu_no;					//ѧ��
	char stu_name[MAX_NAME_LEN];  //����
	/* ���������private���ݳ�Ա����Ա�����Լ�������Ҫ������ */
	char first;
	char second[6];
	friend stu_list;
public:
	//���಻�������κεĹ������ݳ�Ա����Ա����
};

/* stu_list ������ѡ����Ϣ���������ݲ�׼�����ɼ����������Ҫ��������� */
class stu_list {
private:
	student list_round_1[MAX_STU_NUM];	//��һ��ѡ�ε�ѧ�������������򡢲�ȥ�أ�
	int list_num_1;						//��һ��ѡ�ε�ѧ������

	student list_round_2[MAX_STU_NUM];	//�ڶ���ѡ�ε�ѧ�������������򡢲�ȥ�أ�
	int list_num_2;						//�ڶ���ѡ�ε�ѧ������

	stu_merge list_merge[MAX_STU_NUM];	//�ϲ����ѧ��������ȥ�أ����������У�
	int list_merge_num;					//�ϲ����ѧ��������Ŀǰ����ӡ�����������ڲ������������Ҫ��Ҳ��Ҫɾ����

	/* ���������private���ݳ�Ա�ͳ�Ա����
	   ע�⣬���������array / set / map / vector��STL���� */

public:
	stu_list();										//���캯����������ɳ�ʼ�����ܣ��������Ҫ�������պ�������
	int read(const char* filename, const int round);	//���ļ��ж���ѡ����Ϣ��roundΪ1/2����ʾѡ���ִ�
	int print(const char* prompt = NULL);				//��ӡ���յ�ѡ������

	/* �������������public��Ա��������ʾ���ϲ���ȥ�ء�����ȣ�
	   �������幫�е����ݳ�Ա
	   �������ڳ�Ա������ʹ��array / set / map / vector��STL���� */
	void adding();
	void sorting();

};


//��ȫ��strcpy
char* tj_strcpy(char* s1, const char* s2)
{
	char* virs1 = s1;
	if (s1 == NULL)
		;
	else if (s2 == NULL) {
		*s1 = '\0';
	}
	else {
		while (*s2 != '\0') {
			*virs1 = *s2;
			virs1++;
			s2++;
		}
		*virs1 = '\0';
	}

	return s1;
}


/* --- ������Ը���stu_merge/stu_list������ĳ�Ա����������ʵ�� --- */


/***************************************************************************
  �������ƣ�
  ��    �ܣ����ļ��ж���ѡ����Ϣ��roundΪ1/2����ʾѡ���ִ�
  ���������
  �� �� ֵ��
  ˵    �������캯����������ɳ�ʼ�����ܣ��������Ҫ�������պ�������
***************************************************************************/
stu_list::stu_list()
{
	int i,j;
	for (i = 0; i < MAX_STU_NUM; i++) {
		list_merge[i].stu_no = 0;
		list_merge[i].first = '/';
		tj_strcpy(list_merge[i].second, "�˿�");
		list_round_1[i].no = 0;
		list_round_2[i].no = 0;

		for (j = 0; j < MAX_NAME_LEN; j++) {
			list_merge[i].stu_name[j] = 0;
			list_round_1[i].name[j] = 0;
			list_round_2[i].name[j] = 0;
		}
	}
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��̬���ӿ��ʹ�ã��������е��þ�̬���ӿ��е�Ԥ�ú���
  ���������
  �� �� ֵ��
  ˵    ��������������Ҫ�޸�
***************************************************************************/
int stu_list::read(const char* filename, const int round)
{
	int ret = 0;
	/* ��ȡ��1/2�ֵ�ѡ����������ӡ */
	switch (round) {
	case 1:
		this->list_num_1 = read_stulist(filename, this->list_round_1, MAX_STU_NUM);
		if (this->list_num_1 > 0)
			print_stulist("��һ��ѡ��������", this->list_round_1, this->list_num_1);
		else
			ret = -1;
		break;
	case 2:
		this->list_num_2 = read_stulist(filename, this->list_round_2, MAX_STU_NUM);
		if (this->list_num_2 > 0)
			print_stulist("�ڶ���ѡ��������", this->list_round_2, this->list_num_2);
		else
			ret = -1;
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}




//�ϲ���ȥ��
void stu_list::adding()
{
	int i,j,k;
	int judge1 = 0;
	int judge2 = 0;
	int x = 0;
	for (i = 0,x=0; list_round_1[x].no != 0; i++,x++) {
		list_merge[i].first = 'Y';
		for (k = 0; k < i; k++) {
			if (list_round_1[x].no == list_merge[k].stu_no) {
				judge1 = 1;
				break;
			}
		}
		if (judge1 == 0) {
			list_merge[i].stu_no = list_round_1[x].no;
			for (j = 0; list_round_1[x].name[j] != 0; j++) {
				list_merge[i].stu_name[j] = list_round_1[x].name[j];
			}
		}
		else {
			i--;
		}
		judge1 = 0;
	}
	
	judge1 = 0;
	judge2 = 0;
	for (x=0; list_round_2[x].no != 0; i++,x++) {
		for (k = 0; k < i; k++) {//�ж��Ƿ��ԭ�������ظ�
			if (list_round_2[x].no == list_merge[k].stu_no) {
				judge1 = 1;
				break;
			}
		}
		for (k = 0; list_round_1[k].no!=0; k++) {//�ж��Ƿ��ڵ�һ��ѡ��������
			
			if (list_round_2[x].no == list_round_1[k].no) {
				int t = 0;
				for (t = 0; list_merge[t].stu_no != list_round_1[k].no; t++)
					;
				tj_strcpy(list_merge[t].second, "Y");
				judge2 = 1;
				break;
			}

		}
		if (judge1 == 0) {
			list_merge[i].stu_no = list_round_2[x].no;
			for (j = 0; list_round_2[x].name[j]!=0; j++) {
				list_merge[i].stu_name[j] = list_round_2[x].name[j];
			}
		}
		else {
			i--;
		}
		if (judge2 == 0) {
			tj_strcpy(list_merge[i].second, "��ѡ");
		}
		judge1 = 0;
		judge2 = 0;
	}

}



//����
void stu_list::sorting()
{
	int i, j;
	for (i = 0; list_merge[i].stu_no != 0; i++) {
		for (j = i+1; list_merge[j].stu_no != 0; j++) {
			if (list_merge[i].stu_no > list_merge[j].stu_no) {
				stu_merge center;
				center = list_merge[i];
				list_merge[i] = list_merge[j];
				list_merge[j] = center;
			}
		}
	}
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ӡ���յ�ѡ������
***************************************************************************/
int stu_list::print(const char* prompt)
{
	if (prompt != NULL) {
		cout << prompt << endl;
	}	
	cout << setw(60) << setfill('=') << "="<<endl;
	cout << setfill(' ');
	cout << setw(5) << setiosflags(ios::left) << "���";
	cout<< setw(9) << setiosflags(ios::left) << "ѧ��";
	cout << setw(32) << setiosflags(ios::left) << "����";
	cout << setw(7) << setiosflags(ios::left) << "��һ��";
	cout << setw(7) << setiosflags(ios::left) << "�ڶ���" << endl;
	cout << setw(60) << setfill('=') << "="<<endl;
	int i;
	for (i = 0; list_merge[i].stu_no != 0; i++) {
		cout << setfill(' ');
		cout << setw(5) << setiosflags(ios::left) << i+1;
		cout << setw(9) << setiosflags(ios::left) << list_merge[i].stu_no;
		cout << setw(32) << setiosflags(ios::left) << list_merge[i].stu_name;
		cout << setw(7) << setiosflags(ios::left) << list_merge[i].first;
		cout << setw(7) << setiosflags(ios::left) << list_merge[i] .second<< endl;
	}
	return 0;
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char** argv)
{
	char file1[MAX_FILENAME_LEN], file2[MAX_FILENAME_LEN];

	cout << "������ǰһ��ѡ�ε������ļ� : ";
	gets_s(file1); //cin���ܶ��пո���ļ�

	cout << "�������һ��ѡ�ε������ļ� : ";
	gets_s(file2);

	stu_list list;

	/* �������� */
	if (list.read(file1, 1) < 0)
		return -1;
	if (list.read(file2, 2) < 0)
		return -1;

	/* �������� */
	list.adding();
	list.sorting();

	/* ��ӡ */
	list.print("����ѡ������");

	return 0;
}
