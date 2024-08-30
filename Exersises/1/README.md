# Exercises on Polynomial Regression and RMSE Calculation

This repository contains two exercises that demonstrate the application of polynomial regression and the calculation of the Root Mean Squared Error (RMSE) using Python. The exercises utilize the diabetes dataset from Scikit-learn and implement polynomial regression to model the relationship between input features and target values.

## Exercise 1: Polynomial Regression (Phi_Problem.py)

This exercise implements polynomial regression using a closed-form solution. The code generates random training and testing data, constructs the design matrix, and calculates the optimal weights using the normal equation. The resulting model is then used to make predictions on the test data and visualize the results.

### Key Features

- **Data Generation**: Randomly generates training and testing data points.
- **Design Matrix Construction**: Constructs a design matrix with polynomial features.
- **Training**: Computes optimal weights using the closed-form solution.
- **Testing**: Predicts target values for the test data.
- **Visualization**: Plots the training data, predicted values, and actual values for comparison.

### How to Use

1. Ensure you have the required libraries installed: `numpy`, `matplotlib`.
2. Run the `Phi_Problem.py` script to execute the polynomial regression.
3. The output will display a plot comparing the predicted values against the actual values.

## Exercise 2: RMSE Calculation (RMSE_SOLVED.py)

This exercise focuses on calculating the Root Mean Squared Error (RMSE) for predictions made by a linear regression model on the diabetes dataset. It demonstrates how to evaluate the performance of the regression model using RMSE.

### Key Features

- **Data Loading**: Loads the diabetes dataset from Scikit-learn.
- **RMSE Function**: Implements a custom function to calculate RMSE.
- **Data Splitting**: Splits the dataset into training and testing sets.
- **Design Matrix Construction**: Constructs a design matrix for linear regression.
- **Training**: Computes weights using the normal equation.
- **Testing**: Predicts target values for the test data.
- **Performance Evaluation**: Calculates and prints the RMSE for the model.

### How to Use

1. Ensure you have the required libraries installed: `numpy`, `matplotlib`, `scikit-learn`.
2. Run the `RMSE_SOLVED.py` script to execute the RMSE calculation.
3. The output will display the RMSE value along with a plot comparing the predicted and actual values.

## Conclusion

These exercises provide a practical understanding of polynomial regression and RMSE calculation in the context of regression analysis. They demonstrate the importance of model evaluation and the use of polynomial features to improve predictions. Feel free to modify the code and experiment with different datasets or polynomial degrees to explore the effects on model performance.