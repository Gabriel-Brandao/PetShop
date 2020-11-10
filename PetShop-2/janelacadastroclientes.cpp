#include "janelacadastroclientes.h"
#include "ui_janelacadastroclientes.h"
#include "janelacadastroclientes_ave.h"
#include "janelacadastroclientes_tartaruga.h"
#include "janelacadastroclientes_cachorro.h"
#include "janelacadastroclientes_gato.h"
#include "controladorcliente.h"
#include "controladoranimal.h"
#include <QMessageBox>

#include "animal.h"
#include "cliente.h"
#include "endereco.h"
#include <string>
#include<stdlib.h>
#include <sstream>

#include <iostream>
#include <QScrollArea>

using namespace std;

JanelaCadastroClientes::JanelaCadastroClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes)
{

    ui->setupUi(this);

    this->setGeometry(0, 0, 551, 1000);
    on_pb_consultarCliente_toggled(false);
    QString sql = "SELECT A.SequencialAni Seq, "
                  "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                  "FROM Animal A ORDER BY SequencialAni ASC";
    atualizaComboBoxAnimais(0,sql);
    sql = "SELECT  C.AnimalId Seq, C.Nome, C.Cpf "
          "FROM Cliente C ORDER BY AnimalId ASC";
    atualizaComboBoxClientes(0,sql);
}

JanelaCadastroClientes::~JanelaCadastroClientes(){
    delete ui;
}

void JanelaCadastroClientes::on_pb_ave_clicked(){//Ave
    Animal* dadosAnimal = obtemDadosAnimal();
    if(dadosAnimal != nullptr){
           int index = ui->cbox_animaisCadastrados->count()-1;
           QString sql = "SELECT MAX(A.SequencialAni) Seq, "
                          "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                          "FROM Animal A";
           ControladorAnimal CA = ControladorAnimal(this, dadosAnimal, "Ave", false);
           atualizaComboBoxAnimais(index, sql);
    }
}

void JanelaCadastroClientes::on_pb_gato_clicked(){//Gato
    Animal* dadosAnimal = obtemDadosAnimal();
    if(dadosAnimal != nullptr){
            int index = ui->cbox_animaisCadastrados->count()-1;
            QString sql = "SELECT MAX(A.SequencialAni) Seq, "
                           "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                           "FROM Animal A";
            ControladorAnimal CA = ControladorAnimal(this, dadosAnimal, "Gato", false);
            atualizaComboBoxAnimais(index, sql);
    }
}

void JanelaCadastroClientes::on_pb_cachorro_clicked(){//Cachorro
    Animal* dadosAnimal = obtemDadosAnimal();
    if(dadosAnimal != nullptr){
            int index = ui->cbox_animaisCadastrados->count()-1;
            QString sql = "SELECT MAX(A.SequencialAni) Seq, "
                           "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                           "FROM Animal A";
            ControladorAnimal CA = ControladorAnimal(this, dadosAnimal, "Cachorro", false);
            atualizaComboBoxAnimais(index, sql);
    }

}

void JanelaCadastroClientes::on_pb_tartaruga_clicked(){//Tartaruga
    Animal* dadosAnimal = obtemDadosAnimal();
    if(dadosAnimal != nullptr){
            int index = ui->cbox_animaisCadastrados->count()-1;
            QString sql = "SELECT MAX(A.SequencialAni) Seq, "
                           "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                           "FROM Animal A";
            ControladorAnimal CA = ControladorAnimal(this, dadosAnimal, "Tartaruga", false);
            atualizaComboBoxAnimais(index, sql);
    }
}

void JanelaCadastroClientes::on_pb_outroAnimal_clicked(){//Outro Animal
    //limpaAnimal();
    Animal* dadosAnimal = obtemDadosAnimal();

    QMessageBox::information(this, "Outro Animal", "Outro animal foi cadastrado, complete os dados do cliente e clique em inserir para vincular");
}

