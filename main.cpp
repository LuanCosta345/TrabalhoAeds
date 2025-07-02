#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <limits>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// ===================================================================
// DEFINIÇÃO DA CLASSE LOCAL
// ===================================================================
#define MAX_NOME 100

class Local {
public:
    int id;
    char nome[MAX_NOME];
    float coordenadaX;
    float coordenadaY;

    Local();
    Local(int id, const char* nome, float x, float y);
    int getId() const;
    const char* getNome() const;
    float getCoordenadaX() const;
    float getCoordenadaY() const;
    void setId(int id);
    void setNome(const char* nome);
    void setCoordenadaX(float x);
    void setCoordenadaY(float y);
    void exibir() const;
};

Local::Local() {
    id = -1;
    strcpy(nome, "");
    coordenadaX = 0.0f;
    coordenadaY = 0.0f;
}

Local::Local(int id, const char* nome, float x, float y) {
    this->id = id;
    strncpy(this->nome, nome, MAX_NOME - 1);
    this->nome[MAX_NOME - 1] = '\0';
    coordenadaX = x;
    coordenadaY = y;
}

int Local::getId() const { return id; }
const char* Local::getNome() const { return nome; }
float Local::getCoordenadaX() const { return coordenadaX; }
float Local::getCoordenadaY() const { return coordenadaY; }
void Local::setId(int id) { this->id = id; }
void Local::setNome(const char* nome) {
    strncpy(this->nome, nome, MAX_NOME - 1);
    this->nome[MAX_NOME - 1] = '\0';
}
void Local::setCoordenadaX(float x) { coordenadaX = x; }
void Local::setCoordenadaY(float y) { coordenadaY = y; }
void Local::exibir() const {
    std::cout << "ID: " << id << ", Nome: " << nome << ", X: " << coordenadaX << ", Y: " << coordenadaY << std::endl;
}

// ===================================================================
// DEFINIÇÃO DA CLASSE CRUD DE LOCAIS
// ===================================================================
const int MAX_LOCAIS_CRUD = 1000;
const char* ARQUIVO_LOCAIS = "locais.dat";
const char* ARQUIVO_CONTADOR_LOCAIS = "contador_locais.dat";

class CrudLocais {
private:
    int obterProximoId();
    void salvarProximoId(int id);
    bool nomeJaExiste(const char* nome, int idIgnorado = -1);

public:
    Local locais[MAX_LOCAIS_CRUD];
    int quantidade;

    CrudLocais();
    void criarLocal();
    void listarLocais();
    void atualizarLocal();
    void deletarLocal();
    int menu();
    int buscarLocalPorId(int id);
    Local getLocalById(int id);
    void salvarTodosLocais();
    void carregarLocais();
};

CrudLocais::CrudLocais() {
    quantidade = 0;
    carregarLocais();
}

int CrudLocais::obterProximoId() {
    FILE* arquivo = fopen(ARQUIVO_CONTADOR_LOCAIS, "rb");
    int proximoId = 1;
    if (arquivo) {
        fread(&proximoId, sizeof(int), 1, arquivo);
        fclose(arquivo);
    }
    return proximoId;
}

void CrudLocais::salvarProximoId(int id) {
    FILE* arquivo = fopen(ARQUIVO_CONTADOR_LOCAIS, "wb");
    if (arquivo) {
        fwrite(&id, sizeof(int), 1, arquivo);
        fclose(arquivo);
    }
}

void CrudLocais::salvarTodosLocais() {
    FILE* arquivo = fopen(ARQUIVO_LOCAIS, "wb");
    if (arquivo) {
        fwrite(locais, sizeof(Local), quantidade, arquivo);
        fclose(arquivo);
        salvarProximoId(obterProximoId()); // Salva o contador de ID também
        std::cout << "Backup de locais realizado com sucesso." << std::endl;
    } else {
        std::cerr << "Erro ao salvar locais!\n";
    }
}

void CrudLocais::carregarLocais() {
    FILE* arquivo = fopen(ARQUIVO_LOCAIS, "rb");
    quantidade = 0;
    if (arquivo) {
        while (quantidade < MAX_LOCAIS_CRUD && fread(&locais[quantidade], sizeof(Local), 1, arquivo) == 1) {
            quantidade++;
        }
        fclose(arquivo);
    }
}

bool CrudLocais::nomeJaExiste(const char* nome, int idIgnorado) {
    for (int i = 0; i < quantidade; i++) {
        if (locais[i].getId() != idIgnorado && strcmp(locais[i].getNome(), nome) == 0) {
            return true;
        }
    }
    return false;
}

