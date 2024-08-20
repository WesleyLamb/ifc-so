# História dos Sistemas Operacionais

## Aluno
Wesley Ricardo Lamb

# Linha do tempo

https://my.visme.co/view/vd6my93d-historia-dos-so-039-s

## 1943 - 1954: Primeiros computadores (Fase 0)
Computadores gigantes. Não possuíam SO ou possuíam um SO muito simples chamados de Monitores, onde o seus propósitos eram chamar o programa do usuário, registrar alguns dados sobre o uso, liberar o hardware após o uso e linkar algumas bibliotecas ao programa do usuário.

Na Universidade de Cambridge, na Inglaterra, o EDSAC era utilizado por matemáticos a fim de resolver alguns problemas matemáticos mais complexos. Como havia uma fila de programas a serem executados e a necessidade de analisar o fluxo do programa, se viu a necessidade de criar um programa para trabalhar nestas necessidades. Foi assim que surgiram os programas Monitores.[1][2]

### Principais computadores
- ENIAC;
- EDVAC;
- EDSAC (Utilizava programas Monitores).

## 1955 - 1961: Primeiros Sistemas Operacionais (Fase 1)

Nos primeiros anos, o modo de trabalho era o seguinte:
- Um comitê era montado onde um matemático explicava o seu problema;
- O comitê analisava o caso e decidia quais funções seriam usadas no programa;
- Um programador, baseado nas decisões do comitê, escrevia um código em uma linguagem simbólica;
- Uma operadora datilografava o programa em uma fita perfurada;
- Ao detectar que seria utilizada uma função da biblioteca de funções, a operadora adicionava mecanicamente uma cópia da fita com a função da biblioteca de funções, através de uma máquina que percorria a fita e perfurava;
- A operadora realizada o processo de datilografar 2x;
- Após perfurar as fitas, a operadora passava as duas fitas em uma máquina que verificava se as duas fitas estavam iguais. Caso não estivessem, significava que a operadora tinha cometido algum erro durante a datilografia;
- Finalizando o processo, a operadora adicionava o programa a uma fila de trabalhos (que era um tipo de varal);
- Um outro operador pegava uma das fitas da fila, fazia o computador executar o programa. Após a conclusão do programa, o operador retirava a fita e a saída digitada pelo computador e as colocava em uma uma outra fila de saída;
- A operadora que datilografou o programa, em conjunto com as saídas do computador analisava se o código havia sido executado com sucesso (Graças ao programa Monitor, havia um tipo de debug que listava todas as funções executadas, em ordem).

Um dos problemas era que, normalmente quem operava o computador era um outro programador e programadores eram escassos na época.

Com isso surgiu a ideia de um programa para orquestrar todos os periféricos, monitorar o programa, executar outro programa em sequência e gerar relatórios sobre a execução do programa, a fim de cobrança.

O primeiro SO documentado é o GM-NAA I/O para o IBM 704, criado no Laboratório de Pesquisas da General Motors, entre os anos de 1955 e 1956, por Robert L. Patrick (General Motors) e Owen Mock (North American Aviation). Sua função principal era de executar um novo programa após o programa anterior terminar. Era composto de rotinas compartilhadas com os programas para acessar os periféricos de entrada e saída.

