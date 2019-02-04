/*main.cpp*/

//
// Grade Analysis program in modern C++.
//
// << LUCAS CEPIEL >>
// U. of Illinois, Chicago
// CS 341: Fall 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;



////////////////////////////////

class Department
{
private:

public:
  string dept;
  int numA, numB, numC, numD, numF;
  int numCourses;
  
  
  Department (string Dept){
    dept = Dept;
    numA=0; numB=0; numC=0; numD=0; numF=0;
  }
  
  
  double getNumGrades(){    //return number of letter grades for whole dept
    double x = numA + numB + numC + numD + numF;
    return x;
  }
  
  double getNumCourses(){   //return number of courses in dept
    return numCourses;
  }
  

};


/////////////////////////////////////
class Course
{
private:

public:
  string dept;
  int courseNum;
  string name;
  int numA, numB, numC, numD, numF, numI, numNR, numS, numU, numW;
  string instructor;

  
  Course(string Dept, int CourseNum, string Name, int NumA, int NumB, int NumC, int NumD, int NumF, int NumI, int NumNR, int NumS, int NumU, int NumW, string Instructor) : dept(Dept), courseNum(CourseNum), name(Name), numA(NumA), numB(NumB), numC(NumC), numD(NumD), numF(NumF), numI(NumI), numNR(NumNR), numS(NumS), numU(NumU), numW(NumW), instructor(Instructor)
  {  }
  
  
  double getDFW(){  //returns percentage of students that were DFW
    double x = numD + numF + numNR + numW;
    x=x/(numA + numB + numC + numD + numF + numNR + numW);
    x=x*100;
    
    return x;
  }
  
  double getNumGrades(){  //returns number of letter grades in course
    double x = numA + numB + numC + numD + numF;
    return x;
  }
  
  string getInstructor(){ //return instructor name
    return instructor;
  }  
  


};


