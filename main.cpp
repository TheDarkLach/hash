#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

struct student
{
  char Fname[80];
  char Lname[80];
  int id;
  float gpa;
  student* next;
  student prev*;
};

void ADD(student** list, student* newStudent, int size);
void PRINT(student** list, int size);
void REMOVE(student** list, int id, int size);
bool COLL(student** list, int size);

int main()
{
  bool run = true;
  char input[10];
  int randid = 6; //keeps track of id
  
  student** list = new student*[100];
  int size = 100;

  while(run)
  {
    cout << "Commands are add, addrand, remove, print, and quit." << endl;

    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');

    //add students normally
    if (strcmp(input, "add") == 0)
    { 
      //input
      student* newStudent = new student();
      newStudent->next = NULL;
      newStudent->prev = NULL;
      cout << "Enter first name: " << endl;
      cin >> newStudent->Fname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter last name: " << endl;
      cin >> newStudent->Lname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter ID: " << endl;
      cin >> newStudent->id;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter GPA: " << endl;
      cin >> newStudent->gpa;
      cin.clear();
      cin.ignore(81, '\n');
      ADD(list, newStudent, size);
      cout << endl << "New student added to hash table." << endl;

      //collision
      if (COLL(list, size)) {
	cout << endl << "changing hash table array to double the size." << endl;
	student** temp = new student*[size];  //create temp array
	for (int m = 0; m < size; m++) {
	  temp[m] = list[m];
	}
	int newsize = 2*size;
	list = new student*[newsize]; //recreate list to double
	for (int c = 0; c < newsize; c++) {
          list[c] = NULL;
        }
	//re-add all students to newly sized list
	for (int a = 0; a < size; a++) {
	  if (temp[a] != NULL) {
	    student* move = temp[a];
	    if (move->next != NULL) {
	      student* nxt = move->next;
	      move->next = NULL;
	      nxt->prev = NULL;
	      ADD(list, nxt, newsize);
	      if (nxt->next != NULL) {
		student* dnxt = nxt->next;
		nxt->next = NULL;
		dnxt->prev = NULL;
		ADD(list, dnxt, newsize);
	      }
	    }
	    ADD(list, move, newsize);
	  }
	}
	delete[] temp;
	size = newsize; //update list's size
      }
    }
     else if (strcmp(input, "remove") == 0) 
     { 
      cout << "Input ID of student to remove: ";
      int in;
      cin >> in;
      cin.clear();
      cin.ignore(10000, '\n');
      REMOVE(list, in, size);
    }
    else if (strcmp(input, "print") == 0) 
    {
      PRINT(list, size);
    }
  }
   return 0;
}
