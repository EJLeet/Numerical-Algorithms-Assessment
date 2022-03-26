import matplotlib.pyplot as plt
import numpy as np

def read_file(file):
    vals = []
    with open (file, "r") as fp:
        for line in fp:
            vals.append(line)
    draw_plot(vals)

def draw_plot(vals):

    data = [int(line) for line in vals]
    
    # dv/dt
    plt.figure(0)
    plt.title("Acceleration dv/dt \nfrom t = 0 to t = 30")
    plt.xlabel("Time (t)")
    plt.ylabel('Acceleration')
    plt.plot(data[:30]) 
    plt.yticks([-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220], 
            [-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220])
    plt.tight_layout()
    plt.savefig('dv.jpg')
    
    # dv"/dt
    plt.figure(1)
    plt.title('Rate of Change of Acceleration dv"/dt \nfrom t = 0 to t = 30')
    plt.xlabel("Time (t)")
    plt.ylabel('Change of Acceleration')
    plt.plot(data[30:]) 
    plt.yticks([0, 4, 22], 
            [0, 4, 22])
    plt.tight_layout()
    plt.savefig('dv2.jpg')
    
    # combined
    plt.figure(2)
    plt.title("Acceleration and Rate of Change of Acceleration \nfrom t = 0 to t = 30")
    plt.xlabel("Time (t)")
    plt.ylabel('Derivative Value')
    plt.plot(data[:30])
    plt.plot(data[30:]) 
    plt.yticks([-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220], 
            [-5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220])
    plt.legend(['dv/dt', 'dv"/dt'], loc ="upper right")
    plt.tight_layout()
    plt.savefig('combined.jpg')




if __name__ == "__main__":
    read_file("output.txt")




