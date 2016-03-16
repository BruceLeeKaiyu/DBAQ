# -*- coding:utf-8 -*-
import string
import random 
if __name__ == '__main__':
	data = open("data.csv")
	cnt=0
	L=[]
	for each_line in data:
		cnt=cnt +1
		print cnt
		L.append(each_line)
