# 📚 Sistema de Gerenciamento de Notas Escolares

Este projeto acadêmico foi desenvolvido em C++ com o objetivo de criar um sistema simples para **gerenciar notas escolares**. Ele permite o cadastro de alunos, disciplinas, turmas, lançamento de notas, cálculo de médias e geração de relatórios. Os dados são persistidos em arquivos `.txt`.

> Projeto desenvolvido como parte das atividades do curso de Análise e Desenvolvimento de Sistemas.

---

## ✨ Funcionalidades

- 📌 Cadastro de alunos, disciplinas e turmas
- 📋 Associação de disciplinas às turmas
- 📝 Lançamento de notas por disciplina e período
- 📊 Cálculo de médias por disciplina e média geral
- 🔍 Consulta de notas por aluno ou disciplina
- 🗂️ Geração de relatórios em arquivo `.txt`

---

## 🛠️ Tecnologias e Conceitos Utilizados

- Linguagem: **C++**
- Manipulação de arquivos (`fstream`)
- Matrizes e arrays bidimensionais
- Funções modulares
- Estruturas condicionais e de repetição
- Separação de dados com delimitador (`;`)

---

## 📂 Estrutura dos Arquivos

- `main.cpp`: Arquivo principal com toda a lógica do sistema.
- `alunos.txt`: Alunos cadastrados.
- `disciplinas.txt`: Disciplinas cadastradas.
- `turmas.txt`: Turmas e as disciplinas associadas.
- `notas.txt`: Notas dos alunos por disciplina e período.
- `relatorio.txt`: Relatório gerado com as notas.

---

## ▶️ Como Usar

1. **Compile o projeto** com um compilador C++, por exemplo:

   ```bash
   g++ main.cpp -o gerenciador_notas
   ```

2. **Execute o programa:**

   ```bash
   ./gerenciador_notas
   ```

3. **Navegue pelo menu interativo**, com opções como:

   - Registrar aluno, disciplina ou turma
   - Lançar ou atualizar notas
   - Consultar notas por aluno ou disciplina
   - Gerar relatório de desempenho

---

## 📌 Exemplo de Uso

```text
--- MENU ---
1 - Register subject
2 - Register student
3 - Register class
4 - Assign subject to class
5 - Update student grade
6 - View student grades
7 - View subject grades
8 - Generate report
0 - Exit
Enter option:
```

---

## ✅ Requisitos

- Compilador C++ (g++ recomendado)
- Terminal interativo para entrada de dados
- Sistema operacional compatível com leitura/escrita de arquivos `.txt`

---