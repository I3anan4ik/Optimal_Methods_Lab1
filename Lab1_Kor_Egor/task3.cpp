#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
#include "functions.h"
#include "function.h"

struct FuncInfo {
    std::string name;
    std::function<double(double)> f;
    double a0, b0;
    bool maximize;
};

int main() {
    std::vector<FuncInfo> funcs = {
        {"foo1", foo1, -3.0, 0.0, false},
        {"foo2", foo2, -4.0, 0.0, false},
        {"foo3", foo3, -1.0, 3.0, true},
        {"foo4", foo4, -4.0, 1.0, false},
        {"foo5", foo5, -2.0, 0.0, false},
        {"foo6", foo6,  0.0, 2.0, false},
    };

    const double eps = 1e-6;
    const int N_H = 40;

    for (const auto& fi : funcs) {
        std::string fname = "n_vs_h_" + fi.name + ".csv";
        std::ofstream out(fname);
        out << "h;uniform;local;dihotomia;golden;fibonacci\n";
        out << std::fixed << std::setprecision(6);

        double H_max = fi.b0 - fi.a0;
        double H_min = 0.01;

        for (int i = 0; i < N_H; ++i) {
            double t = static_cast<double>(i) / (N_H - 1);
            double h = H_min * std::pow(H_max / H_min, t);
            double a = fi.a0;
            double b = fi.a0 + h;
            if (b > fi.b0) b = fi.b0;

            auto f = [&](double x) { return fi.maximize ? -fi.f(x) : fi.f(x); };

            int n_uniform = 0, n_local = 0, n_diho = 0, n_gold = 0, n_fib = 0;
            min_uniform_search(a, b, eps, f, nullptr, &n_uniform);
            min_local        (a, b, eps, f, nullptr, &n_local);
            min_dihotomia    (a, b, eps, f, nullptr, &n_diho);
            min_golden_ration(a, b, eps, f, nullptr, &n_gold);
            min_fibbonachi   (a, b, eps, f, nullptr, &n_fib);

            out << h << ";" << n_uniform << ";" << n_local << ";"
                << n_diho << ";" << n_gold << ";" << n_fib << "\n";
        }
        out.close();
        std::cout << "Saved " << fname << "\n";
    }
    return 0;
}