from libcpp.string cimport string
from libc.stdint cimport uint64_t
from libc.stdlib cimport free

from cython cimport view
from cpython cimport PyObject, Py_INCREF

cdef extern from "fractalgen.cpp":
    cdef cppclass mesh_info[T]:
        T* verts
        uint64_t * edges
        uint64_t * faces
        uint64_t vert_size, edge_size, face_size
    mesh_info[double] generateMesh(string filename, unsigned int level)

cdef void notify_free(void* ptr):
    free(ptr)
    print("hola")

def x(filename, level):
    cdef string cpp_file = bytes(filename, "utf8")
    cdef mesh_info[double] bla = generateMesh(cpp_file, level)
    cdef view.array vert_array = <double[:bla.vert_size // 3, :3]> bla.verts
    cdef view.array edge_array = <uint64_t[:bla.edge_size // 2, :2]> bla.edges
    #vert_array.callback_free_data = notify_free 
    #edge_array.callback_free_data = notify_free 

    return (vert_array, edge_array)
