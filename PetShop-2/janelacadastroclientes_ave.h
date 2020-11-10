#ifndef JANELACADASTROCLIENTES_AVE_H
#define JANELACADASTROCLIENTES_AVE_H

#include <QDialog>
#include <string>

#include "animal.h"
using namespace std;

namespace Ui {
class JanelaCadastroClientes_Ave;
}

class JanelaCadastroClientes_Ave : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes_Ave(QWidget *parent = nullptr, Animal *dados=nullptr, bool consulta=false);
    ~JanelaCadastroClientes_Ave();
    void consultarAve(bool dieta, bool gaiola, string penugem, string especie, float invergadura);

private slots:
    void on_pb_aveInserir_clicked();

    void on_pb_aveAlterar_toggled(bool checked);

    void on_pb_aveAlterar_clicked();

private:
    Ui::JanelaCadastroClientes_Ave *ui;
};

#endif // JANELACADASTROCLIENTES_AVE_H
