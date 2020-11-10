#ifndef CONTROLADORANIMAL_H
#define CONTROLADORANIMAL_H

#include "animal.h"
#include <janelacadastroclientes_ave.h>
#include <janelacadastroclientes_gato.h>
#include <janelacadastroclientes_cachorro.h>
#include <janelacadastroclientes_tartaruga.h>
#include <janelacadastroclientes_outro.h>

#include <QWidget>

class ControladorAnimal
{
public:
    ControladorAnimal(QWidget *parent, Animal *animal, string qualAnimal, bool consulta);
    static string inserirAnimal(Animal *animal);
    static string alterarAnimal(Animal *animal);
    static string removerAnimal(int id);
};

#endif // CONTROLADORANIMAL_H
