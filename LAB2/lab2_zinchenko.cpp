#include <iostream>
#include <vector>
using namespace std;

double my_left = 0;
double my_right = 1;

double zero_edge();
double right_edge(double, int);
void algorithm(double, double);


int main()
{
    algorithm(0.1, 0.1);
    cout << endl;
    algorithm(0.1, 0.001);

    return 0;
}

double zero_edge() {
    return 0;
}

double right_edge(double dt, int counter) {
    return (2 * dt * (counter + 1));
}

void algorithm(double step_x, double step_t) {
    int n_x = (my_right - my_left) / step_x + 1;
    int n_t = (my_right - my_left) / step_t + 1;

    double a_or_c = -step_t / (step_x * step_x);
    double b_j = 1 + 2 * (-a_or_c);

    vector<vector<double>> answer(n_x);
    vector<double> alphas(n_x);
    vector<double> betas(n_x);

    for (int i = 0; i < n_x; i++) {
        answer[i].push_back(zero_edge());
    }

    for (int i = 0; i < n_t; i++) {
        alphas[0] = 0;
        betas[0] = 0 * (i + 1) * step_t;
        for (int j = 1; j < n_x - 1; j++) {
            alphas[j] = (-a_or_c) / (b_j + a_or_c * alphas[j - 1]);
            betas[j] = ((answer[j].back() - 0 * step_t) - a_or_c * betas[j - 1]) / (b_j + a_or_c * alphas[j - 1]);
        }
        answer[n_x - 1].push_back(right_edge(step_t, i));
        for (int j = n_x - 2; j >= 0; j--) {
            answer[j].push_back(alphas[j] * answer[j + 1].back() + betas[j]);
        }
    }
    cout.fill(' ');
    cout.precision(6);
    for (int i = 0; i < n_t; i++) {
        for (int j = 0; j < n_x - 1; j++) {
            cout << answer[j][i] << fixed << "  ";
        }
        cout << answer[n_x - 1][i] << fixed << endl;
    }
}
