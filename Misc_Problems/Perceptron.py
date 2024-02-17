import matplotlib.pyplot as plt
from random import random

# Positive randon data points
x1 = [[random(), random()] for i in range(100)]
# Negative random data points
x2 = [[-random(), -random()] for i in range(100)]

w = [0.2, -0.1 , 0.8]
lr = 1

#plot the data points
plt.plot([x[0] for x in x1], [x[1] for x in x1], 'ro')
plt.plot([x[0] for x in x2], [x[1] for x in x2], 'bo')
x = [i for i in range(-1,2)]
y = [-(w[0] + w[1]*i)/w[2] for i in x]
plt.plot(x,y)
plt.show()

def line(x1,x2,w):
    return w[0] + w[1]*x1 + w[2]*x2

def sign(x):
    if x >= 0:
        return 1
    else:
        return -1

def update(x,y,w):
    error = sign(x) - sign(line(x,y,w))
    w[0] = w[0] + lr*error
    w[1] = w[1] + lr*error*x
    w[2] = w[2] + lr*error*y
    return error

error = 1
while error != 0:
    error = 0
    for x in x1:
        if update(x[0],x[1],w) != 0:
            error = 1
    for x in x2:
        if update(x[0],x[1],w) != 0:
            error = 1

# Plot the line defined by w
x = [i for i in range(-1,2)]
y = [-(w[0] + w[1]*i)/w[2] for i in x]
plt.plot(x,y)
plt.plot([x[0] for x in x1], [x[1] for x in x1], 'ro')
plt.plot([x[0] for x in x2], [x[1] for x in x2], 'bo')
plt.show()



