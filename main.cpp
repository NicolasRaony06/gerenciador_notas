#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX_LINES = 1000;
const int MAX_COLUMNS = 20;

// functionality: Splits lines from a string array into a 2D array based on a
// delimiter. return: void
void mapFunction(string lines[], int numLines,
                 string mapped[MAX_LINES][MAX_COLUMNS],
                 int colSizes[MAX_LINES]) {
  for (int i = 0; i < numLines; i++) {
    string temp = "";
    int col = 0;
    for (char c : lines[i]) {
      if (c == ';') {
        mapped[i][col++] = temp;
        temp = "";
      } else {
        temp += c;
      }
    }
    if (!temp.empty() || lines[i].back() == ';') {
      mapped[i][col++] = temp;
    }
    colSizes[i] = col;
  }
}

// functionality: Reads all lines from a file into a C-style string array.
// return: The number of lines read, or 0 if the file can't be opened.
int getAllLines(string fileName, string lines[MAX_LINES]) {
  ifstream file(fileName);
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return 0;
  }

  int i = 0;
  while (getline(file, lines[i]) && i < MAX_LINES) {
    i++;
  }
  file.close();
  return i;
}

// functionality: Appends a string of data to the end of a file.
// return: True if the data was successfully written, false otherwise.
bool putInFile(string fileName, string data) {
  ofstream file(fileName, ios::app);
  if (file.is_open()) {
    file << data << endl;
    file.close();
    return true;
  }
  return false;
}

// functionality: Registers a new subject by prompting the user for its name and
// code. return: True if registration is successful, false otherwise.
bool registerSubject() {
  string fileName = "disciplinas.txt";
  string subjectName;
  cout << "Enter subject name: ";
  cin >> subjectName;
  if (subjectName != "") {
    int subjectCode;
    cout << "Enter subject code: ";
    cin >> subjectCode;
    if (subjectCode <= 0) {
      cout << "Invalid subject code!" << endl;
      return false;
    }
    string data = subjectName + ";" + to_string(subjectCode);
    return putInFile(fileName, data);
  }
  return false;
}

// functionality: Counts the number of lines in a file.
// return: The number of lines in the file.
int getLineNumber(string fileName) {
  ifstream file(fileName);
  int lineNumber = 0;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      lineNumber++;
    }
    file.close();
  }
  return lineNumber;
}

// functionality: Registers a new student, automatically generating a code.
// return: True if registration is successful, false otherwise.
bool registerStudent() {
  string fileName = "alunos.txt";
  string studentName;
  cout << "Enter student name: ";
  cin >> studentName;
  if (studentName != "") {
    int studentCode = getLineNumber(fileName) + 1;
    string courseName;
    cout << "Enter course name: ";
    cin >> courseName;
    if (courseName == "") {
      cout << "Invalid course name!" << endl;
      return false;
    }
    string data = studentName + ";" + to_string(studentCode) + ";" + courseName;
    return putInFile(fileName, data);
  }
  return false;
}

// functionality: Registers a new class with a name and auto-generated code.
// return: True if registration is successful, false otherwise.
bool registerClass() {
  string fileName = "turmas.txt";
  string className;
  cout << "Enter class name: ";
  cin >> className;
  if (className == "") {
    cout << "Invalid class name!" << endl;
    return false;
  }
  int classCode = getLineNumber(fileName) + 1;
  string data = className + ";" + to_string(classCode) + ";";
  return putInFile(fileName, data);
}

// functionality: Searches for a query string in the first two columns of a
// given file. return: The index of the found line, or -1 if not found.
int search(string fileName, string query) {
  string lines[MAX_LINES];
  int numLines = getAllLines(fileName, lines);
  string data[MAX_LINES][MAX_COLUMNS];
  int colSizes[MAX_LINES];

  mapFunction(lines, numLines, data, colSizes);

  for (int i = 0; i < numLines; i++) {
    for (int j = 0; j < min(2, colSizes[i]); j++) {
      if (data[i][j] == query) {
        return i;
      }
    }
  }
  return -1;
}

