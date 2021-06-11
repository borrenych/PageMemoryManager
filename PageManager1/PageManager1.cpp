// PageManager.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Func.h";
#include <fstream>
using namespace std;

int main()
{


	InitMemory();
	int trapa1 = AllocMemory(3500);
	int trapa2 = AllocMemory(10000);
	FreeMemory(trapa1);
	int trapa3 = AllocMemory(5000);
	int trapa4 = AllocMemory(5000);
	int trapa5 = AllocMemory(10000);
	Dump();
	char a[3] = { 1,2,2 };
	char b[5] = { 3,0,11,3,4 };
	WriteMemory(trapa2, 9005, 3, a);
	WriteMemory(trapa3, 0, 5, b);
	WriteMemory(trapa4, 0, 3, a);
	//WriteMemory(trapa5, 4, 3, a);
	Dump();
}

