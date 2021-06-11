#pragma once
int AllocMemory(int sz);
void InitMemory();
void Dump(void);
void FreeMemory(int handle);
int WriteMemory(int handle, int Offset, int Size, char* Data);
int changer(int nb);
int ReadMemory(int handle, int Offset, int Size, char* Data);