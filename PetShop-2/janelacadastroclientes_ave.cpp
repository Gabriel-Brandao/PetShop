#include "janelacadastroclientes_ave.h"
#include "ui_janelacadastroclientes_ave.h"

#include <QMessageBox>
#include "janelacadastroclientes.h"
#include"animal.h"
#include "controladoranimal.h"
#include <iostream>


Animal *dadosAve = nullptr;

JanelaCadastroClientes_Ave::JanelaCadastroClientes_Ave(QWidget *parent, Animal *dados, bool consulta) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes_Ave)
{
    ui->setupUi(this);
    dadosAve = dados;
    if(consulta){
        Ave *ave = dynamic_cast<Ave*>(dados);
        consultarAve(ave->isDieta(), ave->isGaiola(), ave->getPenugem(), ave->getEspecie(), ave->getInvergadura());
        on_pb_aveAlterar_toggled(true);
    }
     else
        on_pb_aveAlterar_toggled(false);
}

JanelaCadastroClientes_Ave::~JanelaCadastroClientes_Ave(){
    delete ui;
}

void JanelaCadastroClientes_Ave::on_pb_aveInserir_clicked(){//INSERIR
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

    bool gaiola;
    if(ui->rb_gaiolaSim->isChecked())
        gaiola = true;
      else if(ui->rb_gaiolaNao->isChecked())
               gaiola =  false;
            else{
                 QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
                 return;
            }

    string penugem = ui->txt_penugem->text().toStdString();
    string especie = ui->txt_especie->text().toStdString();
    string invergadura = ui->txt_invergadura->text().toStdString();
    if(!penugem.compare("") || !invergadura.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

     string mensagem_erro = "";
     animal = new Ave(dieta, gaiola, penugem, especie, controladorjCC.converterParaFloat(invergadura),
                              dadosAve->getNome(), dadosAve->getSexo(), dadosAve->getIdade(), dadosAve->getPeso());

     cout << animal->getSexo()  << " [janelaCadastro_Cachorro/INSERIR]"<< endl;

     if(animal != nullptr)
         mensagem_erro = ControladorAnimal::inserirAnimal(animal);
     else
         mensagem_erro = "Algum atributo do Animal nao foi preeenchido";

     if(!mensagem_erro.compare("")){
         int sequencial = animal->obtemSequencial();
         animal->setSequencial(sequencial);
     }
      else
         QMessageBox::critical(this, "ERRO !", QString::fromStdString(mensagem_erro));

    this->close();
}

void JanelaCadastroClientes_Ave::on_pb_aveAlterar_clicked(){//ALTERAR
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

    bool gaiola;
    if(ui->rb_gaiolaSim->isChecked())
        gaiola = true;
      else if(ui->rb_gaiolaNao->isChecked())
               gaiola =  false;
            else{
                 QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
                 return;
            }

    string penugem = ui->txt_penugem->text().toStdString();
    string especie = ui->txt_especie->text().toStdString();
    string invergadura = ui->txt_invergadura->text().toStdString();
    if(!penugem.compare("") || !invergadura.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

     string mensagem_erro = "";
     animal = new Ave(dieta, gaiola, penugem, especie, controladorjCC.converterParaFloat(invergadura),
                              dadosAve->getNome(), dadosAve->getSexo(), dadosAve->getIdade(), dadosAve->getPeso());

     animal->setSequencial(dadosAve->getSequencial());

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

void JanelaCadastroClientes_Ave::consultarAve(bool dieta, bool gaiola, string penugem, string especie, float invergadura){
    if(dieta){
        ui->rb_dietaSim->setChecked(true);
        ui->rb_dietaNao->setChecked(false);
    }
     else{
        ui->rb_dietaSim->setChecked(false);
        ui->rb_dietaNao->setChecked(true);
    }

    if(gaiola){
        ui->rb_gaiolaSim->setChecked(true);
        ui->rb_gaiolaNao->setChecked(false);
    }
     else{
        ui->rb_gaiolaSim->setChecked(false);
        ui->rb_gaiolaNao->setChecked(true);
    }

    ui->txt_penugem->setText(QString::fromStdString(penugem));
    ui->txt_especie->setText(QString::fromStdString(especie));
    ui->txt_invergadura->setText(QString::number(invergadura));
}


void JanelaCadastroClientes_Ave::on_pb_aveAlterar_toggled(bool checked){
    if(checked){
        ui->pb_aveAlterar->setEnabled(true);
        ui->pb_aveInserir->setEnabled(false);
    }
     else{
        ui->pb_aveAlterar->setEnabled(false);
        ui->pb_aveInserir->setEnabled(true);
    }

}


