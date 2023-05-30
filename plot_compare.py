import csv
import math as m
import matplotlib.pyplot as plt
import os

RAW_DATA = os.path.join("test", "data", "celestrak_1yr_1mo.csv")
INTERP_DATA = os.path.join("build", "interp_data.csv")

raw_data_mjd = []
raw_data_x = []
with open(RAW_DATA, "r", newline="") as fp:
    csv_file = csv.reader(fp, delimiter=",")
    next(csv_file)

    for row in csv_file:
        raw_data_mjd.append(float(row[1]))
        raw_data_x.append(float(row[2]))

interp_data_mjd = []
interp_data_x = []
with open(INTERP_DATA, "r", newline="") as fp:
    csv_file = csv.reader(fp, delimiter=",")
    next(csv_file)

    for row in csv_file:
        interp_data_mjd.append(float(row[0]))
        interp_data_x.append(float(row[1]))


plt.figure()
plt.plot(raw_data_mjd, raw_data_x, "r*", label="Raw")
plt.plot(interp_data_mjd, interp_data_x, "b", label="Interpolated")
plt.title("Raw Data Points vs Interpolation")
plt.xlabel("MJD")
plt.ylabel("X [arcsec]")
plt.legend()
plt.grid()
plt.savefig("yay_results.png")
