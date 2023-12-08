        #shader vertex
        #version 330 core
        layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
        out vec2 TexCoords;

        uniform mat4 projection2;

        uniform vec2 u_Ratio;
                                                                                                                            //0,0 ZACINA V LEVO DOLE, OPROTI OSTATNIM SHADERUM
        void main()
        {
            gl_Position =  projection2 * vec4(vertex.x, vertex.y, 0.0, 1.0);
            TexCoords = vertex.zw;
        }  

        #shader fragment
        #version 330 core
        in vec2 TexCoords;
        out vec4 color;

        uniform sampler2D text;
        uniform vec3 textColor;

        void main()
        {    
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
            color = vec4(textColor, 1.0) * sampled;
        }  