import matplotlib.pyplot as plt
if __name__ == '__main__':
    fin = open("node_list.txt")
    node_size = int(fin.readline())
    node_x, node_y = [], []
    for i in range(node_size):
        a,b = map(int, fin.readline().split(' '))
        node_x.append(a)
        node_y.append(b)
    #print(node_x, node_y)
    plt.ioff()
    plt.scatter(node_x, node_y)
    
    fout = open('convex_nodes.txt')
    convex_size = int(fout.readline())
    convex_x, convex_y = [], []
    for i in range(convex_size):
        a,b = map(int, fout.readline().split(' '))
        convex_x.append(a)
        convex_y.append(b)
    convex_x.append(convex_x[0])
    convex_y.append(convex_y[0])
    plt.plot(convex_x, convex_y)
    plt.show()
    #input()