import matplotlib.pyplot as plt

with open("output.txt", "r") as file:
    lines = file.readlines()
    data = [float(x) for x in lines]

plt.plot(data)
plt.show()