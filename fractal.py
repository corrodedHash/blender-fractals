"""Uses the cpp fractal generator"""
import os
import faulthandler

import bpy
from bpy_extras.io_utils import unpack_list, unpack_face_list

from .fractal_cpp.build.fractalgen import generate_fractal
from .util.timer import Timer



def _create_fractal_fast(self, _context):
    faulthandler.enable()
    if self.grammar_path == "":
        return

    with Timer(name="all", verbose=True):
        with Timer(name="Generation", verbose=True):
            verts, edges, faces = generate_fractal(self.grammar_path, self.iteration)
            if edges is None:
                edges = []
            if faces is None:
                faces = []

        len_faces = len(faces)

        with Timer(name="Copying", verbose=True):
            me = bpy.data.meshes.new('Cube')
            me.vertices.add(len(verts))
            me.vertices.foreach_set("co", unpack_list(verts))

            me.loops.add(len(faces.vertices))
            me.loops.foreach_set("vertex_index", unpack_face_list(faces))

            me.polygons.add(len(faces)) 
            me.polygons.foreach_set("loop_start", list(faces.starts))
            me.polygons.foreach_set("loop_total", list(faces.totals))
#me.polygons.foreach_set("vertices", unpack_face_list(faces))
        with Timer(name="Optimizing", verbose=True):

            me.update(calc_edges=True)
            me.calc_normals()
#me.validate(True)

        ob = bpy.data.objects.new(me.name, me)
        bpy.context.scene.objects.link(ob)
        bpy.context.scene.update()

def _create_fractal(self, _context):
    faulthandler.enable()
    if self.grammar_path == "":
        return

    with Timer(name="all", verbose=True):
        with Timer(name="Generation", verbose=True):
            verts, edges, faces = generate_fractal(self.grammar_path, self.iteration)
            if edges is None:
                edges = []
            if faces is None:
                faces = []


        profile_mesh = bpy.data.meshes.new("FractalMesh")

        with Timer(name="Copying", verbose=True):
            profile_mesh.from_pydata(verts, edges, faces)
            #profile_mesh.vertices.foreach_get("co", verts)
            #profile_mesh.edges.foreach_get("vertices", edges)

        profile_mesh.update()
        profile_object = bpy.data.objects.new("Fractal", profile_mesh)
        profile_object.data = profile_mesh

        scene = bpy.context.scene
        scene.objects.link(profile_object)

        with Timer(name="Optimizing", verbose=True):
            scene.objects.active = profile_object

            bpy.ops.object.mode_set(mode='EDIT')
            bpy.ops.mesh.remove_doubles(threshold=0.0001)
            bpy.ops.object.mode_set(mode='OBJECT')

    # bpy.context.window_manager.progress_end()


class Fractal_add_object(bpy.types.Operator):
    """Create a new Fractal"""
    bl_idname = "mesh.add_fractal"
    bl_label = "Add Fracal"
    bl_options = {'REGISTER', 'UNDO'}

    iteration = bpy.props.IntProperty(
        name="Iteration Count",
        default=1,
        min=1,
        soft_min=1,
        soft_max=10,
        subtype='UNSIGNED',
        description="Number of iterations of the fractal")

    standard_path = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                 "examples", "3d", "menge.txt")

    def reset_iteration(self, _context):
        """Resets iteration"""
        self.iteration = 2

    grammar_path = bpy.props.StringProperty(
        name="Grammar path",
        default=standard_path,
        description="The grammar for the fractal you want to draw",
        subtype='FILE_PATH',
        update=reset_iteration
    )

    def execute(self, context):
        """Create the fractal"""
        _create_fractal_fast(self, context)

        return {'FINISHED'}
