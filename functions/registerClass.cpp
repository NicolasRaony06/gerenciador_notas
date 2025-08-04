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