void JanelaCadastroClientes::on_pb_limparCliente_clicked(){//LIMPAR
    ui->txt_nomeAnimal->clear();
    if(ui->rb_femea->isChecked()){
        ui->rb_femea->setAutoExclusive(false);
        ui->rb_femea->setChecked(false);
        ui->rb_femea->setAutoExclusive(true);
    }else{
        ui->rb_macho->setAutoExclusive(false);
        ui->rb_macho->setChecked(false);
        ui->rb_macho->setAutoExclusive(true);
    }
    ui->txt_idadeAnimal->clear();
    ui->txt_pesoAnimal->clear();

    ui->txt_nomeCliente->clear();
    ui->txt_idadeCliente->clear();
    ui->txt_cpfCliente->clear();

    ui->txt_cepCliente->clear();
    ui->txt_ruaCliente->clear();
    ui->txt_numeroCliente->clear();
    ui->txt_complementoCliente->clear();
    ui->txt_bairroCliente->clear();
    ui->cbox_estadoCliente->setCurrentIndex(0);
    ui->txt_cidadeCliente->clear();

    ui->cbox_animaisCadastrados->setCurrentIndex(0);
    ui->cbox_clientesCadastrados->setCurrentIndex(0);

    on_pb_consultarCliente_toggled(false);
}

void JanelaCadastroClientes::on_pb_inserirCliente_clicked(){//INSERIR
    string mensagem_erro = "";
    int index = ui->cbox_clientesCadastrados->count() - 1;
    Cliente *cliente = obtemDadosCliente();

    if(cliente != nullptr && cliente->getPet() != nullptr) //cliente está completo
        mensagem_erro = ControladorCliente::inserirCliente(cliente);
    else
        mensagem_erro = "Algum atributo do Cliente nao foi preeenchido, ou o Animal nao foi cadastrado [JanelaCadastroClientes.cpp/inserirClientes()]";

    if(!mensagem_erro.compare("")){
        //atualizar combobox se necessario
        QString sql = "SELECT MAX(C.AnimalId) Seq, C.Nome, C.Cpf FROM Cliente C";
        atualizaComboBoxClientes(index, sql);
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));
    on_pb_consultarCliente_toggled(false);
}

void JanelaCadastroClientes::on_pb_consultarCliente_clicked(){//CONSULTAR

    Cliente *cliente = getComboBoxClientes();
    Animal *animal = getComboBoxAnimais();
    on_pb_limparCliente_clicked();

    if(animal != nullptr && cliente != nullptr){
        QMessageBox::critical(this, "ERRO !", "Selecione um animal OU um cliente para consultar. "
                                              "Apenas uma entidade pode ser alterada ou removida por vez!!");
        return;
    }

    //pega cliente se não der certo pega animal.
    if(cliente == nullptr){

        if(animal != nullptr){
            setCamposDoCliente(animal);
            ui->txt_nomeAnimal->setText(QString::fromStdString(animal->getNome()));
            if(animal->getSexo() == 'F'){
                ui->rb_femea->setChecked(true);
                ui->rb_macho->setChecked(false);
            }
             else{
                ui->rb_femea->setChecked(false);
                ui->rb_macho->setChecked(true);
            }
            ui->txt_idadeAnimal->setText(QString::number(animal->getIdade()));
            ui->txt_pesoAnimal->setText(QString::number(animal->getPeso()));

            Ave *ave = dynamic_cast<Ave*>(animal);
            if(ave != nullptr){
                 ControladorAnimal(this, animal, "Ave", true);
            } else{
                Cachorro *cachorro = dynamic_cast<Cachorro*>(animal);
                if(cachorro != nullptr){
                   ControladorAnimal(this, animal, "Cachorro", true);
                 } else{
                    Gato *gato = dynamic_cast<Gato*>(animal);
                    if(gato != nullptr){
                       ControladorAnimal(this, animal, "Gato", true);
                     } else{
                        Tartaruga *tartaruga = dynamic_cast<Tartaruga*>(animal);
                        if(tartaruga != nullptr){
                             ControladorAnimal(this, animal, "Tartaruga", true);
                         } else{
                            Outro *outro = dynamic_cast<Outro*>(animal);
                            if(outro != nullptr){
                               ControladorAnimal(this, animal, "Outro", true);
                            }
                         }
                     }
                 }
             }
             on_pb_consultarCliente_toggled(true);
        }
         else
            QMessageBox::critical(this, "ERRO !", "Erro ao consultar, selecione um animal OU algum cliente");
    }
     else{
        setCamposDoAnimal(cliente);
        Endereco *endereco = cliente->getEndereco();
        ui->txt_nomeCliente->setText(QString::fromStdString(cliente->getNome()));
        ui->txt_idadeCliente->setText(QString::number(cliente->getIdade()));
        ui->txt_cpfCliente->setText(QString::fromStdString(cliente->getCpf()));

        ui->txt_cepCliente->setText(QString::fromStdString(endereco->getCep()));
        ui->txt_ruaCliente->setText(QString::fromStdString(endereco->getRua()));
        ui->txt_numeroCliente->setText(QString::number(endereco->getNumero()));
        ui->txt_complementoCliente->setText(QString::fromStdString(endereco->getComplemento()));
        ui->txt_bairroCliente->setText(QString::fromStdString(endereco->getBairro()));
        ui->cbox_estadoCliente->setCurrentIndex(endereco->getEstado());
        ui->txt_cidadeCliente->setText(QString::fromStdString(endereco->getCidade()));

        on_pb_consultarCliente_toggled(true);
    }


}

