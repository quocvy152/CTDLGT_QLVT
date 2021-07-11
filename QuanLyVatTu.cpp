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
// ================================== UTIL TOOL =======================================
// ====================================================================================

// ---------------------------------- lay gio he thong --------------------------------
struct Date {
	int ngay, thang, nam;
};
Date LayGioHeThong() {
	time_t t = time(NULL);
	struct tm* now = localtime(&t);
	Date date;
	date.ngay = now->tm_mday;
	date.thang = now->tm_mon + 1;
	date.nam = now->tm_year + 1900;
	return date;
}

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
	Date ngayLap = LayGioHeThong();
	string loai; // chi nhan X va N (X: xuat, N: Nhan)
	DSChiTietHoaDon dsChiTietHoaDon;
};
struct NodeHD {
	HoaDon info;
	NodeHD* pNext = NULL;
};	
typedef NodeHD* PTRHD;

// ====================================================================================
// ==================================== DS NHAN VIEN ==================================
// ====================================================================================
struct NhanVien {
	string maNV;
	string ho;
	string ten;
	string phai;
	PTRHD FirstHD;
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
// ======================================= VAT TU =====================================
// ====================================================================================

//-------------------------------- ham khoi tao node nhan vien ------------------------
nodeVatTu* KhoiTaoNodeVT () {
	nodeVatTu *p = new nodeVatTu;
	p->pRight = NULL;
	p->pLeft = NULL;
	return p;
}

void chuyenCaySangMang(TREE TREE_VT, VatTu *vt[], int &nVT) {
	if(TREE_VT != NULL) {
		// data
		// nho thu lai neu gan TREE_VT->info == vt[n] co duoc khong
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
		if(TREE_VT->info.maVT.compare(p->info.maVT) < 0)
			themMotVatTu(TREE_VT->pRight, p);
		else if(TREE_VT->info.maVT.compare(p->info.maVT) > 0)
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
		cout << "So luong ton: " << vt[i]->slTon << endl;
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
			//so luong ton khong duoc phep hieu chinh
//			cout << "Nhap so luong ton vat tu hieu chinh: ";
//			cin >> TREE_VT->info.slTon;
			
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
	tam->FirstHD = p->FirstHD;

	p->ho = q->ho;
	p->maNV = q->maNV;
	p->ten = q->ten;
	p->phai = q->phai;
	p->FirstHD = q->FirstHD;

	q->ho = tam->ho;
	q->maNV = tam->maNV;
	q->ten = tam->ten;
	q->phai = tam->phai;
	q->FirstHD = tam->FirstHD;
	
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
		
		cout << "THAY DOI THANH CONG! " << endl;
	}
}

//---------------------------------- xoa nhan vien -------------------------------------
//void xoa_nv(DS_NHAN_VIEN& ds_nv)
//{
//	kt = xuat_ds_nhan_vien(ds_nv);
//	if (kt == -1)
//	{
//		return;
//	}
//	xoa:
//	string a;
//	rectangle(122,9,40,3,WHITE);
//	gotoxy(125, 10);
//	cout << "Nhap ma nhan vien: "; kt = nhap_ki_tu(a,1);
//	gotoxy(143, 10);
//	cout << "                ";
//	if (kt == -1)
//	{
//		return;
//	}
//	
//	int vt = kt_ma(a, ds_nv);
//	// xoa
//	if (vt < 0)
//	{
//		gotoxy(125, 12);
//		cout << "NHAN VIEN KHONG TON TAI" ;
//		Sleep(1000);
//		gotoxy(125, 12);
//		cout << "                        ";
//		gotoxy(125, 12);
//		cout << "MOI NHAP LAI! ";
//		Sleep(1000);
//		gotoxy(125, 12);
//		cout << "                        ";		
//		goto xoa;
//	}
//	else if (ds_nv.ds[vt]->danh_sach_hd.pHead != NULL)
//	{
//		gotoxy(122, 12);
//		cout << "KHONG DUOC XOA NHAN VIEN DA LAP HOA DON!";
//		Sleep(1000);
//		gotoxy(122, 12);
//		cout << "                                         ";
//		gotoxy(122, 12);
//		cout << "MOI NHAP LAI! ";
//		Sleep(1000);
//		gotoxy(122, 12);
//		cout << "                        ";
//		system("cls");
//		goto xoa;
//	}
//	else
//	{
//		for (int i = vt; i < ds_nv.sl - 1; i++)
//		{
//			ds_nv.ds[i]->ma_nv = ds_nv.ds[i + 1]->ma_nv;
//			ds_nv.ds[i]->ten = ds_nv.ds[i + 1]->ten;
//			ds_nv.ds[i]->ho = ds_nv.ds[i + 1]->ho;
//			ds_nv.ds[i]->phai = ds_nv.ds[i + 1]->phai;
//			ds_nv.ds[i]->danh_sach_hd = ds_nv.ds[i + 1]->danh_sach_hd;
//		}
//
//		NHAN_VIEN* tam = ds_nv.ds[ds_nv.sl - 1];
//		ds_nv.sl--;
//		delete tam;
//		gotoxy(125, 12);
//		cout << "DA XOA THANH CONG !" << endl;
//		Sleep(1000);
//		gotoxy(125, 12);
//		cout << "                    " << endl;
//
//	}
//}
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

//================================ MENNU TINH =========================================
void Menu() {
	// khoi tao cac danh sach
	DSNhanVien DSNV;
	DSVatTu DSVT;
	
	// doc ghi file
	DocFileDSNV(DSNV);
	
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
			case 0: {
				cout << "Tam biet. Ban da dung chuong trinh" << endl;
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
