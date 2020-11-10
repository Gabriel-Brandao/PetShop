#ifndef VISAO_H
#define VISAO_H

#include <string>

using namespace std;

template <class T>

class Visao {
private:
    T *chave;
    string info;
public:
    Visao(T *chave, string info);
    T* getChave();
    string getInfo();
    string toString();

};

#endif // VISAO_H