void JanelaCadastroClientes::on_pb_alterarCliente_clicked(){//ALTERAR
    string mensagem_erro = "";
    Cliente *cliente = obtemDadosCliente(); //animal está nullptr
    cliente->setPet(obtemDadosAnimal());

    if(cliente != nullptr && cliente->getPet() != nullptr)
        mensagem_erro = ControladorCliente::alterarCliente(cliente);
    else
        mensagem_erro = "Algum atributo do Cliente nao foi preeenchido, ou o Animal nao foi cadastrado [JanelaCadastroClientes.cpp/alterarClientes()]";

    if(!mensagem_erro.compare("")){
        //carrega comboBox do BD
        QString sql = "SELECT A.SequencialAni Seq, "
                      "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                      "FROM Animal A ORDER BY SequencialAni ASC";
        atualizaComboBoxAnimais(0,sql);
        sql = "SELECT  C.AnimalId Seq, C.Nome, C.Cpf "
              "FROM Cliente C ORDER BY AnimalId ASC";
        atualizaComboBoxClientes(0,sql);
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));

    on_pb_consultarCliente_toggled(false);
}

void JanelaCadastroClientes::on_pb_removerCliente_clicked(){//REMOVER
    string mensagem_erro = "";
    Cliente *cliente = obtemDadosCliente(); //animal está nullptr

    QMessageBox msgBox;
    msgBox.setWindowTitle("Remover");
    msgBox.setText(tr("Voce deseja remover:"));
    QAbstractButton* pButtonPet = msgBox.addButton(tr("Apenas o Pet"), QMessageBox::YesRole);
    QAbstractButton* pButtonAmbos = msgBox.addButton(tr("Pet e Cliente"), QMessageBox::AcceptRole);
    QAbstractButton* pButtonCliente = msgBox.addButton(tr("Apenas o Cliente"), QMessageBox::ApplyRole);
    QAbstractButton* pButtonCancelar = msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);
    msgBox.exec();

    if(cliente != nullptr){
        if (msgBox.clickedButton()==pButtonPet){
            cout << "Pet" << endl;//id
            int id = obtemSequencialAni(cliente->getCpf());
            mensagem_erro = ControladorAnimal::removerAnimal(id);
         }else
            if (msgBox.clickedButton()==pButtonCliente){
                cout << "Cliente" << endl;//string
                mensagem_erro = ControladorCliente::removerCliente(cliente->getCpf());
            }else
                if (msgBox.clickedButton()==pButtonAmbos){
                    cout << "Os dois" << endl;//string,id
                    int id = obtemSequencialAni(cliente->getCpf());
                    mensagem_erro = ControladorAnimal::removerAnimal(id);
                    mensagem_erro += ControladorCliente::removerCliente(cliente->getCpf());
                 }else
                    if (msgBox.clickedButton()==pButtonCancelar)
                        return;
    }else
        mensagem_erro = "Algum atributo do Cliente nao foi preeenchido, ou o Animal nao foi cadastrado [JanelaCadastroClientes.cpp/removerClientes()]";

    if(!mensagem_erro.compare("")){
        //carrega comboBox do BD
        QString sql = "SELECT A.SequencialAni Seq, "
                      "A.AveId Aid, A.CachorroId Cid, A.GatoId Gid, A.TartarugaId Tid, A.OutroAnimalId Oid, A.Nome "
                      "FROM Animal A ORDER BY SequencialAni ASC";
        atualizaComboBoxAnimais(0,sql);
        sql = "SELECT  C.AnimalId Seq, C.Nome, C.Cpf "
              "FROM Cliente C ORDER BY AnimalId ASC";
        atualizaComboBoxClientes(0,sql);
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));

    on_pb_consultarCliente_toggled(false);
}