// functionality: Searches for a specific student and subject in the grades
// file. return: The index of the found grade line, or -1 if not found.
int searchGrade(string fileName, string query) {
  string lines[MAX_LINES];
  int numLines = getAllLines(fileName, lines);
  string data[MAX_LINES][MAX_COLUMNS];
  int colSizes[MAX_LINES];

  mapFunction(lines, numLines, data, colSizes);

  size_t sep = query.find(';');
  if (sep == string::npos)
    return -1;
  string q0 = query.substr(0, sep);
  string q1 = query.substr(sep + 1);

  for (int i = 0; i < numLines; i++) {
    if (colSizes[i] >= 2 && data[i][0] == q0 && data[i][1] == q1) {
      return i;
    }
  }
  return -1;
}

// functionality: Overwrites a file with the content of a C-style string array.
// return: void
void updateData(string fileName, string lines[MAX_LINES], int numLines) {
  ofstream file(fileName);
  if (file.is_open()) {
    for (int i = 0; i < numLines; i++) {
      file << lines[i] << endl;
    }
    file.close();
  }
}

// functionality: Appends a subject's code to an existing class's data line in
// the file. return: True if the assignment is successful, false otherwise.
bool assignSubjectToClass() {
  string fileName = "turmas.txt";
  string classQuery;
  cout << "Enter class code or name: ";
  cin >> classQuery;
  if (classQuery == "") {
    cout << "Invalid code or name!" << endl;
    return false;
  }
  int local = search(fileName, classQuery);
  if (local == -1) {
    cout << "Invalid class code!" << endl;
    return false;
  }

  string lines[MAX_LINES];
  int numLines = getAllLines(fileName, lines);
  string &line = lines[local];

  string subjectQuery;
  cout << "Enter subject code or name: ";
  cin >> subjectQuery;
  if (subjectQuery == "") {
    cout << "Invalid subject code or name!" << endl;
    return false;
  }
  if (search("subjects.txt", subjectQuery) == -1) {
    cout << "Invalid subject code!" << endl;
    return false;
  }

  line += subjectQuery + ";";
  updateData(fileName, lines, numLines);
  return true;
}

// functionality: Adds or updates a student's grade for a specific subject and
// period. return: True if the update is successful, false otherwise.
bool updateStudentGrade() {
  string fileName = "grades.txt";
  string studentQuery;
  cout << "Enter student code or name: ";
  cin >> studentQuery;
  if (studentQuery == "") {
    cout << "Invalid student code or name!" << endl;
    return false;
  }
  if (search("students.txt", studentQuery) == -1) {
    cout << "Invalid student code!" << endl;
    return false;
  }
  string subjectQuery;
  cout << "Enter subject code or name: ";
  cin >> subjectQuery;
  if (subjectQuery == "") {
    cout << "Invalid subject code or name!" << endl;
    return false;
  }
  if (search("subjects.txt", subjectQuery) == -1) {
    cout << "Invalid subject code!" << endl;
    return false;
  }
  int period;
  cout << "Enter period (1 to 4): ";
  cin >> period;
  if (period < 1 || period > 4) {
    cout << "Invalid period!" << endl;
    return false;
  }
  int grade;
  cout << "Enter grade: ";
  cin >> grade;
  if (grade < 0 || grade > 100) {
    cout << "Invalid grade!" << endl;
    return false;
  }
  string query = studentQuery + ";" + subjectQuery;
  int pos = searchGrade(fileName, query);
  if (pos != -1) {
    string lines[MAX_LINES];
    int numLines = getAllLines(fileName, lines);
    string &line = lines[pos];
    if (!line.empty() && line.back() != ';')
      line += ";";
    line += to_string(period) + ":" + to_string(grade);
    updateData(fileName, lines, numLines);
    return true;
  } else {
    string data = studentQuery + ";" + subjectQuery + ";" + to_string(period) +
                  ":" + to_string(grade);
    return putInFile(fileName, data);
  }
}

// functionality: Calculates the average grade for a student in a specific
// subject from the file. return: The calculated average as a float, or -1 if no
// grades are found.
float calculateStudentSubjectAverage(const string &studentName,
                                     const string &subjectName) {
  string lines[MAX_LINES];
  int numLines = getAllLines("grades.txt", lines);

  for (int i = 0; i < numLines; i++) {
    string line = lines[i];
    if (line.find(studentName + ";" + subjectName) != 0)
      continue;

    float sum = 0;
    int count = 0;
    size_t pos = line.find_last_of(";");
    if (pos == string::npos)
      return -1;

    string grades = line.substr(pos + 1);
    size_t start = 0, end;
    while ((end = grades.find(":", start)) != string::npos) {
      start = grades.find(":", end) + 1;
      int grade =
          stoi(grades.substr(end + 1, grades.find(";", end + 1) - end - 1));
      sum += grade;
      count++;
      if (grades.find(";", end) == string::npos)
        break;
      end = grades.find(";", end);
      start = end + 1;
    }

    return (count > 0) ? sum / count : -1;
  }

  return -1;
}

