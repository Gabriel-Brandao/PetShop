#include "janelacadastroclientes_outro.h"
#include "ui_janelacadastroclientes_outro.h"
#include "janelacadastroclientes.h"

Animal *dadosOutro = nullptr;

JanelaCadastroClientes_Outro::JanelaCadastroClientes_Outro(QWidget *parent, Animal *dados, bool consulta) :
    QDialog(parent),
    ui(new Ui::JanelaCadastroClientes_Outro)
{
    ui->setupUi(this);
    dadosOutro = dados;
    if(consulta){
        Outro *outro = dynamic_cast<Outro*>(dados);
        //consultarAve(ave->isDieta(), ave->isGaiola(), ave->getPenugem(), ave->getEspecie(), ave->getInvergadura());
    }
}

JanelaCadastroClientes_Outro::~JanelaCadastroClientes_Outro()
{
    delete ui;
}
