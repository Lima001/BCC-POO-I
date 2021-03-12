# Implementação das Componentes do Sistema

Nesse local é possível encontrar todo o código desenvolvido para a
simulação física dividido em pacotes. Nos pacotes é possível encontrar a implementação das
classes do sistema, bem como alguns testes realizados sobre esses elementos.

## Ferramentas Utilizadas no Desenvolvimento

-- Linguagem C++: Linguagem adotada pelo docente responsável pela disciplina
para o desenvolvimento das atividades e do projeto. C++ É uma linguagem muito
interessante de trabalhar uma vez que pode ser compreendida como um superconjunto
da linguagem C onde têm-se recursos como alocação de memória dinâmica herdada
do C junto de recursos da Orientação a Objetos adicionados pelas implementações
C++;

-- Compilador g++: Compilador padrão da distribuição Linux Ubuntu 20.04 utilizado
ao longo do desenvolvimento do trabalho. A título de especificação, o projeto foi
compilado usando-se da versão C++14;

-- Biblioteca SDL: É uma biblioteca escrita em C que funciona nativamente em C++ e
foi usada para proporcionar acesso de baixo nível a hardware de vídeo, som, teclado,
mouse etc. A título de especificação, o projeto faz uso da versão 2.0.10;

-- Doxygen: É uma ferramenta que permite a escrita de comentários no código C++
que futuramente podem ser compilados e gerar uma documentação para o projeto.
A título de especificação, o projeto faz uso da versão 1.8.17;

## Divisão dos Pacotes
- Arquivo: Implementação da componente responsável pela Persistência de Dados simplificada do sistema.
- Base: Implementação das componentes responsáve por representar e permitir a manipulação dos elementos matemáticos e físicos do sistema.
- Interface: Implementação das componentes responsável por abstrair a biblbioteca SDL e permitir a criação de uma Interface Gráfica simples.
- Integração: Implementação de testes que integram maior parte das funcionalidades implementadas pelos outros pacotes.