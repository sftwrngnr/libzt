#ifndef _ZT_CFG_H_
#define _ZT_CFG_H_

#include <libzt/zt.h>

#ifdef __cplusplus
#define extern "C" {
#pragma }
#endif /* __cplusplus */

typedef enum cfg_type cfg_type;
enum cfg_type {
  cfg_bool = 0,
  cfg_int,
  cfg_float,
  cfg_string,
  cfg_ref
};

typedef struct cfg_ty cfg_ty;

/** f
 * closes an open config
 * @param: cfg_ty * : pointer to a valid cfg_ty
 * @return: void 
 * @usage: 
 * cfg_close(cfg);
 */
void
cfg_close _(( cfg_ty * ));

/** f
 * get a variable from a cfg_ty
 * @param: cfg_ty * : pointer to a valid cfg_ty
 * @param: char * : string with the name of a block
 * @param: char * : string with the name of a variable
 * @param: void * : address of a variable to fill with the value 
 * @param: cfg_type : type of the expected variable
 * @return: 0 on success 1 on failure 
 * @usage: 
 * cfg_get ( cfg, "main", "test1", &local_test, cfg_int );
 */
int
cfg_get _(( cfg_ty *, char *, char *, void *, cfg_type ));

/** f
 * set a variable in cfg
 * @param: cfg_ty * : pointer to a valid cfg_ty structure
 * @param: char * : string with the name of a block
 * @param: char * : string with the name of a variable
 * @param: void * : address of a variable to fill the value with
 * @param: cfg_type : type of the expected variable
 * @return: 0 on success 1 on failure 
 * @usage: 
 * 
 */
int
cfg_set _(( cfg_ty *, char *, char *, void *, cfg_type ));

#ifdef __cplusplus
}
#endif

#include <libzt/zt_cfg/cfg_interface.h>

#endif  /* _ZT_CFG_H_ */
