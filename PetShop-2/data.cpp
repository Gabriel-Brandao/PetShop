#include "data.h"
#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>

#include <iostream>

#include <iostream>
using namespace std;

Data::Data(int dia, int mes, int ano){
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

Data::Data(){
    this->dia = 0;
    this->mes = 0;
    this->ano = 0;
}

string Data::getData(){

    stringstream data;

    if(dia == 0 && mes == 0 && ano == 0)
        return "Nao ha data agendada";

        if (dia < 10)
            data << "0" << dia;
        else
            data << "" << dia;

         if (mes < 10)
            data << "/0" << mes << "/";
         else
            data << "/" << mes << "/";

        data << "" << ano;

    return data.str();
}

int Data::getDia(){
    return this->dia;
}

int Data::getMes(){
    return  this->mes;
}

int Data::getAno(){
    return this->ano;
}

int Data::getSequencial(){
    return this->sequencial;
}

void Data::setSequencial(int sequencial){
    this->sequencial = sequencial;
}

/************************************** S Q L ****************************************************/
int Data::obtemSequencial(Data *data){
    QString sql = "SELECT * FROM Data WHERE Dia = ? AND Mes = ? AND Ano = ?";
    QSqlQuery query;
    int sequencial=-1;

    query.prepare(sql);
    query.addBindValue(data->getDia());
    query.addBindValue(data->getMes());
    query.addBindValue(data->getAno());

    if(query.exec())
        while(query.next())
            sequencial = query.value("SequencialDat").toInt();
    else
       qDebug() << "Não foi possivel verificar a data no banco de dados [Data.cpp/obtemSequencial()]";

    return sequencial;
}

string Data::inserirData(Data *data){
    QString sql = "SELECT * FROM Data WHERE Dia = ? AND Mes = ? AND Ano = ?";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(data->getDia());
    query.addBindValue(data->getMes());
    query.addBindValue(data->getAno());

    if(query.exec()){
        while(query.next()){
            cout << "Esta data ja está cadastrada";
            return "";
        }
    }
     else
        qDebug() << "Não foi possivel verificar a data no banco de dados [Data.cpp/inserirData()]";

    sql = "INSERT INTO Data (Dia, Mes, Ano) VALUES (?, ?, ?)";

    query.prepare(sql);
    query.addBindValue(data->getDia());
    query.addBindValue(data->getMes());
    query.addBindValue(data->getAno());

    if(query.exec()){
        return "";
    }
     else
        qDebug() << "Não foi possivel inserir a data no banco de dados [Data.cpp/inserirData()]";
}
