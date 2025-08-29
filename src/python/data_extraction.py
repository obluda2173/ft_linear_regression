import sqlite3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("../../data/data.csv")
print(df)

print(df.plot(kind = "scatter", x = "km", y = "price"))

mean = df.mean()

print("Mean value of price: ", mean.loc["price"])

x_arr = np.array(df.get("km"))
y_arr = np.array(df.get("price"))

print(x_arr)
print(y_arr)

m, k = np.polyfit(x_arr, y_arr, deg = 1)

plt.plot(x_arr, y_arr, "yo", x_arr, m*x_arr+k, "--k")
plt.show()
