/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
//#include <string.h>
//#include "dm9051_lw.h"
#include "dm9051_lw_conf.h"

//#include "dm9051_debug_lw.h" //"..\..\..\lwip_dm9051_driver2303v3\debug.h" //..#include "FreeRTOS.h" (#include "debug.h")
#include "developer_conf.h" //#include "main.h" //#include "developer_conf.h"

#include "lwip/apps/httpd_opts.h"
#include "lwip/def.h"
#include "lwip/apps/fs.h"

#include HTTPD_FSDATA_FILE

//[file__contributor_html]

//int get_contr_len(void) {
//	return sizeof(data__contributor_html) - 20;
//}
//const unsigned char *restrict get_cont_data(void) {
//	return (data__contributor_html + 20);
//}

/*-----------------------------------------------------------------------------------*/

#if LWIP_HTTPD_CUSTOM_FILES
int fs_open_custom(struct fs_file *file, const char *name);
void fs_close_custom(struct fs_file *file);
#if LWIP_HTTPD_FS_ASYNC_READ
u8_t fs_canread_custom(struct fs_file *file);
u8_t fs_wait_read_custom(struct fs_file *file, fs_wait_cb callback_fn, void *callback_arg);
int fs_read_async_custom(struct fs_file *file, char *buffer, int count, fs_wait_cb callback_fn, void *callback_arg);
#else /* LWIP_HTTPD_FS_ASYNC_READ */
int fs_read_custom(struct fs_file *file, char *buffer, int count);
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
#endif /* LWIP_HTTPD_CUSTOM_FILES */


#if HTTPD_JJ_DYNAMIC_FSDATA
/*-----------------------------------------------------------------------------------*/
#define IMPL_FILENAME "/implementation.html" //(20 chars)
#define IMPL_FILENAME_STRUCT_LEN 22

