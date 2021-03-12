# BCC-Projeto-POO

O presente relatório tem como motivo de sua produção a apresentação do processo
de desenvolvimento de um projeto prático para a disciplina de Programação Orientada a
Objetos I do curso de Bacharelado em Ciências da Computação da turma de ingresso em
\2020. Esse projeto executado ao longo do decorrer da disciplina citada tem como tema o
desenvolvimento de um simulador físico simples.

- Docente Responsável: Eder Augusto Penharbel 

## Breve Resumo
O presente trabalho objetiva a apresentação do projeto desenvolvido para a disciplina de Programação Orientada a Objetos I, onde o tema definido para abordagem é simulação física 2D. Através de pesquisas a cerca de aspectos de programação como Orientação a Objetos e linguagem C++, juntamente do estudo de diversos aspectos matemáticos e físicos, é possível construir a simulação de um sistema elástico onde aplicam-se conhecimentos como integração para movimentação de um corpo físico a partir de uma função de aceleração conhecida, conservação de movimento e reflexão especular para cálculo de colisões. O desenvolvimento do projeto consiste na divisão desse em três pacotes, onde cada um é responsável por uma funcionalidade do sistema como um todo. Os pacotes podem ser brevemente separados em Base, Interface e Arquivo onde têm-se respectivamente componentes para representação e estruturação da base matemática, abstração e criação de uma interface gráfica e por fim, persistência de dados. Além da implementação desses pacotes obtêm-se como resultado final do projeto uma série de testes dessas componentes, bem como uma simulação final correlacionando a teoria matemática e física à programação desenvolvida. 

## Ferramentas Utilizadas

Para o desenvolvimento do trabalho não foi necessário o uso de ferramentas consi-
deradas complexas, sendo que as necessidades do trabalho estão intimamente relacionadas
ao ambiente acadêmico de um curso de Ciências da Computação. Logo em sequência é
possível observar uma breve lista das ferramentas e tecnologias empregadas ao longo do
processo de desenvolvimento do trabalho.

- Linguagem C++: Linguagem adotada pelo docente responsável pela disciplina
para o desenvolvimento das atividades e do projeto. C++ É uma linguagem muito
interessante de trabalhar uma vez que pode ser compreendida como um superconjunto
da linguagem C onde têm-se recursos como alocação de memória dinâmica herdada
do C junto de recursos da Orientação a Objetos adicionados pelas implementações
C++;

- Compilador g++: Compilador padrão da distribuição Linux Ubuntu 20.04 utilizada
ao longo do desenvolvimento do trabalho. A título de especificação, o projeto foi
compilado usando-se da versão C++14;

- Biblioteca SDL: É uma biblioteca escrita em C que funciona nativamente em C++ e
foi usada para proporcionar acesso de baixo nível a hardware de vídeo, som, teclado,
mouse etc. A título de especificação, o projeto faz uso da versão 2.0.10;

- Doxygen: É uma ferramenta que permite a escrita de comentários no código C++
que futuramente podem ser compilados e gerar uma documentação para o projeto.
A título de especificação, o projeto faz uso da versão 1.8.17;

- Dia: É um software de diagramação simples que foi utilizado para a modelagem de
diagramas de classe para o projeto.

- Geogebra: É um software de interface gráfica que implementa recursos matemáticos e
permite a simulação de certos cálculos. Foi usado ao longo do projeto para modelagem
de situações necessárias de implementação no projeto com grande rigor matemático,
como as colisões;

## Objetivos
Os objetivos do trabalho podem ser divididos em dois tipos, sendo eles objetivos
gerais e objetivos específicos. Logo abaixo é possível conferir os objetivos elencados para o
trabalho de desenvolvimento do simulador físico, bem como um breve detalhamento de
cada um desses objetivos.

### Objetivos Gerais
- Aplicar conceitos de orientação a objetos no desenvolvimento de uma aplicação
gráfica utilizando C++ e SDL2;

- Apresentar um projeto prático para fins avaliativos na disciplina de Programação
Orientada a Objetos I do curso de Bacharelado em Ciências da Computação ofertado
pelo Instituto Federal Catarinense Campus Blumenau;

