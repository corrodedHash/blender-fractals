import fractal
verts, edges, faces = fractal.generate_fractal("../examples/3d/menge.txt", 2)
if edges is None:
    edges = []
if faces is None:
    faces = []
    
for x in faces:
    print('---')
print(len(faces))
print(faces[2300])