int JanelaCadastroClientes::obtemSequencialAni(string cpf){
    QString sql = "SELECT SequencialAni id FROM Animal A, Cliente C "
                  "WHERE C.Cpf = ? AND C.AnimalId = SequencialAni";
    int id = -1;
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(QString::fromStdString(cpf));

    if(query.exec()){
        while(query.next())
            id = query.value("id").toInt();
    }
     else
        qDebug() << "Não foi possivel obter o animal desse cliente [janelaCadastroClientes.cpp/obtemSequencialAni()]";

    return id;
}

Animal* JanelaCadastroClientes::obtemDadosAnimal(){
    string nomeAnimal = ui->txt_nomeAnimal->text().toStdString();

    char sexoAnimal;
    if(ui->rb_femea->isChecked())
        sexoAnimal = 'F';
     else if(ui->rb_macho->isChecked())
         sexoAnimal = 'M';
      else{
            QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
            return nullptr;
        }
    string idadeAnimal = ui->txt_idadeAnimal->text().toStdString();
    string pesoAnimal = ui->txt_pesoAnimal->text().toStdString();
    if(!idadeAnimal.compare("") || !pesoAnimal.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return nullptr;
    }
    Animal *dadosAnimal = new Animal(nomeAnimal, sexoAnimal, converterParaInt(idadeAnimal), converterParaFloat(pesoAnimal));
    return dadosAnimal;
}

Cliente * JanelaCadastroClientes::obtemDadosCliente(){

    string nomeCliente = ui->txt_nomeCliente->text().toStdString();
    if(!nomeCliente.compare(""))
        return nullptr;

    string idadeCliente = ui->txt_idadeCliente->text().toStdString();
    if(!idadeCliente.compare(""))
        return nullptr;

    string cpfCliente = ui->txt_cpfCliente->text().toStdString();
    if(!cpfCliente.compare(""))
        return nullptr;

    string cepCliente = ui->txt_cepCliente->text().toStdString();
    if(!cepCliente.compare(""))
        return nullptr;

    string ruaCliente = ui->txt_ruaCliente->text().toStdString();

    string numeroCliente = ui->txt_numeroCliente->text().toStdString();
    if(!numeroCliente.compare(""))
        return nullptr;

    string complementoCliente = ui->txt_complementoCliente->text().toStdString();

    string bairroCliente = ui->txt_bairroCliente->text().toStdString();
    if(!bairroCliente.compare(""))
        return nullptr;

    Estado estadoCliente = static_cast<Estado>(getEstadoCliente(ui->cbox_estadoCliente->currentText().toStdString()));/*getEstadoCliente(ui->cbox_estadoCliente->currentText().toStdString());*/
    if(estadoCliente == NDA)
        return nullptr;

    string cidadeCliente = ui->txt_cidadeCliente->text().toStdString();
    if(!cidadeCliente.compare(""))
        return nullptr;


    Endereco *endereco =  new Endereco(cepCliente, ruaCliente, converterParaInt(numeroCliente), complementoCliente, bairroCliente, estadoCliente, cidadeCliente);
    Animal *animal = getComboBoxAnimais();
    Cliente *cliente;

    cliente = new Cliente(animal, nomeCliente, converterParaInt(idadeCliente), cpfCliente, endereco);

    return cliente;
}

Animal *JanelaCadastroClientes::getComboBoxAnimais(){
    string visao = ui->cbox_animaisCadastrados->currentText().toStdString();

    if(!visao.compare(""))
        return nullptr;

    vector<string> tokens;    // vetor de sub-string
    istringstream tokenizer { visao };// stream de strings de input inicializado com a string a ser separada
    string token;// auxiliar

    while (getline(tokenizer, token, ' '))// separa as sub-strings por espaço e coloca no vetor destino
       tokens.push_back(token);

    int sequencialAni = stoi(tokens[0]);

    Animal *animal = Animal::buscarAnimal(sequencialAni);

    return  animal;
}

Cliente *JanelaCadastroClientes::getComboBoxClientes(){
    string comboBox = ui->cbox_clientesCadastrados->currentText().toStdString();

    if(!comboBox.compare("")){
        qDebug() << "Não foi possivel acessar o combo box de clientes [JanelaCadastroClientes.cpp/getComboBoxClientes()]";
        return nullptr;
    }

    vector<string> tokens;    // vetor de sub-string
    istringstream tokenizer { comboBox };// stream de strings de input inicializado com a string a ser separada
    string token;// auxiliar

    while (getline(tokenizer, token, ' '))// separa as sub-strings por espaço e coloca no vetor destino
       tokens.push_back(token);

    string cpf = tokens[0];

    Cliente *cliente = Cliente::buscarCliente(cpf);
    return  cliente;
}

