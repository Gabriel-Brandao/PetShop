#include "janelacadastroservicos.h"
#include "ui_janelacadastroservicos.h"
#include "controladorservico.h"
#include "servico.h"

#include <QMessageBox>
#include <iostream>
#include <sstream>

using namespace std;


JanelaCadastroServicos::JanelaCadastroServicos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroServicos)
{
    ui->setupUi(this);
    on_cb_retorno_toggled(false);
    on_pb_consultarServico_toggled(false);

    QString sql = "SELECT  C.AnimalId Seq, C.Nome, C.Cpf "
                  "FROM Cliente C ORDER BY AnimalId ASC";
    atualizaComboBoxClientes(0, sql);
    sql = "SELECT C.Cpf, C.Nome, S.Serviços, S.Valor, S.SequencialSer Seq "
          "FROM Serviço S, Cliente C "
          "WHERE S.ClienteId = C.Cpf ORDER BY S.SequencialsER ASC";
    atualizaComboBoxServicos(0, sql);
}

JanelaCadastroServicos::~JanelaCadastroServicos()
{
    delete ui;
}

void JanelaCadastroServicos::atualizaComboBoxClientes(int index, QString sql){
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
                    ui->cbox_clientes->insertItem(1,visao);
                    ui->cbox_clientes->setCurrentIndex(1);
                }
            }
             else
               qDebug() << "Não foi possível atualizar o ComboBox dos Clientes²";
         }
}

void JanelaCadastroServicos::atualizaComboBoxServicos(int index, QString sql){
    QString cpf, nome, servicos, valor, sequencialSer, visao;
    QSqlQuery query;

    int maxSequencial=-1;
    QString sqlChecagem = "SELECT MAX(SequencialSer) Seq FROM Serviço";

    query.prepare(sqlChecagem);
    if(query.exec()){
        while(query.next())
            maxSequencial = query.value("Seq").toInt();
    }
     else
        qDebug() << "Não foi possível atualizar o ComboBox dos Serviços¹";

        if(index != maxSequencial){
            query.prepare(sql);
            if(query.exec()){
                while(query.next()){
                    cpf = "";
                    nome = "";
                    servicos = "";
                    valor = "";
                    sequencialSer = "";
                    visao = "";

                    cpf = query.value("Cpf").toString();
                    nome = query.value("Nome").toString();
                    servicos = query.value("Serviços").toString();
                    valor = query.value("Valor").toString();
                    sequencialSer = query.value("Seq").toString();

                    vector<string> tokens;    // vetor de sub-string
                    istringstream tokenizer { servicos.toStdString() };// stream de strings de input inicializado com a string a ser separada
                    string token;// auxiliar
                    while (getline(tokenizer, token, ','))// separa as sub-strings por virgulas e coloca no vetor destino
                       tokens.push_back(token);

                    int n = tokens.size();
                    visao += cpf + " - " + nome + " - " + QString::number(n) + " serviços - R$" + valor + " - [" + sequencialSer + "]";
                    ui->cbox_servico->insertItem(1, visao);
                    ui->cbox_servico->setCurrentIndex(1);
                }
            }
             else
               qDebug() << "Não foi possível atualizar o ComboBox dos Clientes²";
        }











}

