
-- this function is called each frame for the associated object
function d3Object_AI( dt )

    local v = test()
--	self.RotateX( v[1] )
	
	v = test2()
	self.RotateX( v[1] )
	
--	self.RotateX( dt )
--	self.RotateY( dt )
--	self.RotateZ( dt )
end

-- this functon is called when the object is initialized
function d3Object_Init()
end
