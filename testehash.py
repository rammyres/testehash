#!/usr/local/bin/python
# coding: utf8


import hashlib #Funçoes criptograficas do python
import random #Criaçao de numeros pseudoaleatorios
import sys #Permite usar a interface com o sistema para ler as linhas de comandos

from argparse import ArgumentParser
#Permite usar o processador de argumentos para geraçao da ajuda tratamento automatizado de argumentos da linha de comando

"""
A funçao abaixo cria o objeto criptografico strout, com algoritmo sha256
A mensagem recebia como parametro e convertida em string (mesmo que ja seja)
E retornado o hash tratado como hexadecimais de tamanho duplo (hexdigest) 
"""
def digest(mensagem):
    strout = hashlib.sha256()
    strout.update(str(mensagem))
    return strout.hexdigest()


"""
A funçao gera n numeros aleatorios e seus hashs, usando a funçao digest acima
Os numeros gerados sao inteiros de 24 bits (ate 8 digitos), formatados com zeros 
iniciais (08d)
"""
def _imp_int(n):
    i = 0
    while i < n:
        x = random.getrandbits(24)
        print('| Inteiro: {0:08d} | Hash: {1}'.format(x, digest(x)))
        i += 1

"""
A funçao gera o hahs da string recebida. 
O condicional e meramente estetico, permitindo que strings muito extensas sejam impressas numa linha e seu hash em ou-
tra. 
"""
def _imp_str(s):
    if len(s)<16:
        print('| String: {0} | Hash: {1}'.format(s, digest(s)))
    else:
        print('| String: {0} \n| Hash: {1}'.format(s, digest(s)))


#Main
"""
O processador de argumentos e primeiro criado e as 3 funçoes que criei na versao original em java e implementei na 
versao em C
As funçoes possuem arguumentos compostos (nargs = '+') podem receber varias strings na linha de comando sem 
a necessidade de tratamentos extras no codigo 
"""
parser = ArgumentParser(description="Simula a geração de hashs a partir de inteiros aleatórios ou strings")
parser.add_argument("-n", help="O programa gerará X números aleatórios e seus respectivos hashes", type=int,
                    metavar='X', dest='X')
parser.add_argument("-s", help="O programa apresentará os hashs das N strings apresentada", type=str,
                    metavar='String1, String2, ... StringN', nargs='+')
parser.add_argument("-sl", help="O programa unirá todas as strings apresentadas e criará um hash único", type=str,
                    metavar='S', nargs='+')
parser.parse_args() #processa os argumentos

"""
sys.argv e uma lista, que funciona de forma similar aos arrays argv do java e C, com a facilidade da busca automatica
"""
if ("-n" in sys.argv):
    _imp_int(int(sys.argv[sys.argv.index("-n") + 1]))
if "-s" in sys.argv:
    for i in range(sys.argv.index("-s") + 1, len(sys.argv)):
        _imp_str(sys.argv[i])
""" Nao ha mecanismo similar a stringbuilders em python. Pra contornar essa situaçao, criei uma lista chamada buff
    que anexa todas as strings passadas na linha de comando e que depois e unida (''.join). A string resultante e
    entao encripada usando a funçao _imp_str."""
if "-sl" in sys.argv:
    buff = []
    for i in range(sys.argv.index("-sl") + 1, len(sys.argv)):
        if len(buff) == 0:
            buff.append(sys.argv[i])
        else:
            buff.append(" ")
            buff.append(sys.argv[i])
    _imp_str(''.join(buff))