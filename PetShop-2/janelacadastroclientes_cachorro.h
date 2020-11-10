#ifndef JANELACADASTROCLIENTES_CACHORRO_H
#define JANELACADASTROCLIENTES_CACHORRO_H

#include <QDialog>
#include "animal.h"

namespace Ui {
class JanelaCadastroClientes_Cachorro;
}

class JanelaCadastroClientes_Cachorro : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaCadastroClientes_Cachorro(QWidget *parent = nullptr, Animal *dados=nullptr, bool consulta=false);
    ~JanelaCadastroClientes_Cachorro();
    void consultarCachorro(string raca, string pelagem, bool adestrado, bool castrado);

private slots:
    void on_pb_cachorroInserir_clicked();

    void on_pb_cachorroAlterar_toggled(bool checked);

    void on_pb_cachorroAlterar_clicked();

private:
    Ui::JanelaCadastroClientes_Cachorro *ui;
};

#endif // JANELACADASTROCLIENTES_CACHORRO_H
