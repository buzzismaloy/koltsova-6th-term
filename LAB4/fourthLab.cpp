#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double const EPSILON{0.00001};

double get_left_edge() {
    return 1.0;
}

double get_right_edge(){
    return 4.7;
}

double get_zero_edge(double j, double h){
    return 2*(j-1) * h - 1;
}

void algorithm_iteration(int n,double h, double dt){
    int size_j{static_cast<int>(1/h) + 1}, size_n{static_cast<int>(1 / dt)};

    std::vector<std::vector<double>> vec(size_n + 1, std::vector<double>(size_j));

    for(int i = 0; i < size_j; ++i) vec[0][i] = get_zero_edge(i,h);

    while(true){
        for(int i = 1; i < size_j - 1; ++i)
            vec[n+1][i] = ((vec[n][i+1] - 2 * vec[n][i] + vec[n][i-1])/ (h * h)) * dt - dt +
                2 * (i - 1) * h * dt - ((vec[n][i] - vec[n][i - 1]) / h) * dt + vec[n][i];

        vec[n+1][0] = get_left_edge();
        vec[n+1][size_j - 1] = get_right_edge();

        double sum{};
        for(int i = 0; i < size_j - 1; ++i) sum += (vec[n+1][i] - vec[n][i]) * (vec[n+1][i] - vec[n][i]);

        if(std::sqrt(h * sum) <= EPSILON){
            std::cout<<"h = "<<h<<"; dt = "<<dt<<'\n'<<"number of iterations: "<<n<<"\n\n";
            std::cout.fill(' ');
            std::cout<<std::setprecision(5);
            for(int i = 0; i < n+2; ++i){
                for(int j = 0; j < size_j; ++j){
                    std::cout<<vec[i][j]<<std::fixed<<' ';
                }

                std::cout<<'\n';
            }

            return;
        }
        else{
            n++;
            if(n == size_n){
                std::cout<<"Unable to solve\n";
                return;
            }
        }
    }
    

}

int main(){
    int n{0};
    double h{0.1}, dt{0.001};
    double h1{0.01}, dt1{0.00001}, dt2{0.0001};
    //algorithm_iteration(n, h, dt);
    algorithm_iteration(n, h1, dt1);
    //algorithm_iteration(n, h, dt2);
    return 0;
}