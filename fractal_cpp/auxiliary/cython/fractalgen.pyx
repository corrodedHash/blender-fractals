from libcpp.string cimport string
from libc.stdint cimport uint32_t
from libc.stdlib cimport free

from cython cimport view
from cpython cimport PyObject, Py_INCREF

cdef extern from "generator/fractalgen.h" namespace "frac":
    cdef cppclass mesh_info:
        float* verts
        uint32_t * edges
        uint32_t * face_verts
        uint32_t * face_bounds
        uint32_t * face_starts
        uint32_t * face_totals
        uint32_t vert_size, edge_size, face_vert_size, face_bound_size
    mesh_info generateMesh(string filename, unsigned int level)

class FaceList:
    def __init__(self, vertices, indices, starts, totals):
        self.vertices = vertices
        self.indices = indices
        self.starts = starts
        self.totals = totals

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
    cdef mesh_info bla = generateMesh(cpp_file, level)
    cdef view.array vert_array = <float[:bla.vert_size // 3, :3]> bla.verts
    cdef view.array edge_array
    cdef view.array face_vert_array
    cdef view.array face_bound_array
    cdef view.array face_starts_array
    cdef view.array face_totals_array

    facelist = None

    if (bla.edge_size > 0):
      edge_array = <uint32_t[:bla.edge_size // 2, :2]> bla.edges
      edge_array.callback_free_data = notify_free
    else:
      edge_array = None

    if (bla.face_vert_size > 0):
      face_vert_array = <uint32_t[:bla.face_vert_size]> bla.face_verts
      face_bound_array = <uint32_t[:bla.face_bound_size]> bla.face_bounds
      face_starts_array = <uint32_t[:bla.face_bound_size]> bla.face_starts
      face_totals_array = <uint32_t[:bla.face_bound_size]> bla.face_totals

      face_vert_array.callback_free_data = notify_free
      face_bound_array.callback_free_data = notify_free
      face_starts_array.callback_free_data = notify_free
      face_totals_array.callback_free_data = notify_free
      facelist = FaceList(face_vert_array, face_bound_array, face_starts_array, face_totals_array)


    vert_array.callback_free_data = notify_free

    return (vert_array, edge_array, facelist)
