# python detect_color.py --image pokemon_games.png
import numpy as np
import argparse
import cv2

def detectColor(color, distance):
    
    while True:
	ap = argparse.ArgumentParser()
	ap.add_argument("-i", "--image", help = "path to the image")
	args = vars(ap.parse_args())

	image = cv2.imread(args["image"])

	boundaries = [(red),(green),(purple),(yellow),(blue)]

    # create NumPy arrays from the boundaries
	for (lower, upper) in boundaries:
		lower = np.array(lower, dtype = "uint8")
		upper = np.array(upper, dtype = "uint8")

		mask = cv2.inRange(image, lower, upper)
		output = cv2.bitwise_and(image, image, mask = mask)

		# find the colors within the specified boundaries and apply
		# the mask
		returnColor=cv2.imshow("images", np.hstack([image,output]))
		if cv2.waitKey(0) & 0xFF == ord('q'):break

		return returnColor


red=[36,30,100],[43,57,192] 
green=[59,106,24],[113,204,46]
purple=[131,52,108],[173,68,142]
yellow=[63,208,244],[111,220,247]
blue=[111,61,35],[219,152,52]

distance=3
detectColor(red, distance)


# cv2.imshow("images", np.hstack([image, output]))




# colorRed=boundaries[0]
# colorGreen=boundaries[1]
# colorPurple=boundaries[2]
# colorYellow=boundaries[3]
# colorBlue=boundaries[4]















