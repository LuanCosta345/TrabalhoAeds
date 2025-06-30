#include <cstring>


//enum pra representar estado
enum Estado {
    DISPONIVEL,
    OCUPADO
};

class Veiculo{
    
    private:
    char placa[100]; //È o UID do carro, não pode ser repetida
    char modelo[100];
    Estado estado;
    Local local;

   public:
   //Construtor padrão
   Veiculo(char *p, char *m, Local l) {
        // não é uma pratica tao boa usar strcpy mas relevar isso por agora  
        this->local = l;
        this->estado = DISPONIVEL;
        strcpy(p, this->placa);
        strcpy(m, this->modelo);
   }   

   // Get
    char* getPlaca() const {
        return this->placa;
    }

    char* getModelo() const {
        return this->modelo;
    }

    Estado getEstado() const {
        return this->estado;
    }
    
    Local getLocal() const {
        return this->local;
    }

    // Set
    void setPlaca(const char* novaPlaca) mutable {
        strcpy(this->placa, novaPlaca);
    }

    void setModelo(const char* novoModelo) mutable {
        strcpy(this->modelo, novoModelo);
    }

    void setEstado(Estado novoEstado) {
        this->estado = novoEstado;
    }

    void setLocal(const Local novoLocal) {
        this->local = novoLocal;
    } 

}


