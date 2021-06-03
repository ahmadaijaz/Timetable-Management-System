#include<iostream>
#include <fstream>
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20
using namespace std; 



//You will use the following 5 functions do to all work

//A) DRAWING FUNCTIONS
//the two drawing functions that you will use to make all shapes
void draw_line(int x1, int y1, int x2, int y2, int color=WHITE, int width=1){
	GP142_lineXY (color,x1,y1,x2,y2,width);
}

void draw_circle(int x, int y, int radius, int color=WHITE){
	 GP142_circleXY(color, x, y, radius);
}

//B) EVENT HANDLERS
//Mouse handler
void handle_mouse(int x, int y){
    GP142_printfXY(YELLOW,x,y,9,"Mouse at (%d,%d)", x, y);
}

//Keyboard handler
void handle_kbd(char c[],int &x,int &y,int color,int size)
{
	//put the character anywhere you want to.
	//I'm putting it on the origin
	//GP142_printfXY(WHITE+color, x, y,   TEXT_SIZE, "%c", c);
	GP142_printfXY(YELLOW+color, x, y, size, c, x, y);
	y = y - (size+10);
}

//periodic handler you will not need to use because we're not doing animation
void demo_handle_periodic(void){};

//---------------------------------------
//PROJECT

//---------> GLOBAL DATA FOR INTIALIZING TIME EVERYDAY (^-^)
int H = 8;
int M = 0;

struct node
{
	int startHour;
	char subjectName[100];
	char DayName[10];
	char section[50];
	node* next;
	node* prev;
};

class LLADT_clash
{
private:
	node* first;
public:
	LLADT_clash() { first = NULL; }
	void insert(int startHour, char subjectName[], char section[], char DayName[])
	{
		node* temp = new node;
		strcpy_s(temp->DayName, DayName);
		strcpy_s(temp->subjectName, subjectName);
		strcpy_s(temp->section, section);
		temp->startHour = startHour;
		temp->next = NULL;

		if (first == NULL)
			first = temp;
		else
		{
			node*  curr = first;
			while (curr->next != 0)
				curr = curr->next;
			curr->next = temp;
			temp->prev = curr;
		}
	}
	void Print()
	{
		int x = -479;
		int y = 339;

		node* curr = first;
		while (curr)
		{
			char arr[1000];
			int index = 0;

			arr[index] = '1';
			index++;

			for (int i = 0; curr->subjectName[i] != '\0'; i++)
			{
				arr[index] = curr->subjectName[i];
				index++;
			}

			arr[index] =' ';
			index++;

			for (int i = 0; curr->section[i] != '\0'; i++)
			{
				arr[index] = curr->section[i];
				index++;
			}

			arr[index] = ' ';
			index++;

			for (int i = 0; curr->DayName[i] != '\0'; i++)
			{
				arr[index] = curr->DayName[i];
				index++;
			}

			arr[index] = '\0';
			handle_kbd(arr, x, y, 1,20);
			curr = curr->next;

		}
	}
	node* Head()
	{
		return first;
	}
	void Printclashs(node* h1, node* h2, ostream& fout)
	{
		fout << "CLASH OF " << h1->subjectName << " " << h1->section << " WITH " << h2->subjectName << " " << h2->section << " ON " << h1->DayName << " AT " << h1->startHour << endl;
	}
};

