// TravelPacking.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Chuong trinh sap xep hanh ly
// Chuc nang co ban: liet ke, them, sua, xoa, tim kiem do dung
// Chuc nang chinh: lua chon va goi y cac kieu sap xep phu hop dua tren giai thuat Di truyen
// Co the luu tru du lieu trong file item.txt -> Load len mang struct de dung
// 

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>

#define MAX_ITEM 1000

#define SWAP(type,x,y) do{type tmp = x; x = y; y = tmp;} while(0)

using namespace std;


//==================== // MỘT SỐ HÀM PHỤ TRỢ TRONG MÀN HÌNH CONSOLE //=============================

void ClearScreen()                 // Ham don sach man hinh 
{
    system("cls");
}

void gotoXY(SHORT posX, SHORT posY)							// hàm dịch con trỏ hiện tại đến điểm có tọa độ(x, y) 
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;
    SetConsoleCursorPosition(hStdout, Position);
}


//===========================// PHẦN CHÍNH CỦA CHƯƠNG TRÌNH //=====================================


string path = "item.txt";
int so_luong_item_hientai; //Bien quyet dinh so luong
static int n = 500;  //So luong ca the trong quan the
int** nghiem = new int* [n];//Mang luu cac ca the
float* thichNghi = new float[n];//Mang luu do thich nghi cua tung ca the

float canNang; // Dung luong cua balo

struct item {
    string name; // ten goi
    float price; // gia thanh
    float weight; // can nang (g)
    float height; // chieu dai (cm)
    float width; // chieu ngang (cm)
    // Contructor: luu tru thong tin truc tiep
    item() {
        this->name = "Unknown";
        this->price = 0;
        this->weight = 0;
        this->height = 0;
        this->width = 0;
    }
    item(string name, float price, float weight, float height, float width) {
        this->name = name;
        this->price = price;
        this->weight = weight;
        this->height = height;
        this->width = width;
    }
};

item* it = new item[MAX_ITEM]; //Mang luu tru items


int length_of_array_item(item it[]) {
    unsigned int x = sizeof(*it) / sizeof(it[0]);
    return x;
}

#pragma region Luu_tru_du_lieu

void du_lieu_mau(item it[]) // Hàm dùng để thêm dữ liệu cho việc test
{
    it[0] = item("Dark Nhan Tam", 60000, 260, 20.5, 14.5);
    it[1] = item("Ao thun mac trong", 100000, 120, 80, 50);
    it[2] = item("Ao khoac da", 100000, 600, 100, 90);
    it[3] = item("Ao mua nilong", 100000, 80, 80, 50);
    it[4] = item("Tat trong nha", 100000, 80, 80, 50);
    it[5] = item("So ghi chep a5", 100000, 240, 80, 50);
    it[6] = item("So ve phac hoa a4", 100000, 350, 80, 500);
    it[7] = item("Day nit Guchi", 15000000, 800, 80, 50);
    it[8] = item("Dong ho Rolex", 3000000000, 550, 10, 20);
    it[9] = item("Quan di boi", 80000, 100, 50, 70);
    it[10] = item("Quan jean", 400000, 420, 140, 80);
    it[11] = item("Dep lao", 100000, 240, 30, 15);
    it[12] = item("Ao khoac di bien", 300000, 180, 80, 50);
    it[13] = item("Vot bat hai san", 300000, 360, 80, 50);
    it[14] = item("May anh", 1000000, 420, 80, 50);
    so_luong_item_hientai = 15;
}

void sample_item(item it[]) // Lay du lieu mau tu file item.txt dua vao struct
{
    int line = 1, index = 0, item_index = 0;
    string Text;
    string item_value[5];
    ifstream MyReadFile(path);

    while (getline(MyReadFile, Text)) {
        item_value[index++] = Text;

        if (line != 1 && line % 5 == 0) {
            it[item_index].name = item_value[0];
            it[item_index].price = stof(item_value[1]);
            it[item_index].weight = stof(item_value[2]);
            it[item_index].height = stof(item_value[3]);
            it[item_index].width = stof(item_value[4]);
            item_index++;
            index = 0;
        }
        line++;
    }

    so_luong_item_hientai = item_index;
}

