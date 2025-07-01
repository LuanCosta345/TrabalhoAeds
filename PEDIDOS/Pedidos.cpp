#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <fstream>

using namespace std;

struct Pedido {
    int id;
    double valor;
    char descricao[100];
};

vector<Pedido> pedidos;
int proximoId = 1;

void salvarParaArquivo() {
    ofstream ofs("pedidos.bin", ios::binary | ios::trunc);
    for (auto &p : pedidos) {
        ofs.write(reinterpret_cast<char*>(&p), sizeof(Pedido));
    }
}

void carregarDoArquivo() {
    ifstream ifs("pedidos.bin", ios::binary);
    if (!ifs) return;
    Pedido p;
    while (ifs.read(reinterpret_cast<char*>(&p), sizeof(Pedido))) {
        pedidos.push_back(p);
        if (p.id >= proximoId) proximoId = p.id + 1;
    }
}

void criarPedido() {
    Pedido p;
    p.id = proximoId++;
    cout << "Valor: ";
    while (!(cin >> p.valor)) {
        cout << "Valor inválido. Tente novamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    cout << "Descrição (máx 99 chars): ";
    cin.getline(p.descricao, sizeof p.descricao);
    pedidos.push_back(p);
    salvarParaArquivo();
    cout << "Criado ID " << p.id << "\n";
}

void listarPedidos() {
    if (pedidos.empty()) {
        cout << "Nenhum pedido.\n";
        return;
    }
    for (auto &p : pedidos) {
        cout << "ID " << p.id 
             << " | R$" << p.valor 
             << " | " << p.descricao << "\n";
    }
}

void atualizarPedido() {
    int id;
    cout << "ID para atualizar: ";
    cin >> id;
    cin.ignore();
    for (auto &p : pedidos) {
        if (p.id == id) {
            cout << "Novo valor: ";
            while (!(cin >> p.valor)) {
                cout << "Valor inválido. Tente novamente: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();
            cout << "Nova descrição: ";
            cin.getline(p.descricao, sizeof p.descricao);
            salvarParaArquivo();
            cout << "Atualizado.\n";
            return;
        }
    }
    cout << "ID não encontrado.\n";
}

void deletarPedido() {
    int id;
    cout << "ID para deletar: ";
    cin >> id;
    for (auto it = pedidos.begin(); it != pedidos.end(); ++it) {
        if (it->id == id) {
            pedidos.erase(it);
            salvarParaArquivo();
            cout << "Deletado.\n";
            return;
        }
    }
    cout << "ID não encontrado.\n";
}

void mostrarMenu() {
    cout << "\n--- Menu de Pedidos ---\n";
    cout << "[1] Cadastrar pedidos\n";
    cout << "[2] Listar pedidos\n";
    cout << "[3] Atualizar pedidos\n";
    cout << "[4] Deletar pedidos\n";
    cout << "[0] Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    carregarDoArquivo();
    int opc;
    do {
        mostrarMenu();
        cin >> opc;
        switch (opc) {
            case 1: criarPedido(); break;
            case 2: listarPedidos(); break;
            case 3: atualizarPedido(); break;
            case 4: deletarPedido(); break;
            case 0: cout << "Saindo...\n"; break;
            default: cout << "Opção inválida.\n";
        }
    } while (opc != 0);
    return 0;
}
