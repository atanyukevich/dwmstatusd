#ifndef _smprintf_h_
#define _smprintf_h_

/*
 * #define _BSD_SOURCE
 * I've no idea howto do it without -D_BSD_SOURCE compiler option
 */

/******************************************************************************/
char * smprintf(char *fmt, ...);
int readint (char * filename);
char * readstring (char * filename);
/******************************************************************************/

#endif  /* _smprintf_h_ */
