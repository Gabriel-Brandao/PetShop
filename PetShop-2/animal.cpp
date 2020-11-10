#include "animal.h"
#include "bd.h"
#include <sstream>

//#include <QString>
#include <iostream>
using namespace std;

Animal::Animal(string nome, char sexo, int idade, float peso){
    this->nome = nome;
    this->sexo = sexo;
    this->idade = idade;
    this->peso = peso;
}

string Animal::getNome(){
    return nome;
}

char Animal::getSexo(){
    return this->sexo;
}

int Animal::getIdade(){
    return this->idade;
}

float Animal::getPeso(){
    return this->peso;
}

int Animal::getSequencial(){
    return this->Sequencial;
}

void Animal::setSequencial(int sequencial){
    this->Sequencial = sequencial;
}

Cachorro::Cachorro(string raca, string pelagem, bool adestrado, bool castrado, string nome, char sexo, int idade, float peso):Animal(nome, sexo, idade, peso){
    this->raca = raca;
    this->pelagem = pelagem;
    this->adestrado = adestrado;
    this->castrado = castrado;
}

string Cachorro::getNome(){
    return nome;
}

string Cachorro::getRaca(){
    return this->raca;
}

string Cachorro::getPelagem(){
    return this->pelagem;
}

bool Cachorro::isAdestrado(){
    return this->adestrado;
}

bool Cachorro::isCastrado(){
    return this->castrado;
}

Gato::Gato(string pelagem, bool castrado, string observacao, string nome, char sexo, int idade, float peso):Animal(nome, sexo, idade, peso){
    this->pelagem = pelagem;
    this->castrado = castrado;
    this->observacao = observacao;
}

string Gato::getNome(){
    return nome;
}

string Gato::getPelagem(){
    return this->pelagem;
}

bool Gato::isCastrado(){
    return this->castrado;
}

string Gato::getObservacao(){
    return this->observacao;
}

Ave::Ave(bool dieta, bool gaiola, string penugem, string especie, float invergadura, string nome, char sexo, int idade, float peso):Animal(nome, sexo, idade, peso){
    this->dieta = dieta;
    this->gaiola = gaiola;
    this->penugem = penugem;
    this->especie = especie;
    this->invergadura = invergadura;
}

string Ave::getNome(){
    return nome;
}

bool Ave::isDieta(){
    return this->dieta;
}

bool Ave::isGaiola(){
    return this->gaiola;
}

string Ave::getPenugem(){
    return this->penugem;
}

string Ave::getEspecie(){
    return this->especie;
}

float Ave::getInvergadura(){
    return this->invergadura;
}

Tartaruga::Tartaruga(bool dieta, string tipoDeAmbiente, float tamanhoDaCarapaca, string nome, char sexo, int idade, float peso) : Animal(nome, sexo, idade, peso){
    this->dieta = dieta;
    this->tipoDeAmbiente = tipoDeAmbiente;
    this->tamanhoDaCarapaca = tamanhoDaCarapaca;
}

string Tartaruga::getNome(){
    return nome;
}

bool Tartaruga::isDieta(){
    return this->dieta;
}

string Tartaruga::getTipoDeAmbiente(){
    return tipoDeAmbiente;
}

float Tartaruga::getTamanhoDaCarapaca(){
    return this->tamanhoDaCarapaca;
}

Outro::Outro(string familia, string nome, char sexo, int idade, float peso):Animal(nome, sexo, idade, peso){
    this->familia = familia;
}

string Outro::getNome(){
    return nome;
}

string Outro::getFamilia(){
    return this->familia;
}


/********************* S Q L *************************/

