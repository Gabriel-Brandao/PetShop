#ifndef CONTROLADORCLIENTE_H
#define CONTROLADORCLIENTE_H

#include <QScrollArea>
#include "cliente.h"

class ControladorCliente
{
public:
    ControladorCliente();
    static string inserirCliente(Cliente *cliente);
    static string alterarCliente(Cliente *cliente);
    static string removerCliente(string cpf);
};

#endif // CONTROLADORCLIENTE_H
