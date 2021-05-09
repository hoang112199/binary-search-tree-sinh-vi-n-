#include<iostream>
#include<string.h>

using namespace std;

float HighestScore = 0;
struct Node {
	int StuID;
	string Name;
	string Class;
	float Score;
	Node* LP, * RP;
};
typedef Node* PNode;
typedef PNode BSearchTree;
void Init(BSearchTree& Root)
{
	Root = NULL;
}

void Insert(BSearchTree& Root, int _StuID, string _Name, string _Class, float _Score)
{
	PNode Q;
	if (Root == NULL)
	{
		Q = new Node;
		Q->StuID = _StuID;
		Q->Name = _Name;
		Q->Class = _Class;
		Q->Score = _Score;
		Q->LP = NULL;
		Q->RP = NULL;
		Root = Q;
	}
	else
	{
		if (_StuID < Root->StuID)
		{
			Insert(Root->LP, _StuID, _Name, _Class, _Score);
		}
		else
		{
			Insert(Root->RP, _StuID, _Name, _Class, _Score);
		}
	}
}

void DeleteNode(PNode& P)
{
	PNode Q, R;
	if (P->LP == NULL && P->RP == NULL) {
		delete P;
	}
	else if (P->LP == NULL) {
		Q = P;
		P = P->RP;
		delete Q; return;
	}
	else if (P->RP == NULL)
	{
		Q = P;
		P = P->LP;
		delete Q; return;
	}
	else {
		Q = P->LP;
		if (Q->RP == NULL) {
			P->StuID = Q->StuID;
			P->Name = Q->Name;
			P->Class = Q->Class;
			P->Score = Q->Score;
			P->LP = Q->LP;
			delete Q; return;
		}
		else {
			do {
				R = Q;
				Q = Q->RP;
			} while (Q->RP != NULL);
			P->StuID = Q->StuID;
			P->Name = Q->Name;
			P->Class = Q->Class;
			P->Score = Q->Score;
			R->RP = Q->LP;
			delete Q; return;
		}
	}
}

void Delete(BSearchTree& Root,int _StuID)
{
	if (Root != NULL)
	{
		if (_StuID < Root->StuID) Delete(Root->LP, _StuID);
		else if (_StuID > Root->StuID) Delete(Root->RP, _StuID);
		else DeleteNode(Root);
	}
}

PNode SearchStuID(BSearchTree& Root, int _StuID)
{
	if (Root == NULL)
		return NULL;
	else
	{
		if (Root->StuID == _StuID)
			return Root;
		else if (_StuID < Root->StuID)
			return SearchStuID(Root->LP, _StuID);
		else
			return SearchStuID(Root->RP, _StuID);
	}
}

PNode SearchName(BSearchTree& Root, string _Name)
{
	if (Root == NULL)
		return NULL;
	if (Root->Name == _Name)
		return Root;
	SearchName(Root->LP, _Name);
	SearchName(Root->RP, _Name);
}

float _HighestScore(BSearchTree& Root)
{
	if (Root == NULL)
	{
		return HighestScore;
	}
	else
	{
		if (HighestScore < Root->Score)
			HighestScore = Root->Score;
		_HighestScore(Root->LP);
		_HighestScore(Root->RP);
	}
	return HighestScore;
}

void DisplayHighestScore(BSearchTree Root, float _Score)
{
	if (Root == NULL)
		return;
	if (Root->Score == _Score)
	{
		cout << "Ho Ten: " << Root->Name << endl;
		cout << "MSSV: " << Root->StuID << endl;
		cout << "Lop: " << Root->Class << endl;
		cout << "Diem: " << Root->Score << endl;
	}
	DisplayHighestScore(Root->LP, _Score);
	DisplayHighestScore(Root->RP, _Score);
}

void DisplayTreeStuID(BSearchTree& Root)
{
	if (Root == NULL)
		return;
	else {
		DisplayTreeStuID(Root->LP);
		cout << "Ho Ten: " << Root->Name << endl;
		cout << "MSSV: " << Root->StuID << endl;
		cout << "Lop: " << Root->Class << endl;
		cout << "Diem: " << Root->Score << endl;
		DisplayTreeStuID(Root->RP);
	}
}

void DisplayTree(BSearchTree& Root)
{
	if (Root == NULL)
		return;
	else {
		cout << "Ho Ten: " << Root->Name << endl;
		cout << "MSSV: " << Root->StuID << endl;
		cout << "Lop: " << Root->Class << endl;
		cout << "Diem: " << Root->Score << endl;
		DisplayTree(Root->LP);
		DisplayTree(Root->RP);
	}
}

void DisplayNode(PNode P)
{
	cout << "Ho Ten: " << P->Name << endl;
	cout << "MSSV: " << P->StuID << endl;
	cout << "Lop: " << P->Class << endl;
	cout << "Diem: " << P->Score << endl;
}

float TotalScore(BSearchTree Root) {
	float Sum = 0;
	if (Root == NULL) return Sum;
	else {
		Sum += Root->Score;
		Sum += TotalScore(Root->LP);
		Sum += TotalScore(Root->RP);
	} return Sum;
}
float Count(BSearchTree Root, int& count) {
	if (Root == NULL) return count;
	else {
		count++;
		Count(Root->LP, count);
		Count(Root->RP, count);
	} return count;
}


int main()
{
	BSearchTree T;
	Init(T);
	Insert(T, 3, "Hoang", "ET1", 9);
	Insert(T, 6, "Duc", "ET1", 5);
	Insert(T, 9, "Anh", "ET1", 7);
	Insert(T, 7, "Tuan", "ET1", 3);
	Insert(T, 2, "Viet", "ET1", 8);
	Insert(T, 1, "Cuong", "ET1", 10);
	Insert(T, 5, "Minh", "ET1", 4);
	cout << "thong tin toan bo sinh vien: " << endl;
	DisplayTree(T);
	cout << "xoa sinh vien mssv 6: " << endl;
	Delete(T, 6);
	DisplayTree(T);
	cout << "tim thong tin sinh vien ma so 2: " << endl;
	DisplayNode(SearchStuID(T, 2));
	cout << "tim thong tin sinh vien theo ten Hoang: " << endl;
	DisplayNode(SearchName(T, "Hoang"));
	cout << "Thong tin theo mssv tang dan: " << endl;
	DisplayTreeStuID(T);
	cout << "tim thong tin sinh vien co diem cao nhat: " << endl;
	DisplayHighestScore(T, _HighestScore(T));
	int x = 0;
	cout << "diem trung binh :" << TotalScore(T) / Count(T, x) << endl;
	return 0;
}