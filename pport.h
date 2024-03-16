#ifndef __PPORTBASE__
#define __PPORTBASE__ 

enum{
    PP_ERROR=-1,
    PP_LOW=0,
    PP_HIGH=1 
} pp_values;

enum {
    PP_DISABLED,
    PP_INPUT, 
    PP_OUTPUT
} pp_mode;

enum {
    PP_IDLE,
    PP_WAITREADY, 
    PP_READDATA,
    PP_SENDTAKEN,    
    PP_WRITEDATA,
    PP_SENDREADY,
    PP_WAITTAKEN
} pp_state;

enum{
    PPDM_INIT,
    PPDM_IDLE,
    PPDM_HOSTARGS,
    PPDM_HOST,
    PPDM_PINGARGS, 
    PPDM_PING, 
    PPDM_WGETARGS,
    PPDM_WGET
} ppd_mode;

enum{
    PPDS_IDLE,
    PPDS_WAITB,
    PPDS_WAITCNK,    
    PPDS_WAITCMDB,        
    PPDS_WAITCMDCNK,
    PPDS_REVICEB,      
    PPDS_REVICECNK,   
    PPDS_REVICECMDB, 
    PPDS_REVICECMDCNK, 
    PPDS_SENDB,    
    PPDS_SENDCNK
} ppd_state;

enum{
    PPDR_ERROR = 0,
    PPDR_DONE = 0,
    PPDR_QUIT = 0,
    PPDR_OK = 1,
    PPDR_MORE = 1
} pdd_revtal;

enum{
    PPDVAL_NONE,
    PPDVAL_TOIO,
    PPDVAL_TOPRG,
    PPDVAL_ROOT
} ppd_values;

enum{
    PPDERR_NONE,
    PPDERR_TIMEOUT_IO,
    PPDERR_TIMEOUT_PROG,
    PPDERR_CMD_ERROR,
    PPDERR_CMD_UNKNOWN,
    PPDERR_FATAL_IO,
    PPDERR_UNKNOWN
} pdd_error;

enum {
    PPDE_NONE,
    PPDE_RESET,
    PPDE_STATUS,
    PPDE_RESTART,
    PPDE_SHUTDOWN
} ppd_event;

enum{
    PPDCMD_HOST,
    PPDCMD_PING,
    PPDCMD_WGET
} ppd_cmds;

enum{
    HOST_RESET,
    HOST_STATUS,
    HOST_SAVE,
    HOST_RESTART,        
    HOST_SHUTDOWN
} host_args;

#endif