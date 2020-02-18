from PIL import Image

for i in range(10):
	filename = str(i)+".png"

	image = Image.open(filename)
	pixels = image.load()

	filename = str(i)+".bin"
	outfile = open(filename, "wb")

	for y in range(16):
		for x in range(16):
			outfile.write(chr(pixels[x,y][0]))
