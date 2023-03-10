
#ifndef DEFINES_H
# define DEFINES_H

// Settings
# define IMG_WIDTH		1920
# define IMG_HEIGHT		1080
# define EPSILON		0.000001
# define THREADCOUNT	12
# define RAYDEPTH		2

// Error messages
# define E_ARGCOUNT		"Wrong number of arguments. Please supply scene file.\n"
# define E_FILETYPE		"Invalid input file type. Please supply a .rt file.\n"
# define E_FILENAME		"Invalid input file name.\n"
# define E_OPENFILE		"Could not open input file.\n"
# define E_THREADCREATE	"Could not create thread.\n"
# define E_THREADJOIN	"Could not join thread.\n"

# define E_MALLOC		"Malloc error.\n"

# define E_INVALOBJID	"Invalid object identifier.\n"
# define E_MANDATORY	"Camera (C) and Light (L) must both be defined.\n"

# define E_AMBLIGHTDEF	"Ambient light (A): may only be defined once.\n"
# define E_AMBLIGHT1	"Ambient light (A): invalid first argument.\n"
# define E_AMBLIGHT2	"Ambient light (A): invalid second argument.\n"

# define E_CAMERADEF	"Camera (C): may only be defined once.\n"
# define E_CAMERA1		"Camera (C): invalid first argument.\n"
# define E_CAMERA2		"Camera (C): invalid second argument.\n"
# define E_CAMERA3		"Camera (C): invalid third argument.\n"

# define E_LIGHTDEF		"Light (L): may only be defined once.\n"
# define E_LIGHT1		"Light (L): invalid first argument.\n"
# define E_LIGHT2		"Light (L): invalid second argument.\n"
# define E_LIGHT3		"Light (L): invalid third argument.\n"

# define E_PLANE1		"Plane (pl): invalid first argument.\n"
# define E_PLANE2		"Plane (pl): invalid second argument.\n"
# define E_PLANE3		"Plane (pl): invalid third argument.\n"

# define E_DISC1		"Disc (di): invalid first argument.\n"
# define E_DISC2		"Disc (di): invalid second argument.\n"
# define E_DISC3		"Disc (di): invalid third argument.\n"
# define E_DISC4		"Disc (di): invalid fourth argument.\n"

# define E_TRIANGLE1	"Triangle (tr): invalid first argument.\n"
# define E_TRIANGLE2	"Triangle (tr): invalid second argument.\n"
# define E_TRIANGLE3	"Triangle (tr): invalid third argument.\n"
# define E_TRIANGLE4	"Triangle (tr): invalid fourth argument.\n"
# define E_TRI_VECTOR	"Triangle (tr): Given points do not define a plane.\n"

# define E_SPHERE1		"Sphere (sp): invalid first argument.\n"
# define E_SPHERE2		"Sphere (sp): invalid second argument.\n"
# define E_SPHERE3		"Sphere (sp): invalid third argument.\n"

# define E_CYLINDER1	"Cylinder (cy): invalid first argument.\n"
# define E_CYLINDER2	"Cylinder (cy): invalid second argument.\n"
# define E_CYLINDER3	"Cylinder (cy): invalid third argument.\n"
# define E_CYLINDER4	"Cylinder (cy): invalid fourth argument.\n"
# define E_CYLINDER5	"Cylinder (cy): invalid fifth argument.\n"

# define E_CONE1		"Cone (co): invalid first argument.\n"
# define E_CONE2		"Cone (co): invalid second argument.\n"
# define E_CONE3		"Cone (co): invalid third argument.\n"
# define E_CONE4		"Cone (co): invalid fourth argument.\n"
# define E_CONE5		"Cone (co): invalid fifth argument.\n"

#endif
