#include "janelacadastroclientes_cachorro.h"
#include "ui_janelacadastroclientes_cachorro.h"

#include <QMessageBox>
#include "janelacadastroclientes.h"
#include "controladoranimal.h"
#include "animal.h"
#include <iostream>

using namespace std;

Animal *dadosCao = nullptr;

JanelaCadastroClientes_Cachorro::JanelaCadastroClientes_Cachorro(QWidget *parent, Animal *dados, bool consulta) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes_Cachorro)
{
    ui->setupUi(this);
    dadosCao = dados;
    if(consulta){
        Cachorro *cao = dynamic_cast<Cachorro*>(dados);
        consultarCachorro(cao->getRaca(), cao->getPelagem(), cao->isAdestrado(), cao->isCastrado());
        on_pb_cachorroAlterar_toggled(true);
    }
     else
        on_pb_cachorroAlterar_toggled(false);
}

JanelaCadastroClientes_Cachorro::~JanelaCadastroClientes_Cachorro()
{
    delete ui;
}

void JanelaCadastroClientes_Cachorro::on_pb_cachorroInserir_clicked(){//INSERIR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    string raca = ui->txt_raca->text().toStdString();
    string pelagem = ui->txt_pelagem->text().toStdString();
    if(!pelagem.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }
    bool adestrado = ui->cb_adestrado->isChecked();
    bool castrado = ui->cb_castrado->isChecked();

    string mensagem_erro = "";
    animal = new Cachorro(raca, pelagem, adestrado, castrado,
                          dadosCao->getNome(), dadosCao->getSexo(), dadosCao->getIdade(), dadosCao->getPeso());

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

void JanelaCadastroClientes_Cachorro::on_pb_cachorroAlterar_clicked(){//ALTERAR
    JanelaCadastroClientes controladorjCC;
    Animal *animal;

    string raca = ui->txt_raca->text().toStdString();
    string pelagem = ui->txt_pelagem->text().toStdString();
    if(!pelagem.compare("")){
        QMessageBox::critical(this, "ERRO", "Campo obrigatorio nao preenchido");
        return;
    }
    bool adestrado = ui->cb_adestrado->isChecked();
    bool castrado = ui->cb_castrado->isChecked();

    string mensagem_erro = "";
    animal = new Cachorro(raca, pelagem, adestrado, castrado,
                          dadosCao->getNome(), dadosCao->getSexo(), dadosCao->getIdade(), dadosCao->getPeso());

    animal->setSequencial(dadosCao->getSequencial());

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


void JanelaCadastroClientes_Cachorro::consultarCachorro(string raca, string pelagem, bool adestrado, bool castrado){
    ui->txt_raca->setText(QString::fromStdString(raca));
    ui->txt_pelagem->setText(QString::fromStdString(pelagem));
    if(adestrado)
        ui->cb_adestrado->setChecked(true);
    else
        ui->cb_adestrado->setChecked(false);

    if(castrado)
        ui->cb_castrado->setChecked(true);
    else
        ui->cb_castrado->setChecked(false);
}

void JanelaCadastroClientes_Cachorro::on_pb_cachorroAlterar_toggled(bool checked){
    if(checked){
        ui->pb_cachorroAlterar->setEnabled(true);
        ui->pb_cachorroInserir->setEnabled(false);
    }
     else{
        ui->pb_cachorroAlterar->setEnabled(false);
        ui->pb_cachorroInserir->setEnabled(true);
    }
}
