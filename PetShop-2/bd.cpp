#include "bd.h"
#include <iostream>

using namespace std;

static QSqlDatabase bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");

BD::BD(){

    bancoDeDados.setDatabaseName("D:/Documentos/Monitoria - POO/db_PetShop.db");

    if(!bancoDeDados.open())
        cout << "Banco de Dados nao foi aberto !!" << endl;
    else
        cout << "Banco de Dados Aberto com SUCESSO" << endl;

}