string Animal::alterarAnimal(Animal *animal){//ALTERAR
    string mensagem_erro = "";
    QString sqlQualAnimal = "SELECT AveId Aid, CachorroId Cid, GatoId Gid, TartarugaId Tid, OutroAnimalId Oid "
                            "FROM Animal Ani WHERE Ani.SequencialAni = ?";

    QSqlQuery queryQualAnimal;

    QString aveId = nullptr;
    QString cachorroId = nullptr;
    QString gatoId = nullptr;
    QString tartarugaId = nullptr;
    QString outroAnimalId = nullptr;


    queryQualAnimal.prepare(sqlQualAnimal);
    queryQualAnimal.addBindValue(animal->getSequencial());

    if(queryQualAnimal.exec()){
        while(queryQualAnimal.next()){
            aveId = queryQualAnimal.value("Aid").toString();
            cachorroId = queryQualAnimal.value("Cid").toString();
            gatoId = queryQualAnimal.value("Gid").toString();
            tartarugaId = queryQualAnimal.value("Tid").toString();
            outroAnimalId = queryQualAnimal.value("Oid").toString();
        }
    }
     else
      qDebug()<<"Erro ao buscar Sequencial em Animal [animal.cpp/alterar()]";


    if(aveId != nullptr){
        Ave *ave = dynamic_cast<Ave*>(animal);
        mensagem_erro = Ave::alterarAve(ave, aveId.toInt());
    }
     else
       if(cachorroId != nullptr){
            Cachorro *cachorro = dynamic_cast<Cachorro*>(animal);
            mensagem_erro = Cachorro::alterarCachorro(cachorro, cachorroId.toInt());
       }
        else
           if(gatoId != nullptr){
               Gato *gato = dynamic_cast<Gato*>(animal);
               mensagem_erro = Gato::alterarGato(gato, gatoId.toInt());
           }
            else
               if(tartarugaId != nullptr){
                   Tartaruga *tartaruga = dynamic_cast<Tartaruga*>(animal);
                   mensagem_erro = Tartaruga::alterarTartaruga(tartaruga, tartarugaId.toInt());
               }
                else
                   if(outroAnimalId != nullptr){

                   }

    if(mensagem_erro.compare(""))
        return mensagem_erro;

    return "";
}

string Animal::inserirAnimal(Animal *animal){//INSERIR
    cout << animal->getSexo()  << " [animal/inserirAnimal()]"<< endl;
    string mensagem_erro = ""; //deve continuar ""
    QString sqlPKanimal = ""; // deve conter o SQL para pegar a chave primaria maxima de algum animal
    QSqlQuery queryPK_x;
    int pk_x = -1;
    QString sqlAnimal = "";  //deve conter o SQL para inserir no foreign key correto
    QSqlQuery queryAnimal;

    Ave *ave = dynamic_cast<Ave*>(animal);
    if(ave != nullptr){
       mensagem_erro = Ave::inserirAve(ave);
       sqlPKanimal = "SELECT MAX (SequencialAve) as MaxSeq FROM Ave";
       sqlAnimal = "INSERT INTO Animal (Nome, Sexo, Idade, Peso, AveId) VALUES (?, ?, ?, ?, ?)";
     } else{
        Cachorro *cachorro = dynamic_cast<Cachorro*>(animal);
        if(cachorro != nullptr){
            mensagem_erro = Cachorro::inserirCachorro(cachorro);
            sqlPKanimal = "SELECT MAX (SequencialCao) as MaxSeq FROM Cachorro";
            sqlAnimal = "INSERT INTO Animal (Nome, Sexo, Idade, Peso, CachorroId) VALUES (?, ?, ?, ?, ?)";
         } else{
            Gato *gato = dynamic_cast<Gato*>(animal);
            if(gato != nullptr){
                mensagem_erro = Gato::inserirGato(gato);
                sqlPKanimal = "SELECT MAX (SequencialGat) as MaxSeq FROM Gato";
                sqlAnimal = "INSERT INTO Animal (Nome, Sexo, Idade, Peso, GatoId) VALUES (?, ?, ?, ?, ?)";
             } else{
                Tartaruga *tartaruga = dynamic_cast<Tartaruga*>(animal);
                if(tartaruga != nullptr){
                    mensagem_erro = Tartaruga::inserirTartaruga(tartaruga);
                    sqlPKanimal = "SELECT MAX (SequencialTar) as MaxSeq FROM Tartaruga";
                    sqlAnimal = "INSERT INTO Animal (Nome, Sexo, Idade, Peso, TartarugaId) VALUES (?, ?, ?, ?, ?)";
                 } else{
                    Outro *outro = dynamic_cast<Outro*>(animal);
                    if(outro != nullptr){
                        mensagem_erro = Outro::inserirOutro(outro);
                        sqlPKanimal = "SELECT MAX (SequencialOA) as MaxSeq FROM OutroAnimal";
                        sqlAnimal = "INSERT INTO Animal (Nome, Sexo, Idade, Peso, OutroAnimalId) VALUES (?, ?, ?, ?, ?)";
                    }
                 }
             }
         }
     }

    if(mensagem_erro.compare(""))
        return mensagem_erro;

    //Extrair primeira chave do ultimo animal cadastrado
    queryPK_x.prepare(sqlPKanimal);
    if(queryPK_x.exec()){
        while(queryPK_x.next())
            pk_x = queryPK_x.value("MaxSeq").toInt();
    }
     else{
        return "Nao foi possivel extrair a chave primaria desse animal";
    }

    //Inseri Animal no banco de dados
    queryAnimal.prepare(sqlAnimal);
    queryAnimal.addBindValue(QString::fromStdString(animal->getNome()));
    queryAnimal.addBindValue(animal->getSexo());
    queryAnimal.addBindValue(animal->getIdade());
    queryAnimal.addBindValue(animal->peso);
    queryAnimal.addBindValue(pk_x);

    cout << mensagem_erro << endl;

    if(queryAnimal.exec())
        return mensagem_erro;
     else
        return "Nao foi possivel inserir ANIMAL no Banco de Dados";
}

