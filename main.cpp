//
//  main.cpp
//  lab1
//
//  Created by Andrew on 12/8/17.
//  Copyright © 2017 Andrew Golovenko. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void print(vector<vector<double>> A) {
    int n = static_cast<int>(A.size());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << A[i][j] << "\t";
            if (j == n - 1) {
                cout << "| ";
            }
        }
        cout << "\n";
    }
    cout << endl;
}

vector<double> gauss(vector<vector<double>> A) {
    int n = static_cast<int>(A.size());
    
    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        double maxEl = abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(A[k][i]) > maxEl) {
                maxEl = abs(A[k][i]);
                maxRow = k;
            }
        }
        
        // Swap maximum row with current row (column by column)
        for (int k = i; k < n + 1; k++) {
            double tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        
        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            double c = -A[k][i]/A[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    A[k][j] = 0;
                } else {
                    A[k][j] += c * A[i][j];
                }
            }
        }
    }
    
    // Solve equation Ax=b for an upper triangular matrix A
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; k--) {
            A[k][n] -= A[k][i] * x[i];
        }
    }
    return x;
}

int main() {
    int n;
    cout << "Size: " << endl;
    cin >> n;
    
    vector<double> line(n + 1, 0);
    vector<vector<double>> A(n, line);
    
    // Input
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "]: " << endl;
            cin >> A[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << "A[" << i << "] = " << endl;
        cin >> A[i][n];
    }
    print(A);
    
    vector<double> x(n);
    x = gauss(A);
    
    cout << "Result:\t";
    for (int i=0; i<n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}
