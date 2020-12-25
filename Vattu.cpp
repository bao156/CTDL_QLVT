#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <mylib.h>
#include <sstream> 
#include <math.h>
#pragma warning(disable:4996)
using namespace std;
#define MAUCHU 48
#define MAUNEN 36
const int MAXLISTHD=20;
const int MAXLISTNV=500;
const int MAXMONTH=13;
enum TRANGTHAI{UP,DOWN,LEFT,RIGHT,ENTER,BACK,EXIT};
typedef struct
{
	int manv;
	string password;
}User;
typedef struct
{
	int soluong=0;
	User *dsuser[MAXLISTNV];
}Dsuser;
// DANH SACH VAT TU
 typedef struct
{
	string mavt;
	string tenvt;
	string donvitinh;
	float soluongton;	
}Vattu;
struct node
{
	Vattu vt;
	struct node *pleft;
	struct node *pright;
};
typedef struct node* Tree;
typedef struct
{
	Tree ds=NULL;
	int n;
}Dsvt;
//DANH SACH CHI TIET HOA DON
typedef struct
{
	string mavt;
	float soluong;
	int dongia;
	float vat;//Thue %
	int trangthai;//1:mua   0: tra   
}Cthoadon;
typedef struct
{
	Cthoadon dshd[MAXLISTHD];
	int n=0;
}Dscthoadon;
typedef struct
{
	int day;
	int month;
	int year;
}Date;

struct hoadon
{
	string soHD;
	Date ngaylap;
	string loai;
	Dscthoadon dscthd;
	hoadon *pnext;
};
typedef struct hoadon Hoadon;

typedef struct
{
	Hoadon *phead;
	Hoadon *ptail;
	int n=0;
}Dshoadon;

//DANH SACH NHAN VIEN
typedef struct 
{
    int manv;
	string ho;
	string ten;
	string phai;
	string cmnd;
	Dshoadon dshd;
}Nhanvien;
typedef struct
{
	int n=0;
	Nhanvien *dsnv[MAXLISTNV];
}Dsnhanvien;

typedef struct
{
	int soluongnv;
	int soluonghdx;
	int soluonghdn;
}Autoid;

				/// GENERAL FUNCTION	
bool checkInt(string &s)
{
	bool check=true;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]>57 || s[i]<48)
		{
			check=false;
			break;
		}
	}
	return check;
}
				