void LuuThongTinMoi(item it[]) // Luu thong tin da co thay doi vao file
{
    ofstream MyFile(path);

    for (int i = 0; i < so_luong_item_hientai; i++) {
        MyFile << it[i].name << endl;
        MyFile << it[i].price << endl;
        MyFile << it[i].weight << endl;
        MyFile << it[i].height << endl;
        MyFile << it[i].width << endl;
    }

    MyFile.close();
}

#pragma endregion

#pragma region Tuong_tac_du_lieu
void InThongTin(item it) {
    cout << "\n\t\t-----------------------------------------";
    cout << "\n\t\t|Ten vat dung: " << it.name;
    cout << "\n\t\t|   - Gia thanh: " << it.price ;
    cout << "\n\t\t|   - Can nang: " << it.weight ;
    cout << "\n\t\t|   - Chieu dai: " << it.height;
    cout << "\n\t\t|   - Chieu rong: " << it.width << endl;
}

void themItem(item it[]) // Them du lieu hoan toan moi
{
    int n = so_luong_item_hientai;
    cout << "\n\t\tNhap them san pham: " << endl;
    rewind(stdin);
    cout << "\n\t\tNhap ten san pham can them :";
    getline(cin, it[n].name);
    cout << "\n\t\tNhap gia thanh: ";
    cin >> it[n].price;
    cout << "\n\t\tNhap can nang: ";
    cin >> it[n].weight;
    cout << "\n\t\tNhap chieu cao: ";
    cin >> it[n].height;
    cout << "\n\t\tNhap chieu rong: ";
    cin >> it[n].width;
    so_luong_item_hientai++;
}

void NhapThongTinMoi(string& newname, float& newprice, float& newweight, float& newheight, float& newwidth)
{
    rewind(stdin);
    cout << "\n\t\tNhap ten vat dung moi: ";
    getline(cin, newname);
    cout << "\n\t\tNhap gia thanh moi: ";
    cin >> newprice;
    cout << "\n\t\tNhap can nang moi: ";
    cin >> newweight;
    cout << "\n\t\tNhap chieu cao moi: ";
    cin >> newheight;
    cout << "\n\t\tNhap chieu rong moi: ";
    cin >> newwidth;
}

void suaItem(item it[]) // Tim kiem vat dung theo ten, sau do thuc hien chinh sua
{
    string x, newname;
    float newprice, newweight, newheight, newwidth;
    int tmp = 0;
    int n = so_luong_item_hientai;
    rewind(stdin);
    cout << "\n\t\tNhap ten san pham muon sua: ";
    getline(cin, x);
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (it[i].name == x)
        {
            cout << "\n\t\tThong tin san pham: ";
            InThongTin(it[i]);
            cout << "\n\t\tNhap thong tin chinh sua: " << endl;
            NhapThongTinMoi(newname, newprice, newweight, newheight, newwidth); //goi ham nhap 1 san pham de nhap lai san pham
            it[i].name = newname;
            it[i].price = newprice;
            it[i].weight = newweight;
            it[i].height = newheight;
            it[i].width = newwidth;
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\n\t\tKhong tim thay san pham trong danh sach!" << endl;
    }
}

void xoa(item it[], int n, int tmp)
{
    for (int i = tmp; i < n; i++)
    {
        it[i] = it[i + 1];
    }
}

void xoaItem(item it[]) // Tim kiem vat dung, sau do xoa vat dung
{
    string x;
    int n = so_luong_item_hientai;
    cout << "\n\t\tNhap ten san pham can xoa: ";
    rewind(stdin);
    getline(cin, x);
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (it[i].name == x)
        {
            found = 1;
            xoa(it, n, i);
        }
    }
    if (found == 0)
    {
        cout << "\n\t\t Vat dung khong co !";
    }
    else
    {
        cout << "\n\t\t Da xoa vat dung co ten la: " << x;
        so_luong_item_hientai--;
    }
}

