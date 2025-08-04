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