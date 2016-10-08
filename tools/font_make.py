import os
from PIL import Image

files = [];

for filename in os.listdir("./font_standard"):
    if filename.endswith(".bmp"):
        files.append(filename)

im = Image.new('RGB', (8 * len(files), 8), "#ffffff")

for index, file in enumerate(files):
    bitmap_char = Image.open("./font_standard/" + file)
    im.paste(bitmap_char, (8 * index, 0))

# im.show()
im.save("standard_font.bmp")
print("ok")
