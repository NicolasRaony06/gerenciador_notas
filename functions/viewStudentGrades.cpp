void viewStudentGrades() {
  string studentName;
  cout << "Enter student code or name: ";
  cin >> studentName;

  string lines[MAX_LINES];
  int numLines = getAllLines("grades.txt", lines);

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