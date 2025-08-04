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