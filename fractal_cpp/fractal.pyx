from libcpp.string cimport string

cdef extern from "fractalgen.cpp":
  cdef cppclass mesh_info[T]:
    T* verts
    unsigned long * edges, faces
    unsigned long vert_size, edge_size, face_size

  mesh_info[double] generateMesh(string filename, unsigned int level)

def p():
    print("hello")

def x(filename, level):
    bla = generateMesh(filename, level)
    print(bla.vert_size)
