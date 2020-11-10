#ifndef JANELACADASTROCLIENTES_H
#define JANELACADASTROCLIENTES_H

#include "animal.h"
#include "cliente.h"
#include "endereco.h"
#include <string>
#include <QDialog>

namespace Ui {
class JanelaCadastroClientes;
}

class JanelaCadastroClientes : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes(QWidget *parent = nullptr);
    ~JanelaCadastroClientes();
    Animal *obtemDadosAnimal();
    Cliente *obtemDadosCliente();
    int converterParaInt(string str);
    float converterParaFloat (string str);
    int getEstadoCliente(string estado);

    //static Animal *animal;
    //static void limpaAnimal();
    static string getNome();
    static float getInvergadura();
    static string getAnimal();
    static int obtemSequencialAni(string cpf);
    void atualizaComboBoxAnimais(int index, QString sql);
    void atualizaComboBoxClientes(int index, QString sql);
    Animal *getComboBoxAnimais();
    Cliente *getComboBoxClientes();
    void setCamposDoCliente(Animal *animal);
    void setCamposDoAnimal(Cliente *cliente);

private slots:

    void on_pb_ave_clicked();

    void on_pb_tartaruga_clicked();

    void on_pb_cachorro_clicked();

    void on_pb_gato_clicked();

    void on_pb_outroAnimal_clicked();

    void on_pb_limparCliente_clicked();

    void on_pb_inserirCliente_clicked();

    void on_pb_consultarCliente_clicked();

    void on_pb_consultarCliente_toggled(bool checked);

    void on_pb_alterarCliente_clicked();

    void on_pb_removerCliente_clicked();

private:

    Ui::JanelaCadastroClientes *ui;
};



#endif // JANELACADASTROCLIENTES_H
