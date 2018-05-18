from matplotlib import pyplot as plt
import csv
import numpy as np

times1 = []
thetas1 = []
times2 = []
thetas2 = []

hit_break = False

with open('../../txt/data.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        if (len(thetas1) > 0 and round(float(row[1])) < thetas1[-1]):
            hit_break = True
        if (not hit_break):
            times1.append(int(row[0]))
            thetas1.append(round(float(row[1])))
        else:
            times2.append(int(row[0]))
            thetas2.append(round(float(row[1])))

fig = plt.figure()

ax = fig.add_subplot(1, 1, 1)
ax.spines['right'].set_position('center')
ax.spines['top'].set_position('center')

line1, = plt.plot(times1,thetas1,'b')
line2, = plt.plot(times2,thetas2,'b')
#uncomment following line to turn on wrapping
line3, = plt.plot((times1[-1], times2[0]), (thetas1[-1], thetas2[0]),'b--' )

plt.xlabel('Time (ms)')
plt.ylabel('Theta ($^\circ$)')
plt.title('Desired Angle of leg in degrees')


plt.yticks(np.arange(-180, 181, 30))




plt.show()
