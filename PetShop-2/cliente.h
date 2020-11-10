#ifndef CLIENTE_H
#define CLIENTE_H

#include "Animal.h"
#include "Endereco.h"
#include <QString>
#include <bd.h>

class Cliente{
private:
    Animal *pet;
    string nome;
    int idade;
    string cpf;
    Endereco *endereco;
public:
    Cliente(Animal *pet, string nome, int idade, string cpf, Endereco *endereco);
    void setPet(Animal *animal);
    Animal *getPet();
    string getNome();
    int getIdade();
    string getCpf();
    Endereco *getEndereco();

    static Cliente *buscarCliente(string cpf);
    static string inserirCliente(Cliente *cliente);
    static string alterarCliente(Cliente *cliente);
    static string removerCliente(string cpf);
};

#endif // CLIENTE_H