// functionality: Calculates the overall average grade for a student across all
// subjects. return: The calculated average as a float, or -1 if no grades are
// found.
float calculateStudentOverallAverage(const string &studentName) {
  string lines[MAX_LINES];
  int numLines = getAllLines("grades.txt", lines);

  float sum = 0;
  int total = 0;

  for (int i = 0; i < numLines; i++) {
    if (lines[i].find(studentName + ";") != 0)
      continue;

    string line = lines[i];
    size_t pos = line.find_last_of(";");
    string grades = line.substr(pos + 1);

    size_t start = 0, end;
    while ((end = grades.find(":", start)) != string::npos) {
      start = grades.find(":", end) + 1;
      int grade =
          stoi(grades.substr(end + 1, grades.find(";", end + 1) - end - 1));
      sum += grade;
      total++;
      if (grades.find(";", end) == string::npos)
        break;
      end = grades.find(";", end);
      start = end + 1;
    }
  }

  return (total > 0) ? sum / total : -1;
}

// functionality: Displays all grades and the overall average for a given
// student from the file. return: void
void viewStudentGrades() {
  string studentName;
  cout << "Enter student code or name: ";
  cin >> studentName;

  string lines[MAX_LINES];
  int numLines = getAllLines("notas.txt", lines);

  cout << "Grades for " << studentName << ":\n";
  for (int i = 0; i < numLines; i++) {
    if (lines[i].find(studentName + ";") == 0) {
      cout << lines[i] << endl;
    }
  }

  float overallAverage = calculateStudentOverallAverage(studentName);
  if (overallAverage >= 0)
    cout << "Overall average: " << overallAverage << endl;
  else
    cout << "No grades registered.\n";
}

// functionality: Displays all grades for a specific subject across all
// students. return: void
void viewSubjectGrades() {
  string subjectName;
  cout << "Enter subject code or name: ";
  cin >> subjectName;

  string lines[MAX_LINES];
  int numLines = getAllLines("grades.txt", lines);

  cout << "Grades in subject " << subjectName << ":\n";
  for (int i = 0; i < numLines; i++) {
    if (lines[i].find(";" + subjectName + ";") != string::npos) {
      cout << lines[i] << endl;
    }
  }
}

// functionality: Creates a text file named 'report.txt' with all recorded
// grades. return: void
void generateReport() {
  ofstream outFile("relatorio.txt");
  if (!outFile.is_open()) {
    cout << "Error creating report file!\n";
    return;
  }

  string lines[MAX_LINES];
  int numLines = getAllLines("notas.txt", lines);

  outFile << "Grades Report\n------------------\n";
  for (int i = 0; i < numLines; i++) {
    outFile << lines[i] << endl;
  }

  outFile.close();
  cout << "Report saved to report.txt\n";
}

// functionality: Main application loop that displays a menu and calls other
// functions based on user input. return: void
void menu() {
  for (;;) {
    cout << "\n--- MENU ---\n";
    cout << "1 - Register subject\n";
    cout << "2 - Register student\n";
    cout << "3 - Register class\n";
    cout << "4 - Assign subject to class\n";
    cout << "5 - Update student grade\n";
    cout << "6 - View student grades\n";
    cout << "7 - View subject grades\n";
    cout << "8 - Generate report\n";
    cout << "0 - Exit\n";
    cout << "Enter option: ";

    int option;
    cin >> option;

    switch (option) {
    case 1:
      registerSubject();
      break;
    case 2:
      registerStudent();
      break;
    case 3:
      registerClass();
      break;
    case 4:
      assignSubjectToClass();
      break;
    case 5:
      updateStudentGrade();
      break;
    case 6:
      viewStudentGrades();
      break;
    case 7:
      viewSubjectGrades();
      break;
    case 8:
      generateReport();
      break;
    case 0:
      return;
    default:
      cout << "Invalid option!\n";
      break;
    }
  }
}

// functionality: The program's entry point. Calls the main menu function.
// return: 0 upon successful execution.
int main() {
  menu();
  return 0;
}
