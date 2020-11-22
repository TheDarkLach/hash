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
}
