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