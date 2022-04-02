from multiprocessing.connection import wait
import matplotlib.pyplot as plt
import numpy as np

with open('half.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Half h-value vs error ")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y)
plt.savefig("half.jpg")
plt.close()

with open('float.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Float h-value vs error ")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y)
plt.savefig("float.jpg")
plt.close()

with open('double.txt', 'r') as file:
    lines = file.readlines()
    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
plt.title("Double h-value vs error ")
plt.xlabel("Log10 h-value")
plt.ylabel("log10 error")
plt.scatter(x, y)
plt.savefig("double.jpg")
plt.close()

    