// [All are my dummy data], no need counting but dummy data instead, we implement not more than raw file data (1214 bytes) field.
unsigned char data__implement_html[] = {
/* /implementation.html (20 chars), /contributor.html (18 chars), occupied 22 (IMPL_FILENAME_STRUCT_LEN) bytes */
0x2f,0x63,0x6f,0x6e,0x74,0x72,0x69,0x62,0x75,0x74,0x6f,0x72,0x2e,0x68,0x74,0x6d,
0x6c,0x00,0x00,0x00,0x00,0x00,

/* HTTP header */
/* "HTTP/1.0 200 OK
" (17 bytes) */
0x48,0x54,0x54,0x50,0x2f,0x31,0x2e,0x30,0x20,0x32,0x30,0x30,0x20,0x4f,0x4b,0x0d,
0x0a,
/* "Server: lwIP/2.1.2 (http://savannah.nongnu.org/projects/lwip)
" (63 bytes) */
0x53,0x65,0x72,0x76,0x65,0x72,0x3a,0x20,0x6c,0x77,0x49,0x50,0x2f,0x32,0x2e,0x31,
0x2e,0x32,0x20,0x28,0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x73,0x61,0x76,0x61,0x6e,
0x6e,0x61,0x68,0x2e,0x6e,0x6f,0x6e,0x67,0x6e,0x75,0x2e,0x6f,0x72,0x67,0x2f,0x70,
0x72,0x6f,0x6a,0x65,0x63,0x74,0x73,0x2f,0x6c,0x77,0x69,0x70,0x29,0x0d,0x0a,
/* "Content-Length: 1214
" (18+ bytes) */
0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x4c,0x65,0x6e,0x67,0x74,0x68,0x3a,0x20,
0x31,0x32,0x31,0x34,0x0d,0x0a,
/* "Content-Type: text/html

" (27 bytes) */
0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x54,0x79,0x70,0x65,0x3a,0x20,0x74,0x65,
0x78,0x74,0x2f,0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,0x0a,
/* raw file data (1214 bytes) */
#if 1
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
#endif
#if 0
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
#endif
#if 1
0x3c,0x68,0x74,0x6d,0x6c,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x70,0x61,0x64,
0x64,0x69,0x6e,0x67,0x3a,0x30,0x70,0x78,0x3b,0x22,0x3e,0x0a,0x3c,0x68,0x65,0x61,
0x64,0x3e,0x3c,0x6d,0x65,0x74,0x61,0x20,0x68,0x74,0x74,0x70,0x2d,0x65,0x71,0x75,
0x69,0x76,0x3d,0x22,0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x54,0x79,0x70,0x65,
0x22,0x20,0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x3d,0x22,0x74,0x65,0x78,0x74,0x2f,
0x68,0x74,0x6d,0x6c,0x3b,0x20,0x63,0x68,0x61,0x72,0x73,0x65,0x74,0x3d,0x55,0x54,
0x46,0x2d,0x38,0x22,0x3e,0x0a,0x3c,0x74,0x69,0x74,0x6c,0x65,0x3e,0x43,0x6f,0x6e,
0x74,0x72,0x69,0x62,0x75,0x74,0x6f,0x72,0x20,0x43,0x72,0x65,0x64,0x69,0x74,0x73,
#endif
#if 1
0x3c,0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,0x0a,0x09,0x3c,0x6c,0x69,0x6e,0x6b,0x20,
0x72,0x65,0x6c,0x3d,0x22,0x73,0x74,0x79,0x6c,0x65,0x73,0x68,0x65,0x65,0x74,0x22,
0x20,0x74,0x79,0x70,0x65,0x3d,0x22,0x74,0x65,0x78,0x74,0x2f,0x63,0x73,0x73,0x22,
0x20,0x68,0x72,0x65,0x66,0x3d,0x22,0x2e,0x2f,0x73,0x74,0x79,0x6c,0x65,0x32,0x2e,
0x63,0x73,0x73,0x22,0x3e,0x0a,0x09,0x3c,0x21,0x2d,0x2d,0x3c,0x6d,0x65,0x74,0x61,
0x20,0x68,0x74,0x74,0x70,0x2d,0x65,0x71,0x75,0x69,0x76,0x3d,0x22,0x72,0x65,0x66,
0x72,0x65,0x73,0x68,0x22,0x20,0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x3d,0x22,0x31,
0x30,0x22,0x3e,0x2d,0x2d,0x3e,0x0a,0x3c,0x73,0x74,0x79,0x6c,0x65,0x3e,0x0a,0x09,
0x68,0x74,0x6d,0x6c,0x20,0x7b,0x20,0x6f,0x76,0x65,0x72,0x66,0x6c,0x6f,0x77,0x2d,
0x78,0x3a,0x68,0x69,0x64,0x64,0x65,0x6e,0x3b,0x20,0x7d,0x0a,0x3c,0x2f,0x73,0x74,
0x79,0x6c,0x65,0x3e,0x0a,0x3c,0x2f,0x68,0x65,0x61,0x64,0x3e,0x0a,0x3c,0x62,0x6f,
0x64,0x79,0x3e,0x0a,0x0a,0x3c,0x66,0x6f,0x72,0x6d,0x20,0x6d,0x65,0x74,0x68,0x6f,
0x64,0x3d,0x22,0x67,0x65,0x74,0x22,0x3e,0x0a,0x3c,0x64,0x69,0x76,0x20,0x63,0x6c,
0x61,0x73,0x73,0x3d,0x22,0x74,0x6f,0x70,0x5f,0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,
0x22,0x20,0x73,0x74,0x79,0x6c,0x65,0x3d,0x22,0x77,0x69,0x64,0x74,0x68,0xef,0xbc,
0x9a,0x61,0x75,0x74,0x6f,0x3b,0x20,0x68,0x65,0x69,0x67,0x68,0x74,0x3a,0x61,0x75,
0x74,0x6f,0x22,0x3e,0x0a,0x3c,0x74,0x61,0x62,0x6c,0x65,0x20,0x77,0x69,0x64,0x74,
0x68,0x3d,0x22,0x31,0x30,0x30,0x25,0x22,0x20,0x62,0x6f,0x72,0x64,0x65,0x72,0x3d,
0x22,0x30,0x22,0x20,0x62,0x6f,0x72,0x64,0x65,0x72,0x63,0x6f,0x6c,0x6f,0x72,0x3d,
0x22,0x23,0x43,0x43,0x43,0x43,0x43,0x43,0x22,0x3e,0x0a,0x3c,0x74,0x62,0x6f,0x64,
0x79,0x3e,0x0a,0x3c,0x74,0x72,0x3e,0x0a,0x3c,0x74,0x64,0x20,0x68,0x65,0x69,0x67,
0x68,0x74,0x3d,0x22,0x31,0x38,0x22,0x20,0x63,0x6c,0x61,0x73,0x73,0x3d,0x22,0x67,
0x72,0x22,0x3e,0x3c,0x64,0x69,0x76,0x20,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x72,
0x69,0x67,0x68,0x74,0x22,0x3e,0x0a,0x3c,0x66,0x6f,0x6e,0x74,0x20,0x73,0x69,0x7a,
0x65,0x3d,0x22,0x33,0x22,0x20,0x66,0x61,0x63,0x65,0x3d,0x22,0x61,0x72,0x69,0x61,
0x6c,0x22,0x20,0x63,0x6f,0x6c,0x6f,0x72,0x3d,0x62,0x6c,0x75,0x65,0x3e,0x0a,0x4d,
0x6f,0x64,0x75,0x6c,0x65,0x20,0x4e,0x61,0x6d,0x65,0xef,0xbc,0x9a,0x0a,0x3c,0x2f,
0x66,0x6f,0x6e,0x74,0x3e,0x0a,0x3c,0x2f,0x64,0x69,0x76,0x3e,0x3c,0x2f,0x74,0x64,
0x3e,0x0a,0x3c,0x74,0x64,0x20,0x68,0x65,0x69,0x67,0x68,0x74,0x3d,0x22,0x31,0x38,
0x22,0x20,0x63,0x6c,0x61,0x73,0x73,0x3d,0x22,0x67,0x72,0x22,0x3e,0x3c,0x64,0x69,
0x76,0x20,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x6c,0x65,0x66,0x74,0x22,0x3e,0x0a,
0x3c,0x66,0x6f,0x6e,0x74,0x20,0x73,0x69,0x7a,0x65,0x3d,0x22,0x35,0x22,0x20,0x66,
0x61,0x63,0x65,0x3d,0x22,0x61,0x72,0x69,0x61,0x6c,0x22,0x20,0x63,0x6f,0x6c,0x6f,
0x72,0x3d,0x67,0x72,0x65,0x65,0x6e,0x3e,0x0a,0x3c,0x62,0x3e,0x44,0x4d,0x39,0x30,
0x35,0x31,0x20,0x45,0x74,0x68,0x65,0x72,0x6e,0x65,0x74,0x3c,0x2f,0x62,0x3e,0x0a,
0x3c,0x2f,0x66,0x6f,0x6e,0x74,0x3e,0x0a,0x3c,0x2f,0x64,0x69,0x76,0x3e,0x3c,0x2f,
0x74,0x64,0x3e,0x0a,0x3c,0x2f,0x74,0x72,0x3e,0x0a,0x3c,0x2f,0x74,0x62,0x6f,0x64,
0x79,0x3e,0x0a,0x3c,0x2f,0x74,0x61,0x62,0x6c,0x65,0x3e,0x0a,0x3c,0x2f,0x64,0x69,
0x76,0x3e,0x0a,0x3c,0x2f,0x66,0x6f,0x72,0x6d,0x3e,0x0a,0x0a,0x3c,0x21,0x2d,0x2d,
0x3c,0x64,0x69,0x76,0x20,0x69,0x64,0x3d,0x22,0x73,0x69,0x64,0x65,0x62,0x61,0x72,
0x22,0x3e,0x0a,0x3c,0x64,0x69,0x76,0x20,0x69,0x64,0x3d,0x22,0x68,0x65,0x6c,0x70,
0x22,0x3e,0x0a,0x3c,0x64,0x69,0x76,0x20,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x6c,
0x65,0x66,0x74,0x22,0x3e,0x0a,0x3c,0x66,0x6f,0x6e,0x74,0x20,0x73,0x69,0x7a,0x65,
0x3d,0x22,0x33,0x22,0x20,0x66,0x61,0x63,0x65,0x3d,0x22,0x61,0x72,0x69,0x61,0x6c,
0x22,0x3e,0x0a,0x3c,0x75,0x6c,0x3e,0x0a,0x53,0x6f,0x66,0x74,0x77,0x61,0x72,0x65,
0x20,0x73,0x75,0x70,0x70,0x6f,0x72,0x74,0x20,0x74,0x65,0x61,0x6d,0x0a,0x3c,0x2f,
0x75,0x6c,0x3e,0x0a,0x3c,0x2f,0x66,0x6f,0x6e,0x74,0x3e,0x0a,0x3c,0x2f,0x64,0x69,
0x76,0x3e,0x0a,0x3c,0x2f,0x64,0x69,0x76,0x3e,0x0a,0x3c,0x2f,0x64,0x69,0x76,0x3e,
0x2d,0x2d,0x3e,0x0a,0x0a,0x3c,0x21,0x2d,0x2d,0x3c,0x64,0x69,0x76,0x20,0x69,0x64,
0x3d,0x22,0x73,0x69,0x64,0x65,0x62,0x61,0x72,0x22,0x3e,0x2d,0x2d,0x3e,0x0a,0x3c,
0x21,0x2d,0x2d,0x3c,0x64,0x69,0x76,0x20,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x6c,
0x65,0x66,0x74,0x22,0x3e,0x2d,0x2d,0x3e,0x0a,0x3c,0x74,0x61,0x62,0x6c,0x65,0x20,
#endif
0x77,0x69,0x64,0x74,0x68,0x3d,0x22,0x31,0x30,0x30,0x25,0x22,0x20,0x62,0x6f,0x72,
0x64,0x65,0x72,0x3d,0x22,0x30,0x22,0x3e,0x0a,0x3c,0x74,0x62,0x6f,0x64,0x79,0x3e,
0x0a,0x3c,0x74,0x72,0x3e,0x0a,0x3c,0x74,0x64,0x20,0x68,0x65,0x69,0x67,0x68,0x74,
0x3d,0x22,0x31,0x38,0x22,0x20,0x77,0x69,0x64,0x74,0x68,0x3d,0x20,0x38,0x3e,0x3c,
0x2f,0x74,0x64,0x3e,0x0a,0x3c,0x74,0x64,0x20,0x68,0x65,0x69,0x67,0x68,0x74,0x3d,
0x22,0x31,0x38,0x22,0x20,0x63,0x6c,0x61,0x73,0x73,0x3d,0x22,0x67,0x72,0x22,0x3e,
0x3c,0x64,0x69,0x76,0x20,0x61,0x6c,0x69,0x67,0x6e,0x3d,0x22,0x6c,0x65,0x66,0x74,
0x22,0x3e,0x0a,0x3c,0x66,0x6f,0x6e,0x74,0x20,0x73,0x69,0x7a,0x65,0x3d,0x22,0x33,
0x22,0x20,0x66,0x61,0x63,0x65,0x3d,0x22,0x61,0x72,0x69,0x61,0x6c,0x22,0x3e,0x0a,
0x53,0x6f,0x66,0x74,0x77,0x61,0x72,0x65,0x20,0x73,0x75,0x70,0x70,0x6f,0x72,0x74,
0x20,0x74,0x65,0x61,0x6d,0x0a,0x3c,0x2f,0x66,0x6f,0x6e,0x74,0x3e,0x0a,0x3c,0x2f,
0x64,0x69,0x76,0x3e,0x3c,0x2f,0x74,0x64,0x3e,0x0a,0x3c,0x2f,0x74,0x72,0x3e,0x0a,
0x3c,0x2f,0x74,0x62,0x6f,0x64,0x79,0x3e,0x0a,0x3c,0x2f,0x74,0x61,0x62,0x6c,0x65,
0x3e,0x0a,0x3c,0x21,0x2d,0x2d,0x3c,0x2f,0x64,0x69,0x76,0x3e,0x2d,0x2d,0x3e,0x0a,
0x3c,0x21,0x2d,0x2d,0x3c,0x2f,0x64,0x69,0x76,0x3e,0x2d,0x2d,0x3e,0x0a,0x0a,0x3c,
0x2f,0x62,0x6f,0x64,0x79,0x3e,0x3c,0x2f,0x68,0x74,0x6d,0x6c,0x3e,0x0a,};

