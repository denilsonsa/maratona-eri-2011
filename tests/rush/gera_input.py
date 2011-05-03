# -*- coding: utf-8 -*-

from math import log
from random import randint, random

NUM_CASES = 50

MAX_P = 1000  # funcionarios == fluxo maximo
MAX_N = 100  # nos do grafo
MAX_W = 10  # capacidade maxima de cada aresta

def gera():
	N = randint(2, MAX_N)  # um grafo interessante precisa de, no minimo, 2 nós
	P = randint(1, min(MAX_P, 2*MAX_N))  # range escolhido empiricamente para
	                                     # ter uma boa distribuicao de respostas
	p_sink = 0.1  # probabilidade de um nó ser um bairro de interesse.
	              # precisamos disso para garantir que eles vão existir!
				  # o valor foi escolhido empiricamente para obter uma boa
				  # distribuicao de respostas.

	# seja G(n, p) um grafo aleatório de n nós onde cada aresta tem
	# probabilidade p de existir.  segundo o modelo de Erdos-Renyi[1], se
	# p > (1+epsilon) * ln n / n entao o grafo é almost surely connected.
	#
	# [1] http://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model

	# abaixo vamos tentar escolher p aleatoriamente no range [min_p, 1) onde
	# min_p atende à propriedade acima descrita
	min_p = log(N) / N
	p = min_p + random() / (1 - min_p)  # comprime [0, 1) para [0, min_p) e
	                                    # desloca de min_p obtendo [min_p, 1)

	arestas = []
	for i in xrange(1, N+1):
		# sorteia se 'i' será um bairro de interesse
		if random() < p_sink:
			# o nó 'i' foi eleito. portanto, nenhuma aresta sai dele.
			continue

		for j in xrange(1, N+1):
			if i == j:
				continue

			# testa se a aresta (i, j) vai existir
			if random() < p:
				arestas.append( (i, j) )

	# imprime o caso de teste
	M = len(arestas)
	print P, N, M
	for orig, dest in arestas:
		vias = randint(1, MAX_W)  # vias == capacidade da aresta
		print orig, dest, vias


if __name__ == '__main__':
	for i in xrange(NUM_CASES):
		gera()
	print 0, 0, 0  # fim de input
