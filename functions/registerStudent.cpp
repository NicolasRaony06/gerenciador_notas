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