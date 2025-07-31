#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string aluno_dados_splited[3], disciplina_dados_splited[2], nota_dados_splited[5];
void split_line(string line, char type){
    string value = "";
    int separator_counter = 0;
    
    if(type == 'a'){
        for(char i : line){
            if(i == ';'){
                aluno_dados_splited[separator_counter] = value;
                value = "";
                separator_counter++;
                continue;
            }
            value += i;
        }
    }
    else if(type == 'd'){
        for(char i : line){
            if(i == ';'){
                disciplina_dados_splited[separator_counter] = value;
                value = "";
                separator_counter++;
                continue;
            }
            value += i;
        }
    }
    else if(type == 'n'){
        for(char i : line){
            if(i == ';'){
                nota_dados_splited[separator_counter] = value;
                value = "";
                separator_counter++;
                continue;
            }
            value += i;
        }
    }
}

string get_subjectname_by_id(string subject_id){
    string file_name = "disciplinas.txt";
    ifstream arquivo(file_name);
    
    if(!arquivo.is_open()){
        cerr << "Erro ao tentar abrir arquivo!";
        return "none";
    }
    
    string linha;
    while(getline(arquivo, linha)){
        split_line(linha, 'd');
        if(disciplina_dados_splited[1] == subject_id){
            return disciplina_dados_splited[0];
        }
    }
    
    arquivo.close();
    return "indisponivel";
}

string get_studentname_by_id(string student_id){
    string file_name = "alunos.txt";
    ifstream arquivo(file_name);
    
    if(!arquivo.is_open()){
        cerr << "Erro ao tentar abrir arquivo!";
        return "none";
    }
    
    string linha;
    while(getline(arquivo, linha)){
        split_line(linha, 'a');
        if(aluno_dados_splited[1] == student_id){
            return aluno_dados_splited[0];
        }
    }
    
    arquivo.close();
    return "indisponivel";
}

bool get_student_grades_allsubjects(string matricula){
    string file_name = "notas.txt";
    ifstream arquivo(file_name);
    
    if(!arquivo.is_open()){
        cerr << "Erro ao tentar abrir arquivo!";
        return false;
    }
    
    string linha;
    while(getline(arquivo, linha)){
        split_line(linha, 'n');
        if(nota_dados_splited[1] == matricula){
            cout << "O aluno " << get_studentname_by_id(matricula) << " tem na disciplina: " << get_subjectname_by_id(nota_dados_splited[0]) << ", as notas: "
            << nota_dados_splited[2] << " " << nota_dados_splited[3] << " " << nota_dados_splited[4] << endl;
        }
    }
    
    
    arquivo.close();
    return true;
}

int main(){
    split_line("1;2;100;55;68;", 'n');
    
    for(string i : aluno_dados_splited){
        cout << i << endl;
    }
    for(string i : disciplina_dados_splited){
        cout << i << endl;
    }
    for(string i : nota_dados_splited){
        cout << i << endl;
    }
    
    get_student_grades_allsubjects("2");
    
    cout << get_subjectname_by_id("10");
}