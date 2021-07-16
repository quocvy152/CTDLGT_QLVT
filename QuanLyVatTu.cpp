#include <iostream>
#include <string.h>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

// define constant
#define MAX_CTHD 20
#define MAX_NHANVIEN 500

#define TRUE 1
#define FALSE 0

// define num of keyboard
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SPACE 32

using namespace std;

// ====================================================================================
// =============================== TIEN ICH ===========================================
// ====================================================================================

struct Date {
	int ngay, thang, nam;
};

// ----------------------------------- chuan hoa chu ------------------------------------
// VD: stringBefore: "     phAm    quOC   Vy     " ==> expectResultString: "PHAM QUOC VY"
void ChuanHoaChu(string &a)
{
	while (a[0] == ' ')
	{
		a.erase(a.begin() + 0);
	}
	while (a[a.length() - 1] == ' ')
	{
		a.erase(a.begin() + a.length() - 1);
	}
	// kt giua
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ' && a[i + 1] == ' ')
		{
			a.erase(a.begin() + i + 1);
			i--;
		}
	}
	// ------------------------------------ bien doi chu hoa  ----------------------
	if (a[0] >= 97 && a[0] <= 122)
	{
		a[0] -= 32;
	}
	for (int i = 1; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			i++;
			if (a[i] >= 97 && a[i] <= 122)
			{
				a[i] -= 32;
			}
		}
		else if (a[i] >= 97 && a[i] <= 122)
		{
			a[i] -= 32;
		}
	}
}

