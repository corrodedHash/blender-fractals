bl_info = {
    "name": "Fractals",
    "author": "corrodedHash",
    "version": (0, 3),
    "blender": (2, 75, 0),
    "location": "View3D > Add > Mesh > Fractal",
    "description": "Adds a new fractal",
    "warning": "",
    "wiki_url": "",
    "category": "Add Mesh",
}

import bpy  # NOQA

# import dragon  # NOQA
from .fractal import Fractal_add_object  # NOQA

# Registration

def add_fractal_button(self, context):
    """Adds the fractal button"""
    self.layout.operator(
        Fractal_add_object.bl_idname,
        text="Fractal",
        icon='PLUGIN')


# This allows you to right click on a button and link to the manual
def add_dragon_manual_map():
    """I don't know, does stuff"""
    url_manual_prefix = "http://wiki.blender.org/index.php/Doc:2.6/Manual/"
    url_manual_mapping = (
        ("bpy.ops.mesh.add_object", "Modeling/Objects"),
    )
    return url_manual_prefix, url_manual_mapping


def register():
    """Appends the fractal button to the menu"""
    bpy.utils.register_class(Fractal_add_object)
    # bpy.utils.register_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.append(add_fractal_button)


def unregister():
    """Removes the fractal button from the menu"""
    bpy.utils.unregister_class(Fractal_add_object)
    # bpy.utils.unregister_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.remove(add_fractal_button)


if __name__ == "__main__":
    register()
