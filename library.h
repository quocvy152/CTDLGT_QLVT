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

void KhungXuatLTC() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                 ";
	gotoxy(84, 5); cout << "      DANH SACH LOP TIN CHI      ";
	gotoxy(84, 6); cout << "                                 ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(69, i); cout << char(186);
		gotoxy(87, i); cout << char(186);
		gotoxy(104, i); cout << char(186); 
		gotoxy(113, i); cout << char(186); 
		gotoxy(126, i); cout << char(186);
		gotoxy(137, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(149, 9); cout << char(187);
	gotoxy(149, 11); cout << char(185);
	gotoxy(149, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(69, 11); cout << char(206);
	gotoxy(87, 11); cout << char(206);
	gotoxy(104, 11); cout << char(206); 
	gotoxy(113, 11); cout << char(206); 
	gotoxy(126, 11); cout << char(206);
	gotoxy(137, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);   gotoxy(59, 27); cout << char(202);
	gotoxy(69, 9); cout << char(203);	gotoxy(69, 27); cout << char(202);
	gotoxy(87, 9); cout << char(203);	gotoxy(87, 27); cout << char(202);
	gotoxy(104, 9); cout << char(203); 	gotoxy(104, 27); cout << char(202);
	gotoxy(113, 9); cout << char(203); 	gotoxy(113, 27); cout << char(202);
	gotoxy(126, 9); cout << char(203);	gotoxy(126, 27); cout << char(202);
	gotoxy(137, 9); cout << char(203);	gotoxy(137, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(62, 10); cout << "MA LOP";
	gotoxy(74, 10); cout << "MA MON HOC";
	gotoxy(92, 10); cout << "NIEN KHOA";
	gotoxy(107, 10); cout << "NHOM";
	gotoxy(117, 10); cout << "HOC KY";
	gotoxy(129, 10); cout << "SV MAX";
	gotoxy(141, 10); cout << "SV MIN";
	
	gotoxy(160, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(160, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(160, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(160, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
}

void KhungXuatDSLOP() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                 ";
	gotoxy(84, 5); cout << "          DANH SACH LOP          ";
	gotoxy(84, 6); cout << "                                 ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(128, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(148, 9); cout << char(187);
	gotoxy(148, 11); cout << char(185);
	gotoxy(148, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(128, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(128, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(128, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(68, 10); cout << "MA LOP";
	gotoxy(102, 10); cout << "TEN LOP";
	gotoxy(135, 10); cout << "NIEN KHOA";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungXuatDiemTBLop() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                     ";
	gotoxy(84, 5); cout << "    BANG DIEM TRUNG BINH KHOA HOC    ";
	gotoxy(84, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(135, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(148, 9); cout << char(187);
	gotoxy(148, 11); cout << char(185);
	gotoxy(148, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(135, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(135, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(135, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(96, 10); cout << "HO";
	gotoxy(123, 10); cout << "TEN";
	gotoxy(140, 10); cout << "DIEM";
	
	gotoxy(160, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(160, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(160, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(160, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
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
	
//	TextColor(224);
//	gotoxy(188, 15); cout << char(30);
//	gotoxy(186, 16); cout << char(17);
//	gotoxy(190, 16); cout << char(16);
//	gotoxy(188, 17); cout << char(31);
//	TextColor(7);
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

void KhungXuatDSDKLTC() {
	TextColor(241);
	gotoxy(90, 4); cout << "                                     ";
	gotoxy(90, 5); cout << "    DANH SACH DANG KY LOP TIN CHI    ";
	gotoxy(90, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 163; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(163, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(132, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(163, 9); cout << char(187);
	gotoxy(163, 11); cout << char(185);
	gotoxy(163, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(132, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(132, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(132, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(97, 10); cout << "HO";
	gotoxy(122, 10); cout << "TEN";
	gotoxy(137, 10); cout << "PHAI";
	gotoxy(153, 10); cout << "SDT";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungNhapDiem(string tenMH) {
	TextColor(241);
	gotoxy(90, 7); cout << "      BANG DIEM MON " << tenMH << "     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 60; i <= 154; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 13); cout << char(205);
		gotoxy(i, 31); cout << char(205);
	}
	
	for(int i = 12; i <= 30; i++) {
		// ve duong doc ben trai va phai
		gotoxy(60, i); cout << char(186);
		gotoxy(154, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(67, i); cout << char(186);
		gotoxy(86, i); cout << char(186);
		gotoxy(120, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(154, 11); cout << char(187);
	gotoxy(154, 13); cout << char(185);
	gotoxy(154, 31); cout << char(188);
	
	gotoxy(60, 11); cout << char(201);
	gotoxy(60, 13); cout << char(204);
	gotoxy(60, 31); cout << char(200);
	
	gotoxy(67, 13); cout << char(206);
	gotoxy(86, 13); cout << char(206);
	gotoxy(120, 13); cout << char(206);
	gotoxy(140, 13); cout << char(206);
	
	gotoxy(67, 11); cout << char(203);
	gotoxy(86, 11); cout << char(203);
	gotoxy(120, 11); cout << char(203);
	gotoxy(140, 11); cout << char(203);
	
	gotoxy(67, 31); cout << char(202);
	gotoxy(86, 31); cout << char(202);
	gotoxy(120, 31); cout << char(202);
	gotoxy(140, 31); cout << char(202);
	
	gotoxy(62, 12); cout << "STT";
	gotoxy(74, 12); cout << "MSSV";
	gotoxy(105, 12); cout << "HO";
	gotoxy(130, 12); cout << "TEN";
	gotoxy(145, 12); cout << "DIEM";
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
	
	gotoxy(160, 19); cout << "UP   : LEN";
	gotoxy(160, 20); cout << "LEFT : TRAI";
	gotoxy(160, 21); cout << "RIGHT: PHAI";
	gotoxy(160, 22); cout << "DOWN : XUONG";
	
	gotoxy(61, 32); TextColor(116); cout << "ESC: "; 
	gotoxy(68, 32); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungNhapTTLTC() {
	gotoxy(90, 12); cout << " NHAP THONG TIN LOP TIN CHI ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap nien khoa: "; 
	gotoxy(72, 15); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 16); cout << "Nhom          : "; 
	gotoxy(72, 17); cout << "Nhap ma MH    : "; 
}

void XoaKhungNhapLTC() {
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << "                                                                                     ";
	}
}

void KhungThemLTC(int maLTC) {
	gotoxy(85, 12); cout << " NHAP THONG TIN LOP TIN CHI MUON THEM ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 21); cout << char(205);
	}
	
	for(int i = 11; i <= 21; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 21); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 21); cout << char(200);
	
	gotoxy(72, 14); cout << "Ma LTC        : "; gotoxy(89, 14); cout << maLTC; 
	gotoxy(72, 15); cout << "Nhap ma MH    : "; 
	gotoxy(72, 16); cout << "Nhap nien khoa: "; 
	gotoxy(72, 17); cout << "Nham nhom     : "; 
	gotoxy(72, 18); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 19); cout << "Nhap SV MAX   : ";
	gotoxy(72, 20); cout << "Nhap SV MIN   : ";
}

void KhungCapNhatLTC(int maLTC) {
	gotoxy(85, 12); cout << " NHAP THONG TIN LOP TIN CHI CAP NHAT MOI ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 21); cout << char(205);
	}
	
	for(int i = 11; i <= 21; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 21); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 21); cout << char(200);
	
	gotoxy(72, 14); cout << "Ma LTC        : "; gotoxy(89, 14); cout << maLTC; 
	gotoxy(72, 15); cout << "Nhap ma MH    : "; 
	gotoxy(72, 16); cout << "Nhap nien khoa: "; 
	gotoxy(72, 17); cout << "Nham nhom     : "; 
	gotoxy(72, 18); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 19); cout << "Nhap SV MAX   : ";
	gotoxy(72, 20); cout << "Nhap SV MIN   : ";
}

void KhungNhapSV() {
	TextColor(241);
	gotoxy(87, 4); cout << "                                     ";
	gotoxy(87, 5); cout << "      NHAP DANH SACH SINH VIEN       ";
	gotoxy(87, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 164; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(164, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(133, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(164, 9); cout << char(187);
	gotoxy(164, 11); cout << char(185);
	gotoxy(164, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(133, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(133, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(133, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(97, 10); cout << "HO";
	gotoxy(122, 10); cout << "TEN";
	gotoxy(138, 10); cout << "PHAI";
	gotoxy(153, 10); cout << "SDT";
}

void KhungCapNhatSV() {
	gotoxy(87, 12); cout << " NHAP THONG TIN SINH VIEN CAP NHAT MOI ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 19); cout << char(205);
	}
	
	for(int i = 11; i <= 19; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 19); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 19); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ho  : ";
	gotoxy(72, 15); cout << "Nhap ten : ";
	gotoxy(72, 16); cout << "Nhap mssv: ";
	gotoxy(72, 17); cout << "Nhap SDT : ";
}

void KhungThemMH() {
	gotoxy(92, 12); cout << " NHAP THONG TIN MON HOC ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ma MH  : "; 
	gotoxy(72, 15); cout << "Nhap ten MH : "; 
	gotoxy(72, 16); cout << "So TCLT     : "; 
	gotoxy(72, 17); cout << "So TCTH     : "; 
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

void khungThongTinNV(string ho, string ten, string phai) {
	TextColor(241);
	gotoxy(60, 5);  cout << "                               ";  
	gotoxy(60, 6);  cout << "      THONG TIN NHAN VIEN      ";
	gotoxy(60, 7); cout << "     Ho va Ten: " << ho << " " << ten << "   ";
	gotoxy(60, 8); cout << "     Gioi tinh: " << phai << "            ";
	gotoxy(60, 9);  cout << "                               ";
	TextColor(7);
}

void KhungCapNhatMH() {
	gotoxy(89, 12); cout << " NHAP THONG TIN MON HOC CAP NHAT MOI ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ma MH  : "; 
	gotoxy(72, 15); cout << "Nhap ten MH : "; 
	gotoxy(72, 16); cout << "So TCLT     : "; 
	gotoxy(72, 17); cout << "So TCTH     : "; 
}

void KhungDKLTC() {
	gotoxy(93, 3); cout << " THONG TIN SINH VIEN ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 2); cout << char(205);
		gotoxy(i, 10); cout << char(205);
	}
	
	for(int i = 2; i <= 10; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 2); cout << char(187);
	gotoxy(140, 10); cout << char(188);
	
	gotoxy(70, 2); cout << char(201);
	gotoxy(70, 10); cout << char(200);
}

void khungXuatCTHD() {
	// ve cac duong ngang
	for(int i = 52; i <= 180; i++) {
		gotoxy(i, 18); cout << char(205);
		gotoxy(i, 20); cout << char(205);
		gotoxy(i, 37); cout << char(205);
	}
	
	for(int i = 18; i <= 37; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(180, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(58, i); cout << char(186);
		gotoxy(68, i); cout << char(186);
		gotoxy(80, i); cout << char(186);
		gotoxy(128, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		gotoxy(157, i); cout << char(186);
		gotoxy(168, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(180, 18); cout << char(187);
	gotoxy(180, 20); cout << char(185);
	gotoxy(180, 37); cout << char(188);
	
	gotoxy(52, 18); cout << char(201);
	gotoxy(52, 20); cout << char(204);
	gotoxy(52, 37); cout << char(200);
	
	gotoxy(58, 20); cout << char(206);
	gotoxy(68, 20); cout << char(206);
	gotoxy(80, 20); cout << char(206);
	gotoxy(128, 20); cout << char(206); 
	gotoxy(140, 20); cout << char(206); 
	gotoxy(149, 20); cout << char(206);
	gotoxy(157, 20); cout << char(206);
	gotoxy(168, 20); cout << char(186);
	
	gotoxy(58, 18); cout << char(203); gotoxy(58, 37); cout << char(202);
	gotoxy(68, 18); cout << char(203); gotoxy(68, 37); cout << char(202);
	gotoxy(80, 18); cout << char(203); gotoxy(80, 37); cout << char(202);
	gotoxy(128, 18); cout << char(203); gotoxy(128, 37); cout << char(202);
	gotoxy(140, 18); cout << char(203); gotoxy(140, 37); cout << char(202);
	gotoxy(149, 18); cout << char(203);	gotoxy(149, 37); cout << char(202);
	gotoxy(157, 18); cout << char(203);	gotoxy(157, 37); cout << char(202);
	gotoxy(168, 18); cout << char(203); gotoxy(168, 37); cout << char(202);
	
	gotoxy(54, 19); cout << "STT";
	gotoxy(61, 19); cout << "MA VAT TU";
	gotoxy(72, 19); cout << "MA MH";
	gotoxy(99, 19); cout << "TEN VAT TU";
	gotoxy(130, 19); cout << "SO LUONG";
	gotoxy(143, 19); cout << "DON GIA";
	gotoxy(150, 19); cout << "THUE VAT (%)";
	gotoxy(158, 19); cout << "THUE VAT (VND)";
	gotoxy(169, 19); cout << "SLOT TRONG";
}

// khung xuat lop tin chi khong thoa dieu kien
void KhungXuatLTC_KTDK() {
	TextColor(241);
	gotoxy(85, 9); cout << "                                                      ";
	gotoxy(85, 10); cout << "      DANH SACH LOP TIN CHI KHONG THOA DIEU KIEN      ";
	gotoxy(85, 11); cout << "                                                      ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 160; i++) {
		gotoxy(i, 13); cout << char(205);
		gotoxy(i, 15); cout << char(205);
		gotoxy(i, 32); cout << char(205);
	}
	
	for(int i = 13; i <= 32; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(160, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(72, i); cout << char(186);
		gotoxy(92, i); cout << char(186);
		gotoxy(108, i); cout << char(186);
		gotoxy(119, i); cout << char(186);
		gotoxy(129, i); cout << char(186);
		gotoxy(139, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(160, 13); cout << char(187);
	gotoxy(160, 15); cout << char(185);
	gotoxy(160, 32); cout << char(188);
	
	gotoxy(52, 13); cout << char(201);
	gotoxy(52, 15); cout << char(204);
	gotoxy(52, 32); cout << char(200);
	
	gotoxy(59, 15); cout << char(206);
	gotoxy(72, 15); cout << char(206);
	gotoxy(92, 15); cout << char(206);
	gotoxy(108, 15); cout << char(206); 
	gotoxy(119, 15); cout << char(206); 
	gotoxy(129, 15); cout << char(206);
	gotoxy(139, 15); cout << char(206);
	gotoxy(148, 15); cout << char(206);
	
	gotoxy(59, 13); cout << char(203); gotoxy(59, 32); cout << char(202);
	gotoxy(72, 13); cout << char(203); gotoxy(72, 32); cout << char(202);
	gotoxy(92, 13); cout << char(203); gotoxy(92, 32); cout << char(202);
	gotoxy(108, 13); cout << char(203); gotoxy(108, 32); cout << char(202);
	gotoxy(119, 13); cout << char(203); gotoxy(119, 32); cout << char(202);
	gotoxy(129, 13); cout << char(203);	gotoxy(129, 32); cout << char(202);
	gotoxy(139, 13); cout << char(203);	gotoxy(139, 32); cout << char(202);
	gotoxy(148, 13); cout << char(203); gotoxy(148, 32); cout << char(202);
	
	gotoxy(54, 14); cout << "STT";
	gotoxy(63, 14); cout << "MA LOP";
	gotoxy(80, 14); cout << "MA MH";
	gotoxy(96, 14); cout << "NIEN KHOA";
	gotoxy(112, 14); cout << "NHOM";
	gotoxy(122, 14); cout << "HOC KY";
	gotoxy(132, 14); cout << "SV MAX";
	gotoxy(141, 14); cout << "SV MIN";
	gotoxy(150, 14); cout << "SV DA DK";
	
	TextColor(116);
	gotoxy(53, 38); cout << "  BAN CO THAT SU MUON HUY CAC LOP KHONG DU DIEU KIEN?  ";
	gotoxy(53, 39); cout << "              Co: (Bam y), Khong: (Bam n)              ";
	TextColor(7);
	
	gotoxy(163, 21); TextColor(116); cout << "UP   :"; TextColor(12); cout << " LEN";
	gotoxy(163, 22); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(163, 23); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(163, 24); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(57, 34); TextColor(116); cout << "Bam C/c: "; 
	gotoxy(65, 34); TextColor(12); cout << "Tiep tuc viec xoa"; TextColor(7);
	gotoxy(57, 35); TextColor(116); cout << "ESC    : "; 
	gotoxy(65, 35); TextColor(12); cout << "Ket thuc viec xoa"; TextColor(7);
	
	gotoxy(168, 17); cout << char(30);
	gotoxy(166, 18); cout << char(17);
	gotoxy(170, 18); cout << char(16);
	gotoxy(168, 19); cout << char(31);
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

void XoaKhungHuongDan() {
	gotoxy(93, 9);  cout << "                                                                  ";
	gotoxy(93, 10); cout << "                                                                  ";
	gotoxy(93, 11); cout << "                                                                  ";
	gotoxy(93, 12); cout << "                                                                  ";
	gotoxy(93, 13); cout << "                                                                  ";
 
	gotoxy(98, 10); cout << "                                                                  ";
	gotoxy(96, 11); cout << "                                                                  ";
	gotoxy(100, 11); cout << "                                                                  ";
	gotoxy(98, 12); cout << "                                                                  ";
 
 	gotoxy(79, 16); cout << "                                                                  ";
	gotoxy(79, 17); cout << "                                                                  ";
	gotoxy(79, 18); cout << "                                                                  ";
	gotoxy(79, 19); cout << "                                                                  ";
	
	gotoxy(93, 21); cout << "                                                                  ";
	
	gotoxy(93, 22); cout << "                                                                  ";
	gotoxy(93, 23); cout << "                                                                  "; 
	gotoxy(93, 24); cout << "                                                                  "; 
	gotoxy(93, 25); cout << "                                                                  ";
}

void XoaKhungXuatLTC() {
	for(int i = 4; i <= 26; i++) {
		gotoxy(52, i); cout << "                                                                                                                        ";
	} 
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

void XoaKhungNhapDiem() {
	for(int i = 7; i <= 34; i++) {
		gotoxy(60, i); cout << "                                                                                                                         ";
	} 
}

void XoaKhungXuatLTC_KTDK() {
	for(int i = 9; i <= 34; i++) {
		gotoxy(52, i); cout << "                                                                                                                              ";
	} 
}