string Animal::removerAnimal(int id){//REMOVER
    string mensagem_erro = "";
    QString sqlQualAnimal = "SELECT AveId Aid, CachorroId Cid, GatoId Gid, TartarugaId Tid, OutroAnimalId Oid "
                            "FROM Animal Ani WHERE Ani.SequencialAni = ?";

    QSqlQuery queryQualAnimal;

    QString aveId = nullptr;
    QString cachorroId = nullptr;
    QString gatoId = nullptr;
    QString tartarugaId = nullptr;
    QString outroAnimalId = nullptr;

    queryQualAnimal.prepare(sqlQualAnimal);
    queryQualAnimal.addBindValue(id);

    if(queryQualAnimal.exec()){
        while(queryQualAnimal.next()){
            aveId = queryQualAnimal.value("Aid").toString();
            cachorroId = queryQualAnimal.value("Cid").toString();
            gatoId = queryQualAnimal.value("Gid").toString();
            tartarugaId = queryQualAnimal.value("Tid").toString();
            outroAnimalId = queryQualAnimal.value("Oid").toString();
        }
    }
     else
      qDebug()<<"Erro ao buscar Sequencial em Animal [animal.cpp/remover()]";

    sqlQualAnimal = "";

    if(aveId != nullptr){
        sqlQualAnimal = "DELETE FROM Ave WHERE SequencialAve = ?";
        queryQualAnimal.prepare(sqlQualAnimal);
        queryQualAnimal.addBindValue(aveId);
    }
     else
       if(cachorroId != nullptr){
            sqlQualAnimal = "DELETE FROM Cachorro WHERE SequencialCao = ?";
            queryQualAnimal.prepare(sqlQualAnimal);
            queryQualAnimal.addBindValue(cachorroId);
       }
        else
           if(gatoId != nullptr){
                sqlQualAnimal = "DELETE FROM Gato WHERE SequencialGat = ?";
                queryQualAnimal.prepare(sqlQualAnimal);
                queryQualAnimal.addBindValue(gatoId);
           }
            else
               if(tartarugaId != nullptr){
                    sqlQualAnimal = "DELETE FROM Tartaruga WHERE SequencialTar = ?";
                    queryQualAnimal.prepare(sqlQualAnimal);
                    queryQualAnimal.addBindValue(tartarugaId);
               }
                else
                   if(outroAnimalId != nullptr){
                        sqlQualAnimal = "DELETE FROM OutroAnimal WHERE SequencialOA = ?";
                        queryQualAnimal.prepare(sqlQualAnimal);
                        queryQualAnimal.addBindValue(outroAnimalId);
                   }

    if(!sqlQualAnimal.compare(""))
        return "nao foi possivel remover o animal";

    //remoção é feita no modo ON DELETE CASCATE (de Filho para Pai)
    if(queryQualAnimal.exec())
        return "";
    return "nao foi possivel remover o animal";
}

