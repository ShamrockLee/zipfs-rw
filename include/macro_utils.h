#ifndef __ZIPFS__MACRO_UTILS_H_
#define __ZIPFS__MACRO_UTILS_H__

#define concat_tokens(x, y) x##y

#define concat_tokens_expanded(x, y) concat_tokens(x, y)

// Stringify whatever token between the braces
#define stringify(x) #x

// Stringify the expanded result of the macro
#define stringify_expanded(x) stringify(x)

#ifndef container_of(p_container, type_container,    \
		     name_member)(type_container *)( \
	((char *)(p_container)) - offsetof(type_container, name_member))

#endif /* __ZIPFS__MACRO_UTILS_H__ */
