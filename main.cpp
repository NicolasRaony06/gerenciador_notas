#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX_LINES = 1000;
const int MAX_COLUMNS = 20;

// Funcionalidade: Divide linhas de um array de strings em um array 2D com base em um delimitador.
// Retorno: void
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

// Funcionalidade: Lê todas as linhas de um arquivo para um array de strings no estilo C.
// Retorno: O número de linhas lidas ou 0 caso o arquivo não possa ser aberto.
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

// Funcionalidade: Adiciona uma string de dados ao final de um arquivo.
// Retorno: True se os dados foram escritos com sucesso, false caso contrário.
bool putInFile(string fileName, string data) {
  ofstream file(fileName, ios::app);
  if (file.is_open()) {
    file << data << endl;
    file.close();
    return true;
  }
  return false;
}

// Funcionalidade: Conta o número de linhas em um arquivo.
// Retorno: O número de linhas no arquivo.
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

// Funcionalidade: Cadastra uma nova disciplina solicitando ao usuário o nome e gerando o código automaticamente.
// Retorno: True se o cadastro for bem-sucedido, false caso contrário.
bool registerSubject() {
  string fileName = "disciplinas.txt";
  string subjectName;
  cout << "Enter subject name: ";
  cin >> subjectName;
  if (subjectName != "") {
    int subjectCode = getLineNumber(fileName) + 1;
    if (subjectCode <= 0) {
      cout << "Invalid subject code!" << endl;
      return false;
    }
    string data = subjectName + ";" + to_string(subjectCode);
    return putInFile(fileName, data);
  }
  return false;
}

// Funcionalidade: Cadastra um novo aluno, gerando automaticamente um código.
// Retorno: True se o cadastro for bem-sucedido, false caso contrário.
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

// Funcionalidade: Cadastra uma nova turma com um nome e um código gerado automaticamente.
// Retorno: True se o cadastro for bem-sucedido, false caso contrário.
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

// Funcionalidade: Busca uma string de consulta nas duas primeiras colunas de um arquivo fornecido.
// Retorno: O índice da linha encontrada, ou -1 se não encontrada.
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

// Funcionalidade: Procura um aluno e disciplina específicos no arquivo de notas.
// Retorno: O índice da linha de nota encontrada, ou -1 se não encontrada.
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

// Funcionalidade: Sobrescreve um arquivo com o conteúdo de um array de strings no estilo C.
// Retorno: void
void updateData(string fileName, string lines[MAX_LINES], int numLines) {
  ofstream file(fileName);
  if (file.is_open()) {
    for (int i = 0; i < numLines; i++) {
      file << lines[i] << endl;
    }
    file.close();
  }
}

// Funcionalidade: Adiciona o código de uma disciplina à linha de dados de uma turma existente no arquivo.
// Retorno: True se a atribuição for bem-sucedida, false caso contrário.
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
  if (search("turmas.txt", subjectQuery) == -1) {
    cout << "Invalid subject code!" << endl;
    return false;
  }

  line += subjectQuery + ";";
  updateData(fileName, lines, numLines);
  return true;
}

