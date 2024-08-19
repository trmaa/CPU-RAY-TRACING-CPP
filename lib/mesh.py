obj_vertices = [
    [1.0, 1.0, 0.0],
    [2.0, 3.0, 0.0],
    [3.0, 1.0, 0.0]
]

obj_faces = [
    [0, 1, 2]
]

triangles = []

for face in obj_faces:
    v1 = obj_vertices[face[0]]
    v2 = obj_vertices[face[1]]
    v3 = obj_vertices[face[2]]

    center = v1

    s1 = [v2[i] - v1[i] for i in range(3)]
    s2 = [v3[i] - v1[i] for i in range(3)]

    triangle = {
        "center": center,
        "s1": s1,
        "s2": s2
    }

    triangles.append(triangle)

print(triangles)
