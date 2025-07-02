
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std

// pra entrega eu preciso receber um pedido, e do vetor de locais e de locais

class Entrega{
    private:
    vector<Veiculo>& veiculos;
    vector<Local>& locais;
    Pedido& pedido;
    
    //TODO ajustar o CrudLocais pra fazer sentido

    public:
    Entrega(vector<Veiculo>& v, vector<Local>& l, Pedido& p) : veiculos(v), locais(l), pedido(p) {}

    //metodo pra retornar o veiculo(disponivel mais proximo da origem), local de origem do pedido(ja tenho), 
    // local de destinho(ja tenho), e a distancia entre o local de origem e o destino calculada usando
    // a distância euclidiana entre suas coordenadas (X, Y). apos isso eu coloco o veiculo como ocupado e
    // depois voltar pra disponivel e passar o local atual do veiculo para o local de destino do pedido

    float calcularDistancia(Local local1, Local local2) const{
        return sqrt(pow(local2.getCoordenadaX() - local1.getCoordenadaX(), 2) 
        + pow(local2.getCoordenadaY() - local1.getCoordenadaY(), 2));
    }

    Local acharLocalMaisProximo(Local local) const{
        Local localMaisProximo = locais[0];
        for(auto loc : locais){
            if(loc.getCoordenadaX() == local.getCoordenadaX() && loc.getCoordenadaY() == local.getCoordenadaX()){
                continue;
            }
            else if(calcularDistancia(local, loc) < calcularDistancia(local, localMaisProximo)){
                localMaisProximo = loc;
            }
        }
        return localMaisProximo;
    }

    void realizarEntrega() mutable{
        //primeiro achar o veiculo mais proximo:
        Veiculo& veiculoProximo = veiculos[0];
        for(auto& veic : veiculos){
            if(calcularDistancia(veic.getLocal(), pedido.getLocalOrigem()) < calcularDistancia(veiculoProximo.getLocal(), pedido.getLocalOrigem())){
                veiculoProximo = veic;
            }
        }
        cout << "Veiculo selecionado: " << veic.getModelo << " Placa: " << veic.getPlaca
        << "\n" << "Local de Origem do Pedido: " << pedido.getLocalOrigem().getNome() 
        << "\n" << "Local de Destino do Pedido: " << pedido.getLocalDestino().getNome()
        << "\n" << "Distancia Total: " << calcularDistancia(pedido.getLocalOrigem(), pedido.getLocalDestino()) 
        << endl;
        veiculoProximo.setEstado(OCUPADO);
        cout << "Entrega Concluida" << endl;
        veiculoProximo.setEstado(DISPONIVEL);
        veiculoProximo.setLocal(pedido.getLocalDestino);

    }

}
