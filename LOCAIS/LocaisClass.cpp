#ifndef LOCAISCLASS_H
#define LOCAISCLASS_H
#include <cstring>
#include <cstdio>

#define MAX_NOME 100

class Local {
private:
    int id;
    char nome[MAX_NOME];
    float coordenadaX;
    float coordenadaY;

public:
    // Construtor
    Local() {
        id = 0;
        strcpy(nome, "");
        coordenadaX = 0.0f;
        coordenadaY = 0.0f;
    }
    
    Local(int id, const char* nome, float x, float y) {
        this->id = id;
        strncpy(this->nome, nome, MAX_NOME - 1);
        this->nome[MAX_NOME - 1] = '\0'; // Garantir terminação
        coordenadaX = x;
        coordenadaY = y;
    }
    
    // Getters
    int getId() const { return id; }
    const char* getNome() const { return nome; }
    float getCoordenadaX() const { return coordenadaX; }
    float getCoordenadaY() const { return coordenadaY; }
    
    // Setters
    void setId(int id) { this->id = id; }
    void setNome(const char* nome) { 
        strncpy(this->nome, nome, MAX_NOME - 1);
        this->nome[MAX_NOME - 1] = '\0';
    }
    void setCoordenadaX(float x) { coordenadaX = x; }
    void setCoordenadaY(float y) { coordenadaY = y; }
    
    // Método para exibir informações do local
    void exibir() const {
        printf("ID: %d, Nome: %s, X: %.2f, Y: %.2f\n", id, nome, coordenadaX, coordenadaY);
    }
};

#endif // LOCAISCLASS_H 