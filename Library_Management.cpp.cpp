#include <bits/stdc++.h>
#include <conio.h>

using namespace std;
struct date
{
	int d;
	int m;
	int y;


};

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31
                          };

int countLeapYears(date d)
{
	int years = d.y;
	if (d.m <= 2)
		years--;
	return years / 4 - years / 100 + years / 400;
}
int getDifference(date dt1, date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1);
}
class Book
{
	char name[50];
	char author[20];
	char isbn[7];
	int copies;

public:
	void add_book();
	void create_book()
	{
		cout << "CREATING NEW BOOK" << endl;
		cout << "ENTER THE ISBN NUMBER OF BOOK" << endl;
		cin >> isbn;
		cout << "ENTER THE BOOK NAME" << endl;
		cin >> name;
		cout << "ENTER THE NAME OF AUTHOR" << endl;
		cin >> author;
		cout << "BOOK CREATED" << endl;
	}
	void show_book()
	{
		cout << " ISBN NUMBER OF BOOK :" << isbn;
		cout << " BOOK NAME : ";
		puts(name); cout << endl;
		cout << " AUTHOR NAME : ";
		puts(author); cout << endl;
	}
	void modify_book()
	{
		cout << " BOOK NUMBER : " << isbn << endl;
		cout << " MODIFY BOOK NAME : ";
		gets(name);
		cout << " MODIFY AUTHOR'S NAME OF BOOK : ";
		gets(author);
	}
	char* ret_isbn()
	{
		return isbn;
	}
	void report()
	{
		cout << isbn << setw(30) << name << setw(30) << author << endl;
	}

};

class Student
{
	char s_name[20];
	char roll_no[11];
	char stbno[7];

public:
	int token;
	char* issue_date;
	void create_student()
	{
		system("cls");//clrscr();
		cout << " NEW STUDENT ENTRY " << endl;
		getchar();
		cout << " Enter The roll no." << endl;
		cin >> roll_no;
		getchar();
		cout << " Enter The Name of The Student " << endl;
		gets(s_name);
		token = 0;
		stbno[0] = '/0';
		cout << " Student Record Created " << endl;
	}
	void show_student()
	{
		cout << " Admission no. : " << roll_no;
		cout << " Student Name : ";
		puts(s_name);
		cout << " No of Book issued : " << token;
		if (token == 1)
			cout << " Book No " << stbno;

	}
	void modify_student()
	{
		cout << " ROLL NO. : " << roll_no;
		getchar();
		cout << " Modify Student Name : ";
		gets(s_name);
	}
	char* ret_roll_no()
	{
		return roll_no;
	}
	char* retstbno()
	{
		return stbno;
	}

	void getstbno(char t[])
	{
		strcpy(stbno, t);
	}
	void report()
	{
		cout << roll_no << setw(20) << s_name << setw(20) << token << endl;
	}

};
fstream fp, fp1;
Book b;
Student s;

