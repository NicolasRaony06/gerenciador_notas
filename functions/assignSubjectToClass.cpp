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