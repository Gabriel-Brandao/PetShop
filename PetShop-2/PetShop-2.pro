QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    animal.cpp \
    bd.cpp \
    cliente.cpp \
    controladoranimal.cpp \
    controladorcliente.cpp \
    controladorservico.cpp \
    data.cpp \
    endereco.cpp \
    janelacadastroclientes.cpp \
    janelacadastroclientes_ave.cpp \
    janelacadastroclientes_cachorro.cpp \
    janelacadastroclientes_gato.cpp \
    janelacadastroclientes_outro.cpp \
    janelacadastroclientes_tartaruga.cpp \
    janelacadastroservicos.cpp \
    main.cpp \
    janelaprincipal.cpp \
    servico.cpp \
    visao.cpp

HEADERS += \
    animal.h \
    bd.h \
    cliente.h \
    controladoranimal.h \
    controladorcliente.h \
    controladorservico.h \
    data.h \
    endereco.h \
    janelacadastroclientes.h \
    janelacadastroclientes_ave.h \
    janelacadastroclientes_cachorro.h \
    janelacadastroclientes_gato.h \
    janelacadastroclientes_outro.h \
    janelacadastroclientes_tartaruga.h \
    janelacadastroservicos.h \
    janelaprincipal.h \
    servico.h \
    visao.h

FORMS += \
    janelacadastroclientes.ui \
    janelacadastroclientes_ave.ui \
    janelacadastroclientes_cachorro.ui \
    janelacadastroclientes_gato.ui \
    janelacadastroclientes_outro.ui \
    janelacadastroclientes_tartaruga.ui \
    janelacadastroservicos.ui \
    janelaprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
