# USAGE
# python detect_color.py --image pokemon_games.png

# import the necessary packages
import numpy as np
import argparse
import cv2

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", help = "path to the image")
args = vars(ap.parse_args())

# load the image
image = cv2.imread(args["image"])

# red=[8,255,255],[8,255,255]
yellow=[0,255,255],[100,255,255] #RGB. BGR #works 
green=[0,150,0],[255,255,10] #works
green=[70,248,71],[255,255,10]
blue=[124,158,78],[255,255,138]
#BGR
# NumPy is in reverse order BGR [lower bound] [upper bound]


# Here, we are saying that all pixels in our image that have a R >= 100, B >= 15, and G >= 17 along with R <= 
# define the list of boundaries
boundaries = [
       # (yellow),
       (green)
	# (red),
	
	# ([25, 146, 190], [62, 174, 250]),
	# ([103, 86, 65], [145, 133, 128])
]

# loop over the boundaries
for (lower, upper) in boundaries:
	# create NumPy arrays from the boundaries
	lower = np.array(lower, dtype = "uint8")
	upper = np.array(upper, dtype = "uint8")

	# find the colors within the specified boundaries and apply
	# the mask
	mask = cv2.inRange(image, lower, upper)
	output = cv2.bitwise_and(image, image, mask = mask)

	# show the images
	cv2.imshow("images", np.hstack([image, output]))
	if cv2.waitKey(0) & 0xFF == ord('q'):
		break
