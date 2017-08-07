/*
 *  Misc utilities
 *
 *  (c) Adrian Smith 2012-2014, triode1@btinternet.com
 *  (c) Philippe 2016-2017, philippe_44@outlook.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __UTIL_H
#define __UTIL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "platform.h"
#include "pthread.h"
#include "jansson.h"
#include "ixml.h"

#define NFREE(p) if (p) { free(p); p = NULL; }

typedef struct sQueue {
	struct sQueue *next;
	void *item;
} tQueue;

typedef struct metadata_s {
	char *artist;
	char *album;
	char *title;
	char *genre;
	char *path;
	char *artwork;
	u32_t track;
	u32_t duration;
	u32_t track_hash;
} metadata_t;

void 		QueueInit(tQueue *queue);
void 		QueueInsert(tQueue *queue, void *item);
void 		*QueueExtract(tQueue *queue);
void 		QueueFlush(tQueue *queue);

void 		free_metadata(struct metadata_s *metadata);

int			pthread_cond_reltimedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, u32_t msWait);

int 		GetMediaItem_I(json_t *root, int n, char *item);
double 		GetMediaItem_F(json_t *root, int n, char *item);
const char* GetMediaItem_S(json_t *root, int n, char *item);
const char* GetAppIdItem(json_t *root, char* appId, char *item);
bool 		GetMediaVolume(json_t *root, int n, double *volume, bool *muted);

char 	   	*XMLGetChangeItem(IXML_Document *doc, char *Tag, char *SearchAttr, char *SearchVal, char *RetAttr);
const char 	*XMLGetLocalName(IXML_Document *doc, int Depth);
IXML_Node  	*XMLAddNode(IXML_Document *doc, IXML_Node *parent, char *name, char *fmt, ...);
IXML_Node  	*XMLUpdateNode(IXML_Document *doc, IXML_Node *parent, bool refresh, char *name, char *fmt, ...);
int 	   	XMLAddAttribute(IXML_Document *doc, IXML_Node *parent, char *name, char *fmt, ...);
char 	   	*XMLGetFirstDocumentItem(IXML_Document *doc, const char *item);
int 	   	XMLFindAndParseService(IXML_Document *DescDoc, const char *location,
							const char *serviceTypeBase, char **serviceId,
							char **serviceType, char **eventURL, char **controlURL);

u32_t 		gettime_ms(void);

char*		stristr(char *s1, char *s2);
#if WIN
char* 		strsep(char** stringp, const char* delim);
int 		asprintf(char **strp, const char *fmt, ...);
#endif
char* 		strextract(char *s1, char *beg, char *end);
u32_t 		hash32(char *str);
char*		ltrim(char *s);
char*		rtrim(char *s);
char*		trim(char *s);

bool 		get_interface(struct in_addr *addr);
in_addr_t 	get_localhost(char **name);
void 		get_mac(u8_t mac[]);
void 		winsock_init(void);
void 		winsock_close(void);

typedef struct {
	char *key;
	char *data;
} key_data_t;


bool 		http_parse(int sock, char *method, key_data_t *rkd, char **body, int *len);
char*		http_send(int sock, char *method, key_data_t *rkd);
int 		read_line(int fd, char *line, int maxlen, int timeout);
int 		send_response(int sock, char *response);

char*		kd_lookup(key_data_t *kd, char *key);
bool 		kd_add(key_data_t *kd, char *key, char *value);
char* 		kd_dump(key_data_t *kd);
void 		kd_free(key_data_t *kd);


#if WIN
int asprintf(char **strp, const char *fmt, ...);
#endif

#endif
