#include<iostream>
#include<time.h>
#include<fstream>
#include<Windows.h>
#include<cstring>
#include<cmath>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void Hide_Cursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
    SetConsoleCursorInfo(hConsole, &cursor_info);
}

void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    
    SetConsoleCursorPosition(hConsole, pos);

}

struct acg
{
	string name;
	double iyear;
	double imon;
	double iday;
	double net; 
	double hot;
	double epi;
	double cyear;
	double fgrade;
	double grade; 
	acg* next;
};

class pro
{
	acg* head;
	acg* bf;
	acg* nmt;
	acg* tail;
	int times;
	fstream timesfile; 
	public:
		pro()
		{
			head = NULL;
			tail = NULL;
			bf = NULL;
			nmt = NULL;			
			timesfile.open("times.txt", ios::in);
			timesfile >> times;
			timesfile.close();
			
		}
		~pro()
		{
			
			
			timesfile.close();			
		}
		void insert()//加动漫 
		{
			acg* p;
			ofstream fs("D:\\文件\\编程\\C++\\随手编的\\补番计划.txt",ios::app);
			tm *ptr;
			time_t t = time(NULL);
			ptr = localtime(&t);
			p = new acg;
			p -> iyear = ptr -> tm_year + 1900;
			p -> imon = ptr -> tm_mon + 1;
			p -> iday = ptr -> tm_mday;
			cout << "name:";
			cin >> p -> name;
			cout << "hot:";
			cin >> p -> hot;
			cout << "epi:"; 
			cin >> p -> epi;
			cout << "cyear:";
			cin >> p -> cyear;
			getgrade(*p);
			p -> fgrade = p -> grade;
			fs << p -> name << '\t' 
			   << p -> iyear << '\t' 
			   << p -> imon << '\t' 
			   << p -> iday << '\t' 
			   << p -> hot << '\t' 
			   << p -> epi << '\t' 
			   << p -> cyear << '\t'
			   << p -> grade << endl;
			p -> next = NULL;
			tail -> next = p;
			tail = p;
		}
		void getgrade(acg& p)//****************************************************************分数 
		{
			tm *ptr;
			time_t t = time(NULL);
			ptr = localtime(&t);
			double net = (ptr -> tm_year + 1900 - p.iyear) * 12 + (ptr -> tm_mon + 1 - p.imon) + (ptr -> tm_mday - p.iday) / 30;
			net = abs(net) + 1;
		//	if(p.epi >= 30)
		//	{
				//net += net * net / p.epi;
		//	} 
			p.net = net; 
			if(p.net <= 12 && p.net > 6)
			{
				p.net = 2 * p.net - 6;
			}
			else if(p.net > 12)
			{
				//p.net += (p.net * p.net / 12) + p.net - 12;
				p.net = p.net * p.net - 22 * p.net + 138; //***********************************************************************************************************
			}  
			p.grade = (net * p.hot) / (p.epi * 3 + ptr->tm_year + 1900 - p.cyear);
			p.grade *= 100;
			if(ptr->tm_year + 1900 - p.cyear + 1) 
			{
				p.grade += p.hot / (ptr->tm_year + 1900 - p.cyear + 1);
			}
			else
			{
				p.grade += p.hot * 2;
			}
			int jx = 20;
			int lx = times;
			for(int jk = lx; jk > 0; jk --)
			{ 
				jx = 35 * jk;
				if(p.grade > jx)
				{
					int h = p.grade / jx;
					double k = 0;
					for(int i = h; i > 0; i --)
					{
						k += p.grade - jx * i;
						k /= (i + 1.00000);					
					}
					p.grade = jx + k;
				} 
			}
			if(p.grade >= 100)
			{
				times += int(p.grade / 100);
				timesfile.open("times.txt", ios::out);
				timesfile << times;
				timesfile.close();
			}
		}
		void create()//创建链表 
		{
			acg* p1;
			acg* p2;
			p1 = p2 = new acg;
			ifstream fin("D:\\文件\\编程\\C++\\随手编的\\补番计划.txt");
			while(!fin.eof())
			{
				fin >> p1 -> name 
					>> p1 -> iyear 
					>> p1 -> imon 
					>> p1 -> iday 
					>> p1 -> hot 
					>> p1 -> epi 
					>> p1 -> cyear
					>> p1 -> fgrade;
				getgrade(*p1);
				if(head == NULL)
				{
					head = p1;
				}
				else
				{
					p2 -> next = p1; 
				}
				p2 = p1;
				p1 = new acg;
			}
			p2 -> next = NULL;
			fin.close();
			p2 = head;
			while(p2)
			{
				if(p2 -> next -> next == NULL)
				{
					tail = p2;
					p2 -> next = NULL;
				}
				p2 = p2 -> next;
			}
		}
		void text(int kbk)//要看动漫之后的操作 
		{			
			tm *ptr;
			time_t t = time(NULL);
			ptr = localtime(&t);
			acg* p;
			if(kbk)
			{
				ofstream fs("D:\\文件\\编程\\C++\\随手编的\\seen.txt",ios::app);
				fs << "已于 " << ptr -> tm_year + 1900 << "年" <<  ptr -> tm_mon + 1 << "月" << ptr -> tm_mday << "日开始看:" 
				   << nmt -> name << endl;
				fs << "开始想看的日期:" << nmt -> iyear << "年" 
				   << nmt -> imon << "月" 
				   << nmt -> iday << "日\n当年热度:" 
				   << nmt -> hot << "\n集数:" 
				   << nmt -> epi << "\n最后更新年份:" 
				   << nmt -> cyear << "\n观看指数："  
					<< nmt -> grade << '\n' << endl;				
				if(nmt == head)
				{
					p = head;
					head = head -> next;
					delete p;
				}
				else
				{
					if(tail == nmt)
					{
						tail = bf;
					}
					p = nmt;
					bf -> next = nmt -> next;
					delete p;
				}
			}
			else
			{
				nmt -> iyear = ptr -> tm_year + 1900;
				nmt -> imon = ptr -> tm_mon + 1;
				nmt -> iday = ptr -> tm_mday;
				nmt -> fgrade = nmt -> grade;
				if(nmt == head)
				{
					//p = head;
					head = head -> next;
					//delete p;
				}
				else
				{
					if(tail == nmt)
					{
						return;
						//tail = bf;
					}
					//p = nmt;
					bf -> next = nmt -> next;
					//delete p;
				}
				getgrade(*nmt);
				tail -> next = nmt;
				tail = nmt;
				nmt -> next = NULL;
			}
			ofstream fout("D:\\文件\\编程\\C++\\随手编的\\补番计划.txt");
			acg* p2 = head;
			while(p2)
			{
				fout << p2 -> name << '\t' 
				     << p2 -> iyear << '\t' 
					 << p2 -> imon << '\t' 
					 << p2 -> iday << '\t' 
					 << p2 -> hot << '\t' 
					 << p2 -> epi << '\t' 
			    	 << p2 -> cyear << '\t'
			    	 << p2 -> fgrade << endl;
			    p2 = p2->next;
			}
		}
		bool nextbig(int i, int no)//下一个最大 
		{
			double nd = nmt -> grade;
			string bigname = nmt -> name;
			acg* p1 = NULL;
			acg* p2 = head;
			nmt = new acg;
			nmt -> grade = 0;
			while(p2)
			{
				if(p2 -> grade > nmt -> grade && p2 -> grade < nd)
				{
					nmt = p2;
					bf = p1;	
				}
				p1 = p2;
				p2 = p2 -> next;
			}
			gotoxy(0, i);
			cout << "\n\n其中最为推荐的是：" << nmt -> name << "                                   " << endl;
			cout << "开始想看的时间：" << nmt -> iyear << "年" << nmt -> imon <<"月" << nmt -> iday << "日   " << endl;
			cout << "这是 " << nmt -> cyear << " 年的动漫" << endl;
			cout << "共有 " << nmt -> epi << " 集" <<endl;
			cout << "网友评分：" << nmt -> hot <<  '\t' << endl;
			cout << "推荐指数：" << nmt -> grade << '\t' << endl;
			cout << "这是排第 " << no << endl;
			float disg = nd - nmt -> grade;
			cout << "距第 " << no - 1 << " 还差 " << disg << " 分\t\t\t" << endl; 
			char a;
			a = getch();
			if(a == '3')
			{
				return false;
			} 
			else if(a == '1')
			{
				text(1);
				return false;
			}
			else if(a == '2')
			{
				text(0);
				return false;
			}
			else
			{
				return true;
			}
		}
		void choose()//动漫详情 
		{
			acg* p2 = head;
			acg* p1 = NULL;
			nmt = p2;
			int i = 0; 
			int nday = 1;
			int year = head -> iyear;
			int month = head -> imon;
			int day = head -> iday;
			cout << year << '.' << month << '.' << day << endl;
			gotoxy(25, 0);
			cout << "年份\t热度\t集数\t|\t推荐\t初始\t增长" << endl;
			while(p2)
			{
				if(p2 -> iyear != year || p2 -> imon != month || p2 -> iday != day)
				{
					nday ++;
					year = p2 -> iyear;
					month = p2 -> imon;
					day = p2 -> iday;
					cout << year << '.' << month << '.' << day << endl;//输出********************************************************
				}
				cout << p2 -> name;
				gotoxy(25, nday + i ++);
				cout.precision(4);
				cout << p2 -> cyear << "\t" << p2 -> hot << "\t" << p2 -> epi << "\t|\t";
				cout.precision(3);
				cout << p2 -> grade << "\t" << p2 -> fgrade << "\t";
				if(p2 -> grade - p2 -> fgrade < 0.01)
				{
					cout << '0';
				}
				else
				{
					cout << p2 -> grade - p2 -> fgrade;
				} 
				cout << endl; 
				if(p2 -> grade > nmt -> grade)
				{
					nmt = p2;
					bf = p1;	
				}
				p1 = p2;
				p2 = p2 -> next;
			}
			cout << "共有这么" << i << "部我想看的动漫" << endl;
			cout.precision(6);
			cout << "\n\n其中最为推荐的是：" << nmt -> name << endl;
			cout << "开始想看的时间：" << nmt -> iyear << "年" << nmt -> imon <<"月" << nmt -> iday << "日" << endl;
			cout << "这是 " << nmt -> cyear << " 年的动漫" << endl;
			cout << "共有 " << nmt -> epi << " 集" <<endl; 
			cout << "网友评分：" << nmt -> hot << endl;
			cout << "推荐指数：" << nmt -> grade << endl;
			cout << "\n\n\n如果你选择观看，将自动将这部动漫从列表删除，是否观看？" << endl;
			cout << "1:看\n2:不看\n3:返回\n任意键:跳过" << endl;
			if(nmt -> grade < 80)
			{
				times -= (80 - nmt -> grade) / 10;
				timesfile.open("times.txt", ios::out);
				timesfile << times;
				timesfile.close();
			}
			char a;
			a = getch();
			if(a == '1')
			{
				text(1);
			}
			if(a == '2')
			{
				text(0);
			}
			if(a == '3')
			{
				return;
			}
			else
			{
				int no = 2;
				while(nextbig(i + 1 + nday, no ++));
			} 
		}
		void select()
		{
			system("cls");
			cout << "1:name\n2:iday\n3:hot\n4:cyear\n5:grade" << endl;
			char a;
			a = getch();
			system("cls");
			acg* p = head;
			acg* pb = NULL;
			switch(a)
			{
				case '1':
				{
					cout << "输入name:"; 
					string b;
					cin >> b;
					while(p)
					{
						if(p -> name == b)
						{
							nmt = p;
							bf = pb;
							cout << p -> name << '\n' 
					     		 <<"想看的时间为："<< p -> iyear << "年" 
			   			 		 << p -> imon << "月" 
			   			 		 << p -> iday << "日\n" 
			   			 		 << "当年的热度为:"<< p -> hot << '\n' 
			   			 		 << "共有 "<< p -> epi << " 集\n" 
			    		 		 << "出番时间:" << p -> cyear << "年\n"
							     << "当时的推荐指数:" << p -> fgrade << '\n' 
			    		 		 << "现在的推荐指数:" << p -> grade << endl;
			    		 	cout << "\n\n如果你选择观看，将自动将这部动漫从列表删除，是否观看？" << endl;
							cout << "1:看\n2:不看" << endl;
							char b;
							b = getch();
							if(b == '1')
							{
								text(1);
							}
			    			break;
						}
						pb = p;
						p = p -> next;
					}
					if(p == NULL)
					{
						cout << "查无此动漫" << endl; 
						getch();
					}
					break;
				}
				case '2':
				{
					int i = 0;
					cout << "输入iyear:";
					int d[3];
					cin >> d[0];
					cout << "输入imon:";
					cin >> d[1];
					cout << "输入iday:";
					cin >> d[2];
					while(p)
					{
						if(p -> iyear == d[0] && p -> imon == d[1] && p -> iday == d[2])
						{
							i ++;
							cout << p -> name << '\n' 
					     		 <<"想看的时间为："<< p -> iyear << "年" 
			   			 		 << p -> imon << "月" 
			   			 		 << p -> iday << "日\n" 
			   			 		 << "当年的热度为:"<< p -> hot << '\n' 
			   			 		 << "共有 "<< p -> epi << " 集\n" 
			    		 		 << "出番时间:" << p -> cyear << "年\n"
							     << "当时的推荐指数:" << p -> fgrade << '\n' 
			    		 		 << "现在的推荐指数:" << p -> grade << endl;
			    		 	cout << endl;
						}
						p = p -> next;
					} 
					cout << "当天加入的动漫共有 " << i << " 部" << endl;
					getch(); 
					break;
				}
				case '3':
				{
					double hmax;
					double hmin;
					int i = 0;
					cout << "输入hotmax:";
					cin >> hmax;
					cout << "输入hotmin:";
					cin >> hmin;
					while(p)
					{
						if(p -> hot >= hmin && p -> hot <= hmax)
						{
							i ++;
							cout << p -> name << '\n' 
					     		 <<"想看的时间为："<< p -> iyear << "年" 
			   			 		 << p -> imon << "月" 
			   			 		 << p -> iday << "日\n" 
			   			 		 << "当年的热度为:"<< p -> hot << '\n' 
			   			 		 << "共有 "<< p -> epi << " 集\n" 
			    		 		 << "出番时间:" << p -> cyear << "年\n"
							     << "当时的推荐指数:" << p -> fgrade << '\n' 
			    		 		 << "现在的推荐指数:" << p -> grade << endl;
			    		 	cout << endl;
						}
						p = p -> next;
					} 
					cout << "热度在 " << hmin << " 到 " << hmax <<" 之间的共有 " << i << " 部" << endl; 
					getch();
					break;
				}
				case '4':
				{
					int cy;
					cout << "输入cyear:";
					cin >> cy;
					int i = 0;
					while(p)
					{
						if(p -> cyear == cy)
						{
							i ++;
							cout << p -> name << '\n' 
					     		 <<"想看的时间为："<< p -> iyear << "年" 
			   			 		 << p -> imon << "月" 
			   			 		 << p -> iday << "日\n" 
			   			 		 << "当年的热度为:"<< p -> hot << '\n' 
			   			 		 << "共有 "<< p -> epi << " 集\n" 
			    		 		 << "出番时间:" << p -> cyear << "年\n"
							     << "当时的推荐指数:" << p -> fgrade << '\n' 
			    		 		 << "现在的推荐指数:" << p -> grade << endl;
			    		 	cout << endl;
						}
						p = p -> next;
					} 
					cout << "出番时间为 " << cy << " 共有 " << i << " 部" << endl; 
					getch();
					break;
				}
				case '5':
				{
					double hmax;
					double hmin;
					int i = 0;
					cout << "输入grademax:";
					cin >> hmax;
					cout << "输入grademin:";
					cin >> hmin;
					while(p)
					{
						if(p -> grade >= hmin && p -> grade <= hmax)
						{
							i ++;
							cout << p -> name << '\n' 
					     		 <<"想看的时间为："<< p -> iyear << "年" 
			   			 		 << p -> imon << "月" 
			   			 		 << p -> iday << "日\n" 
			   			 		 << "当年的热度为:"<< p -> hot << '\n' 
			   			 		 << "共有 "<< p -> epi << " 集\n" 
			    		 		 << "出番时间:" << p -> cyear << "年\n"
							     << "当时的推荐指数:" << p -> fgrade << '\n' 
			    		 		 << "现在的推荐指数:" << p -> grade << endl;
			    		 	cout << endl;
						}
						p = p -> next;
					} 
					cout << "分数在 " << hmin << " 到 " << hmax <<" 之间的共有 " << i << " 部" << endl; 
					getch();
					break;
				}
			}
		}
};

int main()
{
	system("mode con lines=1000"); 
	Hide_Cursor();
	pro bf;
	bf.create();
	while(1)
	{
		char a;
		cout << "1:添加\n2:查找\n3:已看\n4:推荐" << endl; 
		a = getch();
		system("cls");
		if(a == '1')
			bf.insert();
		else if(a == '2')
			bf.select();
		else if(a == '3')
		{
			ifstream fin("D:\\文件\\编程\\C++\\随手编的\\seen.txt");
			if(!fin)
			{
				cout<<"File open error!\n";
				return 0;
			}
			char c;
			int num = 0;
			while((c=fin.get())!=EOF)
			{
				if(c == '\n')
				{
					num ++;
						if(num % 7 == 0)
				{
					cout << num / 7 << endl;
				} 
				}
				cout<<c;
			}
			cout << "\n已看" << num / 7 << "部旧番" << endl;
			fin.close();
			getch();
		}
		else 
			bf.choose();
		system("cls");
	}
	return 0;
} 