int CrudLocais::buscarLocalPorId(int id) {
    for (int i = 0; i < quantidade; i++) {
        if (locais[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

Local CrudLocais::getLocalById(int id) {
    int index = buscarLocalPorId(id);
    return (index != -1) ? locais[index] : Local();
}

void CrudLocais::criarLocal() {
    char nome[MAX_NOME];
    float x, y;
    std::cout << "Digite o nome do local: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(nome, MAX_NOME);

    if (nomeJaExiste(nome)) {
        std::cout << "Local com este nome ja cadastrado!\n";
        return;
    }
    std::cout << "Digite a coordenada X: ";
    std::cin >> x;
    std::cout << "Digite a coordenada Y: ";
    std::cin >> y;

    int novoId = obterProximoId();
    locais[quantidade++] = Local(novoId, nome, x, y);
    salvarProximoId(novoId + 1);
    std::cout << "Local cadastrado com sucesso! ID: " << novoId << "\n";
}

void CrudLocais::atualizarLocal() {
    int id;
    std::cout << "Digite o ID do local a ser atualizado: ";
    std::cin >> id;
    int indice = buscarLocalPorId(id);

    if (indice != -1) {
        char novoNome[MAX_NOME];
        float x, y;
        std::cout << "Local atual: ";
        locais[indice].exibir();
        
        std::cout << "Digite o novo nome do local: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(novoNome, MAX_NOME);

        if (nomeJaExiste(novoNome, id)) {
            std::cout << "Ja existe outro local com este nome!\n";
            return;
        }
        std::cout << "Digite a nova coordenada X: ";
        std::cin >> x;
        std::cout << "Digite a nova coordenada Y: ";
        std::cin >> y;
        
        locais[indice].setNome(novoNome);
        locais[indice].setCoordenadaX(x);
        locais[indice].setCoordenadaY(y);
        
        std::cout << "Local atualizado com sucesso!\n";
    } else {
        std::cout << "Local com ID " << id << " nao encontrado!\n";
    }
}

void CrudLocais::deletarLocal() {
    int id;
    std::cout << "Digite o ID do local a ser deletado: ";
    std::cin >> id;
    int indice = buscarLocalPorId(id);

    if (indice != -1) {
        for (int i = indice; i < quantidade - 1; i++) {
            locais[i] = locais[i + 1];
        }
        quantidade--;
        std::cout << "Local deletado com sucesso!\n";
    } else {
        std::cout << "Local com ID " << id << " nao encontrado!\n";
    }
}

void CrudLocais::listarLocais() {
    if (quantidade == 0) {
        std::cout << "Nenhum local cadastrado.\n";
        return;
    }
    std::cout << "\n=== Lista de Locais ===\n";
    for (int i = 0; i < quantidade; i++) {
        locais[i].exibir();
    }
}

int CrudLocais::menu() {
    int opcao;
    do {
        std::cout << "\n--- Menu Locais ---\n";
        std::cout << "1. Cadastrar Local\n";
        std::cout << "2. Listar Locais\n";
        std::cout << "3. Atualizar Local\n";
        std::cout << "4. Deletar Local\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: criarLocal(); break;
            case 2: listarLocais(); break;
            case 3: atualizarLocal(); break;
            case 4: deletarLocal(); break;
            case 0: break;
            default: std::cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);
    return 0;
}

// ===================================================================
// DEFINIÇÃO DA CLASSE VEICULO
// ===================================================================
enum Estado { DISPONIVEL, OCUPADO };

class Veiculo {
private:
    char placa[50];
    char modelo[50];
    Estado status;
    Local local;

public:
    Veiculo();
    Veiculo(const char *p, const char *m, Local l);
    const char* getPlaca() const;
    const char* getModelo() const;
    Estado getStatus() const;
    Local getLocal() const;
    void setPlaca(const char *p);
    void setModelo(const char *m);
    void setStatus(Estado s);
    void setLocal(Local l);
};

Veiculo::Veiculo() {
    strcpy(this->placa, "");
    strcpy(this->modelo, "");
    this->status = DISPONIVEL;
}

Veiculo::Veiculo(const char *p, const char *m, Local l) {
    strncpy(this->placa, p, 49);
    this->placa[49] = '\0';
    strncpy(this->modelo, m, 49);
    this->modelo[49] = '\0';
    this->status = DISPONIVEL;
    this->local = l;
}
const char* Veiculo::getPlaca() const { return this->placa; }
const char* Veiculo::getModelo() const { return this->modelo; }
Estado Veiculo::getStatus() const { return this->status; }
Local Veiculo::getLocal() const { return this->local; }
void Veiculo::setPlaca(const char *p) { strncpy(this->placa, p, 49); }
void Veiculo::setModelo(const char *m) { strncpy(this->modelo, m, 49); }
void Veiculo::setStatus(Estado s) { this->status = s; }
void Veiculo::setLocal(Local l) { this->local = l; }

// ===================================================================
// DEFINIÇÃO DA CLASSE CRUD DE VEICULOS
// ===================================================================
class CrudVeiculos {
private:
    CrudLocais& crudLocaisRef;
    const char* estadoPraString(Estado estado) const;

public:
    std::vector<Veiculo> veiculos;
    CrudVeiculos(CrudLocais& locaisRef);
    void criarVeiculo();
    void listarVeiculos();
    void atualizarVeiculo();
    void deletarVeiculo();
    int menu();
    void salvarParaArquivo();
    void carregarDoArquivo();
};

CrudVeiculos::CrudVeiculos(CrudLocais& locaisRef) : crudLocaisRef(locaisRef) {
    carregarDoArquivo();
}

void CrudVeiculos::salvarParaArquivo() {
    std::ofstream ofs("veiculos.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) {
        std::cerr << "Erro ao abrir veiculos.dat para escrita!" << std::endl;
        return;
    }
    for (const auto& veiculo : veiculos) {
        ofs.write(reinterpret_cast<const char*>(&veiculo), sizeof(Veiculo));
    }
    std::cout << "Backup de veiculos realizado com sucesso." << std::endl;
}

void CrudVeiculos::carregarDoArquivo() {
    std::ifstream ifs("veiculos.dat", std::ios::binary);
    if (!ifs) return;
    veiculos.clear();
    Veiculo veiculo;
    while (ifs.read(reinterpret_cast<char*>(&veiculo), sizeof(Veiculo))) {
        veiculos.push_back(veiculo);
    }
}

void CrudVeiculos::criarVeiculo() {
    char placa[50], modelo[50];
    std::cout << "Digite a placa do veiculo: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(placa, 50);
    std::cout << "Digite o modelo do veiculo: ";
    std::cin.getline(modelo, 50);
    int idLocal;
    std::cout << "Digite o ID do local onde o veiculo esta: ";
    std::cin >> idLocal;
    Local local = crudLocaisRef.getLocalById(idLocal);
    if(local.getId() == -1){
        std::cout << "Local nao encontrado! Cadastre o local primeiro.\n";
        return;
    }
    veiculos.push_back(Veiculo(placa, modelo, local));
    std::cout << "Veiculo cadastrado com sucesso!\n";
}

void CrudVeiculos::listarVeiculos() {
    if (veiculos.empty()) {
        std::cout << "Nenhum veiculo cadastrado.\n";
        return;
    }
    std::cout << "\n--- Lista de Veiculos ---\n";
    for (const auto& v : veiculos) {
        std::cout << "Placa: " << v.getPlaca()
                  << ", Modelo: " << v.getModelo()
                  << ", Status: " << estadoPraString(v.getStatus())
                  << ", Local: " << v.getLocal().getNome() << " (ID: " << v.getLocal().getId() << ")"
                  << std::endl;
    }
}

void CrudVeiculos::atualizarVeiculo() {
    char placa[50];
    std::cout << "Digite a placa do veiculo a ser atualizado: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(placa, 50);

    for (auto& veiculo : veiculos) {
        if (strcmp(veiculo.getPlaca(), placa) == 0) {
            char novoModelo[50];
            int novoIdLocal;
            std::cout << "Digite o novo modelo: ";
            std::cin.getline(novoModelo, 50);
            std::cout << "Digite o ID do novo local: ";
            std::cin >> novoIdLocal;
            Local novoLocal = crudLocaisRef.getLocalById(novoIdLocal);
            if (novoLocal.getId() == -1) {
                std::cout << "Local nao encontrado!\n";
                return;
            }
            veiculo.setModelo(novoModelo);
            veiculo.setLocal(novoLocal);
            std::cout << "Veiculo atualizado com sucesso!\n";
            return;
        }
    }
    std::cout << "Veiculo nao encontrado!\n";
}

void CrudVeiculos::deletarVeiculo() {
    char placa[50];
    std::cout << "Digite a placa do veiculo a ser deletado: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(placa, 50);

    for (auto it = veiculos.begin(); it != veiculos.end(); ++it) {
        if (strcmp(it->getPlaca(), placa) == 0) {
            veiculos.erase(it);
            std::cout << "Veiculo deletado com sucesso!\n";
            return;
        }
    }
    std::cout << "Veiculo nao encontrado!\n";
}

const char* CrudVeiculos::estadoPraString(Estado estado) const {
    return (estado == DISPONIVEL) ? "Disponivel" : "Ocupado";
}

int CrudVeiculos::menu() {
    int opcao;
    do {
        std::cout << "\n--- Menu Veiculos ---\n";
        std::cout << "1. Cadastrar Veiculo\n";
        std::cout << "2. Listar Veiculos\n";
        std::cout << "3. Atualizar Veiculo\n";
        std::cout << "4. Deletar Veiculo\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1: criarVeiculo(); break;
            case 2: listarVeiculos(); break;
            case 3: atualizarVeiculo(); break;
            case 4: deletarVeiculo(); break;
            case 0: break;
            default: std::cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);
    return 0;
}


// ===================================================================
// DEFINIÇÃO DA CLASSE PEDIDO
// ===================================================================
class Pedido {
private:
    int id;
    float peso;
    Local origem;
    Local destino;

public:
    Pedido();
    Pedido(int id, float peso, Local origem, Local destino);
    int getId() const;
    float getPeso() const;
    Local getOrigem() const;
    Local getDestino() const;
    void setId(int id);
    void setPeso(float peso);
    void setOrigem(Local origem);
    void setDestino(Local destino);
};

Pedido::Pedido() { id = -1; peso = 0.0f; }

Pedido::Pedido(int id, float peso, Local origem, Local destino) {
    this->id = id;
    this->peso = peso;
    this->origem = origem;
    this->destino = destino;
}
int Pedido::getId() const { return id; }
float Pedido::getPeso() const { return peso; }
Local Pedido::getOrigem() const { return origem; }
Local Pedido::getDestino() const { return destino; }
void Pedido::setId(int id) { this->id = id; }
void Pedido::setPeso(float peso) { this->peso = peso; }
void Pedido::setOrigem(Local origem) { this->origem = origem; }
void Pedido::setDestino(Local destino) { this->destino = destino; }

// ===================================================================
// DEFINIÇÃO DA CLASSE CRUD DE PEDIDOS
// ===================================================================
class CrudPedidos {
private:
    int proximoId;
    CrudLocais& crudLocaisRef;
    void carregarProximoId();
    void salvarProximoId();

public:
    std::vector<Pedido> pedidos;
    CrudPedidos(CrudLocais& locaisRef);
    void criarPedido();
    void listarPedidos();
    void atualizarPedido();
    void deletarPedido();
    int menu();
    void salvarParaArquivo();
    void carregarDoArquivo();
};

CrudPedidos::CrudPedidos(CrudLocais& locaisRef) : crudLocaisRef(locaisRef) {
    carregarDoArquivo();
}

void CrudPedidos::salvarParaArquivo() {
    std::ofstream ofs("pedidos.dat", std::ios::binary | std::ios::trunc);
    if (!ofs) {
        std::cerr << "Erro ao abrir pedidos.dat para escrita!" << std::endl;
        return;
    }
    for (const auto &p : pedidos) {
        ofs.write(reinterpret_cast<const char*>(&p), sizeof(Pedido));
    }
    salvarProximoId();
    std::cout << "Backup de pedidos realizado com sucesso." << std::endl;
}

void CrudPedidos::carregarDoArquivo() {
    std::ifstream ifs("pedidos.dat", std::ios::binary);
    if (!ifs) return;
    pedidos.clear();
    Pedido p;
    while (ifs.read(reinterpret_cast<char*>(&p), sizeof(Pedido))) {
        pedidos.push_back(p);
    }
    carregarProximoId();
}

void CrudPedidos::carregarProximoId() {
    std::ifstream ifs("pedidos_id.dat", std::ios::binary);
    proximoId = 1;
    if (ifs) {
        ifs.read(reinterpret_cast<char*>(&proximoId), sizeof(proximoId));
    }
}

void CrudPedidos::salvarProximoId() {
    std::ofstream ofs("pedidos_id.dat", std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(&proximoId), sizeof(proximoId));
}

void CrudPedidos::criarPedido() {
    float peso;
    int idOrigem, idDestino;
    std::cout << "Digite o peso do item (em kg): ";
    std::cin >> peso;
    std::cout << "Digite o ID do local de origem: ";
    std::cin >> idOrigem;
    std::cout << "Digite o ID do local de destino: ";
    std::cin >> idDestino;
    Local origem = crudLocaisRef.getLocalById(idOrigem);
    Local destino = crudLocaisRef.getLocalById(idDestino);
    if (origem.getId() == -1 || destino.getId() == -1) {
        std::cout << "Local de origem ou destino nao encontrado. Cadastre-os primeiro.\n";
        return;
    }
    pedidos.push_back(Pedido(proximoId++, peso, origem, destino));
    std::cout << "Pedido criado com sucesso! ID: " << proximoId - 1 << "\n";
}

void CrudPedidos::listarPedidos() {
    if (pedidos.empty()) {
        std::cout << "Nenhum pedido cadastrado.\n";
        return;
    }
    std::cout << "\n--- Lista de Pedidos ---\n";
    for (const auto &p : pedidos) {
        std::cout << "ID: " << p.getId()
                  << ", Peso: " << p.getPeso() << " kg"
                  << ", Origem: " << p.getOrigem().getNome()
                  << ", Destino: " << p.getDestino().getNome() << "\n";
    }
}

void CrudPedidos::atualizarPedido() {
    int id;
    std::cout << "Digite o ID do pedido a ser atualizado: ";
    std::cin >> id;

    for (auto& pedido : pedidos) {
        if (pedido.getId() == id) {
            int novaOrigemId, novoDestinoId;
            float novoPeso;
            
            std::cout << "Digite o novo peso (kg): ";
            std::cin >> novoPeso;
            std::cout << "Digite o ID da nova origem: ";
            std::cin >> novaOrigemId;
            std::cout << "Digite o ID do novo destino: ";
            std::cin >> novoDestinoId;

            Local novaOrigem = crudLocaisRef.getLocalById(novaOrigemId);
            Local novoDestino = crudLocaisRef.getLocalById(novoDestinoId);

            if (novaOrigem.getId() == -1 || novoDestino.getId() == -1) {
                std::cout << "Origem ou destino nao encontrado!\n";
                return;
            }
            pedido.setPeso(novoPeso);
            pedido.setOrigem(novaOrigem);
            pedido.setDestino(novoDestino);
            std::cout << "Pedido atualizado com sucesso!\n";
            return;
        }
    }
    std::cout << "Pedido com ID " << id << " nao encontrado!\n";
}

void CrudPedidos::deletarPedido() {
    int id;
    std::cout << "Digite o ID do pedido a ser deletado: ";
    std::cin >> id;

    for (auto it = pedidos.begin(); it != pedidos.end(); ++it) {
        if (it->getId() == id) {
            pedidos.erase(it);
            std::cout << "Pedido deletado com sucesso!\n";
            return;
        }
    }
    std::cout << "Pedido com ID " << id << " nao encontrado!\n";
}


int CrudPedidos::menu() {
    int opcao;
    do {
        std::cout << "\n--- Menu Pedidos ---\n";
        std::cout << "1. Cadastrar Pedido\n";
        std::cout << "2. Listar Pedidos\n";
        std::cout << "3. Atualizar Pedido\n";
        std::cout << "4. Deletar Pedido\n";
        std::cout << "0. Voltar ao Menu Principal\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        switch (opcao) {
            case 1: criarPedido(); break;
            case 2: listarPedidos(); break;
            case 3: atualizarPedido(); break;
            case 4: deletarPedido(); break;
            case 0: break;
            default: std::cout << "Opcao invalida!\n";
        }
    } while (opcao != 0);
    return 0;
}

// ===================================================================
// DEFINIÇÃO DA CLASSE ENTREGA
// ===================================================================
class Entrega {
private:
    std::vector<Veiculo>& veiculos;
    std::vector<Pedido>& pedidos;
    float calcularDistancia(const Local& local1, const Local& local2) const;

public:
    Entrega(std::vector<Veiculo>& v, std::vector<Pedido>& p);
    void realizarProximaEntrega();
};

Entrega::Entrega(std::vector<Veiculo>& v, std::vector<Pedido>& p) : veiculos(v), pedidos(p) {}

float Entrega::calcularDistancia(const Local& local1, const Local& local2) const {
    return sqrt(pow(local2.getCoordenadaX() - local1.getCoordenadaX(), 2)
        + pow(local2.getCoordenadaY() - local1.getCoordenadaY(), 2));
}

void Entrega::realizarProximaEntrega() {
    if (pedidos.empty()) {
        std::cout << "\nNao ha pedidos na fila para realizar entrega." << std::endl;
        return;
    }
    if (veiculos.empty()) {
        std::cout << "\nNao ha veiculos cadastrados para realizar a entrega." << std::endl;
        return;
    }

    Pedido& pedidoAtual = pedidos.front();
    Veiculo* veiculoMaisProximo = nullptr;
    float menorDistancia = std::numeric_limits<float>::max();

    for (auto& veic : veiculos) {
        if (veic.getStatus() == DISPONIVEL) {
            float distancia = calcularDistancia(veic.getLocal(), pedidoAtual.getOrigem());
            if (distancia < menorDistancia) {
                menorDistancia = distancia;
                veiculoMaisProximo = &veic;
            }
        }
    }

    if (veiculoMaisProximo == nullptr) {
        std::cout << "\nNenhum veiculo disponivel no momento." << std::endl;
        return;
    }

    std::cout << "\n--- Iniciando Entrega do Pedido ID: " << pedidoAtual.getId() << " ---" << std::endl;
    std::cout << "Veiculo selecionado: " << veiculoMaisProximo->getModelo() << " (Placa: " << veiculoMaisProximo->getPlaca() << ")" << std::endl;
    std::cout << "Status do Veiculo: OCUPADO. Entrega em andamento..." << std::endl;
    veiculoMaisProximo->setStatus(OCUPADO);

    std::cout << "Entrega Concluida!" << std::endl;
    veiculoMaisProximo->setStatus(DISPONIVEL);
    veiculoMaisProximo->setLocal(pedidoAtual.getDestino());
    
    std::cout << "Status do Veiculo: DISPONIVEL. Nova localizacao: " << veiculoMaisProximo->getLocal().getNome() << std::endl;
    
    pedidos.erase(pedidos.begin());
    std::cout << "Pedido ID: " << pedidoAtual.getId() << " finalizado e removido da fila." << std::endl;
}

// ===================================================================
// FUNÇÕES AUXILIARES DO MENU PRINCIPAL
// ===================================================================
void backupDados(CrudLocais& crudLocais, CrudVeiculos& crudVeiculos, CrudPedidos& crudPedidos) {
    std::cout << "\nIniciando processo de backup..." << std::endl;
    crudLocais.salvarTodosLocais();
    crudVeiculos.salvarParaArquivo();
    crudPedidos.salvarParaArquivo();
    std::cout << "Processo de backup finalizado." << std::endl;
}

void restaurarDados(CrudLocais& crudLocais, CrudVeiculos& crudVeiculos, CrudPedidos& crudPedidos) {
    std::cout << "\nIniciando processo de restauracao..." << std::endl;
    crudLocais.carregarLocais();
    crudVeiculos.carregarDoArquivo();
    crudPedidos.carregarDoArquivo();
    std::cout << "Dados restaurados dos arquivos com sucesso." << std::endl;
}

// ===================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// ===================================================================
int main() {
    int opcao;
    CrudLocais crudLocais;
    CrudVeiculos crudVeiculos(crudLocais);
    CrudPedidos crudPedidos(crudLocais);

    do {
        std::cout << "\n--- Sistema de Logistica ---\n";
        std::cout << "1. Gerenciar Locais\n";
        std::cout << "2. Gerenciar Veiculos\n";
        std::cout << "3. Gerenciar Pedidos\n";
        std::cout << "4. Realizar Proxima Entrega\n";
        std::cout << "5. Backup de dados\n";
        std::cout << "6. Restaurar dados\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1: crudLocais.menu(); break;
            case 2: crudVeiculos.menu(); break;
            case 3: crudPedidos.menu(); break;
            case 4: {
                Entrega entrega(crudVeiculos.veiculos, crudPedidos.pedidos);
                entrega.realizarProximaEntrega();
                break;
            }
            case 5:
                backupDados(crudLocais, crudVeiculos, crudPedidos);
                break;
            case 6:
                restaurarDados(crudLocais, crudVeiculos, crudPedidos);
                break;
            case 0:
                std::cout << "Saindo do sistema...\n";
                break;
            default:
                std::cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
    } while (opcao != 0);

    return 0;
}