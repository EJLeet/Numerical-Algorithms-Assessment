from multiprocessing.connection import wait
import matplotlib.pyplot as plt
import numpy as np

"""
This line equation scheme is quite messy.
You will first need to remove the log from the main.cpp.
Secondly remove the infinity values from the 
float text file and half text file. After removing 
these you can then run this file to get accurate line
equations. The above does not need to be done
if you only require the graphs.

"""
with open('half.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Predicted Half H-value vs Error ")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y)
# calc the trendline
z = np.polyfit(x, y, 2)
p = np.poly1d(z)
plt.plot(x,p(x),"r--")
# the line equation: remove -inf from data if need be
print ("y=%.6fx^2 + %.6fx + %.6f"%(z[0],z[1], z[2]))
plt.savefig("half.jpg")
plt.close()

with open('float.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Predicted Float H-value vs Error ")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y)
# calc the trendline
z = np.polyfit(x, y, 2)
p = np.poly1d(z)
plt.plot(x,p(x),"r--")
# the line equation: remove -inf from data if need be 
print ("y=%.6fx^2 + %.6fx + %.6f"%(z[0],z[1], z[2]))
plt.savefig("float.jpg")
plt.close()   

with open('double.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Predicted Double H-value vs Error")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y) 
# calc the trendline
z = np.polyfit(x, y, 2)
p = np.poly1d(z)
plt.plot(x,p(x),"r--")
# the line equation:
print ("y=%.12fx^2 + %.12fx + %.12f"%(z[0],z[1], z[2]))
plt.savefig("double.jpg")
plt.close()