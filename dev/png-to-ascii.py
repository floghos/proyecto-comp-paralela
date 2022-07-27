import PIL.Image
import numpy as np

# ASCII_CHARS = ["#", ".", "s", "g"]

def convert_to_ascii(image, s):
    width, height = image.size
    im = image.convert('RGB')
    res = np.chararray((width, height))
    res[:] = '.'

    for i in range(width) :
        for j in range(height):
            r, g, b = im.getpixel((i, j))
            if (r < 20 and g < 20 and b < 20): #black is wall (or black enough)
                res[i, j] = '#'
            if (r > 200 and g < 20 and b < 20): # red is goal
                res[i, j] = 'g'
            if (r < 20 and g > 200 and b < 20): # green is start
                res[i, j] = 's'

    output_name = s + "_ascii.txt"
    f = open(output_name, "w")
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
    #path = "maze"
    path = input("Enter name of PNG image: \n")
    path = path + ".png"
    try:
        image = PIL.Image.open(path)
        # image.show()
        print("Converting png to ASCII...\n")
        convert_to_ascii(image, path)
        print("Done\n")
    except:
        print (path, "is not a valid path to an image.\n")



if __name__ == '__main__':
    main()
