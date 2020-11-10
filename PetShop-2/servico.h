#ifndef SERVICO_H
#define SERVICO_H

#include "cliente.h"
#include "data.h"
#include <vector>

using namespace std;

enum TipoDeServico{ADESTRAMENTO, BANHO, CASTRACAO, CONSULTA, DOACAO, HOSPEDAGEM, LOJINHA, TOSA};


class Servico{
private:
    Cliente *cliente;
    float valor;
    bool agendarVacina;
    Data *retorno;
    vector<TipoDeServico> *tipoDeServico;

public:
    Servico(Cliente *cliente, float valor, bool agendarVacina, Data *retorno,  vector <TipoDeServico> *tipoDeServico);
    Cliente *getCliente();
    bool isAgendarVacina();
    float getValor();
    Data *getRetorno();
    vector <TipoDeServico>* getTipoDeServico();
    static string tipoToString(TipoDeServico tipo);
    static Servico *buscarServico(Servico *servico);
    static string inserirServico(Servico *servico);
};

#endif // SERVICO_H
