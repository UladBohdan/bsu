import os
from os import listdir
from os.path import isfile, join
import glob
from collections import defaultdict
import matplotlib.pyplot as plt
import numpy as np
import shutil
import math

path_to_data = "/home/parallels/poses_temp/"

output_path = "/home/parallels/poses_graphs/"

observation_threshold = 20

files = [f for f in listdir(path_to_data) if isfile(join(path_to_data, f))]
files.sort()

data_t = defaultdict(list) # for translations.
data_q = defaultdict(list) # for rotations (quaternions).

final_cameras = []

for idx, filename in enumerate(files):
	f = open(path_to_data + filename, "r")
	for line in f:
		words = line.split()
		if len(words) != 8:
			print("ALERT, must be 8 in line")
			exit(1)
		num = int(float(words[0]))
		# Camera positions. Stands for tx, ty, tz.
		data_t[num].append((float(words[1]), float(words[2]), float(words[3])))
		# Camera rotations. Stands for q1, q2, q3, q4 (a quaternion).
		data_q[num].append((float(words[4]), float(words[5]), float(words[6]), float(words[7])))		
		if idx == len(files) - 1:
			final_cameras.append(num)

# results map image ids (num-s) to list of differences with the best estimation.
# values are expected to be descending.
dist_t = defaultdict(list)
dist_q = defaultdict(list)

files = glob.glob(output_path + "*")
for f in files:
    os.remove(f)

histogram_t = defaultdict(lambda: 0)

for num, poses in data_t.iteritems():
	if len(poses) >= observation_threshold: # and num in final_cameras:
		best = poses[-1]
		for pose in poses:
			dist_t[num].append(np.linalg.norm(np.subtract(pose,best)))
		sz = len(dist_t[num])
		ox = [float(i)/sz for i in range(sz)]
		oy = dist_t[num]
		for i in range(sz):
			histogram_t[int(ox[i]*10)] += oy[i]
		plt.figure(1)
		plt.plot(ox,oy)
		plt.ylabel("distance")
		plt.xlabel("time")
		plt.savefig(output_path+"t_"+str(num))
		plt.clf()
		plt.figure(2)
		plt.plot(ox, oy)
		
plt.figure(2)
plt.ylabel("distance")
plt.xlabel("time")
plt.savefig(output_path+"a__t_total")
plt.clf()

plt.plot(histogram_t.keys(), histogram_t.values())
plt.ylabel("cumulative distance")
plt.xlabel("time")
plt.savefig(output_path+"a__t_histogram")
plt.clf()

histogram_q = defaultdict(lambda: 0)

for num, quaternions in data_q.iteritems():
	if len(quaternions) >= observation_threshold: # and num in final_cameras:
		b = quaternions[-1] # the 'best' one.
		div = math.sqrt(sum([x*x for x in b]))
		b = tuple(x/div for x in b)
		for q in quaternions:
			div = math.sqrt(sum([x*x for x in q]))
			q = tuple(x/div for x in q)
			# dist_q[num].append(1-sum([b[i]*q[i] for i in range(4)])**2)
			val = 2*sum([b[i]*q[i] for i in range(4)])**2-1
			val = min(1., max(-1., val))  # This is to verify arguments are in range.
			dist_q[num].append(math.acos(val))
		sz = len(dist_q[num])
		ox = [float(i)/sz for i in range(sz)]
		oy = dist_q[num]
		for i in range(sz):
			histogram_q[int(ox[i]*10)] += oy[i]
		plt.figure(1)
		plt.plot(ox, oy)
		plt.ylabel("distance")
		plt.xlabel("time")
		plt.savefig(output_path+"q_"+str(num))
		plt.clf()
		plt.figure(2)
		plt.plot(ox, oy)

plt.figure(2)
plt.ylabel("distance")
plt.xlabel("time")
plt.savefig(output_path+"a__q_total")
plt.clf()

plt.plot(histogram_q.keys(), histogram_q.values())
plt.ylabel("cumulative distance")
plt.xlabel("time")
plt.savefig(output_path+"a__q_histogram")
plt.clf()

