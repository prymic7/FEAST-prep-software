	#shader vertex
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	layout (location = 2) in vec2 aTexCoord;

	out vec3 ourColor;
	out vec2 TexCoord;
	uniform int xReverse;
	uniform int yReverse;

	void main()
	{
		int xRev = xReverse;
		int yRev = yReverse;
		gl_Position = vec4(aPos, 1.0);
		ourColor = aColor;
		TexCoord = vec2(xRev * aTexCoord.x, yRev * aTexCoord.y);
	}

	#shader fragment
	#version 330 core
	vec4 colorHolder;
	out vec4 FragColor;

	in vec3 ourColor;
	in vec2 TexCoord;

	// texture samplers
	uniform sampler2D texture1;
	uniform sampler2D texture2;

	void main()
	{
		vec4 color1 = texture(texture1, TexCoord);
		vec4 color2 = texture(texture2, TexCoord);

		// Calculate the luminance of the color (convert to grayscale)
		float luminance = 0.2126 * color1.r + 0.7152 * color1.g + 0.0722 * color1.b;

		// Discard fragments with a luminance value above a certain threshold
		if (luminance > 0.8) {
			discard;
		}

		// Mix based on the alpha channel of texture1
		FragColor = mix(color1, color2, color1.a);
	}	
