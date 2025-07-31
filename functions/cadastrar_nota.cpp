#include <fstream>
#include <iostream>
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

bool cadastrar_nota(int codigo_disciplina, int matricula_aluno, int notas[3]){
    string file_name = "notas.txt", data;
    bool status;

    data = to_string(codigo_disciplina) + ";" + to_string(matricula_aluno) + ";";
    for(int i = 0; i < 3; i++){
        data += to_string(notas[i]) + ";";
    }

    status = put_in_file(file_name, data);
    if(!status){
        cerr << "Erro ao tentar cadastrar nota!";
        return false;
    }
    return true;
}


int main() {
    int notas[3] = {59,68,84};
    cadastrar_nota(2,15,notas);
}