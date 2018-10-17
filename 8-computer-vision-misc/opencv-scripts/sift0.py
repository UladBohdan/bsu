import cv2
import numpy as np

img = cv2.imread("castle0.jpg")
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
gray = cv2.imread("castle0.jpg")

sift = cv2.SIFT()
kp, des = sift.detectAndCompute(gray,None)

img_sift=cv2.drawKeypoints(gray,kp,flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

cv2.imwrite('castle0_sift_keypoints.jpg',img_sift)

surf = cv2.SURF(400)
kp, des = surf.detectAndCompute(img, None)

img_surf = cv2.drawKeypoints(img, kp)
cv2.imwrite('castle0_surf_keypoints.jpg', img_surf)
