#ifndef __STRINGIFY_H__
#define __STRINGIFY_H__

// Stringify the expanded result of the macro
#define stringify_expanded(x) stringify_directly(x)

// Stringify whatever token between the braces
#define stringify_directly(x) #x

#endif /* __STRINGIFY_H__ */
