#ifndef JANELACADASTROSERVICOS_H
#define JANELACADASTROSERVICOS_H

#include <QDialog>
#include "servico.h"

namespace Ui {
class JanelaCadastroServicos;
}

class JanelaCadastroServicos : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroServicos(QWidget *parent = nullptr);
    ~JanelaCadastroServicos();
    Servico *obtemDadosServico();
    int converterParaInt(string str);
    float converterParaFloat (string str);
    void atualizaComboBoxClientes(int index, QString sql);
    void atualizaComboBoxServicos(int index, QString sql);
    Cliente *getComboBoxClientes();

private slots:
    void on_pb_limparServico_clicked();

    void on_pb_inserirServico_clicked();

    void on_cb_retorno_toggled(bool checked);

    void on_pb_consultarServico_toggled(bool checked);

private:
    Ui::JanelaCadastroServicos *ui;
};

#endif // JANELACADASTROSERVICOS_H
