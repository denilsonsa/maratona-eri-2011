
if __name__ == '__main__':
	while True:
		N = input()
		if N == 0:
			break

		if N % 42 == 0:
			print 'PREMIADO'
		else:
			print 'TENTE NOVAMENTE'

