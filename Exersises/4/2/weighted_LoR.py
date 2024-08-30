import numpy as np
from matplotlib import pyplot
from pandas import DataFrame
import random

def wheights(x_train,x_text,t=5):
    result = np.zeros((len(x_train),len(x_train)))
    for i in range (0,len(x_train)):
        result[i][i] = np.exp(-(np.dot((x_text-x_train[i]),(x_text-x_train[i])))/(2*(t**2)))
    return result


data = np.loadtxt(fname='features_r.txt',dtype='float')
label = np.loadtxt(fname='labels_r.txt',dtype='float')
train_factor = 0.7
data_size = len(data)

x_train = data[:int(train_factor*data_size)]
y_train = label[:int(train_factor*data_size)]

x_test = data[int(train_factor*data_size):]
y_test = label[int(train_factor*data_size):]

lr=0.1
num_iter=100
Lor_lambda = 0.0001

x1 =[]
x2 =[]
labels_pred =[]
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

for i in np.arange(-1,1,0.025):
    for j in np.arange(-1,1,0.025):
        w = wheights(x_train,[i,j])
        theta = np.zeros(x_train.shape[1])
        for k in range(num_iter):
            z = np.dot(x_train, theta)
            h = sigmoid(z)
            gradient = -np.dot(np.matmul(w,x_train).T, (h - y_train)) + (Lor_lambda*theta)
            theta = theta+ lr * gradient
        x1.append(i)
        x2.append(j)
        z = np.dot([i,j], theta)
        h = sigmoid(z)
        h = (h>0.5)
        labels_pred.append(h)

# scatter plot, dots colored by class value
fig, ax = pyplot.subplots()

df2 = DataFrame(dict(x1=x1[:], x2=x2[:], label=labels_pred))
colors2 = {0:'green', 1:'yellow'}
grouped2 = df2.groupby('label')
for key, group in grouped2:
    group.plot(ax=ax, kind='scatter', x='x1', y='x2', label=key, color=colors2[key])


df = DataFrame(dict(x1=x_test[:,0], x2=x_test[:,1], label=y_test))
colors = {0:'red', 1:'blue'}
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax, kind='scatter', x='x1', y='x2', label=key, color=colors[key])

acc = 0
for j in range(0,len(x_test)):
    w = wheights(x_train,x_test[j])
    theta = np.zeros(x_train.shape[1])
    for k in range(num_iter):
        z = np.dot(x_train, theta)
        h = sigmoid(z)
        gradient = -np.dot(np.matmul(w,x_train).T, (h - y_train)) + (Lor_lambda*theta)
        theta = theta+ lr * gradient
    z = np.dot(x_test[j], theta)
    h = sigmoid(z)
    if ((h<0.5 and y_test[j]==0) or (h>=0.5 and y_test[j]==1)):
        acc += 1

acc = acc/len(y_test)
print(acc)

pyplot.show()

