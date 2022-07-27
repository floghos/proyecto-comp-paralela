import PIL.Image
#import numpy as np


s = input("Enter the name of the file: ")
s += ".png"

try:
    image = PIL.Image.open(s)
    image.show()
except:
    print (s, "is not a valid path to an image.")


