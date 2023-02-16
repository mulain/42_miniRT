
#ifndef DEFINES_H
# define DEFINES_H

// Math
# define EPSILON		0.00001

// Error messages
# define E_ARGCOUNT		"Wrong number of arguments. Please supply scene file.\n"
# define E_FILETYPE		"Invalid input file type. Please supply a .rt file.\n"
# define E_FILENAME		"Invalid input file name.\n"
# define E_OPENFILE		"Could not open input file.\n"

# define E_MALLOC		"Malloc error.\n"

# define E_INVALOBJID	"Invalid object identifier.\n"
# define E_MANDATORY	"Camera (C) and Light (L) must both be declared.\n"

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

# define E_SPHERE1		"Sphere (sp): invalid first argument.\n"
# define E_SPHERE2		"Sphere (sp): invalid second argument.\n"
# define E_SPHERE3		"Sphere (sp): invalid third argument.\n"

# define E_PLANE1		"Plane (pl): invalid first argument.\n"
# define E_PLANE2		"Plane (pl): invalid second argument.\n"
# define E_PLANE3		"Plane (pl): invalid third argument.\n"

# define E_CYLINDER1	"Cylinder (cy): invalid first argument.\n"
# define E_CYLINDER2	"Cylinder (cy): invalid second argument.\n"
# define E_CYLINDER3	"Cylinder (cy): invalid third argument.\n"
# define E_CYLINDER4	"Cylinder (cy): invalid fourth argument.\n"
# define E_CYLINDER5	"Cylinder (cy): invalid fifth argument.\n"

#endif