void JanelaCadastroClientes::atualizaComboBoxAnimais(int index, QString sql){
    QString aveId, cachorroId, gatoId, tartarugaId, outroAnimalId, id, queAnimal, nome, visao;
    QSqlQuery query;

    int maxSequencial=-1;
    QString sqlChecagem = "SELECT MAX(SequencialAni) Seq FROM Animal";

    query.prepare(sqlChecagem);
    if(query.exec()){
        while(query.next())
            maxSequencial = query.value("Seq").toInt();
    }
     else
        qDebug() << "Não foi possível atualizar o ComboBox dos Animais¹";


        if(index != maxSequencial){
            query.prepare(sql);
            if(query.exec()){
                while(query.next()){
                    aveId = nullptr;
                    cachorroId = nullptr;
                    gatoId = nullptr;
                    tartarugaId = nullptr;
                    outroAnimalId = nullptr;

                    id = "";
                    queAnimal = "";
                    nome = "";
                    visao = "";

                    aveId = query.value("Aid").toString();
                    cachorroId = query.value("Cid").toString();
                    gatoId = query.value("Gid").toString();
                    tartarugaId = query.value("Tid").toString();
                    outroAnimalId = query.value("Oid").toString();

                    id = query.value("Seq").toString();
                    nome = query.value("Nome").toString();

                    if(aveId != nullptr)
                        queAnimal = " - AVE - ";
                    else
                        if(cachorroId != nullptr)
                            queAnimal = " - CAO - ";
                        else
                            if(gatoId != nullptr)
                                queAnimal = " - GATO - ";
                            else
                                if(tartarugaId != nullptr)
                                    queAnimal = " - TARTARUGA - ";
                                else
                                    if(outroAnimalId != nullptr)
                                        queAnimal = " - OUTRO - ";

                    visao += id + queAnimal + nome;
                    ui->cbox_animaisCadastrados->insertItem(1,visao);
                    ui->cbox_animaisCadastrados->setCurrentIndex(1);
                }
            }
             else
                qDebug() << "Não foi possível atualizar o ComboBox dos Animais²";
    }
}

void JanelaCadastroClientes::atualizaComboBoxClientes(int index, QString sql){
    QString nome, cpf, animalId, visao;
    QSqlQuery query;

    int maxSequencial=-1;
    QString sqlChecagem = "SELECT MAX(AnimalId) Seq FROM Cliente";

    query.prepare(sqlChecagem);
    if(query.exec()){
        while(query.next())
            maxSequencial = query.value("Seq").toInt();
    }
     else
        qDebug() << "Não foi possível atualizar o ComboBox dos Clientes¹";


        if(index != maxSequencial){
            query.prepare(sql);
            if(query.exec()){
                while(query.next()){
                    cpf = "";
                    nome = "";
                    animalId = "";
                    visao = "";

                    cpf = query.value("Cpf").toString();
                    nome = query.value("Nome").toString();
                    animalId = query.value("Seq").toString();

                    visao += cpf + " - " + nome + " - [" + animalId + "]";
                    ui->cbox_clientesCadastrados->insertItem(1,visao);
                    ui->cbox_clientesCadastrados->setCurrentIndex(1);
                }
            }
             else
               qDebug() << "Não foi possível atualizar o ComboBox dos Clientes²";
         }
}

void JanelaCadastroClientes::setCamposDoCliente(Animal *animal){
    QString sql = "SELECT * FROM Cliente C, Animal A, Endereço E "
                  "WHERE C.AnimalId = A.SequencialAni AND A.SequencialAni = ? AND C.EndereçoId = E.SequencialEnd";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(animal->getSequencial());

    if(query.exec()){
        while(query.next()){
            ui->txt_nomeCliente->setText(query.value("Nome").toString());
            ui->txt_idadeCliente->setText(query.value("Idade").toString());
            ui->txt_cpfCliente->setText(query.value("Cpf").toString());

            ui->txt_cepCliente->setText(query.value("Cep").toString());
            ui->txt_ruaCliente->setText(query.value("Rua").toString());
            ui->txt_numeroCliente->setText(query.value("Numero").toString());
            ui->txt_complementoCliente->setText(query.value("Complemento").toString());
            ui->txt_bairroCliente->setText(query.value("Bairro").toString());
            ui->cbox_estadoCliente->setCurrentIndex(query.value("Estado").toInt());
            ui->txt_cidadeCliente->setText(query.value("Cidade").toString());
        }
    }
    else
        qDebug() << "Não foi possivel obter os dados do cliente [JanelaCliente.cpp/setCamposDoCliente()]";
}

