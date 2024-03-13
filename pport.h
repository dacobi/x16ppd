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

enum class IOCON : unsigned char{
    BANK = 0x80
}; 

enum class MCP23017Reg : unsigned char{
    IODIR_A		= 0x00, 		///< Controls the direction of the data I/O for port A.
	IODIR_B		= 0x10,			///< Controls the direction of the data I/O for port B.
	IPOL_A		= 0x01,			///< Configures the polarity on the corresponding GPIO_ port bits for port A.
	IPOL_B		= 0x11,			///< Configures the polarity on the corresponding GPIO_ port bits for port B.
	GPINTEN_A	= 0x02,			///< Controls the interrupt-on-change for each pin of port A.
	GPINTEN_B	= 0x12,			///< Controls the interrupt-on-change for each pin of port B.
	DEFVAL_A	= 0x03,			///< Controls the default comparaison value for interrupt-on-change for port A.
	DEFVAL_B	= 0x13,			///< Controls the default comparaison value for interrupt-on-change for port B.
	INTCON_A	= 0x04,			///< Controls how the associated pin value is compared for the interrupt-on-change for port A.
	INTCON_B	= 0x14,			///< Controls how the associated pin value is compared for the interrupt-on-change for port B.
	IOCON		= 0x0A,			///< Controls the device.
    IOCONAI		= 0x05,			///< Controls the device.
	GPPU_A		= 0x06,			///< Controls the pull-up resistors for the port A pins.
	GPPU_B		= 0x16,			///< Controls the pull-up resistors for the port B pins.
	INTF_A		= 0x07,			///< Reflects the interrupt condition on the port A pins.
	INTF_B		= 0x17,			///< Reflects the interrupt condition on the port B pins.
	INTCAP_A	= 0x08,			///< Captures the port A value at the time the interrupt occured.
	INTCAP_B	= 0x18,			///< Captures the port B value at the time the interrupt occured.
	GPIO_A		= 0x09,			///< Reflects the value on the port A.
	GPIO_B		= 0x19,			///< Reflects the value on the port B.
	OLAT_A		= 0x0A,			///< Provides access to the port A output latches.
	OLAT_B		= 0x1A,			///< Provides access to the port B output latches.
};

#endif