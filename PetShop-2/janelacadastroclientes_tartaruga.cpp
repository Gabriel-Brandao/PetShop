#include "janelacadastroclientes_tartaruga.h"
#include "ui_janelacadastroclientes_tartaruga.h"


#include <QMessageBox>
#include "janelacadastroclientes.h"
#include "controladoranimal.h"
#include <iostream>
#include "animal.h"

using namespace std;

Animal *dadosTartaruga = nullptr;

JanelaCadastroClientes_Tartaruga::JanelaCadastroClientes_Tartaruga(QWidget *parent, Animal *dados, bool consulta) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes_Tartaruga)
{
    ui->setupUi(this);
    dadosTartaruga = dados;
    if(consulta){
        Tartaruga *tartaruga = dynamic_cast<Tartaruga*>(dados);
        consultarTartaruga(tartaruga->isDieta(), tartaruga->getTipoDeAmbiente(), tartaruga->getTamanhoDaCarapaca());
        on_pb_tartarugaAlterar_toggled(true);
    }
     else
        on_pb_tartarugaAlterar_toggled(false);
}

JanelaCadastroClientes_Tartaruga::~JanelaCadastroClientes_Tartaruga()
{
    delete ui;
}


void JanelaCadastroClientes_Tartaruga::on_Inserir_clicked(){//INSERIR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    bool dieta;
    if(ui->rb_dietaSim->isChecked())
        dieta = true;
    else if(ui->rb_dietaNao->isChecked())
        dieta = false;
     else{
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

    string tipoDeAmbiente = ui->txtEdit_tipoDeAmbiente->toPlainText().toStdString();
    string tamanhoDaCarapaca = ui->txt_tamanhoDaCarapaca->text().toStdString();
    if(!tipoDeAmbiente.compare("") || !tamanhoDaCarapaca.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }


    string mensagem_erro = "";
    animal   = new Tartaruga(dieta, tipoDeAmbiente, controladorjCC.converterParaFloat(tamanhoDaCarapaca),
                             dadosTartaruga->getNome(), dadosTartaruga->getSexo(), dadosTartaruga->getIdade(), dadosTartaruga->getPeso());

    cout << animal->getSexo()  << " [janelaCadastro_Cachorro/INSERIR]"<< endl;

    if(animal != nullptr)
        mensagem_erro = ControladorAnimal::inserirAnimal(animal);
    else
        mensagem_erro = "Algum atributo do Animal nao foi preeenchido";

    if(!mensagem_erro.compare("")){
        int sequencial = animal->obtemSequencial();
        animal->setSequencial(sequencial);
        cout << "Combo Box ANIMAL Preenchido" << endl;//**
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));

     this->close();
}

void JanelaCadastroClientes_Tartaruga::on_pb_tartarugaAlterar_clicked(){//ALTERAR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    bool dieta;
    if(ui->rb_dietaSim->isChecked())
        dieta = true;
    else if(ui->rb_dietaNao->isChecked())
        dieta = false;
     else{
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

    string tipoDeAmbiente = ui->txtEdit_tipoDeAmbiente->toPlainText().toStdString();
    string tamanhoDaCarapaca = ui->txt_tamanhoDaCarapaca->text().toStdString();
    if(!tipoDeAmbiente.compare("") || !tamanhoDaCarapaca.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }


    string mensagem_erro = "";
    animal   = new Tartaruga(dieta, tipoDeAmbiente, controladorjCC.converterParaFloat(tamanhoDaCarapaca),
                             dadosTartaruga->getNome(), dadosTartaruga->getSexo(), dadosTartaruga->getIdade(), dadosTartaruga->getPeso());

    cout << dadosTartaruga->getSexo()  << " [janelaCadastro_Cachorro/INSERIR]"<< endl;

    animal->setSequencial(dadosTartaruga->getSequencial());

    if(animal != nullptr)
        mensagem_erro = ControladorAnimal::alterarAnimal(animal);
    else
        mensagem_erro = "Algum atributo do Animal nao foi preeenchido";

    if(!mensagem_erro.compare("")){
         QMessageBox::warning(this, "ALERTA!", "O animal foi alterado, com sucesso clique em \"Alterar\" na janela Cliente, para concluir o processo");
    }
     else
        QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));

     this->close();
}


void JanelaCadastroClientes_Tartaruga::consultarTartaruga(bool dieta, string ambiente, float tamanhoCarapaca){
    if(dieta){
        ui->rb_dietaSim->setChecked(true);
        ui->rb_dietaNao->setChecked(false);
    }
     else{
        ui->rb_dietaSim->setChecked(false);
        ui->rb_dietaNao->setChecked(true);
    }
    ui->txtEdit_tipoDeAmbiente->setText(QString::fromStdString(ambiente));
    ui->txt_tamanhoDaCarapaca->setText(QString::number(tamanhoCarapaca));
}

void JanelaCadastroClientes_Tartaruga::on_pb_tartarugaAlterar_toggled(bool checked){
    if(checked){
        ui->pb_tartarugaAlterar->setEnabled(true);
        ui->Inserir->setEnabled(false);
    }
     else{
        ui->pb_tartarugaAlterar->setEnabled(false);
        ui->Inserir->setEnabled(true);
    }
}


