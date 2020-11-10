#include "cliente.h"
//#include "Animal.h"
#include <iostream>

using namespace std;

Cliente::Cliente(Animal *pet, string nome, int idade, string cpf, Endereco *endereco){
    this->pet = pet;
    this->nome = nome;
    this->idade = idade;
    this->cpf = cpf;
    this->endereco = endereco;
}

void Cliente::setPet(Animal *animal){
    this->pet = animal;
}

Animal* Cliente::getPet(){
  return this->pet;
}

string Cliente::getNome(){
    return this->nome;
}

int Cliente::getIdade(){
    return this->idade;
}

string Cliente::getCpf(){
    return this->cpf;
}

Endereco* Cliente::getEndereco(){
    return this->endereco;
}
//***************** S Q L ******************************

Cliente* Cliente::buscarCliente(string cpf){
    QString sql = "SELECT * FROM Cliente C WHERE C.Cpf = ?";
    QSqlQuery query;

    int animalId = -1;
    Animal *animal = nullptr;
    int idade;
    QString nome;
    Cliente *cliente = nullptr;
    int enderecoId = -1;
    Endereco *endereco = nullptr;

    query.prepare(sql);
    query.addBindValue(QString::fromStdString(cpf));

    if(query.exec()){
        while(query.next()){
            nome = query.value("Nome").toString();
            idade = query.value("Idade").toInt();
            animalId = query.value("AnimalId").toInt();
            enderecoId = query.value("EndereçoId").toInt();

            animal = Animal::buscarAnimal(animalId);
            endereco = Endereco::buscaEndereco(enderecoId);
            if(animal != nullptr && endereco != nullptr)  //se tiver tudo certo
                cliente = new Cliente (animal, nome.toStdString(), idade, cpf, endereco);
        }
    }
     else
        qDebug() << "Falha ao buscar cliente [cliente.cpp/buscarCliente()]";

    return cliente;
}

string Cliente::inserirCliente(Cliente *cliente){
    string mensagem_erro = "";

    int animalId;
    Endereco *endereco = cliente->getEndereco();
    int enderecoId;
    QString sql = "INSERT INTO Cliente (Nome, Idade, Cpf, EndereçoId, AnimalId) VALUES (?, ?, ?, ?, ?)";
    QSqlQuery query;

    if(!Animal::isAnimalVinculado(cliente->getPet()->getSequencial())){ //não há cliente vinculado a esse pet

        animalId = Animal::obtemSequencial();
        if(animalId == -1)
            mensagem_erro = "Não foi possivel extrair o Sequencial do animal [cliente.cpp/inserirCliente()]";
        if(mensagem_erro.compare(""))//se nao ta vazia
            return mensagem_erro;


        mensagem_erro = Endereco::inserirEndereco(endereco);
        if(mensagem_erro.compare(""))//se nao ta vazia
            return mensagem_erro;

        enderecoId = Endereco::obtemSequencial();
        if(enderecoId == -1)
            mensagem_erro = "Não foi possivel extrair o Sequencial do Endereco [cliente.cpp/inserirCliente()]";
        if(mensagem_erro.compare(""))//se nao ta vazia
            return mensagem_erro;
        //se tiver tudo certo vai inserir cliente:
        query.prepare(sql);

        query.addBindValue(QString::fromStdString(cliente->getNome()));
        query.addBindValue(cliente->getIdade());
        query.addBindValue(QString::fromStdString(cliente->getCpf()));
        query.addBindValue(enderecoId);
        query.addBindValue(animalId);

        if(query.exec())
            mensagem_erro = "";
        else
            mensagem_erro = "Nao foi possivel cadastrar o cliente [cliente.cpp/inserirCliente()]";
    }
     else
        mensagem_erro = "O Pet Selecionado já está cadastrado !! [cliente.cpp/inserirCliente()]";

    return mensagem_erro;
}

string Cliente::alterarCliente(Cliente *cliente){
    Animal *animal = cliente->getPet();
    QString sqlAnimal = "UPDATE Animal SET  Nome = ?, Sexo = ?, Idade = ?, Peso = ? "
                       "WHERE SequencialAni = (SELECT AnimalId FROM Cliente WHERE Cliente.Cpf = ?)";

   Endereco *endereco = cliente->getEndereco();
   QString sqlEndereco = "UPDATE Endereço SET  Cep = ?, Rua = ?, Numero = ?, Complemento = ?, Bairro = ?, Estado = ?, Cidade = ? "
                         "WHERE SequencialEnd = (SELECT EndereçoId FROM Cliente WHERE Cliente.Cpf = ?)";

   QString sqlCliente = "UPDATE Cliente SET Nome = ?, Idade = ? WHERE Cpf = ?";

   QSqlQuery query;

   query.prepare(sqlAnimal);
   query.addBindValue(QString::fromStdString(animal->getNome()));
   query.addBindValue(animal->getSexo());
   query.addBindValue(animal->getIdade());
   query.addBindValue(animal->getPeso());
   query.addBindValue(QString::fromStdString(cliente->getCpf()));
   if(!query.exec())
       return "Não foi possível atualizar o animal do cliente";

   query.prepare(sqlEndereco);
   query.addBindValue(QString::fromStdString(endereco->getCep()));
   query.addBindValue(QString::fromStdString(endereco->getRua()));
   query.addBindValue(endereco->getNumero());
   query.addBindValue(QString::fromStdString(endereco->getComplemento()));
   query.addBindValue(QString::fromStdString(endereco->getBairro()));
   query.addBindValue(endereco->getEstado());
   query.addBindValue(QString::fromStdString(endereco->getCidade()));
   query.addBindValue(QString::fromStdString(cliente->getCpf()));
   if(!query.exec())
       return "Não foi possível atualizar o endereço de cliente";

   query.prepare(sqlCliente);
   query.addBindValue(QString::fromStdString(cliente->getNome()));
   query.addBindValue(cliente->getIdade());
   query.addBindValue(QString::fromStdString(cliente->getCpf()));
   if(!query.exec())
       return "Não foi possível atualizar o cliente";

   return "";
}

string Cliente::removerCliente(string cpf){
    string mensage_erro = "";
    QString sql = "SELECT EndereçoId FROM Cliente C, Endereço E "
                  "WHERE C.Cpf = ? AND C.EndereçoId = E.SequencialEnd";
    int endId=-1;
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(QString::fromStdString(cpf));

    if(query.exec()){
        while(query.next())
            endId = query.value("EndereçoId").toInt();
    }
     else
        mensage_erro = "Não foi possivel obter sequencial do endereço [cliente.cpp/removerCliente()]";

    //remoção ON DELETE CASCADE (de Filho para Pai)
    if(endId != -1){
        sql = "DELETE FROM Endereço WHERE SequencialEnd = ?";
        query.prepare(sql);
        query.addBindValue(endId);

        if(query.exec())
            mensage_erro = "";
        else
            mensage_erro = "Não foi possivel remover o cliente";
    }

    return mensage_erro;
}
