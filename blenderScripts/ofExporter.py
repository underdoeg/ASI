bl_addon_info = {
    'name': 'I/O: OF',
    'author': 'Philip Whitfield (underdoeg)',
    'version': '1',
    'blender': (2, 5, 3),
    'location': 'File > Export > OF',
    'description': 'Export to OF',
     'url': 'http://www.underdoeg.com' \
        'Scripts/File I-O/OF', 
    'category': 'Export'}


import bpy
from bpy.props import *
import os
import shutil
from mathutils import Vector
from xml.dom.minidom import *

#create an xml 
copyResPathAbs = ""
copyResPathRel = ""
copyRes = True

def vertToXML(node, vert):
    vertsNode = doc.createElement("v");
    node.appendChild(vertsNode)
    #vertsNode.setAttribute("index", str(vert.index));
    vertsNode.setAttribute("x", str(vert.co.x));
    vertsNode.setAttribute("y", str(vert.co.y));
    vertsNode.setAttribute("z", str(vert.co.z));
    
def meshToXML(node, mesh):
    vertsNode = doc.createElement("verts");
    node.appendChild(vertsNode)
   
    for vert in mesh.verts:
        vertToXML(vertsNode, vert)
    
    for face in mesh.faces:
        fNode = doc.createElement("face");
        node.appendChild(fNode)
        for vert in face.verts:
            vNode = doc.createElement("vRef");
            fNode.appendChild(vNode)
            vNode.setAttribute("index",str(vert))

    if mesh.active_uv_texture != None:
        for texData in mesh.active_uv_texture.data:
            texNode = doc.createElement("texFace")
            if texData.image != None:
                texNode.setAttribute("img",texData.image.name)
            for uv in texData.uv:
                uvNode = doc.createElement("uv")
                texNode.appendChild(uvNode)
                uvNode.setAttribute("u", str(uv[0]))
                uvNode.setAttribute("v", str(uv[1]))
            node.appendChild(texNode)
    return;
    
#translate object animation
def objectAnimToXML(node, object):
    animNode = doc.createElement("anim")
    node.appendChild(animNode)
    if object.animation_data == None:
        return
    action = object.animation_data.action
    for curve in action.fcurves:
        kfNode = doc.createElement("frames")
        animNode.appendChild(kfNode)
        kfNode.setAttribute("path", curve.data_path)
        kfNode.setAttribute("indx", str(curve.array_index))
        for key in curve.keyframe_points:
            kNode = doc.createElement("key")
            kfNode.appendChild(kNode)
            kNode.setAttribute("coX", str(key.co[0]))
            kNode.setAttribute("coY", str(key.co[1]))
            kNode.setAttribute("h1X", str(key.handle1[0]))
            kNode.setAttribute("h1Y", str(key.handle1[1]))
            kNode.setAttribute("h2X", str(key.handle2[0]))
            kNode.setAttribute("h2Y", str(key.handle2[1]))

#bounding box
def boundsToXML(node, bounds):
    bNode = doc.createElement("bounds")
    node.appendChild(bNode)
    for b in bounds:
        n = doc.createElement("v")
        bNode.appendChild(n)
        n.setAttribute("x", str(b[0]));
        n.setAttribute("y", str(b[1]));
        n.setAttribute("z", str(b[2]));
        

