#ifndef BK3266_CMD_LIST_H
#define BK3266_CMD_LIST_H

//Media Player
#define PLAYER_PLAY_PAUSE       "COM+PP\r\n"
#define PLAYER_VOL_UP           "COM+VP\r\n"
#define PLAYER_VOL_DWN          "COM+VD\r\n"
#define PLAYER_MEDIA_NXT        "COM+PN\r\n"
#define PLAYER_MEDIA_PRV        "COM+PV\r\n"

//HFP
#define HFP_ANSWER_CALL         "COM+CA\r\n"
#define HFP_DECLINCE_CALL       "COM+CJ\r\n"
#define HFP_HANGUP_CALL         "COM+CE\r\n"
#define HFP_RD_LAST_CALL        "COM+CR\r\n"

//SYSTEM
#define BK3266_REBOOT           "COM+REBOOT\r\n"
#define BK3266_GET_VOL          "COM+GV\r\n"
#define BK3266_DEF_VOL          "COM+V08\r\n" //Set Default start volume
#define BK3266_INC_WALKIE       "COM+V03\r\n" //Set BT_VOL to 10 when incoming walkie data detected
#define BK3266_EN_CALL          "RECV+CALLON\r\n"
#define BK3266_SET_STEREO       "RECV+STEREO\r\n"
#define BK3266_SET_EQ           "RECV+SETEQNORMAL\r\n"
#define BK3266_AUTO_CONN        "COM+GOBACK\r\n"

#endif