Cliente* JanelaCadastroServicos::getComboBoxClientes(){
    string comboBox = ui->cbox_clientes->currentText().toStdString();

    if(!comboBox.compare("")){
        qDebug() << "Não foi possivel acessar o combo box de clientes [JanelaCadastroServiços.cpp/getComboBoxClientes()]";
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

Servico *JanelaCadastroServicos::obtemDadosServico(){
    vector<TipoDeServico> *listaDeServicos = new vector<TipoDeServico>();

    Cliente *cliente = getComboBoxClientes();
    if(cliente == nullptr)
        return nullptr;

   string valor = ui->txt_valor->text().toStdString();
   if(!valor.compare(""))
       return nullptr;

   if(ui->cb_adestramento->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(0));

   if(ui->cb_banho->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(1));

   if(ui->cb_castracao->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(2));

   if(ui->cb_consulta->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(3));

   if(ui->cb_doacao->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(4));

   if(ui->cb_hospedagem->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(5));

   if(ui->cb_lojinha->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(6));

   if(ui->cb_tosa->isChecked())
       listaDeServicos->push_back(static_cast<TipoDeServico>(7));

   if(listaDeServicos->size() == 0)//se não for selecionado nenhum serviço
       return nullptr;

   bool agendarVacina = ui->cb_agendarVacina->isChecked();
   string dataStr = "";
   Data *data = new Data();

   if(ui->cb_retorno->isChecked()){
      dataStr = ui->txt_retorno->text().toStdString();
      if(!dataStr.compare(""))
          return nullptr;

       vector<int> tokens;    // vetor de sub-string
       istringstream tokenizer { dataStr };// stream de strings de input inicializado com a string a ser separada
       string token;// auxiliar
       while (getline(tokenizer, token, '/'))// separa as sub-strings por / e coloca no vetor destino
          tokens.push_back(stoi(token));
       data = new Data(tokens[0], tokens[1], tokens[2]);
   }

      Servico *servico = new Servico(cliente, converterParaFloat(valor), agendarVacina, data, listaDeServicos);
      return servico;
}


void JanelaCadastroServicos::on_pb_inserirServico_clicked(){//INSERIR
    int index = ui->cbox_servico->count() - 1;
    string mensagem_erro = "";
    Servico *servico = obtemDadosServico();



    vector<TipoDeServico> *listaDeServicos = new vector <TipoDeServico>;
    listaDeServicos = servico->getTipoDeServico();
    int n = listaDeServicos->size();
    for(int i = 0; i < n; i++){
        cout << "janelaServicos.cpp/INSERIR " << listaDeServicos->back() << endl;
        listaDeServicos->pop_back();
    }



    if(servico != nullptr)
        mensagem_erro = ControladorServico::inserirServico(servico);
    else
        mensagem_erro = "Algum atributo do Servico nao foi preeenchido, ou o Cliente nao foi selecionado";

    if(!mensagem_erro.compare("")){
        //atualizar combobox se necessario
        QString sql = "SELECT C.Cpf, C.Nome, S.Serviços, S.Valor, MAX(S.SequencialSer) Seq "
                      "FROM Serviço S, Cliente C WHERE S.ClienteId = C.Cpf";
        atualizaComboBoxServicos(index, sql);
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));
}


void JanelaCadastroServicos::on_pb_limparServico_clicked(){//LIMPAR
    ui->txt_valor->clear();
    ui->txt_retorno->clear();

    ui->cb_adestramento->setChecked(false);
    ui->cb_banho->setChecked(false);
    ui->cb_castracao->setChecked(false);
    ui->cb_consulta->setChecked(false);
    ui->cb_doacao->setChecked(false);
    ui->cb_hospedagem->setChecked(false);
    ui->cb_lojinha->setChecked(false);
    ui->cb_tosa->setChecked(false);

    ui->cb_agendarVacina->setChecked(false);
    ui->cb_retorno->setChecked(false);
    ui->txt_retorno->setDisabled(true);

    ui->cbox_clientes->setCurrentIndex(0);
    ui->cbox_servico->setCurrentIndex(0);
}

void JanelaCadastroServicos::on_cb_retorno_toggled(bool checked){
    ui->txt_retorno->setText("");
    if(checked)
        ui->txt_retorno->setEnabled(true);
    else
        ui->txt_retorno->setDisabled(true);
}

void JanelaCadastroServicos::on_pb_consultarServico_toggled(bool checked){
    if(checked){
        ui->pb_alterarServico->setEnabled(true);
        ui->pb_removerServico->setEnabled(true);
    }
     else{
        ui->pb_alterarServico->setDisabled(true);
        ui->pb_removerServico->setDisabled(true);
    }
}

int JanelaCadastroServicos::converterParaInt(string str){
    istringstream iss(str);
    int retorno;
    iss >> retorno;
    return retorno;
}

float JanelaCadastroServicos::converterParaFloat(string str){
    istringstream iss(str);
    float retorno;
    iss >> retorno;
    return retorno;
}
