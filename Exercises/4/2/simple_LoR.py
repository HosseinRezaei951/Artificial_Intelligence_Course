import numpy as np
from matplotlib import pyplot
from pandas import DataFrame
import random

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

def sigmoid(z):
    return 1 / (1 + np.exp(-z))
        

theta = np.zeros(x_train.shape[1])
for i in range(num_iter):
    z = np.dot(x_train, theta)
    h = sigmoid(z)
    gradient = -np.dot(x_train.T, (h - y_train)) + (theta*Lor_lambda)
    theta = theta+ lr * gradient

z = np.dot(x_test, theta)
h = sigmoid(z)
h=(h>0.5)
print(h)
acc=sum(h==y_test)/len(y_test)
print(acc)

x1=np.array(random.sample(range(0,200000), 100000))
x2=np.array(random.sample(range(0,200000), 100000))
X_pred=[]
x1=(x1/100000)-1
x2=(x2/100000)-1
for i in range(0,len(x1)):
    X_pred.append([x1[i],x2[i]])
    
z1 = np.dot(X_pred,theta)
h1 = sigmoid(z1)
h1=(h1>0.5)

# scatter plot, dots colored by class value
fig, ax = pyplot.subplots()

df2 = DataFrame(dict(x1=x1[:], x2=x2[:], label=h1))
colors2 = {0:'green', 1:'yellow'}
grouped2 = df2.groupby('label')
for key, group in grouped2:
    group.plot(ax=ax, kind='scatter', x='x1', y='x2', label=key, color=colors2[key])


df = DataFrame(dict(x1=x_test[:,0], x2=x_test[:,1], label=y_test))
colors = {0:'red', 1:'blue'}
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax, kind='scatter', x='x1', y='x2', label=key, color=colors[key])

pyplot.show()
