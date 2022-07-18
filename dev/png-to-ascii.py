import PIL.Image
import numpy as np

ASCII_CHARS = ["#", ".", "s", "g"]

def convert_to_ascii(image):
    width, height = image.size
    im = image.convert('RGB')
    res = np.chararray((width, height))
    res[:] = '.'

    for i in range(width) :
        for j in range(height):
            r, g, b = im.getpixel((i, j))
            if (r == g == b == 0): #black is wall
                res[i, j] = '#'
            if (r == 255 and g == 0 and b == 0): # red is goal
                res[i, j] = 'g'
            if (r == 0 and g == 255 and b == 0): # green is start
                res[i, j] = 's'

    f = open("asciimap.txt", "w")
    dims = str(width) + ' ' + str(height) + '\n'
    f.write(dims)
    for i in range(width) :
        line = ''
        for j in range(height):
            char = str(res[i,j]).replace("b", '').replace("'", '')
            line += char + ' '
        line += '\n'
        f.write(line)

    f.close()



def main():
    # path = input("Enter path of PNG image:\n")
    path = "maze.png"
    try:
        image = PIL.Image.open(path)
    except:
        print (path, "is not a valid path to an image.")

    convert_to_ascii(image)
    # image.show()



if __name__ == '__main__':
    main()
