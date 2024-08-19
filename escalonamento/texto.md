# FCFS (First Come First Served)
Primeiro a chegar sera o primeiro a ser processado

# RR (Round-Robin)
Fila de processos porém a variável 'quantum' determina quantos tempos cada processo tem para executar, quando o tempo acabar e o processo não for terminado ele sera suspenso e voltara para o final da fila

# SJF (Shortest Job First)
Executa o processo com o menor tempo até seu término, quase como uma modificação do FCFS

# SRTF (Shortest Remain Time First)
Junção do SJF com o PrioCom

# PrioCop (Priority Cooperative)
A fila é por prioridade, até que o processo termine
Melhor prioridade = Menor número (não se aplica a todos podendo ser o contrário)

# PrioCom (Priority Compreensive)
A fila é por prioridade com a fila podendo mudar todo ciclo