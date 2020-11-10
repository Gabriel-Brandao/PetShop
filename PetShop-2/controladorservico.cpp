#include "controladorservico.h"
#include "janelacadastroservicos.h"

#include<iostream>

using namespace std;

ControladorServico::ControladorServico(){
    JanelaCadastroServicos *janelaCadastroServicos = new JanelaCadastroServicos();
    janelaCadastroServicos->exec();
}

string ControladorServico::inserirServico(Servico *servico){

    vector<TipoDeServico> *listaDeServicos =  new vector<TipoDeServico>;
    listaDeServicos = servico->getTipoDeServico();
    int n = listaDeServicos->size();
    for(int i = 0; i < n; i++){
        cout << "controlador.cpp/inserirServico() " << listaDeServicos->back() << endl;
        listaDeServicos->pop_back();
    }

    Servico *servico1 = Servico::buscarServico(servico);

    if (servico1 == nullptr)
        return Servico::inserirServico(servico);
     else
        return "Esse mesmo serviço já foi cadastrado para esse cliente";
}
