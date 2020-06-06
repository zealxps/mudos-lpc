#ifndef __FS_ITERATOR_H__
#define __FS_ITERATOR_H__

/*
 * iterator for mapping and array. 
 * by lsw
 */

#include <lpc_incl.h>

typedef struct fs_iterator_s {
	void *ptr;
	void *data;
	int sz;
	union __u {
		int index;
		struct map_pair {
			svalue_t *key;
			svalue_t *val;
		} pair;
	} u;
	int cursor;
} fs_iterator;

#define FS_FOREACH(_iter, _container_p) \
	for ((_container_p)->iter_head(&(_iter), (_container_p)); \
			(_iter).ptr; \
			(_container_p)->iter_next(&(_iter), (_container_p)))

#define FS_ITERATOR_INFO(_iter, _container_p) \
	(_container_p)->iter_info(&(_iter), (_container_p))

#define FS_ITERATOR_ERASE(_iter, _container_p) \
	((_container_p)->iter_erase(&(_iter), (_container_p))

#define FS_IS_ITERATOR_NULL(_iter) \
	((_iter).ptr == NULL)

#define FS_SET_ITERATOR_NULL(_iter_p) do { \
	 (_iter_p)->ptr = NULL; \
	 (_iter_p)->data = NULL; \
	} while (0)

#define FS_ITERATOR_KEY(_iter) \
	 (_iter).u.pair.key;

#define FS_ITERATOR_VAL(_iter) \
	 (_iter).u.pair.val;

#define FS_ITERATOR_INITIALIZER \
	 {NULL, NULL, -1, {-1}, -1}

#endif