![IBM 704](https://i.pinimg.com/736x/4e/12/27/4e1227c75c1e0a3d5298c8f7ae784244--retro-design-ibm.jpg)
IBM 704

Naquela época, os sistemas operacionais eram desenvolvidos para aquele modelo de computador apenas, então era comum que as próprias empresas criassem seus próprios sistemas operacionais.

### Principais SOs

- OS/360
- PCP
- MFT
- MVT
- DOS/360
- SCOPE
- MACE
- NOS

## 1962 - 1968: Sistemas Operacionais de tempo compartilhado (Fase 2)

Com os avanços tecnológicos que aumentaram a velocidade dos computadores da época, começou-se a mudar o pensamento de que o computador só deveria fazer uma tarefa por vez. Surgindo assim o conceito de tempo compartilhado (também chamado de multitarefa).

A definição de tempo compartilhado é quando um SO permite que multiplos programas sejam executados ao mesmo tempo, cada um destes processos ocupando uma fração do tempo do processador, a fim de evitar ociosidades no mesmo.

O primeiro sistema operacional de propósito geral que utilizada a ideia de tempo compartilhado foi o CTSS, desenvolvido no MIT no Projeto MAC entre 1961 e 1963, utilizando um mainframe IBM 704 que foi emprestado pela própria IBM para o MIT.[4]

### Principais SOs

- CTSS: Compatible Time-Sharing System (Sistema compatível com tempo compartilhado)
- DTSS

## 1969 - 1979: Precursores dos Sistemas Operacionais modernos (Fase 3)

Após o desenvolvimento do primeiro sistema operacional de tempo compartilhado, o CTSS, em 1969 a equipe de cientistas de IA do projeto MAC desenvolveram um novo sistema operacional com alguns conceitos novos. O recebeu o nome de MULTICS.
Os principais conceitos implementados no MULTICS foram[5]:
- Single-level store;
- Link dinâmico de rotinas;
- Hot swapping (Troca de componentes de hardware sem a necessidade de desligar a máquina);
- Sistema operacional em camadas;
- Sistema de arquivos em hierarquias.

Baseado no MULTICS, em 1971, na Bell Labs, Dennis Ritchie, Ken Thompson e outros desenvolvedores criaram o Unix. Com seu código fonte escrito majoritariamente em C, o Unix se tornou o primeiro sistema operacional portável, o que tornou possível que ele operasse em muitas outras plataformas.
As principais inovações do Unix foram[6][7]:
- Portabilidade;
- Multi-tarefa;
- Multi-usuário;
- Sistema de arquivos hierárquicos;
- Armazenamento das informações em texto plano;
- Comunicação interprocessos por arquivos;
- Utilização de pipes para trabalhar com diversos comandos em sequência, via terminal.

![Gráfico histórico do UNIX](https://upload.wikimedia.org/wikipedia/commons/thumb/7/77/Unix_history-simple.svg/1920px-Unix_history-simple.svg.png)
Gráfico histórico do UNIX

## 1980: SOs para computadores pessoais

Como todos os sistemas operacionais desenvolvidos até então foram criados para fins acadêmicos/profissionais, o mercado de sistemas operacionais para computadores pessoais em sua maioria não implementavam as tecnologias de multi-tarefa e multi-usuário que haviam sido criadas na década passada. Muitos dos softwares desenvolvidos na época assumiam controle da máquina durante seu uso.
As principais novidades para esta época foi o suporte a interfaces gráficas de usuárias, devido à redução no custo das telas.[1]

### Principais SOs
- CP/M-80
- MDOS/MIDAS
- MS-DOS
- PC-DOS

#### Com interface gráfica:
- Microsoft Windows
- Mac OS
- OS-9 Level II
- AmigaOS
- Atari TOS
- IBM OS/2

## 1990: Consolidação dos Sistemas Operacionais

Em 1990, a Psion, fabricante de dispositivos móveis, lançou um PDA (assistente pessoal digital) chamado Psion Series 3, que suportava aplicações escritas pelo usuário através de um sistema operacional chamado EPOC, que foi o sistema operacional para dispositivos móveis mais utilizado até 2010.[1]

Em 1991, um estudante de ciências da computação Finlandês posta em uma Usenet (um tipo de fórum), que está trabalhando em um SO baseado no MINIX para seu Intel 80386. Este sistema operacional ficou conhecido como Linux e é um dos principais SO's modernos.

Em meados dos anos 90, com a abertura da rede mundial de computadores, os sistemas operacionais começaram a adotar navegadores como parte das suas ferramentas essenciais.

# Referências

1. [Wikipedia: History of operating systems](https://en.wikipedia.org/wiki/History_of_operating_systems)
2. [University of Cambridge: The EDSAC Film](https://sms.cam.ac.uk/media/739532)
3. [Milosh's blog: Robert L. Patrick: Operating Systems at Conception](https://millosh.wordpress.com/2008/12/16/robert-l-patrick-operating-systems-at-conception/)
4. [Wikipedia: MIT Computer Science and Artificial Intelligence Laboratory](https://en.wikipedia.org/wiki/MIT_Computer_Science_and_Artificial_Intelligence_Laboratory#Project_MAC)
5. [Wikipedia: Multics](https://en.wikipedia.org/wiki/Multics)
6. [Wikipedia: Unix](https://en.wikipedia.org/wiki/Unix)
7. [YouTube: UNIX: Making Computers Easier To Use -- AT&T Archives film from 1982, Bell Laboratories](https://www.youtube.com/watch?v=XvDZLjaCJuw)