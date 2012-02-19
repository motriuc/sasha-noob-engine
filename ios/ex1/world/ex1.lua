

-- this function is called each frame for the associated object
function d3Object_AI( dt )
	self.RotateX( dt )
	self.RotateY( dt / 4 )
end

-- this functon is called when the object is initialized
function d3Object_Init()
end