string Ave::inserirAve(Ave *ave){
    QString sql = "INSERT INTO Ave (Dieta, Gaiola, Penugem, Espécie, Invergadura) VALUES (?, ?, ?, ?, ?)";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(ave->isDieta());
    query.addBindValue(ave->isGaiola());
    query.addBindValue(QString::fromStdString(ave->getPenugem()));
    query.addBindValue(QString::fromStdString(ave->getEspecie()));
    query.addBindValue(ave->getInvergadura());

    if(query.exec())
        return "";
     else
        return "Nao foi possivel inserir AVE no Banco de Dados";
}

string Cachorro::inserirCachorro(Cachorro *cachorro){

    QString sql = "INSERT INTO Cachorro (Raça, Pelagem, Adestrado, Castrado) VALUES (?, ?, ?, ?)";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(QString::fromStdString(cachorro->getRaca()));
    query.addBindValue(QString::fromStdString(cachorro->getPelagem()));
    query.addBindValue(cachorro->isAdestrado());
    query.addBindValue(cachorro->isCastrado());

    if(query.exec())
        return "";
     else
        return "Nao foi possivel inserir CACHORRO no Banco de Dados";
}

string Gato::inserirGato(Gato *gato){
    QString sql = "INSERT INTO Gato (Pelagem, Castrado, Observação) VALUES (?, ?, ?)";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(QString::fromStdString(gato->getPelagem()));
    query.addBindValue(gato->isCastrado());
    query.addBindValue(QString::fromStdString(gato->getObservacao()));

    if(query.exec())
        return "";
     else
        return "Nao foi possivel inserir GATO no Banco de Dados";
}

string Tartaruga::inserirTartaruga(Tartaruga *tartauga){
    QString sql = "INSERT INTO Tartaruga (Dieta, TipoDeAmbiente, TamanhoDaCarapaça) VALUES (?, ?, ?)";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(tartauga->isDieta());
    query.addBindValue(QString::fromStdString(tartauga->getTipoDeAmbiente()));
    query.addBindValue(tartauga->getTamanhoDaCarapaca());

    if(query.exec())
        return "";
     else
        return "Nao foi possivel inserir TARTARUGA no Banco de Dados";
}

string Outro::inserirOutro(Outro *outro){
    QString sql = "INSERT INTO OutroAnimal (FamiliaAnimal) VALUES (?)";

    QSqlQuery query;
    query.prepare(sql);

    query.addBindValue(QString::fromStdString(outro->getFamilia()));

    if(query.exec())
        return "";
     else
        return "Nao foi possivel inserir OUTRO ANIMAL no Banco de Dados";
}

string Ave::alterarAve(Ave *ave, int id){
    QString sql = "UPDATE Ave SET Dieta = ?, Gaiola = ?, Penugem = ?, Espécie = ?, Invergadura = ? "
                  "WHERE SequencialAve = ?";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(ave->isDieta());
    query.addBindValue(ave->isGaiola());
    query.addBindValue(QString::fromStdString(ave->getPenugem()));
    query.addBindValue(QString::fromStdString(ave->getEspecie()));
    query.addBindValue(QString::number(ave->getInvergadura()));
    query.addBindValue(id);

    if(query.exec())
        return "";
     else
        return "Erro ao atualizar AVE";
}

string Cachorro::alterarCachorro(Cachorro *cachorro, int id){
    QString sql = "UPDATE Cachorro SET Raça = ?, Pelagem = ?, Adestrado = ?, Castrado = ? "
                  "WHERE SequencialCao = ?";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(QString::fromStdString(cachorro->getRaca()));
    query.addBindValue(QString::fromStdString(cachorro->getPelagem()));
    query.addBindValue(cachorro->isAdestrado());
    query.addBindValue(cachorro->isCastrado());
    query.addBindValue(id);

    if(query.exec())
        return "";
     else
        return "Erro ao atualizar CACHORRO";
}

