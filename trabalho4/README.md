# Simulação do Crescimento Populacional Exponencial com Threads e Prevenção de Impasse

## Aluno
Wesley Ricardo Lamb

## Introdução

Trabalho realizado para a matéria de SO com o intuito de demonstrar Deadlocks (impasses) e os possíveis métodos de prevenção para o mesmo.
As condições para um impasse são as seguintes:
- Exclusão mútua: Recursos acessados com exclusão mútua, gerida por semáforos ou similares;
- Posse e espera: A tarefa tem um recurso e quer acessar outro;
- Não-preempção: A tarefa só libera os recursos quando quiser;
- Espera circular: A tarefa t1 quer um recurso retido por t2, que quer um recurso retido por t3, que quer um recurso retido por t1.

Ao evitar pelo menos uma das condições acima listadas, não ocorrerá impasses.

Neste exemplo, a solução proposta irá trabalhar diretamente na condição de Posse e espera, onde será implementado mais um semáforo que será utilizado para controlar a entrada na sessão crítica.

## Compilação

Para gerar o executável (apenas Linux), compile o arquivo main.c com o seguinte comando:

```bash
    gcc ./main.c -lpthread -lrt -lm -o ./main
```

Para habilitar a prevenção de impasse, descomente a linha 13 do arquivo `main.c`

## Análise

Os testes abaixo foram efetuados em uma máquina com 8GB de RAM e um i7-4710MQ 3.5GHz. Foram realizados 10 testes para cada linha da tabela abaixo

|Recursos|Ciclos|Threads|Tempo médio por thread|Tempo total|Deadlocks|
|:-:|:-:|:-:|:-:|:-:|:-:|
||