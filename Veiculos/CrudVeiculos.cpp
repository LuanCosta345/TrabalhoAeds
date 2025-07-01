#include "VeiculoClass.cpp"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class CrudVeiculos {
    public:
    //Não é uma boa pratica mas é impossivel eu fazer o 4 sem isso aqui ser public
    vector<Veiculo> veiculos;

    /* TODO: lerVeiculosDoArquivo, salvarVeiculosDoArquivo
    acho que não faz sentido ficar chamando lerDOarquivo em todo metodo, e sim ser um mettodo no menu sla*/

    void criarVeiculo() {
        //lerLocaisDoArquivo();
        char placa[100], modelo[100], localNome[100];
        Estado estado;
        cout << "Digite a placa do veiculo: ";
        cin.getline(placa, 100);
        //Verificação da placa
        for (auto& v : veiculos) {
            if (!strcmp(placa, v.getPlaca)) {
                cout << "Veículo já cadastrado!\n";
                return;
            }
        }
        cout << "Digite o modelo do veiculo: ";
        cin.getline(modelo, 100);
        cout << "Digite o nome do local: ";
        cin.getline(localNome, 100);
        Local local = getLocal(localNome);
        if(!local){
            cout << "É necessário cadastrar um local primeiro!"
            return;
        }
        veiculos.push_back(Veiculo(placa, modelo, local));
        // salvarLocaisEmArquivo();
        cout << "Local cadastrado com sucesso!\n";
    }

    void listarVeiculos() {
        //lerLocaisDoArquivo();
        if (veiculos.empty()) {
            cout << "Nenhum veículo cadastrado.\n";
            return;
        }
        cout << "Lista de Veiculos:\n";
        for (auto&  v : veiculos) {
            cout << "Placa: " << v.getPlaca() 
            << ", Modelo: " << v.getModelo() 
            << ", Estado: " << estadoPraString(v.getEstado())
            << ", Local: " << v.getLocal().getNome << endl;
        }
    }

    void atualizarLocal() {
        //lerLocaisDoArquivo();
        char placa[100];
        cout << "Digite a placa do local a ser atualizado: ";
        cin.getline(placa, 100);
        for (auto& v: veiculos) {
            if (!strcmp(placa, v.getPlaca)) {
                char modelo[100], nomeLocal[100];
                cout << "Digite o novo modelo do veiculo: ";
                cin.getline(modelo, 100);
                cout << "Digite o nome do local: ";
                cin.getline(localNome, 100);
                Local local = getLocal(localNome);
                if(!local){
                    cout << "É necessário cadastrar um local primeiro!"
                    return;
                }
                v.setModelo(modelo);
                v.setLocal(local);
                //salvarLocaisEmArquivo();
                cout << "Veiculo atualizado com sucesso!\n";
                return;
            }
        }
        cout << "Local não encontrado!\n";
    }

    void deletarVeiculo() {
        //lerLocaisDoArquivo();
        char placa[100];
        cout << "Digite a placa do veiculo a ser deletado: ";
        cin.getline(nome, 100);
        for (auto& v : veiculos) {
            if (v.getPlaca() == placa) {
                veiculos.erase(v);
                //salvarLocaisEmArquivo();
                cout << "Veiculo deletado com sucesso!\n";
                return;
            }
        }
        cout << "Veiculo não encontrado!\n";
    }

    // Precisa dessa funçao pra conseguir printar o Estado do Enum
    char *estadoPraString(Estado estado) const {
        switch (estado) {
            case DISPONIVEL:
                return "Disponivel";
            case OCUPADO:
                return "Ocupado";
        }
    }

    int menu() {
        int opcao;
        do {
            cout << "\n--- Menu Veículos ---\n";
            cout << "1. Cadastrar Veículo\n";
            cout << "2. Listar Veículos\n";
            cout << "3. Atualizar Veículo\n";
            cout << "4. Deletar Veículo\n";
            cout << "0. Sair\n";
            cout << "Escolha uma opção: ";
            cin >> opcao;
            switch (opcao) {
                case 1: criarVeiculo(); break;
                case 2: listarVeiculos(); break;
                case 3: atualizarVeiculo(); break;
                case 4: deletarVeiculo(); break;
                case 0: cout << "Saindo...\n"; break;
                default: cout << "Opção inválida!\n";
            }
        } while (opcao != 0);
        return 0;
    } 
}