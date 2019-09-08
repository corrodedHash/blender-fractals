bl_info = {
    "name": "Fractals",
    "author": "corrodedHash",
    "version": (0, 3),
    "blender": (2, 80, 0),
    "location": "View3D > Add > Mesh > Fractal",
    "description": "Adds a new fractal",
    "warning": "",
    "wiki_url": "",
    "category": "Add Mesh",
}

if "bpy" in locals():
    import importlib

    importlib.reload(fractal)

else:
    from . import fractal

import bpy  # NOQA


def register():
    """Appends the fractal button to the menu"""
    fractal.register()


def unregister():
    """Removes the fractal button from the menu"""
    fractal.unregister()


if __name__ == "__main__":
    register()
