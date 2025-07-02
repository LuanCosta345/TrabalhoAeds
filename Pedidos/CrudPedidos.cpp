#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include "PedidosClass.cpp"

using namespace std;

vector<Pedido> pedidos;
int proximoId = 1;

void salvarParaArquivo() {
    ofstream ofs("pedidos.bin", ios::binary | ios::trunc);
    for (const auto &p : pedidos) p.salvar(ofs);
}

void carregarDoArquivo() {
    ifstream ifs("pedidos.bin", ios::binary);
    if (!ifs) return;
    Pedido p;
    while (true) {
        ifs.read(reinterpret_cast<char*>(&p), sizeof(Pedido));
        if (!ifs) break;
        pedidos.push_back(p);
        if (p.getId() >= proximoId) proximoId = p.getId() + 1;
    }
}

void criarPedido() {
    float valor;
    int quantidade;
    cout << "Valor unitário: ";
    while (!(cin >> valor)) {
        cout << "Valor inválido. Tente novamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Quantidade: ";
    while (!(cin >> quantidade) || quantidade < 1) {
        cout << "Quantidade inválida (>=1). Tente novamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore();
    char desc[100];
    cout << "Descrição (máx 99 chars): ";
    cin.getline(desc, sizeof(desc));

    int partida, destino;
    cout << "ID da partida: ";
    cin >> partida;
    cout << "ID do destino: ";
    cin >> destino;

    Pedido p(proximoId++, desc, valor, quantidade);
    p.setPartida(partida);
    p.setDestino(destino);

    pedidos.push_back(p);
    salvarParaArquivo();

    cout << "Criado ID " << p.getId() 
         << ", Total R$" << p.getValorTotal() << "\n";
}

void listarPedidos() {
    if (pedidos.empty()) {
        cout << "Nenhum pedido.\n";
        return;
    }
    for (auto &p : pedidos) {
        cout << "ID " << p.getId()
             << " | " << p.getDescricao() 
             << " | R$" << p.getValor() << " x " << p.getQuantidade()
             << " = R$" << p.getValorTotal()
             << " | Partida: " << p.getPartida()
             << " | Destino: " << p.getDestino()
             << "\n";
    }
}

void atualizarPedido() {
    int id;
    cout << "ID para atualizar: ";
    cin >> id;
    cin.ignore();
    for (auto &p : pedidos) {
        if (p.getId() == id) {
            float novoValor;
            int novaQuantidade;
            cout << "Novo valor unitário: ";
            while (!(cin >> novoValor)) {
                cout << "Valor inválido. Tente novamente: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Nova quantidade: ";
            while (!(cin >> novaQuantidade) || novaQuantidade < 1) {
                cout << "Quantidade inválida (>=1). Tente novamente: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cin.ignore();
            char desc[100];
            cout << "Nova descrição: ";
            cin.getline(desc, sizeof(desc));

            int novaPartida, novoDestino;
            cout << "Novo ID de partida: ";
            cin >> novaPartida;
            cout << "Novo ID de destino: ";
            cin >> novoDestino;

            p.setValor(novoValor);
            p.setQuantidade(novaQuantidade);
            p.setDescricao(desc);
            p.setPartida(novaPartida);
            p.setDestino(novoDestino);

            salvarParaArquivo();
            cout << "Atualizado ID " << id 
                 << ", Total R$" << p.getValorTotal() << "\n";
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
        if (it->getId() == id) {
            pedidos.erase(it);
            salvarParaArquivo();
            cout << "Deletado.\n";
            return;
        }
    }
    cout << "ID não encontrado.\n";
}

void mostrarMenu() {
    cout << "\n--- Menu de Pedidos ---\n"
         << "[1] Cadastrar pedidos\n"
         << "[2] Listar pedidos\n"
         << "[3] Atualizar pedidos\n"
         << "[4] Deletar pedidos\n"
         << "[0] Sair\n"
         << "Escolha uma opção: ";
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
