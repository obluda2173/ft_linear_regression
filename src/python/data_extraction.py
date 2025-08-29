import sqlite3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("../../data/data.csv")
print(df)

# printing the data table
print(df.plot(kind = "scatter", x = "km", y = "price"))

# finding the mean on price and km values
mean = df.mean()

# accessing and printing the price mean value
print("Mean value of price: ", mean.loc["price"])

# putting values in x_arr and y_arr
x_arr = np.array(df.get("km"))
y_arr = np.array(df.get("price"))
print(x_arr)
print(y_arr)

# getting intersection point and gradient
# I should rewrite it myself
m, k = np.polyfit(x_arr, y_arr, deg = 1)

plt.plot(x_arr, y_arr, "yo", x_arr, m*x_arr+k, "--k")
plt.show()
