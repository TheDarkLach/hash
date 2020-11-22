//Hastable by Faizan Karim
//randomly generated names come from a list i made
//got names from google :/

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

struct student
{
  char Fname[81];
  char Lname[81];
  int id;
  float gpa;
  student* next;
  student* prev;
};

void ADD(student** list, student* newStudent, int size);
void PRINT(student** list, int size);
void REMOVE(student** list, int id, int size);
bool COLL(student** list, int size);

int main()
{
  bool run = true;
  char input[10];
  int randid = 123; //keeps track of id
  
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
    else if (strcmp(input, "addrand") == 0) {  //add random student
      int num;
      //initialize name arrays
      char** namef = new char*[20];
      char** namel = new char*[20];
      for (int i = 0; i < 10; i++) {
	namef[i] = new char[81];
	namel[i] = new char[81];
      }
      cout << endl << "How many random students should be added: ";
      cin >> num;
      cin.clear();
      cin.ignore(10000, '\n');
      ifstream myfile("fnames.txt");
      int linenr = 0;
      char first[81];
      while (linenr < 10) {
	myfile.getline(first, 81);
	cout << first << linenr << endl;
	strcpy(namef[linenr], first);
	linenr++;
      }
      ifstream myfile1("lnames.txt");
      char last[81];
      linenr = 0; //restar count
      while (linenr < 10) {
	myfile1.getline(last, 81);
	strcpy(namel[linenr], last);
	linenr++;
      }
      while (num > 0) {
	student* newStudent = new student();  //initalize new student
	//make random numbers between 0 and 9
	int randomf = rand() % 9;
	int randoml = rand() % 9;
	//assign random data to new studen
	strcpy(newStudent->Fname, namef[randomf]);
	strcpy(newStudent->Lname, namel[randoml]);
	newStudent->id = randid;
	newStudent->gpa = (float)rand()/(RAND_MAX)*5;
	//increment by 100
	randid = randid + 100;
	      
	//add new student genrated
	ADD(list, newStudent, size);
	//balance if collision
	if (COLL(list, size)) {
	  cout << endl << "Changing hash table array to double the size." << endl;
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
	num--;
      }
    }
    else if (strcmp(input, "quit") == 0) {
      cout << endl << "Quitting" << endl;
      run = false;
    } 
    else 
    {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
   return 0;
}

void ADD(student** list, student* newStudent, int size) {
  int index = (newStudent->id) % size;
	
  //put new student in current array
  if (list[index] == NULL) {
    //no colision, simply add to list
    list[index] = newStudent;
  } else {
    //collision, then add as next ptr
    if ((list[index])->next == NULL) {
      //no previous collision
      (list[index])->next = newStudent;
      (list[index]->next)->prev = (list[index])->next;
    } else {
      //already a collision existent there
      ((list[index])->next)->next = newStudent;
      (((list[index])->next)->next)->prev = ((list[index])->next)->next;
    }
  }
}

bool COLL(student** list, int size) 
{
  bool newlist = false;  //keep trak whether there's a need to make a new list
  int ctr = 0;
  while (newlist == false && ctr < size) 
  {
    if (list[ctr] != NULL) 
    {
      if ((list[ctr])->next != NULL) 
      {
	if (((list[ctr])->next)->next != NULL) 
	{
	  newlist = true;
	}
      }
    }
    ctr++;
  }
  return newlist;
}

void PRINT(student** list, int size) 
{
  for (int i = 0; i < size; i++) 
  {
    student* curr = list[i];
    if (curr != NULL) 
    {
      cout << curr->Fname << " ";
      cout << curr->Lname;
      cout << " #" << curr->id << " GPA:";
      cout << fixed << setprecision(2) << curr->gpa;
      student* nxt = curr->next;
      if (nxt != NULL) 
      {
	cout << '\t' << nxt->Fname << " ";
	cout << nxt->Lname;
	cout << "#" << nxt->id << " GPA:";
	cout << fixed << setprecision(2) << nxt->gpa;
      }
      cout << endl;
    } 
  }
}

void REMOVE(student** list, int id, int size) 
{
  int i = id % size;
  if (list[i] == NULL) 
  {
    cout << endl << "No such student to remove." << endl;
  } else {
    if (list[i]->id == id) 
    {
      //found then delete
      if (list[i]->next == NULL) 
      {
	list[i] = NULL; 
      } else 
      {
	//replace with next in collision
	student* newcurr = list[i]->next;
	newcurr->prev = NULL;
	list[i] = newcurr;
      }
    } 
     else 
     {
      if (list[i]->next == NULL) 
      {
	cout << endl << "They don't exist :(" << endl;
      }
      else 
      {
	if (list[i]->next->id == id) 
	{
	  //found then remove
	  list[i]->next = NULL;
	} 
	else 
	{
	    cout << "They don't exist :(" << endl;
	}
      }
    }
  }
}
