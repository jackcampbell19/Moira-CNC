from random import randint
from time import sleep

import matplotlib.pyplot as plt

class Simulator:

    def __init__(self, path):
        self.path = path

    def run(self):
        plt.figure(figsize=(8, 8))
        plt.ion()
        coordinates = [[0, 0, 0]]
        file = open(self.path)
        for line in file.readlines():
            if line.startswith('c'):
                spline = line[2:-1].split(',')
                coord = [coordinates[-1][0], coordinates[-1][1], coordinates[-1][2]]
                for x in range(3):
                    if spline[x].startswith('+') or spline[x].startswith('-'):
                        coord[x] += int(spline[x])
                    else:
                        coord[x] = int(spline[x])
                coordinates.append(coord)
        plt.show()
        for j in range(len(coordinates) - 1):
            plt.plot(0, 0, 'g.')
            plt.plot(0, 8000, 'g.')
            plt.plot(8000, 8000, 'g.')
            plt.plot(8000, 0, 'g.')
            for i in range(0, j + 1):
                x0, y0 = coordinates[i][0], coordinates[i][1]
                x1, y1 = coordinates[i + 1][0], coordinates[i + 1][1]
                plt.plot([x0, x1], [y0, y1], 'b-' if (coordinates[i + 1][2] == 0 and coordinates[i][2] == 0) else 'r-')
            plt.draw()
            plt.pause(0.001)
            plt.clf()
        sleep(10)


s = Simulator("../../tst/runtime/7-shapes.mi")
s.run()
