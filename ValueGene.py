# -*- coding:utf-8 -*-
import string
import math
import random

#Randomly generate <= 40000 * 10000 values to one file
#sampling <= 40000 * 1000 values to another file

def GeneNum(n,file):
    file.write('#'+','+str(n)+'\n')
    for i in range(n):
        file.write(str(int(random.uniform(0,4294967295)))+'\n')

if __name__ == '__main__':
    f = open("Value.txt",'w')
    for i in range(1000):
        times = int(random.uniform(0,500))
        GeneNum(times,f)
    for i in range(11000):
        times = int(random.uniform(500,1000))
        GeneNum(times,f)
    for i in range(4000):
        times = int(random.uniform(1000,5000))
        GeneNum(times,f)
    for i in range(2000):
        times = int(random.uniform(5000,9000))
        GeneNum(times,f)
    for i in range(21000):
        times = int(random.uniform(9000,11000))
        GeneNum(times,f)
    for i in range(1000):
        times = int(random.uniform(11000,15000))
        GeneNum(times,f)
    f.close()
