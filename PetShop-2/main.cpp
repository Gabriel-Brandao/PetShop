#include "JanelaPrincipal.h"
#include <sstream>

#include "cliente.h"
#include "animal.h"
#include "endereco.h"
#include "servico.h"
#include "data.h"
#include "bd.h"
#include "data.h"

#include <QApplication>
#include <vector>
#include <bd.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]){


/******************************************/
    QApplication a(argc, argv);
    JanelaPrincipal w;
    w.show();
/*****************************************/


    BD *bd = new BD();

    QString sql = "SELECT * FROM Cliente";
    QSqlQuery query;

    //query.prepare(sql);

    if(query.exec(sql)){
        int c = 0;
        while(query.next())
            c++;
        cout << c << " correspondencias encontradas" << endl;
    }
    else
        cout << "Log nao efetuado" << endl;


 Animal *bicho1 = new Ave(false, false, "azul", "araris", 23.3, "azulinha", 'F', 1, 0.3);
 Animal *bicho2 = new Cachorro("PitBull", "marrom", true, false, "Naja", 'F', 5, 15.4);
 Animal *bicho3 = new Gato("preto", true, "odeia colo","plutinho", 'M', 0, 0.5);
 Animal *bicho4 =  new Tartaruga(true, "cativeiro", 23.4, "Donatelo", 'M', 2, 3.450);
 Animal *bicho5 = new Outro("Coelho", "Donnie Darko", 'M', 18, 60);

    vector<Animal*> *listaDeAnimais = new vector<Animal*>;
    listaDeAnimais->push_back(bicho1);
    listaDeAnimais->push_back(bicho2);
    listaDeAnimais->push_back(bicho3);
    listaDeAnimais->push_back(bicho4);
    listaDeAnimais->push_back(bicho5);


    for(unsigned i = 0; i < listaDeAnimais->size(); i++){
        if(dynamic_cast<Ave*>(listaDeAnimais->at(i)) != nullptr)
            cout << listaDeAnimais->at(i)->getNome() << " EH UMA AVE" << endl;
         else
            if(dynamic_cast<Cachorro*>(listaDeAnimais->at(i)) != nullptr)
                cout << listaDeAnimais->at(i)->getNome() << " EH UM CACHORRO" << endl;
             else
                if(dynamic_cast<Gato*>(listaDeAnimais->at(i)) != nullptr)
                    cout << listaDeAnimais->at(i)->getNome() << " EH UM GATO" << endl;
                 else
                    if(dynamic_cast<Tartaruga*>(listaDeAnimais->at(i)) != nullptr)
                        cout << listaDeAnimais->at(i)->getNome() << " EH UMA TARTARUGA" << endl;
                     else
                        if(dynamic_cast<Outro*>(listaDeAnimais->at(i)) != nullptr)
                            cout << listaDeAnimais->at(i)->getNome() << " EH UM(A) " << dynamic_cast<Outro*>(listaDeAnimais->at(i))->getFamilia() << endl;
    }

    Endereco *endereco = new Endereco("79845-12", "Rua qualquer", 160, "", "Bairro qualquer", MS, "Dourados");
    Cliente *cliente = new Cliente(bicho2, "otelo", 12, "054.369.456-79", endereco);
    Data *data = new Data(12, 5, 2021);


    vector<TipoDeServico> *listaDeTipos = new vector<TipoDeServico>();

    listaDeTipos->push_back(static_cast<TipoDeServico>(0));
    listaDeTipos->push_back(static_cast<TipoDeServico>(3));
    listaDeTipos->push_back(static_cast<TipoDeServico>(5));
    listaDeTipos->push_back(static_cast<TipoDeServico>(1));

    Servico *servico = new Servico(cliente, 345.98, true, data, listaDeTipos);

    //servico->getTipoDeServico();

    return a.exec();
}
