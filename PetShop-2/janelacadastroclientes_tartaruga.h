#ifndef JANELACADASTROCLIENTES_TARTARUGA_H
#define JANELACADASTROCLIENTES_TARTARUGA_H

#include <QDialog>
#include "animal.h"

namespace Ui {
class JanelaCadastroClientes_Tartaruga;
}

class JanelaCadastroClientes_Tartaruga : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes_Tartaruga(QWidget *parent = nullptr,  Animal *dados=nullptr, bool consulta=false);
    ~JanelaCadastroClientes_Tartaruga();
    void consultarTartaruga(bool dieta, string ambiente, float tamanhoCarapaca);


private slots:
    void on_Inserir_clicked();

    void on_pb_tartarugaAlterar_toggled(bool checked);

    void on_pb_tartarugaAlterar_clicked();

private:
    Ui::JanelaCadastroClientes_Tartaruga *ui;
};

#endif // JANELACADASTROCLIENTES_TARTARUGA_H