void LietKeItem(item it[], int size) {
    for (int i = 0; i < size; i++) {
        InThongTin(it[i]);
    }
}

bool TimKiemTen(item it[], int n, string x)
{
    bool tmp = false;
    for (int i = 0; i < n; i++)
    {
        if (it[i].name.find(x) != string::npos) // Ten co chua chuoi x
        {
            InThongTin(it[i]);
            tmp = true;
        }
    }
    return tmp;
}

bool TimKiemGia(item it[], int n, float x)
{
    bool tmp = false;
    for (int i = 0; i < n; i++)
    {
        if (it[i].price == x)
        {
            InThongTin(it[i]);
            tmp = true;
        }
    }
    return tmp;
}

bool TimKiemCanNang(item it[], int n, float x)
{
    bool tmp = false;
    for (int i = 0; i < n; i++)
    {
        if (it[i].weight == x)

        {
            InThongTin(it[i]);
            tmp = true;
        }
    }
    return tmp;
}

bool TimKiemChieuDai(item it[], int n, float x)
{
    bool tmp = false;
    for (int i = 0; i < n; i++)
    {
        if (it[i].height == x)
        {
            InThongTin(it[i]);
            tmp = true;
        }
    }
    return tmp;
}

bool TimKiemChieuRong(item it[], int n, float x)
{
    bool tmp = false;
    for (int i = 0; i < n; i++)
    {
        if (it[i].width == x)
        {
            InThongTin(it[i]);
            tmp = true;
        }
    }
    return tmp;
}

#pragma endregion

#pragma region Sap_xep

void sapXepGia(item it[])
{
    for (int i = 0; i < so_luong_item_hientai - 1; i++) {
        for (int j = i + 1; j < so_luong_item_hientai; j++) {
            if (it[i].price < it[j].price)
                SWAP(item, it[i], it[j]);
        }
    }
}

void sapXepCanNang(item it[])
{
    for (int i = 0; i < so_luong_item_hientai - 1; i++) {
        for (int j = i + 1; j < so_luong_item_hientai; j++) {

            if (it[i].weight < it[j].weight)
                SWAP(item, it[i], it[j]);
        }
    }
}

void sapXepTen(item it[])
{
    for (int i = 0; i < so_luong_item_hientai - 1; i++) {
        for (int j = i + 1; j < so_luong_item_hientai; j++) {
            if (it[i].name.compare(it[j].name) > 0)
                SWAP(item, it[i], it[j]);
        }
    }
}

#pragma endregion

#pragma region Giai_thuat_di_truyen

void copy(float a[], float b[], int n) //Copy mang
{
    for (int i = 0; i < n; i++)
        b[i] = a[i];
}

