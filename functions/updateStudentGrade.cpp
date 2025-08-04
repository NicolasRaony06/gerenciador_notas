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