string Gato::alterarGato(Gato *gato, int id){
    QString sql = "UPDATE Gato SET Pelagem = ?, Castrado = ?, Observação = ? "
                  "WHERE SequencialGat = ?";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(QString::fromStdString(gato->getPelagem()));
    query.addBindValue(gato->isCastrado());
    query.addBindValue(QString::fromStdString(gato->getObservacao()));
    query.addBindValue(id);
    if(query.exec())
        return "";
     else
        return "Erro ao atualizar GATO";
}

string Tartaruga::alterarTartaruga(Tartaruga *tartaruga, int id){
    QString sql = "UPDATE Tartaruga SET Dieta = ?, TipoDeAmbiente = ?, TamanhoDaCarapaça = ? "
                  "WHERE SequencialTar = ?";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(tartaruga->isDieta());
    query.addBindValue(QString::fromStdString(tartaruga->getTipoDeAmbiente()));
    query.addBindValue(QString::number(tartaruga->getTamanhoDaCarapaca()));
    query.addBindValue(id);
    if(query.exec())
        return "";
     else
        return "Erro ao atualizar TARTARUGA";
}

string Outro::alterarOutro(Outro *outro, int id){

}



int Animal::obtemSequencial(){
    QString sql = "SELECT MAX(SequencialAni) as Seq FROM Animal";
    QSqlQuery query;
    int sequencial=-1;

    query.prepare(sql);
    if(query.exec()){
        while(query.next())
            sequencial = query.value("Seq").toInt();
    }
    else
      qDebug()<<"Erro ao extrair Sequencial de Animal";

    return sequencial;
}

