#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include "library.h"

// define constant
#define MAX_CTHD 20
#define MAX_NHANVIEN 500
#define MAX_THONG_KE_DOANH_THU 500

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
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ' && a[i + 1] == ' ')
		{
			a.erase(a.begin() + i + 1);
			i--;
		}
	}
}

// ham thong bao
void THONG_BAO(string text, int x, int y, int color) {
	int currentX = wherex(); int currentY = wherey();
	gotoxy(x, y);
	TextColor(color);
	gotoxy(x, y);     cout << "     " << text << "     ";
	Sleep(1200);
	while(kbhit()) {
		getch();
	}
	TextColor(0); 
	gotoxy(x, y);
	for (int i = 0; i <= text.length(); i++)
		cout << "  ";
	TextColor(7);
	gotoxy(currentX, currentY);
}

//------------------------------- KIEM TRA VA SUA DOI PHAN NHAP LIEU ---------------------------
// ----------------------------- kiem tra mot ki tu co phai ki tu so ---------------------------
bool laKiTuSo(char c) {
	if (c < '0' || c > '9')
		return false;
	return true;
}

// ----------------------------- kiem tra mot ki tu co phai ki tu in hoa -----------------------
bool laKiTuInHoa(char c) {
	if(c < 'A' || c > 'Z')
		return false;
	return true;
}

// ------------------------------------- bat phim -----------------------------------------------
int getKey() {
	int keyPress = getch();
	if(keyPress == -32 || keyPress == 0) 
		return getch();
	else return keyPress;
}

// ------------------------------------- chuan hoa nhap lieu -------------------------------------
/*
 * 1: nhan vao vua chu, so, va khoang trang
 * 2: nhan vao so
 * 3: nhan vao chu va khoang trang 
 */