#function to convert an object into an xml
def objectToXML(node, object):
    oNode = doc.createElement("object")
    node.appendChild(oNode)
    oNode.setAttribute("name", object.name)
    subX = 0;
    subY = 0;
    subZ = 0;
    obj = object.parent
    while obj != None:
        subX += obj.location.x
        subY += obj.location.y
        subZ += obj.location.z
        obj = obj.parent
    
    oNode.setAttribute("x", str(object.location[0]))
    oNode.setAttribute("y", str(object.location[1]))
    oNode.setAttribute("z", str(object.location[2]))
    
    scX = 0;
    scY = 0;
    scZ = 0;
    obj = object.parent
    while obj != None:
        scX = obj.scale.x
        scY = obj.scale.y
        scZ = obj.scale.z
        obj = obj.parent
    
    oNode.setAttribute("sx", str(object.scale[0]))
    oNode.setAttribute("sy", str(object.scale[1]))
    oNode.setAttribute("sz", str(object.scale[2]))
    
    rX = 0
    rY = 0
    rZ = 0
    obj = object.parent
    while obj != None:
        rX = rX +obj.rotation_euler[0]
        rY = rY +obj.rotation_euler[1]
        rZ = rZ +obj.rotation_euler[2]
        obj = obj.parent
    
    oNode.setAttribute("rx", str(object.rotation_euler[0]))
    oNode.setAttribute("ry", str(object.rotation_euler[1]))
    oNode.setAttribute("rz", str(object.rotation_euler[2]))
    
    #bounding box
    boundsToXML(oNode, object.bound_box)
    
    meshToXML(oNode, object.data)
    objectAnimToXML(oNode, object)
    for child in object.children:
        objectToXML(oNode, child)
    return;
    
#function to convert a cmaera to xml
def camToXML(node, cam):
    if cam == None:
        return
    camNode = doc.createElement("cam")
    node.appendChild(camNode)
    camNode.setAttribute("x", str(cam.location.x))
    camNode.setAttribute("y", str(cam.location.y))
    camNode.setAttribute("z", str(cam.location.z))
    camNode.setAttribute("rx", str(cam.rotation_euler[0]))
    camNode.setAttribute("ry", str(cam.rotation_euler[1]))
    camNode.setAttribute("rz", str(cam.rotation_euler[2]))
    camNode.setAttribute("name", cam.name)
    camNode.setAttribute("lens", str(cam.data.angle))
    camNode.setAttribute("clipStart", str(cam.data.clip_start))
    camNode.setAttribute("clipEnd", str(cam.data.clip_end))
    camNode.setAttribute("imgW", str(bpy.context.scene.render.resolution_x))
    camNode.setAttribute("imgH", str(bpy.context.scene.render.resolution_y))
    objectAnimToXML(camNode, cam)

#function to convert markers
def markerToXML(node, marker):
    markNode = doc.createElement("marker")
    node.appendChild(markNode)
    markNode.setAttribute("name", marker.name)
    markNode.setAttribute("frame", str(marker.frame))

#function to convert sequences to xml
def seqToXML(node, seq):
    seqNode = doc.createElement("seq")
    node.appendChild(seqNode)
    seqNode.setAttribute("type", seq.type)
    seqNode.setAttribute("start", str(seq.frame_start))
    seqNode.setAttribute("length", str(seq.frame_length))
    if seq.type == "SOUND":
        seqNode.setAttribute("name", seq.sound.name)
        seqNode.setAttribute("vol", str(seq.volume))

#function to convert an image to xml
def imageToXML(node, img):
    path = ""
    if hasattr(img, 'filepath'):
        path = img.filepath
    else:
        path = img.filename
    if path == "":
        return
    imgNode = doc.createElement("img")
    node.appendChild(imgNode)
    imgNode.setAttribute("name", img.name)
    if copyRes == True:
        dirName = "images"
        dirPath = os.path.join(copyResPathAbs, dirName)
        if os.path.exists(dirPath) == False:
            os.mkdir(dirPath)
        basename = os.path.join(dirName,os.path.basename(path))
        fullpath = os.path.join(copyResPathAbs, basename)
        if os.path.exists(path) == True:
            shutil.copy(path, fullpath)
        imgNode.setAttribute("file", os.path.join(copyResPathRel, basename))
    else:
        imgNode.setAttribute("file", path)

#function to convert a sound file to xml
def soundToXML(node, snd):   
    path = ""
    if hasattr(snd, 'filepath'):
        path = snd.filepath
    else:
        path = snd.filename
    if path == "":
        return
    sndNode = doc.createElement("snd")
    node.appendChild(sndNode)
    sndNode.setAttribute("name", snd.name)
    if copyRes == True:
        dirName = "sounds"
        dirPath = os.path.join(copyResPathAbs, dirName)
        if os.path.exists(dirPath) == False:
            os.mkdir(dirPath)
        basename = os.path.join(dirName,os.path.basename(path))
        #print("COPY FROM "+snd.filepath+" TO "+os.path.join(copyResPathAbs, basename))
        shutil.copy(path, os.path.join(copyResPathAbs, basename))
        sndNode.setAttribute("file", os.path.join(copyResPathRel, basename))
    else:
        sndNode.setAttribute("file", path)

