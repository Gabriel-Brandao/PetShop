#ifndef CONTROLADORSERVICO_H
#define CONTROLADORSERVICO_H

#include "servico.h"

class ControladorServico
{
public:
    ControladorServico();
    static string inserirServico(Servico *servico);
};

#endif // CONTROLADORSERVICO_H
