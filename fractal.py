import os

import bpy
import bmesh

from .fractalgen import FractalGen
from .lsystem.lsystem_parse import parse as lparse


def _create_fractal(self, _context):
    parsed_lsystem = None
    if self.grammar_path == "":
        return
    try:
        with open(self.grammar_path) as grammar_file:
            parsed_lsystem = lparse(grammar_file.read())
    except FileNotFoundError:
        self.grammar_path = self.standard_path
        return
    except RuntimeError as run_err:
        msg = ""
        for err_line in run_err.args:
            msg += err_line + "\n"
        self.report({'ERROR_INVALID_INPUT'}, msg)
        self.grammar_path = self.standard_path
        return

    bpy.context.window_manager.progress_begin(0, 99)
    frac = FractalGen(self.iteration, parsed_lsystem, bpy.context.window_manager.progress_update,
                      bpy.context.scene.cursor_location)
    frac.draw_vertices()

    profile_mesh = bpy.data.meshes.new("FractalMesh")
    profile_mesh.from_pydata(frac.verts, frac.edges, frac.faces)
    profile_mesh.update()
    profile_object = bpy.data.objects.new("Fractal", profile_mesh)
    profile_object.data = profile_mesh

    scene = bpy.context.scene
    scene.objects.link(profile_object)
    profile_object.select = True

    # bpy.context.scene.objects.active = profile_object
    # bpy.ops.object.editmode_toogle()
    # bpy.ops.mesh.select_all(action='SELECT')
    # bpy.ops.mesh.remove_doubles()
    # bpy.ops.object.editmode_toogle()

    bm = bmesh.new()
    bm.from_mesh(profile_mesh)
    bmesh.ops.remove_doubles(bm, verts=bm.verts, dist=0.001)
    bm.to_mesh(profile_mesh)
    profile_mesh.update()

    bpy.context.window_manager.progress_end()


class Fractal_add_object(bpy.types.Operator):
    """Create a new Fractal"""
    bl_idname = "mesh.add_fractal"
    bl_label = "Add Fracal"
    bl_options = {'REGISTER', 'UNDO'}

    iteration = bpy.props.IntProperty(
        name="Iteration Count",
        default=2,
        min=1,
        soft_min=1,
        soft_max=7,
        subtype='UNSIGNED',
        description="Number of iterations of the fractal")

    standard_path = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                 "examples", "standard", "sierpinski.txt")

    def reset_iteration(self, _context):
        self.iteration = 2

    grammar_path = bpy.props.StringProperty(
        name="Grammar path",
        default=standard_path,
        description="The grammar for the fractal you want to draw",
        subtype='FILE_PATH',
        update=reset_iteration
    )

    def execute(self, context):

        _create_fractal(self, context)

        return {'FINISHED'}
