# Introduction #

Engine Lua API. (Draft)


# LUA sasha-noob-engine API #

## Lua math API ##
| **function** | **description**  |
|:-------------|:-----------------|
|math.abs (x)|Returns the absolute value of x.|
|math.acos (x)|Returns the arc cosine of x (in radians).|
|math.asin (x)|Returns the arc sine of x (in radians).|
|math.atan (x)|Returns the arc tangent of x (in radians).|
|math.atan2 (y, x)|Returns the arc tangent of y/x (in radians), but uses the signs of both parameters to find the quadrant of the result. (It also handles correctly the case of x being zero.)|
|math.ceil (x)|Returns the smallest integer larger than or equal to x.|
|math.cos (x)|Returns the cosine of x (assumed to be in radians).|
|math.cosh (x)|Returns the hyperbolic cosine of x.|
|math.deg (x)|Returns the angle x (given in radians) in degrees.|
|math.exp (x)|Returns the value ex.|
|math.floor (x)|Returns the largest integer smaller than or equal to x.|
|math.fmod (x, y)|Returns the remainder of the division of x by y that rounds the quotient towards zero.|
|math.frexp (x)|Returns m and e such that x = m2e, e is an integer and the absolute value of m is in the range [0.5, 1) (or zero when x is zero).|
|math.huge|The value HUGE\_VAL, a value larger than or equal to any other numerical value.|
|math.ldexp (m, e)|Returns m2e (e should be an integer).|
|math.log (x)|Returns the natural logarithm of x.|
|math.log10 (x)|Returns the base-10 logarithm of x.|
|math.max (x, ···)|Returns the maximum value among its arguments.|
|math.min (x, ···)|Returns the minimum value among its arguments.|
|math.modf (x)|Returns two numbers, the integral part of x and the fractional part of x.|
|math.pi|The value of pi.|
|math.pow (x, y)|Returns xy. (You can also use the expression x^y to compute this value.)|
|math.rad (x)|Returns the angle x (given in degrees) in radians.|
|math.random ([[, n](m.md)])|This function is an interface to the simple pseudo-random generator function rand provided by ANSI C.<br>When called without arguments, returns a uniform pseudo-random real number in the range [0,1). <br>When called with an integer number m, math.random returns a uniform pseudo-random integer in the range [1, m]. <br>When called with two integer numbers m and n, math.random returns a uniform pseudo-random integer in the range [m, n]. <br>
<tr><td>math.randomseed (x)</td><td>Sets x as the "seed" for the pseudo-random generator: equal seeds produce equal sequences of numbers.</td></tr>
<tr><td>math.sin (x)</td><td>Returns the sine of x (assumed to be in radians).</td></tr>
<tr><td>math.sinh (x)</td><td>Returns the hyperbolic sine of x.</td></tr>
<tr><td>math.sqrt (x)</td><td>Returns the square root of x. (You can also use the expression x^0.5 to compute this value.)</td></tr>
<tr><td>math.tan (x)</td><td>Returns the tangent of x (assumed to be in radians).</td></tr>
<tr><td>math.tanh (x)</td><td>Returns the hyperbolic tangent of x. </td></tr></tbody></table>

<h2>3d Object functions - <i>self.</i></h2>

The 3d objects functions makes changes on the object to which the script was associated.<br>
<br>
<table><thead><th> <b>function</b> </th><th> <b>description</b>  </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> self.<b>Move</b>( dx, dy dz ) </td><td> move the object by <i>dx, dy, dz</i> </td><td> <code> self.Move( 1, 0.5, 0.0) </code> </td></tr>
<tr><td> self.<b>RotateX</b>( a ) </td><td> rotate the object around of the X axis by <i>a</i> angle. The angle is specified in radians </td><td> <code> self.RotateX( math.pi / 2.0 ) </code>  </td></tr>
<tr><td> self.<b>RotateY</b>( a ) </td><td> rotate the object around of the Y axis by <i>a</i> angle. The angle is specified in radians </td><td> <code> self.RotateY( math.pi / 2.0 ) </code>  </td></tr>
<tr><td> self.<b>RotateZ</b>( a ) </td><td> rotate the object around of the X axis by <i>a</i> angle. The angle is specified in radians </td><td> <code> self.RotateX( math.pi / 2.0 ) </code>  </td></tr>
<tr><td> self.<b>Scale</b>( sx, sy, sz ) </td><td> slcale the object by <i>sx, sy, sz</i> </td><td> <code> self.Scale( 2.0, 2.0, 2.0 ) </code>  </td></tr></tbody></table>

