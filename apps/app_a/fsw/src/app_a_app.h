/*=======================================================================================
** File Name:  app_a_app.h
**
** Title:  Header File for APP_A Application
**
** $Author:    Patrick Custer
** $Revision: 1.1 $
** $Date:      2021-07-12
**
** Purpose:  To define APP_A's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-12 | Patrick Custer | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_A_APP_H_
#define _APP_A_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "app_a_platform_cfg.h"
#include "app_a_mission_cfg.h"
#include "app_a_private_ids.h"
#include "app_a_private_types.h"
#include "app_a_perfids.h"
#include "app_a_msgids.h"
#include "app_a_msg.h"



/*
** Local Defines
*/
#define APP_A_TIMEOUT_MSEC    1000

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[APP_A_EVT_CNT];

    /* CFE scheduling pipe */
    CFE_SB_PipeId_t  SchPipeId; 
    uint16           usSchPipeDepth;
    char             cSchPipeName[OS_MAX_API_NAME];

    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    
    /* CFE telemetry pipe */
    CFE_SB_PipeId_t  TlmPipeId;
    uint16           usTlmPipeDepth;
    char             cTlmPipeName[OS_MAX_API_NAME];

    /* Task-related */
    uint32  uiRunStatus;
    
    /* Input data - from I/O devices or subscribed from other apps' output data.
       Data structure should be defined in app_a/fsw/src/app_a_private_types.h */
    APP_A_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in app_a/fsw/src/app_a_private_types.h */
    APP_A_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in app_a/fsw/src/app_a_msg.h */
    APP_A_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} APP_A_AppData_t;

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/
int32  APP_A_InitApp(void);
int32  APP_A_InitEvent(void);
int32  APP_A_InitData(void);
int32  APP_A_InitPipe(void);

void  APP_A_AppMain(void);

void  APP_A_CleanupCallback(void);

int32  APP_A_RcvMsg(int32 iBlocking);

void  APP_A_ProcessNewData(void);
void  APP_A_ProcessNewCmds(void);
void  APP_A_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  APP_A_ReportHousekeeping(void);
void  APP_A_SendOutData(void);

boolean  APP_A_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _APP_A_APP_H_ */

/*=======================================================================================
** End of file app_a_app.h
**=====================================================================================*/
    