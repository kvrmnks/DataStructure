import matplotlib.pyplot as plt
import numpy as np
if __name__ == '__main__':
    file1 = open('data.in', 'r')
    file2 = open('rectOut.out', 'r')
    n = int(file1.readline())
    point = []
    for i in range(n):
        s = file1.readline().split(' ')
        pa = float(s[0])
        pb = float(s[1])
        point.append((pa, pb))
    point.append(point[0])
    # print()
    p = np.array(point)
    print(p.shape)
    plt.ion()
    plt.plot(p[:,0], p[:,1])
    input('press any key to get monotone')
    while file2.readable():
        s = file2.readline().split(' ')
        if len(s) < 2:
            break
        print(s)
        x = int(s[0])
        y = int(s[1])
        plt.plot([p[x][0],p[y][0]], [p[x][1], p[y][1]])
    input('press any key to get triangular')
    file3 = open('triangular.out')
    while file3.readable():
        s = file3.readline().split(' ')
        if len(s) < 2:
            break
        print(s)
        x = int(s[0])
        y = int(s[1])
        plt.plot([p[x][0],p[y][0]], [p[x][1], p[y][1]])       
    input('press any key to quit')
    # plt.show()