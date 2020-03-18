from numpy import *
import math
def maxFunc(y):
    realY = y *(4096/1024)
    a = 791.792
    b = 1516.36
    k = 0.00351936
    part = (-realY+a)/(-b+a)
    lnPart = log(part)
    result = -(lnPart/k)
    return result

def minFunc(y):
    realY = y *(4096/1024)
    a = 779.408
    b = 1472.59
    k = 0.0035448
    part = (-realY+a)/(-b+a)
    lnPart = log(part)
    result = -(lnPart/k)
    return result

def meanFunc(y):
    realY = y *(4096/1024)
    a = 790.328
    b = 1504.64
    k = 0.00365181
    part = (-realY+a)/(-b+a)
    lnPart = log(part)
    result = -(lnPart/k)
    return result


def gtFunc(x):
    realX = x * (13419/1024)
    a = 23.202
    b = 74.0784
    k = 0.000258287
    result = 23.202+(74.0784-23.202)*e**(-k*realX)
    return result



outMax = open("maxCombined.dat", "w+")
outMin = open("minCombined.dat", "w+")
outMean = open("meanCombined.dat", "w+")
for y in range(0,1024):
    realY = y *(4096/1024)
    maxV = gtFunc(maxFunc(y))
    minV = gtFunc(minFunc(y))
    meanV = gtFunc(meanFunc(y))
    if not isnan(maxV):
        outMax.write(f'{realY} {maxV}\n')
    if not isnan(minV):
        outMin.write(f'{realY} {minV}\n')
    if not isnan(meanV):
        outMean.write(f'{realY} {meanV}\n')

