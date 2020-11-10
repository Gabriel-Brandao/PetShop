#ifndef JANELACADASTROCLIENTES_GATO_H
#define JANELACADASTROCLIENTES_GATO_H

#include <QDialog>
#include "animal.h"

namespace Ui {
class JanelaCadastroClientes_Gato;
}

class JanelaCadastroClientes_Gato : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes_Gato(QWidget *parent = nullptr,  Animal *dados=nullptr, bool consulta=false);
    ~JanelaCadastroClientes_Gato();
    void consultarGato(string pelagem, bool castrado, string observacao);

private slots:
    void on_pb_gatoInserir_clicked();

    void on_pb_gatoAlterar_toggled(bool checked);

    void on_pb_gatoAlterar_clicked();

private:
    Ui::JanelaCadastroClientes_Gato *ui;
};

#endif // JANELACADASTROCLIENTES_GATO_H