Animal *Animal::buscarAnimal(int sequencial){
    QString sqlQualAnimal = "SELECT AveId Aid, CachorroId Cid, GatoId Gid, TartarugaId Tid, OutroAnimalId Oid FROM Animal Ani "
                  "WHERE Ani.SequencialAni = ?";

    QSqlQuery queryQualAnimal;
    Animal *animal = nullptr;

    QString aveId = nullptr;
    QString cachorroId = nullptr;
    QString gatoId = nullptr;
    QString tartarugaId = nullptr;
    QString outroAnimalId = nullptr;


    queryQualAnimal.prepare(sqlQualAnimal);
    queryQualAnimal.addBindValue(sequencial);

    if(queryQualAnimal.exec()){
        while(queryQualAnimal.next()){
            aveId = queryQualAnimal.value("Aid").toString();
            cachorroId = queryQualAnimal.value("Cid").toString();
            gatoId = queryQualAnimal.value("Gid").toString();
            tartarugaId = queryQualAnimal.value("Tid").toString();
            outroAnimalId = queryQualAnimal.value("Oid").toString();
        }
    }
     else
      qDebug()<<"Erro ao buscar Sequencial em Animal";



    if(aveId != nullptr){
        sqlQualAnimal = "SELECT * FROM Ave A, Animal Ani WHERE A.SequencialAve = ? AND A.SequencialAve = Ani.AveId";
        queryQualAnimal.prepare(sqlQualAnimal);
        queryQualAnimal.addBindValue(aveId.toInt());

        if(queryQualAnimal.exec()){
            while(queryQualAnimal.next()){
                animal = new Ave(queryQualAnimal.value("Dieta").toBool(),
                                 queryQualAnimal.value("Gaiola").toBool(),
                                 queryQualAnimal.value("Penugem").toString().toStdString(),
                                 queryQualAnimal.value("Espécie").toString().toStdString(),
                                 queryQualAnimal.value("Invergadura").toFloat(),
                                 queryQualAnimal.value("Nome").toString().toStdString(),
                                 queryQualAnimal.value("Sexo").toChar() == 'F' ? 'F' : 'M',
                                 queryQualAnimal.value("Idade").toInt(),
                                 queryQualAnimal.value("Peso").toFloat());
                animal->setSequencial(sequencial);
            }
        }
         else
            qDebug()<<"Erro ao buscar AVE com o SequencialAve";

    }
     else
       if(cachorroId != nullptr){
           sqlQualAnimal = "SELECT * FROM Cachorro C, Animal Ani WHERE C.SequencialCao = ? AND C.SequencialCao = Ani.CachorroId";
           queryQualAnimal.prepare(sqlQualAnimal);
           queryQualAnimal.addBindValue(cachorroId.toInt());

           if(queryQualAnimal.exec()){
               while(queryQualAnimal.next()){
                   animal = new Cachorro(queryQualAnimal.value("Raça").toString().toStdString(),
                                    queryQualAnimal.value("Pelagem").toString().toStdString(),
                                    queryQualAnimal.value("Adestrado").toBool(),
                                    queryQualAnimal.value("Castrado").toBool(),
                                    queryQualAnimal.value("Nome").toString().toStdString(),
                                    queryQualAnimal.value("Sexo").toChar() == 'F' ? 'F' : 'M',
                                    queryQualAnimal.value("Idade").toInt(),
                                    queryQualAnimal.value("Peso").toFloat());
                   animal->setSequencial(sequencial);
               }
           }
            else
               qDebug()<<"Erro ao buscar CACHORRO com o SequencialCao";

       }
        else
           if(gatoId != nullptr){
               sqlQualAnimal = "SELECT * FROM Gato G, Animal Ani WHERE G.SequencialGat = ? AND G.SequencialGat = Ani.GatoId";
               queryQualAnimal.prepare(sqlQualAnimal);
               queryQualAnimal.addBindValue(gatoId.toInt());

               if(queryQualAnimal.exec()){
                   while(queryQualAnimal.next()){
                       animal = new Gato(queryQualAnimal.value("Pelagem").toString().toStdString(),
                                        queryQualAnimal.value("Castrado").toBool(),
                                        queryQualAnimal.value("Observação").toString().toStdString(),
                                        queryQualAnimal.value("Nome").toString().toStdString(),
                                        queryQualAnimal.value("Sexo").toChar() == 'F' ? 'F' : 'M',
                                        queryQualAnimal.value("Idade").toInt(),
                                        queryQualAnimal.value("Peso").toFloat());
                       animal->setSequencial(sequencial);
                   }
               }
                else
                   qDebug()<<"Erro ao buscar GATO com o SequencialGat";

           }
            else
               if(tartarugaId != nullptr){
                   sqlQualAnimal = "SELECT * FROM Tartaruga T, Animal Ani WHERE T.SequencialTar = ? AND T.SequencialTar = Ani.TartarugaId";
                   queryQualAnimal.prepare(sqlQualAnimal);
                   queryQualAnimal.addBindValue(tartarugaId.toInt());

                   if(queryQualAnimal.exec()){
                       while(queryQualAnimal.next()){
                           animal = new Tartaruga(queryQualAnimal.value("Dieta").toBool(),
                                            queryQualAnimal.value("TipoDeAmbiente").toString().toStdString(),
                                            queryQualAnimal.value("TamanhoDaCarapaça").toFloat(),
                                            queryQualAnimal.value("Nome").toString().toStdString(),
                                            queryQualAnimal.value("Sexo").toChar() == 'F' ? 'F' : 'M',
                                            queryQualAnimal.value("Idade").toInt(),
                                            queryQualAnimal.value("Peso").toFloat());
                           animal->setSequencial(sequencial);
                       }
                   }
                    else
                       qDebug()<<"Erro ao buscar TARTARUGA com o SequencialTar";

               }
                else
                   if(outroAnimalId != nullptr){

                   }

    return animal;
}

Animal *Animal::buscarAnimalSemCliente(){
    QString sql = "SELECT SequencialAni FROM Animal A WHERE A.SequencialAni NOT IN (SELECT AnimalId FROM Cliente)";
    QSqlQuery query;
    int sequencial, c;
    Animal *animal;

    query.prepare(sql);

    if(query.exec()){
        c = 0;
        while(query.next()){
            c++;
            sequencial = query.value("SequencialAni").toInt();
        }
    }
     else
        qDebug()<<"Erro na funcao buscarAnimalSemVinculo";

    if(c > 0)//se existe mais de um animal sem cliente, retorna o ultimo animal
        animal = buscarAnimal(sequencial);
    else
        animal = nullptr;

    return animal;
}

bool Animal::isAnimalVinculado(int sequencial){
    QString sql = "SELECT * FROM Animal A, Cliente WHERE A.SequencialAni = ? AND A.SequencialAni = Cliente.AnimalId";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(sequencial);

    if(query.exec())
        while(query.next())
            return true;

    return false;
}
