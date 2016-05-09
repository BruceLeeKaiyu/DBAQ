# -*- coding:utf-8 -*-
import string
import random
import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

SIZE = 100

plf = np.polynomial.polynomial.polyfit
mean = np.mean
sum = np.sum

def GeneRandomSample(group,size):
    L = []
    if len(group)< size:
        return group
    L = random.sample(group,size)
    return L

def getV(x):
    return float(x[3])
def getLast(x):
    return float(x[-1])
def getNum(x):
    return int(x[0])

def GetPolyPara(L):
    Len = len(L)
    x = []
    for i in range(Len):
        x.append(i)
    Para = plf(x,L,4)

    return Para

def PolyValue(x,poly):
    y = 0
    xch = 1
    for eachPara in poly:
        y = y + xch*eachPara
        xch = xch * x
    return y


def GeneNormalSample(group,size):
    if len(group)<size:
        return group

    L = []
    res = []

    group.sort(key=getV)
    res.append(group.pop())
    res.append(group.pop(0))
    Len = len(group)
    T = []
    i = 0

    while i<Len:
        if i%SIZE==0 or i==Len-1:
            L.append(T)
            T = []
        else:
            T.append(group.pop(0))
        i = i + 1
    L.pop(0)

    for each in L:
        Num = []
        for eachitem in each:
            Num.append(float(eachitem[3]))
        Norm = norm.fit(Num)
        Mean = Norm[0]
        for eachitem in each:
            eachitem.append(abs(Mean - float(eachitem[3])))

        each.sort(key = getLast)

    itera1 = len(L[-1])
    i=0
    cnt = 0

    while i<itera1:
        for eachone in L:
            if cnt<size:
                res.append(eachone.pop(0))
                cnt = cnt + 1
            else:
                break
        if cnt>=size:
            break
        i = i + 1
    trash = L.pop()


    while i < SIZE:
        for eachone in L:
            if cnt < size:
                res.append(eachone.pop(0))
                cnt = cnt + 1
            else:
                break
        if cnt >= size:
            break
        i = i + 1

    res.sort(key = getNum)
    return res


def GenePolySample(group,size):
    if len(group)<size:
        return group

    L = []
    res = []

    group.sort(key=getV)
    res.append(group.pop())
    res.append(group.pop(0))
    Len = len(group)
    T = []
    i = 0

    while i<Len:
        if i%SIZE==0 or i==Len-1:
            L.append(T)
            T = []
        else:
            T.append(group.pop(0))
        i = i + 1
    L.pop(0)

    for each in L:
        Num = []
        for eachitem in each:
            Num.append(float(eachitem[3]))
        Poly = GetPolyPara(Num)

        j = 0
        for eachitem in each:
            Mean = PolyValue(j,Poly)
            eachitem.append(abs(Mean - float(eachitem[3])))
            j = j + 1

        each.sort(key = getLast)

    itera1 = len(L[-1])
    i=0
    cnt = 0

    while i<itera1:
        for eachone in L:
            if cnt<size:
                res.append(eachone.pop(0))
                cnt = cnt + 1
            else:
                break
        if cnt>=size:
            break
        i = i + 1
    trash = L.pop()


    while i < SIZE:
        for eachone in L:
            if cnt < size:
                res.append(eachone.pop(0))
                cnt = cnt + 1
            else:
                break
        if cnt >= size:
            break
        i = i + 1

    res.sort(key = getNum)
    return res


#Test right!
def FindSize(L,scale):
    Len = len(L)
    size = int(mean(L))
    while 1:
        cnt = 0
        for eachone in L:
            cnt = cnt + min(size,eachone)
        if cnt<scale:
            break
        else:
            size = size - 1

    return size


if __name__ == '__main__':
    f =open("OrderAll.tbl")
    Sample = []
    list_tmp = []
    for each in f:
        if each.strip('\n')[0] == '#':
            Sample.append(list_tmp)
            list_tmp = []
        else:
            object = each.strip('\n').split('|')
            object.pop()
            list_tmp.append(object)

    Sample.pop(0)

    SizeList = []
    for eachone in Sample:
        SizeList.append(len(eachone))
    size = FindSize(SizeList,300000)

    nf = open("Order_Poly_Stra_20%_sample.tbl",'w')
    for each_sample in Sample:
        #L = GeneRandomSample(each_sample,size)
        #L  = GeneNormalSample(each_sample,size)
        L = GenePolySample(each_sample,size)
        print len(L)
        nf.write('#\n')
        for eachone in L:
            for eachitem in eachone:
                nf.write(str(eachitem))
                if eachitem == eachone[-1]:
                    nf.write('\n')
                else:
                    nf.write('|')

    nf.write('##\n')
    nf.close()

    f.close()


