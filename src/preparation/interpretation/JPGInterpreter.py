
from PIL import Image
import numpy as np


class JPGInterpreter:

    def __init__(self, filepath, print_width=None, print_height=None):
        self.print_width = print_width
        self.print_height = print_height
        image = Image.open(filepath, 'r')
        self.matrix = np.array(image.getdata())
        self.width = image.size[0]
        self.height = image.size[1]
        if self.print_width is None:
            self.print_width = self.width
        if self.print_height is None:
            self.print_height = self.height
        self.matrix = self.matrix.reshape((self.height, self.width, 3))

    # Samples the given image at the given sx and sy step values and returns the pen position value
    # False for pen in up position and True for pen in down position.
    def sample(self, sx, sy):
        x = int(round(sx / self.print_width * self.width))
        y = int(round(sy / self.print_height * self.height))
        rgb = self.matrix[y, x]
        greyscale = (0.3 * rgb[0]) + (0.59 * rgb[1]) + (0.11 * rgb[2])
        # distribution sample
        probability = greyscale / 256.0
        probability = self.distribution(probability)
        return np.random.uniform() > probability

    def distribution(self, x):
        return (-(x - 1) ** 4) + 1
