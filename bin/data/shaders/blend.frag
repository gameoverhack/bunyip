uniform sampler2DRect textures[2];

void main()
{

	vec4 kinectLayers;
	vec4 videoLayers;
	
	videoLayers				= texture2DRect(textures[0], gl_TexCoord[0].xy);
	kinectLayers			= texture2DRect(textures[1], gl_TexCoord[0].xy);
	
	vec4 OUT = vec4(0.0);
	
	kinectLayers.a = (kinectLayers.r + kinectLayers.b + kinectLayers.g);
	
	
	
	//OUT.rgb = (kinectLayers.rgb + videoLayers.rgb * kinectLayers.rgb); //(kinectLayers.rgb * kinectLayers.rgb + videoLayers.rgb * (1.0 - kinectLayers.rgb));
	OUT.rgba = kinectLayers.rgba;
	
	gl_FragColor = OUT;

}