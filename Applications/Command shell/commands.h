#ifndef COMMANDS
#define COMMANDS

// commands

#define CMD_NONE              0x00
#define CMD_HELP              0x01
#define CMD_VER               0x02
#define CMD_SET               0x03
#define CMD_PFC               0x04
#define CMD_HBRIDGE           0x05
#define CMD_START             0x06
#define CMD_STOP              0x07

#define CMD_LOG     	      0x20
#define CMD_PRINTLOG          0x21
#define CMD_STARTLOG          0x22
#define CMD_MON			      0x23

#define CMD_INITQUERRY        0x80
#define CMD_SPITEST           0x81
#define CMD_ARGTEST           0x82

// Set arguments

#define SET_UNDEF               0x00
#define SET_DEVID               0x01
#define SET_PFCFS               0x03
#define SET_HBFS                0x04
#define SET_FAN                 0x10
#define SET_ADHB                0x20
#define SET_ADPFC               0x21
#define SET_UREF                0x22
#define SET_PHASE               0x23
#define SET_NONE                0xFF

#define SET_HBVIGAIN            0x30
#define SET_HBVPGAIN            0x31
#define SET_HBIIGAIN            0x32
#define SET_HBIPGAIN            0x33

#define SET_PFCVIGAIN           0x34
#define SET_PFCVPGAIN           0x35
#define SET_PFCIIGAIN           0x36
#define SET_PFCIPGAIN           0x37

#define SET_AUXVIGAIN           0x38
#define SET_AUXVPGAIN           0x39

#define SET_HBFSW               0x40
#define SET_HBVREF              0x41
#define SET_HBDUTY              0x42
#define SET_HBDEADTIME          0x43

#define SET_PFCFSW              0x44
#define SET_PFCVREF             0x45
#define SET_PFCDUTY             0x46

#define SET_AUXFSW              0x47
#define SET_AUXVREF             0x48
#define SET_AUXDUTY             0x49

#define TGL_UNDEF		      0x00
#define TGL_ON				  0x01
#define TGL_OFF				  0x02
#define TGL_NONE			  0xFF




#define MSG_ERROR_COMMAND_NOT_FOUND "Command not found"

#endif // COMMANDS

