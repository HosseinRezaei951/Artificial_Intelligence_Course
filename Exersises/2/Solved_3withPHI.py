import numpy as np
import sklearn
import matplotlib.pyplot as plt
from sklearn import datasets
import random


from sklearn.datasets import make_moons
from matplotlib import pyplot
from pandas import DataFrame

data_size = 2000
train_factor = 0.7


# generate 2d classification dataset
data, label = make_moons(n_samples=data_size)


x_train = data[:int(train_factor*data_size)]
y_train = label[:int(train_factor*data_size)]

x_test = data[int(train_factor*data_size):]
y_test = label[int(train_factor*data_size):]


lr=0.001
num_iter=10000

def sigmoid(z):
    return (1 / (1 + np.exp(-z)))


phi_train=np.concatenate((np.ones((len(x_train),1)),x_train,np.power(x_train,2),np.power(x_train,3),np.power(x_train,4),np.power(x_train,5),np.power(x_train,6),np.power(x_train,7)),axis=1)
theta = np.zeros(phi_train.shape[1])

for i in range(num_iter):
    z = np.dot(phi_train, theta)
    h = sigmoid(z)
    
    gradient = -np.dot(phi_train.T, (h - y_train))/ y_train.size 
    #gradient = (-np.dot(phi_train.T, (h - y_train))/ y_train.size)+ 2*theta*Regulization_lamda

    theta = theta+ lr * gradient


phi_test=np.concatenate((np.ones((len(x_test),1)),x_test,np.power(x_test,2),np.power(x_test,3),np.power(x_test,4),np.power(x_test,5),np.power(x_test,6),np.power(x_test,7)),axis=1)
z = np.dot(phi_test, theta)
h = sigmoid(z)
h=(h>0.5)

acc=sum(h==y_test)/len(y_test)
print(sum(h==y_test))
print(acc)


x1=np.array(random.sample(range(0,300000), 10000))
x2=np.array(random.sample(range(0,300000), 10000))
X=[]
x1=(x1/100000)-1
x2=(x2/200000)-0.5
for i in range(0,len(x1)):
    X.append([x1[i],x2[i]])
    
X=np.concatenate((np.ones((len(X),1)),X,np.power(X,2),np.power(X,3),np.power(X,4),np.power(X,5),np.power(X,6),np.power(X,7)),axis=1)
z1 = np.dot(X,theta)
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



phi_train=np.concatenate((np.ones((len(x_train),1)),x_train,np.power(x_train,2),np.power(x_train,3),np.power(x_train,4),np.power(x_train,5),np.power(x_train,6),np.power(x_train,7)),axis=1)
theta = np.zeros(phi_train.shape[1])

Regulization_lambda = 0.1
for i in range(num_iter):
    z = np.dot(phi_train, theta)
    h = sigmoid(z)
    
    #gradient = -np.dot(phi_train.T, (h - y_train)) / y_train.size
    gradient = (-np.dot(phi_train.T, (h - y_train))/ y_train.size) + 2*theta*Regulization_lambda
    theta = theta+ lr * gradient

phi_test=np.concatenate((np.ones((len(x_test),1)),x_test,np.power(x_test,2),np.power(x_test,3),np.power(x_test,4),np.power(x_test,5),np.power(x_test,6),np.power(x_test,7)),axis=1)
z = np.dot(phi_test, theta)
h = sigmoid(z)
h=(h>0.5)

acc=sum(h==y_test)/len(y_test)
print(sum(h==y_test))
print(acc)


x1=np.array(random.sample(range(0,300000), 10000))
x2=np.array(random.sample(range(0,300000), 10000))
X=[]
x1=(x1/100000)-1
x2=(x2/200000)-0.5
for i in range(0,len(x1)):
    X.append([x1[i],x2[i]])

X=np.concatenate((np.ones((len(X),1)),X,np.power(X,2),np.power(X,3),np.power(X,4),np.power(X,5),np.power(X,6),np.power(X,7)),axis=1)
z1 = np.dot(X,theta)
h1 = sigmoid(z1)
h1=(h1>0.5)

# scatter plot, dots colored by class value
fig2, ax2 = pyplot.subplots()

df2 = DataFrame(dict(x1=x1[:], x2=x2[:], label=h1))
colors2 = {0:'green', 1:'yellow'}
grouped2 = df2.groupby('label')
for key, group in grouped2:
    group.plot(ax=ax2, kind='scatter', x='x1', y='x2', label=key, color=colors2[key])


df = DataFrame(dict(x1=x_test[:,0], x2=x_test[:,1], label=y_test))
colors = {0:'red', 1:'blue'}
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax2, kind='scatter', x='x1', y='x2', label=key, color=colors[key])
pyplot.show()            