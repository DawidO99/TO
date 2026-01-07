#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include "include/Vector2D.h"
#include "include/Vector3D.h"
#include "include/Vector3DInheritance.h"
#include "include/Polar2DAdapter.h"
#include "include/Vector3DDecorator.h"

using namespace std;

void printSeparator(int length = 70) {
    cout << string(length, '=') << endl;
}

void printVector(const string& name, const IVector* vec) {
    vector<double> cart = vec->getComponents();
    cout << name << ":" << endl;
    cout << "  Kartezjańskie: [";
    for (size_t i = 0; i < cart.size(); i++) {
        cout << fixed << setprecision(2) << cart[i];
        if (i < cart.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    // Współrzędne biegunowe
    if (cart.size() == 2) {
        double r = sqrt(cart[0]*cart[0] + cart[1]*cart[1]);
        double angle = atan2(cart[1], cart[0]);
        cout << "  Biegunowe: r=" << fixed << setprecision(2) << r
             << ", φ=" << angle << " rad ("
             << (angle * 180.0 / M_PI) << "°)" << endl;
    } else if (cart.size() >= 3) {
        double r = sqrt(cart[0]*cart[0] + cart[1]*cart[1]);
        double angle = atan2(cart[1], cart[0]);
        cout << "  Biegunowe (XY): r=" << fixed << setprecision(2) << r
             << ", φ=" << angle << " rad ("
             << (angle * 180.0 / M_PI) << "°), z=" << cart[2] << endl;
    }
    cout << "  Długość: " << fixed << setprecision(2) << vec->abs() << endl << endl;
}

int main() {
    printSeparator();
    cout << "SYSTEM WEKTORÓW - DEMONSTRACJA" << endl;
    printSeparator();

    // Utworzenie trzech przykładowych wektorów
    Vector2D v1(3, 4);
    Vector3D v2(1, 2, 2);
    Vector3DInheritance v3(2, -1, 3);

    vector<IVector*> vectors = {&v1, &v2, &v3};
    vector<string> names = {"v1", "v2", "v3"};

    // Wyświetlenie współrzędnych
    cout << "\n--- WSPÓŁRZĘDNE WEKTORÓW ---\n" << endl;
    for (size_t i = 0; i < vectors.size(); i++) {
        printVector(names[i], vectors[i]);
    }

    // Iloczyny skalarne
    cout << "--- ILOCZYNY SKALARNE ---\n" << endl;
    for (size_t i = 0; i < vectors.size(); i++) {
        for (size_t j = i; j < vectors.size(); j++) {
            double dotProduct = vectors[i]->cdot(vectors[j]);
            cout << names[i] << " · " << names[j] << " = "
                 << fixed << setprecision(2) << dotProduct << endl;
        }
    }

    // Iloczyny wektorowe
    cout << "\n--- ILOCZYNY WEKTOROWE ---\n" << endl;
    for (size_t i = 0; i < vectors.size(); i++) {
        for (size_t j = i + 1; j < vectors.size(); j++) {
            Vector3D cross(0, 0, 0);

            if (dynamic_cast<Vector3DInheritance*>(vectors[i])) {
                cross = static_cast<Vector3DInheritance*>(vectors[i])->cross(vectors[j]);
            } else if (dynamic_cast<Vector3D*>(vectors[i])) {
                cross = static_cast<Vector3D*>(vectors[i])->cross(vectors[j]);
            } else if (dynamic_cast<Vector2D*>(vectors[i])) {
                cross = static_cast<Vector2D*>(vectors[i])->cross(vectors[j]);
            }

            vector<double> comp = cross.getComponents();
            cout << names[i] << " × " << names[j] << " = ["
                 << fixed << setprecision(2) << comp[0] << ", "
                 << comp[1] << ", " << comp[2] << "]" << endl;
        }
    }

    // Demonstracja wzorców projektowych
    cout << "\n--- WZORCE PROJEKTOWE ---\n" << endl;

    // Adapter Pattern
    cout << "1. ADAPTER PATTERN:" << endl;
    Polar2DAdapter adapter(&v1);
    cout << "   " << adapter << endl;

    // Decorator Pattern
    cout << "\n2. DECORATOR PATTERN:" << endl;
    Vector3DDecorator decorator(&v1, 5);
    cout << "   " << decorator << endl;
    cout << "   Długość: " << fixed << setprecision(2) << decorator.abs() << endl;

    cout << endl;
    printSeparator();

    return 0;
}