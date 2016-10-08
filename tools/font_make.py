import sys
from PIL import Image, ImageFont, ImageDraw

print ('Number of arguments:', len(sys.argv), 'arguments.')
print ('Argument List:', str(sys.argv))


#im = Image.open("test.bmp")
im = Image.new('RGB', (100, 100), "#ffffff")

draw = ImageDraw.Draw(im)

# # use a bitmap font
# font = ImageFont.load("arial.pil")

# draw.text((10, 10), "hello", font=font)

# use a truetype font
font = ImageFont.truetype("Early GameBoy.ttf", 15)

draw.text((0, 0), "world", font=font, fill=128)

im.show()