void sort(float a[], int n) //Sap xep do thich nghi giam dan
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 1; j < n; j++)
        {
            if (a[j] > a[i])
            {
                float t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
}

void CaThe(int a[]) //Tao ca the
{
    for (int i = 0; i < so_luong_item_hientai; i++)
        a[i] = rand() % 2;
}

void KhoiTao() //Khoi tao quan the
{
    for (int i = 0; i < n; i++)
    {
        nghiem[i] = new int[so_luong_item_hientai];
        CaThe(nghiem[i]);
    }
}

void DanhGia(int nghiemDeCu[], float& best) //Danh gia do thich nghi va tim ca the toi uu
{
    for (int i = 0; i < n; i++)
    {
        thichNghi[i] = 0;
        float wei = 0;
        float val = 0;
        for (int j = 0; j < so_luong_item_hientai; j++)
        {
            wei += it[j].weight * nghiem[i][j];
            val += it[j].price * nghiem[i][j];
        }
        if (wei > canNang)
            thichNghi[i] = 0;
        else
            thichNghi[i] = val;
    }
    float* temp = new float[n];
    copy(thichNghi, temp, n);
    sort(temp, n);
    if (temp[0] > best)
    {
        best = temp[0];
        for (int i = 0; i < n; i++)
            if (thichNghi[i] == best)
            {
                for (int j = 0; j < so_luong_item_hientai; j++)
                    nghiemDeCu[j] = nghiem[i][j];
                break;
            }
    }
}

void ChonLoc() 
{
    float* temp = new float[n];
    copy(thichNghi, temp, n);
    sort(temp, n);
    float nguong = temp[n * 80 / 100];
    for (int i = 0; i < n; i++)
    {
        if (thichNghi[i] <= nguong)
        {
            CaThe(nghiem[i]);
        }
    }
}

void LaiGhep() 
{
    for (int i = 0; i < 50; i++)
    {
        int cha = rand() % n;
        int me = rand() % n;
        for (int j = 0; j < so_luong_item_hientai; j++)
            if (rand() % 2 == 1) {
                int temp = nghiem[cha][j];
                nghiem[cha][j] = nghiem[me][j];
                nghiem[me][j] = temp;
            }
    }
}

void DotBien()
{
    for (int i = 0; i < 5; i++)
    {
        int index = rand() % n;
        int bit = rand() % so_luong_item_hientai;
        if (nghiem[index][bit] == 0)
            nghiem[index][bit] = 1;
        else
            nghiem[index][bit] = 0;
    }
}

void GeneticFunction() 
{
    KhoiTao();
    int* nghiemDeCu = new int[so_luong_item_hientai];
    float best = 0;
    int gen = 900;
    for (int i = 1; i <= gen; i++)
    {
        DanhGia(nghiemDeCu, best);
        ChonLoc();
        LaiGhep();
        DotBien();
    }
    if (best != 0)
    {
        float weight = 0;
        cout << "\n\t\tGoi y: Cac vat dung nen mang theo: " << endl;
        for (int j = 0; j < so_luong_item_hientai; j++)
            if (nghiemDeCu[j] == 1)
            {
                cout <<"\n\t\t" << j + 1 << ". " << it[j].name <<
                    ": gia( " << it[j].price << " ), can nang( " << it[j].weight << " )" << endl;
                weight += it[j].weight;
            }
        cout << "\n\t\tTong can nang: " << weight << endl;
        cout << "\n\t\tTong gia tri: " << best << endl;
    }
    else {
        cout << "\n\t\tXin loi, khong tim duoc goi y phu hop!!! Co le balo cua ban qua nho!!" << endl;
    }
    delete[] nghiemDeCu;
}

#pragma endregion

void NhapKhongGian(float& canNang) // Input cua nguoi dung
{
    cout << "\n\t\tNhap can nang ban co the mang theo: ";
    cin >> canNang;
}


//=====================================// PHAN CODE CHO MENU DONG //===================================================


int x = 40, y = 9;
int w = 30, h = 2, t_color = 11, b_color = 1, b_color_sang = 75;

void SetColor(WORD color)                                  //Hàm đặt màu cho chữ 
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void textcolor(int x)       //Hàm đặt màu nền
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

void ShowCur(bool CursorVisibility)           // Hàm làm ẩn con trỏ chuột 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

void thanh_sang(int xp, int yp, int w, int h, int b_color, string nd)    //Hàm để tạo thanh sáng cho menu
{
    textcolor(b_color);
    for (int iy = yp + 1; iy <= yp + h - 1; iy++)
    {
        for (int ix = xp + 1; ix <= xp + w - 1; ix++)
        {
            gotoXY(ix, iy); cout << " ";
        }
    }
    SetColor(7);
    gotoXY(xp + 1, yp + 1);
    cout << nd;
}

void box(int x, int y, int w, int h, int t_color, int b_color, string nd)    //Hàm tạo một ô của menu động 
{
    textcolor(b_color);
    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        for (int ix = x + 1; ix <= x + w - 1; ix++)
        {
            gotoXY(ix, iy); cout << " ";
        }
    }
    SetColor(7);
    gotoXY(x + 1, y + 1);
    cout << nd;
    textcolor(1);                //Vẽ viền cho menu
    SetColor(t_color);
    if (h <= 1 || w <= 1)return;
    for (int ix = x; ix <= x + w; ix++)
    {
        gotoXY(ix, y);
        cout << "-";
        gotoXY(ix, y + h);
        cout << "-";
    }
    for (int iy = y; iy <= y + h; iy++)
    {
        gotoXY(x, iy);
        cout << "|";
        gotoXY(x + w, iy);
        cout << "|";
    }
    gotoXY(x, y); cout << "+";
    gotoXY(x + w, y); cout << "+";
    gotoXY(x, y + h); cout << "+";
    gotoXY(x + w, y + h); cout << "+";

}

