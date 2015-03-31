# Introduction #

The following example shows how to creare a Lua defined mesh using sasha-noob-engine

# The Steps #

  * create lua mesh file _mesh\_gen.lua_ and add it to the project
```
ucount = 50
vcount = 50


-- create mesh
function Primitive_CreateMesh()
	local k = 1.2
	local k1 = 1.2
	local a = 1.6
	local scale = 1/200
	local zoffset = 0.5
	
	local ubegin = 0.0
	local uend = 8.1 * math.pi
	local ustep = ( uend - ubegin ) / ucount
	
	local vbegin = 0.0
	local vend = 2 * math.pi
	local vstep = ( vbegin - vend ) / vcount
	
	for iu = 0, ucount, 1 do
		local uv = ubegin + ustep * iu
		
		for iv = 0, vcount, 1 do
			local vv = vbegin + vstep * iv
			
			local vcos = math.cos( vv )
			local vsin = math.sin( vv )
			local usin = math.sin( uv )
			local ucos = math.cos( uv )
			local pk = math.pow( k, uv )
			local pk1 = math.pow( k1, uv )
			
			local x = pk * ( 1 + vcos ) * ucos;
			local y = pk * ( 1 + vcos ) * usin;
			local z = pk * vsin - a * pk1
			
			self.AddPoint( x * scale, y * scale, z * scale + zoffset )
			
			local logk = math.log(  k )
			local logk1 = math.log( k1 )
			
			local dxv = -pk * ucos * vsin;
			local dyv = -pk * usin * vsin;
			local dzv = pk * vcos;
			
			local dxu = ( 1 + vcos ) * pk * ( logk * ucos - usin )
			local dyu = ( 1 + vcos ) * pk * ( logk * usin + ucos )
			local dzu = ( vsin * pk * logk ) - a * pk1 * logk1
			
			local cx = dyv * dzu - dzv * dyu;
			local cy = dzv * dxu - dxv * dzu;
			local cz = dxv * dyu - dyv * dxu;
			
			local h = math.sqrt( cx * cx + cy * cy + cz * cz )
			
			cx = cx / h
			cy = cy / h
			cz = cz / h
			
			self.AddNormal( -cx, -cy, -cz )
				
			self.AddTexCoord( 1.0 - ( 1.0 * iu / ucount ), 1.0 * iv / vcount )
		end
	end

	for iu = 0, ucount-1, 1 do
		
		for iv = 0, vcount-1, 1 do
			local i1 = iu * ( vcount + 1 ) + iv
			local i3 = i1 + 1
			local i2 = i3 + vcount
			local i4 = i2 + 1
			
			self.AddIndex( i1, i3, i2 )
			self.AddIndex( i2, i3, i4 )
		end
	end
end

-- estimate vertex count
function Primitive_EstimateVertexCount()
	return ( ucount + 1 ) * ( vcount + 1 );
end

-- estimate index count
function Primitive_EstimateIndexCount()
	return ucount * vcount * 6;
end
```

  * add a texture to the project ( only png files are supported for now )
> > ![http://wiki.sasha-noob-engine.googlecode.com/git/image_texture_red_checker.png](http://wiki.sasha-noob-engine.googlecode.com/git/image_texture_red_checker.png)

  * create _mesh\_lua.xml_ and add it to the project
```
<mesh>
	<primitive type="lua" path="%gameres%/mesh_gen.lua"  />
	
	<material type="texture" >
		<texture name="main.red.ch" />
	</material>
</mesh>
```

  * create a lua script file _rotate.lua_ and add it to the project
```
-- this function is called each frame for the associated object
function d3Object_AI( dt )
	self.RotateX( dt )
	self.RotateY( dt / 4 )
end
```
  * create and add world definition file _world.xml_ to the project
```
 <world>
	<!-- load resources -->
	<resources>
		<texture name="main.red.ch" path="%gameres%/red_checker.png" />
		<mesh name="main.mesh" path="%gameres%/mesh_lua.xml"/>
	</resources>
	
	<!-- lights -->
	<lights.static>
		<light.point>
			<color r="1.0" g="1.0" b="1.0" a="1.0" />
			<position x="0.0" y="0.0" z="-15.0" />
		</light.point>
	</lights.static>
	
	<children>				
		<engine.object.mesh mesh="main.mesh" lua="%gameres%/rotate.lua">
			<!-- use static lights for this object -->
			<lights.static.use />
		</engine.object.mesh>	
	</children>
</world>
```


  * compile and run the project. The result will be a rotating snail shell:
![http://wiki.sasha-noob-engine.googlecode.com/git/image_ex1_result.png](http://wiki.sasha-noob-engine.googlecode.com/git/image_ex1_result.png)