
-- this function is called each frame for the associated object
function d3Object_AI( dt )
	totalTime = totalTime + dt
	local v = ( 1.0 + math.sin( totalTime ) ) / 2.0
	
	render.afterEffect.SetParam( 0, 'level.r', v )
	render.afterEffect.SetParam( 0, 'level.g', v )
end

-- this functon is called when the object is initialized
function d3Object_Init()
	totalTime = 0.0
end
