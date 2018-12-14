# python detect_color.py --image pokemon_games.png
import numpy as np
import argparse
import cv2


def detectColor():
	red=[36,30,100],[43,57,192] 
	green=[59,106,24],[113,204,46]
	purple=[131,52,108],[173,68,142]
	yellow=[63,208,244],[111,220,247]
	blue=[111,61,35],[219,152,52]

    #initial states of

	while True:
		ap = argparse.ArgumentParser()
    	ap.add_argument("-i", "--image", help = "path to the image")
    	args = vars(ap.parse_args())
    	image = cv2.imread(args["image"])
    	boundaries = [(green),(blue),(red),(yellow),(purple)]

    	for (lower, upper) in boundaries:
    		lower = np.array(lower, dtype = "uint8")
    		upper = np.array(upper, dtype = "uint8")

    		mask = cv2.inRange(image, lower, upper)
    		output = cv2.bitwise_and(image, image, mask = mask)

    		pegs=[1,2,3]

    		if output==boundaries[0]:
    			greenBlock=1
    			peg=pegs[0]
    		elif output==boundaries[1]:
    			blueBlock=2
    			peg=pegs[0]
    		elif output==boundaries[2]:
    			redBlock=3
    			peg=pegs[0]
    		elif output==boundaries[3]:
    			yellowBlock=4
    			peg=pegs[0]
    		elif output==pboundaries[4]:
    			purpleBlock=5
    			peg=pegs[0]

    		return peg


    		# # pegIdentifier=cv2.imshow("images", np.hstack([image,output]))

    		# if cv2.waitKey(0) & 0xFF == ord('q'):
    		# 	break