typedef struct impldata_skel_st {
	char filename[IMPL_FILENAME_STRUCT_LEN]; // only dedicated for IMPL_FILENAME
	unsigned char *raw_page_data;
} impldata_skel_t;

const unsigned char http_header[] = {
 0x48,0x54,0x54,0x50,0x2f,0x31,0x2e,0x30,0x20,0x32,0x30,0x30,0x20,0x4f,0x4b,0x0d,
 0x0a,};
const unsigned char server_lwip[] = {
 0x53,0x65,0x72,0x76,0x65,0x72,0x3a,0x20,0x6c,0x77,0x49,0x50,0x2f,0x32,0x2e,0x31,
 0x2e,0x32,0x20,0x28,0x68,0x74,0x74,0x70,0x3a,0x2f,0x2f,0x73,0x61,0x76,0x61,0x6e,
 0x6e,0x61,0x68,0x2e,0x6e,0x6f,0x6e,0x67,0x6e,0x75,0x2e,0x6f,0x72,0x67,0x2f,0x70,
 0x72,0x6f,0x6a,0x65,0x63,0x74,0x73,0x2f,0x6c,0x77,0x69,0x70,0x29,0x0d,0x0a,};

/* "Content-Length: 1214
" (18+ bytes) */
const unsigned char content_len[] = {
/* "Content-Length: " */
/* "1214<cr><lf>" */
 0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x4c,0x65,0x6e,0x67,0x74,0x68,0x3a,0x20,
 0x31,0x32,0x31,0x34,0x0d,0x0a,};

