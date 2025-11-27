#include <stdexcept>
#include <cmath>
#include <iomanip>

// Уверен, что это можно сделать значительно качественнее, но дедлайн близко,
// поэтому спагетти код >:)

void SolveQuadratic(int a, int b, int c) { 
    if (!a && !b && !c) {
        std::cout << "infinite solutions";
        return;
    }
    
    if (!a && !b) {
        std::cout << "no solutions";
        return;
    }

    std::cout << std::setprecision(6);

    if (!a) {
        std::cout << (static_cast<double>(-c) / b);
        return;
    }

    if (!b) {
        if (static_cast<double>(-c) / a < 0) {
            std::cout << "no solutions";
            return;
        }

        double root = std::sqrt(static_cast<double>(-c) / a);
        
        if (root == 0) {
            std::cout << root;
        } else {
            std::cout << -root << " " << root;
        }
        
        return;
    }

    double d = static_cast<double>(b) * b - 4.0 * a * c;
    double x1 = 0.0, x2 = 0.0;

    if (d < 0) {
        std::cout << "no solutions";
        return;
    }

    if (d > 0) {
        x1 = ((-b - std::sqrt(d)) / (2.0 * a));
        x2 = ((-b + std::sqrt(d)) / (2.0 * a));

        if (x1 > x2) {
            std::cout << x2 << " " << x1;
        } else {
            std::cout << x1 << " " << x2;
        } 
        return;
    } 

    std::cout << -b / (2.0 * a);
}
