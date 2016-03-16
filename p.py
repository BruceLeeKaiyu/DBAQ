# -*- coding:utf-8 -*-
import string
import math
import random

def isPrime(n):
	if n<=1:
		return False
	for i in range(2,int(math.sqrt(n))+1):
		if n % i == 0:
			return False
	return True

def num(n):
	if isPrime(n):
		return int(random.uniform(50,1000))
	else:
		if n%2==0:
			return int(random.uniform(1000,5000))
		else:
			return int(random.uniform(1000,5000))+5000

if __name__ == '__main__':
	Qcs = open("QCS.csv")
	data = open("data.csv",'w')
	cnt = 0
	for each_line in Qcs:
		cnt = cnt + 1
		each_line = each_line.strip("\n")
		Size = num(cnt)
		for i in range(Size):
			data.write(each_line)
			data.write(',')
			data.write(str(int(random.uniform(0,4294967295))))
			data.write('\n')
	data.close()
	Qcs.close()