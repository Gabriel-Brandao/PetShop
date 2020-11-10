#ifndef DATA_H
#define DATA_H

#include <string>
#include <QString>
#include "bd.h"

using namespace std;

class Data{
private:
    int sequencial;
    int dia;
    int mes;
    int ano;
public:
    Data(int dia, int mes, int ano);
    Data();
    string getData();
    int getSequencial();
    void setSequencial(int sequencial);
    int getDia();
    int getMes();
    int getAno();
    static string inserirData(Data *data);
    static int obtemSequencial(Data *data);
};

#endif // DATA_H
