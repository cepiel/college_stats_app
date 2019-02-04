/*main.cpp*/

//
// Grade Analysis program in modern C++.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01: Solution
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


//
// A class to model a course in the college of engineering.
//
class Course
{
public:
  string  Dept;
  int     Number;
  string  Title;
  int     A, B, C, D, F, I, NR, S, U, W;
  string  Instructor;

public:
  Course(std::string dept, int number, std::string title,
    int a, int b, int c, int d, int f, int i, int nr, int s, int u, int w,
    std::string instructor)
    : Dept(dept), Number(number), Title(title),
      A(a), B(b), C(c), D(d), F(f), I(i), NR(nr), S(s), U(u), W(w),
      Instructor(instructor)
  { }

  int getNumStudents() const
  {
    return A + B + C + D + F + I + NR + S + U + W;
  }

  int getNumGrades() const
  {
    return A + B + C + D + F;
  }

  double percentDFW() const
  {
    double N = A + B + C + D + F + W;

    if (N == 0.0)
      return 0.0;
    else
      return (D + F + W) / N * 100.0;
  }

  double percentA() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return A / N * 100.0;
  }

  double percentB() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return B / N * 100.0;
  }

  double percentC() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return C / N * 100.0;
  }

  double percentD() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return D / N * 100.0;
  }

  double percentF() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return F / N * 100.0;
  }

};


//
// A class to model a Department in the college.
//
class Dept
{
public:
  string  Name;
  int     NumCourses;
  int     A, B, C, D, F;

public:
  Dept(std::string name)
    : Name(name), NumCourses(0), A(0), B(0), C(0), D(0), F(0)
  { }

  int getNumGrades() const
  {
    return A + B + C + D + F;
  }

  int getNumCourses() const
  {
    return NumCourses;
  }

  double percentA() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return A / N * 100.0;

  }

  double percentB() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return B / N * 100.0;

  }

  double percentC() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return C / N * 100.0;

  }

  double percentD() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return D / N * 100.0;

  }

  double percentF() const
  {
    double N = getNumGrades();

    if (N == 0.0)
      return 0.0;
    else
      return F / N * 100.0;

  }

};


//
// InputCourses
//
// Inputs the course data from the given file, building a vector
// of course objects.  This vector is returned.
//
vector<Course> InputCourses(string filename)
{
  vector<Course> courses;
  string  line, value, dept, title, instructor;
  int number, A, B, C, D, F, I, NR, S, U, W;

  //
  // file format:
  //
  // Dept,Number,Title,A,B,C,D,F,I,NR,S,U,W,Instructor
  //

  ifstream file(filename);

  getline(file, line);  // skip 1st line, which is header row:

  while (getline(file, line))
  {
    stringstream  ss(line);

    // format: Dept,Number,Title,A,B,C,D,F,I,NR,S,U,W,Instructor
    getline(ss, dept, ',');

    getline(ss, value, ',');
    number = stoi(value);

    getline(ss, title, ',');

    getline(ss, value, ',');
    A = stoi(value);
    getline(ss, value, ',');
    B = stoi(value);
    getline(ss, value, ',');
    C = stoi(value);
    getline(ss, value, ',');
    D = stoi(value);
    getline(ss, value, ',');
    F = stoi(value);

    getline(ss, value, ',');
    I = stoi(value);
    getline(ss, value, ',');
    NR = stoi(value);
    getline(ss, value, ',');
    S = stoi(value);
    getline(ss, value, ',');
    U = stoi(value);
    getline(ss, value, ',');
    W = stoi(value);

    getline(ss, instructor, ',');

    Course course(dept, number, title, A, B, C, D, F, I, NR, S, U, W, instructor);

    courses.push_back(course);
  }

  return courses;
}


//
// outputGradeDistForCOE
//
// Output grade distribution for college of engineering.
//
void outputGradeDistForCOE(const vector<Course>& courses, const vector<Dept>& depts)
{
  double N = 0.0;
  int A, B, C, D, F;
  A = B = C = D = F = 0;

  //
  // Sum up the grades from each dept to obtain total for COE:
  //
  for (const Dept& dept : depts)
  {
    N += dept.getNumGrades();
    A += dept.A;
    B += dept.B;
    C += dept.C;
    D += dept.D;
    F += dept.F;
  }

  //
  // Output stats for COE:
  //
  cout << "College of Engineering:" << endl;
  cout << "  Num courses:  " << courses.size() << endl;
  cout << "  Num grades:   " << (int)N << endl;

  cout << "  " << "Distribution: "
    << A / N * 100.0 << "%, "
    << B / N * 100.0 << "%, "
    << C / N * 100.0 << "%, "
    << D / N * 100.0 << "%, "
    << F / N * 100.0 << "%"
    << endl;
}


