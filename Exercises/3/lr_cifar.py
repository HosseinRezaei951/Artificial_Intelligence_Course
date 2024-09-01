
import numpy as np
import sklearn
import matplotlib.pyplot as plt
from keras.datasets import cifar10

(X_train, y_train), (X_test, y_test) = cifar10.load_data()

lr=0.001
num_iter=100
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

batch_size =1000
# weights initialization
theta = np.zeros((3072,1))
for i in range(num_iter):
    for j in range(int(50000/batch_size)):
        X_train_batch = X_train[((j)*batch_size):((j+1)*batch_size),]
		
        X = X_train_batch.reshape(batch_size,32*32*3)
        y_train_batch=y_train[((j)*batch_size):((j+1)*batch_size),]
        y = (y_train_batch != 0) * 1
        z = np.dot(X, theta)
        h = sigmoid(z)
        gradient = np.matmul(np.transpose(X), (h - y)) / y.size
        theta = theta- lr * gradient


X = X_test.reshape(10000,32*32*3)
y = (y_test != 0) * 1
y_p=sigmoid(np.matmul(X,theta))

y_p=(y_p >= 0.5) * 1

zero_count = 0
one_count = 0
for i in range(0,len(y_p)):
        if (y_p[i]==y[i] and y_p[i]==0):
                zero_count = zero_count + 1
        elif (y_p[i]==y[i] and y_p[i]==1):
                one_count = one_count + 1

zero_acc = (zero_count/np.sum(y==0))
one_acc = (one_count/np.sum(y==1))

print(np.sum(y==0),np.sum(y==1))
print("zero count: ",zero_count)
print("one count: ",one_count)
print((zero_acc+one_acc)/2)