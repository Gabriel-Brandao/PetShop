#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include "visao.h"

using namespace std;

class Animal{

protected:
    int Sequencial;
    string nome;
    char sexo; // M|F
    int idade;
    float peso;

public:
    Animal(string nome, char sexo, int idade, float peso);
    virtual string getNome(); //possibilita instanciar a classe
    //virtual string getNome() = 0; //função virtual pura. Clasee abstrata(nao permite instanciamento, mas apontamento)
    char getSexo();
    int getIdade();
    float getPeso();
    int getSequencial();
    void setSequencial(int sequencial);

    Visao<string> *getVisao(Animal *animal);
    static string inserirAnimal(Animal *animal);
    static string alterarAnimal(Animal *animal);
    static string removerAnimal(int id);
    static int obtemSequencial();
    static Animal* buscarAnimal(int sequencial);
    static Animal* buscarAnimalSemCliente();
    static bool isAnimalVinculado(int sequencial);
    //~Animal();
};

class Cachorro : public Animal{
private:
    string raca;
    string pelagem;
    bool adestrado;
    bool castrado;
public:
    Cachorro(string raca, string pelagem, bool adestrado, bool castrado, string nome, char sexo, int idade, float peso);
    virtual string getNome();
    string getRaca();
    string getPelagem();
    bool isAdestrado();
    bool isCastrado();
    static string inserirCachorro(Cachorro *cachorro);
    static string alterarCachorro(Cachorro *cachorro, int id);

};

class Gato : public Animal{
private:
    string pelagem;
    bool castrado;
    string observacao;
public:
    Gato(string pelo, bool castrado, string observacao, string nome, char sexo, int idade, float peso);
    virtual string getNome();
    string getPelagem();
    bool isCastrado();
    string getObservacao();
    static string inserirGato(Gato *gato);
    static string alterarGato(Gato *gato, int id);
};

class Ave : public Animal{
private:
    bool dieta;
    bool gaiola;
    string penugem;
    string especie;
    float invergadura;
public:
    Ave(bool dieta, bool gaiola, string penugem, string especie, float invergadura, string nome, char sexo, int idade, float peso);
    virtual string getNome();
    bool isDieta();
    bool isGaiola();
    string getPenugem();
    string getEspecie();
    float getInvergadura();
    static string inserirAve(Ave *ave);
    static string alterarAve(Ave *ave, int id);
};

class Tartaruga : public Animal{
private:
    bool dieta;
    string tipoDeAmbiente;
    float tamanhoDaCarapaca;
public:
    Tartaruga(bool dieta, string tipoDeAmbiente, float tamanhoDaCarapaca, string nome, char sexo, int idade, float peso);
    virtual string getNome();
    bool isDieta();
    string getTipoDeAmbiente();
    float getTamanhoDaCarapaca();
    static string inserirTartaruga(Tartaruga *tartaruga);
    static string alterarTartaruga(Tartaruga *tartaruga, int id);
};

class Outro : public Animal{
private:
    string familia;
public:
    Outro (string familia, string nome, char sexo, int idade, float peso);
    virtual string getNome();
    string getFamilia();
    static string inserirOutro(Outro *outro);
    static string alterarOutro(Outro *outro, int id);
};


#endif // ANIMAL_H