void n_box(int x, int y, int w, int h, int t_color, int b_color, string nd[], int sl)   //Hàm tạo nhiều ô của menu động 
{
    for (int i = 0; i < sl; i++)
    {
        box(x, y + (i * 2), w, h, t_color, b_color, nd[i]);
        if (i != 0)
        {
            gotoXY(x, y + (i * 2)); cout << "|";
            gotoXY(x + w, y + (i * 2)); cout << "|";
        }
    }
}

void DisableResizeWindow()          //Hàm đặt tên cho màn hình console
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max)               //  Hàm tắt thu phóng max size, min size của màn hình console
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

enum stase											// enum lua chon chuc nang cua menu chinh 
{
    MENU = 0, OUTPUT, ADD, EDIT, DEL, SEARCH, SORT, SUGGEST, EXIT
}stase;


//===========================// CÁC MENU CHÍNH VÀ MENU CON CỦA CHƯƠNG TRÌNH //=============================


void Output(item it[],int so_luong_item_hientai)                //Menu xuat danh sách trong chương trình
{
    SetColor(15);
    gotoXY(43, 2);
    cout << " >>> XUAT DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[3] = { "Xuat danh sach", "Thoat" };
    int sl = 2, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == OUTPUT)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        LietKeItem(it, so_luong_item_hientai);
                        cout << "\n\t\t\t\t\t  DA XUAT DANH SACH THANH CONG!";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Add(item it[])                    //Menu them vật dụng trong chương trình
{
    SetColor(15);
    gotoXY(43, 2);
    cout << " >>> THEM DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[3] = { "Nhap du lieu", "Thoat" };
    int sl = 2, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == ADD)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {

                    textcolor(b_color);
                    ClearScreen();
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        themItem(it);
                        cout << "\n\t\t\t\t\t   DA NHAP DU LIEU THANH CONG!   ";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Del(item it[])							// Menu cua ham xoa vật dụng trong chương trình
{
    SetColor(15);
    gotoXY(43, 2);
    cout << " >>> XOA DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen<< SANG PHAI >> de chon";
    ShowCur(0);
    string nd[3] = { "Xoa mot vat dung", "Thoat" };
    int sl = 2, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == DEL)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        xoaItem(it);
                        cout << "\n\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        ClearScreen();
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Edit(item it[])							//Menu cua ham chinh sua các vật dụng trong chương trình
{
    SetColor(15);
    gotoXY(43, 2);
    cout << " >>> SUA DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[3] = { "Sua mot vat dung", "Thoat" };
    int sl = 2, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == EDIT)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        suaItem(it);
                        cout << "\n\n\t\t\t\t\t    DA SUA THANH CONG !";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        ClearScreen();
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Search(item it[])						//Menu cua ham tim kiem các vật dụng trong chương trình
{
    int n = so_luong_item_hientai;
    string p;
    float t;
    SetColor(15);
    gotoXY(41, 2);
    cout << " >>> TIM KIEM DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[7] = { "Tim kiem theo ten", "Tim kiem theo gia","Tim kiem theo can nang", 
                                        "Tim kiem theo chieu dai","Tim kiem theo chieu rong", "Thoat"};
    int sl = 6, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == SEARCH)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        cout << "\n\t\tNhap ten vat dung ban can tim:  ";
                        rewind(stdin);
                        getline(cin, p);
                        if (!TimKiemTen(it, n, p))
                            cout << "\n\t\tKhong co vat dung co ten nay!\n";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        ClearScreen();
                        SetColor(15);
                        rewind(stdin);
                        ClearScreen();
                        cout << "\n\t\tNhap gia can tim kiem:  ";
                        cin >> t;
                        if (!TimKiemGia(it, n, t))
                            cout << "\n\t\tKhong co vat dung co gia nay!\n";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 2:
                    {
                        ClearScreen();
                        SetColor(15);
                        cout << "\n\t\tNhap can nang can tim kiem: ";
                        cin >> t;
                        if (!TimKiemCanNang(it, n, t))
                            cout << "\n\t\tKhong co vat dung co can nang nay!\n";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 3:
                    {
                        ClearScreen();
                        SetColor(15);
                        cout << "\n\t\tNhap chieu dai can tim kiem: ";
                        cin >> t;
                        if (!TimKiemChieuDai(it, n, t))
                            cout << "\n\t\tKhong co vat dung co chieu dai nay!\n";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 4:
                    {
                        ClearScreen();
                        SetColor(15);
                        cout << "\n\t\tNhap chieu rong can tim kiem: ";
                        cin >> t;
                        if (!TimKiemChieuRong(it, n, t))
                            cout << "\n\t\tKhong co vat dung co chieu rong nay!\n";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 5:
                    {
                        ClearScreen();
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Sort(item it[])							//Menu cua ham sắp xếp các vật trong trong danh sách
{
    SetColor(15);
    gotoXY(41, 2);
    cout << " >>> SAP XEP DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[5] = { "Sap xep theo ten","Sap xep theo gia","Sap xep teo can nang ", "Thoat"};
    int sl = 4, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == SORT)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        sapXepTen(it);
                        LietKeItem(it, so_luong_item_hientai);
                        cout << "\n\t\t\t\t\t     DA SAP XEP THANH CONG!       ";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 1:
                    {
                        ClearScreen();
                        SetColor(15);
                        sapXepGia(it);
                        LietKeItem(it, so_luong_item_hientai);
                        cout << "\n\t\t\t\t\t     DA SAP XEP THANH CONG!       ";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 2:
                    {
                        ClearScreen();
                        SetColor(15);
                        sapXepCanNang(it);
                        LietKeItem(it, so_luong_item_hientai);
                        cout << "\n\t\t\t\t\t     DA SAP XEP THANH CONG!       ";
                        cout << "\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }
                    case 3:
                    {
                        ClearScreen();
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Suggest(item it[])                     //Menu chứa hàm gợi ý các vật dụng  trong chương trình
{
    SetColor(15);
    gotoXY(42, 2);
    cout << " >>> GOI Y DANH SACH <<<";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[3] = { "Goi y vat dung mang theo", "Thoat" };
    int sl = 2, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == SUGGEST)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        ClearScreen();
                        SetColor(15);
                        NhapKhongGian(canNang);
                        GeneticFunction();
                        cout << "\n\n\t\t\t\t\tNHAN PHIM << SPACE >> DE TRO VE !";
                        rewind(stdin);
                        char t = _getch();
                        if (t == 32)
                        {
                            stase = MENU;
                            ClearScreen();
                        }
                        break;
                    }

                    case 1:
                    {
                        ClearScreen();
                        stase = MENU;
                        break;
                    }
                    }
                }
            }
        }
    }
}

