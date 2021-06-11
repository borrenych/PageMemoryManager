#include <iostream>
#include <fstream>
#include "Func.h"

using namespace std;

int H = 0;


char Memory[10000];
struct Pg {
	int handle;		//������������� �����
	int numPage;		// ���������� ����� �������� � �����
	int number;		//����� �������� �� 1 �� 29
	int uses;		//���������� �������� �� ���������
};

Pg Page[30] = { NULL };

void InitMemory()
{
	ofstream Mem("Virtual Memory.txt");
	for (int i = 0; i < 29; i++) {
		Page[i].number = i + 1;
		Page[i].handle = 0;
		Page[i].uses = 0;
	}
	Page[29].number = 0; //����������� ��������� �������� ������� number ��� "���������"
	Page[29].handle = 0;
	Page[29].uses = 0;
}

int AllocMemory(int sz)
{
	int z = 0;
	int k = 0; //����������� ���������� �������
	int kp = 0;// ��� �������� ���������� ����������� ������� ��� ���������
	if (sz % 1000 == 0)
		k = sz / 1000;
	else
		k = sz / 1000 + 1;
	for (int i = 0; i < 30; i++) //������� ������ ������� ��� ���������
	{
		if (kp == k)
			break;

		if (Page[i].handle == 0)
			kp++;
	}
	if (kp == k) //�������� ������ �������
	{
		H++;
		for (int i = 0; i < 30; i++) //������������� ��� ���������
		{
			if (k == 0)
				break;
			if (Page[i].handle == 0)
			{
				Page[i].uses = ++Page[i].uses;
				Page[i].handle = H;
				Page[i].numPage = ++z;
				k--;
			}
		}
		return H;
	}
	return 0;
}

void FreeMemory(int handle)
{
	for (int i = 0; i < 30; i++)
		if (Page[i].handle == handle)
		{
			Page[i].uses = 0;
			Page[i].handle = 0;
		}
}

int WriteMemory(int handle, int Offset, int Size, char* Data)
{
	int OfPage = 0;
	for (int i = 0; i < 30; i++)
	{
		OfPage = Offset / 1000 + 1;
		int offset = Offset % 1000;
		if ((Page[i].handle == handle) && (Page[i].numPage == OfPage))
		{
			Page[i].uses = ++Page[i].uses;
			if (i < 10)
			{

				int start = i * 1000 + offset;
				for (int g = 0; g < Size; g++)
				{
					Memory[start + g] = Data[g];
				}
			}
			else
			{
				int chg = changer(i);
				int start = chg * 1000;
				for (int g = 0; g < Size; g++)
					Memory[start + offset + g] = Data[g];
				
			}

		}
	}return 0;
}


int changer(int nb)
{
	int b = 0;
	int k = 0;
	int min = Page[0].uses;
	for (int i = 0; i <= 9; i++) //���������� ����� ������������ ��������
	{
		if (Page[i].uses <= min)
		{
			min = Page[i].uses;
			b = i;
		}
	}

	int start = b * 1000;
	fstream Mem;
	Mem.open("Virtual Memory.txt", ios::out | ios::in);
	if (Mem.is_open())
	{
		int startMem = 0;
		startMem = 19 * 1000;
		Page[29].handle = Page[b].handle;  //����������� �������� ��������� �������� ������� ��������
		Page[29].uses = Page[b].uses;
		Page[29].number = Page[b].number;
		Page[29].numPage = Page[b].numPage;

		for (int t = 0; t < 1000; t++)				//�������� ������ �� ���������������� �������� � �������
		{
			Mem.seekp(startMem + t, ios::beg);
			Mem.put(Memory[start + t]);
		}

		startMem = (nb - 10) * 1000;
		for (int t = 0; t < 1000; t++)					//������ ������ �� ������ �������� � ����������������
		{
			Mem.seekg(startMem + t, ios::beg);
			Mem.get(Memory[start + t]);
		}
	
		//Page[b].number = Page[nb].number;				//����������� ����� ������������ �������� � ����������� ������ �������� ��������� �������� � ����������� ������
		Page[b].handle = Page[nb].handle;
		Page[b].uses = Page[nb].uses;
		Page[b].numPage = Page[nb].numPage;
		
		//Page[nb].number = Page[29].number;		//����������� ������������ �������� �� ����. ������ �������� ������� ��������
		Page[nb].handle = Page[29].handle;
		Page[nb].uses = Page[29].uses;
		Page[nb].numPage = Page[29].numPage;

		startMem = 19 * 1000;
		start = (nb - 10) * 1000;
		for (int t = 0; t < 1000; t++)				//�������� ������ �� ������� �������� � ������������ � ���� ������
		{
			Mem.seekp(start + t, ios::beg);
			Mem.put(Memory[startMem + t]);
		}

		Page[29].handle = 0;  //����������� �������� ��������� �������� ������� ��������
		Page[29].uses = 0;
		Page[29].number = 0;
		Page[29].numPage = 0;
	}
	return b;
}

int ReadMemory(int handle, int Offset, int Size, char* Data)
{
	for (int i = 0; i < 30; i++)
	{
		if ((Page[i].handle == handle) && (Page[i].numPage == 1))
		{
			if (i < 10)
			{

				int start = i * 1000 + Offset;
				for (int g = 0; g < Size; g++)
				{
					cout << Memory[start + g];
				}
			}
			else
			{
				int chg = changer(i);
				int start = chg * 1000;
				for (int g = 0; g < Size; g++)
					cout << Memory[start + Offset + g];
			}Page[i].uses++;

		}
	}return 0;
}


void Dump(void)
{
	int flag = 0;
	for (int i = 1; i < H + 1; i++) 
	{
		for (int j = 0; j < 30; j++) 
		{
			if (Page[j].handle == i)
			{
				cout << "H: ";
				cout << Page[j].handle;
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			cout << " P: ";
			int sernum = 1;
			for (int j = 0; j < 30; j++) {
				if (Page[j].handle == i && Page[j].numPage == sernum) {
					cout << Page[j].number;
					if (j > 9)
						cout << "* ";
					else
						cout << " ";
					sernum++;
					j = 0;
				}
			}
			cout << "S: ";
			sernum = 1;
			for (int j = 0; j < 9; j++) {
				if (Page[j].handle == i && Page[j].numPage == sernum) {
					int start = j * 1000;
					for (int t = 0; t < 10; t++) {
						printf("%d", Memory[start + t]);
					}
				}
			}
		}
		cout << "\n";
	}

	/*for (int x = 0; x < 30; x++)
	{
		std::cout << "\nBlock";
		std::cout << "\nH: ";
		std::cout << Page[x].handle;
		std::cout << " P: ";
		std::cout << Page[x].number;
		std::cout << " LogPage: ";
		std::cout << Page[x].numPage;
		std::cout << " Uses: ";
		std::cout << Page[x].uses;
	

	}*/
}

