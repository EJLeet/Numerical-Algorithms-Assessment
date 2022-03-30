import matplotlib.pyplot as plt
import numpy as np
import math

def read_file(file):
    vals = []
    with open (file, "r") as fp:
        for line in fp:
            vals.append(line)
    draw_plot(vals)

def draw_plot(vals):
    data = [float(line) for line in vals]
    # comment out other 2 depending on what graph you want to make

    # # plot double
    # plt.plot(data[:10000]) 
    # plt.xticks([0, 2000, 4000, 6000, 8000, 10000], 
    #         [-3, -2, -1, 0, 1, 2])
    # plt.savefig('double.jpg')

    # # plot float
    # plt.plot(data[10000:19999]) 
    # plt.xticks([0, 2000, 4000, 6000, 8000, 10000], 
    #         [-3, -2, -1, 0, 1, 2])
    # plt.savefig('float.jpg')

    # # plot float
    # plt.plot(data[20000:]) 
    # plt.xticks([0, 500, 1000, 1500, 2000, 2500, 3000], 
    #         [-3, -2.5, -2, -1.5, -1, -0.5, 0])
    # plt.savefig('half_float.jpg')

if __name__ == "__main__":
    read_file("outfile.txt")




