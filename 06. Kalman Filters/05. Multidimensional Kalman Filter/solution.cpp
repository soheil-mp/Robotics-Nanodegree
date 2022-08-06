#include <iostream>
#include <math.h>
#include <tuple>
#include "Core" // Eigen Library
#include "LU"   // Eigen Library

using namespace std;
using namespace Eigen;

float measurements[3] = { 1, 2, 3 };

tuple<MatrixXf, MatrixXf> kalman_filter(MatrixXf x, MatrixXf P, MatrixXf u, MatrixXf F, MatrixXf H, MatrixXf R, MatrixXf I) {

    for (int n = 0; n < sizeof(measurements) / sizeof(measurements[0]); n++) {

        // Measurement Update
        MatrixXf Z(1, 1);
        Z << measurements[n];

        MatrixXf y(1, 1);
        y << Z - (H * x);

        MatrixXf S(1, 1);
        S << H * P * H.transpose() + R;

        MatrixXf K(2, 1);
        K << P * H.transpose() * S.inverse();

        x << x + (K * y);

        P << (I - (K * H)) * P;

        // Prediction
        x << (F * x) + u;
        P << F * P * F.transpose();
    }

    return make_tuple(x, P);
}

int main() {

    // Initial state (location and velocity)
    MatrixXf x(2, 1);
    x << 0,
         0;
    
    // Initial Uncertainty
    MatrixXf P(2, 2);
    P << 100, 0,
         0, 100;
    
    // External Motion
    MatrixXf u(2, 1);
    u << 0,
         0;

    // Next State Function
    MatrixXf F(2, 2);
    F << 1, 1,
         0, 1;

    // Measurement Function
    MatrixXf H(1, 2);
    H << 1,
         0;
    
    // Measurement Uncertainty
    MatrixXf R(1, 1);
    R << 1;
    
    // Identity Matrix
    MatrixXf I(2, 2);
    I << 1, 0,
         0, 1;

    tie(x, P) = kalman_filter(x, P, u, F, H, R, I);
    cout << "x= " << x << endl;
    cout << "P= " << P << endl;

    return 0;
}