///////////////////////////////////////////////////////
int main()
{
  string  filename;

  cin >> filename;
  cout << filename << endl;
  cout << endl;

  cout << std::fixed;
  cout << std::setprecision(2);

  ifstream file(filename);              //relevant variables for scanning
  string line, dept, name, instructor;
  string courseNum, numA, numB, numC, numD, numF, numI, numNR, numS, numU, numW;

  
  if(!file.good()){
    cout <<"cannot open file!" << endl;
    return -1;
  }
  
  vector <Course> courses;  //creates vector of course objects
  vector <Department> departments;


  getline(file, line);      //skips header
  
  while(getline(file,line))
  {
    stringstream ss(line);
    
    getline(ss, dept, ',');
    getline(ss, courseNum, ',');
    getline(ss, name, ',');
    getline(ss, numA, ',');
    getline(ss, numB, ',');
    getline(ss, numC, ',');
    getline(ss, numD, ',');
    getline(ss, numF, ',');
    getline(ss, numI, ',');
    getline(ss, numNR, ',');
    getline(ss, numS, ',');
    getline(ss, numU, ',');
    getline(ss, numW, ',');
    getline(ss, instructor);
    
    Course c(dept, stoi(courseNum), name, stoi(numA), stoi(numB), stoi(numC), stoi(numD), stoi(numF), stoi(numI), stoi(numNR), stoi(numS), stoi(numU), stoi(numW), instructor);
    
    //insert @ end:
    courses.push_back(c);
    
  }//end scanning file
  

  //engineering totals variables
  int totalCourses=0;
  int totalGrades=0;
  double totalA = 0; double totalB = 0; double totalC = 0; double totalD=0; double totalF=0;
  
  //add engineering totals
  for (Course& c : courses){
    totalCourses++;
    totalA += c.numA;
    totalB += c.numB;
    totalC += c.numC;
    totalD += c.numD;
    totalF += c.numF;
    totalGrades += c.numA + c.numB + c.numC + c.numD + c.numF;
    string deptName = c.dept;
    
    bool tf=false;
    
    //scan for and create departments
    for (Department& d : departments){
      string searchName = d.dept;
      //set tf to true if a matching dept is found. if its false by the end, means match was never found so add that department!
      
      if(searchName.compare(deptName)==0) { //match found
        tf = true;      }
      
    }
    
    if(tf == false) //then dept name was never found. push dept
    {
      Department d(deptName);
      departments.push_back(d);
    }
	
	
	
  } // end foreach loop of courses


  //calculate dist of engineering grades
  double distA = (totalA/totalGrades) * 100;
  double distB = (totalB/totalGrades) * 100;
  double distC = (totalC/totalGrades) * 100;
  double distD = (totalD/totalGrades) * 100;
  double distF = (totalF/totalGrades) * 100;
  cout << "College of Engineering:\n Num courses:  " << totalCourses << "\n Num grades:   " << totalGrades << endl;
  cout << " Distribution: " << distA << "%, " << distB << "%, " << distC << "%, " << distD << "%, " << distF << "%" << endl;


  //cycle through courses and add stats to the department if the course is from that dept
  for (Department& d : departments){
    string name = d.dept;
    
    for (Course& c : courses){
      if(name.compare(c.dept)==0) { //match found
        d.numCourses++;
        d.numA += c.numA;
        d.numB += c.numB;
        d.numC += c.numC;
        d.numD += c.numD;
        d.numF += c.numF;
      }
    }
    
  }

  
  //print departments and sums
  for (Department& d : departments){
    double numGrades = d.getNumGrades();
    distA = (d.numA/numGrades) * 100;
    distB = (d.numB/numGrades) * 100;
    distC = (d.numC/numGrades) * 100;
    distD = (d.numD/numGrades) * 100;
    distF = (d.numF/numGrades) * 100;
    
    cout << d.dept << ": \n Num courses: " << d.numCourses << "\n Num grades: " << (int)numGrades << endl;
    cout << " Distribution: " << distA << "%, " << distB << "%, " << distC << "%, " << distD << "%, " << distF << "%" << endl;
    
  }

  
  

  string str;
  while(1){         //Loop asking for instructors
  
    cout << "Please enter instructor's name (or prefix or #)> " << endl;
    cin >> str;
    
    if(str.compare("#")==0){ //check if the input is # to end program
      return 0;
    }
    
    //loop through courses they teach and their statistics
    for (Course& c : courses){
      string substring = c.instructor.substr(0,str.length());
      
      if(substring.compare(str)==0) { //instructor match found! this uses a substring to find partial matches
      
        double numGrades = c.getNumGrades(); //gives total letter grades
        distA = (c.numA/numGrades) * 100;
        distB = (c.numB/numGrades) * 100;
        distC = (c.numC/numGrades) * 100;
        distD = (c.numD/numGrades) * 100;
        distF = (c.numF/numGrades) * 100;
      
        int numStudents = (int)numGrades+c.numW+c.numU+c.numS+c.numI+c.numNR; //gets new total of students, not just letter grades

        
        cout << c.dept << " " << c.courseNum << " (" << c.instructor << "):" << endl;
        cout << " Num students: " << numStudents << endl;
        
        double dfw = c.getDFW();
        if(numGrades <= 0){
          cout << " Distribution: no report" << endl;
          if(isnan(dfw))        //checks if dfw is nan, we know the right answer should be 0 and not nan. 
            cout << " DFW rate: 0.00%" << endl;
          else
            cout << " DFW rate: " << dfw << "%" << endl;
        }
        else{
          cout << " Distribution: " << distA << "%, " << distB << "%, " << distC << "%, " << distD << "%, " << distF << "%" << endl;
          cout << " DFW rate: " << dfw << "%" << endl;
        }
 
      
      
      }
    }//end for loop of courses
    

    
    
    
    
    
  }//end while loop

  //
  // done:
  //
  cout << endl;
  return 0;
}
