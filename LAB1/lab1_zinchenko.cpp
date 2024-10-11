#include <iostream>
#include <vector>
using namespace std;

double my_left = 0;
double my_right = 1;

double recurrent_u(double left_u, double middle_u, double right_u, double h, double dt);
double zero_edge(double h, int counter);
double left_edge(double dt, int counter);
double right_edge(double dt, int counter);
void algorithm(double step_x, double step_t);

int main()
{
    algorithm(0.1, 0.1);
    cout << endl;
    algorithm(0.1, 0.001);

    return 0;
}

void algorithm(double step_x, double step_t) {
    int n_x = (my_right - my_left) / step_x + 1;
    int n_t = (my_right - my_left) / step_t + 1;
    vector<vector<double>> answer(n_x);
    for (int i = 0; i < n_x; i++) {
        answer[i].push_back(zero_edge(step_x, i));
    }
    for (int i = 0; i < n_t; i++) {
        for (int j = 1; j < (n_x - 1); j++) {
            answer[j].push_back(recurrent_u(answer[j - 1][i], answer[j][i], answer[j + 1][i], step_x, step_t));
        }
        answer[0].push_back(left_edge(step_t, i));
        answer[n_x - 1].push_back(right_edge(step_t, i));
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

double recurrent_u(double left_u, double middle_u, double right_u, double h, double dt) {
    return (dt * (left_u - 2 * middle_u + right_u) / (h * h) + dt * h * (h + 1) - 2 * dt * dt + middle_u);
}

double zero_edge(double h, int counter) {
    return 0;
}

double left_edge(double dt, int counter) {
    return 0;
}

double right_edge(double dt, int counter) {
    return (2 * dt * (counter + 1));
}
