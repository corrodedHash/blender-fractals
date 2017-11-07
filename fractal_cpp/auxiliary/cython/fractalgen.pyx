from libcpp.string cimport string
from libc.stdint cimport uint64_t
from libc.stdlib cimport free

from cython cimport view
from cpython cimport PyObject, Py_INCREF

cdef extern from "generator/fractalgen.h":
    cdef cppclass mesh_info[T]:
        T* verts
        uint64_t * edges
        uint64_t * face_verts
        uint64_t * face_bounds
        uint64_t vert_size, edge_size, face_vert_size, face_bound_size
    mesh_info[double] generateMesh(string filename, unsigned int level)

class FaceList:
    def __init__(self, vertices, indices):
        self.vertices = vertices
        self.indices = indices

    def __iter__(self):
        return self._iterate()

    def __len__(self):
        return len(self.indices)

    def _iterate(self):
        cdef int last_index = 0
        cdef int cur_index = 0
        for cur_index in self.indices:
            yield self.vertices[last_index:cur_index]
            last_index = cur_index

cdef void notify_free(void* ptr):
    free(ptr)
    print("hola")

def generate_fractal(filename, level):
    cdef string cpp_file = bytes(filename, "utf8")
    cdef mesh_info[double] bla = generateMesh(cpp_file, level)
    cdef view.array vert_array = <double[:bla.vert_size // 3, :3]> bla.verts
    cdef view.array edge_array
    cdef view.array face_vert_array
    cdef view.array face_bound_array

    facelist = None

    if (bla.edge_size > 0):
      edge_array = <uint64_t[:bla.edge_size // 2, :2]> bla.edges
      edge_array.callback_free_data = notify_free
    else:
      edge_array = None

    if (bla.face_vert_size > 0):
      face_vert_array = <uint64_t[:bla.face_vert_size]> bla.face_verts
      face_bound_array = <uint64_t[:bla.face_bound_size]> bla.face_bounds
      face_vert_array.callback_free_data = notify_free
      face_bound_array.callback_free_data = notify_free
      facelist = FaceList(face_vert_array, face_bound_array)


    vert_array.callback_free_data = notify_free

    return (vert_array, edge_array, facelist)