const unsigned char content_type[] = {	
 0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,0x54,0x79,0x70,0x65,0x3a,0x20,0x74,0x65,
 0x78,0x74,0x2f,0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,0x0a,};

#define ADDR_LENGTH									(4)
//extern uint8_t cfg_local_ipe[2][ADDR_LENGTH];
 
char sprntbuf[100];
int sprnt_max = 0;

/*
<!--<div id=\"sidebar\">\
<div id=\"help\">\
<div align=\"left\">\
<font size=\"3\" face=\"arial\">\
<ul>\
Software support team\
</ul>\
</font>\
</div>\
</div>\
</div>-->\
\
<!--<div id=\"sidebar\">-->\
<!--<div align=\"left\">-->\
<!--</div>-->\
<!--</div>-->\
	<!--<meta http-equiv=\"refresh\" content=\"10\">-->\
*/

const char *ssstbl[] = {
	"<html style=\"padding:0px;\">",
	"<head>",
	"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">",
	"<title>",
	"Implementation Data",
	"</title>",
	"<link rel=\"stylesheet\" type=\"text/css\" href=\"./style2.css\">",
	"<style>",
	"html { overflow-x:hidden; }",
	"</style>",
	"</head>",
	"<body>",
	"<form method=\"get\">",
	"<div class=\"top_content\" style=\"width:auto; height:auto\">",
	"<table width=\"100%\" border=\"0\" bordercolor=\"#CCCCCC\">",
	"<tbody>",
	"<tr>",
	"<td height=\"18\" class=\"gr\">",
	"<div align=\"right\">",
	"<font size=\"3\" face=\"arial\" color=blue>",
	"Module Name:",
	"</font>",
	"</div>",
	"</td>",
	"<td height=\"18\" class=\"gr\">",
	"<div align=\"left\">",
	"<font size=\"5\" face=\"arial\" color=green>",
	"<b>DM9051 Ethernet Teddy</b>",
	"</font>",
	"</div>",
	"</td>",
	"</tr>",
	"</tbody>",
	"</table>",
	"</div>",
	"</form>",
	"<table width=\"100%\" border=\"0\">",
	"<tbody>",
	"<tr>",
	"<td height=\"18\" width= 8>",
	"</td>",
	"<td height=\"18\" class=\"gr\"><div align=\"left\">",
//	"<font size=\"3\" face=\"arial\">",
	"<font size=\"2\" face=\"arial\" color=salmon>",
	NULL,
};
const char *sssip = "IP %d.%d.%d.%d<br>\r\n";
const char *sssmac = "MAC %02x:%02x:%02x:%02x:%02x:%02x<br>\r\n";
const char *eeetbl[] = {
	"</font>",
	"</div>",
	"</td>",
	"</tr>",
	"</tbody>",
	"</table>",
	"</body>",
	"</html>",
	NULL,
};

