from libcpp.string cimport string

import numpy as np
cimport numpy as np
np.import_array()

from cpython cimport PyObject, Py_INCREF

cdef extern from "fractalgen.cpp":
    cdef cppclass mesh_info[T]:
        T* verts
        unsigned long * edges
        unsigned long * faces
        unsigned long vert_size, edge_size, face_size
    mesh_info[double] generateMesh(string filename, unsigned int level)

cdef extern from "numpy/arrayobject.h":
    void PyArray_ENABLEFLAGS(np.ndarray arr, int flags)

def p():
    print("hello")

def x(filename, level):
    cdef string cpp_file = bytes(filename, "utf8")
    cdef mesh_info[double] bla = generateMesh(cpp_file, level)
    cdef np.npy_intp shape[1]
    shape[0] = <np.npy_intp> bla.edge_size

    cdef np.ndarray[np.uint64, ndim=1] arr = \
            np.PyArray_SimpleNewFromData(1, shape, np.NPY_UINT64, bla.edges)
    PyArray_ENABLEFLAGS(arr, np.NPY_OWNDATA)

    return arr 