void Menu(item it[])							//Menu chinh cua chuong trinh
{
    SetColor(15);
    gotoXY(28, 2);
    cout << " CHAO MUNG BAN DEN VOI CHUONG TRINH SAP XEP HANH LI ";
    gotoXY(7, 5);
    SetColor(15);
    cout << "Nhan phim di chuyen << LEN >> hoac << XUONG >> de tuy chinh va nhan phim di chuyen << SANG PHAI >> de chon";
    ShowCur(0);
    string nd[9] = {"Liet ke cac vat pham co san","Them mot vat dung","Sua mot vat dung","Xoa mot vat dung",
                                "Tim kiem vat dung","Sap xep thong tin vat dung","Goi y vat dung mang theo","Thoat"};
    int sl = 8, i, j;
    n_box(x, y, w, h, t_color, b_color, nd, sl);
    int xp = x, yp = y;
    int xcu = xp; int ycu = yp;									//toa do anh sang
    bool kt = true;
    while (stase == MENU)
    {
        if (kt == true)											//------ in ----
        {
            i = abs((y - ycu) / 2);
            gotoXY(xcu, ycu);									//----- back space ----
            thanh_sang(xcu, ycu, w, h, b_color, nd[i]);          //rs thanh sang cu
            xcu = xp; ycu = yp;
            j = abs((y - ycu) / 2);
            thanh_sang(xp, yp, w, h, b_color_sang, nd[j]);
            kt = false;
        }
        if (_kbhit())											// dieu khien bang phim di chuyen tren ban phim
        {
            rewind(stdin);
            char c = _getch();
            if (c == -32)
            {
                kt = true;										// khi đã bấm
                c = _getch();
                if (c == 72)									// di chuyển xuống
                {
                    if (yp != y)
                        yp -= 2;
                    else
                    {
                        yp = y + h * (sl - 1);
                    }
                }
                else if (c == 80)							   //di chuyển lên
                {
                    if (yp != y + h * (sl - 1))
                        yp += 2;
                    else
                    {
                        yp = y;
                    }
                }
                else if (c == 77)
                {
                    textcolor(b_color);
                    ClearScreen();
                    gotoXY(40, 10);
                    switch (j)
                    {
                    case 0:
                    {
                        stase = OUTPUT;
                        break;
                    }
                    case 1:
                    {
                        stase = ADD;
                        break;
                    }
                    case 2:
                    {
                        stase = EDIT;
                        break;
                    }
                    case 3:
                    {
                        stase = DEL;
                        break;
                    }
                    case 4:
                    {
                        stase = SEARCH;
                        break;
                    }
                    case 5:
                    {
                        stase = SORT;
                        break;
                    }
                    case 6:
                    {
                        stase = SUGGEST;
                        break;
                    }
                    case 7:
                    {
                    	stase = EXIT;
						break;	
					}
                    }
                }
            }
        }
    }
}

//==================================// HÀM MAIN //========================================================

int main()
{
    DisableCtrButton(0, 1, 1);
    DisableResizeWindow();
    SetConsoleTitle(L"ARANGE LUGGAGE");
    //du_lieu_mau(it);
    sample_item(it);
    stase = MENU;
    Menu(it);
    while (true)
    {
        switch (stase)
        {
        case MENU:
        {
            Menu(it);
            break;
        }
        case OUTPUT:
        {
            Output(it, so_luong_item_hientai);
            break;
        }
        case ADD:
        {
            Add(it);
            break;
        }
        case EDIT:
        {
            Edit(it);
            break;
        }
        case DEL:
        {
            Del(it);
            break;
        }
        case SEARCH:
        {
            Search(it);
            break;
        }
        case SORT:
        {
            Sort(it);
            break;
        }
        case SUGGEST:
        {
            Suggest(it);
            break;
        }
        case EXIT:
        {
        	ClearScreen();
        	SetColor(15);
    		LuuThongTinMoi(it);
    		delete[] it;
    		it = nullptr;
            return 0;
            break;
        }
        }
    }
}


//===============================// KẾT THÚC CHƯƠNG TRÌNH //==============================================