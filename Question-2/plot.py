import matplotlib.pyplot as plt
import numpy as np

def read_file(file):
    vals = []
    with open (file, "r") as fp:
        for line in fp:
            vals.append(line)
    draw_plot(vals)

def draw_plot(vals):

    data = [float(line) for line in vals]
    
    # dv/dt
    plt.figure(0)
    plt.title("Acceleration dv/dt \nfrom t = 0 to t = 30")
    plt.xlabel("Time (t)")
    plt.ylabel('Acceleration')
    plt.plot(data[:300]) 
    plt.xticks( [0, 50, 100, 150, 200, 250, 300], [0, 5, 10, 15, 20, 25, 30])
    plt.tight_layout()
    plt.savefig('dv.jpg')
    
    # dv"/dt
    plt.figure(1)
    plt.title('Rate of Change of Acceleration dv"/dt \nfrom t = 0 to t = 30')
    plt.xlabel("Time (t)")
    plt.ylabel('Change of Acceleration')
    plt.plot(data[300:]) 
    plt.xticks( [0, 50, 100, 150, 200, 250, 300], [0, 5, 10, 15, 20, 25, 30])
    plt.tight_layout()
    plt.savefig('dv2.jpg')
    
    # combined
    plt.figure(2)
    plt.title("Acceleration and Rate of Change of Acceleration \nfrom t = 0 to t = 30")
    plt.xlabel("Time (t)")
    plt.ylabel('Value (Acceleration or Change of Acceleration)')
    plt.plot(data[:300])
    plt.plot(data[300:]) 
    plt.xticks( [0, 50, 100, 150, 200, 250, 300], [0, 5, 10, 15, 20, 25, 30])
    plt.legend(['dv/dt', 'dv"/dt'], loc ="upper right")
    plt.tight_layout()
    plt.savefig('combined.jpg')




if __name__ == "__main__":
    read_file("output.txt")




