#include "endereco.h"

Endereco::Endereco(string cep, string rua, int numero, string complemento, string bairro, Estado estado, string cidade){
    this->cep = cep;
    this->rua = rua;
    this->numero = numero;
    this->complemento = complemento;
    this->bairro = bairro;
    this->estado = estado;
    this->cidade = cidade;
}

string Endereco::getCep(){
    return this->cep;
}

string Endereco::getRua(){
    return this->rua;
}

int Endereco::getNumero(){
    return this->numero;
}

string Endereco::getComplemento(){
    return this->complemento;
}

string Endereco::getBairro(){
    return this->bairro;
}

Estado Endereco::getEstado(){
    return this->estado;
}
string Endereco::getCidade(){
    return this->cidade;
}

/*********************************** S Q L ***************************************/

string Endereco::inserirEndereco(Endereco *endereco){
    QString sql = "INSERT INTO Endereço (Cep, Rua, Numero, Complemento, Bairro, Estado, Cidade)VALUES (?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery query;


    query.prepare(sql);

    query.addBindValue(QString::fromStdString(endereco->getCep()));
    query.addBindValue(QString::fromStdString(endereco->getRua()));
    query.addBindValue(endereco->getNumero());
    query.addBindValue(QString::fromStdString(endereco->getComplemento()));
    query.addBindValue(QString::fromStdString(endereco->getBairro()));
    query.addBindValue(endereco->getEstado());
    query.addBindValue(QString::fromStdString(endereco->getCidade()));

    if(query.exec())
        return "";

    return "Não foi possivel inserir Endereco [endereco.cpp/inserirEndereco()]";
}

int Endereco::obtemSequencial(){
    QString sql = "SELECT MAX(SequencialEnd) as Seq FROM Endereço";
    QSqlQuery query;
    int sequencial=-1;

    query.prepare(sql);
    if(query.exec()){
        while(query.next())
            sequencial = query.value("Seq").toInt();
    }
    else
      qDebug()<<"Erro ao extrair Sequencial de Endereço";

    return sequencial;
}

Endereco *Endereco::buscaEndereco(int sequencial){
    QString sql = "SELECT * FROM Endereço E WHERE E.SequencialEnd = ?";
    QSqlQuery query;

    Endereco *endereco = nullptr;
    QString cep = "";
    QString rua = "";
    int numero;
    QString complemento = "";
    QString bairro = "";
    int estado;
    QString cidade = "";

    query.prepare(sql);
    query.addBindValue(sequencial);

    if(query.exec()){
        while(query.next()){
            cep = query.value("Cep").toString();
            rua = query.value("Rua").toString();
            numero = query.value("Numero").toInt();
            complemento = query.value("Complemento").toString();
            bairro = query.value("Bairro").toString();
            estado = query.value("Estado").toInt();
            cidade = query.value("Cidade").toString();
        }
        endereco = new Endereco(cep.toStdString(), rua.toStdString(), numero, complemento.toStdString(), bairro.toStdString(), getEstadoCliente(estado), cidade.toStdString());
    }
     else
        qDebug()<<"Erro ao extrair dados do Endereço";

    return endereco;
}

Estado Endereco::getEstadoCliente(int estado){
    switch (estado) {
        case 0:
            return NDA;
            break;
        case 1:
            return AC;
            break;
        case 2:
            return AL;
            break;
        case 3:
            return AP;
            break;
        case 4:
            return AM;
            break;
        case 5:
            return BA;
            break;
        case 6:
            return CE;
            break;
        case 7:
            return DF;
            break;
        case 8:
            return ES;
            break;
        case 9:
            return GO;
            break;
        case 10:
            return MA;
            break;
        case 11:
            return MT;
            break;
        case 12:
            return MS;
            break;
        case 13:
            return MG;
            break;
        case 14:
            return PA;
            break;
        case 15:
            return PB;
            break;
        case 16:
            return PR;
            break;
        case 17:
            return PE;
            break;
        case 18:
            return PI;
            break;
        case 19:
            return RJ;
            break;
        case 20:
            return RN;
            break;
        case 21:
            return RS;
            break;
        case 22:
            return RO;
            break;
        case 23:
            return RR;
            break;
        case 24:
            return SC;
            break;
        case 25:
            return SP;
            break;
        case 26:
            return SE;
            break;
        case 27:
            return TO;
            break;
    }
}
