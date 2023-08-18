// flea.cpp

#include "flea.h"
#include "main.h"
#include "worldDefs.h"



#define FLEA_GEOM_SCALE		(0.27 * ROW_SPACING)
#define FLEA_INIT_SPEED		0.6

void Flea::updatePos(float elapsedTime)
{
	float distanceToTravel = elapsedTime * FLEA_INIT_SPEED;

	pos.y = pos.y - distanceToTravel;
}




void Flea::generateVAOs() 
{
	// STORING GEOMETRY SEQUENCES

	vec2 bodyGeometry[FLEA_BODY_GEOM] = {
		// body vertices
		
		vec2(1,-1),		//1
		vec2(1, 0.4),	//2
		vec2(0,0),		//3

		vec2(1, 0.4),	//2
		vec2(0,0),		//3
		vec2(0, 1.4),	//4

		vec2(0,0),		//3
		vec2(0, 1.4),	//4
		vec2(-1,0),		//5

		vec2(0, 1.4),	//4
		vec2(-1,0),		//5
		vec2(-1,1.4),	//6

		vec2(-1,0),		//5
		vec2(-2,0),		//7
		vec2(-1,-1),	//8

		vec2(-2,0),		//7
		vec2(-1,-1),	//8
		vec2(-2,-1)		//9

	};

	vec2 legGeometry[FLEA_LEG_GEOM] = {
		// leg vertices
		//leg 1 
		vec2(0.2,0),
		vec2(0.2,-1.6),
		vec2(-0.05,-1.6),

		vec2(0.2,0),
		vec2(-0.05,-1.6),
		vec2(-0.05,0),
		//leg 2 
		vec2(-0.25,0),
		vec2(-0.25,-1.6),
		vec2(-0.5,-1.6),

		vec2(-0.25,0),
		vec2(-0.5,-1.6),
		vec2(-0.5,0),
		//leg 3
		vec2(-0.7,0),
		vec2(-0.7,-1.6),
		vec2(-0.85,-1.6),

		vec2(-0.7,0),
		vec2(-0.85,-1.6),
		vec2(-0.85,0),
	};

	vec2 eyeGeoemtry[FLEA_EYE_GEOM] = {
		// eye vertices
		vec2(-1,0),		//5
		vec2(-1.9,0),	
		vec2(-1,1.3)
	}; 

	// -- Setting Up VAO --

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Define the VBO

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Define the attributes

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0); // two floats for a position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); // three floats for a colour
	glEnableVertexAttribArray(1);

	// Stop setting up this VAO

	glBindVertexArray(0);

	// -- Setting up Geometry --

	db = new DrawBuffers(VAO); 

	seq<vec2> positions;
	seq<vec3> colours;

	GLuint offset;

	offset = positions.size();

	for (int i = 0; i < FLEA_BODY_GEOM; i++) {
		// add vertices for triangle fan
		positions.add(FLEA_GEOM_SCALE * (bodyGeometry[i]));
	}

	for (int i = offset; i < positions.size(); i++)
		colours.add(FLEA_BODY_COLOUR);

	// Add this geometry to the DrawBuffers structure

	db->mode.add(GL_TRIANGLES);
	db->first.add(offset);
	db->count.add(positions.size() - offset);

	// CREATING EYE GEOMETRY
	
	offset = positions.size();

	for (int i = 0; i < FLEA_EYE_GEOM; i++) {
		positions.add(FLEA_GEOM_SCALE * eyeGeoemtry[i]);
	}

	for (int i = offset; i < positions.size(); i++) {
		colours.add(FLEA_EYE_COLOUR);
	}

	db->mode.add(GL_TRIANGLES);
	db->first.add(offset);
	db->count.add(positions.size() - offset);

	// CREATING LEG GEOMETRY

	offset = positions.size();

	for (int i = 0; i < FLEA_LEG_GEOM; i++) {
		positions.add(FLEA_GEOM_SCALE * legGeometry[i]);
	}

	for (int i = offset; i < positions.size(); i++) {
		colours.add(FLEA_LEG_COLOUR);
	}

	db->mode.add(GL_TRIANGLES);
	db->first.add(offset);
	db->count.add(positions.size() - offset);

	// ---------------- copy positions and colours to the VBO ----------------
	int numFloats = positions.size() * (2 + 3);
	float* buffer = new float[numFloats];
	float* p = buffer;

	for (int i = 0; i < positions.size(); i++) {
		*p++ = positions[i].x;
		*p++ = positions[i].y;
		*p++ = colours[i].x;
		*p++ = colours[i].y;
		*p++ = colours[i].z;
	}

	glBufferData(GL_ARRAY_BUFFER, numFloats * sizeof(float), buffer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Flea::draw(mat4& worldToViewTransform) {
	mat4 T = translate(pos.x, pos.y, 0);
	mat4 MVP = worldToViewTransform * T;

	gpuProg->setMat4("MVP", MVP);

	db->draw();
}

DrawBuffers* Flea::db = NULL;