#if 0
struct fsdata_file file__implement_html = { 
  //.next = FS_ROOT,
  //.flags = FS_FILE_FLAGS_HEADER_INCLUDED | FS_FILE_FLAGS_HEADER_PERSISTENT,
};
struct fsdata_file *setup_dynamic_pages(void) {
	//return FS_ROOT;
}
#endif

int set_c_length(int lc, char *p, int content_length)
{
	int nget = content_length % 10; //nget= 4, [lc= 0, content_length 1314]
	                                 //nget= 1, [lc= 0, content_length 131]
									  //nget= 3, [lc= 0, content_length 13] 
									   //nget= 1, [lc= 0, content_length 1] 
									   //lc= 0, <--- .[0] = 1; (return (lc+1))
									  //lc= 1, <--- .[1] = 3; (return (lc+1))
									 //lc= 2, <--- .[2] = 1; (return (lc+1))
									//lc= 2, <--- .[3] = 4; (return (lc+1)) ;;return 4;
	if (nget == content_length) {
		*(p + lc) = 0x30 + nget;
		return lc + 1;
	}
	lc = set_c_length(lc, p, content_length / 10);
	*(p + lc) = 0x30 + nget;
	return lc + 1;
}

static int set_content_length(char *cl_data, int content_length)
{
	int tmp_content_length = 0, lc = 0;
	char *p;
	//printf("set_content_length().s %02x %02x %02x %02x %02x %02x\r\n", 
		//*(cl_data+16), *(cl_data+17), *(cl_data+18), *(cl_data+19), *(cl_data+20), *(cl_data+21));
	p = cl_data + 16;
	if (*p >= 0x30 && *p <= 0x39) {
		tmp_content_length += *p - 0x30;
		p++;
		while(*p >= 0x30 && *p <= 0x39) {
			tmp_content_length = 10 * tmp_content_length;
			tmp_content_length += *p - 0x30;
			p++;
		}
	}
	//printf("tmp content_length() which was html len %d\r\n", tmp_content_length);
	lc = set_c_length(lc, cl_data+16, content_length); //recursive-skill usage
	*(cl_data+16+lc) = 0x0d;
	*(cl_data+16+lc+1) = 0x0a;
	//printf("set_content_length().e %02x %02x %02x %02x %02x %02x\r\n", 
		//*(cl_data+16), *(cl_data+17), *(cl_data+18), *(cl_data+19), *(cl_data+20), *(cl_data+21));
	//printf("set_content_length() which is html len %d\r\n", content_length);
	return 16 + lc + 2;
}