// Funcionalidade: Adiciona ou atualiza a nota de um aluno para uma disciplina e período específicos.
// Retorno: True se a atualização for bem-sucedida, false caso contrário.
bool updateStudentGrade() {
  string fileName = "notas.txt";
  string studentQuery;
  cout << "Enter student code or name: ";
  cin >> studentQuery;
  if (studentQuery == "") {
    cout << "Invalid student code or name!" << endl;
    return false;
  }
  if (search("alunos.txt", studentQuery) == -1) {
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
  if (search("disciplinas.txt", subjectQuery) == -1) {
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


/**
 * @brief Converte uma string para inteiro.
 * @param s A string a ser convertida.
 * @return O valor inteiro, ou -1 se a string não for um número válido.
 */
int stringToInt(const std::string& s) {
    int result = 0;
    for (char c : s) {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        } else {
            return -1;
        }
    }
    return result;
}

// Funcionalidade: Calcula a média geral de um aluno em todas as disciplinas.
// Retorno: A média calculada como float, ou -1 se nenhuma nota for encontrada.
float calculateStudentOverallAverage(const string& studentId) {
    string lines[MAX_LINES];
    int numLines = getAllLines("notas.txt", lines);

    float sum = 0.0f;
    int totalGrades = 0;

    for (int i = 0; i < numLines; ++i) {
        string line = lines[i];

        if (line.find(studentId + ";") != 0) {
            continue;
        }

        size_t firstSemicolon = line.find(';');
        if (firstSemicolon == std::string::npos) continue;

        size_t secondSemicolon = line.find(';', firstSemicolon + 1);
        if (secondSemicolon == std::string::npos) {

            secondSemicolon = line.length() - 1;
        }

        string gradeString = line.substr(secondSemicolon + 1);

        size_t startPos = 0;
        while (startPos < gradeString.length()) {
            size_t colonPos = gradeString.find(':', startPos);
            if (colonPos == std::string::npos) break;

            size_t endPos = gradeString.find(';', colonPos + 1);
            if (endPos == std::string::npos) {
                endPos = gradeString.length();
            }

            string gradeSub = gradeString.substr(colonPos + 1, endPos - colonPos - 1);

            int grade = stringToInt(gradeSub);


            if (grade != -1) {
                sum += grade;
                totalGrades++;
            }

            startPos = endPos + 1;
        }
    }


    return (totalGrades > 0) ? sum / totalGrades : -1.0f;
}

// Funcionalidade: Exibe todas as notas e a média geral de um aluno fornecido a partir do arquivo.
// Retorno: void
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

// Funcionalidade: Exibe todas as notas de uma disciplina específica entre todos os alunos.
// Retorno: void
void viewSubjectGrades() {
  string subjectName;
  cout << "Enter subject code or name: ";
  cin >> subjectName;

  string lines[MAX_LINES];
  int numLines = getAllLines("notas.txt", lines);

  cout << "Grades in subject " << subjectName << ":\n";
  for (int i = 0; i < numLines; i++) {
    if (lines[i].find(";" + subjectName + ";") != string::npos) {
      cout << lines[i] << endl;
    }
  }
}

// Funcionalidade: Cria um arquivo de texto chamado 'relatorio.txt' com todas as notas registradas.
// Retorno: void
void generateReport() {
  ofstream outFile("relatorio.txt");
  if (!outFile.is_open()) {
    cout << "Error creating report file!\n";
    return;
  }

  string lines[MAX_LINES];
  string data[MAX_LINES][MAX_COLUMNS];
  int colSizes[MAX_LINES];

  
  int numLines = getAllLines("notas.txt", lines);
  mapFunction(lines, numLines, data, colSizes);
  outFile << "Grades Report\n------------------\n";
  for (int i = 0; i < numLines; i++) {
      float averrage = calculateStudentOverallAverage(data[i][0]);
      outFile << lines[i] << "; media: " << averrage << endl;
  }

  outFile.close();
  cout << "Report saved to relatorio.txt\n";
}

// Funcionalidade: Loop principal da aplicação que exibe um menu e chama outras funções com base na entrada do usuário.
// Retorno: void
void menu() {
  for (;;) {
    cout << "\n--- MENU ---\n";
    cout << "1 - Cadastrar disciplina\n";
    cout << "2 - Cadastrar aluno\n";
    cout << "3 - Cadastrar turma\n";
    cout << "4 - Atribuir disciplina à turma\n";
    cout << "5 - Atualizar nota do aluno\n";
    cout << "6 - Visualizar notas do aluno\n";
    cout << "7 - Visualizar notas da disciplina\n";
    cout << "8 - Gerar relatório\n";
    cout << "0 - Sair\n";
    cout << "Digite a opção: ";

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

// Funcionalidade: Ponto de entrada do programa. Chama a função do menu principal.
// Retorno: 0 ao final da execução bem-sucedida.
int main() {
  menu();
  return 0;
}