//
// outputGradeDistForDepts
//
// Output grade distributions for each dept.
//
void outputGradeDistForDepts(const vector<Dept>& depts)
{
  //
  // For each dept, output stats about that dept:
  //
  for (const Dept& D : depts)
  {
    if (D.getNumGrades() == 0)  // no info:
    {
      cout << D.Name << ": 0.0, 0.0, 0.0, 0.0, 0.0" << endl;
    }
    else
    {
      cout << D.Name << ":" << endl;
      cout << "  " << "Num courses:  " << D.getNumCourses() << endl;
      cout << "  " << "Num grades:   " << D.getNumGrades() << endl;
      cout << "  " << "Distribution: "
        << D.percentA() << "%, "
        << D.percentB() << "%, "
        << D.percentC() << "%, "
        << D.percentD() << "%, "
        << D.percentF() << "%"
        << endl;
    }
  }
}


//
// outputGradeDistForInstructors
//
// Outputs the grade distributions for all courses that match
// the given instructor name.  The name could be a prefix that
// matches multiple instructors.
//
void outputGradeDistForInstructors(const vector<Course>& courses, string name)
{
  size_t len = name.length();

  //
  // for each course, see if instructor name matches, and if so, output
  // stats for that course:
  //
  for (const Course& C : courses)
  {

    if (C.Instructor.substr(0, len) == name)  // match:
    {
      cout << C.Dept << " " << C.Number
        << " (" << C.Instructor << "):"
        << endl;

      cout << "  " << "Num students: " << C.getNumStudents() << endl;

      if (C.getNumGrades() == 0)
      {
        cout << "  " << "Distribution: no report" << endl;
      }
      else
      {
        cout << "  " << "Distribution: "
          << C.percentA() << "%, "
          << C.percentB() << "%, "
          << C.percentC() << "%, "
          << C.percentD() << "%, "
          << C.percentF() << "%"
          << endl;
      }

      cout << "  " << "DFW rate: "
        << C.percentDFW() << "%"
        << endl;
    }

  }//for
}


//
// main:
//
int main()
{
  string  filename;

  //
  // input filename, and make sure file exists:
  //
  cin >> filename;
  cout << filename << endl;
  cout << endl;

  ifstream  courseFile(filename);

  cout << std::fixed;
  cout << std::setprecision(2);

  if (!courseFile.good())
  {
    cout << "**ERROR: cannot open course file: '" << filename << "'" << endl;
    return -1;
  }
    
  //
  // Step 1:  input and parse data into a vector of Course objects:
  //
  auto courses = InputCourses(filename);

  //
  // Step 2: loop through the courses and aggregate the data by dept:
  //
  vector<Dept> depts;

  // first we need to get the name of each dept --- we do this by
  // looping through the courses taught, versus just assuming a
  // given set of depts:
  for (Course& C : courses)  // for each course:
  {
    //
    // have we created this dept yet in our vector?
    //
    auto iter = std::find_if(depts.begin(), depts.end(),
      [=](Dept& d)
      {
        if (d.Name == C.Dept)
          return true;
        else
          return false;
      }
    );

    // if not, add this dept to our vector of depts:
    if (iter == depts.end())
      depts.push_back(Dept(C.Dept));
  }

  // now that we have a vector of depts, let's loop through the courses 
  // again and aggregate the data:
  for (Course& C : courses)
  {
    //
    // find the matching dept object:
    //
    auto iter = std::find_if(depts.begin(), depts.end(), 
      [=](Dept& d)
    {
      if (d.Name == C.Dept)
        return true;
      else
        return false;
    });

    if (iter == depts.end())  // not found => error:
      cout << "**Error: unable to find dept '" << C.Dept << "'" << endl;
    else
    {
      // update dept object with data from this course:
      iter->NumCourses++;

      iter->A += C.A;
      iter->B += C.B;
      iter->C += C.C;
      iter->D += C.D;
      iter->F += C.F;
    }
  }

  //
  // Step 3: compute and output grade distribution for entire college
  //
  outputGradeDistForCOE(courses, depts);

  cout << endl;

  //
  // Step 4: compute and output distributions for each dept
  //
  outputGradeDistForDepts(depts);

  cout << endl;

  //
  // Step 5: input a faculty member and output his/her classes:
  //
  string name;

  cout << "Please enter instructor's name (or prefix or #)> ";
  cin >> name;

  while (name != "#")
  {
    size_t len = name.length();

    outputGradeDistForInstructors(courses, name);

    cout << endl;
    cout << "Please enter instructor's name (or prefix or #)> ";
    cin >> name;
  }//while

  //
  // done:
  //
  cout << endl;
  return 0;
}
