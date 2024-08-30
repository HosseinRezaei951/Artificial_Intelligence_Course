import matplotlib.pyplot as plt
import numpy as np


def wheights(x_train,x_text,t=0.8):
    result = np.zeros((len(x_train),len(x_train)))
    for i in range (0,len(x_train)):
        result[i][i] = np.exp(-((x_text-x_train[i])**2)/(2*(t**2)))
    return result


x_train = np.loadtxt(fname='features.txt',dtype='float')
y_train = np.loadtxt(fname='labels.txt',dtype='float')
x_train=x_train[:,np.newaxis]

# Training Step
phi_train=np.concatenate((np.ones((len(x_train),1)),x_train),axis=1)


x = []
y = []
for i in np.arange(-6,13,0.01):
    w = wheights(x_train,i)
    theta=np.matmul(np.matmul(np.matmul(np.linalg.inv(np.matmul(np.matmul(np.transpose(phi_train),w),phi_train)),np.transpose(phi_train)),w),y_train)
    x.append(i)
    y.append(theta[0]+theta[1]*i)

# Plot outputs
plt.scatter(x_train, y_train,  color='black')
plt.plot(x,y, color='blue',linewidth=3)
plt.show()