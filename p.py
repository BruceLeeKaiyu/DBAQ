# -*- coding:utf-8 -*-
import string
import math
import random
import numpy as np
import matplotlib.pyplot as plt

DIVIDE = 10

class DataSlice(object):

	def __init__(self ,Data ,range,threshold,size):
		self.DataList = Data
		self.begin = range[0]
		self.end = range[1]
		self.mean = np.mean(Data)
		self.std = np.var(Data)
		self.Sample = []
		self.threshold = threshold
		self.size = size

	def __getDistance__(self, p, polyPara):
		t = len(polyPara)
		res = 0
		time = 1
		for i in range(t):
			res = res + time *polyPara[-1]
			time = time * p[0]

		return abs(p[1] - res)

	def __polyfit__(self,L):
		#self.DataList.sort()
		Len = len(L)
		x_degree = range(1,(Len+1))
		p = np.polyfit(x_degree,L,3)
		return p

	def __GeneOrder__(self):
		self.DataList.sort()
		PriorList = []
		PriorList.append(self.DataList[0])
		self.DataList.pop(0)
		priorList.append(self.DataList[-1])
		self.DataList.pop()

	def __GeneSample__(self):
		Len = len(self.DataList)
		bottom = int(Len*self.begin)
		top = int(Len*self.bottom)

	def __PrintTest__(self):
		print self.DataList 
		print self.Sample 


if __name__ == '__main__':
	L = [1,23,2,3,4,5,6,6,78,9,9]
	t = [0.1,0.5]
	DN = DataSlice(L,t)

	DN.__PrintTest__()
	print L