bool stringCompare(char arr1[], char arr2[])
{
	int size1 = strlen(arr1);
	int size2 = strlen(arr2);

	if (size1 == size2)
	{
		for (int i = 0; arr1[i] != '\0'; i++)
		{
			if (arr1[i] != arr2[i])
				return false;
		}
	}
	else
		return false;
	return true;
}
class Helper
{
public:
	static void setColor(unsigned short color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

void Menu()
{
	int x = -109; //-479
	int y = 300;

	char head[] = "TIME TABLE";
	handle_kbd(head, x, y, 0, 40);
	y = y - 20;

	x = -479;
	char arr[] = "LOAD TIME TABLE";
	handle_kbd(arr, x, y, 1,20);

	char arr0[] = "PRINT TIME TABLE";
	handle_kbd(arr0, x, y, 2,20);

	char arr1[] = "REGISTRATION";
	handle_kbd(arr1, x, y, 3, 20);

	char arr2[] = "STUDENTS DATA IN CLASS";
	handle_kbd(arr2, x, y, 4, 20);

	char arr3[] = "STUDENT TIMETABLE";
	handle_kbd(arr3, x, y, 5, 20);

	char arr4[] = "PRINT TIMING OF COURSE";
	handle_kbd(arr4, x, y, 6, 20);

	char arr5[] = "PRINT COURSE NAME";
	handle_kbd(arr5, x, y, 7, 20);

	char arr6[] = "PRINT MY SUBJECTS NAME";
	handle_kbd(arr6, x, y, 8, 20);

	char arr7[] = "SAVE CLASHES";
	handle_kbd(arr7, x, y, 9, 20);
	
}

struct Time
{
	int Hour;
	int Mint;
	char timeS[3];
};

struct classlist
{
	int count = 0;
	char name[60][15];
	char rollNo[60][10];
};

template <class T>
struct slot
{
	T exactSection[50];
	T Section[20];
	T NameOfSubject[100];
	Time time;
	classlist* student = NULL;
	slot* next;
	slot* prev;
};

template < class T >
class DLLADT
{
	slot<T>* first;
public:
	DLLADT() { first = 0; }

	slot<T>* Head()
	{
		return first;
	}

	void mystudent(int &x,int &y)
	{
		slot<T>* curr = first;

		char data[1000];

		while (curr != 0) {
			int count = 0;


			char arr[] = " *************************************************************************************************************";
			handle_kbd(arr, x, y, 0, 15);

			strcpy_s(data, "            CLASS NAME : ");
			strcat_s(data, curr->NameOfSubject);
			strcat_s(data, " SECTION NAME : ");
			strcat_s(data, curr->exactSection);
			handle_kbd(data, x, y, -4, 15);

			char arr1[] = " *************************************************************************************************************";
			handle_kbd(arr1, x, y, 0, 15);

			y = y - 40;

			while (curr->student && count < curr->student->count) {
				
				strcpy_s(data, "NAME : ");
				strcat_s(data, curr->student->name[count]);
				strcat_s(data, "	ROLLNO : ");
				strcat_s(data, curr->student->rollNo[count]);
				handle_kbd(data,x,y,count,15);
				y = y - 20;
				count++;
			}
			curr = curr->next;
		}
	}

	void SAVECLASH(int rollno, char DayName[], LLADT_clash &save)
	{
		char arr[33];
		_itoa_s(rollno, arr, 10);

		slot<char>* curr = first;

		while (curr != 0)
		{
			if (curr->student)
			{
				int count1 = 0;
				while (count1 < curr->student->count) {
					if (stringCompare(curr->student->rollNo[count1], arr))
					{
						save.insert(curr->time.Hour, curr->NameOfSubject, curr->exactSection, DayName);
					}
					count1++;
				}
			}
			curr = curr->next;

		}

	}

	bool PrintTiming(char coursename[], char section[],int& x,int& y)
	{

		slot<T>* curr = first;
		bool flag = 0;
		char data[100];
		char arr[100];

		while (curr != 0)
		{
			if (stringCompare(curr->NameOfSubject, coursename) && stringCompare(curr->exactSection, section))
			{
				_itoa(curr->time.Hour, arr, 10);
				strcpy_s(data, arr);
				strcat_s(data, " : ");
				_itoa(curr->time.Mint, arr, 10);
				strcat_s(data, arr);
				strcat_s(data, curr->time.timeS);
				handle_kbd(data, x, y, 0, 15);
				flag = 1;
			}
			curr = curr->next;
		}

		return flag;
	}

	void PrintMYCourse(char rollno[],int &x,int &y)
	{

		slot<T>* curr = first;

		while (curr != 0)
		{
			int count1 = 0;
			while (count1 < curr->student->count) {
				if (stringCompare(curr->student->rollNo[count1], rollno))
					handle_kbd(curr->NameOfSubject, x, y, -4, 15);
				//y = y - 20;
				count1++;
			}
			curr = curr->next;
		}
	}

	void StudentCourses(char rollno[],int &x,int &y)
	{

		char data[1000];

		slot<T>* curr = first;


		while (curr != 0)
		{
			int count1 = 0;

			while (curr->student && count1 < curr->student->count) {

				if (stringCompare(curr->student->rollNo[count1], rollno))
				{
					strcpy_s(data, curr->NameOfSubject);
					strcat_s(data, " (");
					strcat_s(data, curr->exactSection);
					strcat_s(data, ")");

					handle_kbd(data, x, y, -4, 15);

					int EndHour = curr->time.Hour;
					int EndMint = curr->time.Mint;
					char time2[4];

					EndMint += 30;
					EndHour += 1;
					if (EndMint == 60)
					{
						EndMint = 0;
						EndHour += 1;

						if (EndHour > 12)
						{
							EndHour -= 12;
							time2[0] = 'P';
							time2[1] = 'M';
							time2[2] = '\0';
						}
						else
						{
							strcpy_s(time2, curr->time.timeS);
						}
					}
					else
						strcpy_s(time2, curr->time.timeS);

					char arr[30];
					_itoa(curr->time.Hour, arr, 10);
					strcpy_s(data, arr);
					strcat_s(data, ":");
					_itoa(curr->time.Mint, arr, 10);
					strcat_s(data,arr);
					strcat_s(data, curr->time.timeS);
					strcat_s(data, " : ");
					_itoa(EndHour, arr, 10);
					strcat_s(data, arr);
					strcat_s(data, ":");
					_itoa(EndMint, arr, 10);
					strcat_s(data, arr);
					strcat_s(data, time2);
					strcat_s(data, ",");
					strcat_s(data, curr->Section);

					handle_kbd(data, x, y, 0, 15);
				}
				count1++;
			}

			curr = curr->next;
		}
	}

	void AlreadyAssociate(slot<char>* Head)
	{
		slot<char>* Head2 = Head;

		while (Head2 != 0) {

			slot<char>* curr = first;
			while (curr != 0)
			{
				if (stringCompare(curr->NameOfSubject, Head2->NameOfSubject) && stringCompare(curr->exactSection, Head2->exactSection))
				{
					curr->student = Head2->student;
				}
				curr = curr->next;
			}
			Head2 = Head2->next;
		}
	}

	void weUNIQUE()
	{
		slot<T>* curr = first;

		char serialNumber[10];
		char Name[5];
		char section[10];
		char subjectName[50];

		while (curr != 0) {
			if (curr->student == NULL)
			{
				curr->student = new classlist;
				ifstream fin;
				fin.open("Registration1.txt");

				while (!fin.eof())
				{
					fin.getline(serialNumber, 10, ',');
					fin.getline(Name, 5, ',');
					fin.getline(subjectName, 50, ',');
					fin.getline(section, 10, ',');
					fin.ignore();

					if (stringCompare(curr->exactSection, section) && stringCompare(curr->NameOfSubject, subjectName))
					{
						strcpy_s(curr->student->name[curr->student->count], Name);
						strcpy_s(curr->student->rollNo[curr->student->count], serialNumber);
						curr->student->count++;
					}
				}
				fin.close();

			}
			curr = curr->next;
		}
	}

	void PrintCourse(int Hour, int Mint, char time[], char classroom[])
	{
		int x = -479;
		int y = 339;

		slot<T>* curr = first;
		char data[1000];

		while (curr != 0)
		{
			if (stringCompare(curr->Section, classroom) && curr->time.Hour == Hour && curr->time.Mint == Mint && stringCompare(time, curr->time.timeS))
			{
				char arr1[] = "COURSE IS :";
				handle_kbd(arr1, x, y, -4, 15);
				strcpy_s(data, curr->NameOfSubject);
				strcat_s(data, " ");
				strcat_s(data, curr->exactSection);
				handle_kbd(data, x, y, 3, 15);
				break;
			}
			curr = curr->next;
		}
	}

	bool CompareANDassociate(char serialNumber[], char Name[], char subjectName[], char section[])
	{
		slot<T>* curr = first;


		while (curr != 0) {
			
			if (!curr->student)
				curr->student = new classlist;

			if (stringCompare(section, curr->exactSection) && stringCompare(subjectName, curr->NameOfSubject))
			{
				strcpy_s(curr->student->name[curr->student->count], Name);
				strcpy_s(curr->student->rollNo[curr->student->count], serialNumber);
				curr->student->count++;
				return true;
			}

			curr = curr->next;
		}
		return false;
	}

	void insert(T sec[], T exact[], T name[], int hour, int mint, T time1[]) {
		slot<T>*temp = new slot < T >;

		strcpy_s(temp->NameOfSubject, name);
		strcpy_s(temp->exactSection, exact);
		strcpy_s(temp->Section, sec);
		temp->time.Hour = hour;
		temp->time.Mint = mint;
		strcpy_s(temp->time.timeS, time1);
		temp->student = NULL;
		temp->next = temp->prev = 0;

		if (first == 0) {
			first = temp;
		}
		else
		{
			slot<T>* curr = first;
			while (curr->next != 0)
				curr = curr->next;
			curr->next = temp;
			temp->prev = curr;
		}
	}

	void print(int &x,int &y)
	{

		char data[1000];
		char arr[100];

		slot<T>* curr = first;
		int color = 1;
		while (curr != 0)
		{
			color++;

			_itoa(curr->time.Hour, arr, 10);
			strcpy_s(data, arr);
			strcat_s(data, " : ");
			_itoa(curr->time.Mint, arr, 10);
			strcat_s(data, arr);
			strcat_s(data,curr->time.timeS);
			strcat_s(data, "	");
			strcat_s(data, curr->Section);
			strcat_s(data, "	");
			strcat_s(data, curr->NameOfSubject);
			strcat_s(data, "(");
			strcat_s(data, curr->exactSection);
			strcat_s(data, ")");
			handle_kbd(data, x, y, color, 15);

			curr = curr->next;
		}
		y = y - 20;

	}

	bool removeFirst(int & val)
	{

		if (!first)  // if list is empty return false;
			return false;

		//else move first to next node and delete the original first node.
		slot<T>* curr = first;
		val = first->value;
		first = first->next;
		delete curr;

		if (first)	//if there are 2 or more elements in the list then the second one becomes the first
					// and its prev must be 0;
			first->prev = 0;


		return true;


	}

	bool remove(T key)
	{
		slot<T>* curr = first;
		while (curr != 0 && curr->value != key)
			curr = curr->next;

		if (curr == 0)
			return false;
		if (curr == first)
		{
			first = first->next;
			if (first)
				first->prev = 0;
			delete curr;
		}
		else
		{
			curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			delete curr;
		}
		return true;

	}

	int count()
	{
		int C = 0;
		slot<T>* curr = first;
		while (curr != 0) {
			curr = curr->next;

			C++;
		}
		return C;


	}

	~DLLADT()
	{
		slot<T>* curr = first;
		while (first != 0)
		{
			first = first->next;
			if (curr->student)
				delete curr->student;

			delete curr;
			curr = first;
		}
	}

};

struct Day
{
	char Name[10];
	DLLADT<char>* classes = new DLLADT<char>[30];
	int slot_number = 0;
};

class TimeTable
{
private:
	Day WeekDays[5];
	int DayNumber;
public:

	//------>PART (A)
	TimeTable()
	{
		DayNumber = 0;
	}

	void Load(char name[])
	{
		ifstream fin;
		fin.open(name);

		while (!fin.eof()) {
			char Day_name[50];
			char section_name[50];
			char subject_name[100];
			char exact[20];

			int hour = H;
			int mint = M;
			int count = 0;
			char time[3] = { 'A','M','\0' };

			fin >> DayNumber;
			fin.ignore();

			fin.getline(Day_name, 50, ','); //--> for example monday

			fin.getline(section_name, 50, ','); //--> for example cs-1

			while (count < 8) { // --> maximum 8 classes per slot

				fin.getline(subject_name, 100, '('); //--> computer programming
				fin.getline(exact, 20, ')');
				fin.ignore();

				strcpy_s(WeekDays[DayNumber].Name, Day_name);

				if (hour >= 12)
					time[0] = 'P';

				WeekDays[DayNumber].classes[WeekDays[DayNumber].slot_number].insert(section_name, exact, subject_name, hour, mint, time);

				mint = mint + 30;

				if (mint == 60)
				{

					hour = hour + 2;

					if (hour > 12)
					{
						hour = hour - 12;
					}
					mint = 0;
				}
				else
				{
					hour = hour + 1;
					if (hour > 12)
					{
						hour = hour - 12;
					}
				}

				count++;
			}
			WeekDays[DayNumber].slot_number++;
		}

	}

	void Print()
	{
		int x = -479;
		int y = 339;

		int Days = 0;
		int count = 0;
		char arr1[100];
		while (Days <= DayNumber) {
			//-----> working for different slots of a day
			while (count < WeekDays[Days].slot_number) {

				strcpy_s(arr1, WeekDays[Days].Name);
				strcat_s(arr1, ":");
				handle_kbd(arr1, x, y, count, 15);
				WeekDays[Days].classes[count].print(x,y);
				count++;
			}
			count = 0;
			Days++;
		}
	}

	//------>PART (B)
	void Registration()
	{
		int x = -479;
		int y = 339;


		char serialNumber[10];
		char Name[5];
		char section[10];
		char subjectName[50];

		ifstream fin;
		fin.open("Registration1.txt");

		while (!fin.eof())
		{
			fin.getline(serialNumber, 10, ',');
			fin.getline(Name, 5, ',');
			fin.getline(subjectName, 50, ',');
			fin.getline(section, 10, ',');
			fin.ignore();

			//-------------------------SEARCH AND ASSOCIATE----------------------------
			int classNumber = 0;

			while (classNumber < 30) {

				WeekDays[0].classes[classNumber].CompareANDassociate(serialNumber, Name, subjectName, section); //MONDAY
				WeekDays[1].classes[classNumber].CompareANDassociate(serialNumber, Name, subjectName, section); //TUESDAY
				WeekDays[4].classes[classNumber].CompareANDassociate(serialNumber, Name, subjectName, section); //FRIDAY
				classNumber++;
			}


			//-------------------------------------------------------------------------

		}
		fin.close();

		//-------------------------LINKING DAYS------------------------------------

		int myclassN = 0;

		while (myclassN < 30) {
			slot<char>* MONDAY = WeekDays[0].classes[myclassN].Head();
			slot<char>* TUESDAY = WeekDays[1].classes[myclassN].Head();
			slot<char>* FRIDAY = WeekDays[2].classes[myclassN].Head();

			int classN = 0;

			while (classN < 30)
			{
				WeekDays[2].classes[classN].AlreadyAssociate(MONDAY);
				WeekDays[3].classes[classN].AlreadyAssociate(MONDAY);

				WeekDays[2].classes[classN].AlreadyAssociate(TUESDAY);
				WeekDays[3].classes[classN].AlreadyAssociate(TUESDAY);

				WeekDays[2].classes[classN].AlreadyAssociate(FRIDAY);
				WeekDays[3].classes[classN].AlreadyAssociate(FRIDAY);

				classN++;
			}
			myclassN++;
		}

		//----------FOR SOME UNIQUE CLASSES ONLY IN WED AND THURS
		int classNumber = 0;

		while (classNumber < 30) {

			WeekDays[2].classes[classNumber].weUNIQUE(); //WEDNESDAY
			WeekDays[3].classes[classNumber].weUNIQUE();// THURSDAY
			classNumber++;
		}
		char arr1[] = "REGISTRATION DONE....";
		handle_kbd(arr1, x, y, 1, 15);
	}

	void studentInClass()
	{
		int x = -479;
		int y = 339;

		int slotNumber = 0;
		WeekDays[0].classes[slotNumber].mystudent(x,y);
	}

	void PrintClash(LLADT_clash &save, ofstream& fout)
	{
		node* curr = save.Head();

		bool flag = 0;
		while (curr != 0)
		{
			node* curr1 = save.Head();
			while (curr1 != 0)
			{
				if (curr1 != curr)
				{
					if (curr->startHour == curr1->startHour && stringCompare(curr->DayName, curr1->DayName))
					{
						save.Printclashs(curr, curr1, fout);
						flag = 1;
					}
				}
				curr1 = curr1->next;
			}
			curr = curr->next;
		}
		if (flag == 0)
			fout << "NO CLASH\n";
	}

	//----->PART (C)
	void SaveClashes()
	{
		ofstream fout;
		fout.open("CLASH.txt");

		int DAY = 0;
		int slotN = 0;
		int i = 1;
		while (i <= 1280) {
			LLADT_clash save;
			DAY = 0;
			while (DAY < 5) {
				slotN = 0;
				while (slotN < 30) {
					WeekDays[DAY].classes[slotN].SAVECLASH(i, WeekDays[DAY].Name, save);
					slotN++;
				}
				DAY++;
			}
			fout << "CLASHES OF ROLL NUMBER : " << i << endl;
			PrintClash(save, fout);
			i++;
		}
	}

	//(X)
	void PrintStudentCourses(char rollno[])
	{

		int x = -479;
		int y = 339;

		int DAY = 0;
		while (DAY < 5) {
			int slot = 0;
			while (slot < 30)
			{
				WeekDays[DAY].classes[slot].PrintMYCourse(rollno,x,y);
				slot++;
			}
			DAY++;
		}
	}

	void PrintStudentTimeTable(char rollno[])
	{
		int x = -479;
		int y = 339;

		int DayNumber1 = 0;
		while (DayNumber1 < 5) {
			Helper::setColor(DayNumber1 + 5);
			handle_kbd(WeekDays[DayNumber1].Name, x, y, -3, 15);
			int SlotNumber = 0;
			while (SlotNumber < 30) {
				Helper::setColor(15);
				WeekDays[DayNumber1].classes[SlotNumber].StudentCourses(rollno,x,y);
				SlotNumber++;
			}
			DayNumber1++;
		}
	}

	void PrintCourse(char day[], int Hour, int Mint, char time[], char classroom[])
	{
		int DAY = 0;
		int classN = 0;

		while (DAY < 5) {
			if (stringCompare(WeekDays[DAY].Name, day))
			{
				while (classN < 30) {
					WeekDays[DAY].classes[classN].PrintCourse(Hour, Mint, time, classroom);
					classN++;
				}

			}
			DAY++;
		}
	}

	void PrintCourseTimings(char coursename[], char section[])
	{
		int x = -479;
		int y = 339;

		char arr[100];
		int DayNumber = 0;
		while (DayNumber < 5) {
			Helper::setColor(DayNumber + 3);
			strcpy_s(arr, WeekDays[DayNumber].Name);
			strcat_s(arr, " : ");
			handle_kbd(arr, x, y, -4, 15);

			int Slot = 0;
			bool flag = 0;
			while (Slot < 30) {
				Helper::setColor(15);
				if (WeekDays[DayNumber].classes[Slot].PrintTiming(coursename, section,x,y))
					flag = 1;
				Slot++;
			}
			if (flag == 0)
				handle_kbd("NO CLASS",x,y,1,15);
			flag = 0;
			DayNumber++;
		}
	}


};


int main(void)
{  
	TimeTable T;
	char name[] = "TimeTable.txt";


    int quit = 0;           /* has user signaled quit yet?                      */
    int mouse_x, mouse_y;
    char key_pressed;
    GP142_open();           /* Open and initialize the GP142 Graphics Window    */


	int pcount=0;
	int points[4];
   

	Menu();
    //The Event Loop  
    while (!quit) {
    

		int x = -479;
		int y = 339;

        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
            case GP142_QUIT:
                quit = 1;   /* set flag to terminate loop                */
                break;

				
			case GP142_MOUSE:
                handle_mouse(mouse_x,mouse_y);
				if (mouse_x <= -297 && mouse_x >= -488 && mouse_y <= 248 && mouse_y >= 237)
				{
					//LOAD TIME TABLE
					T.Load(name);
					GP142_open();
					handle_kbd("File is Loaded Successfully : )", x, y, 1, 20);
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -298 && mouse_x >= -490 && mouse_y <= 218 && mouse_y >= 208)
				{
					//PRINT TIME TABLE
					GP142_open();
					T.Print();

					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);

				}

				if (mouse_x <= -331 && mouse_x >= -490 && mouse_y <= 189 && mouse_y >= 177)
				{
					//REGISTRATION
					GP142_open();
					T.Registration();
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -223 && mouse_x >= -485 && mouse_y <= 158 && mouse_y >= 148)
				{
					// STUDENT DATA IN CLASS
					GP142_open();
					T.studentInClass();
					
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -273 && mouse_x >= -486 && mouse_y <= 131 && mouse_y >= 118)
				{
					// STUDENT TIME TABLE
					GP142_open();
					char roll[10]="6";
					T.PrintStudentTimeTable(roll);
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -220 && mouse_x >= -486 && mouse_y <= 100 && mouse_y >= 89)
				{
					// PRINT TIMING OF COURSE
					GP142_open();
					char courseName[] = "Machine Learning";
					char section[] = "MS-DS";
					T.PrintCourseTimings(courseName, section);
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -299 && mouse_x >= -484 && mouse_y <= 71 && mouse_y >= 60)
				{
					//PRINT MY COURSE NAME
					GP142_open();
					int Hour = 9;
					int Mint = 30;
					char time[3] = "AM";
					char Day[10] = "Monday";
					char classroom[10] = "CS-1";
					T.PrintCourse(Day, Hour, Mint, time, classroom);
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);

				}

				if (mouse_x <= -269 && mouse_x >= -487 && mouse_y <= 41 && mouse_y >= 30)
				{
					//PRINT MY SUBJECT NAME
					GP142_open();
					char rollno[5] = "6";
					T.PrintStudentCourses(rollno);
					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= -213 && mouse_x >= -485 && mouse_y <= 10 && mouse_y >= -4)
				{
					//SAVE CLASH
					GP142_open();
					T.SaveClashes();

					int x1 = 397;
					int y1 = -263;
					handle_kbd("BACK", x1, y1, 1, 15);
				}

				if (mouse_x <= 436 && mouse_x >= 393 && mouse_y <= -246 && mouse_y >= -269)
				{
					GP142_open();
					//GP142_close();
					Menu();
				}


				//draw_circle(mouse_x,mouse_y,10);
                break;
               
            case GP142_KBD:
				//Keyboard handler

                break;
 
            default:
                break;
        }
    }
        
    GP142_close();          /* Clean up and close graphics window           */
    
    return 0;
}
