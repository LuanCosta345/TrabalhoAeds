#include "LocaisClass.cpp"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<Local> locais;
const string ARQUIVO_LOCAIS = "locais.txt";

void salvarLocaisEmArquivo() {
    ofstream arquivo(ARQUIVO_LOCAIS);
    for (auto &l : locais) {
        arquivo << l.getNome() << ';' << l.getCoordenadaX() << ';' << l.getCoordenadaY() << '\n';
    }
    arquivo.close();
}

void lerLocaisDoArquivo() {
    locais.clear();
    ifstream arquivo(ARQUIVO_LOCAIS);
    if (!arquivo.is_open()) return;
    string linha;
    while (getline(arquivo, linha)) {
        size_t p1 = linha.find(';');
        size_t p2 = linha.rfind(';');
        if (p1 == string::npos || p2 == string::npos || p1 == p2) continue;
        string nome = linha.substr(0, p1);
        float x = stof(linha.substr(p1+1, p2-p1-1));
        float y = stof(linha.substr(p2+1));
        locais.push_back(Local(nome, x, y));
    }
    arquivo.close();
}

void criarLocal() {
    lerLocaisDoArquivo();
    string nome;
    float x, y;
    cout << "Digite o nome do local: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite a coordenada X: ";
    cin >> x;
    cout << "Digite a coordenada Y: ";
    cin >> y;
    for (auto &l : locais) {
        if (l.getNome() == nome) {
            cout << "Local já cadastrado!\n";
            return;
        }
    }
    locais.push_back(Local(nome, x, y));
    salvarLocaisEmArquivo();
    cout << "Local cadastrado com sucesso!\n";
}

void listarLocais() {
    lerLocaisDoArquivo();
    if (locais.empty()) {
        cout << "Nenhum local cadastrado.\n";
        return;
    }
    cout << "Lista de Locais:\n";
    for (auto &l : locais) {
        cout << "Nome: " << l.getNome() << ", X: " << l.getCoordenadaX() << ", Y: " << l.getCoordenadaY() << endl;
    }
}

void atualizarLocal() {
    lerLocaisDoArquivo();
    string nome;
    cout << "Digite o nome do local a ser atualizado: ";
    cin.ignore();
    getline(cin, nome);
    for (auto &l : locais) {
        if (l.getNome() == nome) {
            float x, y;
            cout << "Digite a nova coordenada X: ";
            cin >> x;
            cout << "Digite a nova coordenada Y: ";
            cin >> y;
            l.setCoordenadaX(x);
            l.setCoordenadaY(y);
            salvarLocaisEmArquivo();
            cout << "Local atualizado com sucesso!\n";
            return;
        }
    }
    cout << "Local não encontrado!\n";
}

void deletarLocal() {
    lerLocaisDoArquivo();
    string nome;
    cout << "Digite o nome do local a ser deletado: ";
    cin.ignore();
    getline(cin, nome);
    for (auto it = locais.begin(); it != locais.end(); ++it) {
        if (it->getNome() == nome) {
            locais.erase(it);
            salvarLocaisEmArquivo();
            cout << "Local deletado com sucesso!\n";
            return;
        }
    }
    cout << "Local não encontrado!\n";
}

int main() {
    int opcao;
    do {
        cout << "\n--- Menu Locais ---\n";
        cout << "1. Cadastrar Local\n";
        cout << "2. Listar Locais\n";
        cout << "3. Atualizar Local\n";
        cout << "4. Deletar Local\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        switch (opcao) {
            case 1: criarLocal(); break;
            case 2: listarLocais(); break;
            case 3: atualizarLocal(); break;
            case 4: deletarLocal(); break;
            case 0: cout << "Saindo...\n"; break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
    return 0;
} 