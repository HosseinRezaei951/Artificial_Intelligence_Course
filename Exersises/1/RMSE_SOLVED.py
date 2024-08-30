import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets
import math

import random

# Load the diabetes dataset
diabetes = datasets.load_diabetes()

# RMSE function
def RMSE(actual,predicted):
        total_SUM = 0
        difference = np.subtract(actual,predicted)
        for i in range (len(actual)):
                total_SUM += pow(difference[i],2)
        return math.sqrt(total_SUM/len(actual))

Test_size = 20

# Use only one feature
diabetes_X = diabetes.data[:, np.newaxis, 2]

# Split the data into training/testing sets
x_train = diabetes_X[:-20]
x_test = diabetes_X[-Test_size:]

# Split the targets into training/testing sets
y_train = diabetes.target[:-20]
y_test = diabetes.target[-Test_size:]

#phi_train=np.concatenate((np.ones((len(x_train),1)),x_train,np.power(x_train,3),np.power(x_train,5),np.power(x_train,6),np.power(x_train,7),np.power(x_train,8),np.power(x_train,9)),axis=1)

phi_train=np.concatenate((np.ones((len(x_train),1)),x_train),axis=1)
# Training Step
weight=np.matmul(np.matmul(np.linalg.inv(np.matmul(np.transpose(phi_train),phi_train))
        ,np.transpose(phi_train)),y_train)


# Test Phase
#phi_test=np.concatenate((np.ones((len(x_test),1)),x_test,np.power(x_test,3),np.power(x_test,5),np.power(x_test,6),np.power(x_test,7),np.power(x_test,8),np.power(x_test,9)),axis=1)
phi_test=np.concatenate((np.ones((len(x_test),1)),x_test),axis=1)
y_pred = np.matmul(phi_test,weight)


# Explained variance score: 1 is perfect prediction
print(len(x_train))
print(len(x_test))
# Plot outputs

RMS_Error = RMSE(y_test,y_pred)
print("Test Size : %4d , RMS Erro is: %2.4f" %(Test_size,RMS_Error))

plt.text(0.090,50,"Test Size : %4d \n RMS Erro is: %2.4f" %(Test_size,RMS_Error))
plt.scatter(x_train, y_train,  color='black')
plt.scatter(x_test, y_pred, color='blue')
plt.scatter(x_test, y_test, color='green')

plt.show()