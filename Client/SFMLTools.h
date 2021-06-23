/**
* @file SFMLTools.h contiene deeclaración de constantes para la interfaz gráfica.
*/
#include <cstdlib>

// misceláneos

#define absolute_value( x ) ( ((x) < 0) ? -(x) : (x) )

// Controles del ratón

#define MousePressed( byte ) ((byte) & 1UL << 0)? 1 : 0
#define MouseReleased(byte) ((byte) & 1UL << 1)? 1 : 0

// Controles de botón

#define ButtonEnable(byte) ((byte) & 1UL << 0)? 1 : 0
#define ButtonPressed(byte) ((byte) & 1UL << 1)? 1 : 0
#define ButtonReleased(byte) ((byte) & 1UL << 2)? 1 : 0

// colores
