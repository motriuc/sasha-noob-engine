-- create mesh
function Primitive_CreateMesh()
	local ucount = 50
	local vcount = 50
	local k = 1.2
	local k1 = 1.2
	local a = 1.6
	
	local ubegin = 0.0
	local uend = 8 * math.pi
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
			
			self.AddPoint( x / 200, y / 200, z/ 200 + 0.5 )
			
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
	return 0;
end

-- estimate index count
function Primitive_EstimateIndexCount()
	return 0;
end