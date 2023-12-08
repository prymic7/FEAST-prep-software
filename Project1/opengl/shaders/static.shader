        #shader vertex
        #version 330 core

        layout(location = 0) in vec2 position;
        uniform vec2 u_WindowSize;

        void main()
        {
            vec2 normalizedCoords = position / vec2(u_WindowSize.x, u_WindowSize.y) * 2.0 - 1.0;
            gl_Position = vec4(normalizedCoords.x, -normalizedCoords.y, 0.0, 1.0);
        };

        #shader fragment
        #version 330 core

        out vec4 color;
        uniform vec4 u_Color;


        void main() 
        {

            color = u_Color;
        };