<h2>Camera control functions - <i>world.camera.</i></h2>

<table><thead><th> <b>function</b> </th><th> <b>description</b>  </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> world.camera.<b>Move</b>( dx, dy, dz )  </td><td> moves the current world camera by <i>dx, dy, dz</i> </td><td> <code> world.camera.Move( 1, 0.5, 0.0) </code> </td></tr>
<tr><td> world.camera.<b>MoveUp</b>( d ) </td><td> moves the current world camera up by <i>d</i> distance </td><td> <code> world.camera.MoveUp( 0.3 ) </code> </td></tr>
<tr><td> world.camera.<b>MoveForward</b>( d )</td><td> moves the current world camera forward by <i>d</i> distance </td><td> <code> world.camera.MoveForward ( 0.5 ) </code></td></tr>
<tr><td> world.camera.<b>LookAt</b>( x, y, z ) </td><td> moves the current world camera to look in vector x y z direction </td><td> <code> world.camera.LookAt( 1, 0, 0) </code></td></tr>
<tr><td> world.camera.<b>RotateUp</b>( a )</td><td> rotates the current world camera upwards ( from view point of view ) </td><td> <code> world.camera.RotateUp( math.pi/4 ) </code> </td></tr>
<tr><td> world.camera.<b>RotateLeft</b>( a ) </td><td> rotates the current world camera to the left ( from view point fo view ) </td><td> <code> world.camera.RotateLeft( math.pi/4 ) </code> </td></tr></tbody></table>

<h2>Bullet Physics functions API - <i>world.physics.</i></h2>

<table><thead><th> <b>function</b> </th><th> <b>description</b>  </th><th> <b>Example</b> </th></thead><tbody>
<tr><td> world.physics.<b>SetGravity</b>( x, y, z ) </td><td> Sets the physics world gravity vector. </td><td> <code> world.physics.SetGravity( 0, 0, 10 )</code> </td></tr>
<tr><td> world.physics.static.<b>AddPlane</b>( nx, ny, nz, c ) </td><td> Adds a static plane to the physics engine. returns the id of the object. </td><td> <code> id = world.physics.static.AddPlane( 0, 1, 0, -1 ) </code> </td></tr>
<tr><td> world.physics.rbody.<b>AddSphere</b>( radius, mass ) </td><td> Adds a sphere rigid body to he physics engine. returns the id of the object.</td><td> <code> id = world.physics.rbody.AddSphere( 0.5, 1.0 ) </code></td></tr>
<tr><td> world.physics.<b>Move</b>( id, x, y, z ) </td><td> moves the physics body by <i>x, y, z</i> </td><td> <code> world.physics.Move( id, 0.5, 1.0, 0.0 ) </code> </td></tr></tbody></table>

<h2>Lua mesh functions</h2>
<table><thead><th> <b>function</b> </th><th> <b>description</b>  </th></thead><tbody>
<tr><td> self.<b>AddPoint</b>( x, y z ) </td><td> Adds a vertex (x,y,z) to the lua mesh </td></tr>
<tr><td> self.<b>AddNormal</b>( x, y, z ) </td><td> Adds a normal to the lua mesh vertex </td></tr>
<tr><td> self.<b>AddTexCoord</b>( x, y ) </td><td> Add texture coordinates to the lua mesh vertex </td></tr>
<tr><td> self.<b>AddIndex</b>( i1, i2, i3 ) </td><td> Adds a triangle face with vertexes which have the indexes: i1, i2, i3 </td></tr>