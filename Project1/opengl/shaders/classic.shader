        #shader vertex
        #version 330 core

        layout(location = 0) in vec2 inPosition; // Input vertex position, changed to vec2

        void main()
        {
            gl_Position = vec4(inPosition, 0.0, 1.0); // Set the output position of the vertex with z component as 0.0
        }

        #shader fragment
        #version 330 core

        out vec4 color;
        uniform vec4 u_Color;

        void main() 
        {
            color = u_Color;
        };