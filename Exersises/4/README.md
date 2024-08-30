# Exercise on Linear and Weighted Regression, and Logistic Regression with Weighted and Unweighted Models

This repository contains an exercise demonstrating the implementation and evaluation of linear regression and logistic regression models, including both unweighted and weighted approaches. The exercise focuses on understanding how different weighting schemes affect model performance and accuracy.

## Exercise Overview

The exercise is divided into two main parts:

1. **Linear Regression**:
   - Simple Linear Regression
   - Weighted Linear Regression with varying τ values

2. **Logistic Regression**:
   - Simple Logistic Regression
   - Weighted Logistic Regression with varying τ values

### Data Files

#### Sub-directory 1: Linear Regression
- `features.txt`: Training feature vectors for linear regression.
- `labels.txt`: Corresponding labels for training data.
- `simple_LR.py`: Implementation of Simple Linear Regression.
- `weighted_LR.py`: Implementation of Weighted Linear Regression.
- `simple_LR.png`: Plot showing the result of Simple Linear Regression.
- `weighted_LR_0.1.png`, `weighted_LR_0.3.png`, `weighted_LR_0.8.png`, `weighted_LR_2.png`, `weighted_LR_10.png`: Plots showing results of Weighted Linear Regression with different τ values.

#### Sub-directory 2: Logistic Regression
- `features_r.txt`: Training feature vectors for logistic regression.
- `labels_r.txt`: Corresponding labels for training data.
- `simple_LoR.py`: Implementation of Simple Logistic Regression.
- `weighted_LoR.py`: Implementation of Weighted Logistic Regression.
- `simple_LoR.png`: Plot showing the result of Simple Logistic Regression.
- `weighted_LoR_0.01.png`, `weighted_LoR_0.05.png`, `weighted_LoR_0.1.png`, `weighted_LoR_0.5.png`, `weighted_LoR_0.8.png`, `weighted_LoR_1.png`, `weighted_LoR_5.png`: Plots showing results of Weighted Logistic Regression with different τ values.

### Linear Regression Implementation

#### Simple Linear Regression (`simple_LR.py`)

This script implements simple linear regression to fit a line to the training data. The resulting model is plotted along with the training data.

- **Training**: Performs linear regression using the closed-form solution.
- **Plotting**: Displays the fitted line and training data in `simple_LR.png`.

#### Weighted Linear Regression (`weighted_LR.py`)

This script implements weighted linear regression where each data point is assigned a weight based on its distance from a test point. The weights are computed using a Gaussian kernel with a specified τ value.

- **Training**: Fits a line using weighted least squares regression.
- **Plotting**: Displays the fitted line and training data for various τ values. Plots are saved as `weighted_LR_*.png`.

### Logistic Regression Implementation

#### Simple Logistic Regression (`simple_LoR.py`)

This script implements logistic regression for binary classification. It uses gradient descent for training and evaluates accuracy on a test set.

- **Training**: Performs logistic regression with regularization.
- **Plotting**: Displays decision boundaries and class distributions in `simple_LoR.png`.

#### Weighted Logistic Regression (`weighted_LoR.py`)

This script implements weighted logistic regression, where weights are applied to training samples based on their distance from test points, similar to the approach used in weighted linear regression.

- **Training**: Fits a logistic regression model with weighted samples.
- **Accuracy Evaluation**: Compares the performance with different τ values and plots the decision boundary. Results are shown in `weighted_LoR_*.png`.

### Key Observations

#### Linear Regression
- **Simple Linear Regression**: Provides a straightforward fit to the training data, with results plotted in `simple_LR.png`.
- **Weighted Linear Regression**: The fit changes with different τ values, reflecting how weighting influences the model. Plots for different τ values are saved in `weighted_LR_*.png`.

#### Logistic Regression
- **Simple Logistic Regression**: Shows the decision boundary and class separation in `simple_LoR.png`.
- **Weighted Logistic Regression**: Performance and decision boundaries change with different τ values, as shown in the corresponding `weighted_LoR_*.png` plots.

### How to Use

1. Ensure you have the required libraries installed: `numpy`, `matplotlib`, `pandas`.
2. For linear regression:
   - Navigate to the `Sub-directory 1`.
   - Run `simple_LR.py` to perform simple linear regression.
   - Run `weighted_LR.py` to perform weighted linear regression with different τ values, and review the results in the generated plots.
3. For logistic regression:
   - Navigate to the `Sub-directory 2`.
   - Run `simple_LoR.py` to perform simple logistic regression and evaluate accuracy.
   - Run `weighted_LoR.py` to perform weighted logistic regression with varying τ values, and review the results in the generated plots.

### Conclusion

This exercise explores both linear and logistic regression models, providing insights into the impact of weighting schemes on model performance. By experimenting with different τ values, it highlights how the weighting parameter affects the fit of the model and the decision boundaries in classification tasks. The provided plots and accuracy metrics offer a comprehensive view of model behavior under varying conditions.
