import matplotlib.pyplot as plt
import numpy as np

def read_file(file):
    vals = []
    with open (file, "r") as fp:
        for line in fp:
            vals.append(line)
    draw_plot(vals)

def draw_plot(vals):
    plt.title("Acceleration and Rate of Change of Acceleration \nfrom t = 0 to t = 30")
    plt.xlabel("Time (t)")
    plt.ylabel("Acceleration Value")

    data = [int(line) for line in vals]

    plt.plot(data[:30]) # dv/dt
    plt.plot(data[30:]) # dv"/dt

    plt.yticks([-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220], 
               [-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220])

    plt.legend(['dv/dt', 'dv"/dt'], loc ="upper right")
    plt.tight_layout()
    plt.savefig('acceleration.jpg')

if __name__ == "__main__":
    read_file("output.txt")




