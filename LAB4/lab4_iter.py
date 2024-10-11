import math


e = 0.00001


def U(j, n, h, dt, uj_p1, uj, uj_m1):
    return dt * ((uj_p1 - 2 * uj + uj_m1) / (h * h) - (uj+uj_m1)/h) + (dt*6*(j-1)*(j-1)*h*h - dt*12*(j-1)*h) + uj


def tU(j, n, h, dt):
    return 6*((j)*(j)*h*h) - 12*(j)*h


def x0U(j, n, h, dt):
    return 1


def x1U(j, n, h, dt):
    return 4.7


def f(n, h, dt):
    N_j = int((1.0 - 0.0) / h) + 1
    N_n = int((1.0 - 0.0) / dt)

    u = [0] * (N_n + 1)
    for i in range(N_n + 1):
        u[i] = [0] * (N_j)
    
    for j in range(N_j):
        u[0][j] = tU(j, 0, h, dt)

    while True:
        for j in range(1, N_j - 1):
            u[n+1][j] = U(j, n, h, dt, u[n][j+1], u[n][j], u[n][j-1])
        u[n+1][0] = x0U(1, n, h, dt)
        u[n+1][N_j - 1] = x1U(N_j, n, h, dt)

        s = 0
        for j in range(N_j - 1):
            s += pow(u[n+1][j] - u[n][j], 2)

        if math.sqrt(h*s) <= e:
            print(f'h = {h}, dt = {dt}')
            print(n)
            for i in range(n+2):
                for j in range(N_j):
                    print(round(u[i][j], 3), end='  ')
                print()
            return 0
        else:
            n += 1
            if n == N_n:
                print('No')
                return 0


f(0, 0.01, 0.00001)
print()
# f(0, 0.01, 0.00001)