string nhapLieu(int loai, string noiDungCu) {
	string str;
	char c;
	
	if(noiDungCu.compare("") != 0) {
		str = noiDungCu;
		cout << str;
	}
	
laChuoiRong:
	c = getch();
	while ((int)c != ENTER) {
		if ((int)c == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.length() - 1);
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		
		if(int(c) == -32 || int(c) == 0 || int(c) == 224) 
		{
			c = getch();
			if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
				// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
				c = getch();
				continue;
			}
		}
		
		// chi nhan chu, khoang trang va so (nhap ten vat tu)
		if(loai == 1)
		{
			// vua nhan chu vua nhan so va khoang trang
			if(laKiTuInHoa(c) || c == SPACE || laKiTuSo(c)) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// chi nhan chu, khoang trang va so (nhap ten)
		else if(loai == 2)
		{
			// nhan chu va khoang trang
			if(laKiTuInHoa(c) || c == SPACE) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		
		else if(loai == 3)
		{
			// nhan chu
			if(laKiTuInHoa(c) || laKiTuSo(c)) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		
		if(int(c) == ESC) {
			return "-1";
		}
	}
	if(str == "")
	{
		THONG_BAO("   KHONG DUOC BO TRONG!   ", 90, 40, 79);
		goto laChuoiRong;
	}
	cout << endl;
	return str;
}

// dung de nhap cac so nguyen
int nhapSoNguyen(string noiDungCu) {
	string str;
	char c;
	
	if(noiDungCu.compare("") != 0) {
		str = noiDungCu;
		cout << str;
	}
	
laChuoiRong:
	c = getch(); // nhap ki tu dau tien
	// vong lap vo tan cho den khi bam ENTER
	while ((int)c != ENTER) {
		if (int(c) == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.length() - 1);
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		
		if(laKiTuSo(c)) {
			cout << c;
			str.push_back(c);
		}
		// neu bang ESC return -1
		if(int(c) == ESC) 
			return -1;
		c = getch();
	}
	if(str == "")
	{
		THONG_BAO("   KHONG DUOC BO TRONG!   ", 75, 43, 79);
		goto laChuoiRong;
	}
	cout << endl;
	return atoi(str.c_str());
}

// ham nhap so luong ton
float nhapSoPhay(string noiDungCu) {
	string str;
	char c;
	
	if(noiDungCu != "") {
		str = noiDungCu;
		cout << str;
	}
	
laChuoiRong:
	c = getch(); // nhap ki tu dau tien
	// v�ng lap vo tan cho den khi bam ENTER
	while ((int)c != ENTER) {
		if (int(c) == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.begin() + (str.length() - 1));
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		// neu la so thi cout ra va day vo chuoi
		if(laKiTuSo(c) || c == '.') {
			cout << c;
			str.push_back(c);
		}
		if(int(c) == ESC) 
			return -1;
		c = getch();
	}
	if(str == "")
	{
		THONG_BAO("   KHONG DUOC BO TRONG!   ", 90, 40, 79);
		goto laChuoiRong;
	}
	cout << endl;
	return atof(str.c_str());
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

// kiem tra 2 ngay xem ngay nao lon hon
int soSanhThoiGian(Date a, Date b) {
	if(a.nam > b.nam)
		return 1;
	else if(a.nam < b.nam)
		return -1;
		
	if(a.thang > b.thang)
		return 1;
	else if(a.thang < b.thang)
		return -1;
	
	if(a.ngay > b.ngay)
		return 1;
	else if(a.ngay < b.ngay)
		return -1;
	
	return 0;
}

// ========= kiem tra mot ngay co nam trong khoang thoi gian cho truoc =================
/*
 * return: 1 ==> ngay kiem tra nam trong khoang thoi gian cho truoc
 * return: 0 ==> ngay kiem tra nam ngoai khoang thoi gian cho truoc
 */
int ngayNamTrongKhoang(Date ngayBatDau, Date ngayKetThuc, Date ngayKiemTra) {
	// neu nam kiem tra vuot khoi khoang namBatDau <= namKiemTra <= namKetThuc
	if(ngayKiemTra.nam < ngayBatDau.nam || ngayKiemTra.nam > ngayKetThuc.nam)
		return 0;
		
	// neu nam kiem tra bang nam bat dau thi kiem tra toi thang va ngay
	if(ngayKiemTra.nam == ngayBatDau.nam) 
	{
	if(ngayKiemTra.thang < ngayBatDau.thang)
		return 0;
		
	if(ngayKiemTra.thang == ngayBatDau.thang && ngayKiemTra.ngay < ngayBatDau.ngay)
		return 0;
	}
	
	// neu nam kiem tra bang nam ket thuc thi kiem tra toi ngay va thang
	if(ngayKiemTra.nam == ngayKetThuc.nam)
	{
		if(ngayKiemTra.thang > ngayKetThuc.thang)
			return 0;
		
		if(ngayKiemTra.thang == ngayKetThuc.thang && ngayKiemTra.ngay > ngayKetThuc.ngay)
			return 0;
	}
	
	return 1;
}

// =================== ham in khoang thoi gian ======================================
void inKhoanThoiGian(Date ngayBatDau, Date ngayKetThuc) {
	TextColor(241);
	gotoxy(60, 5);  cout << "                          ";
	gotoxy(60, 6); cout << " Tu Ngay : " << ngayBatDau.ngay << "/" << ngayBatDau.thang << "/" << ngayBatDau.nam << "      ";
	gotoxy(60, 7); cout << " Den Ngay: " << ngayKetThuc.ngay << "/" << ngayKetThuc.thang << "/" << ngayKetThuc.nam << "      ";
	gotoxy(60, 8);  cout << "                          ";
	TextColor(7);
}

// ============================ ham nhac nho xac nhan truoc khi lam gi do =====================================
int thongBaoXacNhan(){
	int key;
	khungXacNhan();
	
	int chon = 0;
	while(1) {
		
		if(chon == 0) {
			TextColor(228);
			gotoxy(115, 39); cout << " CO ";
			TextColor(7);
			gotoxy(140, 39); cout << " KHONG ";
		} else {
			gotoxy(115, 39); cout << " CO ";
			TextColor(228);
			gotoxy(140, 39); cout << " KHONG ";
			TextColor(7);
		}
		
		key = getKey();
		if(key == RIGHT) {
			chon = 1;
		} else if(key == LEFT) {
			chon = 0;
		} if(key == ENTER) {
			if(chon == 0) {
				xoaKhungXacNhan();
				return 1;
			} else {
				xoaKhungXacNhan();
				return 0;
			}
		}
	}
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
	int tonTaiTrongHD = 0;
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
// ================================= KHAI BAO MENU  ===================================
// ====================================================================================
// menu cha
char MENU[4][40] = {
	"  QUAN LY VAT TU      ",
	"  QUAN LY NHAN VIEN   ",
	"  QUAN LY HOA DON     ",
	"  THOAT               " 
};

// menu vat tu
char MENU_VAT_TU[5][40] = {
	"   THEM VAT TU                ",
	"   DANH SACH VAT TU           ",
	"   XOA VAT TU                 ",
	"   HIEU CHINH VAT TU          ",
	"   THONG KE TOP 10 VAT TU     "
};

// menu nhan vien
char MENU_NHAN_VIEN[4][40] = {
	"   THEM NHAN VIEN                ",
	"   DANH SACH NHAN VIEN           ",
	"   XOA NHAN VIEN                 ",
	"   HIEU CHINH NHAN VIEN          ",
};

// menu hoa don
char MENU_HOA_DON[3][40] = {
	"   LAP HOA DON                   ",
	"   XUAT HOA DON                  ",
	"   XUAT HOA DON THEO THOI GIAN   "
};

// ====================================================================================
// ============================== THONG KE DOANH THU  =================================
// ====================================================================================
struct DoanhThu {
	string maVT;
	string tenVT;
	long long doanhThu = 0;
};

struct DSDoanhThu {
	DoanhThu *dt[MAX_THONG_KE_DOANH_THU];
	int sl = 0;
};

// ======================== tinh thanh tien cua hoa don ============================
long long tinhThanhTienCTHD(ChiTietHoaDon cthd) {
	// tinh thanh tien = soLuong * donGia + VAT
	float thanhTienChuaThue = cthd.soLuong * (float)(cthd.donGia);
	float tienThue = (thanhTienChuaThue * cthd.VAT) / 100;
	long long thanhTien = thanhTienChuaThue + tienThue;
	return thanhTien;
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

// ============================ them mot doanh thu ====================================
void themMotDoanhThu(DSDoanhThu &DSDT, DoanhThu *doanhThu) {
	if(DSDT.sl == MAX_THONG_KE_DOANH_THU)
	{
		cout << "DANH SACH THONG KE DOANH THU DAY!" << endl;
		getch();
		return;
	}
		
	DSDT.dt[DSDT.sl] = doanhThu;
	++DSDT.sl;
}

// ====================== ham kiem tra vat tu da co doanh thu chua ====================
int daCoDoanhThu(DSDoanhThu &DSDT, string maVT) {
	for(int i = 0; i < DSDT.sl; i++)
		if(DSDT.dt[i]->maVT == maVT)
			return i;
	return -1;
}

// ===================== hoan vi hai doanh thu de sap xep =============================
void hoanDoiDoanhThu(DoanhThu *&a, DoanhThu *&b)
{
	DoanhThu *tempDoanhThu = new DoanhThu;
	
	tempDoanhThu->maVT = a->maVT;
	tempDoanhThu->tenVT = a->tenVT;
	tempDoanhThu->doanhThu = a->doanhThu;
	
	a->maVT = b->maVT;
	a->tenVT = b->tenVT;
	a->doanhThu = b->doanhThu;
	
	b->maVT = tempDoanhThu->maVT;
	b->tenVT = tempDoanhThu->tenVT;
	b->doanhThu = tempDoanhThu->doanhThu;
	
	delete tempDoanhThu;
}

void sapXepDoanhThu(DSDoanhThu &DSDT)
{
	for(int i = 0; i < DSDT.sl - 1; i++) {
		for(int j = i + 1; j < DSDT.sl; j++) {
			if(DSDT.dt[i]->doanhThu < DSDT.dt[j]->doanhThu) {
				hoanDoiDoanhThu(DSDT.dt[i], DSDT.dt[j]);
			}
		}
	}
}

// ============ tra ve mang doanh thu cua cac vat tu thuoc hoa don xuat ==============
void doanhThuThuocHDXuat(DSNhanVien &DSNV, DSVatTu &DSVT, DSDoanhThu &DSDT, Date ngayBatDau, Date ngayKetThuc) {
	for(int i = 0; i < DSNV.sl; i++) 
	{
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext) 
		{
			// chi liet ke cac doanh thu cua vat tu nam trong hoa don xuat va nam trong khoang thoi gian mong muon
			if(p->info.loai == "X" && ngayNamTrongKhoang(ngayBatDau, ngayKetThuc, p->info.ngayLap)) 
			{
				for(int j = 0; j < p->info.dsChiTietHoaDon.sl; j++) 
				{
					long long thanhTien = tinhThanhTienCTHD(p->info.dsChiTietHoaDon.ds[j]);
					int kiemTraDaCoDT = daCoDoanhThu(DSDT, p->info.dsChiTietHoaDon.ds[j].maVT);
					if(kiemTraDaCoDT == -1) 
					{
						TREE TREE_VT = timNodeVT(DSVT.TREE_VT, p->info.dsChiTietHoaDon.ds[j].maVT);
						
						DoanhThu *doanhThu = new DoanhThu;
						doanhThu->maVT = TREE_VT->info.maVT;
						doanhThu->tenVT = TREE_VT->info.tenVT;
						doanhThu->doanhThu = thanhTien;
						themMotDoanhThu(DSDT, doanhThu);
					}
					else 
					{
						DSDT.dt[kiemTraDaCoDT]->doanhThu = DSDT.dt[kiemTraDaCoDT]->doanhThu + thanhTien;
					}
				}
			}
		}
	}
}

// ========================= reset lai danh sach doanh thu ===========================
void taoLaiDoanhThu(DSDoanhThu &DSDT) {
	for(int i = 0; i < DSDT.sl; i++) 
		delete DSDT.dt[i];
	
	DSDT.sl = 0;
}

// =================== xuat ra 10 vat tu co doanh thu cao nhat ========================
void xuatTopDoanhThu(DSDoanhThu &DSDT, Date ngayBatDau, Date ngayKetThuc) {
	if(DSDT.sl == 0)
	{
		THONG_BAO("KHONG CO VAT TU NAO DUOC LAP HOA DON XUAT TRONG KHOANG THOI GIAN DA NHAP", 90, 40, 79);
		return;
	}
	
	int key;
	int trang = 0, tongTrang = 0;
	
	// lay ra so doanh thu can xuat
	int soLuongXuat = 0;
	DSDT.sl <= 10 ? soLuongXuat = DSDT.sl : soLuongXuat = 10;
	
	xoaKhungNhapXemTGHD();
	xoaKhungDSDT(); khungXuatDSDT();
	
	// chi lay ra 10 vat tu dau tien
	inKhoanThoiGian(ngayBatDau, ngayKetThuc);
	
	while(1) {
		int hang = 0, stt = 0;
		for(int i = trang * 15; i < 15 + trang * 15 &&  i < soLuongXuat; i++) {
			stt = i + 1;
			gotoxy(81, 12 + hang); cout << stt;
			gotoxy(91, 12 + hang); cout << DSDT.dt[i]->maVT;
			gotoxy(113, 12 + hang); cout << DSDT.dt[i]->tenVT;
			gotoxy(157, 12 + hang); cout << DSDT.dt[i]->doanhThu;
			hang++;
		}
		key = getKey();
		
		if(key == ESC) {
			xoaKhungDSDT();
			return;	
		}
	}
}

// ========= thong ke 10 vat tu co doanh thu cao nhat trong khoang thoi gian ==========
void thongKeDoanhThu(DSNhanVien &DSNV, DSVatTu &DSVT, DSDoanhThu &DSDT) {
	Date ngayBatDau, ngayKetThuc;
	string noiDungCu = "";
	
NhapNgayBD:
	khungNhapXemTGHD();	
	gotoxy(80, 13); ngayBatDau.ngay = nhapSoNguyen(noiDungCu);  if(ngayBatDau.ngay == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THU", 90, 40, 79); return; }
	gotoxy(80, 14); ngayBatDau.thang = nhapSoNguyen(noiDungCu); if(ngayBatDau.thang == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THU", 90, 40, 79); return; }
	gotoxy(80, 15); ngayBatDau.nam = nhapSoNguyen(noiDungCu);   if(ngayBatDau.nam == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THU", 90, 40, 79); return; }
	bool trangThaiNBD = laNgayHopLe(ngayBatDau);
	if(!trangThaiNBD)
	{
		THONG_BAO("NGAY BAT DAU KHONG TON TAI!", 90, 40, 79);
		xoaNhapNgayBatDau();
		goto NhapNgayBD;
	}
	
NhapNgayKT:
	gotoxy(112, 13); ngayKetThuc.ngay = nhapSoNguyen(noiDungCu);  if(ngayKetThuc.ngay == -1)  { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THU", 90, 40, 79); return; }
	gotoxy(112, 14); ngayKetThuc.thang = nhapSoNguyen(noiDungCu); if(ngayKetThuc.thang == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THUN", 90, 40, 79); return; }
	gotoxy(112, 15); ngayKetThuc.nam = nhapSoNguyen(noiDungCu);   if(ngayKetThuc.nam == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM TOP DOANH THU", 90, 40, 79); return; }
	bool trangThaiNKT = laNgayHopLe(ngayKetThuc);
	if(!trangThaiNKT)
	{
		THONG_BAO("NGAY KET THUC KHONG TON TAI!", 90, 40, 79);
		xoaNhapNgayKetThuc();
		goto NhapNgayKT;
	}
	
	int soSanhHaiNgay = soSanhThoiGian(ngayBatDau, ngayKetThuc);
	if(soSanhHaiNgay == 1)
	{
		THONG_BAO("KHOANG THOI GIAN KHONG HOP LE! NGAY BAT DAU LON HON NGAY KET THUC!", 72, 40, 79);
		xoaNhapNgayBatDau();
		xoaNhapNgayKetThuc();
		goto NhapNgayBD;
	}
	else if(soSanhHaiNgay == 0)
	{
		THONG_BAO("KHOANG THOI GIAN KHONG HOP LE! NGAY BAT DAU VA NGAY KET THUC BANG NHAU!", 72, 40, 79);
		xoaNhapNgayBatDau();
		xoaNhapNgayKetThuc();
		goto NhapNgayBD;
	}
	
	doanhThuThuocHDXuat(DSNV, DSVT, DSDT, ngayBatDau, ngayKetThuc);
	sapXepDoanhThu(DSDT);
	xuatTopDoanhThu(DSDT, ngayBatDau, ngayKetThuc);
	taoLaiDoanhThu(DSDT);
}

// ====================================================================================
// =================================== GHI FILE =======================================
// ====================================================================================

// ======================= GHI DU LIEU NGAY THANG NAM VAO FILE ========================
void ghiNgayThangNam(ofstream &outFile, Date ngayLap) {
	outFile << ngayLap.ngay << "/";
	outFile << ngayLap.thang << "/";
	outFile << ngayLap.nam << ",";
}

// ================================ GHI FILE VAT TU ===================================
void ghiFileNLR(ofstream &outFile, TREE TREE_VT, int nVT, int &nVTChay) {
	if(TREE_VT != NULL) {
		++nVTChay;
		outFile << TREE_VT->info.maVT << ",";
		outFile << TREE_VT->info.tenVT << ",";
		outFile << TREE_VT->info.slTon << ",";
		outFile << TREE_VT->info.tonTaiTrongHD << ",";
		
		// dang ghi toi cuoi file, loai bo ghi xuong dong
		if(nVTChay == nVT)
			outFile << TREE_VT->info.dvt;
		else
			outFile << TREE_VT->info.dvt << endl;
			
		ghiFileNLR(outFile, TREE_VT->pLeft, nVT, nVTChay);
		ghiFileNLR(outFile, TREE_VT->pRight, nVT, nVTChay);
	}
}

void ghiFileDSVT(DSVatTu &DSVT) {
	ofstream outFile;
	outFile.open("DSVT.txt", ios::out);
	int nVTChay = 0;
	outFile << DSVT.sl << endl;
	ghiFileNLR(outFile, DSVT.TREE_VT, DSVT.sl, nVTChay);
	outFile.close();
}

// ================================ GHI FILE NHAN VIEN ================================
void ghiFileDSNV(DSNhanVien &DSNV) {
	ofstream outFile;
	outFile.open("DSNV.txt", ios::out);
	
	outFile << DSNV.sl << endl;
	
	for(int i = 0; i < DSNV.sl; i++) {
		outFile << DSNV.nv[i]->maNV << ",";
		outFile << DSNV.nv[i]->ho << ",";
		outFile << DSNV.nv[i]->ten << ",";
		outFile << DSNV.nv[i]->phai << endl;
		
		// bat dau ghi thong tin cua hoa don
		outFile << DSNV.nv[i]->DSHD.sl << endl;
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext) {
			outFile << p->info.soHD << ",";
			ghiNgayThangNam(outFile, p->info.ngayLap);
			outFile << p->info.loai << endl;
			
			// bat dau ghi thong tin chi tiet hoa don cua hoa don do
			outFile << p->info.dsChiTietHoaDon.sl << endl;
			for(int i = 0; i < p->info.dsChiTietHoaDon.sl; i++) {
				outFile << p->info.dsChiTietHoaDon.ds[i].maVT << ",";
				outFile << p->info.dsChiTietHoaDon.ds[i].soLuong << ",";
				outFile << p->info.dsChiTietHoaDon.ds[i].donGia << ",";
				outFile << p->info.dsChiTietHoaDon.ds[i].VAT << endl;
			}
		}
	}
}

// ====================================================================================
// ======================================== VAT TU ====================================
// ====================================================================================

//-------------------------------- ham khoi tao node nhan vien ------------------------
TREE KhoiTaoNodeVT () {
	nodeVatTu *p = new nodeVatTu;
	p->pRight = NULL;
	p->pLeft = NULL;
	return p;
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
	string formatMaVT = "VT00000000";
	do {
		for (int i = 2; i < formatMaVT.length(); i++)
			formatMaVT[i] = rand() % (4) + 48;
	} while (kiemTraTrungMaVT(TREE_VT, formatMaVT) == true); // kiem tra ma vat tu trung thi tao ma moi
	return formatMaVT;
}

void nhapVatTu(DSVatTu &DSVT){
	nodeVatTu *p = KhoiTaoNodeVT();
	p->info.maVT = taoMaVT(DSVT.TREE_VT);
	
	gotoxy(71, 12); cout << "Ma vat tu        : ";
	gotoxy(90, 12); cout  << p->info.maVT;
	
	gotoxy(71, 13); cout << "Nhap ten vat tu  : ";
	gotoxy(71, 14); cout << "Nhap don vi tinh : "; 
	gotoxy(71, 15); cout << "Nhap so luong ton: "; 
	
	string tenVTCu = "", dvtCu = "", slTTonCu ="";
	
	khungNhapThemVT();
	gotoxy(90, 13); p->info.tenVT = nhapLieu(1, tenVTCu);
	if(p->info.tenVT == "-1") {
		THONG_BAO("BAN DA THOAT THEM VAT TU!", 90, 40, 79);
		return;
	} 
	
	gotoxy(90, 14); p->info.dvt = nhapLieu(1, dvtCu);
	if(p->info.dvt == "-1") {
		THONG_BAO("BAN DA THOAT THEM VAT TU!", 90, 40, 79);
		return;
	} 
		
	gotoxy(90, 15); p->info.slTon = nhapSoPhay(slTTonCu);
	if(p->info.slTon == -1) {
		THONG_BAO("BAN DA THOAT THEM VAT TU!", 90, 40, 79);
		return;
	} 
	
	ChuanHoaChu(p->info.tenVT);
	ChuanHoaChu(p->info.dvt);
	
	themMotVatTu(DSVT.TREE_VT, p);
	DSVT.sl++;
	THONG_BAO("THEM VAT TU THANH CONG!", 90, 40, 167);
	ghiFileDSVT(DSVT);
}

void xuatDanhSachVT(VatTu *vt[], int nVT){
	int key;
	int trang = 0; int tongTrang = 0;
	int hang;
	
	// sap xep vat tu tang dan theo ho ten
	sapXepVT(vt, nVT);
	
	
	while(1) {
		if(nVT == 0) {
			THONG_BAO("DANH SACH VAT TU RONG!", 80, 40, 79);
		} else {
			if(nVT < 15) {
				//trang = 0;
				tongTrang = 1;
			} else {
				tongTrang = (nVT - 1) / 15 + 1;
			}
		}
		
		int stt = 0; hang = 0;
		xoaKhungDSVT(); khungXuatDSVT();
		for(int i = trang * 15; i < 15 + trang * 15 && i < nVT; i++) {
			stt = i + 1;
			gotoxy(81, 12 + hang); cout << stt;
			gotoxy(91, 12 + hang); cout << vt[i]->maVT;
			gotoxy(113, 12 + hang); cout << vt[i]->tenVT;
			gotoxy(157, 12 + hang); cout << vt[i]->dvt;
			gotoxy(168, 12 + hang); cout << vt[i]->slTon;
			hang++;
		}
		hienThiTrang(trang + 1, tongTrang, 172, 29);
		key = getKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			xoaKhungDSVT();
			return;
		}
			
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

void xoaVatTu(DSNhanVien &DSNV, DSVatTu &DSVT) {
	string maVT;
	string noiDungCu = "";
	khungNhapXoa();
NhapLai:
	gotoxy(72, 12); cout << "Nhap ma Vat Tu: ";
	gotoxy(88, 12); maVT = nhapLieu(3, noiDungCu);
	if(maVT == "-1") {
		THONG_BAO("BAN DA THOAT KHOI XOA VAT TU!", 90, 40, 79);
		return;
	}
	
	TREE TREE_VT = timNodeVT(DSVT.TREE_VT, maVT);
 	if(!TREE_VT) 
	{
		THONG_BAO("MA VAT TU KHONG TON TAI!", 90, 40, 79);
		noiDungCu = maVT;
		goto NhapLai;
	} 
	else 
	{
		// xac nhan co muon xoa vat tu khong
		gotoxy(108, 37); cout << "BAN CO CHAC CHAN MUON XOA VAT TU NAY KHONG?";
		int xacNhan = thongBaoXacNhan();
		if(!xacNhan) {
			noiDungCu = maVT;
			xoaKhungXacNhan();
			goto NhapLai;
		}
		
		if(TREE_VT->info.slTon != 0) 
		{
			THONG_BAO("VAT TU VAN CON SO LUONG TON!", 90, 40, 79);
			noiDungCu = maVT;
			goto NhapLai;
		}
			
		if(TREE_VT->info.tonTaiTrongHD > 0)
		{
			THONG_BAO("VAT TU DA LAP CHI TIET HOA DON! KHONG THE XOA VAT TU!", 90, 40, 79);
			noiDungCu = maVT;
			goto NhapLai;
		}
		
		xoaMotVatTu(DSVT.TREE_VT, maVT);
		DSVT.sl--;
		ghiFileDSVT(DSVT);
		THONG_BAO("XOA THANH CONG!", 90, 40, 167);
		return;
	}
}

void hieuChinhVatTu(DSVatTu &DSVT) {
	string noiDungCu;
	string maVT;
	
NhapLai:
	khungNhapXoa();
	gotoxy(72, 12); cout << "Nhap Ma Vat Tu Can Hieu Chinh: ";
	gotoxy(103, 12); maVT = nhapLieu(3, noiDungCu);
	if(maVT == "-1") {
		THONG_BAO("BAN DA THOAT HIEU CHINH VAT TU!", 90, 40, 79);
		return;
	}
	
	TREE trungMaVT = timNodeVT(DSVT.TREE_VT, maVT);
	if(!trungMaVT) {
		THONG_BAO(" MA VAT TU KHONG TON TAI! ", 90, 40, 79);
		noiDungCu = maVT;
		goto NhapLai;	
	} else {
		xoaKhungNhapXoa();
		string tenVTCN, dvtCN;
		
		khungNhapThemVT();
		TextColor(222);
		gotoxy(94, 11); cout << " THONG TIN VAT TU ";
		TextColor(7);
		gotoxy(71, 12); cout << "Ma vat tu                   : " << trungMaVT->info.maVT;
		gotoxy(71, 13); cout << "Ten vat tu                  : " << trungMaVT->info.tenVT;
		gotoxy(71, 14); cout << "Don vi tinh                 : " << trungMaVT->info.dvt;
		gotoxy(71, 15); cout << "So luong ton                : " << trungMaVT->info.slTon;
		
		khungCapNhatNV();
		TextColor(222);
		gotoxy(91, 20); cout << " THONG TIN NHAN VIEN CAP NHAT ";
		TextColor(7);
		gotoxy(71, 21); cout << "Ma vat tu                    : " << trungMaVT->info.maVT;
		gotoxy(71, 22); cout << "So luong ton cap nhat        : " << trungMaVT->info.slTon;
		gotoxy(71, 23); cout << "Ten vat tu cap nhat  	    : "; 
		gotoxy(71, 24); cout << "Don vi tinh cap nhat         : ";
		
		gotoxy(102, 23); tenVTCN = nhapLieu(1, "");
		if(tenVTCN == "-1") {
			THONG_BAO(" BAN DA THOAT CAP NHAT VAT TU! ", 90, 40, 79);
			return;
		}
		
		gotoxy(102, 24); dvtCN = nhapLieu(1, "");
		if(tenVTCN == "-1") {
			THONG_BAO(" BAN DA THOAT CAP NHAT VAT TU! ", 90, 40, 79);
			return;
		}
		
		khungXacNhan();
		gotoxy(116, 36); cout << "BAN CO CHAC CHAN MUON CAP NHAT";
		gotoxy(115, 37); cout << " THONG TIN VAT TU NAY KHONG?";
		int chon = 0; bool huyNhap = false; int key;
		while(1) {
			
			if(chon == 0) {
				TextColor(228);
				gotoxy(115, 39); cout << " CO ";
				TextColor(7);
				gotoxy(140, 39); cout << " KHONG ";
			} else {
				gotoxy(115, 39); cout << " CO ";
				TextColor(228);
				gotoxy(140, 39); cout << " KHONG ";
				TextColor(7);
			}
			
			key = getKey();
			if(key == RIGHT) {
				chon = 1;
			} else if(key == LEFT) {
				chon = 0;
			} if(key == ENTER) {
				if(chon == 0) {
					xoaKhungXacNhan();
					break;
				} else {
					xoaKhungXacNhan();
					huyNhap = true;
					break;
				}
			}
		}
		
		if(huyNhap) {
			THONG_BAO(" BAN DA THOAT CAP NHAT VAT TU! ", 90, 40, 79);
			return;
		}
		
		trungMaVT->info.tenVT = tenVTCN;
		trungMaVT->info.dvt = dvtCN;
		
		ChuanHoaChu(trungMaVT->info.tenVT);
		ChuanHoaChu(trungMaVT->info.dvt);
		
		THONG_BAO(" CAP NHAT VAT TU THANH CONG! ", 90, 40, 167);
		ghiFileDSVT(DSVT);
		 
	}
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
void nhapNhanVien(DSNhanVien &DSNV) {
	if(DSNV.sl == MAX_NHANVIEN) {
		THONG_BAO("THEM NHAN VIEN THAT BAI! DANH SACH DAY!", 90, 40, 79);
	} else {
		NhanVien* p = new NhanVien;
		khungNhapThemVT();
		p->maNV = taoMaNV(DSNV);
		gotoxy(71, 12); cout << "Ma nhan vien            : "; cout << p->maNV;
		
		gotoxy(71, 13); cout << "Nhap ho nhan vien       : "; 
		gotoxy(71, 14); cout << "Nhap ten nhan vien      : "; 
		gotoxy(71, 15); cout << "Chon gioi tinh nhan vien: "; 
		
		gotoxy(97, 13); p->ho = nhapLieu(2, "");
		if(p->ho == "-1") {
			THONG_BAO("BAN DA THOAT THEM NHAN VIEN!", 90, 40, 79);
			return;
		} 
		gotoxy(97, 14); p->ten = nhapLieu(2, "");
		if(p->ten == "-1") {
			THONG_BAO("BAN DA THOAT THEM NHAN VIEN!", 90, 40, 79);
			return;
		}
		
		int key, chon = 0;
		bool huyNhap = false;
		while(1) {
			if(chon == 0) {
				TextColor(228);
				gotoxy(97, 15); cout << " NAM ";
				TextColor(7);
				gotoxy(105, 15); cout << " NU ";
			} else if(chon == 1) {
				gotoxy(97, 15); cout << " NAM ";
				TextColor(228);
				gotoxy(105, 15); cout << " NU ";
				TextColor(7);
			}
			
			key = getKey();
			if(key == RIGHT) {
				chon = 1;	
			} else if(key == LEFT) {
				chon = 0;
			} else if(key == ENTER) {
				if(chon == 0) {
					xoaKhungXacNhan();
					p->phai = " NAM ";
					break;
				} else {
					xoaKhungXacNhan();
					p->phai = " NU ";
					break;
				}
			} else if(key == ESC) {
				huyNhap = true;
				break;
			}
		}
		
		if(huyNhap) {
			THONG_BAO(" BAN DA THOAT THEM NHAN VIEN! ", 90, 40, 79);
			return;
		}
		
		ChuanHoaChu(p->ho);
		ChuanHoaChu(p->ten);
		
		themMotNV(DSNV, p);
		THONG_BAO(" THEM NHAN VIEN THANH CONG! ", 90, 40, 167);
		ghiFileDSNV(DSNV);
	}
}

void hoanViHaiNV(NhanVien *&p, NhanVien *&q) {
	NhanVien* tam = new NhanVien;
	
	tam->ho = p->ho;
	tam->maNV = p->maNV;
	tam->ten = p->ten;
	tam->phai = p->phai;
	tam->DSHD = p->DSHD;

	p->ho = q->ho;
	p->maNV = q->maNV;
	p->ten = q->ten;
	p->phai = q->phai;
	p->DSHD = q->DSHD;

	q->ho = tam->ho;
	q->maNV = tam->maNV;
	q->ten = tam->ten;
	q->phai = tam->phai;
	q->DSHD = tam->DSHD;
	
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
		THONG_BAO(" DANH SACH NHAN VIEN RONG! ", 90, 40, 79);
		return;
	}
	
	int key;
	int hang = 0;
	int trang = 0; int tongTrang = 0;
	sapXepNhanVien(DSNV);
	
	while(1) {
		if(DSNV.sl < 15) {
			trang = 0; 
			tongTrang = 1;
		} else {
			tongTrang = (DSNV.sl - 1) / 15 + 1;
		}
		
		xoaKhungDSNV(); khungXuatDSNV();
		int stt = 0; hang = 0;
		for(int i = trang * 15; i < 15 + trang * 15 && i < DSNV.sl; i++) {
			stt += 1;
			gotoxy(87, 12 + hang); cout << stt; 
			gotoxy(96, 12 + hang); cout << DSNV.nv[i]->maNV;
			gotoxy(120, 12 + hang); cout << DSNV.nv[i]->ho;
			gotoxy(150, 12 + hang); cout << DSNV.nv[i]->ten;
			gotoxy(169, 12 + hang); cout << DSNV.nv[i]->phai;
			hang++;
		}
		hienThiTrang(trang + 1, tongTrang, 158, 29);
		key = getKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			xoaKhungDSNV();
			return;	
		}
	}
	
	
}

//----------------------------- hieu chinh nhan vien ------------------------------------
void hieuChinhNhanVien(DSNhanVien &DSNV)
{
	if(DSNV.sl == 0) {
		THONG_BAO(" DANH SACH NHAN VIEN RONG! ", 90, 40, 79);
		return;
	}
	
	string maNVKT, noiDungCu = "";
	
NhapLai:
	khungNhapXoa();
	gotoxy(72, 12); cout << "Nhap Ma Nhan Vien Can Hieu Chinh: ";
	gotoxy(106, 12); maNVKT = nhapLieu(3, noiDungCu);
	int vt = kiemTraMaNV(DSNV, maNVKT);
	if (vt < 0) {
		THONG_BAO(" NHAN VIEN KHONG TON TAI!! ", 90, 40, 79);
		noiDungCu = maNVKT;
		goto NhapLai;
	} else {
		xoaKhungNhapXoa();
		string hoCN, tenCN, gtCN;
		
		khungNhapThemVT();
		TextColor(222);
		gotoxy(94, 11); cout << " THONG TIN NHAN VIEN ";
		TextColor(7);
		gotoxy(71, 12); cout << "Ma nhan vien                : " << DSNV.nv[vt]->maNV;
		gotoxy(71, 13); cout << "Ho nhan vien                : " << DSNV.nv[vt]->ho;
		gotoxy(71, 14); cout << "Ten nhan vien               : " << DSNV.nv[vt]->ten;
		gotoxy(71, 15); cout << "Gioi tinh nhan vien         : " << DSNV.nv[vt]->phai;
		
		khungCapNhatNV();
		TextColor(222);
		gotoxy(91, 20); cout << " THONG TIN NHAN VIEN CAP NHAT ";
		TextColor(7);
		gotoxy(71, 21); cout << "Ma nhan vien                 : " << DSNV.nv[vt]->maNV;
		gotoxy(71, 22); cout << "Ho nhan vien cap nhat  	    : "; 
		gotoxy(71, 23); cout << "Ten nhan vien cap nhat       : ";
		gotoxy(71, 24); cout << "Gioi tinh nhan vien cap nhat : ";
		
		gotoxy(102, 22); hoCN = nhapLieu(2, "");
		if(hoCN == "-1") {
			THONG_BAO(" BAN DA THOAT CAP NHAT NHAN VIEN! ", 90, 40, 79);
			return;
		}
		
		gotoxy(102, 23); tenCN = nhapLieu(2, "");
		if(hoCN == "-1") {
			THONG_BAO(" BAN DA THOAT CAP NHAT NHAN VIEN! ", 90, 40, 79);
			return;
		}
		
		int key, chon = 0;
		bool huyNhap = false;
		while(1) {
			if(chon == 0) {
				TextColor(228);
				gotoxy(101, 24); cout << " NAM ";
				TextColor(7);
				gotoxy(112, 24); cout << " NU ";
			} else if(chon == 1) {
				gotoxy(101, 24); cout << " NAM ";
				TextColor(228);
				gotoxy(112, 24); cout << " NU ";
				TextColor(7);
			}
			
			key = getKey();
			if(key == RIGHT) {
				chon = 1;	
			} else if(key == LEFT) {
				chon = 0;
			} else if(key == ENTER) {
				if(chon == 0) {
					xoaKhungXacNhan();
					gtCN = " NAM ";
					break;
				} else {
					xoaKhungXacNhan();
					gtCN = " NU ";
					break;
				}
			} else if(key == ESC) {
				huyNhap = true;
				break;
			}
		}
		
		if(huyNhap) {
			THONG_BAO(" BAN DA THOAT CAP NHAT NHAN VIEN! ", 90, 40, 79);
			return;
		}
		
		khungXacNhan();
		gotoxy(116, 36); cout << "BAN CO CHAC CHAN MUON CAP NHAT";
		gotoxy(115, 37); cout << " THONG TIN NHAN VIEN NAY KHONG?";
		chon = 0; huyNhap = false;
		while(1) {
			
			if(chon == 0) {
				TextColor(228);
				gotoxy(115, 39); cout << " CO ";
				TextColor(7);
				gotoxy(140, 39); cout << " KHONG ";
			} else {
				gotoxy(115, 39); cout << " CO ";
				TextColor(228);
				gotoxy(140, 39); cout << " KHONG ";
				TextColor(7);
			}
			
			key = getKey();
			if(key == RIGHT) {
				chon = 1;
			} else if(key == LEFT) {
				chon = 0;
			} if(key == ENTER) {
				if(chon == 0) {
					xoaKhungXacNhan();
					break;
				} else {
					xoaKhungXacNhan();
					huyNhap = true;
					break;
				}
			}
		}
		
		if(huyNhap) {
			THONG_BAO(" BAN DA THOAT CAP NHAT NHAN VIEN! ", 90, 40, 79);
			return;
		}
		
		DSNV.nv[vt]->ho = hoCN;
		DSNV.nv[vt]->ten = tenCN;
		DSNV.nv[vt]->phai = gtCN;
		
		ChuanHoaChu(DSNV.nv[vt]->ho);
		ChuanHoaChu(DSNV.nv[vt]->ten);
		ChuanHoaChu(DSNV.nv[vt]->phai);
		
		ghiFileDSNV(DSNV);
		THONG_BAO(" HIEU CHINH NHAN VIEN THANH CONG! ", 90, 40, 167);
	}
}

int xoaMotNhanVien(DSNhanVien &DSNV, int vtNV)
{
	delete DSNV.nv[vtNV];
	for(int j = vtNV + 1;  j < DSNV.sl; j++)
		DSNV.nv[j - 1] = DSNV.nv[j];
	DSNV.sl--;
	return 1; 
}


//---------------------------------- xoa nhan vien -------------------------------------
void xoaNhanVien(DSNhanVien &DSNV) {
	if(DSNV.sl == 0) 
	{
		THONG_BAO(" KHONG THE XOA! DANH SACH NHAN VIEN RONG! ", 90, 40, 79);
		return;
	}
	
	string maNV;
	string noiDungCu = "";
	khungNhapXoa();
NhapLai:
	gotoxy(72, 12); cout << "Nhap Ma Nhan Vien Can Xoa: ";
	gotoxy(100, 12); maNV = nhapLieu(3, noiDungCu);
	if(maNV == "-1") {
		THONG_BAO("BAN DA THOAT KHOI XOA NHAN VIEN!", 90, 40, 79);
		return;
	}
	
	int vtNV = kiemTraMaNV(DSNV, maNV);
	if(vtNV == -1)
	{
		THONG_BAO("MA NHAN VIEN KHONG TON TAI!", 90, 40, 79);
		noiDungCu = maNV;
		goto NhapLai;
	}
	
	// xac nhan co muon xoa nhan vien khong
	gotoxy(108, 37); cout << "BAN CO CHAC CHAN MUON XOA VAT TU NAY KHONG?";
	int xacNhan = thongBaoXacNhan();
	if(!xacNhan) {
		noiDungCu = maNV;
		xoaKhungXacNhan();
		goto NhapLai;
	}
	
	if(DSNV.nv[vtNV]->DSHD.FirstHD != NULL)
	{
		THONG_BAO("KHONG THE XOA! NHAN VIEN DA LAP HOA DON!", 90, 40, 79);
		return;
	}
	
	int trangThaiXoa = xoaMotNhanVien(DSNV, vtNV);
	if(trangThaiXoa == 1)
	{
		THONG_BAO("XOA NHAN VIEN THANH CONG!", 90, 40, 167);
		ghiFileDSNV(DSNV);
		return;
	}
}

// ====================================================================================
// ====================================== HOA DON =====================================
// ====================================================================================

// tra ve ten cua loai hoa don
string loaiHoaDon(string loai) {
	if(loai == "X") 
		return "XUAT";
	return "NHAP";
}

// khoi tao hoa don
PTRHD khoiTaoNodeHD()
{
	PTRHD p = new NodeHD;
	p->pNext = NULL;
	return p;
}

// them 1 hoa don
void themMotHD(PTRHD &FirstHD, PTRHD p)
{
	if (FirstHD == NULL)
	{
		FirstHD = p;
	}
	else
	{
		for (PTRHD k = FirstHD; k != NULL; k = k->pNext)
		{	
			if (k->pNext == NULL)
			{
				k->pNext = p;
				break;
			}
		}
	}
}

// luot qua tung hoa don cua tung nhan vien
bool ktTrungMaHD(DSNhanVien DSNV, string soHD) {
	for(int i = 0; i < DSNV.sl; i++)
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext)
 			if (p->info.soHD == soHD)
				return true;
	return false;
}

// luot qua hoa don cua mot nhan vien
bool ktTrungMaHDTrongNV(PTRHD hoaDon, string soHD) {
	for(PTRHD p = hoaDon; p != NULL; p = p->pNext)
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

// ====================================================================================
// ================================ CHI TIET HOA DON ==================================
// ====================================================================================

// tim chi tiet hoa don
int timCTHD(DSChiTietHoaDon &DSCTHD, string maVT)
{
	for (int i = 0; i < DSCTHD.sl; i++)
		if(DSCTHD.ds[i].maVT == maVT) 
			return i;
	return -1;
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

// =============== loai bo 1 chi tiet hoa don ================
int xoaMotCTHD(DSChiTietHoaDon &DSCTHD, int i)
{
	int j;
	if(i < 0 || i >= DSCTHD.sl || DSCTHD.sl == 0) return 0;
	for(j = i + 1;  j < DSCTHD.sl; j++)
		DSCTHD.ds[j - 1] = DSCTHD.ds[j];
	DSCTHD.sl--;
	return 1; 
}

// tra ve ten loai hoa don dua vao loai
string tenLoaiHD(string loai) {
	if(loai == "X")
		return "XUAT";
	else return "NHAP";
}

void khungThongTinCTHD(DSChiTietHoaDon DSCTHD){
	TextColor(241);
	gotoxy(147, 5); cout << "                                              ";
	gotoxy(147, 6); cout << "           DANH SACH CHI TIET VAT TU          ";
	gotoxy(147, 7); cout << "                                              ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 133; i <= 205; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(133, i); cout << char(186);
		gotoxy(205, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(140, i); cout << char(186);
		gotoxy(164, i); cout << char(186);
		gotoxy(181, i); cout << char(186);
		gotoxy(193, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(205, 9); cout << char(187);
	gotoxy(205, 11); cout << char(185);
	gotoxy(205, 27); cout << char(188);
	
	gotoxy(133, 9); cout << char(201);
	gotoxy(133, 11); cout << char(204);
	gotoxy(133, 27); cout << char(200);
	
	gotoxy(140, 9); cout << char(203);
	gotoxy(164, 9); cout << char(203);
	gotoxy(181, 9); cout << char(203);
	gotoxy(193, 9); cout << char(203);
	
	gotoxy(140, 27); cout << char(202);
	gotoxy(164, 27); cout << char(202);
	gotoxy(181, 27); cout << char(202);
	gotoxy(193, 27); cout << char(202);
	
	gotoxy(135, 10); cout << "STT";
	gotoxy(147, 10); cout << "MA VAT TU";
	gotoxy(169, 10); cout << "DON GIA";
	gotoxy(183, 10); cout << "SO LUONG";
	gotoxy(197, 10); cout << "VAT";
	
	int stt = 0, hang = 0;
	for(int i = 0; i < 15 && i < DSCTHD.sl; i++) {
		stt += 1;
		gotoxy(137, 12 + hang); cout << stt; 
		gotoxy(145, 12 + hang); cout << DSCTHD.ds[i].maVT;
		gotoxy(167, 12 + hang); cout << DSCTHD.ds[i].donGia;
		gotoxy(183, 12 + hang); cout << DSCTHD.ds[i].soLuong;
		gotoxy(195, 12 + hang); cout << DSCTHD.ds[i].VAT;
		hang++;
	}
}

// ==================== luu hoa don =========================
void luuHoaDon(DSNhanVien &DSNV) {
	ghiFileDSNV(DSNV);
	THONG_BAO(" GHI FILE THANH CONG! ", 90, 40, 167);
	return;
}

// =================== ham cap nhat lai so luong ton cua vat tu neu nguoi do huy khong luu hoa don ===================
void capNhatSLTon(DSVatTu &DSVT, DSChiTietHoaDon &DSCTHD, string loai){
	for(int i = 0; i < DSCTHD.sl;  i++) {
		TREE tree = timNodeVT(DSVT.TREE_VT, DSCTHD.ds[i].maVT);
		// neu hoa don xuat thi khi cap nhat lai phai cong vao so vat tu da xuat ra
		if(tree && loai.compare("X") == 0) 
		{ 
			tree->info.slTon += DSCTHD.ds[i].soLuong;
			tree->info.tonTaiTrongHD -= 1;
		}
		// neu hoa don nhap thi khi cap nhat lai phai tru di so vat tu da nhap
		else if(tree && loai.compare("N") == 0) 
		{ 
			tree->info.slTon -= DSCTHD.ds[i].soLuong;
			tree->info.tonTaiTrongHD -= 1;
		}
	}
	
	ghiFileDSVT(DSVT);
}

bool xacNhanThoatLapHD(DSNhanVien &DSNV, DSVatTu &DSVT, PTRHD p, int vtNVLap, DSChiTietHoaDon &DSCTHDTam, string loai) {
	gotoxy(109, 37); cout << "BAN CO CHAC CHAN MUON THOAT LAP HOA DON KHONG?";
				
	int xacNhan = thongBaoXacNhan();
	if(xacNhan) {
		// neu xac nhan huy nhap va da nhap 1 so chi tiet hoa don roi
		if(p->info.dsChiTietHoaDon.sl > 0) {
			gotoxy(109, 37); cout << "BAN CO MUON LUU HOA DON KHONG?";
			xacNhan = thongBaoXacNhan();
			if(xacNhan) {
				themMotHD(DSNV.nv[vtNVLap]->DSHD.FirstHD, p); ++DSNV.nv[vtNVLap]->DSHD.sl;
				ghiFileDSVT(DSVT);
				luuHoaDon(DSNV);
				return true;
			} else {
				capNhatSLTon(DSVT, DSCTHDTam, loai);
				THONG_BAO(" BAN DA HUY HOA DON. GHI FILE KHONG THANH CONG! ", 90, 40, 79);
				return true;
			}
		} else { // neu xac nhan huy nhap nhung chua co chi tiet hoa don nao
			THONG_BAO(" BAN DA HUY HOA DON. GHI FILE KHONG THANH CONG! ", 90, 40, 79);
			return true;
		}
	}
	return false;
}

//======================== lap hoa don ======================
void lapHoaDon(DSNhanVien &DSNV, DSVatTu &DSVT)
{
	string maNV, noiDungCu = "";
	khungNhapXoa();
	
NhapLai:
	gotoxy(72, 12); cout << "Nhap Ma Nhan Vien Can Lap Hoa Don: ";
	gotoxy(107, 12); maNV = nhapLieu(3, noiDungCu);
	if(maNV == "-1") {
		THONG_BAO(" BAN DA THOAT LAP HOA DON ", 90, 40, 79);
		xoaKhungNhapXoa();
		return;
	}
	
	int vtNVLap = kiemTraMaNV(DSNV, maNV);
	
	// neu ma nhan vien khong ton tai
	if (vtNVLap == -1)
	{
		THONG_BAO(" MA NHAN VIEN KHONG TON TAI! ", 90, 40, 79);
		noiDungCu = maNV;
		goto NhapLai;
	}
	else
	{
		//xu ly lap hoa don
		PTRHD p = khoiTaoNodeHD();
		
		int key;
		khungXacNhan();
		gotoxy(113, 37); cout << " CHON LOAI HOA DON BAN MUON LAP ";
		int chon = 0;
		while(1) {
			
			if(chon == 0) {
				TextColor(228);
				gotoxy(114, 39); cout << " Hoa Don Nhap ";
				TextColor(7);
				gotoxy(132, 39); cout << " Hoa don Xuat ";
			} else {
				gotoxy(114, 39); cout << " Hoa Don Nhap ";
				TextColor(228);
				gotoxy(132, 39); cout << " Hoa don Xuat ";
				TextColor(7);
			}
			
			key = getKey();
			if(key == RIGHT) {
				chon = 1;
			} else if(key == LEFT) {
				chon = 0;
			} else if(key == ENTER) {
				if(chon == 0) {
					xoaKhungXacNhan();
					xoaKhungNhapXoa();
					p->info.loai = "N";
					break;
				} else {
					xoaKhungXacNhan();
					xoaKhungNhapXoa();
					p->info.loai = "X";
					break;
				}
			} else if(key == ESC) {
				noiDungCu = maNV;
				xoaKhungXacNhan();
				goto NhapLai;
			}
		}
		
		p->info.soHD = taoMaHD(DSNV);
		khungNhapHoaDon();
		gotoxy(63, 6); cout << "Ma hoa don   : " << p->info.soHD;
		gotoxy(63, 7); cout << "Loai hoa don : " << tenLoaiHD(p->info.loai);
			
NhapLaiNgay:
		gotoxy(78, 8); p->info.ngayLap.ngay = nhapSoNguyen("");  if(p->info.ngayLap.ngay == -1) { xoaKhungNhapHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
		gotoxy(78, 9); p->info.ngayLap.thang = nhapSoNguyen(""); if(p->info.ngayLap.thang == -1) { xoaKhungNhapHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
		gotoxy(78, 10); p->info.ngayLap.nam = nhapSoNguyen("");   if(p->info.ngayLap.nam == -1) { xoaKhungNhapHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
		
		if(laNgayHopLe(p->info.ngayLap) == false)
		{
			THONG_BAO(" NGAY BAN VUA NHAP KHONG HOP LE! ", 90, 40, 79);
			xoaNhapNgayBatDau();
			goto NhapLaiNgay;
		}
		
		THONG_BAO("TAO HOA DON THANH CONG! BAM PHIM BAT KI DE TIEP TUC NHAP CHI TIET HOA DON", 60, 40, 167);
		
		gotoxy(63, 13); cout << "Nhan phim bat ki de tiep tuc: "; 
		key = getKey();
		
		if(key == ESC) {
			THONG_BAO(" BAN DA HUY LAP HOA DON! DU LIEU SE KHONG DUOC LUU ", 70, 40, 79);
			xoaKhungNhapHD();
			return;
		}
		
		gotoxy(63, 13); cout << "                                 ";
		
		//----- lap chi tiet hoa don --------------
		// hoa don nhap
		if(p->info.loai == "N") {
			DSChiTietHoaDon DSCTHDTam;
			noiDungCu = "";
			ChiTietHoaDon CTHD;
			khungNhapCTHD();
			
			gotoxy(63, 21); cout << "Nhap ma vat tu: ";
			gotoxy(63, 22); cout << "Nhap so luong : ";
			gotoxy(63, 23); cout << "Nhap don gia  : ";
			gotoxy(63, 24); cout << "Nhap VAT      : ";
			gotoxy(63, 25); cout << "                      ";
			
NhapCTHDNhap:
			xoaKhungThongTinCTHD();
			khungThongTinCTHD(p->info.dsChiTietHoaDon);
			
			gotoxy(79, 21); cout << "                      ";
			gotoxy(79, 22); cout << "                      ";
			gotoxy(79, 23); cout << "                      ";
			gotoxy(79, 24); cout << "                      ";
			
			gotoxy(79, 21); CTHD.maVT = nhapLieu(3, noiDungCu);
			if(CTHD.maVT == "-1") {
				bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
				if(!kiemTraThoat)
					goto NhapCTHDNhap;
				else {
					xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
					return;	
				}
			}
			
			TREE tree = timNodeVT(DSVT.TREE_VT, CTHD.maVT);
			
			if(!tree) {
				THONG_BAO(" MA VAT TU KHONG TON TAI! VUI LONG NHAP LAI ", 90, 40, 79);
				noiDungCu = CTHD.maVT;
				goto NhapCTHDNhap;
			} else {
				gotoxy(79, 22); CTHD.soLuong = nhapSoPhay("");
				if(CTHD.soLuong == -1) {
					bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
					if(!kiemTraThoat)
						goto NhapCTHDNhap;
					else {
						xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
						return;	
					}
				}
				
				gotoxy(79, 23); CTHD.donGia = nhapSoNguyen("");
				if(CTHD.donGia == -1) {
					bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
					if(!kiemTraThoat)
						goto NhapCTHDNhap;
					else {
						xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
						return;	
					}
				}
				
				gotoxy(79, 24); CTHD.VAT = nhapSoPhay("");
				if(CTHD.VAT == -1) {
					gotoxy(109, 37); cout << "BAN CO CHAC CHAN MUON THOAT LAP HOA DON KHONG?";
					
					int xacNhan = thongBaoXacNhan();
					if(xacNhan) return;	
					else goto NhapCTHDNhap;
				}
				
				int trangThaiThem = themMotCTHD(p->info.dsChiTietHoaDon, CTHD);
				
				if(!trangThaiThem) {
					THONG_BAO(" THEM CHI TIET HOA DON THAT BAI. HOA DON DAY ", 90, 40, 79);
					THONG_BAO(" BAM ESC DE THOAT HOAC LUU HOA DON! ", 90, 40, 79);
					goto NhapCTHDNhap;
					return;
				} else {					
					// tinh toan cap nhat lai so luong ton
					float slTonBanDau = tree->info.slTon;
					float slNhapThem = CTHD.soLuong;
					tree->info.slTon = slTonBanDau + slNhapThem;
					tree->info.tonTaiTrongHD += 1;
					
					themMotCTHD(DSCTHDTam, CTHD);
					
					THONG_BAO(" THEM VAT TU VAO HOA DON THANH CONG! BAN CO MUON TIEP TUC NHAP? ", 65, 40, 167);
					
					gotoxy(112, 37); cout << "TIEP TUC NHAP CHI TIET HOA DON?";
					int xacNhan = thongBaoXacNhan();
					if(xacNhan) 
						goto NhapCTHDNhap;	
					else 
					{
						bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
						if(!kiemTraThoat)
							goto NhapCTHDNhap;
						else {
							xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
							return;	
						}
					}
				}
			}
		} else { // hoa don xuat
			noiDungCu = "";
			ChiTietHoaDon CTHD;
			DSChiTietHoaDon DSCTHDTam;
			
			khungNhapCTHD();
			
			gotoxy(63, 21); cout << "Nhap ma vat tu: ";
			gotoxy(63, 22); cout << "Nhap so luong : ";
			gotoxy(63, 23); cout << "Nhap don gia  : ";
			gotoxy(63, 24); cout << "Nhap VAT      : ";
			gotoxy(63, 25); cout << "                      ";
			
NhapCTHDXuat:
			khungThongTinCTHD(p->info.dsChiTietHoaDon);	
			
			gotoxy(79, 21); cout << "                      ";
			gotoxy(79, 22); cout << "                      ";
			gotoxy(79, 23); cout << "                      ";
			gotoxy(79, 24); cout << "                      ";
	
			gotoxy(79, 21); CTHD.maVT = nhapLieu(3, noiDungCu);
			if(CTHD.maVT == "-1") {
				bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
				if(!kiemTraThoat)
					goto NhapCTHDXuat;
				else {
					xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
					return;	
				}
			}
			
			TREE tree = timNodeVT(DSVT.TREE_VT, CTHD.maVT);
			
			if(!tree) 
			{
				THONG_BAO(" MA VAT TU KHONG TON TAI! VUI LONG NHAP LAI ", 90, 40, 79);
				noiDungCu = CTHD.maVT;
				goto NhapCTHDXuat;
			} 
			else 
			{
				gotoxy(79, 22); CTHD.soLuong = nhapSoPhay("");
				if(CTHD.soLuong == -1) {
					bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
					if(!kiemTraThoat)
						goto NhapCTHDXuat;
					else {
						xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
						return;	
					}
				}
				
				gotoxy(79, 23); CTHD.donGia = nhapSoNguyen("");
				if(CTHD.donGia == -1) {
					bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
					if(!kiemTraThoat)
						goto NhapCTHDXuat;
					else {
						xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
						return;	
					}
				}
				
				gotoxy(79, 24); CTHD.VAT = nhapSoPhay("");
				if(CTHD.VAT == -1) {
					gotoxy(109, 37); cout << "BAN CO CHAC CHAN MUON THOAT LAP HOA DON KHONG?";
					
					int xacNhan = thongBaoXacNhan();
					if(xacNhan) return;	
					else goto NhapCTHDXuat;
				}
				
				int trangThaiThem = themMotCTHD(p->info.dsChiTietHoaDon, CTHD);
				
				if(!trangThaiThem) 
				{
					THONG_BAO(" THEM CHI TIET HOA DON THAT BAI. HOA DON DAY ", 90, 40, 79);
					THONG_BAO(" BAM ESC DE THOAT HOAC LUU HOA DON! ", 90, 40, 79);
					goto NhapCTHDXuat;
					return;
				} 
				else 
				{
					// tinh toan cap nhat lai so luong ton
					float slTonBanDau = tree->info.slTon;
					float slXuatRa = CTHD.soLuong;
					
					if(slTonBanDau < slXuatRa) 
					{
						THONG_BAO(" SO LUONG VAT TU TRONG KHO KHONG DU! ", 80, 40, 79);
						
						TextColor(224);
						gotoxy(90, 40); cout << "                SO LUONG " << tree->info.tenVT << " HIEN CO: " << tree->info.slTon << "                  ";
						TextColor(7);
						Sleep(3000);
						
						// neu so luong vat tu xuat ko du thi xoa di cthd vua them vo chinh la cthd o cuoi cua hoa don do
						xoaMotCTHD(p->info.dsChiTietHoaDon, p->info.dsChiTietHoaDon.sl - 1);
						
						noiDungCu = CTHD.maVT;
						goto NhapCTHDXuat;
					} 
					else 
					{
						tree->info.slTon = slTonBanDau - slXuatRa;
						tree->info.tonTaiTrongHD += 1;
						themMotCTHD(DSCTHDTam, CTHD);
						
						THONG_BAO(" THEM VAT TU VAO HOA DON THANH CONG! BAN CO MUON TIEP TUC NHAP? ", 65, 40, 167);
						
						gotoxy(112, 37); cout << "TIEP TUC NHAP CHI TIET HOA DON?";
						int xacNhan = thongBaoXacNhan();
						if(xacNhan) {
							goto NhapCTHDXuat;	
						}
						else 
						{
							bool kiemTraThoat = xacNhanThoatLapHD(DSNV, DSVT, p, vtNVLap, DSCTHDTam, p->info.loai);
							if(!kiemTraThoat)
								goto NhapCTHDXuat;
							else {
								xoaKhungNhapHD(); xoaKhungNhapCTHD(); xoaKhungThongTinCTHD();
								return;	
							}
						}
					}
				}
			}
		}
	}
}

// ========================== tinh tri gia cua hoa don =============================
long long tinhTriGiaHD(DSChiTietHoaDon &DSCTHD) {
	long long tongCong = 0;
	for(int i = 0 ; i < DSCTHD.sl ; i++)
		tongCong += tinhThanhTienCTHD(DSCTHD.ds[i]);
	return tongCong;
}

// ===================== xuat danh sach hoa don cua 1 nhan vien =======================
void inDSHDMotNhanVien(DSNhanVien &DSNV, int vtNV) {
	xoaKhungNhapXemHD();
	int trang = 0, tongTrang;
	int key;
	
	while(1) {
		if(DSNV.sl < 15) {
			tongTrang = 1;
		} else {
			tongTrang = (DSNV.sl - 1) / 15 + 1;
		}
		
		int hang = 0; int stt = 0;
		// dua vao bien duyet de biet in ra tu phan tu nao
		int bienDuyet = 0;
		// tao ra 2 gioi han duyet de biet in ra tu phan tu nao
		int gioiHanDuyetPhai = trang * 15 + 15; int gioiHanDuyetTrai = trang * 15;
		
		xoaKhungDSHD(); khungXuatDSHD();
	 	for (PTRHD p = DSNV.nv[vtNV]->DSHD.FirstHD; p != NULL; p = p->pNext) {
			if((bienDuyet >= gioiHanDuyetTrai && bienDuyet < gioiHanDuyetPhai) && bienDuyet < DSNV.sl) {
				stt += 1;
				gotoxy(81, 12 + hang); cout << stt;
				gotoxy(91, 12 + hang); cout << p->info.soHD << endl;
				gotoxy(113, 12 + hang); cout << p->info.ngayLap.ngay << "/" << p->info.ngayLap.thang << "/" << p->info.ngayLap.nam << endl;
				gotoxy(157, 12 + hang); cout << tenLoaiHD(p->info.loai) << endl;
				hang++;
				bienDuyet += 1;
			} else {
				bienDuyet += 1;
				stt += 1;
			}
		}
		
		hienThiTrang(trang + 1, tongTrang, 158, 29);
		key = getKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			xoaKhungDSHD();
			xoaKhungNhapXemHD();
			return;	
		}
	}
}

void inChiTietHD(DSNhanVien &DSNV, int vtNV, string soHD, DSVatTu DSVT) {
	PTRHD p;
	for(p = DSNV.nv[vtNV]->DSHD.FirstHD; p != NULL; p = p->pNext) 
		if (p->info.soHD == soHD) 
			break;
	
	if(p->info.dsChiTietHoaDon.sl == 0)
	{
		TextColor(79);
		gotoxy(110, 16); cout << "HOA DON KHONG CO VAT TU NAO!" << endl;
		TextColor(7);
	}
	else
	{
		TextColor(241);
		gotoxy(60, 10); cout << "       THONG TIN HOA DON              ";
		gotoxy(60, 11); cout << "     So Hoa Don : " << p->info.soHD << "          ";
		gotoxy(60, 12); cout << "     Ngay Lap   : " << p->info.ngayLap.ngay << "/" << p->info.ngayLap.thang << "/" << p->info.ngayLap.nam << "           ";
		gotoxy(60, 13); cout << "     Loai       : " << tenLoaiHD(p->info.loai) << "                ";
		gotoxy(60, 14);  cout << "                                      ";
		TextColor(7);
		
		long long tongCong = tinhTriGiaHD(p->info.dsChiTietHoaDon);
		long long thanhTien = 0;
		
		int trang = 0, tongTrang;
		int key;
		
		while(1) {
			if(p->info.dsChiTietHoaDon.sl < 15) {
				trang = 0;
				tongTrang = 1;
			} else {
				tongTrang = (p->info.dsChiTietHoaDon.sl - 1) / 15 + 1;
			}
			
			int hang = 0; int stt = 0;
			 
			xoaKhungXuatCTHD(); khungXuatCTHD(tongCong);
			for(int i = trang * 15; i < 15 + trang * 15 && i < p->info.dsChiTietHoaDon.sl; i++)
			{
				stt = i + 1;
				gotoxy(56, 19 + hang); cout << stt;
				gotoxy(67, 19 + hang); cout << p->info.dsChiTietHoaDon.ds[i].maVT;
				
				// lay ra ten vat tu de hien thi dua vao ma vat tu cua CTHD
				TREE TREE_VT = timNodeVT(DSVT.TREE_VT, p->info.dsChiTietHoaDon.ds[i].maVT);
				gotoxy(89, 19 + hang); cout << TREE_VT->info.tenVT;
				gotoxy(134, 19 + hang); cout << p->info.dsChiTietHoaDon.ds[i].soLuong;
				gotoxy(152, 19 + hang); cout << p->info.dsChiTietHoaDon.ds[i].donGia;
				gotoxy(173, 19 + hang); cout << p->info.dsChiTietHoaDon.ds[i].VAT;
				
				thanhTien = tinhThanhTienCTHD(p->info.dsChiTietHoaDon.ds[i]);
				//cout << setprecision(19);
				gotoxy(189, 19 + hang); cout << thanhTien;
				hang++;
			}
			
			hienThiTrang(trang + 1, tongTrang, 175, 37);
			key = getKey();
			if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
				trang++;
			if((key == LEFT || key == UP) && trang > 0)
				trang--;
			if(key == ESC) {
				xoaTrangXuatCTHD();
				return;	
			}
		}
		
	}
}

// =========== ham chuyen danh sach hao don thanh mang de giup cho viec xuat ==========
void chuyenDSHDSangMang(DSNhanVien &DSNV, int vtNV, HoaDon *hd, int &nHD) {
	for(PTRHD p = DSNV.nv[vtNV]->DSHD.FirstHD; p != NULL; p = p->pNext) {
		hd[nHD] = p->info;
		nHD++;
	}
}

// ================================= xuat hoa don =====================================
void inHoaDon(DSNhanVien &DSNV, DSVatTu &DSVT) 
{
	string noiDungCu = "";
	string soHD, maNV;
NhapLai:
	khungNhapXemHD();
	gotoxy(72, 12); cout << "Nhap Ma Nhan Vien Xem Hoa Don: ";
	maNV = nhapLieu(3, noiDungCu);
	if(maNV == "-1") {
		THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79);
		xoaKhungNhapXemHD();
		return;
	}	
	
	int vtNV = kiemTraMaNV(DSNV, maNV);
	
	if(vtNV == -1) 
	{
		THONG_BAO("MA NHAN VIEN KHONG TON TAI!", 90, 40, 79);
		noiDungCu = maNV;
		goto NhapLai;
	}
	else 
	{
		if(DSNV.nv[vtNV]->DSHD.FirstHD == NULL) {
			THONG_BAO("NHAN VIEN CHUA LAP HOA DON" , 90, 40, 79);
			noiDungCu = maNV;
			goto NhapLai;
		}
		
		// in ra danh sach hoa don cua nhan vien
		// 0: nhan vien chua co hoa don, 1: nhan vien co hoa don
		inDSHDMotNhanVien(DSNV, vtNV);
		
		string noiDungHDCu = "";
NhapSoHD:
		khungNhapXemHD();
		gotoxy(72, 13); cout << "Nhap So Hoa Don Muon Xem: ";
		soHD = nhapLieu(1, noiDungHDCu);
		if(soHD == "-1") {
			THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79);
			xoaKhungNhapXemHD();
			return;
		}
		
		bool tonTaiSoHD = ktTrungMaHDTrongNV(DSNV.nv[vtNV]->DSHD.FirstHD, soHD);
		if(!tonTaiSoHD) 
		{
			THONG_BAO("SO HOA DON KHONG TON TAI TRONG NHAN VIEN NAY!", 90, 40, 79);
			noiDungHDCu = soHD;
			goto NhapSoHD;
		}
		else 
		{
			xoaKhungNhapXemHD();
			khungThongTinNV(DSNV.nv[vtNV]->ho, DSNV.nv[vtNV]->ten, DSNV.nv[vtNV]->phai);
			
			inChiTietHD(DSNV, vtNV, soHD, DSVT);
		}
		
	}
}

// ham dua vao so hoa don va duyet tra ve vvi tri nhan vien so huu hoa don do
int viTriNhanVienChuaHD(DSNhanVien &DSNV, string soHD) {
	for(int i = 0; i < DSNV.sl; i++) {
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext) {
			if(soHD.compare(p->info.soHD) == 0) {
				return i;
			}
		}
	}
	return -1;
}

void inThongTinHoaDon(DSHoaDon &DSHD, DSNhanVien &DSNV, Date ngayBatDau, Date ngayKetThuc) {
	if(DSHD.sl == 0) {
		THONG_BAO("KHONG CO HOA DON NAO NAM TRONG KHOANG THOI GIAN NAY!", 90, 40, 79);
		xoaKhungXuatHoaDon();
		return;
	}
		

	int trang = 0;
	int tongTrang, key;
	
	while(1) {
		if(DSHD.sl < 15) {
			tongTrang = 1;
		} else {
			tongTrang = (DSHD.sl - 1) / 15 + 1;
		}
		
		int hang = 0, stt = 0;
		int gioiHanTrai = trang * 15; int gioiHanPhai = 15 + trang * 15;
		int bienDuyet = 0;
		xoaKhungXuatHoaDon(); khungXuatHoaDon(); 
		inKhoanThoiGian(ngayBatDau, ngayKetThuc);
		for(PTRHD p = DSHD.FirstHD; p != NULL; p = p->pNext) {
			if((bienDuyet >= gioiHanTrai && bienDuyet < gioiHanPhai) && bienDuyet < DSHD.sl) 
			{
				int vtNV = viTriNhanVienChuaHD(DSNV, p->info.soHD);
			
				stt++;
				gotoxy(56, 19 + hang); cout << stt;
				gotoxy(67, 19 + hang); cout << p->info.soHD;
				gotoxy(89, 19 + hang); cout << DSNV.nv[vtNV]->ho << " " << DSNV.nv[vtNV]->ten;
				gotoxy(134, 19 + hang); cout << p->info.ngayLap.ngay << "/" << p->info.ngayLap.thang << "/" << p->info.ngayLap.nam;
				cout << setprecision(12);
				gotoxy(152, 19 + hang); cout << loaiHoaDon(p->info.loai);
				gotoxy(173, 19 + hang); cout << tinhTriGiaHD(p->info.dsChiTietHoaDon);
				bienDuyet++; hang++;
			} 
			else 
			{
				bienDuyet++;
				stt++;
			}
			
		}
		
		hienThiTrang(trang + 1, tongTrang, 175, 37);
		key = getKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			xoaKhungXuatHoaDon();
			return;	
		}
	}
}

// ======================= xuat hoa don trong khoang thoi gian =========================
void inHoaDonTrongKhoangTG(DSNhanVien &DSNV) {
	Date ngayBatDau,ngayKetThuc;
	string noiDungCu = "";
	
NhapNgayBD:
	khungNhapXemTGHD();	
	gotoxy(80, 13); ngayBatDau.ngay = nhapSoNguyen(noiDungCu);  if(ngayBatDau.ngay == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	gotoxy(80, 14); ngayBatDau.thang = nhapSoNguyen(noiDungCu); if(ngayBatDau.thang == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	gotoxy(80, 15); ngayBatDau.nam = nhapSoNguyen(noiDungCu);   if(ngayBatDau.nam == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	bool trangThaiNBD = laNgayHopLe(ngayBatDau);
	if(!trangThaiNBD)
	{
		THONG_BAO("NGAY BAT DAU KHONG TON TAI!", 90, 40, 79);
		xoaNhapNgayBatDau();
		goto NhapNgayBD;
	}
	
NhapNgayKT:
	gotoxy(112, 13); ngayKetThuc.ngay = nhapSoNguyen(noiDungCu);  if(ngayKetThuc.ngay == -1)  { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	gotoxy(112, 14); ngayKetThuc.thang = nhapSoNguyen(noiDungCu); if(ngayKetThuc.thang == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	gotoxy(112, 15); ngayKetThuc.nam = nhapSoNguyen(noiDungCu);   if(ngayKetThuc.nam == -1) { xoaKhungNhapXemTGHD(); THONG_BAO("BAN DA THOAT XEM HOA DON", 90, 40, 79); return; }
	bool trangThaiNKT = laNgayHopLe(ngayKetThuc);
	if(!trangThaiNKT)
	{
		THONG_BAO("NGAY KET THUC KHONG TON TAI!", 90, 40, 79);
		xoaNhapNgayKetThuc();
		goto NhapNgayKT;
	}
	
	int soSanhHaiNgay = soSanhThoiGian(ngayBatDau, ngayKetThuc);
	if(soSanhHaiNgay == 1)
	{
		THONG_BAO("THOI GIAN KHONG HOP LE! NGAY BAT DAU LON HON NGAY KET THUC!", 85, 40, 79);
		xoaNhapNgayBatDau();
		xoaNhapNgayKetThuc();
		goto NhapNgayBD;
	}
	else if(soSanhHaiNgay == 0)
	{
		THONG_BAO("THOI GIAN KHONG HOP LE! NGAY BAT DAU VA NGAY KET THUC BANG NHAU!", 85, 40, 79);
		xoaNhapNgayBatDau();
		xoaNhapNgayKetThuc();
		goto NhapNgayBD;
	}
	
	// khai bao mo hoa don tam de luu thong tin nhung hoa don trong khoang thoi gian de xuat ra
	DSHoaDon DSHDTam;
		
	xoaKhungNhapXemTGHD();
	inKhoanThoiGian(ngayBatDau, ngayKetThuc);
	int duyet = 0;
	for(int i = 0; i < DSNV.sl; i++) {
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext) {
			if(ngayNamTrongKhoang(ngayBatDau, ngayKetThuc, p->info.ngayLap))
			{
				PTRHD hdMoi = khoiTaoNodeHD();
				hdMoi->info = p->info;
				themMotHD(DSHDTam.FirstHD, hdMoi); DSHDTam.sl++;
			}
		}
	}
	
	inThongTinHoaDon(DSHDTam, DSNV, ngayBatDau, ngayKetThuc);
}

// =====================================================================================
// ===================================== DOC FILE ======================================
// =====================================================================================

// ========================== DOC FILE DU LIEU NGAY THANG NAM ==========================
void DocNgayThangNam(ifstream &inFile, Date &ngayLap) {
	string tempNgay, tempThang, tempNam;
	getline(inFile, tempNgay, '/'); istringstream(tempNgay) >> ngayLap.ngay;
	getline(inFile, tempThang, '/'); istringstream(tempThang) >> ngayLap.thang;
	getline(inFile, tempNam, ','); istringstream(tempNam) >> ngayLap.nam;
}

// =============================== DOC FILE NHAN VIEN ==================================
void DocFileDSNV(DSNhanVien &DSNV) 
{
	ifstream inFile;
	string tempSL, tempDG, tempVAT;
	inFile.open("DSNV.txt", ios_base::in);
	if(inFile.fail()) {
		cout << "FILE DANH SACH SINH VIEN KHONG TON TAI!" << endl;
		return;
	}
	
	// bien luu tong nhan vien tu file dua vao bien nay de dat dieu kien vong lap
	int tongNV;
	
	// doc thong tin nhan vien
	inFile >> tongNV;
	
	for(int i = 0; i < tongNV; i++) {
		inFile.ignore();
		NhanVien *nv = new NhanVien;
		
		getline(inFile, nv->maNV, ',');
		getline(inFile, nv->ho, ',');
		getline(inFile, nv->ten, ',');
		getline(inFile, nv->phai, '\n');
		
		// doc thong tin hoa don cua nhan vien do
		inFile >> nv->DSHD.sl;
		
		for(int j = 0; j < nv->DSHD.sl; j++) {
			inFile.ignore();
			PTRHD hd = khoiTaoNodeHD();
			getline(inFile, hd->info.soHD, ',');
			DocNgayThangNam(inFile, hd->info.ngayLap);
			getline(inFile, hd->info.loai, '\n');
			
			// doc thong tin chi tiet  hoa don cua hoa don do
			int tongCTHD;
			inFile >> tongCTHD;
			
			for(int i = 0; i < tongCTHD; i++) {
				ChiTietHoaDon cthd;
				inFile.ignore();
				getline(inFile, cthd.maVT, ',');
				inFile >> cthd.soLuong; inFile.ignore();
				inFile >> cthd.donGia; inFile.ignore();
				inFile >> cthd.VAT;
				themMotCTHD(hd->info.dsChiTietHoaDon, cthd);
			}
			
			themMotHD(nv->DSHD.FirstHD, hd);
		}
		
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
	inFile.ignore();
	
	while(!inFile.eof())
	{
		TREE vt = KhoiTaoNodeVT();
		getline(inFile, vt->info.maVT, ',');
		getline(inFile, vt->info.tenVT, ',');
		inFile >> vt->info.slTon; 
		inFile.ignore();
		inFile >> vt->info.tonTaiTrongHD; 
		inFile.ignore();
		getline(inFile, vt->info.dvt, '\n');
		
		themMotVatTu(DSVT.TREE_VT, vt);
	}
	inFile.close();
}

// ============================= GIAI PHONG BO NHO ====================================

// ----------------------- giai phong danh sach vat tu --------------------------------
void GIAI_PHONG_VAT_TU(TREE &TREE_VT) {
	if (TREE_VT != NULL) {
		GIAI_PHONG_VAT_TU(TREE_VT->pLeft);
		GIAI_PHONG_VAT_TU(TREE_VT->pRight);
		delete TREE_VT;
		TREE_VT = NULL;
	}
}

// --------------------- giai phong nhan vien & hoa don --------------------------------
void GIAI_PHONG_NHAN_VIEN_HD(DSNhanVien &DSNV) {
	for(int i = 0; i < DSNV.sl; i++) {
		for(PTRHD p = DSNV.nv[i]->DSHD.FirstHD; p != NULL; p = p->pNext) {
			delete p;
		}
		delete DSNV.nv[i];
	}
}

// ---------------------------------------- giai phong ----------------------------------
void GIAI_PHONG_BO_NHO(DSVatTu &DSVT, DSNhanVien &DSNV) {
	GIAI_PHONG_VAT_TU(DSVT.TREE_VT);
	GIAI_PHONG_NHAN_VIEN_HD(DSNV);
}

// ---------------------------------------- menu dong ------------------------------------
int MenuDong(char MenuChinh[][40], int item) {
	int row;
	// dang o vi tri nao cua menu
	int thaotac = 0;
	int mau[5];
	for(int i = 0; i < item; i++)
		mau[i] = 7;
	mau[0] = 225;
	
	TextColor(228);
	gotoxy(19, 22); cout << "    MENU    ";
	khungHuongDan();
	xuatTenDeTai();
	khungGiaoDien();
	xoaMenu();
	// vong while lap vo han cho toi khi tra ve cai gi do
	while (1) {
		for (int i = 0; i < item; i++)
		{
			TextColor(mau[i]);
			gotoxy(10, 25 + i); cout << "   " << MenuChinh[i] << "   ";
		}
		int key = getKey();
		switch (key)
		{
			case UP:
			case LEFT:
			{
				if (thaotac == 0)
					thaotac = item - 1;
				else
					thaotac--;
				break;
			}
			case DOWN:
			case RIGHT:
			{
				if (thaotac == item - 1)
					thaotac = 0;
				else
					thaotac++;
				break;
			}
			case ESC:
			{
				TextColor(7);
				return thaotac = 27;
			}
			case ENTER:
			{
				TextColor(7);
				xoaTenDeTai();
				return thaotac + 1;
			}
		}
		for (int i = 0; i < item; i++)
			mau[i] = 7;
		mau[thaotac] = 225;
	}
	
}

//================================ MENNU TINH =========================================
void Menu() {
	// khoi tao cac danh sach
	DSNhanVien DSNV;
	DSVatTu DSVT;
	DSDoanhThu DSDT;
	
	// doc file
	DocFileDSNV(DSNV);
	DocFileDSVT(DSVT);
	
	while(1) {
		clrscr();
		int tungDo = 0;
		
menuChinh:
		int thaotac = MenuDong(MENU, 4);
		
		switch(thaotac) 
		{
			case 1: {
menuVatTu:
				int thaotac = MenuDong(MENU_VAT_TU, 5);		
				if(thaotac == 1) {
					nhapVatTu(DSVT);
					xoaKhungThemVT();
					goto menuVatTu;
				}
				if(thaotac == 2) {
					VatTu *vt[100];
					int nVT = 0;
					chuyenCaySangMang(DSVT.TREE_VT, vt, nVT);
					xuatDanhSachVT(vt, nVT);
					giaiPhongDSVatTu(vt, nVT);
					goto menuVatTu;
				}
				if(thaotac == 3) {
					xoaVatTu(DSNV, DSVT);
					xoaKhungNhapXoa();
					goto menuVatTu;
				}
				if(thaotac == 4) {
					hieuChinhVatTu(DSVT);
					xoaKhungThemVT();
					xoaKhungCapNhatNV();
					goto menuVatTu;
				}
				if(thaotac == 5) {
					thongKeDoanhThu(DSNV, DSVT, DSDT);
					goto menuVatTu;
				}
				break;
			}	
			case 2: {
menuNhanVien:	
				int thaotac = MenuDong(MENU_NHAN_VIEN, 4);	
				if(thaotac == 1) {
					nhapNhanVien(DSNV);
					xoaKhungThemVT();
					goto menuNhanVien;
				}
				if(thaotac == 2) {
					xuatDSNV(DSNV);
					goto menuNhanVien;
				}
				if(thaotac == 3) {
					xoaNhanVien(DSNV);
					xoaKhungNhapXoa();
					goto menuNhanVien;
				}
				if(thaotac == 4) {
					hieuChinhNhanVien(DSNV);
					xoaKhungThemVT();
					xoaKhungCapNhatNV();
					goto menuNhanVien;
				}
				break;
			}
			case 3: {
menuHoaDon:
				int thaotac = MenuDong(MENU_HOA_DON, 3);	
				if(thaotac == 1) {
					lapHoaDon(DSNV, DSVT);
					goto menuHoaDon;
				}
				if(thaotac == 2) {
					inHoaDon(DSNV, DSVT);
					goto menuHoaDon;
				}
				if(thaotac == 3) {
					inHoaDonTrongKhoangTG(DSNV);
					goto menuHoaDon;
				}
				break;
			}
			default: {
				TextColor(7);
				ghiFileDSNV(DSNV);
				ghiFileDSVT(DSVT);
				GIAI_PHONG_BO_NHO(DSVT, DSNV);
				return;
			}
		}
	}
}

int main() {
	srand(time(NULL));
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Menu();
//	for(int i = 0; i <= 256; i++) {
//		TextColor(i);
//		cout << "______i: " << i << endl;
//	}
	
	return 0;
}


