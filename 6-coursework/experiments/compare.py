import cv2
import numpy as np
import time
import matplotlib.pyplot as plt

# compare: time, number of keypoints, time per one keypoint, abilities to match
# and which matchers suits better.
# how detectors react on image rotation / scale / brightness.

num_best_matches = 20
cross_check = False

FLANN_INDEX_KDTREE = 1
FLANN_INDEX_LSH = 6

# FLANN sets of options
# SIFT, SURF, etc.
flann_params1 = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
# ORB
flann_params2 = dict(algorithm = FLANN_INDEX_LSH,
                    table_number = 6, #6 12
                    key_size = 12,     #12 20
                    multi_probe_level = 1) #1 2

current_dataset = ""

def run_for_images(dataset, image1, image2):

    runs = [("SIFT",        cv2.xfeatures2d.SIFT_create(),          cv2.xfeatures2d.SIFT_create(),                      cv2.NORM_L2,        flann_params1),
            ("SURF",        cv2.xfeatures2d.SURF_create(),          cv2.xfeatures2d.SURF_create(),                      cv2.NORM_L2,        flann_params1),
            ("BRISK",       cv2.BRISK_create(),                     cv2.BRISK_create(),                                 cv2.NORM_HAMMING,   flann_params2),
            ("ORB",         cv2.ORB_create(nfeatures=3000),         cv2.ORB_create(),                                   cv2.NORM_HAMMING,   flann_params2),
            #("FAST+ORB",    cv2.FastFeatureDetector_create(),       cv2.ORB_create(),                                   cv2.NORM_HAMMING,   flann_params2),
            ("AKAZE",       cv2.AKAZE_create(),                     cv2.AKAZE_create(),                                 cv2.NORM_HAMMING,   flann_params2),
            ("CenSurE+BRIEF",  cv2.xfeatures2d.StarDetector_create(),  cv2.xfeatures2d.BriefDescriptorExtractor_create(),  cv2.NORM_HAMMING,   flann_params2)]

    plt_legends_500 = []
    plt_legends_20 = []

    for (name, detector, extractor, norm, flann_params) in runs:

        img1_src = cv2.imread(image1)
        img2_src = cv2.imread(image2)

        img1 = cv2.resize(img1_src, (640 * img1_src.shape[1] / img1_src.shape[0], 640))
        img2 = cv2.resize(img2_src, (640 * img2_src.shape[1] / img2_src.shape[0], 640))
        #print "IMAGE SIZES: {}  {}".format(img1.shape[:2], img2.shape[:2])

        gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
        gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)

        start_detection = time.time()
        kp1 = detector.detect(gray1)
        kp2 = detector.detect(gray2)
        detection_time = (time.time() - start_detection)

        print " {}  {} {} {:.4f} {}".format(name, len(kp1), len(kp2), detection_time, detection_time / (len(kp1) + len(kp2)))

        start_computation = time.time()
        kp1, descr1 = extractor.compute(gray1, kp1)
        kp2, descr2 = extractor.compute(gray2, kp2)
        computation_time = (time.time() - start_computation)

        print "    computing:  {:.4f}  {}    {} {}".format(computation_time, computation_time / (len(kp1) + len(kp2)), len(descr1), len(descr2))

        print "    for TABLE 1:"
        print "{} & {} & {:.4f} & {:.7f} & {} & {:.4f} & {:.7f}".format(name, (len(kp1) + len(kp2)) / 2, detection_time, detection_time / (len(kp1) + len(kp2)), name, computation_time, computation_time / (len(kp1) + len(kp2)))

        cv2.drawKeypoints(gray1, kp1, img1)
        cv2.imwrite("out/" + dataset + "_" + name + "_keypoints_1.jpg", img1)
        cv2.drawKeypoints(gray2, kp2, img2)
        cv2.imwrite("out/" + dataset + "_" + name + "_keypoints_2.jpg", img2)

        # ok let's try different matchers

        # BruteForce with crossCheck
        matcher = cv2.BFMatcher(norm, crossCheck=True)
        start_matching = time.time()
        matches = matcher.match(descr1, descr2)
        bf1_num_matches = len(matches)
        bf1_matching_time = time.time() - start_matching
        matches = sorted(matches, key = lambda x:x.distance)
        print "    BF crossCheck matching:  {}  {:.4f}".format(len(matches), bf1_matching_time)
        best_matches = matches[:num_best_matches]

        plt.figure(1)
        line, = plt.plot([m.distance / best_matches[-1].distance for m in best_matches], label = name)
        plt_legends_20.append(line)

        plt.figure(2)
        matches_500 = matches[:250]
        line, = plt.plot([m.distance / matches_500[-1].distance for m in matches_500], label = name)
        plt_legends_500.append(line)

        img3 = cv2.drawMatches(img1, kp1, img2, kp2, best_matches, None, flags = 2)
        cv2.imwrite("out/" + dataset + "_" + name + "_bf_crossCheck_matches.jpg", img3)

        # BruteForce without crossCheck with Lowes ratio
        matcher = cv2.BFMatcher(norm, crossCheck=False)
        start_matching = time.time()
        matches = matcher.knnMatch(descr1, descr2, k=2)
        bf2_matching_time = time.time() - start_matching
        print "    BF knn        matching:  {}  {:.4f}".format(len(matches), bf2_matching_time)

        good = []
        for m,n in matches:
            if m.distance < 0.75*n.distance:
                good.append([m])
        print "              good matches:   {}".format(len(good))
        bf2_num_matches = len(good)

        best_matches = good[:num_best_matches]

        img3 = cv2.drawMatchesKnn(img1, kp1, img2, kp2, best_matches, None, flags=2)
        cv2.imwrite("out/" + dataset + "_" + name + "_bf_knn_matches.jpg", img3)

        # FLANN-based
        matcher = cv2.FlannBasedMatcher(flann_params, dict())
        if norm == cv2.NORM_L2:
            descr1 = np.asarray(descr1, np.float32)
            descr2 = np.asarray(descr2, np.float32)
        elif norm == cv2.NORM_HAMMING:
            descr1 = np.asarray(descr1, np.uint8)
            descr2 = np.asarray(descr2, np.uint8)
        start_matching = time.time()
        matches = matcher.knnMatch(descr1, descr2, k=2)
        flann_matching_time = time.time() - start_matching
        print "    FLANN knn     matching:  {}  {:.4f}".format(len(matches), flann_matching_time)
        matchesMask = [[0,0] for i in xrange(len(matches))]
        # ratio test as per Lowe's paper
        best_matches = []
        for i,m_n in enumerate(matches):
            if len(m_n) != 2:
                continue
            (m, n) = m_n
            if m.distance < 0.7*n.distance:
                best_matches.append([m])
        flann_num_matches = len(best_matches)
        draw_params = dict(matchColor = (0,255,0),
                           singlePointColor = (255,0,0),
                           #matchesMask = matchesMask,
                           flags = 0)
        img3 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,best_matches[:num_best_matches],None,**draw_params)
        cv2.imwrite("out/" + dataset + "_" + name + "_flann_knn_matches.jpg", img3)

        print "    for TABLE 2:"
        print "{} & {} & {:.4f} & {} & {:.4f} & {} & {:.4f}".format(name, bf1_num_matches, bf1_matching_time, bf2_num_matches, bf2_matching_time, flann_num_matches, flann_matching_time)

    global current_dataset
    if current_dataset == "swiss-church":
        current_dataset = "church"

    plt.figure(1)
    plt.title(current_dataset + " best 20")
    plt.legend(handles=plt_legends_20, loc = 4)
    plt.savefig("graphs/" + current_dataset + "_top20.jpg")
    plt.clf()

    plt.figure(2)
    plt.title(current_dataset + " best 250")
    plt.legend(handles=plt_legends_500, loc = 4)
    plt.savefig("graphs/" + current_dataset + "_top250.jpg")
    plt.clf()

datasets = [#("graffiti", "png"),
            ("ellis", "jpg"),
            ("swiss-church", "jpg"),
            ("fountain", "png"),
            ("grass", "jpg")]

for (name, ext) in datasets:
    print "{}   ---------------------------------------".format(name.upper())
    current_dataset = name
    run_for_images(name, "images/" + name + "0." + ext, "images/" + name + "1." + ext)