bool CheckSizeString(string x,int size)
{
	if(x.length()>size)
	{
		 return false;
	}
	else
	{
		return true;
	}
}
bool CheckSizeStringBang(string x,int size)
{
	if(x.length()!=size)
	{
		 return false;
	}
	else
	{
		return true;
	}
}
void ConvertStringToFloat(string s,float &get)
{
	get=0;
	int mu=s.length()-1;
	for(int i=0;i<s.length();i++)
	{
		get+=(int)(s[i]-48)*pow(10,mu);
		mu-=1;
	}
}
void ConvertStringToInt(string s,int &get)
{
	get=0;
	int mu=s.length()-1;
	for(int i=0;i<s.length();i++)
	{
		get+=(int)(s[i]-48)*pow(10,mu);
		mu-=1;
	}
}
void ThongBaoLoi(char *s)
{
	SetColor(36);
	cout<<s;
	Sleep(1000);
	SetColor(48);
}
bool CheckThang31Ngay(int &month)
{
	
	if(month<8)
	{
		if(month%2!=0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		
		if(month%2==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool CheckDate(Date date)
{
	if(date.year%4==0)
	{
		if(date.month==2)
		{
			if(date.day>=1 && date.day<=29)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(date.month>=1 && date.month<=12)
		{
			if(CheckThang31Ngay(date.month)==true)
			{
				if(date.day>=1 && date.day<=31)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if(date.day>=1 && date.day<=30)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
		
	}
	else
	{
					if(date.month==2)
					{
						if(date.day>=1 && date.day<=28)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else if(date.month>=1 && date.month<=12)
					{
						if(CheckThang31Ngay(date.month)==true)
						{
							if(date.day>=1 && date.day<=31)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							if(date.day>=1 && date.day<=30)
							{
								return true;
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						return false;
					}
      	}
	
}	
void DocAutoID(fstream &file,Autoid &autoid)
{
    file>>autoid.soluonghdn;
    file>>autoid.soluonghdx;
	file>>autoid.soluongnv;
	file.ignore();
}
void GhiAutoID(fstream &file,Autoid autoid)
{
	file<<autoid.soluonghdn;
	file<<" ";
	file<<autoid.soluonghdx;
	file<<" ";
	file<<autoid.soluongnv;
}				
void GetCurrentlyTime(Date &gettime)
{
	time_t now = time(0);
  	tm *ltm = localtime(&now);
	gettime.day=ltm->tm_mday;
	gettime.month=1 + ltm->tm_mon;
	gettime.year=1900 + ltm->tm_year;
}
string chuanHoaChuoi(string &a)
{   int n = a.length(); // dem so ki tu trong chuoi 
	for (int i = 0; i < n; i++)
	{
		if(i==0)
		{
				if (a[i] == ' ')
				{
					for (int j = i; j < n; j++)
						a[j] = a[j + 1];
					i--;
					n--;
				}
		}
		else if(i<n-1 && i>0)
		{
				if (a[i] == ' ' && a[i - 1] == ' ')
				{
					for (int j = i; j < n; j++)
						a[j-1] = a[j];
					i--;
					n--;
				}
		}
		else if(i==n-1)
		{
			if (a[i-1]==32 && a[i]==32 )
				{	
					n=n-2;
				}
				else if(a[i]==32)
				{
					n=n-1;
				}
				 a= a.substr(0,n);
				
		}
	}
	for (int i = 0; i < n; i++)
	{
		if(a[i]>=97 && a[i]<=122 )
		{
			a[i]-=32;
		}
	}
	return a;
}
void resizeConsoleMain(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
TRANGTHAI key(int x)
{
	if(x==224)
	{
		char c;
		c=_getch();
		if(c==72)
		{
			return UP;
		}
		else if (c==80)
		{
			return DOWN;
		}
		else if(c==77)
		{
			return RIGHT;
		}
		else if(c==75)
		{
			return LEFT;
		}
	}
	else if(x==27)
	{
		return EXIT;
	}
	else if (x==13)
	{
		return ENTER;
	}
}
		/////////////PRIVATE FUNCTION
							// DANH SACH VAT TU

void ThemNode(Tree &t,Vattu x)
{
	if(t==NULL)
	{
		node *p=new node();
		p->vt=x;
		p->pleft=NULL;
		p->pright=NULL;
		t=p;
	}
	else
	{
		if(strcmpi(t->vt.mavt.c_str(),x.mavt.c_str())>0)
		{
			ThemNode(t->pleft,x);
		}
		else if(strcmpi(t->vt.mavt.c_str(),x.mavt.c_str())<0)
		{
			ThemNode(t->pright,x);
		}
	}
}
void DocVatTu(fstream &file,Vattu &vt)
{
	getline(file,vt.mavt,',');
	getline(file,vt.tenvt,',');
	getline(file,vt.donvitinh,',');
	file>>vt.soluongton;
}

void LaySoLuongTuKho(Tree &dsvt,string &mavt,int &get)
{
	
	if(dsvt!=NULL)
	{

		if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
		{
			get=dsvt->vt.soluongton;
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
		{
			LaySoLuongTuKho(dsvt->pleft,mavt,get);
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
		{
			LaySoLuongTuKho(dsvt->pright,mavt,get);
		}	
	}
}
void XuatThongTinVatTu(Vattu &vt)
{
	cout<<"\n\n        ";
	cout<<setw(10)<<left<<vt.mavt<<setw(30)<<left<<vt.tenvt<<setw(20)<<left<<vt.donvitinh<<setw(20)<<left<<vt.soluongton;
}
void XuatDanhSachVatTu(Tree dsvt)
{
	if(dsvt!=NULL)
	{
		XuatDanhSachVatTu(dsvt->pright);
	    XuatThongTinVatTu(dsvt->vt);
	    XuatDanhSachVatTu(dsvt->pleft);
	}	
}
void XuatDanhSachVatTuChoThemChiTiet(Tree dsvt)
{

	if(dsvt!=NULL)
	{
		XuatDanhSachVatTu(dsvt->pright);
		if(dsvt->vt.soluongton!=0)
		{
	    XuatThongTinVatTu(dsvt->vt);
		}
	    XuatDanhSachVatTu(dsvt->pleft);
	}
	
}
void TimVatTuChoXoaSua(Tree dsvt,string &search)
{
	
	if(dsvt!=NULL)
	{
		TimVatTuChoXoaSua(dsvt->pright,search);
		int vitrimavt=dsvt->vt.mavt.find(search);
		if( vitrimavt<=dsvt->vt.mavt.length() && vitrimavt>=0 )
		{
			 XuatThongTinVatTu(dsvt->vt);
		}
	    TimVatTuChoXoaSua(dsvt->pleft,search);
	}
	
}
void TimVatTuChoThemChiTiet(Tree dsvt,string &search,Hoadon &x)
{
	
	if(dsvt!=NULL)
	{
		TimVatTuChoThemChiTiet(dsvt->pright,search,x);
		int vitrimavt=dsvt->vt.mavt.find(search);
		if( vitrimavt<=dsvt->vt.mavt.length() && vitrimavt>=0)
		{
			int *soluongtemp=new int();
			*soluongtemp=dsvt->vt.soluongton;
				for(int i=0;i<x.dscthd.n;i++)
				{
					if(strcmpi(dsvt->vt.mavt.c_str(),x.dscthd.dshd[i].mavt.c_str())==0)
					{
						if(strcmpi(x.loai.c_str(),"X")==0)
						{
							*soluongtemp=*soluongtemp-x.dscthd.dshd[i].soluong;
						}
						else
						{
							*soluongtemp=*soluongtemp+x.dscthd.dshd[i].soluong;
						}
						
					}
				}
				cout<<"\n\n        ";
				cout<<setw(10)<<left<<dsvt->vt.mavt<<setw(30)<<left<<dsvt->vt.tenvt<<setw(20)<<left<<dsvt->vt.donvitinh<<setw(20)<<left<<*soluongtemp;
		}
	    TimVatTuChoThemChiTiet(dsvt->pleft,search,x);
	}
	
}


void TimVatTu(Tree dsvt,string &search)
{
	
	if(dsvt!=NULL)
	{
		TimVatTu(dsvt->pright,search);
		int vitritenvt=dsvt->vt.tenvt.find(search);
		int vitrimavt=dsvt->vt.mavt.find(search);
		if(vitritenvt<=dsvt->vt.tenvt.length() && vitritenvt>=0 || vitrimavt<=dsvt->vt.mavt.length() && vitrimavt>=0 )
		{
			 XuatThongTinVatTu(dsvt->vt);
		}
	    TimVatTu(dsvt->pleft,search);
	}
	
}
void GhiVatTu(fstream &file,Vattu vt)
{
	file<<vt.mavt<<","<<vt.tenvt<<","<<vt.donvitinh<<","<<vt.soluongton<<endl;
}
void GhiDanhSachVatTu(fstream &file, Tree dsvt)
{
	if(dsvt!=NULL)
	{
		GhiDanhSachVatTu(file,dsvt->pright);
		GhiVatTu(file,dsvt->vt);
		GhiDanhSachVatTu(file,dsvt->pleft);
	}
}
bool CheckVatTu(Tree &dsvt, string &mavt)
{
		if(dsvt==NULL)
		{
			return false;
		}
		else
		{
			if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
			{
				CheckVatTu(dsvt->pleft,mavt);
			}
			else if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
			{
				CheckVatTu(dsvt->pright,mavt);
			}
			else if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
			{
				return true;													
			}
		}	
}
void NhapVatTu(Tree &dsvt,Vattu &vt)
{
	string *temp=new string();
	bool *checkrangbuoc=new bool();
	bool *checktontai=new bool();
	do
	{
		fflush(stdin);
		cout<<"\n\n NHAP MA VAT TU: ";
		getline(cin,vt.mavt);
		vt.mavt=chuanHoaChuoi(vt.mavt);
		*checktontai=CheckVatTu(dsvt,vt.mavt);
		*checkrangbuoc=CheckSizeString(vt.mavt,10);
		if(*checkrangbuoc==false)
		{
			cout<<"\n\t\t        ";
			ThongBaoLoi("MA VAT TU PHAI DUOI 10 KI TU");
			clrscr();
			SetColor(36);
			cout<<"\t\t      =========NHAP THONG TIN VAT TU==============";
			SetColor(48);
		}
		else if(*checktontai==true)
		{
			cout<<"\n\t        ";
			ThongBaoLoi("MA VAT TU DA TON TAI! VUI LONG NHAP LAI");
			clrscr();
			SetColor(36);
			cout<<"\t\t      =========NHAP THONG TIN VAT TU==============";
			SetColor(48);
		}
	}while(*checktontai==1 || *checkrangbuoc==false);
	
		do
		{
		fflush(stdin);
		cout<<"\n NHAP TEN VAT TU: ";
		getline(cin,vt.tenvt);
		vt.tenvt=chuanHoaChuoi(vt.tenvt);
		*checkrangbuoc=CheckSizeString(vt.tenvt,50);
		if(*checkrangbuoc==false)
		{
			cout<<"\n\t\t        ";
			ThongBaoLoi("VUOT QUA KI TU CHO PHEP");
			clrscr();
			SetColor(36);
			cout<<"\t\t      =========NHAP THONG TIN VAT TU==============";
			SetColor(48);
			cout<<"\n\n NHAP MA VAT TU: "<<vt.mavt<<endl;
		}
	}while(*checkrangbuoc==false);
	
	fflush(stdin);
	cout<<"\n NHAP DON VI TINH: ";
	getline(cin,vt.donvitinh);
	vt.donvitinh=chuanHoaChuoi(vt.donvitinh);
	do
	{
			*checkrangbuoc=false;
			cout<<"\n NHAP SO LUONG TON: ";
			fflush(stdin);
			getline(cin,*temp);
			if(checkInt(*temp)==true)
			{
				ConvertStringToFloat(*temp,vt.soluongton);
				*checkrangbuoc=true;
			}
			else
			{
				cout<<"\n\t        ";
				ThongBaoLoi("SO LUONG KHONG HOP LE! VUI LONG NHAP LAI");
				clrscr();
				SetColor(36);
				cout<<"\t\t      =========NHAP THONG TIN VAT TU==============";
				SetColor(48);
				cout<<"\n\n NHAP MA VAT TU: "<<vt.mavt;
				cout<<"\n\n NHAP TEN VAT TU: "<<vt.tenvt;
				cout<<"\n\n NHAP DON VI TINH: "<<vt.donvitinh<<endl;
			}
	}while(*checkrangbuoc==false);
	SetColor(42);
	cout<<"\n\t\t\t THEM THANH CONG ";
	Sleep(800);
	SetColor(48);
	//GIAI PHONG TEMP HET
	delete checktontai,checkrangbuoc,temp;
}

void ThemDanhSachVattu(Dsvt &ds)
{
	Vattu vt;
	NhapVatTu(ds.ds,vt);
	ThemNode(ds.ds,vt);   
	ds.n++;
}

bool SuaVatTu(Tree &dsvt,string &mavt)
{
	if(dsvt!=NULL)
	{
		if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
		{
				Vattu *vt=new Vattu();
				vt->mavt=mavt;
				
				bool *checksizestring=new bool();
				do
				{
					//GIU NGUYEN MA VAT TU
					clrscr();
					SetColor(36);
					cout<<"\t\t\t\t"<<(char)254<<" SUA THONG TIN VAT TU "<<char(254);
					cout<<"\n\n\t\t\t\t     MA VAT TU: ";
					SetColor(48);
					cout<<mavt;
					fflush(stdin);
					cout<<"\n\n NHAP TEN VAT TU: ";
					getline(cin,vt->tenvt);
					vt->tenvt=chuanHoaChuoi(vt->tenvt);
					*checksizestring=CheckSizeString(vt->tenvt,50);
					if(*checksizestring==false)
					{
						cout<<"\n\n\t\t\t      ";
						ThongBaoLoi("VUOT QUA KI TU CHO PHEP");
						SetColor(48);
					}
				}while(*checksizestring==false);
				
				cout<<"\n NHAP DON VI TINH: ";
				getline(cin,vt->donvitinh);
				vt->donvitinh=chuanHoaChuoi(vt->donvitinh);
				vt->soluongton=dsvt->vt.soluongton;
				dsvt->vt=*vt;
				delete checksizestring,vt;
				return true;
		}
		else if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
		{
			SuaVatTu(dsvt->pleft,mavt);
		}
		else if(strcmpi(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
		{
			SuaVatTu(dsvt->pright,mavt);
		}	
	}
	else
	{
		return false;
	}
}
void ThemBotSoLuongVatTu(Tree &dsvt,Cthoadon &x)
{
	if(dsvt==NULL)
	{
		cout<<"\nEMPTY LIST!";
	}
	else
	{
		if(strcmpi(dsvt->vt.mavt.c_str(),x.mavt.c_str())==0)
		{
			
			dsvt->vt.soluongton+=x.soluong;
		}
		else if(strcmpi(dsvt->vt.mavt.c_str(),x.mavt.c_str())>0)
		{
			ThemBotSoLuongVatTu(dsvt->pleft,x);
		}
		else if(strcmpi(dsvt->vt.mavt.c_str(),x.mavt.c_str())<0)
		{
			ThemBotSoLuongVatTu(dsvt->pright,x);
		}
		
	}
}
void DiTimNodeThayThe(Tree &X, Tree &Y) 
{

	if (Y->pleft != NULL)
	{
		DiTimNodeThayThe(X, Y->pleft);
	}
	else 
	{
		X->vt = Y->vt; // c?p nh?t cái data c?a node c?n xóa chính là data c?a node th? m?ng
		X = Y; // cho node X(là node mà chúng ta s? di xóa sau này) tr? d?n node th? m?ng ==> ra kh?i hàm thì ta s? xóa node X
		Y = Y->pright; // b?n ch?t ch? này chính là c?p nh?t l?i m?i liên k?t cho node cha c?a node th? m?ng(mà chúng ta s? xóa) v?i node con c?a node th? m?ng	
	}

}
void LayTenVatTu(Tree &dsvt, string &mavt,string &ten)
{
	if(dsvt==NULL)
	{
		return ;
	}
	else
	{
			if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
			{
				LayTenVatTu(dsvt->pleft,mavt,ten);
			}
			else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
			{
				LayTenVatTu(dsvt->pright,mavt,ten);
			}
			else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
			{
				ten= dsvt->vt.tenvt;
			}
		}	
}
void XoaVatTuDocFile(Tree &dsvt, string mavt)
{
	if(dsvt==NULL)
	{
		return;
	}
	else
	{
		if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
		{
			XoaVatTuDocFile(dsvt->pleft,mavt);
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
		{
			XoaVatTuDocFile(dsvt->pright,mavt);
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
		{

					Tree temp=dsvt;
					if (dsvt->pleft == NULL)
					{
						// duy?t sang ph?i c?a cái node c?n xóa d? c?p nh?t m?i liên k?t gi?a node 
						// cha c?a node c?n xóa v?i node con c?a node c?n xóa
						dsvt = dsvt->pright; 
					}
					else if (dsvt->pright==NULL)
					{
						// duy?t sang trái c?a cái node c?n xóa d? c?p nh?t m?i liên k?t gi?a node 
						// cha c?a node c?n xóa v?i node con c?a node c?n xóa
						dsvt = dsvt->pleft;
					}
					else
					{
						DiTimNodeThayThe(temp,dsvt->pright);
					}
					delete temp;
			}
		}	
}
bool XoaVatTu(Dsnhanvien dsnvien,Tree &dsvt, string &mavt)
{
	if(dsvt!=NULL)
	{

		if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())>0)
		{
			XoaVatTu(dsnvien,dsvt->pleft,mavt);
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())<0)
		{
			XoaVatTu(dsnvien,dsvt->pright,mavt);
		}
		else if(strcmp(dsvt->vt.mavt.c_str(),mavt.c_str())==0)
		{
			int *flag=new int();
			*flag=1;
			//check 
			for(int i=0;i<dsnvien.n;i++)
			{
				if(*flag==2)
				{
					break;
				}
				for(Hoadon *hd=dsnvien.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
				{
						if(*flag==2)
						{
								break;
						}
						for(int j=0;j<hd->dscthd.n;j++)
						{
								if(*flag==2)
								{
										break;
								}
								if(strcmp(hd->dscthd.dshd[j].mavt.c_str(),mavt.c_str())==0)
								{
									*flag+=1;
									break;
								}
						}
				}
			}	
			
			//XOA
			if(*flag==1)
			{
					Tree temp=dsvt;
					if (dsvt->pleft == NULL)
					{
						// duy?t sang ph?i c?a cái node c?n xóa d? c?p nh?t m?i liên k?t gi?a node 
						// cha c?a node c?n xóa v?i node con c?a node c?n xóa
						dsvt = dsvt->pright; 
					}
					else if (dsvt->pright==NULL)
					{
						// duy?t sang trái c?a cái node c?n xóa d? c?p nh?t m?i liên k?t gi?a node 
						// cha c?a node c?n xóa v?i node con c?a node c?n xóa
						dsvt = dsvt->pleft;
					}
					else
					{
						DiTimNodeThayThe(temp,dsvt->pright);
					}
					delete temp;
					gotoxy(37,8);
					SetColor(42);
					cout<<"XOA THANH CONG";
					Sleep(800);
					clrscr();
					SetColor(48);
					return true;
			}
				
			else if(*flag==2)
			{
				gotoxy(37,8);
				ThongBaoLoi("KHONG THE XOA SAN PHAM NAY");
				gotoxy(15,30);
			}
			delete flag;												
		 }
		}
		else
		{
			return false;
		}	
	}
void DocDanhSachVatTu(fstream &file,Dsvt &dsvt )
{
	dsvt.n=0;
	do
	{
		Vattu *vt=new Vattu();
		DocVatTu(file,*vt);
		file.ignore();
		ThemNode(dsvt.ds,*vt);
		dsvt.n++;
		if(file.eof()==true)
		{
			bool check;
			XoaVatTuDocFile(dsvt.ds,vt->mavt);
			dsvt.n--;
		}
		delete vt;
	}while(!file.eof());
}
void ChonMaVatTuDeXoa(Dsnhanvien &dsnvien,Dsvt &dsvt)
{
			string *search=new string();
			string *temp=new string();
			string *mavt=new string();
			int count1=0;
			char a;
			TextResize(22);
		  	resizeConsole(1000,700);					
			while(1)
			{		
				if(count1==0)
				{
					clrscr();  
					SetColor(36);
					cout<<"\n\t\t\t\t    DANH SACH VAT TU"<<endl;
					cout<<"\t\t\t      =============||==============="<<endl;
					cout<<"\n\n\n           NHAP MA VAT TU MUON XOA: ";		
					gotoxy(4,10);															
					cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
					cout<<"\n";
					SetColor(6);
					VeKhung(0,2,13,2);
					gotoxy(1,3);
				    cout<<"TAB: THOAT";
				    SetColor(48);
				    gotoxy(25,11);
				    XuatDanhSachVatTu(dsvt.ds);
				    Xu_Li_Con_Tro_Chi_Vi(0);
					gotoxy(25,0);
					count1++;
				}									    		
				a = _getch();
				if(a==9)
				{
					break;
				}
				if (a == 13) 
				{
						*mavt=chuanHoaChuoi(*temp);
						bool checkxoa=XoaVatTu(dsnvien,dsvt.ds,*mavt);
						if(checkxoa==false)
						{
							gotoxy(37,8);
							ThongBaoLoi("KHONG TIM THAY VAT TU");
							clrscr(); 
						}
						else 
						{
							dsvt.n--;
							fstream file;
							file.open("CTDL\\VATTU.txt",ios_base::out);
							GhiDanhSachVatTu(file,dsvt.ds);	
							file.close(); 
						}
						 
				}
				else if (a ==8)
				{
						if(search->empty()!=true)
						{
						  cout<<"\b \b";
						  *search = search->substr(0, search->size()-1);
						  clrscr(); 
						}
				}
				else
				{
						search->push_back(a);
						clrscr();
				}
					 
					SetColor(36);
					cout<<"\n\t\t\t\t    DANH SACH VAT TU"<<endl;
					cout<<"\t\t\t      =============||==============="<<endl;
					cout<<"\n\n\n           NHAP MA VAT TU MUON XOA: ";		
					gotoxy(4,10);															
					cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
					cout<<"\n";
					SetColor(6);
					VeKhung(0,2,13,2);
					gotoxy(1,3);
				    cout<<"TAB: THOAT";		
					gotoxy(35,6);
					SetColor(48);
					cout<<*search;
					*temp=*search;
					*temp=chuanHoaChuoi(*temp);
				    gotoxy(25,11);
				    TimVatTuChoXoaSua(dsvt.ds,*temp);
					gotoxy(25,0);
				};
	delete search;
	delete temp;
	delete mavt;
	
}
void ChonMaVatTuDeSua(Dsnhanvien &dsnvien,Dsvt &dsvt)
{
			string *search=new string();
			string *temp=new string();
			string *mavt=new string();
			int count1=0;
			char a;
			TextResize(22);
		  	resizeConsole(1000,700);					
			while(1)
			{		
				if(count1==0)
				{
					clrscr();  
					SetColor(36);
					cout<<"\n\t\t\t\t    SUA THONG TIN VAT TU"<<endl;
					cout<<"\t\t\t      =============||==============="<<endl;
					cout<<"\n\n\n           NHAP MA VAT TU MUON SUA: ";		
					gotoxy(4,10);															
					cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
					cout<<"\n";
					SetColor(6);
					VeKhung(0,2,13,2);
					gotoxy(1,3);
				    cout<<"TAB: THOAT";
				    SetColor(48);
				    gotoxy(25,11);
				    XuatDanhSachVatTu(dsvt.ds);
				    Xu_Li_Con_Tro_Chi_Vi(0);
					gotoxy(25,0);
					count1++;
				}									    		
				a = _getch();
				if(a==9)
				{
					break;
				}
				if (a == 13) 
				{
						*mavt=chuanHoaChuoi(*temp);
						bool checksua=SuaVatTu(dsvt.ds,*mavt);
						if(checksua==false)
						{
							gotoxy(37,8);
							ThongBaoLoi("KHONG TIM THAY VAT TU");
							clrscr(); 
						}
						else 
						{
							dsvt.n--;
							fstream file;
							file.open("CTDL\\VATTU.txt",ios_base::out);
							GhiDanhSachVatTu(file,dsvt.ds);	
							file.close();
							gotoxy(35,8);
							SetColor(42);
							cout<<"SUA THONG TIN VAT TU THANH CONG";
							Sleep(1000);
							SetColor(48);
							clrscr(); 
						}
						 
				}
				else if (a ==8)
				{
						if(search->empty()!=true)
						{
						  cout<<"\b \b";
						  *search = search->substr(0, search->size()-1);
						  clrscr(); 
						}
				}
				else
				{
						search->push_back(a);
						clrscr();
				}
					SetColor(36);
					cout<<"\n\t\t\t\t    SUA THONG TIN VAT TU"<<endl;
					cout<<"\t\t\t      =============||==============="<<endl;
					cout<<"\n\n\n           NHAP MA VAT TU MUON SUA: ";		
					gotoxy(4,10);															
					cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
					cout<<"\n";
					SetColor(6);
					VeKhung(0,2,13,2);
					gotoxy(1,3);
				    cout<<"TAB: THOAT";		
					gotoxy(35,6);
					SetColor(48);
					cout<<*search;
					*temp=*search;
					*temp=chuanHoaChuoi(*temp);
				    gotoxy(25,11);
				    TimVatTuChoXoaSua(dsvt.ds,*temp);
					gotoxy(25,0);
				};
	delete search;
	delete temp;
	delete mavt;
	
}

	/////////////////// HOA DON NE/////////
void KhoiTaoDanhSach(Dshoadon &dshd)
{
	dshd.phead=dshd.ptail=NULL;
}
Hoadon* TaoHoaDon(Hoadon hd)
{
	Hoadon *temp=new Hoadon();
	if(temp==NULL)
	{
		return NULL;
	}
	temp->dscthd.n=hd.dscthd.n;
	temp->soHD=hd.soHD;
	temp->ngaylap=hd.ngaylap;
	temp->loai=hd.loai;
	for(int i=0;i<hd.dscthd.n;i++)
	{
		temp->dscthd.dshd[i]=hd.dscthd.dshd[i];
	}
	temp->pnext=NULL;
	return temp;
}
void ThemHoaDon(Dshoadon &dshd,Hoadon *hd)
{
	if(dshd.phead==NULL)
	{
		dshd.phead=dshd.ptail=hd;
	}
	else
	{
		dshd.ptail->pnext=hd;
		dshd.ptail=hd;
	}
}
 void DocHoaDon(fstream &file,Hoadon &hd)
{
	getline(file,hd.soHD,',');
	getline(file,hd.loai,',');
	file>>hd.ngaylap.day;
	file>>hd.ngaylap.month;
	file>>hd.ngaylap.year;	
}
void DocChiTietHoaDon(fstream &file, Cthoadon &cthd)
{
	getline(file,cthd.mavt,',');
	file>>cthd.soluong;
	file>>cthd.dongia;
	file>>cthd.vat;
	file>>cthd.trangthai;	
	
}
void CapNhapSoluongTrongHoaDon(Hoadon &x,string &mavt,int soluong)
{
	for(int i=0;i<x.dscthd.n;i++)
	{
		if(strcmpi(x.dscthd.dshd[i].mavt.c_str(),mavt.c_str())==0)
		{
		  	x.dscthd.dshd[i].soluong=soluong;
		   break;
		}
	}
}
void LayChiTietTrongHoaDon(Hoadon x,string &mavt,Cthoadon &cthd)
{
	bool *check=new bool();
	*check=false;
	for(int i=0;i<x.dscthd.n;i++)
	{
		if(strcmpi(x.dscthd.dshd[i].mavt.c_str(),mavt.c_str())==0)
		{
			*check=true;
		  	cthd=x.dscthd.dshd[i];
		    break;
		}
	}
	if(*check==false)
	{
		cthd.soluong=0;
	}
	delete check;	
}
void ThemChiTietHoaDon(Tree dsvt,Hoadon &hd,Cthoadon &cthd,string loai)
{
	int soluongcan,laysoluong;
	bool *check=new bool();
	bool *checkint=new bool();
	bool *checktontai=new bool();
	
	char a;
	Dsvt temp;
	Cthoadon *tempcthd=new Cthoadon();
	string *tempstring=new string();
	string *tenvttemp=new string();
	fstream file;
	*check=false;
	// NÊU CO MA VT TRONG HOA DON ROI THI LAY RA FILL VAO DO PHAI NHAP
	
			Xu_Li_Con_Tro_Chi_Vi(0);
			SetColor(36);
			cout<<"\t\t\t\t    THEM CHI TIET VAT TU "<<endl;
			cout<<"\t\t\t      =============||==============="<<endl;
			cout<<"\n\n\n              NHAP MA VAT TU: ";		
			gotoxy(4,9);
			cout<<"";																	
			cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
			cout<<"\n";
			SetColor(48);
			gotoxy(25,9);
			XuatDanhSachVatTuChoThemChiTiet(dsvt);
			gotoxy(25,0);
		    while(1)
	 	    {															    	
			if(_kbhit())
			{														    	
		    	a = _getch();
			   if (a == 13) 
				{
				*check=CheckSizeString(cthd.mavt,10);
				*checktontai=CheckVatTu(dsvt,cthd.mavt);
				if(*check==false)
				{
					gotoxy(28,7);
					ThongBaoLoi("MA VAT TU PHAI DUOI 10 KI TU");
				}
				else if(*checktontai==false|| strcmpi(tempcthd->mavt.c_str()," ")==0)
				{
					gotoxy(28,7);
					ThongBaoLoi("MA VAT TU KHONG TON TAI! VUI LONG NHAP LAI");		
				}
				else
				{
					//DOC FILE ÐE CHECK SO LUONG KHO
					tempcthd->mavt=chuanHoaChuoi(cthd.mavt);
					file.open("CTDL\\VATTU.txt",ios_base::in);
					DocDanhSachVatTu(file,temp);
					
				    LaySoLuongTuKho(temp.ds,tempcthd->mavt,laysoluong);
				    LayChiTietTrongHoaDon(hd,tempcthd->mavt,cthd);
				    
				    if(laysoluong==0 && strcmpi(hd.loai.c_str(),"X")==0) 
				    {
				    		gotoxy(42,7);
				    		SetColor(36);
							cout<<cthd.mavt<<" DA HET HANG";
							Sleep(1500);
							SetColor(48);	
					}
					else if (cthd.soluong<laysoluong || strcmpi(hd.loai.c_str(),"N")==0 )
					{
							 //KIEM TRA XEM CO DU SO LUONG DE PHUC VU HEM
								do
								{
									//KIEM TRA DUNG KIEU DU LIEU CHUA		
										do
										{
											clrscr();
											SetColor(36);
											cout<<"\t\t\t\t            THEM CHI TIET VAT TU "<<endl;
											cout<<"\t\t\t               =============||==============="<<endl;
				    						cout<<"\n\n\t\t\t\t\t    MA VAT TU: ";
											cout<<tempcthd->mavt;
											int *soluongtemp=new int();
											LayTenVatTu(dsvt,tempcthd->mavt,*tenvttemp);
											cout<<"\n\n\t\t\t               TEN VAT TU: "<<*tenvttemp;
											SetColor(48);
											cout<<"\n\nNHAP SO LUONG: ";
											fflush(stdin);
											getline(cin,*tempstring);
											*checkint=checkInt(*tempstring);
											if(*checkint==true)
											{
												ConvertStringToFloat(*tempstring,tempcthd->soluong);
												break;
											}
											else
											{
												ThongBaoLoi("\n\t\t\t\tSO LUONG KHONG HOP LE! VUI LONG NHAP LAI");							
											}
										}while(*checkint==false);
										
										soluongcan=tempcthd->soluong+cthd.soluong;			
										
										if(*checkint==true)
										{
												if(strcmp(loai.c_str(),"X")==0)
												{
													if(soluongcan<=laysoluong && soluongcan>=0)
													{
														*check=true;
													}
													else if(soluongcan>laysoluong)
													{
														*check=false;
														SetColor(36);
														cout<<"\n\t\t\tHIEN "<<cthd.mavt<<" TRONG KHO CHI CON "<<laysoluong-cthd.soluong<<" KHONG DU SO LUONG!";
														Sleep(1000);
														SetColor(48);
													}
												}
												else
												{
													*check=true;
													break;
												}
										}
									
								}while(*check==false );
								
								if(cthd.soluong==0)
								{
												do
												{
													cout<<"\nNHAP DON GIA: ";
													fflush(stdin);
													getline(cin,*tempstring);
													*checkint=checkInt(*tempstring);
													if(*checkint==true)
													{	
														ConvertStringToInt(*tempstring,tempcthd->dongia);
														break;
													}
													else
													{
														ThongBaoLoi("\n\t\t\t\tDON GIA KHONG HOP LE! VUI LONG NHAP LAI");
														clrscr();
														SetColor(36);
														cout<<"\t\t\t\t            THEM CHI TIET VAT TU "<<endl;
														cout<<"\t\t\t               =============||==============="<<endl;
														cout<<"\n\n\t\t\t\t\t    MA VAT TU: ";
														cout<<tempcthd->mavt;
														cout<<"\n\n\t\t\t               TEN VAT TU: "<<*tenvttemp;
							    						SetColor(48);
														
														cout<<"\n\nNHAP SO LUONG: "<<tempcthd->soluong<<endl;
													}
											}while(*checkint==false);
										
											// RANG BUOC VAT NE
											do
											{
													cout<<"\nNHAP VAT: ";
													fflush(stdin);
													getline(cin,*tempstring);
													*checkint=checkInt(*tempstring);
													if(*checkint==true)
													{
														ConvertStringToFloat(*tempstring,tempcthd->vat);
													}
													else
													{
														ThongBaoLoi("\n\t\t\t\tVAT KHONG HOP LE! VUI LONG NHAP LAI");
														clrscr();
														SetColor(36);
														cout<<"\t\t\t\t            THEM CHI TIET VAT TU "<<endl;
														cout<<"\t\t\t               =============||==============="<<endl;
														cout<<"\n\n\t\t\t\t\t    MA VAT TU: ";
														cout<<tempcthd->mavt;
														cout<<"\n\n\t\t\t               TEN VAT TU: "<<*tenvttemp;
														SetColor(48);
														cout<<"\n\nNHAP SO LUONG: "<<tempcthd->soluong;
														cout<<"\n\nNHAP DON GIA: "<<tempcthd->dongia<<endl;
													}
											}while(*checkint==false);
											cthd=*tempcthd;
									}
									else
									{
															CapNhapSoluongTrongHoaDon(hd,tempcthd->mavt,soluongcan);
															hd.dscthd.n--;
									}
				    				cthd.trangthai=1;
				    				break;
				    			}
				    			else
				    			{
				    				gotoxy(42,7);
						    		SetColor(36);
									cout<<cthd.mavt<<" DA HET HANG";
									Sleep(1500);
									SetColor(48);	
								}
				}				
			}
			else if (a ==8)
		    {
				if(tempcthd->mavt.empty()!=true)
				{
						cout<<"\b \b";
						tempcthd->mavt = tempcthd->mavt.substr(0, tempcthd->mavt.size()-1);
				}
			}
			else
			{
				tempcthd->mavt.push_back(a);
			}
				clrscr();
				Xu_Li_Con_Tro_Chi_Vi(0);
				SetColor(36);
				cout<<"\t\t\t\t            THEM CHI TIET VAT TU "<<endl;
				cout<<"\t\t\t               =============||==============="<<endl;
				cout<<"\n\n\n              NHAP MA VAT TU: ";		
				gotoxy(4,9);
				cout<<"";																	
				cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
				cout<<"\n";
				SetColor(48);
			    gotoxy(30,5);
			    cout<<tempcthd->mavt;
				cthd.mavt=tempcthd->mavt;
				cthd.mavt=chuanHoaChuoi(cthd.mavt);
				gotoxy(25,9);
			    TimVatTuChoThemChiTiet(dsvt,cthd.mavt,hd);
			    gotoxy(25,0);
			}
		};
   
	// RANG BUOC DON GIA NE
	delete checktontai,check,checkint,tempstring,tempcthd,tenvttemp;	
	file.close();
}
void XuatChiTietHoaDon(Tree dsvt,Cthoadon cthd)
{
	string *tenvt=new string();
	cout<<"\n\t";
	cout<<setw(10)<<left<<cthd.mavt;
	LayTenVatTu(dsvt,cthd.mavt,*tenvt);
	cout<<setw(20)<<left<<*tenvt;
	cout<<setw(14)<<left<<cthd.soluong;
	cout<<left<<cthd.vat<<setw(9)<<left<<"%";
	cout<<setw(16)<<left<<cthd.dongia;
	cout<<setw(16)<<left<<(long)(cthd.dongia*cthd.soluong+(cthd.dongia*cthd.soluong*(cthd.vat/100)));
	cout<<setw(5)<<left<<cthd.trangthai;
	delete tenvt;
}
void XuatDanhSachChiTietHoaDon(Tree dsvt,Dscthoadon dscthd)
{
				long sum=0;
				SetColor(36);
				cout<<"\n\t"<<left<<setw(13)<<"Ma VT";
				cout<<left<<setw(15)<<"Ten VT";
				cout<<left<<setw(15)<<"So Luong";
				cout<<left<<setw(10)<<"VAT";
				cout<<left<<setw(15)<<"Don Gia";
				cout<<left<<setw(15)<<"Thanh Tien";
				cout<<left<<setw(5)<<"Trang Thai";
				SetColor(48);
				cout<<"\n\t-----------------------------------------------------------------------------------------";
	for(int i=0;i<dscthd.n;i++)
	{
		XuatChiTietHoaDon(dsvt,dscthd.dshd[i]);
		sum+=(dscthd.dshd[i].soluong*dscthd.dshd[i].dongia)+(dscthd.dshd[i].soluong*dscthd.dshd[i].dongia*(dscthd.dshd[i].vat/100));
	}
	cout<<"\n\t-----------------------------------------------------------------------------------------";
	cout<<"\n\t\t\t\t\t\t\t\t\t\t Tong Tien: "<<sum;
}
void XoaChiTietHoaDon(Hoadon &hd,string &mavt)
{
	bool *checktontai=new bool();
	*checktontai=false;
	for(int i=0;i<hd.dscthd.n;i++)
	{
		if(strcmp(hd.dscthd.dshd[i].mavt.c_str(),mavt.c_str())==0)
		{
			*checktontai=true;
			if(i!=hd.dscthd.n-1)
			{		
				for(int j=i;j<hd.dscthd.n-1;j++)
				{
					hd.dscthd.dshd[j]=hd.dscthd.dshd[j+1];
				}
				hd.dscthd.n--;
			}
			else
			{
				hd.dscthd.n--;
			}
		}
	}
	if(*checktontai==true)
	{
			SetColor(42);
			cout<<"\n\n\t\t\t\t\t XOA THANH CONG";
			Sleep(1000);
			SetColor(48);
	}
	else
	{
		cout<<"\n\n\t\t\t\t\t ";
		ThongBaoLoi("MA VAT TU KHONG TON TAI");
	}
}
void ThemVaoDanhSachHoaDon(Dsvt &dsvt,Hoadon &x, Date &dc, Autoid &autoid,bool &checkghi,User &user)
{
	int count=0;
	stringstream *ss=new stringstream();
	string *numberid=new string();
	bool *checkloai=new bool();
	x.ngaylap.day=dc.day;
	x.ngaylap.month=dc.month;
	x.ngaylap.year=dc.year;
	*checkloai=true;
	resizeConsole(1300,300);
	do
	{
		clrscr();
		SetColor(36);
		cout<<"\n\t\t\t\t\t\t"<<(char)219<<" LAP HOA DON "<<(char)219<<endl;
	    cout<<"\t\t\t\t\t==============||==============="<<endl;
		SetColor(48);
		cout<<"\nNHAP LOAI HOA DON: ";
		fflush(stdin);
		getline(cin,x.loai);
		x.loai=chuanHoaChuoi(x.loai);
		if(strcmpi(x.loai.c_str(),"N")==0 || strcmpi(x.loai.c_str(),"X")==0)
		{
			*checkloai=true;
			break;
		}
		else
		{
			*checkloai=false;
			SetColor(36);
			cout<<"\n\t\t\tLOAI HOA KHONG HOP LE VUI LONG NHAP LAI";
			Sleep(500);
			SetColor(48);	
		}
	}while(*checkloai==false);
	
	if(strcmpi(x.loai.c_str(),"N")==0)
	{
			*ss<< autoid.soluonghdn;
			*ss>>*numberid;
	}
	else
	{
		*ss<< autoid.soluonghdx;
		*ss>>*numberid;
	}
	if(numberid->length()>9)
	{
		SetColor(36);
		cout<<"\n\n\t\t\t\t\t SO HOA DON PHAI NHO HON 11 KI TU";
		SetColor(48);
		Sleep(500);
	}
	else
	{
	x.soHD=x.loai+*numberid;
	char choose;
	do
	{
				clrscr();
				gotoxy(25,0);
				Xu_Li_Con_Tro_Chi_Vi(0);
				if(x.dscthd.n==0)
				{
				resizeConsole(1300,600);
				SetColor(36);			
				cout<<"\n\t\t\t\t\t\t  SO HOA DON:"<<x.soHD;	
				VeKhung(48,0,17,2);
				cout<<"\n\n\t\tLoai Hoa Don:"<<x.loai;
				cout<<"\n\t\tNgay Lap:"<< x.ngaylap.day<<"/"<<x.ngaylap.month<<"/"<<x.ngaylap.year;
				cout<<"\n\t\tMa Nhan Vien: "<<user.manv<<endl;						
				SetColor(36);	
				cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   1. THEM CHI TIET HOA DON\t\t\t4. HUY";	
				cout<<"\n";
				}
				else
				{
						gotoxy(25,0);
						resizeConsole(1300,600);
						SetColor(36);			
						cout<<"\n\t\t\t\t\t\t  SO HOA DON:"<<x.soHD;
						VeKhung(48,0,17,2);
						cout<<"\n\n\t\tLoai Hoa Don:"<<x.loai;
						cout<<"\n\t\tNgay Lap:"<< x.ngaylap.day<<"/"<<x.ngaylap.month<<"/"<<x.ngaylap.year;
						cout<<"\n\t\tMa Nhan Vien: "<<user.manv<<endl;	
						XuatDanhSachChiTietHoaDon(dsvt.ds,x.dscthd);
						SetColor(36);
						cout<<"\n\n\n\n\n\n\n\n\n\t1. THEM CHI TIET HOA DON \t 2. XOA CHI TIET HOA DON \t3. XAC NHAN \t 4.HUY";		
						cout<<"\n";
						SetColor(48);
				}
				choose=_getch();
				if(choose=='1')
				{
				
						if(x.dscthd.n==20)
						{
							clrscr();
							cout<<"\n\n\t\t\t\t\t  HOA DON DA DAY! VUI LONG TAO HOA DON KHAC";
						}
						else
						{	
								clrscr();
								SetColor(48);
								ThemChiTietHoaDon(dsvt.ds,x,x.dscthd.dshd[x.dscthd.n],x.loai);
								x.dscthd.n++;
						}
			
				}
				else if (choose=='2'&& x.dscthd.n!=0)
				{
					SetColor(36);
					string *mavt=new string();
					cout<<"\n\n NHAP MA VAT TU CAN XOA: ";
					SetColor(48);
					fflush(stdin);
					getline(cin,*mavt);
					*mavt=chuanHoaChuoi(*mavt);
					XoaChiTietHoaDon(x,*mavt);
					delete mavt;
				}
				//THÊM HÀNG R?I M?I CHO TAO HOA DON VOI COUNT
				else if(choose=='3'&& x.dscthd.n!=0)
				{
					SetColor(42);
					checkghi=true;
					cout<<"\n\n\t\t\t\t\t  TAO HOA DON THANH CONG";
						if(strcmpi(x.loai.c_str(),"N")==0)
						{
								autoid.soluonghdn++;	
						}
						else
						{
							autoid.soluonghdx++;
						}
					Sleep(700);
					SetColor(48);
					break;
				}
				else if(choose=='4')
				{
					checkghi=false;
					SetColor(36);
					cout<<"\n\n\t\t\t\t\t    DA HUY TAO HOA DON ";
					Sleep(700);
					SetColor(48);
					break;
				}
		
	  }while(choose!=3);
	}
	delete ss,numberid;
}
void GhiHoaDon(fstream &file, Hoadon hd,User user)
{
	
	file<<hd.soHD<<","<<hd.loai<<","<<hd.ngaylap.day<<" "<<hd.ngaylap.month<<" "<<hd.ngaylap.year<<" "<<user.manv<<" "
	<<hd.dscthd.n<<"\n";
	for (int i=0;i<hd.dscthd.n;i++)
	{
		file<<hd.dscthd.dshd[i].mavt<<","<<hd.dscthd.dshd[i].soluong<<" "<<hd.dscthd.dshd[i].dongia<<" "<<hd.dscthd.dshd[i].vat<<" "<<hd.dscthd.dshd[i].trangthai<<"\n";
	}
}
void GhiDanhSachHoaDon(fstream &file, Dshoadon dshd,User user)
{
	for(Hoadon* hd=dshd.phead;hd!=NULL; hd=hd->pnext)
	{
		GhiHoaDon(file,*hd,user);
	}
}
	void XuatDanhSachHoaDon(Tree dsvt,Dsnhanvien ds)
{
	for (int i=0;i<ds.n;i++)
	{
		
		for (Hoadon *hd=ds.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
			{
				cout<<"\n\n\n\t\t\t HOA DON: "<<hd->soHD;
				cout<<"\nNGAY LAP: "<<hd->ngaylap.day<<"/"<<hd->ngaylap.month<<"/"<<hd->ngaylap.year;
				cout<<"\nLOAI:"<<hd->loai; 
				cout<<"\n\t\t\t CHI TIET HOA DON";
				for(int i=0;i<hd->dscthd.n;i++)
				{
				XuatChiTietHoaDon(dsvt,hd->dscthd.dshd[i]);
				}
	      }
		
	}	
}
void CapNhatSoLuong(Dsvt &dsvt,Hoadon &x)
{
	for(int i=0;i<x.dscthd.n;i++)
	{
		if(strcmp(x.loai.c_str(),"N")==0)
		{
			ThemBotSoLuongVatTu(dsvt.ds,x.dscthd.dshd[i]);
		}
		else
		{
			x.dscthd.dshd[i].soluong*=(-1);
			ThemBotSoLuongVatTu(dsvt.ds,x.dscthd.dshd[i]);
			x.dscthd.dshd[i].soluong*=(-1);
			
		}
	}
}

///////////////QUAN LI NHAN VIEN////////
		// DOC 1 NHAN VIEN CUA FILE

void DocLogin(fstream &file, User &useraccess)
{
	getline(file,useraccess.password,',');
	file>>useraccess.manv;	
	file.ignore();
}
void XoaLogin(Dsuser &ds,int &manv)
{
			for(int i=0;i<ds.soluong;i++)
			{
				if(manv==ds.dsuser[i]->manv)
				{
					if(i<ds.soluong-1)
					{
						for(int j=i+1;j<ds.soluong;j++)
						{
							ds.dsuser[j-1]=ds.dsuser[j];
						}
						delete ds.dsuser[ds.soluong-1];
						ds.soluong--;
						break;
					}
					
					
					else if(i==ds.soluong-1)
					{
						delete ds.dsuser[ds.soluong-1];
						ds.soluong--;
						break;
					}
					
				}
					
			}

}
void DocDanhSachLogin(fstream &file, Dsuser &ds)
{
	ds.soluong=0;
	do
	{
		ds.dsuser[ds.soluong]=new User();
		DocLogin(file,*ds.dsuser[ds.soluong]);
		ds.soluong++;
		if(file.eof()==true)
		{
			XoaLogin(ds,ds.dsuser[ds.soluong-1]->manv);
		}
	}while(!file.eof());
}	

void GhiLogin(fstream &file, User user)
{
	file<<user.password<<",";
	file<<user.manv;
	file<<"\n";	
}
void GhiDanhSachLogin(fstream &file,Dsuser ds)
{
	for(int i=0;i<ds.soluong;i++)
	{
		GhiLogin(file,*ds.dsuser[i]);
	}
}
void DocNhanVien(fstream &file, Nhanvien &nv)
{
	getline(file,nv.ho,'-');
	getline(file,nv.ten,'-');
	getline(file,nv.phai,'-');
	getline(file,nv.cmnd,'-');
	file>>nv.manv;
	fstream file1;
    file1.open("CTDL\\HOADON.txt",ios_base::in);
    do
    {
    	int *testmanv=new int();
    	int *n=new int();
    	Hoadon testhd;
    	DocHoaDon(file1,testhd);
		file1>>*testmanv;
		file1>>*n;
		testhd.dscthd.n=*n;
		file1.ignore();
		for(int i=0;i<testhd.dscthd.n;i++)
	    {
	    	Cthoadon cthd;	
			DocChiTietHoaDon(file1,cthd);
			testhd.dscthd.dshd[i]=cthd;
			file1.ignore();
		}
    	if(nv.manv==*testmanv)
    	{	
			if(file1.eof()==false)
			{
				Hoadon* addhd=TaoHoaDon(testhd);
    			ThemHoaDon(nv.dshd,addhd);									
    			nv.dshd.n++;
			}	
			else if (file1.eof()==true)
			{
				nv.dshd.n-=2;
			}
		}
		delete testmanv,n;
	}while(!file1.eof());
	file1.close();	
}
void XoaNhanVienDocFile(Dsnhanvien &ds,int &manv)
{			
	for(int i=0;i<ds.n;i++)
    {
	if(ds.dsnv[i]->manv==manv)
	{
    	if(i<ds.n-1)
		{
			for (int j=i+1;j<ds.n;j++)
			{
			ds.dsnv[j-1]=ds.dsnv[j];
			}
			delete ds.dsnv[ds.n-1];	
			ds.n--;																			
		}
		else if (i==ds.n-1)
		{
			delete ds.dsnv[ds.n-1];
			ds.n--;							
		}
		break;
		}
	}
}
void DocDanhSachNhanVien(fstream &file, Dsnhanvien &ds)
{
	ds.n=0;
	do
	{
		ds.dsnv[ds.n]=new Nhanvien();
		DocNhanVien(file,*ds.dsnv[ds.n]);
		file.ignore();
		ds.n++;	
		if(file.eof()==true)
		{
			XoaNhanVienDocFile(ds,ds.dsnv[ds.n-1]->manv);
		}
	}while(!file.eof());
}


void SapXepNhanVien(Dsnhanvien ds)
{
	for(int i=0;i<ds.n-1;i++)
	{
		for(int j=i+1;j<ds.n;j++)
		{
			Nhanvien a=*ds.dsnv[i];
			Nhanvien b=*ds.dsnv[j];
			if(strcmpi(a.ten.c_str(),b.ten.c_str())>0)
			{
				Nhanvien *temp=new Nhanvien();
				*temp=a;
				a=b;
				b=*temp;
				delete temp;
			}
			else if(strcmpi(a.ten.c_str(),b.ten.c_str())==0)
			{
				if(strcmpi(a.ho.c_str(),b.ho.c_str())>0)
				{
						Nhanvien *temp=new Nhanvien() ;
						*temp=a;
						a=b;
						b=*temp;
						delete temp;
				}				
			}
				*ds.dsnv[i]=a;
			*ds.dsnv[j]=b;
		}
	}
}
void GhiThongTinNhanVien(fstream &file, Nhanvien nv)
{
	file<<nv.ho<<"-"<<nv.ten<<"-"<<nv.phai<<"-"<<nv.cmnd<<"-"<<nv.manv<<"\n";
}
void GhiDanhSachNhanVien(fstream &file, Dsnhanvien ds)
{
	SapXepNhanVien(ds);
	for (int i=0;i<ds.n;i++)
	{
		GhiThongTinNhanVien(file,*ds.dsnv[i]);
	}
}
void GhiDanhSachHoaDonFull(fstream &file, Dsnhanvien &ds,User user)
{
	SapXepNhanVien(ds);
	for (int i=0;i<ds.n;i++)
	{
		for (Hoadon *hd=ds.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
		{
			GhiHoaDon(file,*hd,user);
		}
	}
}
void XuatDanhSachNhanVien(Dsnhanvien ds )
{
	SapXepNhanVien(ds);
	SetColor(36);
	cout<<"\t\t\t\t    DANH SACH NHAN VIEN"<<endl;
	cout<<"\t\t\t      =============||==============="<<endl;
	cout<<"\n\n\n\n\n\n\n\n             "<<setw(15)<<left<<"MA NV"<<setw(13)<<left<<"HO "<<setw(13)<<"TEN"<<setw(13)<<left<<"PHAI"<<setw(15)<<"SO CMND";
	SetColor(48);
	for (int i=0;i<ds.n;i++)
	{
		cout<<"\n\n\t      "<<setw(10)<<left<<ds.dsnv[i]->manv<<setw(15)<<left<<ds.dsnv[i]->ho<<setw(15)<<left<<ds.dsnv[i]->ten<<setw(13)<<left<<ds.dsnv[i]->phai<<setw(15)<<left<<ds.dsnv[i]->cmnd;	
	}
	SetColor(6);
	VeKhung(0,2,13,2);
	gotoxy(1,3);
	cout<<"TAB: THOAT";
}
int CheckMaNVTonTai(Dsnhanvien &dsnvien,int &manv)
{
	int flag=0;
	for(int i=0;i<dsnvien.n;i++)
	{
		if(dsnvien.dsnv[i]->manv==manv)
		{
			flag++;
			break;
		}
	}
	return flag;
}
int CheckMaNVTonTaiNhanVien(Dsnhanvien &dsnvien,Nhanvien &nv)
{
	int flag=0;
	for(int i=0;i<dsnvien.n;i++)
	{
		if(dsnvien.dsnv[i]->manv==nv.manv)
		{
			flag++;
			break;
		}
	}
	return flag;
}
int CheckCMNDTonTaiNhanVien(Dsnhanvien &dsnvien,Nhanvien &nv)
{
	int flag=0;
	for(int i=0;i<dsnvien.n;i++)
	{
         if(strcmp(dsnvien.dsnv[i]->cmnd.c_str(),nv.cmnd.c_str())==0)
		{
			flag++;
			break;
		}
	}
	return flag;
}
void TimNhanVienChoXoaSua(Dsnhanvien dsnvien,string &search,char *loai)
{		
			SetColor(6);
			VeKhung(0,2,13,2);
			gotoxy(1,3);
			cout<<"TAB: THOAT";
			gotoxy(15,5);
			SetColor(36);
			cout<<"NHAP MA NHAN VIEN MUON "<<loai<<": ";		
		    SetColor(48);
			gotoxy(37,0);
		    SetColor(36);
			cout<<"  DANH SACH NHAN VIEN"<<endl;
			gotoxy(12,1);
			cout<<"\t\t\t =============||==============="<<endl;
			gotoxy(2,4);
			cout<<"\n\n\n\n\n\n             "<<setw(15)<<left<<"MA NV"<<setw(13)<<left<<"HO "<<setw(13)<<"TEN"<<setw(13)<<left<<"PHAI"<<setw(15)<<"SO CMND";
			SetColor(48);
	for (int i=0;i<dsnvien.n;i++)
	{
		int *manvtemp=new int();
		*manvtemp=dsnvien.dsnv[i]->manv;
		stringstream *ss=new stringstream();
		string *manvstring=new string();
		*ss<<*manvtemp;
		*ss>>*manvstring;
		
		if(strcmpi(search.c_str(),manvstring->c_str())==0)
		{
				cout<<"\n\n\t      "<<setw(10)<<left<<dsnvien.dsnv[i]->manv<<setw(15)<<left<<dsnvien.dsnv[i]->ho<<setw(15)<<left<<dsnvien.dsnv[i]->ten<<setw(13)<<left<<dsnvien.dsnv[i]->phai<<setw(15)<<left<<dsnvien.dsnv[i]->cmnd;	
		}
		delete ss,manvstring;
	}
		gotoxy(25,2);
		
}
void TimNhanVien(Dsnhanvien dsnvien,string &search)
{		
            SetColor(6);
			VeKhung(0,2,13,2);
			gotoxy(1,3);
			cout<<"TAB: THOAT";
			gotoxy(15,5);
			SetColor(36);
			cout<<"TIM KIEM: ";		
			SetColor(48);
			gotoxy(37,0);
		    SetColor(36);
			cout<<"  DANH SACH NHAN VIEN"<<endl;
			gotoxy(12,1);
			cout<<"\t\t\t =============||==============="<<endl;
			gotoxy(2,4);
			cout<<"\n\n\n             "<<setw(15)<<left<<"MA NV"<<setw(13)<<left<<"HO "<<setw(13)<<"TEN"<<setw(13)<<left<<"PHAI"<<setw(15)<<"SO CMND";
			SetColor(48);
	for (int i=0;i<dsnvien.n;i++)
	{
		int *manvtemp=new int();
		*manvtemp=dsnvien.dsnv[i]->manv;
		stringstream *ss=new stringstream();
		string *manvstring=new string();
		*ss<<*manvtemp;
		*ss>>*manvstring;
		
		int *vitrimanv=new int();
		*vitrimanv=manvstring->find(search);
		int *vitricmnd=new int();
		*vitricmnd=dsnvien.dsnv[i]->cmnd.find(search);
		int *vitriten=new int();
		*vitriten=dsnvien.dsnv[i]->ten.find(search);
		if(*vitricmnd<=dsnvien.dsnv[i]->cmnd.length() && *vitricmnd>=0 || *vitriten<=dsnvien.dsnv[i]->ten.length() && *vitriten>=0 || *vitrimanv<=manvstring->length() && *vitrimanv>=0)
		{
				cout<<"\n\n\t      "<<setw(10)<<left<<dsnvien.dsnv[i]->manv<<setw(15)<<left<<dsnvien.dsnv[i]->ho<<setw(15)<<left<<dsnvien.dsnv[i]->ten<<setw(13)<<left<<dsnvien.dsnv[i]->phai<<setw(15)<<left<<dsnvien.dsnv[i]->cmnd;	
		}
		delete ss,manvstring,vitrimanv,vitricmnd,vitriten;
	}
		gotoxy(25,2);		
}
void ThemNhanVien(Dsnhanvien &dsnvien,Nhanvien &nv,Autoid &autoid)
{
		User *user=new User();
		int *check=new int();
		bool *checkphai=new bool();
		string password;
		nv.manv=autoid.soluongnv;
		autoid.soluongnv+=1;
		SetColor(36);
		cout<<"\n\t\t\t\t      "<<(char)219<<" THEM NHAN VIEN MOI "<<(char)219<<endl;
		cout<<"\n\t\t\t         ==============||==============="<<endl;
		cout<<"\n\t\t\t            	    ID:"<<autoid.soluongnv-1<<endl;
		SetColor(48);	
		cout<<"\nNHAP HO: ";
		fflush(stdin);
		getline(cin, nv.ho);
		cout<<"\nNHAP TEN: ";
		fflush(stdin);
		getline(cin, nv.ten);
		do
		{
		        	*checkphai=true;
					cout<<"\nNHAP PHAI: ";
					fflush(stdin);
					getline(cin, nv.phai);
					nv.phai=chuanHoaChuoi(nv.phai);
					if(strcmpi(nv.phai.c_str(),"NAM")!=0 && strcmp(nv.phai.c_str(),"NU")!=0)
					{
						*checkphai=false;
						cout<<"\n\n\t\t\t" ;
						ThongBaoLoi("PHAI KHONG HOP LE! VUI LONG NHAP LAI");
						clrscr();
						SetColor(36);
						cout<<"\n\t\t\t\t      "<<(char)219<<" THEM NHAN VIEN MOI "<<(char)219<<endl;
						cout<<"\n\t\t\t         ==============||==============="<<endl;
						SetColor(48);
						cout<<"\nNHAP HO: "<<nv.ho;
						cout<<"\n\nNHAP TEN: "<<nv.ten<<endl;		
					}	
		}while(*checkphai==false);

		cout<<"\nNHAP PASSWORD: ";
			while(1)
		    {
		    	char a = _getch();
				if (a == 13) 
				{
					break;
				}
				else if (a ==8)
				{
					if(password.empty()!=true)
					{
						cout<<"\b \b";
						user->password = user->password.substr(0,user->password.size()-1);
					}
				}
				else
				{
					cout<<"*";
					user->password.push_back(a);
				}
		    };
		 cout<<"\n";   
		do
		{
					*check=0;
					cout<<"\nNHAP CMND: ";
					fflush(stdin);
					getline(cin, nv.cmnd);
					*check=CheckCMNDTonTaiNhanVien(dsnvien,nv);
					if(*check==1)
					{
						cout<<"\n\t\t ";
						ThongBaoLoi("CMND HOAC THE CAN CUOC DA TON TAI! VUI LONG NHAP LAI");
						clrscr();
						SetColor(36);
						cout<<"\n\t\t\t\t      "<<(char)219<<" THEM NHAN VIEN MOI "<<(char)219<<endl;
						cout<<"\n\t\t\t         ==============||==============="<<endl;
						SetColor(48);
						cout<<"\nNHAP HO: "<<nv.ho;
						cout<<"\n\nNHAP TEN: "<<nv.ten;	
						cout<<"\n\nNHAP PHAI: "<<nv.phai;
							cout<<"\n\nNHAP PASSWORD: ";
						for(int i=0;i<user->password.length();i++)
						{
							cout<<"*";
						}
						cout<<endl;
						
					}
					else if(CheckSizeStringBang(nv.cmnd,9)==false && CheckSizeStringBang(nv.cmnd,12)==false)
					{
						*check+=1;
						cout<<"\n\t\t ";
						ThongBaoLoi("CMND HOAC THE CAN CUOC KHONG HOP LE! VUI LONG NHAP LAI");
						clrscr();
						SetColor(36);
						cout<<"\n\t\t\t\t      "<<(char)219<<" THEM NHAN VIEN MOI "<<(char)219<<endl;
						cout<<"\n\t\t\t         ==============||==============="<<endl;
						SetColor(48);
						cout<<"\nNHAP HO: "<<nv.ho;
						cout<<"\n\nNHAP TEN: "<<nv.ten;	
						cout<<"\n\nNHAP PHAI: "<<nv.phai;
						cout<<"\n\nNHAP PASSWORD: ";
						for(int i=0;i<user->password.length();i++)
						{
							cout<<"*";
						}
						cout<<endl;
						
						
					}
		}while(*check==1);
		nv.ho=chuanHoaChuoi(nv.ho);
		nv.ten=chuanHoaChuoi(nv.ten);
		user->manv=nv.manv;
		SetColor(42);
		cout<<"\n\n\t\t\t\t THEM NHAN VIEN THANH CONG";
		Sleep(800);
		SetColor(48);
		fstream file;
		file.open("CTDL\\LOGIN.txt",ios_base::app);
		GhiLogin(file,*user);
		file.close();	
		delete check,checkphai,user;
}
void ThemDanhSachNhanVien(Dsnhanvien &ds,Autoid &autoid)
{
	if(ds.n==MAXLISTNV-1)
	{
		cout<<"\n\n\t\t";
		ThongBaoLoi("DANH SACH DAY");
	}
	else
	{
		ds.dsnv[ds.n]=new Nhanvien();
		ThemNhanVien(ds,*ds.dsnv[ds.n],autoid);
		ds.n++;
	}
	
}

void XoaNhanVien(Dsnhanvien &ds,User &user,Dsuser &dsuser)
{
	int *manv=new int();				
	int *flag=new int();
	string *search=new string();
	string *temp=new string();
	char a;
	gotoxy(25,0);
	SetColor(6);
	VeKhung(0,2,13,2);
	gotoxy(1,3);
	cout<<"TAB: THOAT";
	gotoxy(15,5);
	SetColor(36);
	cout<<"NHAP MA NHAN VIEN MUON XOA: ";	
	gotoxy(15,0);	
	Xu_Li_Con_Tro_Chi_Vi(0);
	SetColor(48);										
  	 while(1)
  	 {
		if(_kbhit())
		{
		*flag=0;
		Xu_Li_Con_Tro_Chi_Vi(0);
		a = _getch();
		if(a==9)
		{
			break;
		}
		else if (a == 13 ) 
		{
					ConvertStringToInt(*temp,*manv);
					bool *checksuccess=new bool();
					*checksuccess=false;
						for(int i=0;i<ds.n;i++)
						{
						  if(ds.dsnv[i]->manv==*manv)
							{
								*flag+=1;
								if(user.manv==*manv)
								{
									gotoxy(35,7);
									ThongBaoLoi("KHONG THE XOA NHAN VIEN NAY");
									clrscr();	
									break;
								}
								else if(ds.dsnv[i]->dshd.n==0)
								{
									*flag+=1;	
									int count1=0;
									if(i<ds.n-1)
									{
										for (int j=i;j<ds.n-1;j++)
										{
											ds.dsnv[j]=ds.dsnv[j+1];
										}
									}
									ds.n-=1;
									gotoxy(35,7);
									SetColor(42);
									cout<<"XOA THANH CONG";
									Sleep(1000);
									SetColor(48);
									XoaLogin(dsuser,*manv);								
									fstream file;
									file.open("CTDL\\LOGIN.txt",ios_base::out);
									GhiDanhSachLogin(file,dsuser);
									file.close();
									*checksuccess=true;
									break;
								}
								else
								{
									gotoxy(35,7);
									ThongBaoLoi("KHONG THE XOA NHAN VIEN NAY");
									clrscr();	
									break;
								}
							}
							if(*checksuccess==true)
							{
								break;
							}
						}	
								if(*flag==0)
								{
									gotoxy(35,7);
									ThongBaoLoi("KHONG TIM THAY NHAN VIEN");
									clrscr();	
								}
						if(*checksuccess==true)
						{
							break;
						}
						delete checksuccess;
		}	
		else if (a ==8)
		{
			 if(search->empty()!=true)
			 {
			 	clrscr();	
				cout<<"\b \b";
				*search = search->substr(0, search->size()-1);
			 }
		}
		else
		{
			clrscr();	
			search->push_back(a);													
		}
				if(search->length()!=0)
				{
						gotoxy(43,5);
						cout<<*search;
						*temp=*search;
						*temp=chuanHoaChuoi(*temp);
					    TimNhanVienChoXoaSua(ds,*temp,"XOA");
						gotoxy(15,0);
				}
				else
				{
						XuatDanhSachNhanVien(ds);
						gotoxy(15,5);
						SetColor(36);
						cout<<"NHAP MA NHAN VIEN MUON XOA: ";	
						gotoxy(43,4);
						SetColor(48);
						cout<<*search;
						gotoxy(15,0);
				}
											
			};									
	}
	
	delete manv,flag,search,temp;
}


void SuaThongTinNhanVien(Dsnhanvien ds)
{
	int *manv=new int();
	int *flag=new int();
	string *temp=new string();
	string *search=new string();
	bool *check=new bool;
	bool *checkcmnd=new bool();
	bool *checkphai=new bool();
	char a;
	*check=false;
	gotoxy(25,0);
	VeKhung(0,2,13,2);
	gotoxy(1,3);
	SetColor(6);
	cout<<"TAB: THOAT";
	gotoxy(15,5);
	SetColor(36);
	cout<<"NHAP MA NHAN VIEN MUON SUA: ";	
	gotoxy(15,0);	
	Xu_Li_Con_Tro_Chi_Vi(0);
	SetColor(48);										
  	while(1)
  	{
	   if(_kbhit())
		{
		*flag=0;
		Xu_Li_Con_Tro_Chi_Vi(0);
		a = _getch();
		if(a==9)
		{
			break;
		}
		else if (a == 13 ) 
		{
			ConvertStringToInt(*temp,*manv);
			bool *checksuccess=new bool();
			*checksuccess=false;
			for(int i=0;i<ds.n;i++)
			{
				if(ds.dsnv[i]->manv==*manv)
				{	
							*flag+=1;
							Nhanvien nv;
							clrscr();
							SetColor(36);
							cout<<"\t\t\t\t"<<(char)254<<" SUA THONG TIN NHAN VIEN "<<char(254);
							cout<<"\n\n\t\t\t\t     MA NHAN VIEN: ";
							SetColor(48);
							cout<<*manv;
							nv.manv=*manv;
							cout<<"\n\nNHAP HO: ";
							fflush(stdin);
							getline(cin, nv.ho);
							cout<<"\nNHAP TEN: ";
							fflush(stdin);
							getline(cin, nv.ten);
							
							do
							{
					        	*checkphai=true;
								cout<<"\nNHAP PHAI: ";
								fflush(stdin);
								getline(cin, nv.phai);
								nv.phai=chuanHoaChuoi(nv.phai);
									if(strcmp(nv.phai.c_str(),"NAM")!=0 && strcmp(nv.phai.c_str(),"NU")!=0)
									{
										*checkphai=false;
										cout<<"\n\n\t\t\t ";
										ThongBaoLoi("PHAI KHONG HOP LE! VUI LONG NHAP LAI");
										clrscr();
										SetColor(36);
										cout<<"\t\t\t\t"<<(char)254<<" SUA THONG TIN NHAN VIEN "<<char(254);
										cout<<"\n\n\t\t\t\t     MA NHAN VIEN: ";
										SetColor(48);
										cout<<*manv;
										cout<<"\n\nNHAP HO: "<<nv.ho;
										cout<<"\n\nNHAP TEN: "<<nv.ten<<endl;
									}	
							}while(*checkphai==false);
								
							do
							{
								cout<<"\nNHAP CMND: ";
								fflush(stdin);
								getline(cin, nv.cmnd);	
							    *checkcmnd=true;
								for(int j=0;j<ds.n;j++)
								{
									if(strcmp(ds.dsnv[j]->cmnd.c_str(),nv.cmnd.c_str())==0 && ds.dsnv[j]->manv!=nv.manv)
									{
										*checkcmnd=false;
										cout<<"\n\t\t ";
										ThongBaoLoi("SO CMND DA TON TAI! VUI LONG NHAP LAI");
									}
									else if(CheckSizeStringBang(nv.cmnd,9)==false && CheckSizeStringBang(nv.cmnd,12)==false)
									{
										*checkcmnd=false;
										cout<<"\n\t\t ";
										ThongBaoLoi("CMND HOAC THE CAN CUOC KHONG HOP LE! VUI LONG NHAP LAI");
									}
									else
									{
										*checkcmnd=true;
									}
									
									if(*checkcmnd==false)
									{
										clrscr();
										SetColor(36);
										cout<<"\t\t\t\t"<<(char)254<<" SUA THONG TIN NHAN VIEN "<<char(254);
										cout<<"\n\n\t\t\t\t     MA NHAN VIEN: ";
										SetColor(48);
										cout<<*manv;
										cout<<"\n\nNHAP HO: "<<nv.ho;
										cout<<"\n\nNHAP TEN: "<<nv.ten;
										cout<<"\n\nNHAP PHAI: "<<nv.phai<<endl;	
										break;	
									}
								}
							}while(*checkcmnd==false);
							nv.ho=chuanHoaChuoi(nv.ho);	
							nv.ten=chuanHoaChuoi(nv.ten);
							*ds.dsnv[i]=nv;
							SetColor(42);
							cout<<"\n\n\t\t\t     SUA THONG TIN NHAN VIEN THANH CONG";
					     	Sleep(1000);
						    SetColor(48);
							*check=true;
							*checksuccess=true;
							break;
				}
			}	
					if(*checksuccess==true)
					{
						clrscr();
						break;
					}
					else if(*flag==0)
					{
					  gotoxy(35,7);
					 ThongBaoLoi("KHONG TIM THAY NHAN VIEN");
					 clrscr();	
					}
					delete checksuccess;
		 }	
		
		
		else if (a ==8)
		{
			 if(search->empty()!=true)
			 {
			 	clrscr();	
				cout<<"\b \b";
				*search = search->substr(0, search->size()-1);
			 }
		}
		else
		{
			clrscr();	
			search->push_back(a);													
		}
		
				if(search->length()!=0)
				{
						gotoxy(43,5);
						cout<<*search;
						*temp=*search;
						*temp=chuanHoaChuoi(*temp);
					    TimNhanVienChoXoaSua(ds,*temp,"SUA");
						gotoxy(15,0);
				}
				else
				{
						XuatDanhSachNhanVien(ds);
						gotoxy(15,5);
						SetColor(36);
						cout<<"NHAP MA NHAN VIEN MUON SUA: ";	
						gotoxy(43,4);
						SetColor(48);
						cout<<*search;
						gotoxy(15,0);
				}
											
			};									
	}
	delete manv,flag,search,temp,checkcmnd,checkphai,check;
}

void checkLogin(User &useraccess,bool &checkuser,bool &checkpassword)
{
	fstream file;
	checkuser=false;
	checkpassword=false;
	file.open("CTDL\\LOGIN.txt",ios_base::in);
	while(!file.eof())
	{
		User temp;
		DocLogin(file,temp);
		if(useraccess.manv==temp.manv)
		{
			checkuser=true;
			if(strcmp(useraccess.password.c_str(),temp.password.c_str())==0)
			{
						checkpassword=true;
						useraccess.manv=temp.manv;
			}
			break;
		}
	}
	file.close();
}
void Login(User &user)
{
	Xu_Li_Con_Tro_Chi_Vi(0);
	bool checkuser,checkpass;
	string erroruser="",errorpass="",success="";
	int coloruser=47;
	int colorpass=47;
	do
	{
	clrscr();
	system("color F0");
	SetColor(20);
	gotoxy(19,0);
	//DESIGN KHUNG
	gotoxy(18,0);
	char a=157;
	cout<<a<<" WELCOME TO B&D FURNITURE "<<a;
	TextResize(24);
	resizeConsole(695,365);
	SetColor(48);
	VeKhung(0,2,58,10);
	SetColor(48);
	gotoxy(25,2);
	cout<<"DANG NHAP";
	gotoxy(5,4);	
	cout<<"Ma Nhan Vien: ";
	SetColor(coloruser);
	gotoxy(15,5);
	cout<<erroruser;

	SetColor(48);
	gotoxy(8,8);
	cout<<" Mat khau: ";
	SetColor(colorpass);
	gotoxy(15,9);
	cout<<errorpass;
	gotoxy(19,4);
	SetColor(48);
	
	//NHAP MA NHAN VIEN DE CHECK
	cin>>user.manv;
	gotoxy(19,8);
	
	//CHECK DIEU KIEN
		    while(1)
		    {
		    	char a = _getch();
				if (a == 13) 
				{
					break;
				}
				else if (a ==8)
				{
					if(user.password.empty()!=true)
					{
						cout<<"\b \b";
						user.password = user.password.substr(0, user.password.size()-1);
					}
				}
				else
				{
					cout<<"*";
					user.password.push_back(a);
				}
		    };
		    checkLogin(user,checkuser,checkpass);
		    if(checkuser==false)
		    {
		    	coloruser=60;
		    	colorpass=47;
		    	user.manv=NULL;
		    	user.password="";
		    	erroruser="Nguoi dung khong ton tai";
		    	errorpass="";
			}
			else if(checkpass==false)
			{
				coloruser=60;
		    	colorpass=12;
				user.manv=NULL;
		    	user.password="";
		    	erroruser="";
		    	errorpass="Sai mat khau";
			}
	}while(checkpass==false || checkuser==false);
	Xu_Li_Con_Tro_Chi_Vi(0);
}

void DoiTraHang(Dsnhanvien &dsnvien, Dsvt &dsvt,bool &checkdate,Date &nowtime)
{
						string *mahd=new string();
						bool check=false;
						bool *checkmavttontai=new bool();
						*checkmavttontai=false;
						resizeConsole(1300,300);
						SetColor(36);
						cout<<"\n\t\t\t\t\t "<<(char)219<<" DOI TRA HANG "<<(char)219<<endl;
						cout<<"\n\t\t\t         ==============||==============="<<endl;
						fflush(stdin);
						cout<<"\n\nNHAP VAO SO HOA DON CAN THAO TAC: ";
						SetColor(48);
						getline(cin,*mahd);
						*mahd=chuanHoaChuoi(*mahd);	
						clrscr();
						resizeConsole(1300,800);
						for(int i=0;i<dsnvien.n;i++)
						{
							for(Hoadon *hd=dsnvien.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
							{
								
								if(strcmp(hd->soHD.c_str(),mahd->c_str())==0)
								{
									check=true;
								    checkdate=true;
									SetColor(36);
									cout<<"\n\t\t\t\t\t\t "<<(char)219<<" DOI TRA HANG "<<(char)219<<endl;
						 			cout<<"\n\t\t\t\t         ==============||==============="<<endl<<endl;		
									cout<<"\n";
									VeKhung(48,6,17,2);
									gotoxy(49,7);
									cout<<" SO HOA DON:"<<hd->soHD;
									cout<<"\n";
									cout<<setw(60)<<"\n\t\tLoai Hoa Don:";
									SetColor(48);
									cout<<hd->loai;
									SetColor(36);
									cout<<setw(20)<<"\n\t\tNgay Lap:";
									SetColor(48);
									cout<< hd->ngaylap.day<<"/"<<hd->ngaylap.month<<"/"<<hd->ngaylap.year;
									SetColor(36);
									cout<<setw(20)<<"\n\t\tMa Nhan Vien:";
									SetColor(48);
									cout<<dsnvien.dsnv[i]->manv<<endl;
									SetColor(36);
									cout<<setw(20)<<"\t\tTen Nhan Vien:";
									SetColor(48);
									cout<<dsnvien.dsnv[i]->ho<<" "<<dsnvien.dsnv[i]->ten<<endl;
									SetColor(36);
								    cout<<"\n\t"<<left<<setw(13)<<"Ma VT";
									cout<<left<<setw(15)<<"Ten VT";
									cout<<left<<setw(15)<<"So Luong";
									cout<<left<<setw(10)<<"VAT";
									cout<<left<<setw(15)<<"Don Gia";
									cout<<left<<setw(15)<<"Thanh Tien";
									cout<<left<<setw(5)<<"Trang Thai"<<endl;
									SetColor(48);
									cout<<"\t---------------------------------------------------------------------------------------------";
									for(int i=0;i<hd->dscthd.n;i++)
									{
										XuatChiTietHoaDon(dsvt.ds,hd->dscthd.dshd[i]);
									}
									cout<<"\n\t---------------------------------------------------------------------------------------------";
									if(strcmpi(hd->loai.c_str(),"N")==0)
									{
										SetColor(36);
										cout<<"\n\n\n\t\t\t\t   LOAI DON HANG NAY KHONG THE TRA";
										Sleep(1500);
										cout<<"\n";
									}
									else
									{
										if(hd->ngaylap.year!=nowtime.year)
										{
											if(nowtime.year-hd->ngaylap.year==1 && hd->ngaylap.month==12 && nowtime.month==1 && hd->ngaylap.day>=30 && nowtime.day<=2 )
											{
												if((nowtime.day+30)-hd->ngaylap.day<2)
												{
													checkdate=true;
												}
												else
												{
													checkdate=false;
												}
											}
											else
											{
												checkdate=false;
											}
								     	}
										else if ((nowtime.month!=hd->ngaylap.month))
										{
											
											if(nowtime.year%4==0)//NEU LA NAM NHUAN
											{
												
													if(hd->ngaylap.month==2)
													{
														if((nowtime.month==3 && hd->ngaylap.day>=28 && nowtime.day<=2 ))
														{
																if(((nowtime.day+30)-hd->ngaylap.day)<=3)
																{
																	checkdate=true;
																}
																else
																{
																	checkdate=false;
																}
														}
														else
														{
															checkdate=false;
														}	
													}
													else if (hd->ngaylap.month!=2)
													{
														if(CheckThang31Ngay(hd->ngaylap.month)==true)
														{	
															 if((nowtime.month-hd->ngaylap.month)==1 && hd->ngaylap.day>=30 && nowtime.day<=2 )
															{
																	if(((nowtime.day+30)-hd->ngaylap.day)<2)
																	{
																		checkdate=true;
																	}
																	else
																	{
																		checkdate=false;
																	}
															}
															else
															{
																checkdate=false;
															}
														}
														else
														{
															if((nowtime.month-hd->ngaylap.month)==1 && hd->ngaylap.day>=29 && nowtime.day<=2 )
															{
																	if(((nowtime.day+30)-hd->ngaylap.day)<3)
																	{
																		checkdate=true;
																	}
																	else
																	{
																		checkdate=false;
																	}
															}
															else
															{
																checkdate=false;
															}
														}
													}
											}
										
											else if(nowtime.year%4!=0)//NEU KHONG PHAI LA NAM NHUAN
											{
													if(hd->ngaylap.month==2)
													{
															if((nowtime.month-hd->ngaylap.month)==1 && hd->ngaylap.day>=27 && nowtime.day<=2 )
															{
																	if(((nowtime.day+30)-hd->ngaylap.day)<=4)
																	{
																		checkdate=true;
																	}
																	else
																	{
																		checkdate=false;
																	}
															}
														else
														{
															checkdate=false;
														}	
													}
													else if (hd->ngaylap.month!=2)
													{
														if(CheckThang31Ngay(hd->ngaylap.month)==true)
														{	
															 if((nowtime.month-hd->ngaylap.month)==1 && hd->ngaylap.day>=30 && nowtime.day<=2 )
															{
																
																	if(((nowtime.day+30)-hd->ngaylap.day)<2)
																	{
																		checkdate=true;
																	}
																	else
																	{
																		checkdate=false;
																	}
															}
															else
															{
																checkdate=false;
															}
														}
														else
														{
															if((nowtime.month-hd->ngaylap.month)==1 && hd->ngaylap.day>=29 && nowtime.day<=2 )
															{
																	if(((nowtime.day+30)-hd->ngaylap.day)<3)
																	{
																		checkdate=true;
																	}
																	else
																	{
																		checkdate=false;
																	}
															}
															else
															{
																checkdate=false;
															}
														}
													}
											}
											
										}
										else 
										{
											if ( (nowtime.day-hd->ngaylap.day)>=3 )
												checkdate=false;
											else checkdate=true;	
										}
										
									// SAU KHI CHECK DATE	
									if(checkdate==true)
										{
												checkdate=true;
												string mavt;
												SetColor(36);
												cout<<"\n\n\n NHAP MA VAT TU CAN TRA: ";
												SetColor(48);
												fflush(stdin);
												getline(cin,mavt);
												mavt=chuanHoaChuoi(mavt);
												for(int j=0;j<hd->dscthd.n;j++)
												{
													if(strcmp(hd->dscthd.dshd[j].mavt.c_str(),mavt.c_str())==0)
													{
														*checkmavttontai=true;
														if(hd->dscthd.dshd[j].trangthai!=0)
														{
															hd->dscthd.dshd[j].trangthai=0;
															if(strcmp(hd->loai.c_str(),"X"))
															{	
																	hd->dscthd.dshd[j].soluong*=(-1);
																	ThemBotSoLuongVatTu(dsvt.ds,hd->dscthd.dshd[j]);
																	hd->dscthd.dshd[j].soluong*=(-1);
															}
															SetColor(42);
															cout<<"\n\n\n\t\t\t\t\t TRA HANG THANH CONG";
															cout<<"\n";
															Sleep(1500);
															SetColor(48);
													    }
													    else
													    {
													    	SetColor(36);
													    	cout<<"\n\n\t\t\t\t     HANG DA TRA ROI";	
													    	Sleep(1500);
													    	SetColor(48); 
														}
														break;	
													}
													
												}
												if(*checkmavttontai==false)
												{
															SetColor(36);
													    	cout<<"\n\n\n\t\t\t\t      VAT TU KHONG CO TRONG HOA DON";	
													    	Sleep(1500);
													    	SetColor(48); 
												}
		
										}
										else if(checkdate==false)
										{
											SetColor(36);
											cout<<"\n\n\t\t\t\t\t HOA DON DA HET HAN TRA HANG";
											cout<<"\n";
											Sleep(1500);
										}
								}
								}
							}
						}
						if(check==false)
						{
							TextResize(32);
							resizeConsole(1300,300);
							cout<<"\n\n\t\t\t\t ";
							ThongBaoLoi("KHONG TIM THAY HOA DON");
						}
	delete mahd;
						
}
void InHoaDon(Dsnhanvien dsnvien,Tree dsvt,string &mahd)
{
	bool *checktontai=new bool();
	*checktontai=false;
	for(int i=0;i<dsnvien.n;i++)
	{
		for(Hoadon *hd=dsnvien.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
		{
			if(strcmpi(hd->soHD.c_str(),mahd.c_str())==0)
			{
				SetColor(36);
				cout<<setw(50)<<"\t\t\tHOA DON THANH TOAN";
				cout<<"\n\n";
				cout<<setw(50)<<"\t\t  SO HOA DON:"<<hd->soHD;
				VeKhung(48,5,17,2);
				cout<<"\n\n\t\tLoai Hoa Don: ";
				SetColor(48);
				cout<<hd->loai;
				SetColor(36);
				cout<<"\n\t\tNgay Lap: ";
				SetColor(48);
				cout<< hd->ngaylap.day<<"/"<<hd->ngaylap.month<<"/"<<hd->ngaylap.year;
				SetColor(36);
				cout<<"\n\t\tMa Nhan Vien: ";
				SetColor(48);
				cout<<dsnvien.dsnv[i]->manv;
				SetColor(36);
				cout<<"\n\t\tTen Nhan Vien: ";
				SetColor(48);
				cout<<dsnvien.dsnv[i]->ho<<" "<<dsnvien.dsnv[i]->ten;

				SetColor(36);
				cout<<"\n";	
			    cout<<"\n\t"<<left<<setw(13)<<"Ma VT";
				cout<<left<<setw(15)<<"Ten VT";
				cout<<left<<setw(15)<<"So Luong";
				cout<<left<<setw(10)<<"VAT";
				cout<<left<<setw(15)<<"Don Gia";
				cout<<left<<setw(15)<<"Thanh Tien";
				cout<<left<<setw(5)<<"Trang Thai";
				SetColor(48);

				float sum=0;
				SetColor(48);
				cout<<"\n\t---------------------------------------------------------------------------------------------";
				for(int j=0;j<hd->dscthd.n;j++)
				{
					XuatChiTietHoaDon(dsvt,hd->dscthd.dshd[j]);
					sum+=(hd->dscthd.dshd[j].dongia*hd->dscthd.dshd[j].soluong)+(hd->dscthd.dshd[j].dongia*hd->dscthd.dshd[j].soluong*(hd->dscthd.dshd[j].vat/100));
				}
				cout<<"\n\t---------------------------------------------------------------------------------------------";
				cout<<"\n\t\t\t\t\t\t";
				cout<<setw(40)<<right<<"Tong Tien: "<<sum;
				cout<<"\n";
				*checktontai=true;
			}		
		}		
	}
	if(*checktontai==false)
	{
		resizeConsole(1300,300);
		cout<<"\n\n\t\t\t\t";
		ThongBaoLoi("HOA DON KHONG TON TAI! VUI LONG KIEM TRA LAI");
	}
	delete checktontai;
}
bool CheckHoaDonDungNgay(Date d1,Date d2,Date dc)
{
	//HOAN DOI GIA TRI KHI NHAP D1 LÀ FUTURE D2
	if(d1.year>d2.year)
	{
		swap(d1,d2);
	}
	else if(d1.year==d2.year &&d1.month>d2.month)
	{
		swap(d1,d2);
	}
	else if(d1.year==d2.year &&d1.month==d2.month && d1.day>d2.day)
	{
		swap(d1,d2);
	}


	if(d1.year<d2.year)
	{
		if(dc.year==d1.year && dc.month==d1.month && dc.day>=d1.day)
		{
			return true;
		}
		else if(dc.year==d1.year && dc.month>d1.month)
		{
			return true;
		}
		else if(dc.year>d1.year && dc.year<d2.year)
		{
			return true;
		}
		else if(dc.year==d2.year && dc.month<d2.month)
		{
			return true;
		}
		else if (dc.year==d2.year && dc.month==d2.month && dc.day<=d2.day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(d1.month<d2.month)
	{
		if(dc.year==d1.year && dc.month==d1.month && dc.day>=d1.day)
		{
			return true;
		}
		else if(dc.year==d1.year && dc.month>d1.month && dc.month<d2.month)
		{
			return true;
		}
		else if(dc.year==d1.year && dc.month==d2.month && dc.day<=d2.day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (d1.day<d2.day)
	{
		if(dc.year==d1.year && dc.month==d1.month && dc.day>=d1.day && dc.day<=d2.day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(dc.year==d1.year && dc.month==d1.month && dc.day==d1.day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
void VeBieuDoDoanhThu(long sum[],int nam)
{
	gotoxy(0,21);
	cout<<"(DOANH THU)";
    gotoxy(70,41);
	cout<<"(THANG)";
	liney(23,40,8);
	//DU LIEU
	int count=1;
	for(int i=0;i<24;i+=2)
	{
			if(i<16)
			{
					gotoxy(1,38-i);
					cout<<count<<"00 000";
			}
			gotoxy(count*5+7,41);
			cout<<count;
			count++;
	}
	linex(8,70,40);
	count=1;
	SetColor(18);
	for(int i=0;i<12;i++)
	{
		float check=sum[i]/100000;
		if(check>=8)
		{
			liney(24,39,count*5+6);
			liney(24,39,count*5+7);
			liney(24,39,count*5+8);
			linex(count*5+6,count*5+9,24);
		}
		else if (check<8 && check>7)
		{
			liney(25,39,count*5+6);
			liney(25,39,count*5+7);
			liney(25,39,count*5+8);
			linex(count*5+6,count*5+9,25);
		}
		else if ( check==7)
		{
			liney(26,39,count*5+6);
			liney(26,39,count*5+7);
			liney(26,39,count*5+8);
			linex(count*5+6,count*5+9,26);
		}
		else if ( check<7 && check >6)
		{
			liney(27,39,count*5+6);
			liney(27,39,count*5+7);
			liney(27,39,count*5+8);
			linex(count*5+6,count*5+9,27);
		}
		else if ( check ==6)
		{
			liney(28,39,count*5+6);
			liney(28,39,count*5+7);
			liney(28,39,count*5+8);
			linex(count*5+6,count*5+9,28);
		}
		else if ( check<6 && check >5)
		{
			liney(29,39,count*5+6);
			liney(29,39,count*5+7);
			liney(29,39,count*5+8);
			linex(count*5+6,count*5+9,29);
		}
				else if ( check==5)
		{
			liney(30,39,count*5+6);
			liney(30,39,count*5+7);
			liney(30,39,count*5+8);
			linex(count*5+6,count*5+9,30);
		}
		else if ( check<5 && check >4)
		{
			liney(31,39,count*5+6);
			liney(31,39,count*5+7);
			liney(31,39,count*5+8);
			linex(count*5+6,count*5+9,31);
		}
		else if ( check==4)
		{
			liney(32,39,count*5+6);
			liney(32,39,count*5+7);
			liney(32,39,count*5+8);
			linex(count*5+6,count*5+9,32);
		}
		else if ( check<4 && check >3)
		{
			liney(33,39,count*5+6);
			liney(33,39,count*5+7);
			liney(33,39,count*5+8);
			linex(count*5+6,count*5+9,33);
		}
		else if ( check==3)
		{
			liney(34,39,count*5+6);
			liney(34,39,count*5+7);
			liney(34,39,count*5+8);
			linex(count*5+6,count*5+9,34);
		}
		else if ( check<3 && check >2)
		{
			liney(35,39,count*5+6);
			liney(35,39,count*5+7);
			liney(35,39,count*5+8);
			linex(count*5+6,count*5+9,35);
		}
		else if ( check==2)
		{
			liney(36,39,count*5+6);
			liney(36,39,count*5+7);
			liney(36,39,count*5+8);
			linex(count*5+6,count*5+9,36);
		}
		else if ( check<2 && check>1)
		{
			liney(37,39,count*5+6);
			liney(37,39,count*5+7);
			liney(37,39,count*5+8);
			linex(count*5+6,count*5+9,37);
		}
		else if ( check==1)
		{
			liney(38,39,count*5+6);
			liney(38,39,count*5+7);
			liney(38,39,count*5+8);
			linex(count*5+6,count*5+9,38);
		}
		else if ( check<1 && check>0)
		{
			liney(39,39,count*5+6);
			liney(39,39,count*5+7);
			liney(39,39,count*5+8);
			linex(count*5+6,count*5+9,39);
		}
		count++;
	}
	gotoxy(33,43);
	SetColor(36);
	cout<<"BIEU DO DOANH THU NAM "<<nam;
	cout<<"\n\n";
	SetColor(48);

}
void ThongKeDoanhThu(Dsnhanvien dsnvien,int &nam)
{

	bool *checkdulieu=new bool();
	*checkdulieu=false;
	long sum[MAXMONTH];
	for(int i=1;i<13;i++)
	{
		sum[i]=0;
	}
	for(int i=0;i<dsnvien.n;i++)
	{
		for(Hoadon *hd=dsnvien.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
		{
			if(hd->ngaylap.year==nam)
			{
				for(int j=0;j<hd->dscthd.n;j++)
					{
						if(strcmpi(hd->loai.c_str(),"X")==0)
						{
							*checkdulieu=true;
							sum[hd->ngaylap.month]+=(hd->dscthd.dshd[j].dongia*hd->dscthd.dshd[j].soluong)+(hd->dscthd.dshd[j].dongia*hd->dscthd.dshd[j].soluong*(hd->dscthd.dshd[j].vat/100));
								
						}

					
				    }
			}			    
		}
	}
	if(*checkdulieu==true)
	{
			SetColor(36);
			cout<<"\n\t\t\t  "<< (char)219<<" BANG DOANH THU TRONG NAM "<<nam<< " "<< (char)219;
			cout<<"\n\n\t\t   THANG"<<"\t\t\t      DOANH THU";
			SetColor(48);
			cout<<"\n";
			for (int i=1;i<13;i++)
			{
				cout<<"\n\t\t  THANG "<<i<<" \t\t\t\t"<<sum[i];
			}
			VeBieuDoDoanhThu(sum,nam);
			gotoxy(100,100);
			cout<<" ";
			SetColor(42);
			Xu_Li_Con_Tro_Chi_Vi(0);
			cout<<"\n\t\t\t\t (NHAN ENTER DE TIEP TUC)"<<endl;
			SetColor(48);
	}
	else
	{
		TextResize(28);
		cout<<"\n\n\t\t\t   ";
		resizeConsole(1000,300);
		Xu_Li_Con_Tro_Chi_Vi(0);
		ThongBaoLoi("  KHONG CO DU LIEU");
		SetColor(42);
		cout<<"\n\n\t\t\t(NHAN ENTER DE TIEP TUC)"<<endl;
			SetColor(48);
	}
	delete checkdulieu;
}
void KetXuatHoaDon(Tree dsvt,Dsnhanvien dsnvien,Date d1,Date d2,int manv)
{
	bool *checkempty=new bool();
	*checkempty=false;
	SetColor(36);
	cout<<"\n\t\t\t    "<<(char)223<<" BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN "<<(char)223;
	cout<<"\n\n\n\tTu ngay:"<<d1.day<<"/"<<d1.month<<"/"<<d1.year<<"\t\t\t\t\t\tDen ngay:"<<d2.day<<"/"<<d2.month<<"/"<<d2.year;
	for(int i=0;i<dsnvien.n;i++)
	{
		for(Hoadon *hd=dsnvien.dsnv[i]->dshd.phead;hd!=NULL;hd=hd->pnext)
		{
			if(CheckHoaDonDungNgay(d1,d2,hd->ngaylap)==true && dsnvien.dsnv[i]->manv==manv)
			{
				resizeConsole(1300,700);
				SetColor(36);
				*checkempty=true;
				cout<<"\n\n\t\t\t\t\tNhan Vien: ";
				SetColor(48);
				cout<<dsnvien.dsnv[i]->ho<<" "<<dsnvien.dsnv[i]->ten;
				SetColor(36);
				cout<<"\n\tSo HD: ";
				SetColor(48);
				cout<<hd->soHD;
				SetColor(36);
				cout<<"\n\tNgay Lap: ";
				SetColor(48);
				cout<<hd->ngaylap.day<<"/"<<hd->ngaylap.month<<"/"<<hd->ngaylap.year;
				SetColor(36);
				cout<<"\n\tLoai: ";
				SetColor(48);
				cout<<hd->loai;
				SetColor(36);
				cout<<"\n\tMa Nhan Vien: ";
				SetColor(48);
				cout<<dsnvien.dsnv[i]->manv;
				cout<<"\n";
				XuatDanhSachChiTietHoaDon(dsvt,hd->dscthd);
				cout<<"\n\t\t___________________________________________________________________________";
				cout<<"\n";
			}
		}
	}
	if(*checkempty==false)
	{
		resizeConsole(1300,300);
		cout<<"\n\n\n\t\t\t     KHONG TON TAI HOA DON TRONG KHOANG THOI GIAN TREN!";
	}
	delete checkempty;
}
int menu(User &user)
{
	clrscr();
	int tt=0;//CHI RA DANG O THAO TAC NAO. HIEN TAI DANG O THAO TAC TT0 THAO TAC THU 1
	int *mau=new int[4];
	system("color F9");	
	//TRANG TRI 
	char a=219;	
	char b=220;
	char c=205;
	char d=188;
	char f=200;
	SetColor(48);
	TextResize(24);
	resizeConsole(900,600);
	Xu_Li_Con_Tro_Chi_Vi(0);
	int x;
	for(int i=0;i<4;i++)
	{
		if(i==0)
		{
		mau[i]=36;	
		}
		else
		mau[i]=48;
	}
	SetColor(36);
	cout<<"\n\t\t\t  "<<(char)a<<" B&D FURNITURE COMPANY "<<(char)a;
	cout<<"\n\n\t\t       "<<"    MAKE YOUR LIFE BE SO EASY  ";
		while(x!=27)
		{
				
					    SetColor(mau[0]);
						gotoxy(13,8);
						cout<<"NHAN VIEN";
						VeKhung(4,6,27,4);
						gotoxy(35,12);
						SetColor(12);
						cout<<(char)b<<(char)b<<(char)b<<(char)b<<(char)b<<(char)b;
						gotoxy(35,13);
						cout<<f<<c<<c<<c<<c<<d;
						
						
						SetColor(36);
						gotoxy(1,1);
					    cout<<"ID: "<<user.manv;
						
						SetColor(6);
						VeKhung(0,2,15,2);
						gotoxy(1,3);
					    cout<<"ESC: DANG XUAT";
						
						
						gotoxy(28,22);
						SetColor(48);
						cout<<"(NHAN ENTER DE THAO TAC)";
						
						
						SetColor(mau[2]);
						gotoxy(54,8);
						cout<<"HOA DON";
						VeKhung(43,6,27,4);
						
						SetColor(mau[1]);
						gotoxy(14,18);
						cout<<"VAT TU";
						VeKhung(4,16,27,4);
						
						
					 	SetColor(mau[3]);
						gotoxy(53,18);
						cout<<"DOANH THU";
						VeKhung(43,16,27,4);
						x=_getch();
						TRANGTHAI trangthai=key(x);
						switch(trangthai)
						{
						clrscr();
						SetColor(36);
						cout<<"\n\t\t\t  "<<(char)a<<" B&D FURNITURE COMPANY "<<(char)a;
						cout<<"\n\n\t\t       "<<"    MAKE YOUR LIFE BE SO EASY  ";
					    SetColor(mau[0]);
						gotoxy(13,8);
						cout<<"NHAN VIEN";
						VeKhung(4,6,27,4);
						gotoxy(35,12);
						SetColor(12);
						cout<<(char)b<<(char)b<<(char)b<<(char)b<<(char)b<<(char)b;
						gotoxy(35,13);
						cout<<f<<c<<c<<c<<c<<d;
						
						
						SetColor(36);
						gotoxy(1,1);
					    cout<<"ID: "<<user.manv;
						
						SetColor(6);
						VeKhung(0,2,13,2);
						gotoxy(1,3);
					    cout<<"ESC: DANG XUAT";
						
						
						gotoxy(28,22);
						SetColor(48);
						cout<<"(NHAN ENTER DE THAO TAC)";
						
						
						SetColor(mau[2]);
						gotoxy(54,8);
						cout<<"HOA DON";
						VeKhung(43,6,27,4);
						
						SetColor(mau[1]);
						gotoxy(14,18);
						cout<<"VAT TU";
						VeKhung(4,16,27,4);
						
						
					 	SetColor(mau[3]);
						gotoxy(53,18);
						cout<<"DOANH THU";
						VeKhung(43,16,27,4);
								case UP:
									{
										if(tt==0)
										{
											tt=1;
										}
										else if(tt==2)
										{
											tt=3;
										}
										else tt--;
										break;
									}
								case DOWN:
									{
										if(tt==1)
										{
											tt=0;
										}
										else if(tt==3)
										{
											tt=2;
										}
										else
										tt++;
										break;
									}
								case RIGHT:
								{
									if(tt==2)
									{
										tt=0;
									}
									else if(tt==3)
									{
										tt=1;
									}
									else
									{
										tt+=2;
									}
									break;
								} 
								
									case LEFT:
								{
									if(tt==0)
									{
										tt=2;
									}
									else if(tt==1)
									{
										tt=3;
									}
									else tt-=2;
									break;
								} 
								case ENTER:
								{
									
									return tt;
									
								}
								case EXIT:
								{
									tt=4;
									return tt;
								}
						 	
							
							}
									for(int	i=0;i<4;i++)
									{
										mau[i]=MAUCHU;
									}
									mau[tt]=MAUNEN;	
								
						
	}
	delete mau;
}
void GiaoDienNhanVien(fstream &file,Dsnhanvien &dsnvien,Dsvt &dsvt,Autoid &autoid,User &user,Dsuser &dsuser)
{
					char choose;
					while(1)	
					{
					clrscr();
					TextResize(26);
					resizeConsole(1100,500);
					Xu_Li_Con_Tro_Chi_Vi(0);
					SetColor(36);
					cout<<"\t\t\t           B&D FURNITURE COMPANY";
					cout<<"\n\t\t\t      ==============||=================";
					cout<<"\n\n\t\t\t            QUAN LI NHAN VIEN";
					cout<<"\n\n";
					SetColor(48);
					cout<<"\n\n\t\t"<<setw(23)<<left<<"1. Them Nhan Vien\t\t"<<setw(25)<<left<<"  2. Xuat Danh Sach Nhan Vien ";
					cout<<"\n\n";
					cout<<"\n\n\t\t"<<setw(23)<<left<<"3. Xoa Nhan Vien\t\t"<<setw(25)<<left<<" 4. Sua Thong Tin Nhan Vien ";
					cout<<"\n\n\t\t\t   "<<right<<setw(20)<<"0. Thoat"<<endl;
					cout<<"\n\n\t\t\t\t"<<right<<setw(20)<<"(NHAN SO DE THAO TAC)";
					choose=_getch();
							switch(choose)
							{
										case '0':
											{
												break;
												
											}
										case '1':
											{
												clrscr();
												TextResize(26);
												resizeConsole(1100,700);
												ThemDanhSachNhanVien(dsnvien,autoid);
												file.open("CTDL\\NHANVIEN.txt",ios_base::out);
											    GhiDanhSachNhanVien(file,dsnvien);		
											  	 file.close(); // dóng file NHANVIEN.TXT	
											
											    file.open("CTDL\\ID.txt",ios_base::out);
											    GhiAutoID(file,autoid);		
											    file.close(); // dóng file NHANVIEN.TXT	
											    break;
											}
										case '2':
											{
													string *search=new string();
													char a;
												    clrscr();
													resizeConsole(1100,700);
													XuatDanhSachNhanVien(dsnvien);	
													SetColor(6);
													VeKhung(0,2,13,2);
													gotoxy(1,3);
													cout<<"(TAB: THOAT)";													
													gotoxy(15,6);
													SetColor(36);
													cout<<"TIM KIEM: ";	
													gotoxy(15,0);	
													Xu_Li_Con_Tro_Chi_Vi(0);
													SetColor(48);										
													 while(1)
												    {
												    	
												    	if(_kbhit())
												    	{	
												    	clrscr();
												    	Xu_Li_Con_Tro_Chi_Vi(0);
												    
												    	a = _getch();
														if ( a==9) 
														{
															break;
														}
														else if(a == 13)
														{
															
														}
														else if (a ==8)
														{
															if(search->empty()!=true)
															{
																cout<<"\b \b";
																*search = search->substr(0, search->size()-1);
															}
														}
														else
														{
															search->push_back(a);
														}
														gotoxy(25,5);
														cout<<*search;
														string *temp=new string();
														*temp=*search;
														*temp=chuanHoaChuoi(*temp);
														TimNhanVien(dsnvien,*temp);
														gotoxy(15,0);
														delete temp;
												    };
													
													}
													delete search;
												break;
										}
										case '3':
											{
												clrscr();
												resizeConsole(1100,700);
												XuatDanhSachNhanVien(dsnvien);
												cout<<"\n";
												XoaNhanVien(dsnvien,user,dsuser);
												file.open("CTDL\\NHANVIEN.txt",ios_base::out);
											    GhiDanhSachNhanVien(file,dsnvien);		
											    file.close(); // dóng file SINHVIEN.TXT	
											    break;
											}
										case '4':
											{
												clrscr();
												resizeConsole(1100,700);
												SetColor(48);
												XuatDanhSachNhanVien(dsnvien);
												SuaThongTinNhanVien(dsnvien);
												file.open("CTDL\\NHANVIEN.txt",ios_base::out);
											    GhiDanhSachNhanVien(file,dsnvien);		
											    file.close(); // dóng file SINHVIEN.TXT	
											    break;
											}
										default: break;
								  }
								if(choose==48)
								{
									break;
								}
					};
}
void GiaoDienVatTu(fstream &file,Dsnhanvien &dsnvien,Dsvt &dsvt)
{
							char choose;
							while(1)	
							{
								clrscr();
								TextResize(26);
								resizeConsole(1000,500);
								Xu_Li_Con_Tro_Chi_Vi(0);
								SetColor(36);
								cout<<"\t\t\t          B&D FURNITURE COMPANY";
								cout<<"\n\t\t\t    ==============||=================";
								cout<<"\n\n\t\t\t          QUAN LI KHO VAT TU";
								cout<<"\n\n";
								SetColor(48);
								cout<<"\n\n\t\t"<<setw(23)<<left<<"1. Them Vat Tu\t"<<setw(25)<<left<<"\t  2. Xuat Danh Sach Vat Tu ";
								cout<<"\n\n";
								cout<<"\n\n\t\t"<<setw(23)<<left<<"3. Xoa Vat Tu\t"<<setw(25)<<left<<"\t  4. Sua Thong Tin Vat Tu ";
								cout<<"\n\n\t\t\t"<<right<<setw(20)<<"0. Thoat"<<endl;
								cout<<"\n\n\t\t\t     "<<right<<setw(20)<<"(NHAN SO DE THAO TAC)";
								choose=_getch();
								switch(choose)
									{			
													case '0':
														{
															break;	
														}
													case '1':
														{
															clrscr();
															SetColor(36);
															cout<<"\t\t      =========NHAP THONG TIN VAT TU==============";
															SetColor(48);
															ThemDanhSachVattu(dsvt);
															file.open("CTDL\\VATTU.txt",ios_base::out);
															GhiDanhSachVatTu(file,dsvt.ds);	
															file.close(); // dóng file SINHVIEN.TXT	
															break;
														}
													case '2':
														{
															clrscr();
															string *search=new string();
															int count=0;
															char a;
															 TextResize(22);
														 	resizeConsole(1000,700);
															SetColor(36);
																    	cout<<"\n\t\t\t\t    DANH SACH VAT TU"<<endl;
																		cout<<"\t\t\t      =============||==============="<<endl;
																		cout<<"\n\n\n              TIM KIEM: ";		
																		gotoxy(4,8);																	
																		cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
																		cout<<"\n";
																		SetColor(48);
																		gotoxy(25,9);
																		XuatDanhSachVatTu(dsvt.ds);	
																		gotoxy(25,0);
																		SetColor(6);
																		VeKhung(0,2,13,2);
																		gotoxy(1,3);
																		cout<<"(TAB: THOAT)";
																		Xu_Li_Con_Tro_Chi_Vi(0);
																		SetColor(48);
																		gotoxy(25,0);								
																	 while(1)
																    {	
																    	
																    	if(_kbhit())
																    	{	
																    	
																    	clrscr();
																    	Xu_Li_Con_Tro_Chi_Vi(0);
																    	SetColor(36);
																    	cout<<"\n\t\t\t\t    DANH SACH VAT TU"<<endl;
																		cout<<"\t\t\t      =============||==============="<<endl;
																		cout<<"\n\n\n              TIM KIEM: ";		
																		gotoxy(4,9);
																		cout<<"";																	
																		cout<<setw(15)<<left<<"MA VAT TU"<<setw(24)<<left<<"TEN VAT TU"<<setw(20)<<left<<"DON VI TINH"<<setw(20)<<"SO LUONG TON";
																		cout<<"\n";
																		SetColor(6);
																		VeKhung(0,2,13,2);
																		gotoxy(1,3);
																		cout<<"(TAB: THOAT)";
																		SetColor(48);
																		gotoxy(25,0);
																		a = _getch();
																		if ( a==9 ) 
																		{
																			break;
																		}
																		else if (a==13)
																		{
																			
																		}
																		else if (a ==8)
																		{
																			if(search->empty()!=true)
																			{
																				cout<<"\b \b";
																				*search = search->substr(0, search->size()-1);
																			}
																		}
																		else
																		{
																			search->push_back(a);
																		}
																		gotoxy(23,6);
																		cout<<*search;
																		string *temp=new string();
																		*temp=*search;
																		*temp=chuanHoaChuoi(*temp);
																		gotoxy(25,9);
																		TimVatTu(dsvt.ds,*temp);
																		gotoxy(4,0);
																		delete temp;
																   		 };
															}
															delete search;
															break;
														}
														
													case '3':
													{
															clrscr();
															TextResize(22);
															resizeConsole(1000,700);
															ChonMaVatTuDeXoa(dsnvien,dsvt);			
															break;
														}
													case '4':
														{
															clrscr();
															TextResize(22);
															resizeConsole(1000,700);
															ChonMaVatTuDeSua(dsnvien,dsvt);
																break;
													    	}
											  		 }
											if(choose==48)
											{
												break;
											}   
								};
}
void GiaoDienHoaDon(fstream &file,Dsnhanvien &dsnvien,Dsvt &dsvt,Autoid &autoid, Date &nowtime,User &user)
{
	char p2;
							while(1)	
							{
								clrscr();
								TextResize(29);
								resizeConsole(1300,550);
								SetColor(36);
								Xu_Li_Con_Tro_Chi_Vi(0);
								cout<<"\t\t\t\t        B&D FURNITURE COMPANY";
								cout<<"\n\t\t\t\t  ==============||=================";
								cout<<"\n\n\t\t\t\t         QUAN LI HOA DON";
								cout<<"\n\n";
								SetColor(48);
								cout<<"\n\n\t\t  "<<setw(28)<<left<<"1. Lap Hoa Don\t"<<setw(25)<<left<<"\t      2. In Hoa Don ";
								cout<<"\n\n";
								cout<<"\n\n\t\t  "<<setw(28)<<left<<"3. Tra Hang\t"<<setw(25)<<left<<"\t      4. Liet Ke Hoa Don ";
								cout<<"\n\n\t\t\t     "<<right<<setw(20)<<"0. Thoat"<<endl;
								cout<<"\n\n\t\t\t\t   "<<right<<setw(20)<<"(NHAN SO DE THAO TAC)";
								p2=_getch();
									switch(p2)
									{
										TextResize(26);
										case '0':
											{
											break;
											}
										case '1':
											{
											clrscr();
											TextResize(26);
											resizeConsole(1300,600);
												Hoadon x;
												bool *checkghi=new bool();
											    ThemVaoDanhSachHoaDon(dsvt,x,nowtime,autoid,*checkghi,user);	
											    if(*checkghi==true)
											    {
											    CapNhatSoLuong(dsvt,x);
											    file.open("CTDL\\ID.txt",ios_base::out);
											    GhiAutoID(file,autoid);		
											    file.close(); 
											    
											    file.open("CTDL\\HOADON.txt",ios_base::app);			
												GhiHoaDon(file,x,user)	;
											    file.close(); 
											    
											    file.open("CTDL\\VATTU.txt",ios_base::out);
												GhiDanhSachVatTu(file,dsvt.ds);	
												file.close();
												
												file.open("CTDL\\NHANVIEN.txt",ios_base::in);
												DocDanhSachNhanVien(file,dsnvien);
												file.close();
												}
												delete checkghi;
											break;
										}
										
										case '2':
										{
										string *mahd=new string();
										clrscr();
										TextResize(26);
										SetColor(36);
									    cout<<"\n\t\t\t\t    "<<(char)219<<" IN HOA DON THANH TOAN "<<(char)219<<endl;
									    cout<<"\t\t\t         ==============||==============="<<endl;
										cout<<"\n\nNHAP MA HOA DON CAN IN: ";
										fflush(stdin);
										SetColor(48);
										getline(cin,*mahd);
										*mahd=chuanHoaChuoi(*mahd);	
										clrscr();
										resizeConsole(1300,700);
										SetColor(36);
										cout<<setw(60)<<"\t\tB&D FURNITURE COMPANY "<<endl;
										cout<<setw(60)<<"\t\t ==============||=================";
										cout<<"\n\n\n";
										InHoaDon(dsnvien,dsvt.ds,*mahd);
										SetColor(42);
										cout<<"\n\n\t\t\t\t        (NHAN ENTER DE TIEP TUC)"<<endl;
										SetColor(48);
										system("pause");
										delete mahd;
										break;
											}
										case '3':
											{
												TextResize(26);
												resizeConsole(1300,300);
												clrscr();
												bool *checkdate=new bool();
												GetCurrentlyTime(nowtime);
												DoiTraHang(dsnvien,dsvt,*checkdate,nowtime);
												if(*checkdate==true)
												{
												file.open("CTDL\\VATTU.txt",ios_base::out);
												GhiDanhSachVatTu(file,dsvt.ds);	
												file.close();
												
												file.open("CTDL\\HOADON.txt",ios_base::out);
												GhiDanhSachHoaDonFull(file,dsnvien,user);	
												file.close();
												}
												delete checkdate;
												break;
											}
											
										case '4':
													string *tempday=new string();
													string *tempmonth=new string();
													string *tempyear=new string();
													string *tempstring=new string();
													int flag,manv;
													bool checkint;
													Date d1,d2;
													TextResize(26);
													resizeConsole(1300,300);
													//CHECK MA NHAN VIEN
														do
														{
															clrscr();
															SetColor(36);
														    cout<<"\t\t\t\t      "<<(char)219<<" LIET KE DANH SACH HOA DON "<<(char)219;
															cout<<"\n\n\n\tNHAP MA NHAN VIEN: ";
															SetColor(48);
															fflush(stdin);
															getline(cin,*tempstring);
															if(checkInt(*tempstring)==true)
															{
																	ConvertStringToInt(*tempstring,manv);
																	checkint=true;
																	flag=CheckMaNVTonTai(dsnvien,manv);
																	if(flag==0)
																	{
																		SetColor(36);
																		cout<<"\n\t\t\tMA NHAN VIEN KHONG TON TAI! VUI LONG NHAP LAI";
																		Sleep(500);
																		SetColor(48);
																	}
															}
															else
															{
																	SetColor(36);
																	cout<<"\n\t\t\t\tMA NHAN VIEN KHONG HOP LE! VUI LONG NHAP LAI";
																	Sleep(500);
																	SetColor(48);
																	checkint=false;
															}
														}while(checkint==false || flag==0);
												
													//CHECK NGAY
													do
													{
															clrscr();
															SetColor(36);
														    cout<<"\t\t\t\t      "<<(char)219<<" LIET KE DANH SACH HOA DON "<<(char)219;
															SetColor(36);
															cout<<"\n\n\n\tNHAP MA NHAN VIEN: ";
															SetColor(48);
															cout<<manv;
															gotoxy(25,4);
															SetColor(36);
															cout<<"\n\t    TU NGAY:  ";
																SetColor(48);
																gotoxy(21,5);
																//cin>>d1.day;
																fflush(stdin);
																getline(cin,*tempday);
																gotoxy(24,5);
																cout<<"/";
																
																gotoxy(26,5);
																//cin>>d1.month;
																fflush(stdin);
																getline(cin,*tempmonth);
																gotoxy(29,5);
																cout<<"/";
																
																
																gotoxy(30,5);
																//cin>>d1.year;
																fflush(stdin);
																getline(cin,*tempyear);
																if(checkInt(*tempday)==false || checkInt(*tempmonth)==false || checkInt(*tempyear)==false  )
																{
																	checkint=false;
																	cout<<"\n\t\t\t";
																	ThongBaoLoi("NGAY KHONG HOP LE VUI LONG NHAP LAI");
																	clrscr();
																}
																else
																{
																	checkint=true;
																	ConvertStringToInt(*tempday,d1.day);
																	ConvertStringToInt(*tempmonth,d1.month);
																	ConvertStringToInt(*tempyear,d1.year);
																	if(CheckDate(d1)==false)
																	{
																		checkint=false;
																		cout<<"\n\t\t\t        ";
																		ThongBaoLoi(" KHONG HOP LE VUI LONG NHAP LAI");	
																		clrscr();
																		
																	}
																	else
																	{
																	do
																			{
																				
	
																					SetColor(36);
																					gotoxy(70,5);
																					cout<<"DEN NGAY:  ";
																					SetColor(48);
																					gotoxy(80,5);
																					fflush(stdin);
																					getline(cin,*tempday);
																					gotoxy(83,5);
																					cout<<"/";
																				
																					gotoxy(85,5);
																					fflush(stdin);
																					getline(cin,*tempmonth);
																					gotoxy(88,5);
																					cout<<"/";
																				
																					gotoxy(89,5);
																					fflush(stdin);
																					getline(cin,*tempyear);
																					
																				if(checkInt(*tempday)==false || checkInt(*tempmonth)==false || checkInt(*tempyear)==false )
																				{
																					checkint=false;
																					SetColor(36);
																					cout<<"\n\t\t\t        NGAY KHONG HOP LE VUI LONG NHAP LAI";
																					Sleep(500);
																					clrscr();
																				}
																				else
																				{
																					checkint=true;
																					ConvertStringToInt(*tempday,d2.day);
																					ConvertStringToInt(*tempmonth,d2.month);
																					ConvertStringToInt(*tempyear,d2.year);
																					if(CheckDate(d2)==false)
																					{
																							checkint=false;
																							SetColor(36);
																							cout<<"\n\t\t\t        NGAY KHONG HOP LE VUI LONG NHAP LAI";
																							Sleep(600);
																							clrscr();
																								SetColor(36);
																							    cout<<"\n\t\t\t\t      "<<(char)219<<" LIET KE DANH SACH HOA DON "<<(char)219;
																								gotoxy(25,4);
																								cout<<"\n\t    TU NGAY:  ";
																								SetColor(48);
																								gotoxy(21,5);
																								cout<<d1.day;
																								gotoxy(24,5);
																								cout<<"/";
																								
																								gotoxy(26,5);
																								cout<<d1.month;
																								gotoxy(29,5);
																								cout<<"/";
																								
																								gotoxy(30,5);
																								cout<<d1.year;					
																					}
																					else
																					{
																						break;
																					}
																				}
																			
																			}while(checkint==false);
																	}
																}
																
																if(checkint==true)
																{
																	break;
																}
													}while(checkint==false);
													clrscr();
													resizeConsole(1300,800);
													KetXuatHoaDon(dsvt.ds,dsnvien,d1,d2,manv);
													SetColor(42);
													cout<<"\n\n\t\t\t\t     (NHAN ENTER DE TIEP TUC)";
													SetColor(48);
													delete tempday,tempmonth,tempyear;
													cout<<"\n\n";
													system("pause");
												
											gotoxy(0,0);
											delete tempstring;
											break;
									};
									if(p2==48)
									{
										break;
									}
							};
}
void GiaoDienDoanhThu(Dsnhanvien &dsnvien)
{
					clrscr();
					string *tempstring=new string();
					bool *checkint=new bool();
					int flag;
					int nam,manv;
					TextResize(24);
					resizeConsole(1000,400);		
					do
					{
							clrscr();
							SetColor(36);
							cout<<"\t\t                   B&D FURNITURE COMPANY";
							cout<<"\n\t\t           ================||=================";
							cout<<"\n\n\n\t\t\t     "<<(char)219<<" BANG THONG KE DOANH THU "<<(char)219 ;
							SetColor(48);
							cout<<"\n\n";
							cout<<"\n\n\t NHAP NAM CAN TRA: ";
							gotoxy(27,8);
							fflush(stdin);
							getline(cin,*tempstring);
							*checkint=checkInt(*tempstring);
							if(*checkint==true)
							{
								ConvertStringToInt(*tempstring,nam);
							}
							else
							{
								cout<<"\n\t\t\t\t";
								ThongBaoLoi("NAM KHONG HOP LE! VUI LONG NHAP LAI");
							}
					}while(*checkint==false);

					clrscr();
					resizeConsole(1000,800);	
					ThongKeDoanhThu(dsnvien,nam);
					delete checkint,tempstring;
					system("pause");
}
int main()
{
	int choose;
	Dsuser dsuser;
	fstream file;
	Dsvt dsvt;
	Autoid autoid;
	int p;
	Dsnhanvien dsnvien;
	Date nowtime;
	GetCurrentlyTime(nowtime);
				//Doc Auto ID
	file.open("CTDL\\ID.txt",ios_base::in);
	DocAutoID(file,autoid);
	file.close();
				// Doc Vat Tu
	file.open("CTDL\\VATTU.txt",ios_base::in);
	DocDanhSachVatTu(file,dsvt);
	file.close(); // dóng file VATTU.TEXT
				// Doc Nhan Vien
	file.open("CTDL\\NHANVIEN.txt",ios_base::in);
	DocDanhSachNhanVien(file,dsnvien);
	file.close();	
				// Doc Login
	file.open("CTDL\\LOGIN.txt",ios_base::in);
	DocDanhSachLogin(file,dsuser);
	file.close();
	
	while(1)
	{
			User user;
			Login(user);
			do
			{
			p=0;
			p=menu(user);
			if(p==0)
			{
			GiaoDienNhanVien(file,dsnvien,dsvt,autoid,user,dsuser);
	     	}	
		   	else if(p==1)
		    {
		     	GiaoDienVatTu(file,dsnvien,dsvt);
			}
			else if(p==2)
			{
			Xu_Li_Con_Tro_Chi_Vi(0);
			GiaoDienHoaDon(file,dsnvien,dsvt,autoid,nowtime,user);
			}
			else if (p==3)
			{
			GiaoDienDoanhThu(dsnvien);
			}
			else if(p==4)
			{
				break;
			}			
	}while(p!=4);
	};
	return 0;
}
