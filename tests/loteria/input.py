
from random import randint

# gera varios PREMIADO
MAX_NUM = int('9'*20)
for i in xrange(1, 100):
	if 42**i <= MAX_NUM:
		print 42**i

# imprime os limites, just in case...
print 1
print MAX_NUM

# gera varios numeros aleatorios
for i in xrange(100):
	print randint(1, MAX_NUM)

# imprime o sample, just in case...
print """42
17283940536172938433
17283940536172938432
10000000000000000000
0"""
