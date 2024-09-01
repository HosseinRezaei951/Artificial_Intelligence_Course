import matplotlib.pyplot as plt
import numpy as np

x_train = np.loadtxt(fname='features.txt',dtype='float')
y_train = np.loadtxt(fname='labels.txt',dtype='float')
x_train=x_train[:,np.newaxis]

# Training Step
phi_train=np.concatenate((np.ones((len(x_train),1)),x_train),axis=1)
theta=np.matmul(np.matmul(np.linalg.inv(np.matmul(np.transpose(phi_train),phi_train)),np.transpose(phi_train)),y_train)

# Plot outputs
plt.scatter(x_train, y_train,  color='black')
plt.plot([-6,13],[theta[0]+(-6*theta[1]),theta[0]+(13*theta[1])],  color='blue',linewidth=3)
plt.show()