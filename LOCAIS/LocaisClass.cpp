#ifndef LOCAISCLASS_H
#define LOCAISCLASS_H
#include <string>
using namespace std;

class Local {
private:
    string nome;
    float coordenadaX;
    float coordenadaY;
public:
    Local(string nome, float x, float y) : nome(nome), coordenadaX(x), coordenadaY(y) {}
    string getNome() const { return nome; }
    float getCoordenadaX() const { return coordenadaX; }
    float getCoordenadaY() const { return coordenadaY; }
    void setNome(string nome) { this->nome = nome; }
    void setCoordenadaX(float x) { coordenadaX = x; }
    void setCoordenadaY(float y) { coordenadaY = y; }
};

#endif // LOCAISCLASS_H 