#include "controladorcliente.h"
#include "janelacadastroclientes.h"
#include "cliente.h"

#include   <iostream>

using namespace std;

ControladorCliente::ControladorCliente(){

    JanelaCadastroClientes *janelaCadastroClientes = new JanelaCadastroClientes();
    janelaCadastroClientes->setModal(true);
    janelaCadastroClientes->setGeometry(0, 0, 551, 1000);
    //JanelaCadastroClientes janelaCadastroClientes;
        QScrollArea scrollArea;
        scrollArea.setWidget(janelaCadastroClientes);
        scrollArea.viewport()->setAutoFillBackground(true);
        scrollArea.setWindowTitle(QObject::tr("Cliente"));
        //scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
       // scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea.show();
    //    janelaCadastroClientes.exec();


    janelaCadastroClientes->exec();
}

string ControladorCliente::inserirCliente(Cliente *cliente){

    Cliente *cliente1 = Cliente::buscarCliente(cliente->getCpf());

    if (cliente1 == nullptr)
        return Cliente::inserirCliente (cliente);
     else
        return "CPF de cliente já cadastrado";

}

string ControladorCliente::alterarCliente(Cliente *cliente){

    Cliente *cliente1 = Cliente::buscarCliente(cliente->getCpf());

    if(cliente1 != nullptr)
        return Cliente::alterarCliente(cliente);
    else
        return "CPF do cliente não está cadastrado";
}

string ControladorCliente::removerCliente(string cpf){

    Cliente *cliente1 = Cliente::buscarCliente(cpf);

    if(cliente1 != nullptr)
        return Cliente::removerCliente(cpf);
    else
        return "CPF do cliente não está cadastrado";
}
