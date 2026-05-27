import serial
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

ser = serial.Serial('COM18', 115200, timeout=1)

plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# --- Better plane model (clearly shows orientation) ---
plane = np.array([
    [2, 0, 0],      # nose
    [-1, -1, 0],    # left wing
    [-1, 1, 0],     # right wing
    [-0.5, 0, 0.5]  # tail (gives 3D feel)
])

# Define faces (triangles)
faces = [
    [plane[0], plane[1], plane[2]],  # main wing
    [plane[0], plane[2], plane[3]],  # right side
    [plane[0], plane[1], plane[3]]   # left side
]

poly = Poly3DCollection(faces, alpha=0.8)
poly.set_facecolor('blue')
ax.add_collection3d(poly)

# Set limits ONCE
ax.set_xlim([-3, 3])
ax.set_ylim([-3, 3])
ax.set_zlim([-3, 3])

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

def rotation_matrix(roll, pitch):
    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(roll), -np.sin(roll)],
        [0, np.sin(roll), np.cos(roll)]
    ])

    Ry = np.array([
        [np.cos(pitch), 0, np.sin(pitch)],
        [0, 1, 0],
        [-np.sin(pitch), 0, np.cos(pitch)]
    ])

    return Ry @ Rx

while True:
    try:
        line = ser.readline().decode().strip()
        if not line:
            continue

        data = line.split(',')
        if len(data) != 2:
            continue

        try:
            roll = float(data[0]) * np.pi / 180
            pitch = float(data[1]) * np.pi / 180
        except:
            continue

        R = rotation_matrix(roll, pitch)
        rotated = plane @ R.T

        # update faces instead of clearing
        new_faces = [
            [rotated[0], rotated[1], rotated[2]],
            [rotated[0], rotated[2], rotated[3]],
            [rotated[0], rotated[1], rotated[3]]
        ]

        poly.set_verts(new_faces)

        plt.draw()
        plt.pause(0.001)   # smaller pause = smoother

    except KeyboardInterrupt:
        break