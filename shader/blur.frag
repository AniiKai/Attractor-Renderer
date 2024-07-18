#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D image;

uniform bool horizontal;
//float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
float weight[9] = float[9] (0.2659615203, 0.212965337, 0.1613138163, 0.1093400498, 0.06631809253, 0.03599397768, 0.0174812594, 0.007597324016, 0.002954565608);

void main()
{
	for (int i=0; i<9; i++) {
		weight[i] *= 0.75;
	}
     vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
     vec3 result = texture(image, TexCoords).rgb * weight[0];
     if(horizontal)
     {
         for(int i = 1; i < 9; ++i)
         {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
         }
     }
     else
     {
         for(int i = 1; i < 9; ++i)
         {
             result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
             result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
         }
     }
     FragColor = vec4(result, 1.0);
}
