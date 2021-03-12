#ifndef __LIB_STDDEF_H
#define __LIB_STDDEF_H

#undef NULL
#define NULL ((void *)0)

enum {
	false	= 0,
	true	= 1
};

#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)

#define offsetofend(TYPE, MEMBER) \
	(offsetof(TYPE, MEMBER)	+ sizeof(((TYPE *)0)->MEMBER))

#endif
