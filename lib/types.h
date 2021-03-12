#ifndef __LIB_TYPES_H
#define __LIB_TYPES_H

typedef int bool;

typedef unsigned long	uintptr_t;
typedef uintptr_t		size_t;

typedef unsigned char		__u8;
typedef char				__s8;
typedef unsigned short		__u16;
typedef short				__s16;
typedef unsigned int		__u32;
typedef int					__s32;
typedef unsigned long long	__u64;
typedef long long			__s64;

/* bsd */
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

/* sysv */
typedef unsigned char	unchar;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;


#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__

typedef		__u8		u_int8_t;
typedef		__s8		int8_t;
typedef		__u16		u_int16_t;
typedef		__s16		int16_t;
typedef		__u32		u_int32_t;
typedef		__s32		int32_t;

#endif /* !(__BIT_TYPES_DEFINED__) */

typedef		__u8		uint8_t;
typedef		__u16		uint16_t;
typedef		__u32		uint32_t;

#if defined(__GNUC__)
typedef		__u64		uint64_t;
typedef		__u64		u_int64_t;
typedef		__s64		int64_t;
#endif

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#endif  /* !__LIB_TYPES_H */
