import pandas as pd
import matplotlib.pyplot as plt
import os

funcs = ["foo1", "foo2", "foo3", "foo4", "foo5", "foo6"]
methods = ["uniform", "local", "dihotomia", "golden", "fibonacci"]
colors = {"uniform": "tab:red", "local": "tab:orange", "dihotomia": "tab:green",
          "golden": "tab:blue", "fibonacci": "tab:purple"}
markers = {"uniform": "o", "local": "s", "dihotomia": "^", "golden": "D", "fibonacci": "v"}

for fn in funcs:
    path = f"n_vs_h_{fn}.csv"
    if not os.path.exists(path):
        print(f"skip {path}")
        continue
    df = pd.read_csv(path, sep=";")

    plt.figure(figsize=(9, 6))
    for m in methods:
        plt.plot(df["h"], df[m], label=m, color=colors[m], marker=markers[m], markersize=4)
    plt.xlabel("Ширина отрезка h")
    plt.ylabel("Число итераций n")
    plt.title(f"n(h) для {fn} (все методы, лог-шкала)")
    plt.xscale("log"); plt.yscale("log")
    plt.grid(True, which="both", ls="--", alpha=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"n_vs_h_{fn}_log.png", dpi=150)
    plt.close()

    plt.figure(figsize=(9, 6))
    for m in methods[1:]:
        plt.plot(df["h"], df[m], label=m, color=colors[m], marker=markers[m], markersize=4)
    plt.xlabel("Ширина отрезка h")
    plt.ylabel("Число итераций n")
    plt.title(f"n(h) для {fn} (без uniform)")
    plt.grid(True, ls="--", alpha=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"n_vs_h_{fn}_linear.png", dpi=150)
    plt.close()

    print(f"Saved plots for {fn}")