- Aprimorar os conhecimentos em programação, orientação a objetos, linguagem C++,
SDL2 e conteúdos da matemática e da física.Introdução
14

### Objetivos Específicos
- Construir um projeto de simulação computacional simples aplicando conhecimen-
tos matemáticos e físicos como integração numérica, conservação de movimento e
transformações geométricas;

- Dividir o projeto em componentes/pacotes separando a programação dos aspectos
matemáticos/físicos da simulação, da implementação dos recursos de interface para
o usuário para que esses possam ser reutilizados;

- Implementar uma camada simples de abstração a biblioteca SDL2;

- Apresentar documentação e modelagem simples do sistema para auxiliar o seu uso
compartilhado, ou possível reaproveitamento de código;

## Estrutura do Trabalho
- docs: Documentação do Trabalho gerado pelo Doxygen + Diagrama de Classes
- src: Pacotes com as implementações das classes do sistema + Testes dos códigos
- extras: Aspectos extras do projeto para quem possuir curiosidade
- run: Simulação Final integrando todos os aspectos do Trabalho

## Possibilidade de Trabalhos Futuros
Devido ao fato introdutório da disciplina, bem como a restrição dessa em um
tempo delimitado, existem diversos aspectos do trabalho que possuem potencial de serem
desenvolvidos e possivelmente resultarem em versões novas do projeto, bem como trabalhos
próprios inteiramente novos. Nessa seção estão elencados alguns dos pontos julgados
mais interessantes pelo o autor que podem ser abordados em momentos futuros e que
não referem-se a simples correções e otimizações do projeto atual, mas sim adição de
funcionalidades.

- Cálculo de colisão múltipla simultaneamente: Conforme fora visto em seções anterio-
res, o cálculo de colisão é efetuado entre 2 objetos por vez. Todavia existem casos
em que um objeto colide com mais de um único objeto ao mesmo tempo. Nesse caso
seria necessária, por exemplo, a modelagem de um sistemas de equações capaz de
resolver essas diversas colisões de maneira correta;

- Simulação com Objetos em formatos diferentes: Os Objetos da simulação ficaram
restritos ao formato de circunferência, todavia é interessante permitir simulações com
outras formas geométricas como triângulos e retângulos, e inclusive entre Objetos de
formatos diferentes. Nesse caso seria necessário, por exemplo, modificar a colisão e
incluir efeitos como rotação de figuras;

- Ajuste do tempo da simulação em conformidade ao tempo real: Conforme fora
citado anteriormente, existia uma ideia de fazer com que o tempo de simulação
correspondesse ao tempo real. Para isso seria necessário a modificação e manipulação
do tempo de processamento das instruções do simulador;

- Expansão dos conceitos físicos do simulador: Além de usar os conceitos apresentados e
detalhados na seção A Teoria: Matemática e Física Envolvida, seria possível trabalhar
com aspectos físicos como forças (de maneira mas explícita), sistemas inelásticos,
corpos com velocidade angular, corpos com carga elétrica, campo elétrico e magnético
etc.

- Expansão dos conceitos matemáticos do simulador: Além dos próprios conceitos
físicos, muita exploração matemática poderia ser efetuada como trabalhar com
coordenadas polares, descrição de elementos do sistema através de matrizes (de forma
mais complexa), exploração de outros métodos de integração numérica, exploração
de conceitos vetoriais etc.

- Simulação no espaço: Conforme pode-se observar todas as simulações são realizadas
no plano. Entretanto uma das possibilidades de aprofundamento do trabalho é
desenvolver uma simulação com características similares, mas que ocorre no espaço
3D. Nesse caso seria necessária toda uma reformulação do código tanto para a base
matemática, como para os elementos de interface;

- Criação de uma interface interativa com o usuário: A simulação final criada consiste
em um ambiente pré-configurado pelo autor do projeto. Para alterar a simulação é
necessário modificar diretamente componentes dos códigos escritos. Todavia uma
possibilidade seria criar uma interface interativa onde um usuário poderia informar
valores para configurar certos elementos do código, sendo possível assim a criação
interativa e simples de diversas simulações.
