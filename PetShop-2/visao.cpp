#include "visao.h"


template <class T>
Visao<T>::Visao(T *chave, string info){
    this->chave = chave;
    this->info = info;
}
template <class T>
T* Visao<T>::getChave(){
    return this->chave;
}

template <class T>
string Visao<T>::getInfo(){
    return this->info;
}

template <class T>
string Visao<T>::toString(){
    return this->info;
}