void write_student()
{
	char b;
	fp.open("student.dat", ios::out | ios::app);
	do
	{
		s.create_student();
		fp.write((char*)&s, sizeof(Student));
		cout << "do you want to add more record(y/n)" << endl;
		cin >> b;
	} while (b == 'y' || b == 'Y');
	fp.close();
}
void display_sps(char n[])
{
	cout << " STUDENT DETAILS " << endl;
	int flag = 0;
	fp.open("student.dat", ios::in);
	while (fp.read((char*)&s, sizeof(Student)))
	{
		if ((strcmp(s.ret_roll_no(), n) == 0))
		{
			s.show_student();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << " Student does not exist " << endl;
	getch();
}
void modify_student()
{
	char n[11];
	int found = 0;
	system("cls");//clrscr();
	cout << "MODIFY STUDENT RECORD ";
	cout << " Enter The roll no. of The student ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	while (fp.read((char*)&s, sizeof(Student)) && found == 0)
	{
		if (strcmp(s.ret_roll_no(), n) == 0)
		{
			s.show_student();
			cout << " Enter The New Details of student " << endl;

			s.modify_student();
			int pos = -1 * sizeof(s);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&s, sizeof(Student));
			cout << " Record Updated " << endl;
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << " Record Not Found " << endl;
	getch();
}

void delete_student()
{
	char n[11];
	int flag = 0;
	system("cls");//clrscr();
	cout << " DELETE STUDENT " << endl;
	cout << " Enter The roll no. of the Student You Want To Delete : ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;

	fp2.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&s, sizeof(Student)))
	{
		if (strcmp(s.ret_roll_no(), n) != 0)
			fp2.write((char*)&s, sizeof(Student));
		else
			flag = 1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	if (flag == 1)
		cout << " Record Deleted " << endl;
	else
		cout << " Record not found ";
	getch();
}



void display_alls()

{
	system("cls");//clrscr();
	fp.open("student.dat", ios::in);
	if (!fp)
	{
		cout << " ERROR ";
		getch();
		return;
	}
	cout << " STUDENT LIST \n";

	cout << "roll No." << setw(15) << " Name " << setw(20) << " Book Issued " << endl;

	while (fp.read((char*)&s, sizeof(Student)))
	{
		s.report();
	}

	fp.close();
	getch();
}

void add_book()
{
	char a;
	fp.open("book.dat", ios::out | ios::app);
	do
	{
		system("cls");// clrscr();
		b.create_book();
		fp.write((char*)&b, sizeof(Book));
		cout << endl << "DO YOU WANT TO ADD MORE REECORD..(Y/N)";
		cin >> a;
	} while (a == 'y' || a == 'Y');
	fp.close();
}
void delete_book()
{
	char isbn[7];
	system("cls");//clrscr();
	cout << " ENTER THE ISBN NUMBER OF THE BOOK YOU WANT TO DELETE : ";
	cin >> isbn;
	fp.open("book.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&b, sizeof(Book)))
	{
		if (strcmp(b.ret_isbn(), isbn) != 0)
		{
			fp2.write((char*)&b, sizeof(Book));
		}
	}
	fp2.close();
	fp.close();
	remove("book.dat");
	rename("temp.dat", "book.dat");
	cout << " RECORD DELETED ";
	getch();
}
void modify_book()
{
	char isbn[7];
	int found = 0;
	system("cls");
	cout << " MODIFY BOOK REOCORD " << endl;
	cout << "Enter The book no. of The book ";
	cin >> isbn;
	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&b, sizeof(Book)) && found == 0)
	{
		if (strcmp(b.ret_isbn(), isbn) == 0)
		{
			b.show_book();
			cout << " Enter The New Details of book " << endl;
			b.modify_book();
			int pos = -1 * sizeof(b);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&b, sizeof(Book));
			cout << " Record Updated " << endl;
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << " Record Not Found " << endl;
	getch();
}
void display_book(char n[])
{
	cout << " BOOK DETAILS ";
	int flag = 0;
	fp.open("book.dat", ios::in);
	while (fp.read((char*)&b, sizeof(Book)))
	{
		if (strcmp(b.ret_isbn(), n) == 0)
		{
			b.show_book();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)cout << " BOOK  DOES NOT EXIST " << endl;
	getch();
}

void display_book_list()
{

	system("cls");
	fp.open("book.dat", ios::in);
	if (!fp)
	{
		cout << "ERROR !!! " << endl;
		getch();
		return;
	}
	cout << "                BOOK LIST                " << endl;
	cout << " BOOK NUMBER " << setw(20) << " BOOK NAME " << setw(25) << " AUTHOR " << endl;
	while (fp.read((char*)&b, sizeof(Book)))
	{
		b.report();
	}
	fp.close();
	getch();
}
void book_issue()
{
	char sn[50], bn[20];
	int found = 0, flag = 0;
	system("cls");
	cout << " BOOK ISSUE " << endl;
	cout << " ENTER THE STUDENT'S ROLL NO." << endl;
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&s, sizeof(Student)) && found == 0)
	{
		if (strcmp(s.ret_roll_no(), sn) == 0)
		{
			found = 1;
			if (s.token < 3)
			{
				time_t rawtime;
				struct tm * timeinfo;
				char buffer[80];

				time (&rawtime);
				timeinfo = localtime(&rawtime);

				strftime(buffer, sizeof(buffer), "%d-%m-%Y ", timeinfo);
				char* str(buffer);
				s.issue_date = str;
				cout << " Enter the book no.";

				cin >> bn;

				while (fp1.read((char*)&b, sizeof(Book)) && flag == 0)

				{
					if (strcmp(b.ret_isbn(), bn) == 0)

					{
						b.show_book();
						flag = 1;
						s.token++;
						s.getstbno(b.ret_isbn());

						int pos = -1 * sizeof(s);

						fp.seekp(pos, ios::cur);

						fp.write((char*)&s, sizeof(Student));

						cout << " Book issued successfully " << endl;
					}
				}
				if (flag == 0)
					cout << "Book no. does not exist " << endl;
			}
			else
				cout << " You have already taken 3 books  " << endl;

		}
	}
	if (found == 0)

		cout << "Student record not exist " << endl;
	getch();
	fp.close();

	fp1.close();
}

void book_deposit()
{
	char sn[11], bn[6];
	int found = 0, flag = 0, day, fine;
	system("cls");
	cout << " BOOK DEPOSIT " << endl;
	cout << "Enter The student's roll no." ;
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&s, sizeof(Student)) && found == 0)
	{
		if (strcmp(s.ret_roll_no(), sn) == 0)
		{
			found = 1;
			if (s.token > 0)
			{
				while (fp1.read((char*)&b, sizeof(Book)) && flag == 0)

				{
					if (strcmp(b.ret_isbn(), s.retstbno()) == 0)
					{
						b.show_book();
						flag = 1;

						int r, h, y;
						r = atoi(s.issue_date);
						s.issue_date += 3;
						h = atoi(s.issue_date);
						s.issue_date += 3;
						y = atoi(s.issue_date);
						date d1 = {r, h, y};
						cout << "Enter current date:- (dd mm yy)";
						date d;
						int a, b, c;
						cin >> a >> b >> c;
						date d2 = {a, b, c};

						int diff = getDifference(d1, d2);
						if (diff > 14 - 12 - 736931)
						{
							cout << " Fine is:- " << diff - 12 - 736931 << " Rupees\n";
						}
						s.token--;
						int pos = -1 * sizeof(s);
						fp.seekp(pos, ios::cur);

						fp.write((char*)&s, sizeof(Student));

						cout << " Book deposited successfully " << endl;
					}
				}
				if (flag == 0)
					cout << " Book no. does not exist " << endl;
			}

			else
				cout << " No book is issued " << endl;
		}
	}
	if (found == 0)
		cout << " Student record not exist " << endl;
	getch();
	fp.close();
	fp1.close();
}
void admin_menu()
{
	system("cls");
	int n;
	cout << "                             ADMINISTRATOR MENU                             " << endl;
	cout << "1.CREATE STUDENT RECORD " << endl;
	cout << "2.DISPLAY ALL STUDENTS RECORD " << endl;
	cout << "3.DISPLAY SPECIFIC STUDENT RECORD " << endl;
	cout << "4.MODIFY STUDENT RECORD " << endl;
	cout << "5.DELETE STUDENT RECORD " << endl;
	cout << "6.CREATE BOOK " << endl;
	cout << "7.DISPLAY ALL BOOKS " << endl;
	cout << "8.DISPLAY SPECIFIC BOOK " << endl;
	cout << "9.MODIFY BOOK " << endl;
	cout << "10.DELETE BOOK " << endl;
	cout << "11.BACK TO MAIN MENU " << endl;
	cout << "Please Enter Your Choice " << endl;
	cin >> n;
	switch (n)
	{
	case 1: {
		system("cls");
		write_student(); break;
	}
	case 2: {system("cls"); display_alls(); break;}
	case 3:
		char num[11];
		system("cls");
		cout << "Please Enter The Admission No. " << endl;
		cin >> num;
		display_sps(num);
		break;
	case 4: system("cls"); modify_student(); break;
	case 5: system("cls"); delete_student(); break;

	case 6: //clrscr();
		system("cls"); add_book(); break;
	case 7: system("cls"); display_book_list(); break;
	case 8: {
		char num[7];
		system("cls");
		cout << "Please Enter The book No. " << endl;
		cin >> num;
		display_book(num);
		break;

	}

	case 9: modify_book(); break;
	case 10: delete_book(); break;
	case 11: return;
	default: cout << "\a";
	}
	admin_menu();
}



int main()
{
	system("Color 7C");
	char ch;
	do
	{
		system("cls");
//clrscr();
		cout << "               MAIN MENU               " << endl;
		cout << "01. BOOK ISSUE " << endl;
		cout << "02. BOOK DEPOSIT " << endl;
		cout << "03. ADMINISTRATOR MENU " << endl;
		cout << "04. EXIT " << endl;
		cout << " Please Select Your Option " << endl;
		ch = getche();
		switch (ch)
		{

		case '1'://clrscr();
		{
			system("cls");
			book_issue();
			break;
		}
		case '2': book_deposit();
			break;
		case '3': admin_menu();
			break;
		case '4': exit(0);
		default : cout << "\a";
		}

	} while (ch != '4');
	return 0;
}