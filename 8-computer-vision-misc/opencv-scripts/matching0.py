import cv2
import numpy as np
import cPickle

def output_matches(algo, img1, kp1, img2, kp2, matches, color=None):
    """Draws lines between matching keypoints of two images.
    Keypoints not in a matching pair are not drawn.
    Places the images side by side in a new image and draws circles
    around each keypoint, with line segments connecting matching pairs.
    You can tweak the r, thickness, and figsize values as needed.
    Args:
        img1: An openCV image ndarray in a grayscale or color format.
        kp1: A list of cv2.KeyPoint objects for img1.
        img2: An openCV image ndarray of the same format and with the same
        element type as img1.
        kp2: A list of cv2.KeyPoint objects for img2.
        matches: A list of DMatch objects whose trainIdx attribute refers to
        img1 keypoints and whose queryIdx attribute refers to img2 keypoints.
        color: The color of the circles and connecting lines drawn on the images.
        A 3-tuple for color images, a scalar for grayscale images.  If None, these
        values are randomly generated.
    """

    path = dataset + processed_postfix

    # We're drawing them side by side.  Get dimensions accordingly.
    # Handle both color and grayscale images.
    if len(img1.shape) == 3:
        new_shape = (max(img1.shape[0], img2.shape[0]), img1.shape[1]+img2.shape[1], img1.shape[2])
    elif len(img1.shape) == 2:
        new_shape = (max(img1.shape[0], img2.shape[0]), img1.shape[1]+img2.shape[1])
    new_img = np.zeros(new_shape, type(img1.flat[0]))
    # Place images onto the new image.
    new_img[0:img1.shape[0],0:img1.shape[1]] = img1
    new_img[0:img2.shape[0],img1.shape[1]:img1.shape[1]+img2.shape[1]] = img2

    # Draw lines between matches.  Make sure to offset kp coords in second image appropriately.
    r = 15
    thickness = 2
    if color:
        c = color
    for m in matches:
        # Generate random color for RGB/BGR and grayscale images as needed.
        if not color:
            c = np.random.randint(0,256,3) if len(img1.shape) == 3 else np.random.randint(0,256)
        # So the keypoint locs are stored as a tuple of floats.  cv2.line(), like most other things,
        # wants locs as a tuple of ints.
        end1 = tuple(np.round(kp1[m.trainIdx].pt).astype(int))
        if m.queryIdx >= len(kp2):
            print 'failed because {}>={}'.format(m.queryIdx, len(kp2))
        else:
            end2 = tuple(np.round(kp2[m.queryIdx].pt).astype(int) + np.array([img1.shape[1], 0]))
            cv2.line(new_img, end1, end2, c, thickness)
            cv2.circle(new_img, end1, r, c, thickness)
            cv2.circle(new_img, end2, r, c, thickness)

    cv2.imwrite('{}/{}_matches0.jpg'.format(path, algo), new_img)
    print "matches are written"
    #plt.figure(figsize=(15,15))
    #plt.imshow(new_img)
    #plt.show()

def read_images():
    img = []
    for i in range(0, sz):
        img.append(cv2.imread('{}/{}.jpg'.format(dataset, i)))
        print 'read {}/{}'.format(i, sz)
    return img

def compute(algo, img):
    detector = {
        'sift': cv2.SIFT(),
        'orb': cv2.ORB(),
        'surf': cv2.SURF(),
    }[algo]

    kp = []
    des = []
    for i in range(0, sz):
        kp0, des0 = detector.detectAndCompute(img[i], None)
        kp.append(kp0)
        des.append(des0)
        print '{} computed {}/{} len kp: {}, len des: {}'.format(algo, i, sz, len(kp[i]), len(des[i]))
    return (kp, des)

