#ifndef ENDERECO_H
#define ENDERECO_H

#include<string>
#include "bd.h"

using namespace std;

enum Estado {NDA, AC, AL, AP, AM, BA, CE, DF, ES, GO, MA, MT, MS, MG, PA, PB, PR, PE, PI, RJ, RN, RS, RO, RR, SC, SP, SE, TO};

class Endereco{

public:
    Endereco(string cep, string rua, int numero, string complemento, string bairro, Estado estado, string cidade);
    string getCep();
    string getRua();
    int getNumero();
    string getComplemento();
    string getBairro();
    Estado getEstado();
    string getCidade();

    static string inserirEndereco(Endereco *endereco);
    static int obtemSequencial();
    static Endereco *buscaEndereco(int sequencial);
    static Estado getEstadoCliente(int estado);
private:
    string cep;
    string rua;
    int numero;
    string complemento;
    string bairro;
    Estado estado;
    string cidade;
};

#endif // ENDERECO_H
