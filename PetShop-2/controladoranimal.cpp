#include "controladoranimal.h"


#include "janelacadastroclientes_ave.h"
#include "janelacadastroclientes_cachorro.h"
#include "janelacadastroclientes_gato.h"
#include "janelacadastroclientes_tartaruga.h"
#include "janelacadastroclientes_outro.h"

#include   <iostream>

using namespace std;


ControladorAnimal::ControladorAnimal(QWidget *parent, Animal *dadosAnimal, string qualAnimal, bool consulta){
    if(!qualAnimal.compare("Ave")){
        JanelaCadastroClientes_Ave janelaCadastroClientes_Ave(parent, dadosAnimal, consulta);
        janelaCadastroClientes_Ave.exec();
    }
     else
        if(!qualAnimal.compare("Gato")){
            JanelaCadastroClientes_Gato janelaCadastroClientes_Gato(parent, dadosAnimal, consulta);
            janelaCadastroClientes_Gato.exec();
        }
         else
            if(!qualAnimal.compare("Cachorro")){
                JanelaCadastroClientes_Cachorro janelaCadastroClientes_Cachorro(parent, dadosAnimal, consulta);
                janelaCadastroClientes_Cachorro.exec();
            }
             else
                if(!qualAnimal.compare("Tartaruga")){
                    JanelaCadastroClientes_Tartaruga janelaCadastroClientes_Tartaruga(parent, dadosAnimal, consulta);
                    janelaCadastroClientes_Tartaruga.exec();
                }
                else
                   if(!qualAnimal.compare("Outro")){
                       JanelaCadastroClientes_Outro janelaCadastroClientes_Outro(parent, dadosAnimal, consulta);
                       janelaCadastroClientes_Outro.exec();
                   }
}

string ControladorAnimal::inserirAnimal(Animal *animal){
                     //Retorna o ultimo animal cadastrado sem cliente
    Animal *animal1 = Animal::buscarAnimalSemCliente();//Animal::buscarAnimal(animal->obtemSequencial());

    if (animal1 == nullptr)
        return Animal::inserirAnimal(animal);
     else
        return "Ja existe um animal cadastrado sem vinculo com cliente, Vincule a algum cliente ou exclua algum animal";
}

string ControladorAnimal::alterarAnimal(Animal *animal){
    return Animal::alterarAnimal(animal);
}

string ControladorAnimal::removerAnimal(int id){
    Animal *animal1 = Animal::buscarAnimal(id);

    if(animal1 != nullptr)
       return Animal::removerAnimal(id);
    else
        return "Animal não encontrado";

}
