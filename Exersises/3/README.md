# Exercise on Accuracy Calculation in Imbalanced Datasets and Impact of Epoch and Iteration Numbers

This repository contains an exercise that demonstrates how to calculate accuracy in imbalanced datasets and analyzes the effects of varying the number of epochs and iterations on the resulting accuracy. The exercise focuses on understanding the behavior of logistic regression when applied to a dataset with a significant class imbalance, using a custom accuracy formula.

## Exercise Overview: Accuracy Calculation in Imbalanced Datasets (`lr_cifar.py`)

This exercise introduces a specific formula for calculating accuracy in imbalanced datasets, assuming a binary classification scenario. The focus is on evaluating how the accuracy changes when modifying the number of epochs and iterations during training. The exercise uses the CIFAR-10 dataset, a popular benchmark in image classification tasks.

### Key Features

- **Data Loading**: Uses the CIFAR-10 dataset, loading training and testing data for a binary classification problem.
- **Custom Accuracy Calculation**: Implements a custom formula to calculate accuracy in imbalanced datasets, accounting for both classes separately.
- **Logistic Regression Implementation**: Uses logistic regression with batch processing, where the batch size and number of iterations (epochs) are adjustable.
- **Imbalanced Dataset Handling**: Handles the class imbalance by focusing on binary classification (class 0 vs. all others).
- **Epoch and Iteration Impact Analysis**: Examines how different values for batch size and epochs affect the model’s accuracy.

### Custom Accuracy Formula

Given an imbalanced dataset with two classes (0 and 1), the accuracy is calculated as follows:

\[ \text{Accuracy} = \frac{1}{2} \left( \frac{\text{Correct predictions for class 0}}{\text{Total samples of class 0}} + \frac{\text{Correct predictions for class 1}}{\text{Total samples of class 1}} \right) \]

This formula ensures that the accuracy metric takes into account the performance on both classes, which is particularly important in imbalanced datasets where a simple accuracy metric might be misleading.

### Experimental Results and Analysis

The results of the experiments are presented in a table that includes the following details:

- **Batch Size**: Number of samples processed in each iteration.
- **Iterations (Epochs)**: Number of times the model processes the entire dataset.
- **Zero Count**: Number of correctly predicted samples belonging to class 0.
- **One Count**: Number of correctly predicted samples belonging to class 1.
- **Result**: The final calculated accuracy based on the custom formula.

#### Sample Results

| Batch Size | Iterations (Epochs) | Zero Count | One Count | Result |
|------------|---------------------|------------|-----------|--------|
| 1          | 1                   | 633        | 6753      | 0.6917 |
| 100        | 1                   | 0          | 9000      | 0.5000 |
| 500        | 10                  | 695        | 6977      | 0.7351 |
| 1000       | 4                   | 866        | 4865      | 0.7033 |

#### Observations

- **Impact of Batch Size**: Increasing the batch size generally improves accuracy, but this trend is not consistent across all settings, indicating that batch size must be carefully tuned.
- **Effect of Iterations (Epochs)**: The accuracy tends to improve with more iterations, but beyond a certain point, the improvements become marginal or even negative.
- **Best Results**: The highest accuracy was observed when the batch size was set to 500 and the number of iterations was set to 10.

### How to Use

1. Ensure you have the required libraries installed: `numpy`, `matplotlib`, `sklearn`, `keras`.
2. Run the `lr_cifar.py` script to perform logistic regression on the CIFAR-10 dataset with the specified batch size and iteration settings.
3. Observe the printed zero and one counts, and the final accuracy result to understand the model's performance under different configurations.

### Conclusion

This exercise provides valuable insights into the challenges of working with imbalanced datasets in machine learning. By experimenting with different batch sizes and iteration numbers, the exercise highlights the importance of tuning these hyperparameters to achieve optimal performance, especially when dealing with imbalanced data.

The custom accuracy formula ensures that the evaluation metric is fair and representative of both classes, avoiding the pitfalls of using standard accuracy metrics in imbalanced scenarios.
