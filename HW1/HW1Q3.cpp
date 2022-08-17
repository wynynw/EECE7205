#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

/**
 * @brief the structure to shore the data of students 
 * @param name  student's name
 * @param grade student's grade
 * */
struct Student
{
    string name;
    int grade;
};

/** 
 * @brief list students
 * sort students by grades in desending order, and display the complete list
 * @param student  the pointer for the struct array
 * @param n        class size
 */
void list(Student *student, int n)
{
    bool swapped;        //whether swap
    struct Student temp; //temp value for swapping
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            //Larger one first
            if (student[j].grade < student[j + 1].grade)
            {
                //swap
                temp = student[j + 1];
                student[j + 1] = student[j];
                student[j] = temp;
                //there is a swap
                swapped = true;
            }
        }
        // all elements are in order
        if (swapped == false)
            break;
    }
    //output the sorted array
    for (int i = 0; i < n; i++)
    {
        cout << "Name: " << student[i].name
             << ", Grade: " << student[i].grade << endl;
    }
}

/** 
 * @brief find the average and median grades and display
 * @param student  the pointer for the struct array
 * @param n        class size
 */
void avgAndMid(Student *student, int n)
{
    int total = 0;
    float mid;
    int flag = n; //end of the array
    for (int i = 0; i < n; i++)
    {
        //calculate the total grade
        total += student[i].grade;
        //move backward to the start of the array
        flag--;
        //for odd array, when i=flag, array[i] is the median
        //for even array, when i+1=flag, their average is median
        if (i == flag || i + 1 == flag)
            mid = (student[i].grade + student[flag].grade) / 2.0;
    }
    float avg = total / float(n); //calcualte the average
    cout << "Average: " << avg << endl;
    cout << "Median: " << mid << endl;
}

/** 
 * @brief find the maximum grade and display it
 * @param student  the pointer for the struct array
 * @param n        class size
 */
void maxGrade(Student *student, int n)
{
    cout << "Student with max grade: " << student[0].name
         << ",The maximum grade: " << student[0].grade << endl;
}

/** 
 * @brief find the minimum grade and display it
 * @param student  the pointer for the struct array
 * @param n        class size
 */
void minGrade(Student *student, int n)
{
    cout << "Student with min grade: " << student[n - 1].name
         << ", The minimum grade: " << student[n - 1].grade << endl;
}

int main()
{
    Student *student; //initialize the structure array
    int n;
    string name; //prevent from the error with directly assign it in sturct
    //get class size
    cout << "Input the class size> ";
    cin >> n;
    //use dynamic memory to create the array.
    student = (Student *)malloc(n * sizeof(Student));
    //get user imput
    for (int i = 0; i < n; i++)
    {
        cout << "Imput the name> ";
        cin >> name;
        student[i].name = name; //assign the name into struct
        cout << "Imput the grade> ";
        cin >> student[i].grade;
    }
    //sort and list all students with descending grades
    list(student, n);
    //display the average and median
    avgAndMid(student, n);
    //display the maximum grade
    maxGrade(student, n);
    //display the minimum grade
    minGrade(student, n);
}
