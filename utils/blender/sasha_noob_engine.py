#  ***** GPL LICENSE BLOCK *****
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#  All rights reserved.
#  ***** GPL LICENSE BLOCK *****

bl_info = {
    "name": "sasha-noob-engine (.xml)",
    "author": "Alexandru Motriuc",
    "version": (1, 0, 0),
    "blender": (2, 5, 8),
    "location": "File > Export > sasha-noob-engine (.xml)",
    "description": "Export sasha-noob-engine Model Format (.xml)",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

import os
from math import radians

import bpy
from mathutils import *

#Container for the exporter settings
class SNEExporterSettings:
    def __init__(self,
                 context,
                 FilePath,
                 CoordinateSystem=1,
                 FlipNormals=False,
                 ApplyModifiers=False,
                 IncludeFrameRate=False,
                 ExportTextures=True,
                 ExportArmatures=False,
                 ExportAnimation=0,
                 ExportMode=1,
                 Verbose=False):
        self.context = context
        self.FilePath = FilePath
        self.CoordinateSystem = int(CoordinateSystem)
        self.FlipNormals = FlipNormals
        self.ApplyModifiers = ApplyModifiers
        self.IncludeFrameRate = IncludeFrameRate
        self.ExportTextures = ExportTextures
        self.ExportArmatures = ExportArmatures
        self.ExportAnimation = int(ExportAnimation)
        self.ExportMode = int(ExportMode)
        self.Verbose = Verbose
        self.Path = os.path.split(FilePath)[0]
        self.Prefix = os.path.splitext( os.path.split(FilePath)[1] )[0]


CoordinateSystems = (
    ("1", "Left-Handed", ""),
    ("2", "Right-Handed", ""),
    )


AnimationModes = (
    ("0", "None", ""),
    ("1", "Keyframes Only", ""),
    ("2", "Full Animation", ""),
    )

ExportModes = (
    ("1", "All Objects", ""),
    ("2", "Selected Objects", ""),
    )
ExportObjectFilter = {'ARMATURE', 'EMPTY', 'MESH', 'LAMP'}

from bpy.props import StringProperty, EnumProperty, BoolProperty

##------------------------------------------------------------------------------------------
## Utils
##------------------------------------------------------------------------------------------

#returns object children			
def GetObjectChildren(Parent):
    return [Object for Object in Parent.children
                if Object.type in ExportObjectFilter]

#Returns the vertex count of Mesh, counting each vertex for every face.
def GetMeshVertexCount(Mesh):
    VertexCount = 0
    for Face in Mesh.faces:
        VertexCount += len(Face.vertices)
    return VertexCount
	
def GetMaterialTexture(Material):
    if Material:
        #Create a list of Textures that have type "IMAGE"
        ImageTextures = [Material.texture_slots[TextureSlot].texture for TextureSlot in Material.texture_slots.keys() if Material.texture_slots[TextureSlot].texture.type == "IMAGE"]
        #Refine a new list with only image textures that have a file source
        ImageFiles = [bpy.path.basename(Texture.image.filepath) for Texture in ImageTextures if getattr(Texture.image, "source", "") == "FILE"]
        if ImageFiles:
            return ImageFiles[0]
    return None		

##------------------------------------------------------------------------------------------
## SashaNoobEngineExporter
##------------------------------------------------------------------------------------------
class SashaNoobEngineExporter:
    def __init__(self, settings):
                 self.settings = settings
                 self.tablevel = 0
                 self.resources = list()
                 self.staticLights = list()
                 self.defaultCamera = None
				 
    def log(self, text):
        finaltext="{}{}".format("   " * self.tablevel, text )
        print( finaltext )
		
    def logtab(self,v):
        self.tablevel +=v
	
    def AddWorldResource(self,res):
         self.resources.append( res )
		 
    def AddStaticLight(self,light):
        self.staticLights.append( light )
	
    def Export(self):
        self.log( "---------------- sasha-noob-engine Export to : {}".format(self.settings.FilePath) )
        self.logtab( 1 )
		
        self.SelectExportObjects()
        self.ExportObjects(self.exportList)
		
        #write world file
        self.log( "Open File" )
        self.file = open(self.settings.FilePath, "w")
		
        self.GenerateFileHeader()
        self.GenerateFileContent()
		
        self.logtab( -1 )
        self.log( "Close File" ) 
        self.file.close()
		
    def GenerateFileContent(self):
        tl = 0
        self.file.write( "\n{}<world>".format( "\t" * tl ) )
        tl+=1
        self.GenerateResources( tl )
        self.GenerateDefCamera( tl )		
        self.GenerateStaticLights( tl )

        self.file.write("\n{}<children>".format( "\t" * tl ) )
        tl+=1
        self.GenerateObjects( tl, self.exportList )
        tl-=1
        self.file.write("\n{}</children>".format( "\t" * tl ) )
		
        tl-=1
        self.file.write( "\n{}</world>".format( "\t" * tl ) )
		
    def GenerateDefCamera(self,tl):
        if self.defaultCamera == None :
            return
		
        self.file.write( "\n{}<!-- world default camera -->".format( "\t" * tl ) )
        self.file.write( "\n{}<camera>".format( "\t" * tl ) )
        tl +=1
		
        renderSettings = self.settings.context.scene.render
		
        position = self.defaultCamera.matrix_world.to_translation()
		
        cameraUp = Vector(( 0.0, 1.0, 0.0 ))
        cameraLookAt = Vector(( 0.0, 0.0, -1.0 ))
		
        rotationMatrix = self.defaultCamera.matrix_world.to_3x3();
		
        cameraUp = rotationMatrix * cameraUp
        cameraLookAt = rotationMatrix * cameraLookAt
		
        clip_start = self.defaultCamera.data.clip_start
        clip_end = self.defaultCamera.data.clip_end
        fov = self.defaultCamera.data.angle
        aspect = renderSettings.resolution_y / renderSettings.resolution_x  
		
        self.file.write( "\n{}<position x=\"{:9f}\" y=\"{:9f}\" z=\"{:9f}\"/>".format( "\t" * tl, position[0], position[1], position[2] ) )
        self.file.write( "\n{}<lookat x=\"{:9f}\" y=\"{:9f}\" z=\"{:9f}\"/>".format( "\t" * tl, cameraLookAt[0], cameraLookAt[1], cameraLookAt[2] ) )
        self.file.write( "\n{}<up x=\"{:9f}\" y=\"{:9f}\" z=\"{:9f}\"/>".format( "\t" * tl, cameraUp[0], cameraUp[1], cameraUp[2] ) )

        self.file.write( "\n{}<clip plane.near=\"{:9f}\" plane.far=\"{:9f}\"/>".format( "\t" * tl, clip_start, clip_end ) )
        self.file.write( "\n{}<projection fov=\"{:9f}\" aspect=\"{:9f}\"/>".format( "\t" * tl, fov, aspect ) )
		
        tl -=1
        self.file.write( "\n{}</camera>".format( "\t" * tl ) )
       		
		
    def GenerateResources(self, tl):
        self.file.write( "\n{}<!-- load resources -->".format( "\t" * tl ) )
        self.file.write( "\n{}<resources>".format( "\t" * tl ) )
        tl+=1
		
        for res in self.resources:
            self.file.write("\n{}{}".format( "\t" * tl, res ) )
			
        tl-=1
        self.file.write( "\n{}</resources>".format( "\t" * tl ) )
		
    def GenerateStaticLights(self, tl):
        self.file.write( "\n{}<!-- global static lights -->".format( "\t" * tl ) )
        self.file.write( "\n{}<lights.static>".format( "\t" * tl ) )
        tl+=1
		
        for light in self.staticLights:
            self.file.write("\n{}{}".format( "\t" * tl, light ) )
			
        tl-=1
        self.file.write( "\n{}</lights.static>".format( "\t" * tl ) )
		
		
    def GenerateObjects(self, tl, objectList):
        for object in objectList:
            self.GenerateObject( tl, object )

    def GenerateObject(self, tl, object):
        if object.type == "MESH":
            self.GenerateMeshObject(tl, object)
	
    def GenerateMeshObject(self, tl, object):
        rname = "{}.{}".format(self.settings.Prefix, object.name)	
        self.file.write( "\n{}<engine.object.mesh name=\"{}\" mesh=\"{}\">".format( "\t" * tl, rname, rname ) )
        tl +=1
        self.file.write( "\n{}<lights.static.use/>".format( "\t" * tl ) )
        self.GenerateMatrix(tl, object.matrix_local)
        tl -=1
        self.file.write( "\n{}</engine.object.mesh>".format( "\t" * tl ) )
	
    def GenerateFileHeader(self):
        self.log("Write file header")
		
        self.file.write( "<!--\nFile exported from Blender using sasha-noob-engine script " ) 
        self.file.write( "\n-->")
		
    def GenerateMatrix(self, tl, matrix):
        _v11 = matrix[0][0]
        _v12 = matrix[1][0]
        _v13 = matrix[2][0]
        _v14 = matrix[3][0]

        _v21 = matrix[0][1]
        _v22 = matrix[1][1]
        _v23 = matrix[2][1]
        _v24 = matrix[3][1]

        _v31 = matrix[0][2]
        _v32 = matrix[1][2]
        _v33 = matrix[2][2]
        _v34 = matrix[3][2]

        _v41 = matrix[0][3]
        _v42 = matrix[1][3]
        _v43 = matrix[2][3]
        _v44 = matrix[3][3]
		
        self.file.write( "\n{}<transformation type=\"matrix\" \
_11=\"{:9f}\" _12=\"{:9f}\" _13=\"{:9f}\" _14=\"{:9f}\" \
_21=\"{:9f}\" _22=\"{:9f}\" _23=\"{:9f}\" _24=\"{:9f}\" \
_31=\"{:9f}\" _32=\"{:9f}\" _33=\"{:9f}\" _34=\"{:9f}\" \
_41=\"{:9f}\" _42=\"{:9f}\" _43=\"{:9f}\" _44=\"{:9f}\" \
/>".format( "\t" * tl , _v11, _v12, _v13, _v14, _v21, _v22, _v23, _v24, _v31, _v32, _v33, _v34, _v41, _v42, _v43, _v44  ) )
 	
    def SelectExportObjects(self):
        #all objects
        if self.settings.ExportMode == 1:
            self.exportList = [Object for Object in self.settings.context.scene.objects
                               if Object.type in ExportObjectFilter
                               and Object.parent is None]
        else:
            ExportList = [Object for Object in self.settings.context.selected_objects
                          if Object.type in ExportObjectFilter]
            self.exportList = [Object for Object in ExportList
                               if Object.parent not in ExportList]
							   
        self.log("Selected objects: {}".format(self.exportList))
		
        camObjects = [Object for Object in self.settings.context.scene.objects
                               if Object.type in {"CAMERA"}
                               and Object.parent is None]
							   
        if len( camObjects ) > 0:
            self.log("Found cameras: {}".format(camObjects))
		
            selectedCameras = [Object for Object in camObjects
                               if Object.name=="Camera"]

            self.log("Seleceted cameras: {}".format(selectedCameras))
		
            if len( selectedCameras ) == 0:
                selectedCameras = camObjects
				
            self.defaultCamera = selectedCameras[0]
            self.log("Selected default camera : {}".format( self.defaultCamera ) )

		
    def ExportObjects(self,objectList):
        self.log("Start exporting objects...")
        self.logtab( 1 )
		
        for object in objectList:
            self.log("Export Object: {} type {} ...".format(object.name, object.type) )
			
            self.logtab( 1 )
            if object.type == "MESH":
                self.ExportMesh(object)
            elif object.type == "LAMP":
                self.ExportLight(object)
            self.logtab( -1 )
				
        self.logtab( -1 )

    def ExportLight(self, light):
        data = light.data
        if data.type == "POINT":
            self.ExportLightPoint( light )
        else:
            self.log( "Light ignored : {} {}".format( light.name, data.type ) )
		
    def ExportLightPoint(self,light):
        lightOut = ""
        tl = 0
        self.AddStaticLight( "{}<light.point>".format( "\t" * tl ) )
        tl+=1
		
        position = light.matrix_world.to_translation()
		
        if light.data.use_diffuse:
            colorDiffuse = light.data.color
        else:
            colorDiffuse = (0.0,0.0,0.0)
		
        if light.data.use_specular:
            colorSpecular = light.data.color
        else:
            colorSpecular = (0.0,0.0,0.0)
			
        colorAmbient = light.data.color
        maxdistance = light.data.distance
        attenuation = 0.0
		
        self.AddStaticLight("{}<position x=\"{:9f}\" y=\"{:9f}\" z=\"{:9f}\" />".format( "\t" * tl, position[0], position[1], position[2] ) )
        self.AddStaticLight("{}<color.diffuse r=\"{:4f}\" g=\"{:4f}\" b=\"{:4f}\" />".format( "\t" * tl, colorDiffuse[0], colorDiffuse[1], colorDiffuse[2] ) )
        self.AddStaticLight("{}<color.specular r=\"{:4f}\" g=\"{:4f}\" b=\"{:4f}\" />".format( "\t" * tl, colorSpecular[0], colorSpecular[1], colorSpecular[2] ) )
        self.AddStaticLight("{}<color.ambient r=\"{:4f}\" g=\"{:4f}\" b=\"{:4f}\" />".format( "\t" * tl, colorAmbient[0], colorAmbient[1], colorAmbient[2] ) )
        self.AddStaticLight("{}<maxdistance value= \"{:9f}\" />".format( "\t" * tl, maxdistance ) )
        self.AddStaticLight("{}<attenuation value= \"{:9f}\" />".format( "\t" * tl, attenuation ) )
        tl-=1
        self.AddStaticLight("{}</light.point>".format( "\t" * tl ) )
		
    def ExportMesh(self, object):
        self.log("Generating Mesh...")
        if self.settings.ApplyModifiers:
            if self.settings.ExportArmatures:
                #Create a copy of the object and remove all armature modifiers so an unshaped
                #mesh can be created from it.
                copyObject = object.copy()
				
                for Modifier in [Modifier for Modifier in copyObject.modifiers if Modifier.type == "ARMATURE"]:
                    copyObject.modifiers.remove(Modifier)
                mesh = copyObject.to_mesh(bpy.context.scene, True, "PREVIEW")
            else:
                mesh = object.to_mesh(bpy.context.scene, True, "PREVIEW")
        else:
            mesh = object.to_mesh(bpy.context.scene, False, "PREVIEW")
        self.log("Done")
		
        self.WriteMesh( mesh, object.name )
		
        if self.settings.ApplyModifiers and self.settings.ExportArmatures:
            bpy.data.objects.remove(copyObject)
        bpy.data.meshes.remove(mesh)
	
    def WriteMesh(self,mesh,name):
        self.AddWorldResource( "<!-- object {} -->".format( name ) )
		
        self.WriteMeshVB(mesh,name)
        self.WriteMeshIB(mesh,name)

        #writing mesh definitoin file
        fname = "{}_mesh_{}.xml".format(self.settings.Prefix, name)
        rname = "{}.{}".format(self.settings.Prefix, name)
		
        fileName = os.path.join( self.settings.Path, fname )
        self.log("Writing mesh file {} ...". format(fileName) )
        fmesh = open(fileName, "w")
        self.logtab( 1 )
		
        tl = 0
        fmesh.write( "{}<mesh>".format( "\t" * tl ) )
        tl+=1
        fmesh.write( "\n{}<vbuffer name=\"{}\"/>".format( "\t" * tl, rname ) )
        fmesh.write( "\n{}<ibuffer name=\"{}\"/>".format( "\t" * tl, rname ) )
        self.WriteMeshMaterials( fmesh, tl, mesh, name )
        tl-=1
        fmesh.write( "\n{}</mesh>".format( "\t" * tl ) )
		
        fmesh.close()	
        self.logtab( -1 )
        self.log("Done")
        self.AddWorldResource( "<mesh name=\"{}\" path=\"%gameres%/{}\"/>".format( rname, fname ) )
		
		
		
    def WriteMeshIB(self,mesh,name):
        fname = "{}_mesh_{}.ib".format(self.settings.Prefix, name)
        rname = "{}.{}".format(self.settings.Prefix, name)

        fileName = os.path.join( self.settings.Path, fname )
        self.log("Writing vb file {} ...". format(fileName) )
        self.logtab( 1 )
		
        cvb = open(fileName, "w")

        Index = 0
        for Face in mesh.faces:
            vcount = len( Face.vertices )
            if vcount == 3 :
                cvb.write( "{} {} {}\n".format(Index, Index + 1, Index + 2 ) )
            elif vcount == 4 :
                cvb.write( "{} {} {} {} {} {}\n".format(Index, Index + 1, Index + 2, Index, Index + 2, Index + 3 ) )
            else:
                self.log("Warning !!! unknown face type {}".format( Face.vertices ) )
				
            Index += vcount
  
        cvb.close()
        self.logtab( -1 )
        self.log("Done")
        self.AddWorldResource( "<ibuffer name=\"{}\" path=\"%gameres%/{}\"/>".format( rname, fname ) )
		
    
    def GetMeshUVCoord(self,Mesh):
        self.log("Get UV coordinates..." )
        vertexList = list()
		
        UVCoordinates = None
        for UV in Mesh.uv_textures:
            if UV.active_render:
                UVCoordinates = UV.data
                break
        if UVCoordinates == None:
            return vertexList
			
        for Face in UVCoordinates:
            Vertices = []
            for Vertex in Face.uv:
                 Vertices.append(tuple(Vertex))
			
            if self.settings.CoordinateSystem == 1:
                Vertices = Vertices[::-1]
				
            for Vertex in Vertices:
                vertexList.append( Vertex )
				
        self.log("Done {} count".format( len(vertexList) ) )
        return vertexList
	
    def WriteMeshVB(self,mesh,name):
	
        VertexCount = GetMeshVertexCount(mesh)
        self.log( "vertex count {}".format( VertexCount ) )
        uvList = self.GetMeshUVCoord(mesh)
		
        if VertexCount == 0:
            uvPerVertex = 0
        else:
            uvPerVertex = len( uvList ) / VertexCount
		
        fname = "{}_mesh_{}.vb".format(self.settings.Prefix, name)
        rname = "{}.{}".format(self.settings.Prefix, name)
		
        fileName = os.path.join( self.settings.Path, fname )
        self.log("Writing vb file {} ...". format(fileName) )
        self.logtab( 1 )
		
        cvb = open(fileName, "w")
        cvb.write("XYZ|NORMAL")
        
        if uvPerVertex > 0 :
             cvb.write("|TX1")
			 
        Index = 0
		
        for Face in mesh.faces:
            Vertices = list(Face.vertices)

            if self.settings.CoordinateSystem == 1:
                 Vertices = Vertices[::-1]
			
            for Vertex in [mesh.vertices[Vertex] for Vertex in Vertices]:
                Position = Vertex.co
				
                if Face.use_smooth:
                    Normal = Vertex.normal
                else:
                    Normal = Face.normal
                if self.settings.FlipNormals:
                    Normal = -Normal
					
                cvb.write("\n{:9f} {:9f} {:9f}\t{:9f} {:9f} {:9f}".format( Position[0], Position[1], Position[2], Normal[0], Normal[1], Normal[2]) )
                if uvPerVertex > 0 :
                    uv = uvList[Index]
                    cvb.write( "\t{:9f} {:9f}".format( uv[0], 1.0 - uv[1] ) )
					
                Index += 1
				
        cvb.close()
        self.logtab( -1 )
        self.log("Done")
        self.AddWorldResource( "<vbuffer name=\"{}\" path=\"%gameres%/{}\"/>".format( rname, fname ) )
			
    def WriteMeshMaterials(self,fmesh, tl,mesh,name):
        self.log( "Get materials..." )
        self.logtab( 1 )
		
        Materials = mesh.materials
        if Materials.keys():
            MaterialIndexes = {}
			
            for Face in mesh.faces:
                if Materials[Face.material_index] not in MaterialIndexes:
                    MaterialIndexes[Materials[Face.material_index]] = len(MaterialIndexes)
					
            Materials = [Item[::-1] for Item in MaterialIndexes.items()]
            Materials.sort()
            for Material in Materials:
                self.WriteMeshMaterial( fmesh, tl, Material[1], name )
					
            self.log( "Material indexes : {}".format( MaterialIndexes ) )
        else:
            self.log("Warning !!! No materials found")
			
        self.logtab( -1 )
        self.log( "Done" )
			
    def WriteMeshMaterial(self,fmesh, tl,material,name):
        if material:
            self.log("Material : {}".format( material.name ) )
			
            Texture = None
		
            if self.settings.ExportTextures:
                Texture = GetMaterialTexture( material )
		   
            if Texture:
                self.log("TextureFilename {{\"{}\";}}\n".format(Texture))
                fmesh.write( "\n{}<material type=\"texture\" name=\"{}\"/>".format( "\t" * tl, name ) )
            else:
                Diffuse = list(material.diffuse_color)
                Diffuse.append( material.alpha )
                Ambient = list( Vector(Diffuse) * material.ambient )
                Specular = list( material.specular_color )
                hardness = material.specular_hardness / 8.0
			
                fmesh.write( "\n{}<material type=\"solid\" name=\"{}\">".format( "\t" * tl, name ) )
                tl+=1
                fmesh.write( "\n{}<color.ambient r=\"{:9f}\" g=\"{:9f}\" b=\"{:9f}\" a=\"{:9f}\"/>".format( "\t" * tl, Ambient[0], Ambient[1], Ambient[2], Ambient[3] ) )
                fmesh.write( "\n{}<color.diffuse intensity=\"{:9f}\" r=\"{:9f}\" g=\"{:9f}\" b=\"{:9f}\" a=\"{:9f}\"/>".format( "\t" * tl, material.diffuse_intensity, Diffuse[0], Diffuse[1], Diffuse[2], Diffuse[3] ) )
                fmesh.write( "\n{}<color.specular intensity=\"{:9f}\" hardness=\"{:9f}\" r=\"{:9f}\" g=\"{:9f}\" b=\"{:9f}\" />".format( "\t" * tl, material.specular_intensity, hardness, Specular[0], Specular[1], Specular[2] ) )
				
                tl-=1
                fmesh.write( "\n{}</material>".format( "\t" * tl ) )
				
			
        else:
            self.log("Set default material")
            fmesh.write( "\n{}<material name=\"{}\"/> type=\"solid\"".format( "\t" * tl, name ) )

##------------------------------------------------------------------------------------------
## SNEExport
##------------------------------------------------------------------------------------------
class SNEExport(bpy.types.Operator):
    """Export to the sasha-noob-engine model format (.xml)"""

    bl_idname = "export.sashanoobengine"
    bl_label = "Export sasha-noob-engine"

    filepath = StringProperty(subtype='FILE_PATH')

    #Coordinate System
    CoordinateSystem = EnumProperty(
        name="System",
        description="Select a coordinate system to export to",
        items=CoordinateSystems,
        default="2")

    #General Options
    FlipNormals = BoolProperty(
        name="Flip Normals",
        description="",
        default=False)
    ApplyModifiers = BoolProperty(
        name="Apply Modifiers",
        description="Apply object modifiers before export",
        default=False)
    IncludeFrameRate = BoolProperty(
        name="Include Frame Rate",
        description="Include the AnimTicksPerSecond template which is used by " \
                    "some engines to control animation speed",
        default=False)
    ExportTextures = BoolProperty(
        name="Export Textures",
        description="Reference external image files to be used by the model",
        default=True)
    ExportArmatures = BoolProperty(
        name="Export Armatures",
        description="Export the bones of any armatures to deform meshes",
        default=False)
    ExportAnimation = EnumProperty(
        name="Animations",
        description="Select the type of animations to export. Only object " \
                    "and armature bone animations can be exported. Full " \
                    "Animation exports every frame",
        items=AnimationModes,
        default="0")

    #Export Mode
    ExportMode = EnumProperty(
        name="Export",
        description="Select which objects to export. Only Mesh, Empty, " \
                    "and Armature objects will be exported",
        items=ExportModes,
        default="1")

    Verbose = BoolProperty(
        name="Verbose",
        description="Run the exporter in debug mode. Check the console for output",
        default=False)

    def execute(self, context):
        #Append .xml
        FilePath = bpy.path.ensure_ext(self.filepath, ".xml")

        config = SNEExporterSettings(context,
                                         FilePath,
                                         CoordinateSystem=self.CoordinateSystem,
                                         FlipNormals=self.FlipNormals,
                                         ApplyModifiers=self.ApplyModifiers,
                                         IncludeFrameRate=self.IncludeFrameRate,
                                         ExportTextures=self.ExportTextures,
                                         ExportArmatures=self.ExportArmatures,
                                         ExportAnimation=self.ExportAnimation,
                                         ExportMode=self.ExportMode,
                                         Verbose=self.Verbose)
		
        exporter = SashaNoobEngineExporter(config)
        exporter.Export()
		
        return {"FINISHED"}

    def invoke(self, context, event):
        if not self.filepath:
            self.filepath = bpy.path.ensure_ext(bpy.data.filepath, ".xml")
        WindowManager = context.window_manager
        WindowManager.fileselect_add(self)
        return {"RUNNING_MODAL"}


def menu_func(self, context):
    self.layout.operator(SNEExport.bl_idname, text="sasha-noob-engine (.xml)")


def register():
    bpy.utils.register_module(__name__)

    bpy.types.INFO_MT_file_export.append(menu_func)


def unregister():
    bpy.utils.unregister_module(__name__)

    bpy.types.INFO_MT_file_export.remove(menu_func)


if __name__ == "__main__":
    register()
