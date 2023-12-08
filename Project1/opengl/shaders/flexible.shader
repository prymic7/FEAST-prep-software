        #shader vertex
        #version 330 core

        layout(location = 0) in vec2 position;
        vec2 jebak;
        uniform mat4 u_OrthographicMatrix;
        uniform vec2 u_WindowSize;
        uniform vec2 u_BaseWindowDiff;
        uniform vec2 u_Ratio;

        void main()
        {
            jebak.x = position.x - u_BaseWindowDiff.x;
            jebak.y = u_WindowSize.y - (position.y - u_BaseWindowDiff.y);
            vec2 normalizedCoords = jebak / vec2(u_WindowSize.x, u_WindowSize.y) * 2.0 - 1.0;
            gl_Position = u_OrthographicMatrix * vec4(normalizedCoords.x * u_Ratio.x, normalizedCoords.y * u_Ratio.y, 0.0, 1.0);
        };

        #shader fragment
        #version 330 core

        out vec4 color;
        uniform vec4 u_Color;

        void main() 
        {
            color = u_Color;
        };







        







        