def output_data(algo, img, kp, des):
    path = dataset + processed_postfix

    for i in range(0, sz):
        new_img = cv2.drawKeypoints(img[i], kp[i])
        cv2.imwrite('{}/img{}_{}_0.jpg'.format(path, i, algo), new_img)
        new_img = cv2.drawKeypoints(img[i], kp[i], flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        cv2.imwrite('{}/img{}_{}_1.jpg'.format(path, i, algo), new_img)

        index = []
        for point in kp[i]:
            temp = (point.pt, point.size, point.angle, point.response, point.octave, point.class_id)
            index.append(temp)
        f = open('{}/img{}_{}_keypoints.txt'.format(path, i, algo), "w")
        f.write(cPickle.dumps(index))
        f.close()

        f = open('{}/img{}_{}_descriptors.txt'.format(path, i, algo), "w")
        f.write(cPickle.dumps(des[i]))
        f.close()

        print '{} output written {}/{}'.format(algo, i, sz)

def bf_match(algo, des0, des1):
    bf = {
        'sift': cv2.BFMatcher(cv2.NORM_L2, crossCheck=True),
        'orb': cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True),
        'surf': cv2.BFMatcher(cv2.NORM_L2, crossCheck=True),
    }[algo]
    matches = bf.match(des0, des1)
    matches = sorted(matches, key = lambda x:x.distance)

    print '{} matched: {} found'.format(algo, len(matches))
    return matches

def save_matches(matches, img0, kp0, img1, kp1):
    path = dataset + processed_postfix
    top = 20

    print '{} foung TOP-{} matches, image is outputed. TOP3 distances are {} {} {}'.format(algo, top, matches[0].distance, matches[1].distance, matches[2].distance)

    top_kp0 = []
    for i in range(0, top):
        top_kp0.append(kp0[matches[i].queryIdx])

    top_kp1 = []
    for i in range(0, top):
        top_kp1.append(kp1[matches[i].trainIdx])

    new_img = cv2.drawKeypoints(img0, top_kp0, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    cv2.imwrite('{}/img0_top3.jpg'.format(path), new_img)

    new_img = cv2.drawKeypoints(img1, top_kp1, flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    cv2.imwrite('{}/img1_top3.jpg'.format(path), new_img)

def bf_knn_match(algo, des0, des1):
    # drawing fails when using this function
    bf = cv2.BFMatcher()
    matches = bf.knnMatch(des0, des1, k=2)

    # Apply ratio test
    good = []
    for m,n in matches:
        if m.distance < 0.75*n.distance:
            good.append([m])

    print '{} matched & good: {} found'.format(algo, len(good))
    return good

def flann_match(des0, des1):
    FLANN_INDEX_KDTREE = 0
    FLANN_INDEX_LSH = 0
    index_params = {
        'sift': dict(algorithm = FLANN_INDEX_KDTREE, trees = 5),
        'surf': dict(algorithm = FLANN_INDEX_KDTREE, trees = 5),
        'orb': dict(algorithm = FLANN_INDEX_LSH, table_number = 6, key_size = 12, multi_probe_level = 1)
    }[algo]
    search_params = dict(checks=50)
    flann = cv2.FlannBasedMatcher(index_params, search_params)
    matches = flann.match(des0, des1)
    print 'matched with flann: {} found'.format(len(matches))
    return matches


# MAIN
dataset = "testset0"
processed_postfix = "_processed"
sz = 2
algo = 'sift'

def compute_and_match():
    img = read_images()
    kp = []
    des = []

    kp, des = compute(algo, img)
    output_data(algo, img, kp, des)

    #matches = bf_match(algo, des[0], des[1])
    matches = flann_match(des[0], des[1])
    save_matches(matches, img[0], kp[0], img[1], kp[1])

    limit_matches = min(50, len(kp[0]), len(kp[1]))
    output_matches(algo, img[0], kp[0], img[1], kp[1], matches[:limit_matches], None)

if __name__ == "__main__":
    compute_and_match()

# let's assume here we have pairs of descriptors, which are REALLY the same point in real world, but on different images.