def sceneToXML(node, scene):
    sceneNode = doc.createElement("scene")
    node.appendChild(sceneNode)
    
    #scene settings
    sceneNode.setAttribute("frameEnd", str(scene.frame_end))
    sceneNode.setAttribute("fps", str(scene.render.fps))
    sceneNode.setAttribute("name", str(scene.name))
    
    #the camera
    camToXML(sceneNode, scene.camera)
    
    #objects
    objectsNode = doc.createElement("objects")
    sceneNode.appendChild(objectsNode)
    for object in scene.objects:
        if object.type == 'MESH' and object.parent == None:
            objectToXML(objectsNode, object)
    
    #markers
    markersNode = doc.createElement("markers")
    sceneNode.appendChild(markersNode)
    for marker in scene.timeline_markers:
        markerToXML(markersNode, marker)
    
    #sequence stuff
    seqNode = doc.createElement("sequences")
    sceneNode.appendChild(seqNode)
    if scene.sequence_editor != None:
        for seq in scene.sequence_editor.sequences:
            seqToXML(seqNode, seq)
    
    
def doIt(context, path):
    global copyResPathRel, copyResPathAbs, doc
    filepath = path
    """
    filepath = bpy.data.filepath.replace(".blend", ".xml")
    context = bpy.context;
    """
   
    #create doc
    doc = xml.dom.minidom.Document()
    root = doc.createElement("root")
    doc.appendChild(root)
    
    #get the paths right
    basename = os.path.splitext(os.path.basename(filepath))[0]
    copyResPath = os.path.dirname(filepath)
    copyResPathRel = basename+"Res"
    copyResPathAbs = os.path.join(copyResPath, copyResPathRel)
    if os.path.exists(copyResPathAbs) == False:
        os.mkdir(copyResPathAbs)
        
    if copyRes == True:
        root.setAttribute("relRes", "1")
    else:
        root.setAttribute("relRes", "0")
    
    #the scene
    for scn in bpy.data.scenes:
        sceneToXML(root, scn)
    
    #PARSE GLOBAL RESOURCES
    
    #the images
    for img in bpy.data.images:
        imageToXML(root, img)
    
    #the sounds
    for snd in bpy.data.sounds:
        soundToXML(root, snd)
    
    fileObj = open(filepath,"w") 
    fileObj.write(doc.toprettyxml(indent="  "))
    fileObj.close()
    print("EXPORTED TO "+filepath)

class ExportOF(bpy.types.Operator):
    bl_idname = "export.OF"
    bl_label = "export OF"
    bl_description = "Export objects and animations to OpenFrameworks"
    bl_options = {'REGISTER', 'UNDO'}
    
    filepath = StringProperty(name="File Path",
        description="Filepath used for exporting the file",
        maxlen=1024,
        default="")
    
    copyRes = BoolProperty(name="copyRes",
                         description="Copy all Ressources to subfolder",
                         default=True)
    
    def draw(self, context):
        props = self.properties
        layout = self.layout

    def execute(self, context):
        doIt(context, self.properties.filepath)
        return {'FINISHED'}

    def invoke(self, context, event):
        wm = context.manager
        wm.add_fileselect(self)
        return {'RUNNING_MODAL'}
        
# Registering / Unregister
def menu_func(self, context):
    default_path = bpy.data.filepath.replace(".blend", ".xml")
    self.layout.operator(ExportOF.bl_idname, text="OF (.xml)", icon='PLUGIN')

def register():
    bpy.types.register(ExportOF)
    bpy.types.INFO_MT_file_export.append(menu_func)


def unregister():
    bpy.types.unregister(ExportOF)
    bpy.types.INFO_MT_file_export.remove(menu_func)


if __name__ == "__main__":
    #unregister()
    register()