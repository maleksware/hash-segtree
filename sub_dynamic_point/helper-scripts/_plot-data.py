import matplotlib.pyplot as plt
import csv

col_map = {
    "hash": "red",
    "point": "blue",
    "range": "green"
}

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111)
ax.set_xlabel("Test size")
ax.set_ylabel("Wall clock execution time, ms")

for progname in ["hash", "point", "range"]:
    avg_times_qp = {}
    avg_times_ln = {}

    lengths_qp = []
    times_qp = []
    lengths_ln = []
    times_ln = []

    with open(f"{progname}.csv", "r") as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        
        for row in reader:
            if row[0] == "qp":
                avg_times_qp[int(row[1])] = avg_times_qp.get(int(row[1]), list())
                avg_times_qp[int(row[1])].append(float(row[2]))
            else:
                avg_times_ln[int(row[1])] = avg_times_ln.get(int(row[1]), list())
                avg_times_ln[int(row[1])].append(float(row[2]))


    for key in avg_times_qp:
        value = avg_times_qp[key]
        lengths_qp.append(key)
        times_qp.append(sum(value) / len(value))

    for key in avg_times_ln:
        value = avg_times_ln[key]
        lengths_ln.append(key)
        times_ln.append(sum(value) / len(value))

    ax.scatter(lengths_qp, times_qp, color=col_map[progname], marker="o", label=progname + " (QP)", s=[10] * len(lengths_qp))
    ax.scatter(lengths_ln, times_ln, color=col_map[progname], marker="^", label=progname + " (LN)", s=[10] * len(lengths_ln))

plt.legend(loc="lower right")
plt.savefig("..\\paper\\images\\figure2.png", bbox_inches="tight")