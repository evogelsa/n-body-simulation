import matplotlib.pyplot as plt
import sys


def main():
    # read data
    with open('output.csv', 'r') as f:
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


    if '-i' in sys.argv:
        plt.show()
    else:
        plt.savefig('output.png')


if __name__ == '__main__':
    main()
