import matplotlib.pyplot as plt
import sys


def main():
    # read data
    fn = 'output.csv'
    for arg in sys.argv:
        if '.csv' in arg:
            fn = arg

    with open(fn, 'r') as f:
        lines = f.readlines()

    # create 3d axes figure
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')

    # parse data into x,y,z for each body
    bodies = {}
    for line in lines:
        body, x, y, z = line.strip().split(',')
        x, y, z = float(x), float(y), float(z)

        if body in bodies:
            bodies[body]['x'].append(x)
            bodies[body]['y'].append(y)
            bodies[body]['z'].append(z)
        else:
            bodies[body] = {'x': [x], 'y': [y], 'z': [z]}

    # plot each body
    for body in bodies:
        ax.scatter(bodies[body]['x'], bodies[body]['y'], bodies[body]['z'], 'o')


    #  ax.set_xlim3d(-3, 10)
    #  ax.set_ylim3d(-3, 10)
    #  ax.set_zlim3d(-10, 3)

    ax.set_xlabel('x axis')
    ax.set_ylabel('y axis')
    ax.set_zlabel('z axis')

    if '-i' in sys.argv:
        plt.show()
    else:
        plt.savefig('output.png')


if __name__ == '__main__':
    main()
