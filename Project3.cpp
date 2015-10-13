//
//  main.cpp
//  project3.cpp
//
//  Created by Stephan Dubuke on 5/3/14.
//  Copyright (c) 2014 Stephan Dubuke. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
using namespace std;
double find_avg();
struct student_info
{
    string student_name;
    double student_id;
    double quiz[5];
    double midterms[2];
    double fianl;
    double avg;
    char letter_grade;
    int class_rank;
    
};
void find_avg( student_info x[], int n);
void s_sort(student_info x[],  int n);
double findLowest( student_info x);
void letterGrade (student_info x[],  int n);
double bestStudentAVG (student_info x[], int n);
void disply_menu(student_info x[], int n);
void s_sort2(student_info x[], int n);
void find_classrank(student_info x[], int n);
void record_finding(student_info x[], int n);
void stars(int n);

int main()
{
    double class_avg;
    int countA=0;
    int countB=0;
    int countC=0;
    int countD=0;
    int countF=0;
    int i=0;
    string file;
    ifstream in_file;
    //ofstream out_file;
    
    cout << "Enter an input file: ";
    cin >> file;
    
    in_file.open("/Users/TheDirtyHam/Documents/test.txt");
    //out_file.open("/Users/TheDirtyHam/Documents/result.txt");
    
    cout << "-----------------------------------------------" << endl;
    if (in_file.fail())
    {
        cout << "Error: input file open failed.\n";
        exit (1);
    }
    student_info student[30];
    
    
    while(!in_file.eof())
    {
        in_file >> student[i].student_name;
        in_file >> student[i].student_id;
        for (int x=0; x<5; x++) {
            in_file >> student[i].quiz[x];
        }
        in_file >> student[i].midterms[0] >> student[i].midterms[1];
        in_file >> student[i].fianl;
        i++;
    }
    find_avg (student, i);
    letterGrade(student , i);
    s_sort(student, i);
    find_classrank(student, i);
    disply_menu(student, i);
    cout << "\tStatistics" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Number of students " << i << endl;
    for (int l=0; l < i; l++) {
        class_avg += (student[l].avg)/i;
    }
    cout << "Class Average: " << class_avg << endl;
    cout << "Grade Distribution (histogram)" << endl;
    for (int o=0; o < i; o++) {
        if (student[o].letter_grade == 'A') {
            countA++;
        }
        if (student[o].letter_grade == 'B') {
            countB ++;
        }
        if (student[o].letter_grade == 'C') {
            countC ++;
        }
        if (student[o].letter_grade == 'D') {
            countD ++;

        }
        if (student[o].letter_grade == 'F') {
            countF ++;

        }
        
    }
    cout << "A | ";
    stars(countA);
    cout << endl;
    cout << "B | ";
    stars(countB);
    cout << endl;
    cout << "C | ";
    stars(countC);
    cout << endl;
    cout << "D | ";
    stars(countD);
    cout << endl;
    cout << "F | ";
    stars(countF);
    cout << endl;
    cout << "-----------------------------------------------" << endl;
    cout << endl;
    cout << "-----------------------------------------------" << endl;

    
    record_finding(student, i);
    return 0;
}

// this Function finds the avg of each student
void find_avg (student_info x[], int n)
{
    double quiz_avg;
    double midterm_avg;
    for (int i=0; i < n; i++)
    {
        quiz_avg = (x[i].quiz[0] + x[i].quiz[1] + x[i].quiz[2] +
                    x[i].quiz[3] + x[i].quiz[4] - findLowest(x[i]))*2.5;
        midterm_avg= (x[i].midterms[0] + x[i].midterms[1])/2;
        x[i].avg= quiz_avg*.2 + midterm_avg*.4 +x[i].fianl * .4;
    }
    
}

// This function sorts the students by avg, but if they have the same avg it sorts the students by studnent name

void s_sort(student_info x[],  int n) {
    int m;
    student_info hold;
    for (int k=0; k<=n-2; k++) {
        m = k;
        for (int j=k+1; j <= n-1; j++) {
            if (x[j].avg == x[m].avg)
            {
                m = j;
                if (x[j].student_name >= x[m].student_name)
                {
                    m = j;
                }
            }
            if (x[j].avg > x[m].avg)
                m = j;
        }
        hold = x[m];
        x[m] = x[k];
        x[k] = hold;
    }
    return;
}

