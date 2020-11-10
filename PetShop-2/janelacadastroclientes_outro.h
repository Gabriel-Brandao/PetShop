#ifndef JANELACADASTROCLIENTES_OUTRO_H
#define JANELACADASTROCLIENTES_OUTRO_H

#include <QDialog>
#include "animal.h"

namespace Ui {
class JanelaCadastroClientes_Outro;
}

class JanelaCadastroClientes_Outro : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes_Outro(QWidget *parent = nullptr,  Animal *dados=nullptr, bool consulta=false);
    ~JanelaCadastroClientes_Outro();
    void consultarOutro();

private:
    Ui::JanelaCadastroClientes_Outro *ui;
};

#endif // JANELACADASTROCLIENTES_OUTRO_H
