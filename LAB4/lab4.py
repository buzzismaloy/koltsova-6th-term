import copy
import math


def algorithm(n, dt, h):
    Nx = int((1 - 0) / h) + 1
    U_n = [0 for _ in range(Nx)]
    U_n_1 = [0 for _ in range(Nx)]
    alpha = [0 for _ in range(Nx)]
    beta = [0 for _ in range(Nx)]

    # начальное условие
    for j in range(Nx):
        U_n[j] = 1

    while True:
        alpha[0] = 0
        beta[0] = 3

        for j in range(1, Nx - 1):
            alpha[j] = round((dt / h ** 2)
                             / ((1 + dt / h + (2 * dt) / (h ** 2)) + (-dt / h - dt / (h ** 2)) * alpha[j - 1]), 3)
            beta[j] = round(((U_n[j] + dt) - (-dt / h - dt / (h ** 2)) * beta[j - 1])
                            / ((1 + dt / h + (2 * dt) / (h ** 2)) + (-dt / h - dt / (h ** 2)) * alpha[j - 1]), 3)

        U_n_1[Nx - 1] = 5.7

        for j in range(Nx - 2, -1, -1):
            U_n_1[j] = round(alpha[j] * U_n_1[j + 1] + beta[j], 3)

        if math.sqrt(h * sum([(U_n_1[j] - U_n[j]) ** 2 for j in range(Nx)])) <= 0.0001:
            break
        else:
            U_n = copy.deepcopy(U_n_1)

    [print(elem, end=' ') for elem in U_n_1]


def main():
    algorithm(n=0, h=0.1, dt=0.1)
    print()
    algorithm(n=0, h=0.1, dt=0.01)
    print()
    algorithm(n=0, h=0.1, dt=0.001)
    print()
    algorithm(n=0, h=0.01, dt=0.1)
    print()
    algorithm(n=0, h=0.01, dt=0.01)
    print()
    algorithm(n=0, h=0.01, dt=0.001)


if __name__ == '__main__':
    main()
