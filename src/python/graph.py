import sqlite3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import json

df = pd.read_csv("../../data/data.csv")

# printing the data table
# print(df.plot(kind = "scatter", x = "km", y = "price"))

mean = df.mean()

# accessing and printing the price mean value
# print("Mean value of price: ", mean.loc["price"])

# putting values in x_arr and y_arr
x_arr = np.array(df.get("km")) / 1000
y_arr = np.array(df.get("price"))

with open("../../data/model.json", "r") as f:
    parsed_thetas = json.load(f)

intercept = parsed_thetas["theta0"]
slope = parsed_thetas["theta1"]

plt.xlabel("mileage in km")
plt.ylabel("cost")

plt.plot(x_arr, y_arr, "yo", x_arr, slope * x_arr + intercept, "--k")
plt.show()
