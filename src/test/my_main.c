#include "testrunner.h"
#include "test_spiffs.h"
#include "spiffs_nucleus.h"
#include "spiffs.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SMALL_FILESYSTEM	(128 * 1024)
#define LOG_PAGE_SIZE 256

typedef  int32_t s32_t;
typedef uint32_t u32_t;
typedef  int16_t s16_t;
typedef uint16_t u16_t;
typedef   int8_t s8_t;
typedef  uint8_t u8_t;


static uint8_t *flash;
static spiffs fs;

static s32_t flash_read (u32_t addr, u32_t size, u8_t *dst) {
  memcpy (dst, flash + addr, size);
  return SPIFFS_OK;
}

static s32_t flash_write (u32_t addr, u32_t size, u8_t *src) {
  memcpy (flash + addr, src, size);
  return SPIFFS_OK;
}

static s32_t flash_erase (u32_t addr, u32_t size) {
  memset (flash + addr, 0xff, size);
  return SPIFFS_OK;
}

static void die(char * c)
{
printf("%s\n", c);
}

static void import (char *src, char *dst)
{
  int fd = open (src, O_RDONLY);
  if (fd < 0)
    die (src);

  spiffs_file fh = SPIFFS_open (&fs, dst, SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_WRONLY, 0);
  if (fh < 0)
    die("spiffs_open");

  char buff[16384];
  s32_t n;
  while ((n = read (fd, buff, sizeof (buff))) > 0)
    if (SPIFFS_write (&fs, fh, buff, n) < 0)
      die ("spiffs_write");

  if (SPIFFS_close (&fs, fh) < 0)
    die("spiffs_close");
  close (fd);
}

static void export (char *src, char *dst)
{
  spiffs_file fh = SPIFFS_open (&fs, src, SPIFFS_RDONLY, 0);
  if (fh < 0)
    die ("spiffs_open");

  int fd = open (dst, O_CREAT | O_TRUNC | O_WRONLY, 0664);
  if (fd < 0)
    die (dst);

  char buff[512];
  s32_t n;
  while ((n = SPIFFS_read (&fs, fh, buff, sizeof (buff))) > 0)
    if (write (fd, buff, n) < 0)
      die ("write");

  SPIFFS_close (&fs, fh);
  close (fd);
}


int main()
{
/*
int sz = 0;
spiffs_config cfg;
  cfg.phys_size = sz;
  cfg.phys_addr = 0;
  cfg.phys_erase_block = 0x1000;
  cfg.log_block_size = 0x1000 * (sz > SMALL_FILESYSTEM ? 2 : 1);
  cfg.log_page_size = LOG_PAGE_SIZE;
  cfg.hal_read_f = flash_read;
  cfg.hal_write_f = flash_write;
  cfg.hal_erase_f = flash_erase;

printf("hel\n");
static u8_t spiffs_work_buf[LOG_PAGE_SIZE*2];
static u8_t spiffs_fds[32*4];


fs_reset();

int res;
res  = SPIFFS_mount (&fs, &cfg,
      spiffs_work_buf,
      spiffs_fds,
      sizeof(spiffs_fds),
      malloc(65536), 65536, 0);
char *src = 0, *dst = 0;
src = (char*)malloc( 260 + 1 );	//MAX_PATH
dst = (char*)malloc( 260 + 1 );
export (src, dst);
    free (src);
    free (dst);
*/
//printf("%d\n", res);
spiffs_file fd = SPIFFS_open(&fs, "my_file", SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);
//int fd_success = open("_tests_ok", O_APPEND | O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
printf("%d\n", fd);
return 0;  

}
