import matplotlib.pyplot as plt

with open("output.txt", "r") as file:
    lines = file.readlines()
    data = [float(x) for x in lines]

plt.plot(data)
plt.title("Total Deflection Over The Length Of The Rod")
plt.xlabel("Length")
plt.ylabel("Deflection")
plt.xticks([0, 10, 20, 30, 40, 50, 60],[0, 5, 10, 15, 20, 25, 30])
plt.savefig("results.jpg")