// this function sorts the students by student name, but if the stendents names are the same it gets sorted by avg
void s_sort2(student_info x[],  int n) {
    int m;
    student_info hold;
    for (int k=0; k<=n-2; k++) {
        m = k;
        for (int j=k+1; j <= n-1; j++) {
            if (x[j].student_name == x[m].student_name)
            {
                    m = j;
                if (x[j].avg >= x[m].avg)
                {
                    m = j;
                }
            }

            if (x[j].student_name < x[m].student_name)
                m = j;
        }
        hold = x[m];
        x[m] = x[k];
        x[k] = hold;
    }
}

// This functions fids the studnets lowest quiz score so i can drop it in the avg function
double findLowest(student_info x)
{
    double lowest = x.quiz[0];
    for (int i=0; i < 5; i++)
    {
        if(x.quiz[i] < lowest)
            lowest= x.quiz[i];
    }
    
    return lowest;
}

// This functions gets a letter grade by using a char and comparing the students avg to be above what the specific letter grade
void letterGrade(student_info x[],  int n)
{
    for (int i=0; i < n; i++) {
        if(x[i].avg >= 90)
            x[i].letter_grade= 'A';
		else if(x[i].avg >= 80){
			x[i].letter_grade = 'B';
		}
		else if(x[i].avg >= 70){
			x[i].letter_grade = 'C';
		}
		else if(x[i].avg >= 60){
			x[i].letter_grade = 'D';
		}
		else
			x[i].letter_grade = 'F';
    }
}

// This finds the best student, its revelant becuase it can be.
double bestStudentAVG(student_info x[], int n)
{
    double best_student;
    best_student = x[0].avg;
    
    for (int i=0; i < n; i++)
    {
        if (x[i].avg > best_student)
        {
            best_student = x[i].avg;
        }
    }
    
    return best_student;
}

// This function is finding the class rank of the students by using a counter, but it also check to see if the students avg is the same so it will give the same count to those studnets but still skip to the respected class rank.
void find_classrank(student_info x[], int n)
{
    int count=1;
    x[0].class_rank = 1;
    for (int i=1; i < n; i++)
    {
        count++;
        if (x[i].avg == x[i-1].avg) {
            x[i].class_rank = x[i-1].class_rank;
        }
        if (x[i].avg < x[i-1].avg ) {
            x[i].class_rank = count;
        }
    }
}

// My display menu is just showing the studnets sorting in order both times with first by acg and then by student name

void disply_menu (student_info x[], int n)
{
    cout << "-----------------------------------------------" << endl;
    cout << "\tCourse Report: Numerical Average Order" << endl;
    cout << "-----------------------------------------------" << endl;
    for(int j = 0; j < n; j++)
    {
        cout << x[j].student_name << " \t " << x[j].student_id << " - " << x[j].avg << " (" << x[j].letter_grade << ") " << "(rank: " << x[j].class_rank << ")" << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "\n";
    cout << "-----------------------------------------------" << endl;
    s_sort2(x, n);
    for(int p = 0; p < n; p++)
    {
        cout << x[p].student_name << " \t " << x[p].student_id << " - " << x[p].avg << " (" << x[p].letter_grade << ") " << "(rank: " << x[p].class_rank << ")" << endl;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "\n" << endl;
    cout << "-----------------------------------------------" << endl;
}

// my recording finding function is the required function that allows you to pull up any studnets info and gives you an error when you type in the name of a wrong student, this function is case sensitive, it will not find the studnet you are looking for if you forget the cap the first letter of the name.
void record_finding(student_info x[], int n)
{
    string student;
    char user;
    do {
        bool flag= false;
    cout << "Record Finder: Enter the name of a student: ";
        cin >> student;
        cout << "-----------------------------------------------" << endl;
    for (int i=0; i < n ; i++) {
        if (student == x[i].student_name) {
            cout << "Name: " << x[i].student_name << endl;
            cout << "Id: " << x[i].student_id << endl;
            cout << "Avgerage: " << x[i].avg << "(" << x[i].letter_grade << ")" << endl;
            cout << "\n";
            flag = true;
        }
    }
        if (flag == false) {
            cout << "Fail " << student << " isnt enrolled in this class. " << endl;
        }
        cout << "-----------------------------------------------" << endl;
        cout << "Do you want to contuine? Y or N" << endl;
        cin >> user;
    }
    while (user == 'Y' || user == 'y');
    
                
}

// my stars functions calculates the number of a's, b's, c's d's and f's and displays them in the main
void stars (int n)
{
    for (int i=0; i< n; i++) {
        cout << " * ";
    }
}


// Thank you so much jose for teaching me my first programming course. I have lreaded a lot in such a little time, I can not thank you enough for all the one on one help you have giving me, it goes a long way.
// Thank you again for teaching me the into to c++!!!!!



