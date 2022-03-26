import matplotlib.pyplot as plt
import numpy as np

def read_file(file):
    vals = []
    with open (file, "r") as fp:
        for line in fp:
            vals.append(line)
    draw_plot(vals)

def draw_plot(vals):
    plt.title("Central Difference Formula at Different h-value")
    plt.xlabel("h-value")
    plt.ylabel("Result")
    h = 0.25
    plt.xticks([0, 20, 40, 60, 80, 100], [round(h/1, 4), round(h/20, 4), 
                round(h/40, 4), round(h/60, 4), round(h/80, 4), round(h/100, 4)])

    data = [float(line) for line in vals]

    inc = (data[99] - data[0]) / 11
    plt.yticks([0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30], 
               [round(data[0], 4), round(data[0] + inc, 4), 
                round(data[0] + (2 * inc), 4), round(data[0] + (3 * inc), 4), 
                round(data[0] + (4 * inc), 4), round(data[0] + (5 * inc), 4), 
                round(data[0] + (6 * inc), 4), round(data[0] + (7 * inc), 4), 
                round(data[0] + (8 * inc), 4), round(data[0] + (9 * inc), 4), 
                round(data[99], 4)])
    plt.plot(vals)
    plt.tight_layout()
    plt.savefig('h_results.jpg')

if __name__ == "__main__":
    read_file("output.txt")




