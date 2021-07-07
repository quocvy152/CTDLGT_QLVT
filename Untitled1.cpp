#include <iostream>

using namespace std;

struct HocVien {
	string tenHV;
	float diemTB;
	string hang;
};

struct NodeHV {
	HocVien info;
	NodeHV* pNext = NULL;
};	
typedef NodeHV* PTRHV;

void XetHang(PTRHV &First) {
	for(PTRHV p = First; p != NULL; p = p->pNext) {
		if(p->info.diemTB >= 8.5 && p->info.diemTB <= 10)
			p->info.hang = "A";
		else if(p->info.diemTB >= 7.0 && p->info.diemTB <= 8.4)
			p->info.hang = "B";
		else if(p->info.diemTB >= 5.5 && p->info.diemTB <= 6.9)
			p->info.hang = "C";
		else if(p->info.diemTB >= 5.4 && p->info.diemTB <= 4.0)
			p->info.hang = "D";
		else
			p->info.hang = "F";
	}
}
