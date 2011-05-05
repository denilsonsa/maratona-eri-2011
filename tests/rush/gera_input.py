# -*- coding: utf-8 -*-

from math import log, sqrt
from random import randint, random, sample, shuffle

MAX_P = 1000  # funcionarios == fluxo maximo
MAX_N = 100  # nos do grafo
MAX_W = 10  # capacidade maxima de cada aresta

def gera_erdos_renyi():
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

def gera_permutado(P=None, N=None, M=None):
	N = N or randint(2, MAX_N)
	M = M or randint(N-1, N*(N-1))  # no minimo um DAG conexo
	P = P or randint(1, 3*N)

	# lista dos bairros de interesse
	bairros_interesse = sample(range(2, N+1), randint(1, max(1, N/10)))

	# cria todas as arestas possiveis e remove os loops.
	# isso é importante para evitar a geração de arestas repetidas!
	all_arestas = [(i, j) for i in xrange(1, N+1) for j in xrange(1, N+1)]
	for i in xrange(1, N+1):
		all_arestas.remove( (i, i) )

	# cria uma permutacao para os nós com o 1 na primeira posição
	tmp = range(2, N+1)
	shuffle(tmp)
	nos = [1] + tmp

	# inicializa lista das arestas deste test case
	arestas = []

	# para cada nó ``v``, escolhe aleatoriamente um nó ``u`` que venha antes
	# dele na permutação e cria a aresta ``(u, v)``.
	for i in xrange(1, N):
		orig = bairros_interesse[0]
		while orig in bairros_interesse:
			orig = randint(0, i - 1)
		aresta = (nos[orig], nos[i])
		arestas.append(aresta)
		all_arestas.remove(aresta)
		M -= 1
	
	# cria arestas até o limite que havíamos determinado
	while M > 0:
		idx = None
		while idx is None or all_arestas[idx][0] in bairros_interesse:
			if idx is not None:
				# remove do vetor pra evitar resortearmos
				all_arestas.pop(idx)
			if len(all_arestas) == 0:
				break
			idx = randint(0, len(all_arestas) - 1)
		if len(all_arestas) == 0:
			break
		arestas.append(all_arestas.pop(idx))
		M -= 1

	# imprime o caso de teste
	M = len(arestas)
	print P, N, M
	for orig, dest in arestas:
		vias = randint(1, MAX_W)  # vias == capacidade da aresta
		print orig, dest, vias

def gera_tripinha(N=None):
	N = N or randint(2, MAX_N)
	P = randint(1, 3*N)

	# cria uma permutacao para os nós com o 1 na primeira posição
	tmp = range(2, N+1)
	shuffle(tmp)
	nos = [1] + tmp

	# inicializa lista das arestas deste test case
	arestas = []

	# gera uma tripinha do nó anterior para o nó seguinte da lista
	for i in xrange(1, N):
		orig = nos[i-1]
		dest = nos[i]
		arestas.append( (orig, dest) )
	
	# imprime o caso de teste
	M = len(arestas)
	print P, N, M
	for orig, dest in arestas:
		vias = randint(1, MAX_W)  # vias == capacidade da aresta
		print orig, dest, vias

def gera_camadas(N=None):
	N = N or randint(2, MAX_N)
	P = randint(1, 3*N)

	# cria uma permutacao para os nós de 2 em diante
	nos = range(2, N+1)
	shuffle(nos)

	# inicializa lista das arestas deste test case
	arestas = []

	# inicializa camadas
	camada_anterior = None
	camada_atual = [1]

	# gera camadas
	while len(nos) > 0:
		qtd = min(len(nos), int(sqrt(N)))
		camada_anterior = camada_atual
		camada_atual = nos[:qtd]
		nos = nos[qtd:]
		arestas_na_camada = randint(qtd, 3*qtd)
		for i in xrange(arestas_na_camada):
			orig = camada_anterior[randint(0, len(camada_anterior) - 1)]
			dest = camada_atual[randint(0, len(camada_atual) - 1)]
			arestas.append( (orig, dest) )
	
	# faz um 'unique' na lista das arestas
	arestas = list(set(arestas))
	
	# imprime o caso de teste
	M = len(arestas)
	print P, N, M
	for orig, dest in arestas:
		vias = randint(1, MAX_W)  # vias == capacidade da aresta
		print orig, dest, vias


if __name__ == '__main__':
	# casos aleatorios
	for i in xrange(50):
		gera_permutado()
	
	# corner cases
	for i in xrange(10):
		gera_permutado(10, 2, 1)
	for i in xrange(10):
		gera_permutado(MAX_P, MAX_N, MAX_N*(MAX_N-1))
		gera_permutado(None, MAX_N, MAX_N*(MAX_N-1))
	
	# grafos em tripa
	for i in xrange(10):
		gera_tripinha()
		gera_tripinha(MAX_N)

	# grafos em camada
	for i in xrange(20):
		gera_camadas()
		gera_camadas(MAX_N)

	# samples
	print """1 2 1
1 2 1
4 4 4
1 2 2
1 3 2
2 4 2
3 4 1
0 0 0"""
