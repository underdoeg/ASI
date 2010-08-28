import bpy

bl_addon_info = {
    'name': 'reset origin of child object',
    'author': 'Philip Whitfield (underdoeg)',
    'version': '0.1',
    'blender': (2, 5, 2),
    'url': 'undef.ch',
    'description': 'Sets the origin of child objects to parent\'s origin',
    'category': 'Operations'}

# Operator
class ResetChildOrigin(bpy.types.Operator):
    
    bl_label = "Reset Child Origin"

    def execute(self, context):
        objs = context.selected_objects

        #objs = bpy.context.selected_objects
        bpy.ops.object.select_all(action='DESELECT')
        
        #disable auto keying
        origAutoKey = bpy.context.tool_settings.use_auto_keying
        bpy.context.tool_settings.use_auto_keying = False
        
        #loop the objects
        for obj in objs:
            if obj.parent != None:
                #get the offset for later
                parMat = obj.parent.matrix.copy() 
                locMat = obj.matrix.copy()
                mat = parMat.invert()*locMat
                
                oldLoc = obj.location.copy();
                
                """
                print("OLD LOCATION ")
                print(oldLoc)
                """
                
                #now clear origin and location
                obj.selected = True
                bpy.ops.object.location_clear()
                bpy.ops.object.origin_clear()
                
                #move back to original location
                newLoc = mat.translation_part()
                scalePart = obj.parent.scale
        
                newLoc[0]*=scalePart[0]
                newLoc[1]*=scalePart[1]
                newLoc[2]*=scalePart[2]
                obj.location = newLoc
                #obj.matrix = mat
                
                #deselect to finish up
                obj.selected = False
                
                #locMat = obj.matrix-locMat
                trans = obj.location-oldLoc
                
                """
                print("NEW LOCATION ")
                print(obj.location)
                """
                
                #clean up animation
                if obj.animation_data != None:
                    action = obj.animation_data.action
                    for curve in action.fcurves:
                        if curve.data_path == "location":
                            for key in curve.keyframe_points:
                                key.co[1] += trans[curve.array_index]
                                key.handle1[1] += trans[curve.array_index]
                                key.handle2[1] += trans[curve.array_index]
        
        #little cleanup, restore original selection
        for obj in objs:
            obj.selected = True
            
        bpy.context.tool_settings.use_auto_keying = origAutoKey

def register():
    bpy.types.register(ResetChildOrigin)

def unregister():
    bpy.types.unregister(ResetChildOrigin)

if __name__ == "__main__":
    register()