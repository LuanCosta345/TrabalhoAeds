#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

class Pedido {
private:
    int id;
    float valor;
    int quantidade;
    float valorTotal;
    char descricao[100];
    int idPartida;
    int idDestino;

    void atualizarTotal() {
        valorTotal = valor * quantidade;
    }

public:
    Pedido(int id = 0, const char* desc = "", float valor = 0.0f, int quantidade = 1) {
        this->id = id;
        strncpy(this->descricao, desc, sizeof(this->descricao)-1);
        this->descricao[sizeof(this->descricao)-1] = '\0';
        this->valor = valor;
        this->quantidade = quantidade;
        atualizarTotal();
    }

    int getId() const { return id; }
    float getValor() const { return valor; }
    int getQuantidade() const { return quantidade; }
    float getValorTotal() const { return valorTotal; }
    const char* getDescricao() const { return descricao; }
    int getPartida() const { return idPartida; }
    int getDestino() const { return idDestino; }

    void setValor(float v) {
        valor = v;
        atualizarTotal();
    }

    void setQuantidade(int q) {
        quantidade = q;
        atualizarTotal();
    }

    void setDescricao(const char* desc) {
        strncpy(descricao, desc, sizeof(descricao)-1);
        descricao[sizeof(descricao)-1] = '\0';
    }

    void salvar(std::ofstream &ofs) const {
        ofs.write(reinterpret_cast<const char*>(this), sizeof(Pedido));
    }

    void carregar(std::ifstream &ifs) {
        ifs.read(reinterpret_cast<char*>(this), sizeof(Pedido));
    }

    void setPartida(int p) {
        idPartida = p;
    }

    void setDestino(int d) {
        idDestino = d;
    }
};
