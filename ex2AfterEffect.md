# Introduction #

The following example shows how to add an after effect to word in sasha-noob-engine.


# The Steps #

Add your content here.  Format your content with:
  * Create the after effect definition file _after\_effect.xml_
```
<aftereffect>
        <filter type="color" level.r="1.0" level.g="1.0" level.b="1.0" contrast="1.0"/>
</aftereffect>
```

  * Create a lua file which will animate the after effect _world.lua_:
```
-- this function is called each frame for the associated object
function d3Object_AI( dt )
        totalTime = totalTime + dt
        local v = ( 1.0 + math.sin( totalTime ) ) / 2.0
        
        world.afterEffect.SetParam( 0, 'level.r', v )
        world.afterEffect.SetParam( 0, 'level.g', v )
end

-- this functon is called when the object is initialized
function d3Object_Init()
        totalTime = 0.0
end
```
  * Update _world.xml_ file:
```
<!-- set world lua script -->
<world lua="%gameres%/world.lua">
        <!-- load resources -->
        <resources>
                ...
                <!-- load after effect definition -->
                <aftereffect name="main.aff" path="%gameres%/after_effect.xml" />
               ...
        </resources>
        
         ...
        <!-- set current after effect -->
        <aftereffect name="main.aff"/>
         ...       
</world>
```