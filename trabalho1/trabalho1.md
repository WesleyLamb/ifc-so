# História dos Sistemas Operacionais

## Aluno
Wesley Ricardo Lamb

## 1943 - 1954: Primeiros computadores (Fase 0)
Computadores gigantes. Não possuíam SO ou possuíam um SO muito simples chamados de Monitores, onde o seus propósitos eram chamar o programa do usuário, registrar alguns dados sobre o uso, liberar o hardware após o uso e linkar algumas bibliotecas ao programa do usuário.

__Na Universidade de Cambridge, na Inglaterra, o EDSAC era utilizado por matemáticos a fim de resolver alguns problemas matemáticos mais complexos. Como havia uma fila de programas a serem executados e a necessidade de analisar o fluxo do programa, se viu a necessidade de criar um programa para trabalhar nestas necessidades. Foi assim que surgiram os programas Monitores__[1][2]

### Principais computadores
- ENIAC;
- EDVAC;
- EDSAC (Utilizava programas Monitores).

## 1955 - 1970: Primeiros Sistemas Operacionais (Fase 1)

Nos primeiros anos, o modo de trabalho era o seguinte:
- Um comitê era montado onde um matemático explicava o seu problema;
- O comitê analisava o caso e decidia quais funções seriam usadas no programa;
- Um programador, baseado nas decisões do comitê, escrevia um código em uma linguagem simbólica;
- Uma operadora datilografava o programa em uma fita perfurada;
- __Quando seria utilizada uma função da biblioteca de funções, a operadora pegava uma fita com o programa já perfurado e a passava em uma máquina copiadora que copiava o código pronto e o perfurava no programa;__
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

## 1970: Sistemas Operacionais de tempo compartilhado (Fase 2)

Com os avanços tecnológicos que aumentaram a velocidade dos computadores da época, começou-se a mudar o pensamento de que o computador só deveria fazer uma tarefa por vez. Surgindo assim o conceito de tempo compartilhado.




# Referências

1. [Wikipedia: History of operating systems](https://en.wikipedia.org/wiki/History_of_operating_systems)
2. [University of Cambridge: The EDSAC Film](https://sms.cam.ac.uk/media/739532)
3. [Milosh's blog: Robert L. Patrick: Operating Systems at Conception](https://millosh.wordpress.com/2008/12/16/robert-l-patrick-operating-systems-at-conception/)