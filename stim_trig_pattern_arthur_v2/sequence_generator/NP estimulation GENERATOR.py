import numpy as np
import matplotlib.pyplot as plt


fArqSaida= input('Qual o arquivo de saída: ')
file_object1 = open("{}.txt".format(fArqSaida), "w")
file_object2 = open("{}_cutpaste.txt".format(fArqSaida), "w")

# Parâmetros
#tamSec = 10000  # Defina a duração da estimulação em segundos
tamSec=int(input('Defina a duração da estimulação em segundos: ')) 
Nestimulos = int(input('Qual o número de estímulos por segundo: ')) # Definido como 4 no experimento do VICA
intervaloMinimo = 20  # Intervalo mínimo entre pulsos em ms
intervaloMinimo=int(input('Qual o intervalo mínimo entre pulsos em ms: '))

ts = np.zeros(tamSec * Nestimulos)  # Vetor de time stamps dos pulsos

for seg in range(tamSec):  # Loop para gerar a NPS a cada segundo
    ini = 0
    fim = 1000-((Nestimulos-1)*intervaloMinimo)

    for i in range(Nestimulos):  # Este loop gera os timestamps de Nestimulos pulsos a cada segundo - em ms
        aux = np.random.rand(1)
        auxNorm = aux * (fim - ini) + ini  # Escalonamento da randomização uniforme para o intervalo ini-fim

        if auxNorm - ini < intervaloMinimo:  # Garante intervalo mínimo de 20 ms
            auxNorm = ini + intervaloMinimo

        ts[i + seg * Nestimulos] = auxNorm + seg * 1000  # Atribui o time stamp respeitando o segundo atual

        # Uma linha só para debugar:
        # print(f'<i: {i} Seg: {seg}> Ini: {ini} Fim: {fim} TS: {ts[i + seg * Nestimulos]:.1f}')

        ini = auxNorm  # A cada segundo, o próximo pulso é sempre randomizado no intervalo entre o pulso anterior e o fim do segundo: é o que confere a característica de power law
        fim = fim + intervaloMinimo  # Fim começa em 940 e aumenta para 960, 980 e 1000 para garantir espaço para os Nestimulos pulsos, espaçados de 20 ms, ainda que o resultado de rand seja sempre 1

# Aqui é só para confirmar a correta distribuição dos pulsos
tsIPI = np.diff(ts)  # Cálculo dos intervalos entre pulsos
plt.hist(tsIPI, bins=100)  # Histograma de IPI - deve ser ajustado por y = 1/x
plt.title('IPI histogram')
plt.xlabel('Inter-pulse interval (ms)')
plt.ylabel('Count of occurrences')
plt.show()

for y in range(0,len(tsIPI)):
    file_object1.write(("{0},{1}\n").format(round(tsIPI[y]),round(ts[y])))
    file_object2.write(("{0},").format(round(tsIPI[y])))

file_object1.close
file_object2.close

print(f'Valor mínimo de IPI obtido (não pode ser menor que 20 ms): {np.min(tsIPI):.2f} ms')