import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets, linear_model
from sklearn.metrics import mean_squared_error, r2_score
import random


# Load the diabetes dataset
# diabetes = datasets.load_diabetes()


# # Use only one feature
# diabetes_X = diabetes.data[:, np.newaxis, 2]

# # Split the data into training/testing sets
# diabetes_X_train = diabetes_X[:-420]
# diabetes_X_test = diabetes_X[-420:]

# # Split the targets into training/testing sets
# diabetes_y_train = diabetes.target[:-420]
# diabetes_y_test = diabetes.target[-420:]

x_train=np.sort(np.array(random.sample(range(1, 100), 9)))
x_train=x_train[:,np.newaxis]
print(x_train)
x_train=x_train/100
y_train=-0.3+0.5*np.sin(x_train*np.pi*2)
print(y_train)

x_test=np.sort(np.array(random.sample(range(1, 100), 99)))
x_test=x_test[:,np.newaxis]
x_test=x_test/100
y_test=-0.3+0.5*np.sin(x_test*np.pi*2)

phi_train=np.concatenate((np.ones((len(x_train),1)),x_train,np.power(x_train,3),np.power(x_train,5),np.power(x_train,6),np.power(x_train,7),np.power(x_train,8),np.power(x_train,9)),axis=1)
#phi_train=np.concatenate((np.ones((len(x_train),1)),x_train,np.power(x_train,3)),axis=1)

# Training Step
weight=np.matmul(np.matmul(np.linalg.inv(np.matmul(np.transpose(phi_train),phi_train)),np.transpose(phi_train)),y_train)


# Test Phase
phi_test=np.concatenate((np.ones((len(x_test),1)),x_test,np.power(x_test,3),np.power(x_test,5),np.power(x_test,6),np.power(x_test,7),np.power(x_test,8),np.power(x_test,9)),axis=1)
#phi_test=np.concatenate((np.ones((len(x_test),1)),x_test,np.power(x_test,3)),axis=1)
y_pred = np.matmul(phi_test,weight)


# Explained variance score: 1 is perfect prediction
print(len(x_train))
print(len(x_test))
# Plot outputs

plt.scatter(x_train, y_train,  color='black')
plt.scatter(x_test, y_pred, color='blue')
plt.plot(x_test, y_pred, color='blue',linewidth=3)
plt.plot(x_test, y_test, color='green')

plt.show()