
bl_info = {
    "name": "Dragon Curve",
    "author": "corrodedHash",
    "version": (0, 1),
    "blender": (2, 75, 0),
    "location": "View3D > Add > Mesh > Dragon Curve",
    "description": "Adds a new Dragon Curve",
    "warning": "",
    "wiki_url": "",
    "category": "Add Mesh",
    }


import bpy
import bmesh
from bpy.types import Operator
from bpy.props import IntProperty, BoolProperty
from bpy_extras.object_utils import AddObjectHelper, object_data_add
from mathutils import Vector

def create_dragon(self, context):
    def dragon(turn):
        flip_count = 0
        cur_bit = turn % 2
        while turn > 0:
            turn = turn // 2
            if turn % 2 is not cur_bit:
                cur_bit = turn % 2
                flip_count += 1
        return flip_count % 4

    def fold(direction):
        if direction == 0:
            return (0, 1)

        if direction == 1:
            return (1, 0)

        if direction == 2:
            return (0, -1)

        if direction == 3:
            return (-1, 0)
        
        else:
            raise ValueError

    me = bpy.data.meshes.new('dragonMesh') 

    ob = bpy.data.objects.new('DragonCurve', me) 

    bpy.context.scene.objects.link(ob)

    bm = bmesh.new() # create an empty BMesh
    bm.from_mesh(me) # fill it in from a Mesh

    cur_vec = (0.0, 0.0, 0.0)
    last_v1 = bm.verts.new( cur_vec )
    last_v2 = bm.verts.new( (cur_vec[0], cur_vec[1] + 1, cur_vec[2]) )

    for cur_turn in range(1, self.count):
        dir_vec = fold(dragon(cur_turn))

        cur_vec = (cur_vec[0] + dir_vec[0], cur_vec[1], cur_vec[2] + dir_vec[1])
        cur_v1 = bm.verts.new( cur_vec )
        cur_v2 = bm.verts.new( (cur_vec[0], cur_vec[1] + 1, cur_vec[2]) )

        bm.verts.index_update()
        bm.faces.new( (last_v1, last_v2, cur_v2, cur_v1) )

        last_v1 = cur_v1
        last_v2 = cur_v2

    #if self.merge_vertices:
    #    print(str(bpy.context.area.type))
    #    bpy.ops.mesh.remove_doubles()

    bm.to_mesh(me)

class DragonCurve_add_object(Operator, AddObjectHelper):
    """Create a new Dragon Curve"""
    bl_idname = "mesh.add_dragoncurve"
    bl_label = "Add Dragon Curve"
    bl_options = {'REGISTER', 'UNDO'}

    count = IntProperty(
            name="Edge Count",
            default=100,
            min=1,
            soft_min=1,
            subtype='UNSIGNED',
            description="Number of squares the dragon will consist of",
            )

    def iteration_update(self, context):
        self.count = 2 ** self.iteration

    iteration = IntProperty(
            name="Iteration Count",
            default=2,
            min=1,
            soft_min=1,
            soft_max=10,
            subtype='UNSIGNED',
            description="Number of iterations of the dragon curve",
            update=iteration_update)



    merge_vertices = BoolProperty(
            name="Merge vertices", 
            description="Remove duplicate vertices",
            default=True
            )
            
    def execute(self, context):

        create_dragon(self, context)

        return {'FINISHED'}


# Registration

def add_object_button(self, context):
    self.layout.operator(
        DragonCurve_add_object.bl_idname,
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
    bpy.utils.register_class(DragonCurve_add_object)
    #bpy.utils.register_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.append(add_object_button)


def unregister():
    bpy.utils.unregister_class(DragonCurve_add_object)
    #bpy.utils.unregister_manual_map(add_object_manual_map)
    bpy.types.INFO_MT_mesh_add.remove(add_object_button)


if __name__ == "__main__":
    register()
