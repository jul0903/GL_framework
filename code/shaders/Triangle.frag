#version 330
		 
out vec4 color;
uniform vec4 aCol;
in vec4 position;

void main() {
	color = aCol;
}