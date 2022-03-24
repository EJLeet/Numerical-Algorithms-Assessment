import matplotlib.pyplot as plt

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
    plt.plot(vals)
    plt.show()

if __name__ == "__main__":
    read_file("output.txt")




