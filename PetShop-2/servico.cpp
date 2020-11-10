#include "servico.h"
#include <iostream>


Servico::Servico(Cliente *cliente, float valor, bool agendarVacina, Data *retorno, vector <TipoDeServico> *tipoDeServico){
    this->cliente = cliente;
    this->valor = valor;
    this->agendarVacina = agendarVacina;
    this->retorno = retorno;

    this->tipoDeServico = new vector <TipoDeServico>;
    while(tipoDeServico->size() != 0){
        this->tipoDeServico->push_back(tipoDeServico->back());
        tipoDeServico->pop_back();
    }
}

Cliente* Servico::getCliente(){
    return this->cliente;
}

float Servico::getValor(){
    return this->valor;
}

bool Servico::isAgendarVacina(){
    return this->agendarVacina;
}

Data* Servico::getRetorno(){
    return this->retorno;
}

vector <TipoDeServico> *Servico::getTipoDeServico(){
    return this->tipoDeServico;
}

string Servico::tipoToString(TipoDeServico tipo){
    switch (tipo) {
        case 0:
            return "ADESTRAMENTO,";
        case 1:
            return "BANHO,";
        case 2:
            return  "CASTRACAO,";
        case 3:
            return "CONSULTA,";
        case 4:
            return  "DOACAO,";
        case 5:
            return "HOSPEDAGEM,";
        case 6:
            return "LOJINHA,";
        case 7:
            return "TOSA,";
    }
}



/********************************** S Q L **********************************/
string Servico::inserirServico(Servico *servico){
    string mensagem_erro = "";
    int dataId;
    Data *data = servico->getRetorno();
    vector <TipoDeServico> *listaDeServico = new vector<TipoDeServico>;

    QString sql = "INSERT INTO Serviço (ClienteId, Valor, Serviços, AgendarVacina, DataId) VALUES (?, ?, ?, ?, ?)";
    QString servicos = "";
    QSqlQuery query;

    mensagem_erro = Data::inserirData(data); //só inseri no banco de dados se nao haver já essa data.
    dataId = Data::obtemSequencial(data);
    if(dataId == -1)
        mensagem_erro = "Não foi possivel extrair o Sequencial de Data [servico.cpp/inserirServiço()]";
    if(mensagem_erro.compare(""))//se nao ta vazia
        return mensagem_erro;

    //se tiver tudo certo vai inserir Servico:
    query.prepare(sql);

    query.addBindValue(QString::fromStdString(servico->getCliente()->getCpf()));
    query.addBindValue(QString::number(servico->getValor()));

    listaDeServico = servico->getTipoDeServico();
    int n = listaDeServico->size();
    for (int i = 0; i < n; i++){
        servicos += QString::fromStdString(tipoToString(listaDeServico->back()));
        listaDeServico->pop_back();
    }

    query.addBindValue(servicos);
    query.addBindValue(servico->isAgendarVacina());
    query.addBindValue(dataId);

    if(query.exec())
        mensagem_erro = "";
    else
        mensagem_erro = "Nao foi possivel cadastrar Servico [servico.cpp/inserirServico()]";

    return mensagem_erro;
}

Servico *Servico::buscarServico(Servico *servico){
    vector <TipoDeServico> *listaDeServico = new vector <TipoDeServico>;
    QString sql = "SELECT S.ClienteId, S.Valor, S.Serviços, S.AgendarVacina, S.DataId FROM Serviço S "
                  "WHERE S.ClienteId = ? AND S.Valor = ? AND  S.Serviços = ? AND S.DataId = ?";
    QString servicos = "";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(QString::fromStdString(servico->cliente->getCpf()));
    query.addBindValue(QString::number(servico->getValor()));

    listaDeServico = servico->getTipoDeServico();
    int n = listaDeServico->size();
    for (int i = 0; i < n; i++){
        cout << "servico.cpp/buscarServico() " << listaDeServico->back() << endl;
        servicos += QString::fromStdString(tipoToString(listaDeServico->back()));
        listaDeServico->pop_back();
    }

    query.addBindValue(servicos);
    query.addBindValue(QString::number(servico->getRetorno()->getSequencial()));

    if(query.exec()){
        while(query.next()){
            return servico;
        }
    }

    return nullptr;
}
