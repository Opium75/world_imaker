# WORLD IMAKER
##### Pierre THIEL and Yoann KOEPPEL

![world_imaker](./doc/screenshots/world_imaker.png)
=====
### Dependencies :
* OpenGL 4.3
* Eigen 3
### Usage :
#### Building the executuble file :
    - mkdir build
    - cd build/
    - cmake ../
    - make 
#### Launch :
    - bin/wim/world_imaker [world_width] [world_length]
### User interface :

Cubes:
* Add: 		      		                [Insert]
* Delete:	      		                [Suppr]
* Dig:	          		                [ ! ]
* Extrude:		      	                [ : ]
* Change texture:                   	[TAB]
* Move:      		                	[SPACE] + [RETURN]


Lights (random):
* Add ponctual:         	            [ p ]
* Add directional:      	            [ m ]
* Delete punctual:      	            [ 9 ]
* Delete directional:                   [ 0 ]
* Switch on ambiant:		            [ i ]
* Switch of ambiant:		            [ o ]

Camera:
* Rotation:			 	                [MOUSE-BUTTON-MIDDLE] + [MOUVEMENT]
* Zoom-in/out:	                	 	[MOUSE-WHEEL]

Procedural generation:
* Random:                               [ n ]
* RBF:                                  [[Select n times]] + [ * ]
* Add control point:				    [SPACE]
* Discard control point:                [BACKSPACE]
* Discard all :                         [ESCAPE]
* Raise/decrease weight:                [UP-ARROW]/[DOWN-ARROW]


### Screenshots :

![cap1](./doc/screenshots/mine_diamond.png)
==
![cap2](./doc/screenshots/invert_after_lights.png)
