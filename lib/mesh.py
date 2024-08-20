import json

def parse_obj_file(file_path):
    vertices = []
    faces = []

    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith('#') or line.strip() == '':
                continue

            parts = line.split()

            if parts[0] == 'v':
                vertex = list(map(float, parts[1:4]))
                vertices.append(vertex)
            elif parts[0] == 'f':
                face = [int(index.split('/')[0]) - 1 for index in parts[1:]]
                faces.append(face)

    return vertices, faces

class Triangle:
    def __init__(self, c, s0, s1):
        self.center = c
        self.s0 = s0
        self.s1 = s1
        self.color = [255, 255, 255]
        self.emission = 0
        self.roughness = 0
        self.texture = ""

    def to_dict(self):
        return {
            "center": self.center,
            "s0": self.s0,
            "s1": self.s1,
            "color": self.color,
            "emission": self.emission,
            "roughness": self.roughness,
            "texture": self.texture
        }

obj_file_path = './bin/models/donut.obj'
vertices, faces = parse_obj_file(obj_file_path)

triangles = []

for face in faces:
    v1 = vertices[face[0]]
    v2 = vertices[face[1]]
    v3 = vertices[face[2]]

    center = v1
    s1 = [v2[i] - v1[i] for i in range(3)]
    s2 = [v3[i] - v1[i] for i in range(3)]

    triangle = Triangle(center, s1, s2)
    triangles.append(triangle.to_dict())

json_content = {
    "res": [16*3, 9*3],
    "sky": [0.8, 0.9, 1],
    "sphere": [],
    "triangle": triangles
}

json_file_path = './bin/scene.json'

with open(json_file_path, 'w') as json_file:
    json.dump(json_content, json_file, indent=4)

print(f"Triangles saved to {json_file_path}")
