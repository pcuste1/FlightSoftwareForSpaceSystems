/*=======================================================================================
** File Name:  app_b_app.h
**
** Title:  Header File for APP_B Application
**
** $Author:    .
** $Revision: 1.1 $
** $Date:      2021-07-10
**
** Purpose:  To define APP_B's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-10 | . | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _APP_B_APP_H_
#define _APP_B_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "app_b_platform_cfg.h"
#include "app_b_mission_cfg.h"
#include "app_b_private_ids.h"
#include "app_b_private_types.h"
#include "app_b_perfids.h"
#include "app_b_msgids.h"
#include "app_b_msg.h"



/*
** Local Defines
*/
#define APP_B_TIMEOUT_MSEC    1000

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[APP_B_EVT_CNT];

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
       Data structure should be defined in app_b/fsw/src/app_b_private_types.h */
    APP_B_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in app_b/fsw/src/app_b_private_types.h */
    APP_B_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in app_b/fsw/src/app_b_msg.h */
    APP_B_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} APP_B_AppData_t;

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
int32  APP_B_InitApp(void);
int32  APP_B_InitEvent(void);
int32  APP_B_InitData(void);
int32  APP_B_InitPipe(void);

void  APP_B_AppMain(void);

void  APP_B_CleanupCallback(void);

int32  APP_B_RcvMsg(int32 iBlocking);

void  APP_B_ProcessNewData(void);
void  APP_B_ProcessNewCmds(void);
void  APP_B_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  APP_B_ReportHousekeeping(void);
void  APP_B_SendOutData(void);

boolean  APP_B_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _APP_B_APP_H_ */

/*=======================================================================================
** End of file app_b_app.h
**=====================================================================================*/
    