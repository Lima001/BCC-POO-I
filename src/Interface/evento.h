#ifndef EVENTO_H
#define EVENTO_H

#include <iostream>

// Definição dos tipos de eventos aceitos pelo Sistema
/*
    Segue-se a seguinte interpretação:

    QUIT - Evento de saída. Um exemplo é o fechamento da Janela Gráfica
    KEYDOWN - Pressionamento de uma tecla
    KEYUP - Despressionamento de uma tecla
    UNDEFINED - Evento não interpretado e definido pelo Sistema
    NONE - Representa a ausência de eventos. Importante para controle de Eventos - Considerado Estado Padrão
*/
enum TipoEvento{
    QUIT,
    KEYDOWN,
    KEYUP,
    UNDEFINED,
    NONE
};

// Definição dos atividadores de eventos aceitos pelo sistema
/*
    Segue-se a seguinte interpretação:

    T_NONE - Nenhum ativador - Gera um TipoEvento NONE - Considerado Estado Padrão
    T_UNDEFINED - Ativador indefinido - Gera um TipoEvento UNDEFINED
    T_CLOSE -  Fechamento da Janela Gráfica - Gera um TipoEvento QUIT
    T_KQ - Tecla "Q" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KP - Tecla "P" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KW - Tecla "W" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KS - Tecla "S" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KA - Tecla "A" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KD - Tecla "D" do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KLEFT - Tecla seta para esquerda do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KDOWN - Tecla seta para baixo do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KRIGHT - Tecla seta para direita do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
    T_KUP - Tecla seta para cima do teclado - Pode gerar os TipoEvento de KEYDOWN e KEYUP
*/
enum Trigger{
    T_NONE,
    T_UNDEFINED,
    T_CLOSE,
    T_KQ,
    T_KP,
    T_KW,
    T_KS,
    T_KA,
    T_KD,
    T_KLEFT,
    T_KDOWN,
    T_KRIGHT,
    T_KUP
};

/*!
    \file evento.h
    \class Evento
    \author Gabriel Eduardo Lima
    \date Última alteração: 28/02/2021
    \brief Classe Responsável pela representação de um evento
           único capaz de ser processado por um objeto
           do tipo \ref GerenciadorEvento
*/

class Evento{
    public:

        TipoEvento tipo_evento;             //!< Define o tipo do evento gerado. Para ver os tipos permitidos olhe o arquivo da Classe
        Trigger trigger;                    //!< Define quem gerou o evento. Para ver os ativadores permitidos olhe o arquivo da Classe


        //! Construtor Default
        /*!
            Cria um objeto do tipo evento conforme descrito
            pelos parâmetros informados.

            \param te inicializa o atributo \ref tipo_evento
            \param tr inicializa o atributo \ref trigger
        */
        Evento(TipoEvento te, Trigger tr):
            tipo_evento(tipo_evento),
            trigger(tr){    
        };
        
        //! Destrutor da Classe
        ~Evento(){}

        // Sobrecarga de Operadores

        //! Sobrecarga do Insertion Operator para Saída de Dados
        /*!
            \return string no formato: "(a,b)" onde têm-se:
                    a: valor do tipo de evento; 
                    b: valor do ativador do evento
        */
        friend std::ostream& operator<< (std::ostream &out, const Evento &evento){
            out << "(" << evento.tipo_evento << ", " << evento.trigger << ")";
            return out;
        };
};

#endif