#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

in vec3 vNormal[];
out vec3 Normal;

uniform float time;

vec3 getNormal() 
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal) 
{
	//c*(t/=d)*t + b
	float t = time/1.0;
	float magnitude = 5.0;
	float length = clamp(magnitude * t * t + 0.0, 0.0, magnitude);//((sin(time) + 1.0) / 2.0) * magnitude;
	vec3 direction  = normal * length;
	return position + vec4(direction, 0.0);
}

void subdivide() 
{
	vec3 normalDir = getNormal();

    gl_Position =  explode(gl_in[0].gl_Position, normalDir);
    Normal = vNormal[0]; 
    EmitVertex();

    gl_Position =  explode((gl_in[0].gl_Position + gl_in[1].gl_Position)*0.5, normalDir);
    Normal = vNormal[0]; 
    EmitVertex();

    gl_Position =  explode((gl_in[0].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    Normal = vNormal[2]; 
    EmitVertex();

    EndPrimitive();

	gl_Position =  explode(gl_in[1].gl_Position, normalDir);
    Normal = vNormal[1]; 
    EmitVertex();

    gl_Position =  explode((gl_in[1].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    Normal = vNormal[1]; 
    EmitVertex();

     gl_Position =  explode((gl_in[0].gl_Position + gl_in[1].gl_Position)*0.5, normalDir);
    Normal = vNormal[0]; 
    EmitVertex();

    EndPrimitive();


	gl_Position =  explode(gl_in[2].gl_Position, normalDir);
    Normal = vNormal[2]; 
    EmitVertex();

	gl_Position =  explode((gl_in[0].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    Normal = vNormal[2]; 
    EmitVertex();

    gl_Position =  explode((gl_in[1].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    Normal = vNormal[1]; 
    EmitVertex();

    EndPrimitive();

    gl_Position =  explode((gl_in[0].gl_Position + gl_in[1].gl_Position)*0.5, normalDir);
    EmitVertex();
    gl_Position =  explode((gl_in[1].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    EmitVertex();
    gl_Position =  explode((gl_in[0].gl_Position + gl_in[2].gl_Position)*0.5, normalDir);
    EmitVertex();

    EndPrimitive();


}


void justExplode() 
{
	vec3 normalDir = getNormal();
    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = explode(gl_in[i].gl_Position, normalDir);
        Normal = vNormal[i]; 
        EmitVertex();
    }
    EndPrimitive();
}

void main() 
{    
	justExplode();
	//subdivide();
}
