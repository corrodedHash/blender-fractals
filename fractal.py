"""Uses the cpp fractal generator"""
import faulthandler
import os

import bpy
import bpy_extras

from .fractal_cpp.build.fractalgen import generate_fractal
from .util.timer import Timer


def _create_fractal(properties, context):
    faulthandler.enable()
    if properties.grammar_path == "":
        return

    with Timer(name="all", verbose=True):
        with Timer(name="Generation", verbose=True):
            verts, edges, faces = generate_fractal(
                properties.grammar_path, properties.iteration
            )
            if edges is None:
                edges = []
            if faces is None:
                faces = []

        mesh = bpy.data.meshes.new("FractalMesh")

        with Timer(name="Copying", verbose=True):
            mesh.from_pydata(verts, edges, faces)

        mesh_obj = bpy_extras.object_utils.object_data_add(context, mesh, operator=properties)

        with Timer(name="Optimizing", verbose=True):
            context.view_layer.objects.active = mesh_obj
            mesh_obj.select_set(True)

            bpy.ops.object.mode_set(mode="EDIT")
            bpy.ops.mesh.remove_doubles(threshold=0.0001)
            bpy.ops.object.mode_set(mode="OBJECT")

    # bpy.context.window_manager.progress_end()


class add_mesh_fractal(bpy.types.Operator, bpy_extras.object_utils.AddObjectHelper):
    """Create a new Fractal"""

    bl_idname = "mesh.add_fractal"
    bl_label = "Add Fracal"
    bl_options = {"REGISTER", "UNDO"}

    iteration: bpy.props.IntProperty(
        name="Iteration Count",
        default=1,
        min=1,
        soft_min=1,
        soft_max=10,
        subtype="UNSIGNED",
        description="Number of iterations of the fractal",
    )

    standard_path = os.path.join(
        os.path.dirname(os.path.realpath(__file__)), "examples", "3d", "menge.txt"
    )

    def reset_iteration(self, _context):
        """Resets iteration"""
        self.iteration = 2

    grammar_path: bpy.props.StringProperty(
        name="Grammar path",
        default=standard_path,
        description="The grammar for the fractal you want to draw",
        subtype="FILE_PATH",
        update=reset_iteration,
    )

    def execute(self, context):
        """Create the fractal"""
        _create_fractal(self, context)

        return {"FINISHED"}

    def invoke(self, context, event):
        """Invoke"""
        self.execute(context)
        return {"FINISHED"}


# Register:
def menu_func_fractal(self, context):
    layout = self.layout
    layout.separator()
    self.layout.operator(add_mesh_fractal.bl_idname, text="Fractal", icon="MOD_TIME")


classes = (add_mesh_fractal,)


def register():
    from bpy.utils import register_class

    for cls in classes:
        register_class(cls)
    bpy.types.VIEW3D_MT_mesh_add.append(menu_func_fractal)


def unregister():
    from bpy.utils import unregister_class

    for cls in reversed(classes):
        unregister_class(cls)
    bpy.types.VIEW3D_MT_mesh_add.remove(menu_func_fractal)
