#include "janelaprincipal.h"
#include "janelacadastroclientes.h"
#include "controladorcliente.h"
#include "controladorservico.h"


#include "./ui_janelaprincipal.h"
#include "./ui_janelaprincipal.h"
#include "ui_janelaprincipal.h"
/*
#include "./ui_Janelaprincipal.h"
#include "./ui_Janelaprincipal.h"
#include "ui_Janelaprincipal.h"
*/
#include <iostream>
using namespace std;
JanelaPrincipal::JanelaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JanelaPrincipal)
{
    ui->setupUi(this);
}

JanelaPrincipal::~JanelaPrincipal(){
    delete ui;
}



void JanelaPrincipal::on_actionCadastro_triggered(){
  /*
    JanelaCadastroClientes *janelaCadastrosClientes = new JanelaCadastroClientes();
    //janelaCadastrosClientes.exec();

    QScrollArea scrollArea;
    scrollArea.setWidget(janelaCadastrosClientes);
    scrollArea.viewport()->setAutoFillBackground(true);
   // scrollArea.setWindowTitle(QObject::tr("Icon Editor"));
    //scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
   // scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea.show();

    janelaCadastrosClientes->exec();
    */
    ControladorCliente CC = ControladorCliente();
}

void JanelaPrincipal::on_actionCadastro_2_triggered(){
    ControladorServico *CS = new ControladorServico();
}
