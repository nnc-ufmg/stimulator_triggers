import numpy as np
import random
import matplotlib.pyplot as plt


def RunPossibilities(value):
    nspikes=0
    for i in range (0,Ntotal):
        if value&(2**i):
            nspikes+=1
    if nspikes==Mtotal:
        return True
    else:
        return False
    
def RunIntervalos(value):
    line=[]
    for i in range (0,Ntotal):
        if value&(2**i):
            line.append(Ntotal-i)
    return (line)
    
Ntotal=int(input('Qual o número total de BINs em uma WORD: ')) 
Mtotal=int(input('Qual o número de disparos em uma WORD: '))
binsTempoINTRAWord=int(input('Qual o tempo de cada BIN em milissegundos: '))
binsTempoINTERWord=int(input('Qual o tempo de tempo de espera INTER Words (milissegundos): '))
palavraFIXA=int(input('Qual o número que será usado para o cut/paste da palavra FIXA: '))
fArqSaida= input('Qual o arquivo de saída: ')
minhaLISTA=[]

'''
Em 10 BINs, 4 disparos, 15 ms por BIN, 850 ms de espera entre WORDs, a palavra FIXA é 543
existem 10 intervalos em 10bins, logo, 9 intervalos de 15ms, logo, 150ms de intervalo => 850+150=1000ms

'''

file_object1 = open("{}.txt".format(fArqSaida), "w")
file_object2 = open("{}_intervalos.txt".format(fArqSaida), "w")
file_object3 = open("{}_cutpaste.txt".format(fArqSaida), "w")
file_object4 = open("{}_cutpastePALAVRAFIXA.txt".format(fArqSaida), "w")

for x in range(0,2**10):
   if RunPossibilities(x):
        minhaLISTA.append(x)

leftoverFromLastWord=0
random.shuffle(minhaLISTA)

for x in minhaLISTA:
    line="{:010b}".format(x)
    print(line)
    file_object1.write(("{0},{0:0" + str(Ntotal) + "b}\n").format(x))
    #file_object1.write(("{0:0" + str(Ntotal) + "b}").format(x))
    #file_object1.write("\n")
    file_object3.write("{0},".format(x))
    file_object4.write("{0},".format(palavraFIXA))

    posicoes=RunIntervalos(x)
    posicoes.sort() #ordena a lista
    for y in range(0,len(posicoes)):
        if y==0:
            #file_object2.write("{},".format(binsTempoINTERWord+leftoverFromLastWord+binsTempoINTRAWord*(posicoes[y]-1)))
            #file_object2.write(("{0},{1:0" + str(Ntotal) + "b},{2}\n").format((binsTempoINTRAWord+binsTempoINTERWord+leftoverFromLastWord+binsTempoINTRAWord*(posicoes[y]-1)),x,(posicoes[y]-1)))
            file_object2.write(("{0},").format((binsTempoINTRAWord+binsTempoINTERWord+leftoverFromLastWord+binsTempoINTRAWord*(posicoes[y]-1))))
        else:
            #file_object2.write(("{0},{1:0" + str(Ntotal) + "b},{2}\n").format((binsTempoINTRAWord*(posicoes[y]-posicoes[y-1])),x,(posicoes[y]-1)))
            file_object2.write(("{0},").format((binsTempoINTRAWord*(posicoes[y]-posicoes[y-1]))))

    leftoverFromLastWord=binsTempoINTRAWord*(Ntotal-posicoes[len(posicoes)-1])
    #file_object2.write("{},".format(leftoverFromLastWord))

file_object1.close
file_object2.close
file_object3.close
file_object4.close

print (len(minhaLISTA))


#NSequencia=[]
#for m in range(0,Mtotal):
#    NSequencia.append([Ntotal-m,Mtotal-m])
#    print(f"{NSequencia[m][0]} to {NSequencia[m][1]}")
#count=0
''' 
count+=1
line="{:010b}".format(x)
print(line)
#file_object.write("{},".format(543))
file_object.write("{0},".format(x))
file_object.write(("{0:0" + str(Ntotal) + "b}").format(x))
file_object.write("\n")
#file_object.write("{}\n".format(line))
file_object2.write(RunIntervalos(x))
print(f"{x:b}")
'''