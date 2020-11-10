#include "janelacadastroclientes_gato.h"
#include "ui_janelacadastroclientes_gato.h"
#include "controladoranimal.h"

#include <QMessageBox>
#include "janelacadastroclientes.h"
#include "animal.h"
#include <iostream>

using namespace std;

using namespace std;

Animal *dadosGato = nullptr;

JanelaCadastroClientes_Gato::JanelaCadastroClientes_Gato(QWidget *parent, Animal *dados, bool consulta) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes_Gato)
{
    ui->setupUi(this);
    dadosGato = dados;
    if(consulta){
        Gato *gato = dynamic_cast<Gato*>(dados);
        consultarGato(gato->getPelagem(), gato->isCastrado(), gato->getObservacao());
        on_pb_gatoAlterar_toggled(true);
    }
     else
        on_pb_gatoAlterar_toggled(false);
}

JanelaCadastroClientes_Gato::~JanelaCadastroClientes_Gato()
{
    delete ui;
}

void JanelaCadastroClientes_Gato::on_pb_gatoInserir_clicked(){//INSERIR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    string pelagem = ui->txt_pelagem->text().toStdString();
    if(!pelagem.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

    bool castrado = ui->cb_castrado->isChecked();
    string observacao = ui->txtEdit_observacao->toPlainText().toStdString();

    string mensagem_erro = "";
    animal = new Gato(pelagem, castrado, observacao,
                        dadosGato->getNome(), dadosGato->getSexo(), dadosGato->getIdade(), dadosGato->getPeso());

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

void JanelaCadastroClientes_Gato::on_pb_gatoAlterar_clicked(){//ALTERAR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    string pelagem = ui->txt_pelagem->text().toStdString();
    if(!pelagem.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }

    bool castrado = ui->cb_castrado->isChecked();
    string observacao = ui->txtEdit_observacao->toPlainText().toStdString();

    string mensagem_erro = "";
    animal = new Gato(pelagem, castrado, observacao,
                        dadosGato->getNome(), dadosGato->getSexo(), dadosGato->getIdade(), dadosGato->getPeso());

    animal->setSequencial(dadosGato->getSequencial());

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


void JanelaCadastroClientes_Gato::consultarGato(string pelagem, bool castrado, string observacao){
    ui->txt_pelagem->setText(QString::fromStdString(pelagem));

    if(castrado)
        ui->cb_castrado->setChecked(true);
    else
        ui->cb_castrado->setChecked(false);

    ui->txtEdit_observacao->setText(QString::fromStdString(observacao));
}

void JanelaCadastroClientes_Gato::on_pb_gatoAlterar_toggled(bool checked){
    if(checked){
        ui->pb_gatoAlterar->setEnabled(true);
        ui->pb_gatoInserir->setEnabled(false);
    }
     else{
        ui->pb_gatoAlterar->setEnabled(false);
        ui->pb_gatoInserir->setEnabled(true);
    }
}

