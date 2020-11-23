//Hastable by Faizan Karim
//randomly generated names come from a list i made
//got names from google :/

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <time.h>


using namespace std;

struct stud {
  char Fname[81];
  char Lname[81];
  int id;
  float gpa;
  stud* next;
  stud* prev;
};

//functions
void ADD(stud** list, stud* newStud, int size);
void PRINT(stud** list, int size);
void REMOVE(stud** list, int id, int size);
bool COLL(stud** list, int size);

int main() {
  //variables
  bool run = true;
  char input[10];
  int randid = 123; //keeps track or random id value
  //hash table variabes
  stud** list = new stud*[100];
  int size = 100;
  while (run) {
    cout << endl << "You can: add, addrand, remove, print, quit." << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "add") == 0) {  //add student manually
      //get info from user input
      stud* newStud = new stud();
      newStud->next = NULL;
      newStud->prev = NULL;
      cout << "Enter first name: " << endl;
      cin >> newStud->Fname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter last name: " << endl;
      cin >> newStud->Lname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter ID: " << endl;
      cin >> newStud->id;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter GPA: " << endl;
      cin >> newStud->gpa;
      cin.clear();
      cin.ignore(81, '\n');
      ADD(list, newStud, size);
      cout << endl << "New student added to hash table." << endl;
      //balance if collision
      if (COLL(list, size)) {
	cout << endl << "Changing hash table array to double the size." << endl;
	stud** temp = new stud*[size];  //create temp array
	for (int m = 0; m < size; m++) 
	{
	  temp[m] = list[m];
	}
	int newsize = 2*size;
	list = new stud*[newsize]; //recreate list to double
	for (int c = 0; c < newsize; c++) 
	{
          list[c] = NULL;
        }
	//re-add all students to newly sized list
	for (int a = 0; a < size; a++) 
	{
	  if (temp[a] != NULL) {
	    stud* move = temp[a];
	    if (move->next != NULL) 
	    {
	      stud* nxt = move->next;
	      move->next = NULL;
	      nxt->prev = NULL;
	      ADD(list, nxt, newsize);
	      if (nxt->next != NULL) 
	      {
		stud* dnxt = nxt->next;
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
    {  //remove student
      cout << "Input ID of student to remove: ";
      int in;
      cin >> in;
      cin.clear();
      cin.ignore(10000, '\n');
      REMOVE(list, in, size);
    }
    else if (strcmp(input, "print") == 0) 
    {  //print list with students
      PRINT(list, size);
    }
    else if (strcmp(input, "addrand") == 0) 
    {  //add random student
      int num;
      //initialize name arrays
      char** namef = new char*[20];
      char** namel = new char*[20];
      for (int i = 0; i < 20; i++) {
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
      while (linenr < 20) 
      {
	myfile.getline(first, 81);
	cout << first << linenr << endl;
	strcpy(namef[linenr], first);
	linenr++;
      }
      ifstream myfile1("lnames.txt");
      char last[81];
      linenr = 0; //restar count
      while (linenr < 20) {
	myfile1.getline(last, 81);
	strcpy(namel[linenr], last);
	linenr++;
      }
      while (num > 0) 
      {
	stud* newStud = new stud();  //initalize new student
	//make random numbers between 0 and 19
	int randomf = rand() % 19;
	int randoml = rand() % 19;
	//assign random data
	strcpy(newStud->Fname, namef[randomf]);
	strcpy(newStud->Lname, namel[randoml]);
	newStud->id = randid;
	newStud->gpa = (float)rand()/(RAND_MAX)*5;
	randid = randid + 100;
	//add new student genrated
	ADD(list, newStud, size);
	//balance if collision
	if (COLL(list, size)) {
	  cout << endl << "Changing hash table array to double the size." << endl;
	  stud** temp = new stud*[size];  //create temp array
	  for (int m = 0; m < size; m++) {
	    temp[m] = list[m];
	  }
	  int newsize = 2*size;
	  list = new stud*[newsize]; //recreate list to double
	  for (int c = 0; c < newsize; c++) {
	    list[c] = NULL;
	  }
	  //re-add all students to newly sized list
	  for (int a = 0; a < size; a++) {
	    if (temp[a] != NULL) {
	      stud* move = temp[a];
	      if (move->next != NULL) {
		stud* nxt = move->next;
		move->next = NULL;
		nxt->prev = NULL;
		ADD(list, nxt, newsize);
		if (nxt->next != NULL) {
		  stud* dnxt = nxt->next;
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
    } else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

//basically the hash function
void ADD(stud** list, stud* newStud, int size) {
  int index = (newStud->id) % size;
  //put new student in current array
  if (list[index] == NULL) {
    //no colision, simply add to list
    list[index] = newStud;
  } else {
    //collision, then add as next ptr
    if ((list[index])->next == NULL) {
      //no previous collision
      (list[index])->next = newStud;
      (list[index]->next)->prev = (list[index])->next;
    } else {
      //already a collision existent there
      ((list[index])->next)->next = newStud;
      (((list[index])->next)->next)->prev = ((list[index])->next)->next;
    }
  }
}

bool COLL(stud** list, int size) {
  bool newlist = false;  //keep trak whether there's a need to make a new list
  int ctr = 0;
  while (newlist == false && ctr < size) {
    if (list[ctr] != NULL) {
      if ((list[ctr])->next != NULL) {
	if (((list[ctr])->next)->next != NULL) {
	  newlist = true;
	}
      }
    }
    ctr++;
  }
  return newlist;
}

void PRINT(stud** list, int size) {
  for (int i = 0; i < size; i++) {
    stud* curr = list[i];
    if (curr != NULL) {
      cout << curr->Fname << " ";
      cout << curr->Lname;
      cout << " #" << curr->id << " GPA:";
      cout << fixed << setprecision(2) << curr->gpa;
      stud* nxt = curr->next;
      if (nxt != NULL) {
	cout << '\t' << nxt->Fname << " ";
	cout << nxt->Lname;
	cout << "#" << nxt->id << " GPA:";
	cout << fixed << setprecision(2) << nxt->gpa;
      }
      cout << endl;
    } 
  }
}

void REMOVE(stud** list, int id, int size) {
  int i = id % size;
  if (list[i] == NULL) {
    cout << endl << "No such student to remove." << endl;
  } else {
    if (list[i]->id == id) {
      //found then delete
      if (list[i]->next == NULL) {
	list[i] = NULL; 
      } else {
	//replace with next in collision
	stud* newcurr = list[i]->next;
	newcurr->prev = NULL;
	list[i] = newcurr;
      }
    } else {
      if (list[i]->next == NULL) {
	cout << endl << "No such student to remove." << endl;
      } else {
	if (list[i]->next->id == id) {
	  //found then remove
	  list[i]->next = NULL;
	} else {
	    cout << "No such student to remove." << endl;
	}
      }
    }
  }
}

