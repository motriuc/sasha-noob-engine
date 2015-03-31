# Introduction #

The following example shows how to create a simple world in sasha-noob-engine

# The Steps #


  * create _mesh\_torus.xml_ and add it to the project
```
<mesh>
        <primitive type="torus" radius="0.5" tube.radius="0.2" segments="30" tube.segments="20"  />
        
        <material type="texture" >
                <texture name="main.red.ch" />
        </material>
</mesh>
```

  * add a texture to the project ( only png files are supported for now )
![http://wiki.sasha-noob-engine.googlecode.com/git/image_texture_red_checker.png](http://wiki.sasha-noob-engine.googlecode.com/git/image_texture_red_checker.png)

  * create a lua script file _torusrotate.lua_ and add it to the project
```
-- this function is called each frame for the associated object
function d3Object_AI( dt )
        self.RotateX( dt )
        self.RotateY( dt )
        self.RotateZ( dt )
end
```

  * create and add world definition file _world.xml_ to the project
```
<world>
        <!-- load resources -->
        <resources>
                <texture name="main.red.ch" path="%gameres%/red_checker.png" />
                <mesh name="main.mesh" path="%gameres%/mesh_torus.xml"/>
        </resources>
        
        <!-- lights -->
        <lights.static>
                <light.point>
                        <color r="1.0" g="1.0" b="1.0" a="1.0" />
                        <position x="0.0" y="0.0" z="-15.0" />
                </light.point>
        </lights.static>
        
        <children>
                <engine.object.mesh mesh="main.mesh" lua="%gameres%/torusrotate.lua">
                        <lights.static.use />                   
                </engine.object.mesh>   
        </children>
</world>

```

  * compile and run the project. The result will be a rotated torus.

![http://wiki.sasha-noob-engine.googlecode.com/git-history/master/image_result_first_app.png](http://wiki.sasha-noob-engine.googlecode.com/git-history/master/image_result_first_app.png)