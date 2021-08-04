#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

using namespace std;

void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clreol( ) {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void clrscr() {
	system("cls");
}

void hienThiTrang(int trang, int tongtrang, int x, int y) {
	TextColor(6);	gotoxy(x, y); cout << " Trang:        ";
	gotoxy(x + 8, y); cout << trang << "/" << tongtrang;
	TextColor(7);
}

void khungGiaoDien() {
	TextColor(17);
	gotoxy(3, 1); cout << char(201);
	gotoxy(3, 48); cout << char(200);
	gotoxy(208, 1); cout << char(187);
	gotoxy(208, 48); cout << char(188);
		
	// ve cac duong ngang
	for(int i = 4; i <= 207; i++) {
		gotoxy(i, 1); cout << char(205);
		gotoxy(i, 48); cout << char(205);
		if(i <= 52)
			gotoxy(i, 20); cout << char(205);
	}
		
	// ve cac duong doc
	for(int i = 2; i <= 47; i++) {
		gotoxy(3, i); cout << char(186);
		gotoxy(52, i); cout << char(186);
		gotoxy(208, i); cout << char(186);
	}
	TextColor(7);
}

void xuatTenDeTai() {
	TextColor(14);
	gotoxy(87, 3);  cout << "  ___   __ __   ____  ____       _      __ __      __ __   ____  ______      ______  __ __ " << endl;
	gotoxy(87, 4); cout << " /   \ |   |  | /    ||    \\     | |    |  |  |    |  |  | /    ||      |    |      ||  |  |" << endl;
	gotoxy(87, 5); cout << "|     ||  |  ||  o  ||  _  |    | |    |  |  |    |  |  ||  o  ||      |    |      ||  |  |" << endl;
	gotoxy(87, 6); cout << "|  Q  ||  |  ||     ||  |  |    | |___ |  ~  |    |  |  ||     ||_|  |_|    |_|  |_||  |  |" << endl;
	gotoxy(87, 7); cout << "|     ||  :  ||  _  ||  |  |    |     ||___, |    |  :  ||  _  |  |  |        |  |  |  :  |" << endl;
	gotoxy(87, 8); cout << "|     ||     ||  |  ||  |  |    |     ||     |     \\   / |  |  |  |  |        |  |  |     |" << endl;
	gotoxy(87, 9); cout << " \\__,_| \\__,_||__|__||__|__|    |_____||____/       \\\_/  |__|__|  |__|        |__|   \\__,_|" << endl;
	TextColor(7);
}

void xoaTenDeTai() {
	gotoxy(87, 3); cout << "                                                                                             " << endl;
	gotoxy(87, 4); cout << "                                                                                             " << endl;
	gotoxy(87, 5); cout << "                                                                                             " << endl;
	gotoxy(87, 6); cout << "                                                                                             " << endl;
	gotoxy(87, 7); cout << "                                                                                             " << endl;
	gotoxy(87, 8); cout << "                                                                                             " << endl;
	gotoxy(87, 9); cout << "                                                                                             " << endl;
	TextColor(7);
}

void khungXuatDSVT() {
	TextColor(241);
	gotoxy(110, 4); cout << "                                     ";
	gotoxy(110, 5); cout << "           DANH SACH VAT TU          ";
	gotoxy(110, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 78; i <= 176; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(78, i); cout << char(186);
		gotoxy(176, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(85, i); cout << char(186);
		gotoxy(109, i); cout << char(186);
		gotoxy(154, i); cout << char(186);
		gotoxy(165, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(176, 9); cout << char(187);
	gotoxy(176, 11); cout << char(185);
	gotoxy(176, 27); cout << char(188);
	
	gotoxy(78, 9); cout << char(201);
	gotoxy(78, 11); cout << char(204);
	gotoxy(78, 27); cout << char(200);
	
	gotoxy(85, 11); cout << char(206);
	gotoxy(109, 11); cout << char(206);
	gotoxy(154, 11); cout << char(206);
	gotoxy(165, 11); cout << char(206);
	
	gotoxy(85, 9); cout << char(203);
	gotoxy(109, 9); cout << char(203);
	gotoxy(154, 9); cout << char(203);
	gotoxy(165, 9); cout << char(203);
	
	gotoxy(85, 27); cout << char(202);
	gotoxy(109, 27); cout << char(202);
	gotoxy(154, 27); cout << char(202);
	gotoxy(165, 27); cout << char(202);
	
	gotoxy(80, 10); cout << "STT";
	gotoxy(92, 10); cout << "MA VAT TU";
	gotoxy(127, 10); cout << "TEN VAT TU";
	gotoxy(158, 10); cout << "DVT";
	gotoxy(169, 10); cout << "SLT";
	
	gotoxy(183, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(183, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(183, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(183, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(80, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(87, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
}

void khungXuatDSDT() {
	TextColor(241);
	gotoxy(110, 4); cout << "                                                        ";
	gotoxy(110, 5); cout << "           TOP 10 VAT TU CO DOANH THU CAO NHAT          ";
	gotoxy(110, 6); cout << "                                                        ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 78; i <= 176; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(78, i); cout << char(186);
		gotoxy(176, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(85, i); cout << char(186);
		gotoxy(109, i); cout << char(186);
		gotoxy(154, i); cout << char(186);
		gotoxy(165, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(176, 9); cout << char(187);
	gotoxy(176, 11); cout << char(185);
	gotoxy(176, 27); cout << char(188);
	
	gotoxy(78, 9); cout << char(201);
	gotoxy(78, 11); cout << char(204);
	gotoxy(78, 27); cout << char(200);
	
	gotoxy(85, 11); cout << char(206);
	gotoxy(109, 11); cout << char(206);
	gotoxy(154, 11); cout << char(206);
	gotoxy(165, 11); cout << char(206);
	
	gotoxy(85, 9); cout << char(203);
	gotoxy(109, 9); cout << char(203);
	gotoxy(154, 9); cout << char(203);
	gotoxy(165, 9); cout << char(203);
	
	gotoxy(85, 27); cout << char(202);
	gotoxy(109, 27); cout << char(202);
	gotoxy(154, 27); cout << char(202);
	gotoxy(165, 27); cout << char(202);
	
	gotoxy(80, 10); cout << "STT";
	gotoxy(92, 10); cout << "MA VAT TU";
	gotoxy(127, 10); cout << "TEN VAT TU";
	gotoxy(158, 10); cout << "DVT";
	gotoxy(169, 10); cout << "SLT";
	
	gotoxy(183, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(183, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(183, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(183, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(80, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(87, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void xoaKhungDSDT() {
	for(int i = 4; i <= 29; i++) {
		gotoxy(59, i); cout << "                                                                                                                                        ";
	}
}

void khungXuatDSHD() {
	TextColor(241);
	gotoxy(110, 4); cout << "                                     ";
	gotoxy(110, 5); cout << "           DANH SACH HOA DON         ";
	gotoxy(110, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 78; i <= 176; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(78, i); cout << char(186);
		gotoxy(176, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(85, i); cout << char(186);
		gotoxy(109, i); cout << char(186);
		gotoxy(154, i); cout << char(186);
		gotoxy(165, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(176, 9); cout << char(187);
	gotoxy(176, 11); cout << char(185);
	gotoxy(176, 27); cout << char(188);
	
	gotoxy(78, 9); cout << char(201);
	gotoxy(78, 11); cout << char(204);
	gotoxy(78, 27); cout << char(200);
	
	gotoxy(85, 11); cout << char(206);
	gotoxy(109, 11); cout << char(206);
	gotoxy(154, 11); cout << char(206);
	gotoxy(165, 11); cout << char(206);
	
	gotoxy(85, 9); cout << char(203);
	gotoxy(109, 9); cout << char(203);
	gotoxy(154, 9); cout << char(203);
	gotoxy(165, 9); cout << char(203);
	
	gotoxy(85, 27); cout << char(202);
	gotoxy(109, 27); cout << char(202);
	gotoxy(154, 27); cout << char(202);
	gotoxy(165, 27); cout << char(202);
	
	gotoxy(80, 10); cout << "STT";
	gotoxy(92, 10); cout << "SO HOA DON";
	gotoxy(127, 10); cout << "NGAY LAP";
	gotoxy(158, 10); cout << "LOAI";
	
	gotoxy(183, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(183, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(183, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(183, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(80, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(87, 28); TextColor(12); cout << "Thoat che do xem hoa don va nhap so hoa don can xem"; TextColor(7);
}

void khungNhapXemHD() {
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 16); cout << char(205);
	}
	
	for(int i = 11; i <= 16; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 16); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 16); cout << char(200);
	
}

void xoaKhungNhapXemHD() {
	for(int i = 11; i <= 16; i++) {
		gotoxy(70, i);  cout << "                                                                                                                 ";
	} 
}

void khungNhapXemTGHD() {
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 16); cout << char(205);
	}
	
	for(int i = 11; i <= 16; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 16); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 16); cout << char(200);
	
	gotoxy(72, 12); cout << "**NGAY THANG NAM BAT DAU"; 
	gotoxy(72, 13); cout << "Ngay : "; 
	gotoxy(72, 14); cout << "Thang: ";
	gotoxy(72, 15); cout << "Nam  : "; 
	
	gotoxy(104, 12); cout << "**NGAY THANG NAM KET THUC"; 
	gotoxy(104, 13); cout << "Ngay : "; 
	gotoxy(104, 14); cout << "Thang: ";
	gotoxy(104, 15); cout << "Nam  : "; 
}

void xoaKhungNhapXemTGHD(){
	for(int i = 10; i <= 17; i++) {
		gotoxy(70, i); cout << "                                                                                                                                 ";
	}
}

void khungNhapHoaDon() {
	TextColor(31);
	gotoxy(81, 4); cout << " ** LAP THONG TIN HOA DON ** ";
	TextColor(7);
	
	for(int i = 60; i <= 130; i++) {
		gotoxy(i, 3); cout << char(205);
		gotoxy(i, 12); cout << char(205);
	}
	
	
	for(int i = 3; i <= 12; i++) {
		// ve duong doc ben trai va phai
		gotoxy(60, i); cout << char(186);
		gotoxy(130, i); cout << char(186);
	} 
	
	gotoxy(130, 3); cout << char(187);
	gotoxy(130, 12); cout << char(188);
	
	gotoxy(60, 3); cout << char(201);
	gotoxy(60, 12); cout << char(200);
	
	gotoxy(63, 8);  cout << "Ngay         : "; 
	gotoxy(63, 9);  cout << "Thang        : ";
	gotoxy(63, 10); cout << "Nam          : "; 
}

void xoaKhungNhapHD() {
	for(int i = 3; i < 13; i++) {
		gotoxy(60, i); cout << "                                                                                                                                 ";
	}
}

void khungNhapCTHD() {
	TextColor(31);
	gotoxy(77, 19); cout << " ** THONG TIN CHI TIET HOA DON ** ";
	TextColor(7);
	
	for(int i = 60; i <= 130; i++) {
		gotoxy(i, 18); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	
	for(int i = 18; i <= 27; i++) {
		// ve duong doc ben trai va phai
		gotoxy(60, i); cout << char(186);
		gotoxy(130, i); cout << char(186);
	} 
	
	gotoxy(130, 18); cout << char(187);
	gotoxy(130, 27); cout << char(188);
	
	gotoxy(60, 18); cout << char(201);
	gotoxy(60, 27); cout << char(200);
	
	gotoxy(63, 23);  cout << "Ngay          : "; 
	gotoxy(63, 24);  cout << "Thang         : ";
	gotoxy(63, 25);  cout << "Nam           : ";
	
	TextColor(124);
	gotoxy(60, 30);  cout << " ESC   : Thoat Lap Hoa Don ";
	gotoxy(93, 30);  cout << " DELETE: Xoa Vat Tu Da Nhap ";
	TextColor(7);
}

void xoaKhungNhapCTHD(){
	for(int i = 17; i < 30; i++) {
		gotoxy(60, i); cout << "                                                                                                                                 ";
	}
}

void xoaKhungNhapNgay() {
	for(int i = 10; i <= 17; i++) {
		gotoxy(70, i); cout << "                                                                                                                                 ";
	}
}

void khungNhapThemVT() {
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 16); cout << char(205);
	}
	
	for(int i = 11; i <= 16; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 16); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 16); cout << char(200);
}

void xoaKhungThemVT(){
	for(int i = 10; i <= 17; i++) {
		gotoxy(69, i); cout << "                                                                                                                              ";
	}
}

void khungCapNhatNV() {
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 20); cout << char(205);
		gotoxy(i, 25); cout << char(205);
	}
	
	for(int i = 20; i <= 25; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 20); cout << char(187);
	gotoxy(140, 25); cout << char(188);
	
	gotoxy(70, 20); cout << char(201);
	gotoxy(70, 25); cout << char(200);
}

void xoaKhungCapNhatNV(){
	for(int i = 19; i <= 26; i++) {
		gotoxy(69, i); cout << "                                                                                                                              ";
	}
}

void khungNhapXoa() {
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 16); cout << char(205);
	}
	
	for(int i = 11; i <= 16; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 16); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 16); cout << char(200);
}

void xoaKhungNhapXoa(){
	for(int i = 10; i < 17; i++) {
		gotoxy(69, i); cout << "                                                                                                                     ";
	}
}

void khungThongTinNV(string ho, string ten, string phai) {
	gotoxy(61, 5);  cout << "        THONG TIN NHAN VIEN           ";
	gotoxy(62, 6); cout << "Ho va Ten: " << ho << " " << ten;
	gotoxy(62, 7); cout << "Gioi tinh: " << phai;
	
	TextColor(255);
	for(int i = 60; i <= 100; i++) {
		gotoxy(i, 4); cout << "+";
		gotoxy(i, 8); cout << "+";
	}
	for(int i = 4; i <= 8; i++) {
		gotoxy(60, i); cout << "+";
		gotoxy(100, i); cout << "+";
	}
	TextColor(7);
}

void khungThongTinHD() {
	gotoxy(61, 10); cout << "        THONG TIN HOA DON           ";
	
	TextColor(255);
	for(int i = 60; i <= 100; i++) {
		gotoxy(i, 9); cout << "+";
		gotoxy(i, 14); cout << "+";
	}
	for(int i = 10; i <= 14; i++) {
		gotoxy(60, i); cout << "+";
		gotoxy(100, i); cout << "+";
	}
	TextColor(7);
}

void khungXuatCTHD() {
	TextColor(241);
	gotoxy(110, 12); cout << "                                     ";
	gotoxy(110, 13); cout << "           CHI TIET HOA DON          ";
	gotoxy(110, 14); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 54; i <= 206; i++) {
		gotoxy(i, 16); cout << char(205);
		gotoxy(i, 18); cout << char(205);
		gotoxy(i, 34); cout << char(205);
	}
	
	for(int i = 16; i <= 33; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(54, i); cout << char(186);
		gotoxy(206, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(61, i); cout << char(186);
		gotoxy(85, i); cout << char(186);
		gotoxy(130, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		gotoxy(168, i); cout << char(186);
		gotoxy(187, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(206, 16); cout << char(187);
	gotoxy(206, 18); cout << char(185);
	gotoxy(206, 34); cout << char(188);

	gotoxy(54, 16); cout << char(201);
	gotoxy(54, 18); cout << char(204);
	gotoxy(54, 34); cout << char(200);
	
	gotoxy(61, 18); cout << char(206);
	gotoxy(85, 18); cout << char(206);
	gotoxy(130, 18); cout << char(206);
	gotoxy(149, 18); cout << char(206);
	gotoxy(168, 18); cout << char(206);
	gotoxy(187, 18); cout << char(206);
	
	gotoxy(61, 16); cout << char(203);
	gotoxy(85, 16); cout << char(203);
	gotoxy(130, 16); cout << char(203);
	gotoxy(149, 16); cout << char(203);
	gotoxy(168, 16); cout << char(203);
	gotoxy(187, 16); cout << char(203);
	
	gotoxy(61, 34); cout << char(202);
	gotoxy(85, 34); cout << char(202);
	gotoxy(130, 34); cout << char(202);
	gotoxy(149, 34); cout << char(202);
	gotoxy(168, 34); cout << char(202);
	gotoxy(187, 34); cout << char(202);
	
	gotoxy(56, 17); cout << "STT";
	gotoxy(68, 17); cout << "MA VAT TU";
	gotoxy(103, 17); cout << "TEN VAT TU";
	gotoxy(134, 17); cout << "SO LUONG";
	gotoxy(153, 17); cout << "DON GIA";
	gotoxy(172, 17); cout << "THUE (%)";
	gotoxy(191, 17); cout << "THANH TIEN";
	
	gotoxy(169, 39); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(169, 40); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(169, 41); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(169, 42); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(67, 39); TextColor(116); cout << "ESC: "; 
	gotoxy(74, 39); TextColor(12); cout << "Thoat xem chi tiet hoa don"; TextColor(7);
}

void xoaKhungXuatCTHD(){
	for(int i = 15; i <= 39; i++) {
		gotoxy(54, i); cout << "                                                                                                                                                         ";
	}
}

void khungXuatHoaDon() {
	TextColor(241);
	gotoxy(110, 12); cout << "                                     ";
	gotoxy(110, 13); cout << "           DANH SACH HOA DON         ";
	gotoxy(110, 14); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 54; i <= 206; i++) {
		gotoxy(i, 16); cout << char(205);
		gotoxy(i, 18); cout << char(205);
		gotoxy(i, 34); cout << char(205);
	}
	
	for(int i = 16; i <= 33; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(54, i); cout << char(186);
		gotoxy(206, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(61, i); cout << char(186);
		gotoxy(85, i); cout << char(186);
		gotoxy(130, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		gotoxy(168, i); cout << char(186);
		gotoxy(187, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(206, 16); cout << char(187);
	gotoxy(206, 18); cout << char(185);
	gotoxy(206, 34); cout << char(188);

	gotoxy(54, 16); cout << char(201);
	gotoxy(54, 18); cout << char(204);
	gotoxy(54, 34); cout << char(200);
	
	gotoxy(61, 18); cout << char(206);
	gotoxy(85, 18); cout << char(206);
	gotoxy(130, 18); cout << char(206);
	gotoxy(149, 18); cout << char(206);
	gotoxy(168, 18); cout << char(206);
	gotoxy(187, 18); cout << char(206);
	
	gotoxy(61, 16); cout << char(203);
	gotoxy(85, 16); cout << char(203);
	gotoxy(130, 16); cout << char(203);
	gotoxy(149, 16); cout << char(203);
	gotoxy(168, 16); cout << char(203);
	gotoxy(187, 16); cout << char(203);
	
	gotoxy(61, 34); cout << char(202);
	gotoxy(85, 34); cout << char(202);
	gotoxy(130, 34); cout << char(202);
	gotoxy(149, 34); cout << char(202);
	gotoxy(168, 34); cout << char(202);
	gotoxy(187, 34); cout << char(202);
	
	gotoxy(56, 17); cout << "STT";
	gotoxy(68, 17); cout << "SO HOA DON";
	gotoxy(103, 17); cout << "NHAN VIEN LAP HOA DON";
	gotoxy(134, 17); cout << "NGAY LAP";
	gotoxy(153, 17); cout << "LOAI";
	gotoxy(172, 17); cout << "TRI GIA";
	//gotoxy(191, 17); cout << "THANH TIEN";
	
	gotoxy(169, 39); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(169, 40); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(169, 41); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(169, 42); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(67, 39); TextColor(116); cout << "ESC: "; 
	gotoxy(74, 39); TextColor(12); cout << "Thoat xem chi tiet hoa don"; TextColor(7);
}

void xoaKhungXuatHoaDon() {
	for(int i = 5; i <= 43; i++) {
		gotoxy(54, i); cout << "                                                                                                                                                         ";
	}
}

void xoaTrangXuatCTHD(){
	for(int i = 5; i <= 44; i++) {
		gotoxy(54, i); cout << "                                                                                                                                                         ";
	}
}

void khungHuongDan() {
	TextColor(116);
 	gotoxy(8, 3); cout << "                                         ";
	gotoxy(8, 4); cout << "  DUNG 4 PHIM MUI TEN DE DI CHUYEN MENU  ";
	gotoxy(8, 5); cout << "           BAM ENTER DE CHON             ";
	gotoxy(8, 6); cout << "                                         ";
	TextColor(7);
	
	TextColor(225); gotoxy(23, 8); cout << "ENTER:"; TextColor(7); gotoxy(30, 8); cout << "CHON ";
	TextColor(225); gotoxy(23, 9); cout << "UP   :"; TextColor(7); gotoxy(30, 9); cout << "LEN  ";
	TextColor(225); gotoxy(23, 10); cout << "LEFT :"; TextColor(7); gotoxy(30, 10); cout << "TRAI ";
	TextColor(225); gotoxy(23, 11); cout << "RIGHT:"; TextColor(7); gotoxy(30, 11); cout << "PHAI ";
	TextColor(225); gotoxy(23, 12); cout << "DOWN :"; TextColor(7); gotoxy(30, 12); cout << "XUONG";
}

void khungXuatDSNV() {
	TextColor(241);
	gotoxy(114, 4); cout << "                                     ";
	gotoxy(114, 5); cout << "         DANH SACH NHAN VIEN         ";
	gotoxy(114, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 84; i <= 177; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(84, i); cout << char(186);
		gotoxy(177, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(91, i); cout << char(186);
		gotoxy(115, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
		gotoxy(165, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	
	gotoxy(84, 9); cout << char(201);
	gotoxy(84, 11); cout << char(204);
	gotoxy(84, 27); cout << char(200);
	
	gotoxy(91, 11); cout << char(206);
	gotoxy(115, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	gotoxy(165, 11); cout << char(206);
	gotoxy(177, 11); cout << char(185);
	
	gotoxy(91, 9); cout << char(203);
	gotoxy(115, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	gotoxy(165, 9); cout << char(203);
	gotoxy(177, 9); cout << char(187);
	
	gotoxy(91, 27); cout << char(202);
	gotoxy(115, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	gotoxy(165, 27); cout << char(202);
	gotoxy(177, 27); cout << char(188);
	
	gotoxy(86, 10); cout << "STT";
	gotoxy(96, 10); cout << "MA NHAN VIEN";
	gotoxy(129, 10); cout << "HO";
	gotoxy(154, 10); cout << "TEN";
	gotoxy(170, 10); cout << "PHAI";
	
	gotoxy(190, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(190, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(190, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(190, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(85, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(92, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void xoaKhungDSVT() {
	for(int i = 4; i <= 29; i++) {
		gotoxy(75, i); cout << "                                                                                                                         ";
	}
}

void xoaNhapNgayBatDau() {
	gotoxy(80, 13); cout << "    ";
	gotoxy(80, 14); cout << "    ";
	gotoxy(80, 15); cout << "    ";
}

void xoaNhapNgayHoaDon() {
	gotoxy(86, 16); cout << "    ";
	gotoxy(86, 17); cout << "    ";
	gotoxy(86, 18); cout << "    ";
}

void xoaNhapNgayKetThuc() {
	gotoxy(112, 13); cout << "    "; 
	gotoxy(112, 14); cout << "    ";
	gotoxy(112, 15); cout << "    ";
}


void xoaMenu() {
	for (int i = 0; i < 7; i++)
	{
		gotoxy(10, 25 + i); cout << "                               ";
	}
}

void xoaKhungDSNV() {
	for(int i = 4; i <= 29; i++) {
		gotoxy(83, i); cout << "                                                                                                                          ";
	} 
}

void xoaKhungDSHD() {
	for(int i = 4; i <= 29; i++) {
		gotoxy(78, i); cout << "                                                                                                                          ";
	} 
}

void khungXacNhan(){
	TextColor(238);
	for(int i = 105; i <= 155; i++) {
		gotoxy(i, 35); cout << char(205);
		gotoxy(i, 42); cout << char(205);
	}
	
	for(int i = 35; i <= 42; i++) {
		// ve duong doc ben trai va phai
		gotoxy(105, i); cout << char(186);
		gotoxy(155, i); cout << char(186);
	} 
	
	gotoxy(155, 35); cout << char(187);
	gotoxy(155, 42); cout << char(188);
	
	gotoxy(105, 35); cout << char(201);
	gotoxy(105, 42); cout << char(200);
	TextColor(7);
}

void xoaKhungXacNhan(){
	for(int i = 34; i < 43; i++) {
		gotoxy(104, i); cout << "                                                                                                  ";
	}	
}

void xoaKhungThongTinCTHD(){
	for(int i = 5; i <= 32; i++) {
		gotoxy(133, i); cout << "                                                                          ";
	}
}

void khungXoaCTHD(){
	TextColor(238);
	for(int i = 80; i <= 120; i++){
		gotoxy(i, 33); cout << "+";
		gotoxy(i, 37); cout << "+";
	}
	for(int i = 33; i <= 37; i++){
		gotoxy(80, i); cout << "+";
		gotoxy(120, i); cout << "+";
	}
	TextColor(7);
	TextColor(228);
	gotoxy(81, 37); cout << "ESC: Thoat";
	gotoxy(103, 37); cout << "ENTER: Xac Nhan";
	TextColor(7);
}

void xoaKhungXoaCTHD(){
	for(int i = 33; i <= 37; i++){
		gotoxy(80, i); cout << "                                               ";
	}
}
