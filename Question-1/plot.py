from multiprocessing.connection import wait
import matplotlib.pyplot as plt
import numpy as np

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
print ("y=%.6fx+(%.6f)"%(z[0],z[1]))
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
# the line equation: remove -inf from data if need be - will need to 
print ("y=%.6fx+(%.6f)"%(z[0],z[1]))
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
print ("y=%.12fx+(%.12f)"%(z[0],z[1]))

plt.savefig("double.jpg")
plt.close()