// ------------------------------- bien doi thanh chu hoa ----------------------------
string BoKhoangTrang(string &a) {
	// N 18 D C C    N  -> N18DCCN
	// xoa khoang trang dau
	while(a[0] == ' ') {
		a.erase(a.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(a[a.length() - 1] == ' ') {
		a.erase(a.begin() + a.length() - 1);
	}
	for(int i = 0; i < a.length(); i++) {
		if(a[i] == ' ') {
			a.erase(a.begin() + i);
			i--;
		}
	}
	return a;
}

// kiem tra nam nhuan
bool laNamNhuan(int nam) {
	if((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
		return true;
	return false;
}

int tinhSoNgayTrongThang(Date date) {
	int soNgayTrongThang = 0;
	switch(date.thang) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			soNgayTrongThang = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			soNgayTrongThang = 30;
			break;
		case 2: 
			if(laNamNhuan(date.nam))
				soNgayTrongThang = 29;
			else 
				soNgayTrongThang = 28;
			break;
	}
	return soNgayTrongThang;
}

// kiem tra mot ngay co hop le hay khong
bool laNgayHopLe(Date date) {
	if(date.nam < 0)
		return false;
	
	if(date.thang < 1 || date.thang > 12) 
		return false;
		
	if(date.ngay < 1 || date.ngay > tinhSoNgayTrongThang(date))
		return false;
		
	return true;
}

// ====================================================================================
// ================================= CHI TIET HOA DON =================================
// ====================================================================================
struct ChiTietHoaDon {
	string maVT;
	float soLuong;
	int donGia;
	float VAT;
};

struct DSChiTietHoaDon {	
	int sl = 0;				
	ChiTietHoaDon ds[MAX_CTHD];
};

// ====================================================================================
// ==================================== DS HOA DON ====================================
// ====================================================================================
struct HoaDon {
	string soHD;
	Date ngayLap;
	string loai; // chi nhan X va N (X: xuat, N: Nhan)
	DSChiTietHoaDon dsChiTietHoaDon;
};

struct NodeHD {
	HoaDon info;
	NodeHD* pNext = NULL;
};	
typedef NodeHD* PTRHD;

struct DSHoaDon
{
	PTRHD FirstHD = NULL;
	int sl = 0;
};

// ====================================================================================
// ==================================== DS NHAN VIEN ==================================
// ====================================================================================
struct NhanVien {
	string maNV;
	string ho;
	string ten;
	string phai;
	DSHoaDon DSHD;
};

struct DSNhanVien {
	NhanVien* nv[MAX_NHANVIEN];
	int sl = 0;
};

// ====================================================================================
// ====================================== DS VAT TU ===================================
// ====================================================================================
struct VatTu {
	string maVT;
	string tenVT;
	string dvt;
	float slTon;
};
struct nodeVatTu {
	VatTu info;	
	nodeVatTu* pLeft;
	nodeVatTu* pRight;
};
typedef nodeVatTu* TREE;

struct DSVatTu
{
	TREE TREE_VT = NULL;
	int sl = 0;
};

// ====================================================================================
// =================================== GHI FILE =======================================
// ====================================================================================

// ================================ GHI FILE VAT TU ===================================
void ghiFileNLR(ofstream &outFile, TREE TREE_VT) {
	if(TREE_VT != NULL) {
		outFile << TREE_VT->info.maVT << ",";
		outFile << TREE_VT->info.tenVT << ",";
		outFile << TREE_VT->info.slTon << ",";
		outFile << TREE_VT->info.dvt << "\n";
		ghiFileNLR(outFile, TREE_VT->pLeft);
		ghiFileNLR(outFile, TREE_VT->pRight);
	}
}

void ghiFileDSVT(DSVatTu &DSVT) {
	ofstream outFile;
	outFile.open("DSVT.txt", ios::out);
	outFile << DSVT.sl << "\n";
	ghiFileNLR(outFile, DSVT.TREE_VT);
	outFile.close();
}

// ====================================================================================
// ======================================= VAT TU =====================================
// ====================================================================================

//-------------------------------- ham khoi tao node nhan vien ------------------------
TREE KhoiTaoNodeVT () {
	nodeVatTu *p = new nodeVatTu;
	p->pRight = NULL;
	p->pLeft = NULL;
	return p;
}

// ham tim va tra ve node vat tu khi trung
TREE timNodeVT(TREE TREE_VT, string maVT)
{
	if (TREE_VT != NULL) 
	{
		if(maVT.compare(TREE_VT->info.maVT) == 0)
		{
			return TREE_VT;
		}
		else if(maVT.compare(TREE_VT->info.maVT) > 0)
		{
			return timNodeVT(TREE_VT->pRight, maVT);
		}
		else if(maVT.compare(TREE_VT->info.maVT) < 0)
		{
			return timNodeVT(TREE_VT->pLeft, maVT);
		}
	} 
	else
	{
		return NULL;
	}
}

void chuyenCaySangMang(TREE TREE_VT, VatTu *vt[], int &nVT) {
	if(TREE_VT != NULL) {
		vt[nVT] = new VatTu;
		vt[nVT]->maVT = TREE_VT->info.maVT;
		vt[nVT]->tenVT = TREE_VT->info.tenVT;
		vt[nVT]->dvt = TREE_VT->info.dvt;
		vt[nVT]->slTon = TREE_VT->info.slTon;
		nVT++;
		chuyenCaySangMang(TREE_VT->pLeft, vt, nVT);
		chuyenCaySangMang(TREE_VT->pRight, vt, nVT);
	}
}

void hoanViHaiVT(nodeVatTu *a, nodeVatTu *b) {
	nodeVatTu *temp = new nodeVatTu;
	
	temp->info = a->info;
	a->info = b->info;
	b->info = temp->info;
	
	delete temp; 
}

// sap xep vat tu theo ten tang dan
void sapXepVT(VatTu *vt[], int &nVT) {
	VatTu *temp;
	for(int i = 0; i < nVT - 1; i++) {
		for(int j = i + 1; j < nVT; j++) {
			if(vt[i]->tenVT.compare(vt[j]->tenVT) > 0) {
				temp = vt[i];
				vt[i] = vt[j];
				vt[j] = temp;
			}
		}
	}
}

bool kiemTraTrungMaVT(TREE TREE_VT, string maVT) {
	if(TREE_VT != NULL) {
		if(maVT.compare(TREE_VT->info.maVT) == 0)
			return true;
		
		else if(maVT.compare(TREE_VT->info.maVT) > 0)
			return kiemTraTrungMaVT(TREE_VT->pRight, maVT);
			
		else
			return kiemTraTrungMaVT(TREE_VT->pLeft, maVT);
	} else return false;
}

void themMotVatTu(TREE &TREE_VT, nodeVatTu *p) {
	if(!TREE_VT)
		TREE_VT = p;
	else {
		if(p->info.maVT.compare(TREE_VT->info.maVT) > 0)
			themMotVatTu(TREE_VT->pRight, p);
		else if(p->info.maVT.compare(TREE_VT->info.maVT) < 0)
			themMotVatTu(TREE_VT->pLeft, p);
	}
}

string taoMaVT(TREE TREE_VT) {
	string formatMaVT = "VT0000000000";
	do {
		for (int i = 2; i < formatMaVT.length(); i++)
			formatMaVT[i] = rand() % (4) + 48;
	} while (kiemTraTrungMaVT(TREE_VT, formatMaVT) == true); // kiem tra ma vat tu trung thi tao ma moi
	return formatMaVT;
}

void nhapVatTu(DSVatTu &DSVT){
	nodeVatTu *p = KhoiTaoNodeVT();
	cin.ignore();
	p->info.maVT = taoMaVT(DSVT.TREE_VT);
	cout << "Ma vat tu: " << p->info.maVT << endl;
	cout << "Nhap ten vat tu: "; getline(cin, p->info.tenVT);
	cout << "Nhap don vi tinh: "; getline(cin, p->info.dvt);
	cout << "Nhap so luong ton: "; cin >> p->info.slTon;
	
	ChuanHoaChu(p->info.tenVT);
	ChuanHoaChu(p->info.dvt);
	
	themMotVatTu(DSVT.TREE_VT, p);
	DSVT.sl++;
}

void xuatDanhSachVT(VatTu *vt[], int nVT){
	for(int i = 0; i < nVT; i++) {
		cout << "------------ VAT TU " << i + 1 << " --------------" << endl;
		cout << "Ma vat tu: " << vt[i]->maVT << endl;
		cout << "Ten vat tu: " << vt[i]->tenVT << endl;
		cout << "Don vi tinh: " << vt[i]->dvt << endl;
		cout << "So luong ton: " << vt[i]->slTon << endl << endl;
	}
}

void giaiPhongDSVatTu(VatTu *vt[], int nVT) {
	for(int i = 0; i < nVT; i++)
		delete vt[i];
}

void nodeTheMang(TREE TREE_VT, nodeVatTu *&x) {
	if(TREE_VT->pLeft != NULL) {
		nodeTheMang(TREE_VT->pLeft, x);
	} else { //  tim duoc node trai cung cua cay con phai
		hoanViHaiVT(TREE_VT, x);
		x = TREE_VT;
		TREE_VT = TREE_VT->pRight;
	}
}

void xoaMotVatTu(TREE &TREE_VT, string maVT) {
	if(TREE_VT != NULL) {
		if(maVT.compare(TREE_VT->info.maVT) == 0) {
			nodeVatTu *x = TREE_VT;
			
			// neu cay con trai cua node can xoa NULL
			if(TREE_VT->pLeft == NULL)
				TREE_VT = TREE_VT->pRight;
			// neu cay con phai cua node can xoa NULL
			else if(TREE_VT->pRight == NULL)
				TREE_VT = TREE_VT->pLeft;
			// neu ca 2 cay con cua not can xoa khong NULL thi can tim nut the mang
			else if(TREE_VT->pLeft != NULL && TREE_VT->pRight != NULL) {
				// tim node the mang: trai cung cua cay con phai
				nodeTheMang(TREE_VT->pRight, x);
			}
			delete x;
		} else if(maVT.compare(TREE_VT->info.maVT) > 0) {
			xoaMotVatTu(TREE_VT->pRight, maVT);
		} else if(maVT.compare(TREE_VT->info.maVT) < 0) {
			xoaMotVatTu(TREE_VT->pLeft, maVT);
		}
	}
}

void xoaVatTu(DSVatTu &DSVT) {
	string maVT;
	cout << "Nhap ma Vat Tu: ";
	cin.ignore();
	getline(cin, maVT);
	
 	if(!kiemTraTrungMaVT(DSVT.TREE_VT, maVT)) {
		cout << "MA VAT TU KHONG TON TAI!" << endl;
	} else {
		xoaMotVatTu(DSVT.TREE_VT, maVT);
		DSVT.sl--;
		cout << "XOA THANH CONG!" << endl;
	}
	system("pause");
}

void hieuChinhMotVatTu(TREE &TREE_VT, string maVT) {
	if(TREE_VT != NULL) {
		if(maVT.compare(TREE_VT->info.maVT) == 0) {
			
			cin.ignore();
			cout << "Nhap ten vat tu hieu chinh: ";
			getline(cin, TREE_VT->info.tenVT);
			cout << "Nhap don vi tinh vat tu hieu chinh: ";
			getline(cin, TREE_VT->info.dvt);
			
			ChuanHoaChu(TREE_VT->info.tenVT);
			ChuanHoaChu(TREE_VT->info.dvt);
			
		} else if(maVT.compare(TREE_VT->info.maVT) > 0) {
			hieuChinhMotVatTu(TREE_VT->pRight, maVT);
		} else if(maVT.compare(TREE_VT->info.maVT) < 0) {
			hieuChinhMotVatTu(TREE_VT->pLeft, maVT);
		}
	}
}

void hieuChinhVatTu(DSVatTu &DSVT) {
	string maVT;
	cin.ignore();
	cout << "Nhap ma vat tu can hieu chinh: ";
	getline(cin, maVT);
	bool trungMaVT = kiemTraTrungMaVT(DSVT.TREE_VT, maVT);
	if(trungMaVT) {
		hieuChinhMotVatTu(DSVT.TREE_VT, maVT);
	} else {
		cout << "MA VAT TU KHONG TON TAI!" << endl;
	}
	system("pause");
}

// ====================================================================================
// ====================================== NHAN VIEN ===================================
// ====================================================================================

// -------------------------- kiem tra trung ma nhan vien -----------------------------
int kiemTraMaNV(DSNhanVien DSNV, string maNVKT) {
	for (int i = 0; i < DSNV.sl; i++)
		if (DSNV.nv[i]->maNV.compare(maNVKT) == 0)
			return i;
	return -1;
}

//-------------------------- tao ma nhan vien tu dong ---------------------------------
string taoMaNV(DSNhanVien DSNV) {
	string formatMaNV = "NV00000000";
	do {
		for (int i = 2; i < formatMaNV.length(); i++)
			formatMaNV[i] = rand() % (10) + 48;
	} while (kiemTraMaNV(DSNV, formatMaNV) >= 0); // kiem tra ma nhan vien trung thi tao ma moi
	return formatMaNV;
}

//------------------------- them mot nhan vien -----------------------------------------
void themMotNV(DSNhanVien &DSNV, NhanVien* nv) {
	DSNV.nv[DSNV.sl] = nv;
	DSNV.sl++;
}

//------------------------- them nhan vien vao danh mang con tro ------------------------
int nhapNhanVien(DSNhanVien &DSNV) {
	cout << endl;
	if(DSNV.sl == MAX_NHANVIEN) {
		cout << "THEM NHAN VIEN THAT BAI! DANH SACH DAY!" << endl;
		getch();
	} else {
		cout << "  NHAP NHAN VIEN  " << endl;
		
		NhanVien* p = new NhanVien;
		p->maNV = taoMaNV(DSNV);
		cout << "Ma nhan vien: " << p->maNV << endl;
		cin.ignore();
		cout << "Nhap ho nhan vien:  ";
		getline(cin, p->ho);
		cout << "Nhap ten nhan vien:  ";
		getline(cin, p->ten);
		cout << "Nhap gioi tinh nhan vien:  ";
		getline(cin, p->phai);
		
		ChuanHoaChu(p->ho);
		ChuanHoaChu(p->ten);
		ChuanHoaChu(p->phai);
		
		themMotNV(DSNV, p);
		cout << "  THEM THANH CONG  " << endl;
	}
}

void hoanViHaiNV(NhanVien *&p, NhanVien *&q) {
	NhanVien* tam = new NhanVien;
	
	tam->ho = p->ho;
	tam->maNV = p->maNV;
	tam->ten = p->ten;
	tam->phai = p->phai;
	tam->DSHD.FirstHD = p->DSHD.FirstHD;

	p->ho = q->ho;
	p->maNV = q->maNV;
	p->ten = q->ten;
	p->phai = q->phai;
	p->DSHD.FirstHD = q->DSHD.FirstHD;

	q->ho = tam->ho;
	q->maNV = tam->maNV;
	q->ten = tam->ten;
	q->phai = tam->phai;
	q->DSHD.FirstHD = tam->DSHD.FirstHD;
	
	delete tam;
}

void sapXepNhanVien(DSNhanVien &DSNV)
{
	for (int i = 0; i < DSNV.sl - 1; i++)
	{
		for (int j = i + 1; j < DSNV.sl; j++)
		{
			if (DSNV.nv[i]->ten > DSNV.nv[j]->ten)
			{
				hoanViHaiNV(DSNV.nv[i], DSNV.nv[j]);
			}
			else if (DSNV.nv[i]->ten == DSNV.nv[j]->ten)
			{
				if (DSNV.nv[i]->ho > DSNV.nv[j]->ho)
				{
					hoanViHaiNV(DSNV.nv[i], DSNV.nv[j]);
				}
			}
		}
	}
}
 
//------------------------- xuat danh sach nhan vien -----------------------------------
void xuatDSNV(DSNhanVien &DSNV) {
	if(DSNV.sl == 0) {
		cout << "DANH SACH NHAN VIEN RONG!" << endl;
		return;
	}
	
	for(int i = 0; i < DSNV.sl; i++) {
		cout << endl << "------------------- NHAN VIEN " << i + 1 << "-------------------" << endl;
		cout << "Ma nhan vien: " << DSNV.nv[i]->maNV << endl;
		cout << "Ho nhan vien: " << DSNV.nv[i]->ho << endl;
		cout << "Ten nhan vien: " << DSNV.nv[i]->ten << endl;
		cout << "Gioi tinh nhan vien: " << DSNV.nv[i]->phai << endl << endl;
	}
}

//----------------------------- hieu chinh nhan vien ------------------------------------
void hieuChinhNhanVien(DSNhanVien &DSNV)
{
	if(DSNV.sl == 0) {
		cout << "DANH SACH NHAN VIEN RONG!" << endl;
		return;
	}
NhapLai:
	string maNVKT;
	cout << "Nhap ma nhan vien can hieu chinh: ";
	cin >> maNVKT;
	int vt = kiemTraMaNV(DSNV, maNVKT);
	if (vt < 0) {
		cout << "NHAN VIEN KHONG TON TAI!! " << endl;
		goto NhapLai;
	} else {
		cin.ignore();
		string hoCN, tenCN, gtCN;
		cout << "Ho nhan vien       : " << DSNV.nv[vt]->ho << endl;
		cout << "Ten nhan vien      : " << DSNV.nv[vt]->ten << endl;
		cout << "Gioi tinh nhan vien: " << DSNV.nv[vt]->phai << endl;
		
		cout << "Ho nhan vien cap nhat  	 : "; getline(cin, hoCN);
		cout << "Ten nhan vien cap nhat      : "; getline(cin, tenCN);
		cout << "Gioi tinh nhan vien cap nhat: "; getline(cin, gtCN);
		
		DSNV.nv[vt]->ho = hoCN;
		DSNV.nv[vt]->ten = tenCN;
		DSNV.nv[vt]->phai = gtCN;
		
		ChuanHoaChu(DSNV.nv[vt]->ho);
		ChuanHoaChu(DSNV.nv[vt]->ten);
		ChuanHoaChu(DSNV.nv[vt]->phai);
		
		cout << "THAY DOI THANH CONG! " << endl;
	}
}

//---------------------------------- xoa nhan vien -------------------------------------


// ====================================================================================
// ====================================== HOA DON =====================================
// ====================================================================================

// them 1 hoa don
void themMotHD(PTRHD &FirstHD, PTRHD p)
{
	if (FirstHD == NULL)
	{
		FirstHD = p;
	}
	else
	{
		for (PTRHD p = FirstHD; p != NULL; p = p->pNext)
		{
			if (p->pNext == NULL)
			{
				p->pNext = p;
			}
		}
	}
}

// khoi tao hoa don
PTRHD khoiTaoNodeHD()
{
	PTRHD p = new NodeHD;
	p->pNext = NULL;
	return p;
}

// luot qua tung hoa don cua tung nhan vien
bool ktTrungMaHD(DSNhanVien DSNV, string soHD) {
	for(int i = 0; i < DSNV.sl; i++)
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext)
			if (p->info.soHD == soHD)
				return true;
	return false;
}

string taoMaHD(DSNhanVien DSNV) {
	string tempSoHD = "HD00000000";
	do {
		for (int i = 2;i < tempSoHD.length(); i++)
			tempSoHD[i] = rand() % (10) + 48;
	} while (ktTrungMaHD(DSNV, tempSoHD) == true);
	return tempSoHD;
}

// =============== them 1 chi tiet hoa don ==================
int themMotCTHD(DSChiTietHoaDon &DSCTHD, ChiTietHoaDon CTHD)
{  
	// neu danh sach day
	if (DSCTHD.sl == MAX_CTHD)
		return 0;
	
	DSCTHD.ds[DSCTHD.sl] = CTHD;
	DSCTHD.sl++;
	
	return 1;
}

//======================== lap hoa don ======================
void lapHoaDon(DSNhanVien &DSNV, DSVatTu &DSVT)
{
	string maNV;
	cin.ignore();
	cout << "Nhap ma nhan vien lap hoa don: ";
	getline(cin, maNV);
	int vtNVLap = kiemTraMaNV(DSNV, maNV);
	
	// neu ma nhan vien khong ton tai
	if (vtNVLap == -1)
	{
		cout << "MA NHAN VIEN KHONG TON TAI!" << endl;
		system("pause");
	}
	else
	{
		//xu ly lap hoa don
		PTRHD p = khoiTaoNodeHD();
		bool nhap;
		bool ktw = true;
		while (ktw == true)
		{
			system("cls");
			cout << "1. Hoa Don nhap" << endl;
			cout << "2. Hoa don xuat" << endl;
			int x;
			cout << "Nhap loai hoa don: ";
			cin >> x;
			switch (x) {
				case 1: {
					cout << "Loai hoa don: Nhap" << endl;
					nhap = true;
					p->info.loai = "N";
					ktw = false;
					break;
				}
				case 2: {
					cout << "Loai hoa don: Xuat" << endl;
					nhap = false;
					p->info.loai = "X";
					ktw = false;
					break;
				}
			}
		}
		//====================== 
		p->info.soHD = taoMaHD(DSNV);
		cout << "Ma hoa don: " << p->info.soHD << endl;
		cin.ignore();
		do {
			cout << "Nhap Ngay Lap Hoa Don " << endl;
			cout << "Nhap ngay: ";
			cin >> p->info.ngayLap.ngay;
			cout << "Nhap thang: ";
			cin >> p->info.ngayLap.thang;
			cout << "Nhap nam: ";
			cin >> p->info.ngayLap.nam;
			
			if(laNgayHopLe(p->info.ngayLap) == false)
				cout << "NGAY BAN VUA NHAP KHONG HOP LE!" << endl;
		
		} while(laNgayHopLe(p->info.ngayLap) == false);
		
		//--------- them hd vao ds hoa don --------
		themMotHD(DSNV.nv[vtNVLap]->DSHD.FirstHD, p);
		cout << "LAP HOA DON THANH CONG! NHAN PHIM BAT KI DE TIEP TUC NHAP CHI TIET HOA DON" << endl;
		getch();
		cout << endl << "Hoa Don: " << p->info.loai << " Ma Hoa Don: " << p->info.soHD << " Ngay Lap Hoa Don: " << p->info.ngayLap.ngay << "/" << p->info.ngayLap.thang << "/" << p->info.ngayLap.nam << endl;
		
		
		//----- lap chi tiet hoa don --------------
		// hoa don nhap
		if(nhap) {
			ChiTietHoaDon CTHD;
			cout << endl;
NhapCTHDNhap:
			cin.ignore();
			cout << "Nhap ma vat tu: ";
			getline(cin, CTHD.maVT);
			
			TREE tree = timNodeVT(DSVT.TREE_VT, CTHD.maVT);
			
			if(!tree) {
				cout << "MA VAT TU KHONG TON TAI! VUI LONG NHAP LAI" << endl;
				goto NhapCTHDNhap;
			} else {
				cout << "Nhap so luong: ";
				cin >> CTHD.soLuong; cout << endl;
				cout << "Nhap don gia: ";
				cin >> CTHD.donGia; cout << endl;
				cout << "Nhap VAT: ";
				cin >> CTHD.VAT; cout << endl;
				
				int trangThaiThem = themMotCTHD(p->info.dsChiTietHoaDon, CTHD);
				
				if(!trangThaiThem) {
					cout << "THEM CHI TIET HOA DON THAT BAI. HOA DON DAY" << endl;
					getch();
					return;
				} else {
					// tinh toan cap nhat lai so luong ton
					float slTonBanDau = tree->info.slTon;
					float slNhapThem = CTHD.soLuong;
					tree->info.slTon = slTonBanDau + slNhapThem;
					
					cout << "THEM CHI TIET HOA DON THANH CONG! BAN CO MUON TIEP TUC NHAP CHI TIET HOA DON?" << endl;
					
					string tiepTuc;
					cin.ignore();
					cout << "CHON Y/N (Y: tiep tuc nhap ----- N: ket thuc nhap)  :";
					getline(cin, tiepTuc);
					
					if(tiepTuc == "Y" || tiepTuc == "y") 
						goto NhapCTHDNhap;
					else if(tiepTuc == "N" || tiepTuc == "n") {
						cout << "KET THUC VIEC NHAP!" << endl;
						cout << "BAN CO MUON LUU HOA DON KHONG?" << endl; 
						
						string luu;
						cout << "CHON Y/N (Y: tiep tuc nhap ----- N: ket thuc nhap)  :";
						getline(cin, luu);
						
						if(luu == "Y" || luu == "y") 
						{
							ghiFileDSVT(DSVT);
							cout << "GHI FILE THANH CONG!" << endl;
						}
						else if(luu == "N" || luu == "n") 
						{
							cout << "BAN DA HUY HOA DON. GHI FILE KHONG THANH CONG!" << endl;
							return;
						}
					}	
				}
				
			}
		} else { // hoa don xuat
			ChiTietHoaDon CTHD;
			cout << endl;
NhapCTHDXuat:
			cin.ignore();
			cout << "Nhap ma vat tu: ";
			getline(cin, CTHD.maVT);
			
			TREE tree = timNodeVT(DSVT.TREE_VT, CTHD.maVT);
			
			if(!tree) 
			{
				cout << "MA VAT TU KHONG TON TAI! VUI LONG NHAP LAI" << endl;
				goto NhapCTHDXuat;
			} 
			else 
			{
				cout << "Nhap so luong: ";
				cin >> CTHD.soLuong; cout << endl;
				cout << "Nhap don gia: ";
				cin >> CTHD.donGia; cout << endl;
				cout << "Nhap VAT: ";
				cin >> CTHD.VAT; cout << endl;
				
				int trangThaiThem = themMotCTHD(p->info.dsChiTietHoaDon, CTHD);
				
				if(!trangThaiThem) 
				{
					cout << "THEM CHI TIET HOA DON THAT BAI. HOA DON DAY" << endl;
					getch();
					return;
				} 
				else 
				{
					// tinh toan cap nhat lai so luong ton
					float slTonBanDau = tree->info.slTon;
					float slXuatRa = CTHD.soLuong;
					
					if(slTonBanDau < slXuatRa) 
					{
						cout << "SO LUONG VAT TU TRONG KHO KHONG DU!" << endl;
						cout << "So Luong Ton " << tree->info.tenVT << "Hien Co: " << tree->info.slTon << endl;
						getch();
						goto NhapCTHDXuat;
					} 
					else 
					{
						tree->info.slTon = slTonBanDau - slXuatRa;
						
						cout << "THEM CHI TIET HOA DON THANH CONG! BAN CO MUON TIEP TUC NHAP CHI TIET HOA DON?" << endl;
					
						string tiepTuc;
						cin.ignore();
						cout << "CHON Y/N (Y: tiep tuc nhap ----- N: ket thuc nhap)  :";
						getline(cin, tiepTuc);
						
						if(tiepTuc == "Y" || tiepTuc == "y") 
							goto NhapCTHDXuat;
						else if(tiepTuc == "N" || tiepTuc == "n") {
							cout << "KET THUC VIEC NHAP!" << endl;
							cout << "BAN CO MUON LUU HOA DON KHONG?" << endl; 
							
							string luu;
							cout << "CHON Y/N (Y: tiep tuc nhap ----- N: ket thuc nhap)  :";
							getline(cin, luu);
							
							if(luu == "Y" || luu == "y") 
							{
								ghiFileDSVT(DSVT);
								cout << "GHI FILE THANH CONG!" << endl;
							}
							else if(luu == "N" || luu == "n") 
							{
								cout << "BAN DA HUY HOA DON. GHI FILE KHONG THANH CONG!" << endl;
								return;
							}
						}	
					}
				}
			}
		}
	}
}

// =====================================================================================
// ===================================== DOC FILE ======================================
// =====================================================================================

// =============================== DOC FILE NHAN VIEN ==================================
void DocFileDSNV(DSNhanVien &DSNV) 
{
	ifstream inFile;
	inFile.open("DSNV.txt", ios_base::in);
	if(inFile.fail()) {
		cout << "FILE DANH SACH SINH VIEN KHONG TON TAI!" << endl;
		return;
	}
	
	while(!inFile.eof()) 
	{
		//inFile.ignore();
		NhanVien* nv = new NhanVien;
		getline(inFile, nv->maNV, ',');
		getline(inFile, nv->ho, ',');
		getline(inFile, nv->ten, ',');
		getline(inFile, nv->phai, '\n');

		themMotNV(DSNV, nv);
	}
	inFile.close();
}

// =============================== DOC FILE VAT TU ==================================
void DocFileDSVT(DSVatTu &DSVT) 
{
	ifstream inFile;
	inFile.open("DSVT.txt", ios_base::in);
	
	if(inFile.fail()) {
		cout << "FILE DANH SACH VAT TU KHONG TON TAI!" << endl;
		return;
	}
	
	inFile >> DSVT.sl;
	while(!inFile.eof())
	{
		inFile.ignore();
		TREE vt = KhoiTaoNodeVT();
		getline(inFile, vt->info.maVT, ',');
		getline(inFile, vt->info.tenVT, ',');
		inFile >> vt->info.slTon; 
		inFile.ignore();
		getline(inFile, vt->info.dvt, '\n');
		
		themMotVatTu(DSVT.TREE_VT, vt);
	}
	inFile.close();
}

//================================ MENNU TINH =========================================
void Menu() {
	// khoi tao cac danh sach
	DSNhanVien DSNV;
	DSVatTu DSVT;
	
	// doc file
	DocFileDSNV(DSNV);
	DocFileDSVT(DSVT);
	
	bool checkStop = true;
	while(checkStop) {
		system("cls");
		cout << "1. Them vat tu " << endl;
		cout << "2. Xoa vat tu" << endl;
		cout << "3. Hieu chinh vat tu" << endl;
		cout << "4. Xuat danh sach vat tu" << endl;
		cout << "5. Them nhan vien" << endl;
		cout << "6. Hieu chinh nhan vien" << endl;
		cout << "7. Xuat danh sach nhan vien" << endl;
		cout << "9. Lap hoa don" << endl;
		cout << "0. Ket thuc chuong trinh" << endl;
		
		int luaChon;
		cout << "Nhap lua chon cua ban: "; cin >> luaChon; 
		
		switch(luaChon) {
			case 1: {
				cout << " THEM VAT TU " << endl;
				nhapVatTu(DSVT);
				break;
			}
			case 2: {
				xoaVatTu(DSVT);
				break;
			}
			case 3: {
				hieuChinhVatTu(DSVT);
				break;
			}
			case 4: {
				VatTu *vt[100];
				int nVT = 0;
				chuyenCaySangMang(DSVT.TREE_VT, vt, nVT);
				// sap xep tang dan theo ten
				sapXepVT(vt, nVT);
				xuatDanhSachVT(vt, nVT);
				giaiPhongDSVatTu(vt, nVT);
				getch();
				break;
			}
			case 5: {
				nhapNhanVien(DSNV);
				break;
			}
			case 6: {
				cout << " HIEU CHINH NHAN VIEN " << endl;
				hieuChinhNhanVien(DSNV);
				break;
			}
			case 7: {
				cout << endl << " DANH SACH NHAN VIEN " << endl;
				sapXepNhanVien(DSNV);
				xuatDSNV(DSNV);
				getch();
				break;
			}
			case 9: {
				cout << endl << " LAP HOA DON " << endl;
				lapHoaDon(DSNV, DSVT);
				break;
			}
			case 0: {
				cout << "TAM BIET. BAN DA DUNG CHUONG TRINH!" << endl;
				checkStop = false;
				break;
			}
		}
	}
}

int main() {
	srand(time(NULL));
	Menu();
	return 0;
}
