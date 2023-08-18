// flea.h

#include "headers.h"
#include "drawbuffer.h"
#include "worldDefs.h"

#define FLEA_BODY_COLOUR	vec3(0.949, 0.819, 0.329) // yellow
#define FLEA_LEG_COLOUR		vec3(0.878, 0.360, 0.360) // red 
#define FLEA_EYE_COLOUR		vec3(0.545, 0.878, 0.403) // green
#define FLEA_BODY_GEOM		20
#define FLEA_LEG_GEOM		18
#define FLEA_EYE_GEOM		3


class Flea {

	//static GLuint VAO; 
	static DrawBuffers *db;

public:

	vec2 pos; // position
	int damage;

	Flea(vec2 _pos) {
		pos = _pos;
		damage = 0;

		if (db == NULL)
			generateVAOs();
	}

	void generateVAOs();
	void draw(mat4& worldToViewTransform);
	void dropMushrooms();
	void updatePos(float elapsedTime);
};