void JanelaCadastroClientes::setCamposDoAnimal(Cliente *cliente){
    QString sql = "SELECT * FROM Animal A, Cliente C WHERE A.SequencialAni = C.AnimalId AND C.Cpf = ?";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(QString::fromStdString(cliente->getCpf()));

    if(query.exec()){
        while(query.next()){
            ui->txt_nomeAnimal->setText(query.value("Nome").toString());

            QChar sexo = query.value("Sexo").toChar();
            if(sexo == 'F'){
                ui->rb_femea->setChecked(true);
                ui->rb_macho->setChecked(false);
            }
             else{
                ui->rb_femea->setChecked(true);
                ui->rb_macho->setChecked(false);
              }

            ui->txt_idadeAnimal->setText(query.value("Idade").toString());
            ui->txt_pesoAnimal->setText(query.value("Peso").toString());
        }
    }
    else{
        qDebug() << "Não foi possivel obter os dados do animal [JanelaCliente.cpp/setCamposDoAnimal()]";
    }
}

void JanelaCadastroClientes::on_pb_consultarCliente_toggled(bool checked){
    if(checked){
        ui->pb_alterarCliente->setEnabled(true);
        ui->pb_removerCliente->setEnabled(true);
        ui->pb_inserirCliente->setDisabled(true);
        ui->pb_ave->setDisabled(true);
        ui->pb_cachorro->setDisabled(true);
        ui->pb_gato->setDisabled(true);
        ui->pb_tartaruga->setDisabled(true);
        ui->pb_outroAnimal->setDisabled(true);
    }
     else{
        ui->pb_alterarCliente->setDisabled(true);
        ui->pb_removerCliente->setDisabled(true);
        ui->pb_inserirCliente->setEnabled(true);
        ui->pb_ave->setEnabled(true);
        ui->pb_cachorro->setEnabled(true);
        ui->pb_gato->setEnabled(true);
        ui->pb_tartaruga->setEnabled(true);
        ui->pb_outroAnimal->setEnabled(true);
    }
}

int JanelaCadastroClientes::getEstadoCliente(string estado){

    if(!estado.compare("- - -"))
        return 0;

    if(!estado.compare("AC"))
        return 1;

    if(!estado.compare("AL"))
        return 2;

    if(!estado.compare("AP"))
        return 3;

    if(!estado.compare("AM"))
        return 4;

    if(!estado.compare("BA"))
        return 5;

    if(!estado.compare("CE"))
        return 6;

    if(!estado.compare("DF"))
        return 7;

    if(!estado.compare("ES"))
        return 8;

    if(!estado.compare("GO"))
        return 9;

    if(!estado.compare("MA"))
        return 10;

    if(!estado.compare("MT"))
        return 11;

    if(!estado.compare("MS"))
        return 12;

    if(!estado.compare("MG"))
        return 13;

    if(!estado.compare("PA"))
        return 14;

    if(!estado.compare("PB"))
        return 15;

    if(!estado.compare("PR"))
        return 16;

    if(!estado.compare("PE"))
        return 17;

    if(!estado.compare("PI"))
        return 18;

    if(!estado.compare("RJ"))
        return 19;

    if(!estado.compare("RN"))
        return 20;

    if(!estado.compare("RS"))
        return 21;

    if(!estado.compare("RO"))
        return 22;

    if(!estado.compare("RR"))
        return 23;

    if(!estado.compare("SC"))
        return 24;

    if(!estado.compare("SP"))
        return 25;

    if(!estado.compare("SE"))
        return 26;

    if(!estado.compare("TO"))
        return 27;
}

int JanelaCadastroClientes::converterParaInt(string str){
    istringstream iss(str);
    int retorno;
    iss >> retorno;
    return retorno;
}

float JanelaCadastroClientes::converterParaFloat(string str){
    istringstream iss(str);
    float retorno;
    iss >> retorno;
    return retorno;
}



