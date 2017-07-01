bl_info = {
    "name": "Dragon Curve",
    "author": "corrodedHash",
    "version": (0, 2),
    "blender": (2, 75, 0),
    "location": "View3D > Add > Mesh > Dragon Curve",
    "description": "Adds a new Dragon Curve",
    "warning": "",
    "wiki_url": "",
    "category": "Add Mesh",
}


import dragon  # NOQA
import bpy  # NOQA

# Registration


def add_object_button(self, context):
    self.layout.operator(
        dragon.DragonCurve_add_object.bl_idname,
        text="Dragon Curve",
        icon='PLUGIN')


# This allows you to right click on a button and link to the manual
def add_object_manual_map():
    url_manual_prefix = "http://wiki.blender.org/index.php/Doc:2.6/Manual/"
    url_manual_mapping = (
        ("bpy.ops.mesh.add_object", "Modeling/Objects"),
    )
    return url_manual_prefix, url_manual_mapping


def register():
    bpy.utils.register_class(dragon.DragonCurve_add_object)
    # bpy.utils.register_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.append(add_object_button)


def unregister():
    bpy.utils.unregister_class(dragon.DragonCurve_add_object)
    # bpy.utils.unregister_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.remove(add_object_button)


if __name__ == "__main__":
    register()
