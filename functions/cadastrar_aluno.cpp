#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool put_in_file(string file_name, string data) {
  ofstream file;
  file.open(file_name, ios::app);
  if (file.is_open()) {
    file << data << endl;
    file.close();
    return true;
  }
  return false;
}

int get_line_number(string file_name) {
  ifstream file;
  file.open(file_name);
  int line_number = 0;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      line_number++;
    }
    file.close();
  }
  return line_number;
}

bool cadastrar_aluno(string nome, string turma){
    string file_name = "alunos.txt", data;
    int matricula;
    bool status;

    matricula = get_line_number(file_name) + 1;

    data = nome + ";" + to_string(matricula) + ";" + turma + ";";

    status = put_in_file(file_name, data);
    if(!status){
        cerr << "Erro ao tentar cadastrar aluno!";
        return false;
    }
    return true;
}

int main()
{   
    string nome = "nicolas", turma="ads";
    cadastrar_aluno(nome, turma);

    return 0;
}