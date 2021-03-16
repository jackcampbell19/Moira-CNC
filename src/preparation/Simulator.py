from random import randint
from time import sleep

import matplotlib.pyplot as plt
import math

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

        plt.gca().invert_yaxis()
        plt.plot(0, 0, 'g.')
        plt.plot(0, 4000, 'g.')
        plt.plot(4000, 4000, 'g.')
        plt.plot(4000, 0, 'g.')
        travel = 0
        for i in range(len(coordinates) - 1):
            x0, y0 = coordinates[i][0], coordinates[i][1]
            x1, y1 = coordinates[i + 1][0], coordinates[i + 1][1]
            if coordinates[i + 1][2] > 0 and coordinates[i][2] > 0:
                travel += math.sqrt((x1 - x0) ** 2 + (y1 - y0) ** 2)
            plt.plot([x0, x1], [y0, y1], 'b-' if (coordinates[i + 1][2] == 0 and coordinates[i][2] == 0) else 'r-')
        plt.draw()
        print(f"Travel distance: {travel}")
        plt.pause(100)


s = Simulator("../../tst/runtime/shapes.mi")
s.run()
