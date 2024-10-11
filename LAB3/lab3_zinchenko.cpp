#include <vector>
#include <iostream>

using namespace std;
double h = 0.1;
double delT = 0.1;

int Nx = static_cast<int>((1 - 0) / h) + 1; //Nx
int Nt = static_cast<int>((1 - 0) / delT) + 1; //Nt

void arrayPrint(vector<vector <double>> u)
{
    cout.fill(' ');
    cout.precision(4);
    for (int i = 0; i < Nt; i++) {
        for (int j = 0; j < Nx; j++)
            cout << u[i][j] << fixed << "\t";
        cout << endl;
    }
}

int main()
{
    vector<vector <double>> u(Nt, vector<double>(Nx, 0));

    for (int j = 0; j < Nx; j++) {
        u[0][j] = 3 * j * h;
    }

    for (int n = 0; n < Nt - 1; n++)
    {
        u[n + 1][0] = 3 * (n+1) * delT;

        for (int j = 1; j < Nx; j++)
        {
            double a = 6 * h + u[n][j] * h / delT + u[n + 1][j - 1];
            u[n + 1][j] = a / (h / delT + 1);
        }
    }

    arrayPrint(u);

    return 0;
}