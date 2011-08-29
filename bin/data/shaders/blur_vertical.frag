uniform sampler2DRect texture;
uniform float blurSize;

void main()
{

	/*float offset[3];
	float weight[3];
	
	offset[0] = 0.0;
	offset[1] = 1.3846153846;
	offset[2] = 3.2307692308;

	weight[0] = 0.2270270270;
	weight[1] = 0.3162162162;
	weight[2] = 0.0702702703;

	gl_FragColor = texture2DRect( texture, vec2(gl_FragCoord)) * weight[0];
	
	for (int i=1; i<3; i++) {
		gl_FragColor += texture2DRect( texture, ( vec2(gl_FragCoord)+vec2(0.0, offset[i]) ) ) * weight[i];
		gl_FragColor += texture2DRect( texture, ( vec2(gl_FragCoord)-vec2(0.0, offset[i]) ) ) * weight[i];
	}*/
	
	vec4 sum = vec4(0.0);
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
	//sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - 6.0*blurSize)) *0.0000000061;
	//sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - 5.0*blurSize)) *0.0000014867;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - 4.0*blurSize)) * 0.0001338302;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - 3.0*blurSize)) * 0.0044318484;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - 2.0*blurSize)) * 0.0539909665;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - blurSize)) * 0.2419707245;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y)) * 0.3989422804;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + blurSize)) * 0.2419707245;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + 2.0*blurSize)) * 0.0539909665;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + 3.0*blurSize)) * 0.0044318484;
	sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + 4.0*blurSize)) * 0.0001338302;
	//sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + 5.0*blurSize)) *0.0000014867;
	//sum += texture2DRect(texture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + 6.0*blurSize)) *0.0000000061;
	
	sum.a = (sum.r + sum.b + sum.g);
	
	gl_FragColor = sum;
   
}