static int calc_impl_struct_pages(char *data) {
	int ns, tns, n_raw = 0, content_length = 0;
	//impldata_skel_t *p = (impldata_skel_t *) data__implement_html; //struct fs_file *file = ;
	char *data_t = data, *data_s;
	int i; //const char *p;
	const uint8_t *dev;
	const uint8_t *mac;

//printf("calc, data__implement_html[] %x (size %d)\r\n", data__implement_html, sizeof(data__implement_html));	
	
//printf("calc, len %d filename block.\r\n", IMPL_FILENAME_STRUCT_LEN);
	n_raw += IMPL_FILENAME_STRUCT_LEN;
	data_t = data + n_raw;
	
//printf("calc, len %d HTTP_header.\r\n", sizeof(http_header));
	n_raw += sizeof(http_header);
	data_t = data + n_raw;
	
//printf("calc, len %d Server: lwip/2.1.2.\r\n", sizeof(server_lwip));
	n_raw += sizeof(server_lwip);
	data_t = data + n_raw;
	data_s = data_t;
	
//printf("calc, len %d content-length block.\r\n", 22);
//printf("calc, Display dump len %d (bytes)\r\n", n_raw + 22);
//printf("calc, Display dump %x + %d, %x + %d\r\n", data, n_raw, data_t, 22);
//.dm9051_txlog_monitor_tx_all(2, (const uint8_t *)data__implement_html, n_raw + 22);

//printf("---------- calc for content-length block %x + %d\r\n", data_s, 22);
//.dm9051_txlog_monitor_tx_all(2, (const uint8_t *)data_s, 22);
//	ns = set_content_length(data + n_raw, content_length); //we have a recursive-skill usage
//	n_raw += ns; //'sizeof(content_len)'
	data_t = data + n_raw;
	
	n_raw += sizeof(content_type);
	data_t = data + n_raw;
	
#if 1
	i = tns = 0; //p = ssstbl[0];
	while (ssstbl[i]) {
		ns = sprintf(sprntbuf, "%s\r\n", ssstbl[i]);
		if (ns > sprnt_max) sprnt_max = ns;
		tns += ns;
		i++; //p++;
	}
	content_length += tns;
	n_raw += tns;
//printf("---------- calc %3d (content_length %d) sprnt_max %d\r\n", tns, content_length, sprnt_max);
	ns = sprintf(sprntbuf, "%s<br>\r\n", get_application_banner());
	if (ns > sprnt_max) sprnt_max = ns;
	content_length += ns;
	n_raw += ns;
//printf("---------- calc %3d (content_length %d) sprnt_max %d\r\n", ns, content_length, sprnt_max);
	
	dev = lwip_get_ip_addresse();
	ns = sprintf(sprntbuf, sssip, dev[0], dev[1], dev[2], dev[3]);
	if (ns > sprnt_max) sprnt_max = ns;
	content_length += ns;
	n_raw += ns;
//printf("---------- calc %3d (content_length %d) sprnt_max %d\r\n", ns, content_length, sprnt_max);
	
	mac = lwip_get_mac_addresse1();
	ns = sprintf(sprntbuf, sssmac, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	if (ns > sprnt_max) sprnt_max = ns;
	content_length += ns;
	n_raw += ns;
//printf("---------- calc %3d (content_length %d) sprnt_max %d\r\n", ns, content_length, sprnt_max);
	
	i = tns = 0;
	while (eeetbl[i]) {
		ns = sprintf(sprntbuf, "%s\r\n", eeetbl[i]);
		if (ns > sprnt_max) sprnt_max = ns;
		tns += ns;
		i++;
	}
	content_length += tns;
	n_raw += tns;
//printf("---------- calc %3d (content_length %d) sprnt_max %d\r\n", ns, content_length, sprnt_max);
//printf("---------- Sanity CHECK: sprnt_max %d < 100, result: %s\r\n", sprnt_max, sprnt_max < 100 ? "" : "");
#endif
	data_t = data + n_raw;
	
//printf("---------- check raw_page_data s %x (content_length %d)\r\n", data_s, content_length);
//.function_monitor_tx_all((const uint8_t *)data_s, 32);
	ns = set_content_length(data_s, content_length); //we have a recursive-skill usage
	n_raw += ns; //'sizeof(content_len)'
//printf("---------- check raw_page_data e %x (content_length %d)\r\n", data_s, content_length);
//.function_monitor_tx_all((const uint8_t *)data_s, 32);
	
	//printf("calc_impl_struct_pages: content len %d, total struct len %d\r\n", content_length, n_raw);
	//printf("\r\n");
	return content_length;
}

static int setup_impl_pages(char *data, int content_length) {  // make, data__implement_html[]
	int n_raw = 0, ns, re_content_length;
	int i; //const char *p;
	const uint8_t *dev;
	const uint8_t *mac;
#if 1
#if 1
	memcpy(data + n_raw, http_header, sizeof(http_header));
	n_raw += sizeof(http_header);
	memcpy(data + n_raw, server_lwip, sizeof(server_lwip));
	n_raw += sizeof(server_lwip);

	//memcpy(data + n_raw, content_len, sizeof(content_len)); //more or less is both ok.
	ns = set_content_length(data + n_raw, content_length); //we have a recursive-skill usage
	memcpy(data + n_raw, content_len, 16); //'ns' is the exact bytes, remain 16 bytes copied here, ok.
	n_raw += ns; //'ns' can be different to 'sizeof(content_len)'

	memcpy(data + n_raw, content_type, sizeof(content_type));
	n_raw += sizeof(content_type);
#endif
	
	re_content_length = 0;
	
	#if 1
	  i = 0; //p = ssstbl[0];
	  while (ssstbl[i]) {
		ns = sprintf(data + n_raw, "%s\r\n", ssstbl[i]);
		re_content_length += ns;
		n_raw += ns;
		i++; //p++;
	  }
	  ns = sprintf(data + n_raw, "%s<br>\r\n", get_application_banner());
	  re_content_length += ns;
	  n_raw += ns;
	  
	  dev = lwip_get_ip_addresse();
	  ns = sprintf(data + n_raw, sssip, dev[0], dev[1], dev[2], dev[3]);
	  re_content_length += ns;
	  n_raw += ns;
	  
	  mac = lwip_get_mac_addresse1();
	  ns = sprintf(data + n_raw, sssmac, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	  re_content_length += ns;
	  n_raw += ns;
	  
	  i = 0;
	  while (eeetbl[i]) {
		ns = sprintf(data + n_raw, "%s\r\n", eeetbl[i]);
		re_content_length += ns;
		n_raw += ns;
		i++;
	  }
	#endif
	  
	  //printf("[html len checking]: %d vs. %d (%s)\r\n", re_content_length, content_length, (re_content_length == content_length) ? "OK-equal" : "Warn-diff"); //if ()
	
	  //printf("setup_impl_pages() html len %d, with instruction-head %d, total struct len %d\r\n", content_length, n_raw, n_raw + IMPL_FILENAME_STRUCT_LEN); //rawpage-len rawpage for lwip.
#endif 
	  //printf("setup_impl_pages() used len %d, useful zoom len %d, total struct len %d\r\n", n_raw + IMPL_FILENAME_STRUCT_LEN,
	  //		sizeof(data__implement_html), sizeof(data__implement_html));
	return n_raw;
}

int setup_dynamic_pages1(struct fs_file *file, const char *name) {
	impldata_skel_t *p = (impldata_skel_t *) data__implement_html;
	int content_length, len;
	
	if (!strcmp(name, (const char *)IMPL_FILENAME)) {
	
//printf("\r\n");
//printf("calc_\r\n");
//.printf("---------- check %x %x %x\r\n", p, p->filename, data__implement_html);
		content_length = calc_impl_struct_pages((char *)p->filename);
		
		file->data = p->filename + sizeof(p->filename);
//printf("setup_\r\n");
//.printf("---------- check %x %x %x, html_data %x\r\n", p, p->filename, data__implement_html, file->data);
//printf("---------- data__implement_html %x, html_data %x\r\n", data__implement_html, file->data);
		len = setup_impl_pages((char *)file->data, content_length);
		//file->data = (const char *) p->filename + sizeof(p->filename);
		
		file->len = len;
		file->index = len;
		file->pextension = NULL;
		file->flags = FS_FILE_FLAGS_HEADER_INCLUDED | FS_FILE_FLAGS_HEADER_PERSISTENT; //f->flags;
		return content_length;
	}
	return 0;
}

void debug_dynamic_page(void) {
  do {
	#define IMPL_FILENAME "/implementation.html" //(20 chars)
	int setup_dynamic_pages1(struct fs_file *file, const char *name);
	struct fs_file thefs;
	int html_len;
	
	html_len = setup_dynamic_pages1(&thefs, IMPL_FILENAME);
	if (html_len) {
		printf("\r\n");
		printf("fs_file, Setup total fs_file's data len %d\r\n", thefs.len);
		printf("fs_file, total %s content-len %d in fs_file's data\r\n", IMPL_FILENAME, html_len);
		printf(thefs.data); printf("\r\n");
	}
  } while(0);
}
#endif

/*-----------------------------------------------------------------------------------*/
err_t
fs_open(struct fs_file *file, const char *name)
{
  const struct fsdata_file *f;
  struct fsdata_file *root = (struct fsdata_file *) FS_ROOT;

  if ((file == NULL) || (name == NULL)) {
    return ERR_ARG;
  }

#if LWIP_HTTPD_CUSTOM_FILES
  if (fs_open_custom(file, name)) {
    file->is_custom_file = 1;
    return ERR_OK;
  }
  file->is_custom_file = 0;
#endif /* LWIP_HTTPD_CUSTOM_FILES */

#if HTTPD_JJ_DYNAMIC_FSDATA
  //............yukyu.....
  if (setup_dynamic_pages1(file, name)!=0)
	  return ERR_OK;
#endif
  
  for (f = root; f != NULL; f = f->next) {
    if (!strcmp(name, (const char *)f->name)) {
      file->data = (const char *)f->data;
      file->len = f->len;
      file->index = f->len;
      file->pextension = NULL;
      file->flags = f->flags;
#if HTTPD_PRECALCULATED_CHECKSUM
      file->chksum_count = f->chksum_count;
      file->chksum = f->chksum;
#endif /* HTTPD_PRECALCULATED_CHECKSUM */
#if LWIP_HTTPD_FILE_STATE
      file->state = fs_state_init(file, name);
#endif /* #if LWIP_HTTPD_FILE_STATE */
      return ERR_OK;
    }
  }
  /* file not found */
  return ERR_VAL;
}

/*-----------------------------------------------------------------------------------*/
void
fs_close(struct fs_file *file)
{
#if LWIP_HTTPD_CUSTOM_FILES
  if (file->is_custom_file) {
    fs_close_custom(file);
  }
#endif /* LWIP_HTTPD_CUSTOM_FILES */
#if LWIP_HTTPD_FILE_STATE
  fs_state_free(file, file->state);
#endif /* #if LWIP_HTTPD_FILE_STATE */
  LWIP_UNUSED_ARG(file);
}
/*-----------------------------------------------------------------------------------*/
#if LWIP_HTTPD_DYNAMIC_FILE_READ
#if LWIP_HTTPD_FS_ASYNC_READ
int
fs_read_async(struct fs_file *file, char *buffer, int count, fs_wait_cb callback_fn, void *callback_arg)
#else /* LWIP_HTTPD_FS_ASYNC_READ */
int
fs_read(struct fs_file *file, char *buffer, int count)
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
{
  int read;
  if (file->index == file->len) {
    return FS_READ_EOF;
  }
#if LWIP_HTTPD_FS_ASYNC_READ
  LWIP_UNUSED_ARG(callback_fn);
  LWIP_UNUSED_ARG(callback_arg);
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
#if LWIP_HTTPD_CUSTOM_FILES
  if (file->is_custom_file) {
#if LWIP_HTTPD_FS_ASYNC_READ
    return fs_read_async_custom(file, buffer, count, callback_fn, callback_arg);
#else /* LWIP_HTTPD_FS_ASYNC_READ */
    return fs_read_custom(file, buffer, count);
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
  }
#endif /* LWIP_HTTPD_CUSTOM_FILES */

  read = file->len - file->index;
  if (read > count) {
    read = count;
  }

  MEMCPY(buffer, (file->data + file->index), read);
  file->index += read;

  return (read);
}
#endif /* LWIP_HTTPD_DYNAMIC_FILE_READ */
/*-----------------------------------------------------------------------------------*/
#if LWIP_HTTPD_FS_ASYNC_READ
int
fs_is_file_ready(struct fs_file *file, fs_wait_cb callback_fn, void *callback_arg)
{
  if (file != NULL) {
#if LWIP_HTTPD_FS_ASYNC_READ
#if LWIP_HTTPD_CUSTOM_FILES
    if (!fs_canread_custom(file)) {
      if (fs_wait_read_custom(file, callback_fn, callback_arg)) {
        return 0;
      }
    }
#else /* LWIP_HTTPD_CUSTOM_FILES */
    LWIP_UNUSED_ARG(callback_fn);
    LWIP_UNUSED_ARG(callback_arg);
#endif /* LWIP_HTTPD_CUSTOM_FILES */
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
  }
  return 1;
}
#endif /* LWIP_HTTPD_FS_ASYNC_READ */
/*-----------------------------------------------------------------------------------*/
int
fs_bytes_left(struct fs_file *file)
{
  return file->len - file->index;
}