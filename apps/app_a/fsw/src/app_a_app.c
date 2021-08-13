/*=======================================================================================
** File Name:  app_a_app.c
**
** Title:  Function Definitions for APP_A Application
**
** $Author:    Patrick Custer
** $Revision: 1.1 $
** $Date:      2021-07-12
**
** Purpose:  This source file contains all necessary function definitions to run APP_A
**           application.
**
** Functions Defined:
**    Function X - Brief purpose of function X
**    Function Y - Brief purpose of function Y
**    Function Z - Brief purpose of function Z
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-07-12 | Patrick Custer | Build #: Code Started
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include <string.h>

#include "cfe.h"

#include "app_a_platform_cfg.h"
#include "app_a_mission_cfg.h"
#include "app_a_app.h"
#include "app_b_msgids.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/
APP_A_AppData_t  g_APP_A_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: APP_A_InitEvent
**
** Purpose: To initialize and register event table for APP_A application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_EVS_Register
**    CFE_ES_WriteToSysLog
**
** Called By:
**    APP_A_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_APP_A_AppData.EventTbl
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_A_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_APP_A_AppData.EventTbl, 0x00, sizeof(g_APP_A_AppData.EventTbl));

    g_APP_A_AppData.EventTbl[0].EventID = APP_A_RESERVED_EID;
    g_APP_A_AppData.EventTbl[1].EventID = APP_A_INF_EID;
    g_APP_A_AppData.EventTbl[2].EventID = APP_A_INIT_INF_EID;
    g_APP_A_AppData.EventTbl[3].EventID = APP_A_ILOAD_INF_EID;
    g_APP_A_AppData.EventTbl[4].EventID = APP_A_CDS_INF_EID;
    g_APP_A_AppData.EventTbl[5].EventID = APP_A_CMD_INF_EID;

    g_APP_A_AppData.EventTbl[ 6].EventID = APP_A_ERR_EID;
    g_APP_A_AppData.EventTbl[ 7].EventID = APP_A_INIT_ERR_EID;
    g_APP_A_AppData.EventTbl[ 8].EventID = APP_A_ILOAD_ERR_EID;
    g_APP_A_AppData.EventTbl[ 9].EventID = APP_A_CDS_ERR_EID;
    g_APP_A_AppData.EventTbl[10].EventID = APP_A_CMD_ERR_EID;
    g_APP_A_AppData.EventTbl[11].EventID = APP_A_PIPE_ERR_EID;
    g_APP_A_AppData.EventTbl[12].EventID = APP_A_MSGID_ERR_EID;
    g_APP_A_AppData.EventTbl[13].EventID = APP_A_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_APP_A_AppData.EventTbl,
                               APP_A_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("APP_A - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_A_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for APP_A application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_CreatePipe
**    CFE_SB_Subscribe
**    CFE_ES_WriteToSysLog
**
** Called By:
**    APP_A_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_A_AppData.usSchPipeDepth
**    g_APP_A_AppData.cSchPipeName
**    g_APP_A_AppData.SchPipeId
**    g_APP_A_AppData.usCmdPipeDepth
**    g_APP_A_AppData.cCmdPipeName
**    g_APP_A_AppData.CmdPipeId
**    g_APP_A_AppData.usTlmPipeDepth
**    g_APP_A_AppData.cTlmPipeName
**    g_APP_A_AppData.TlmPipeId
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_A_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe */
    g_APP_A_AppData.usSchPipeDepth = APP_A_SCH_PIPE_DEPTH;
    memset((void*)g_APP_A_AppData.cSchPipeName, '\0', sizeof(g_APP_A_AppData.cSchPipeName));
    strncpy(g_APP_A_AppData.cSchPipeName, "APP_A_SCH_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to Wakeup messages */
    iStatus = CFE_SB_CreatePipe(&g_APP_A_AppData.SchPipeId,
                                 g_APP_A_AppData.usSchPipeDepth,
                                 g_APP_A_AppData.cSchPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(APP_A_WAKEUP_MID, g_APP_A_AppData.SchPipeId, CFE_SB_Default_Qos, 1);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_A - Sch Pipe failed to subscribe to APP_A_WAKEUP_MID. (0x%08X)\n", iStatus);
            goto APP_A_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_A - Failed to create SCH pipe (0x%08X)\n", iStatus);
        goto APP_A_InitPipe_Exit_Tag;
    }

    /* Init command pipe */
    g_APP_A_AppData.usCmdPipeDepth = APP_A_CMD_PIPE_DEPTH ;
    memset((void*)g_APP_A_AppData.cCmdPipeName, '\0', sizeof(g_APP_A_AppData.cCmdPipeName));
    strncpy(g_APP_A_AppData.cCmdPipeName, "APP_A_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_APP_A_AppData.CmdPipeId,
                                 g_APP_A_AppData.usCmdPipeDepth,
                                 g_APP_A_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(APP_A_CMD_MID, g_APP_A_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_A - CMD Pipe failed to subscribe to APP_A_CMD_MID. (0x%08X)\n", iStatus);
            goto APP_A_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(APP_A_SEND_HK_MID, g_APP_A_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_A - CMD Pipe failed to subscribe to APP_A_SEND_HK_MID. (0x%08X)\n", iStatus);
            goto APP_A_InitPipe_Exit_Tag;
        }

        iStatus  = CFE_SB_Subscribe(APP_B_OUT_DATA_MID, g_APP_A_AppData.CmdPipeId);
        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_A - CMD Pipe failed to subscribe to APP_B_OUT_DATA_MID. (0x%08X)\n", iStatus);
            goto APP_A_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_A - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto APP_A_InitPipe_Exit_Tag;
    }

    /* Init telemetry pipe */
    g_APP_A_AppData.usTlmPipeDepth = APP_A_TLM_PIPE_DEPTH;
    memset((void*)g_APP_A_AppData.cTlmPipeName, '\0', sizeof(g_APP_A_AppData.cTlmPipeName));
    strncpy(g_APP_A_AppData.cTlmPipeName, "APP_A_TLM_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to telemetry messages on the telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g_APP_A_AppData.TlmPipeId,
                                 g_APP_A_AppData.usTlmPipeDepth,
                                 g_APP_A_AppData.cTlmPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, g_APP_A_AppData.TlmPipeId);
        */
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_A - Failed to create TLM pipe (0x%08X)\n", iStatus);
        goto APP_A_InitPipe_Exit_Tag;
    }

APP_A_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_A_InitData
**
** Purpose: To initialize global variables used by APP_A application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_InitMsg
**
** Called By:
**    APP_A_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_APP_A_AppData.InData
**    g_APP_A_AppData.OutData
**    g_APP_A_AppData.HkTlm
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_A_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&g_APP_A_AppData.InData, 0x00, sizeof(g_APP_A_AppData.InData));

    /* Init output data */
    memset((void*)&g_APP_A_AppData.OutData, 0x00, sizeof(g_APP_A_AppData.OutData));
    CFE_SB_InitMsg(&g_APP_A_AppData.OutData,
                   APP_A_OUT_DATA_MID, sizeof(g_APP_A_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&g_APP_A_AppData.HkTlm, 0x00, sizeof(g_APP_A_AppData.HkTlm));
    CFE_SB_InitMsg(&g_APP_A_AppData.HkTlm,
                   APP_A_HK_TLM_MID, sizeof(g_APP_A_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_A_InitApp
**
** Purpose: To initialize all data local to and used by APP_A application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_WriteToSysLog
**    CFE_EVS_SendEvent
**    OS_TaskInstallDeleteHandler
**    APP_A_InitEvent
**    APP_A_InitPipe
**    APP_A_InitData
**
** Called By:
**    APP_A_AppMain
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_A_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_APP_A_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("APP_A - Failed to register the app (0x%08X)\n", iStatus);
        goto APP_A_InitApp_Exit_Tag;
    }

    if ((APP_A_InitEvent() != CFE_SUCCESS) || 
        (APP_A_InitPipe() != CFE_SUCCESS) || 
        (APP_A_InitData() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto APP_A_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&APP_A_CleanupCallback);

APP_A_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(APP_A_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "APP_A - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_A - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_A_CleanupCallback
**
** Purpose: To handle any neccesary cleanup prior to application exit
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: APP_A_RcvMsg
**
** Purpose: To receive and process messages for APP_A application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization 
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    APP_A_ProcessNewCmds
**    APP_A_ProcessNewData
**    APP_A_SendOutData
**
** Called By:
**    APP_A_Main
**
** Global Inputs/Reads:
**    g_APP_A_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_APP_A_AppData.uiRunStatus
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_A_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(APP_A_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_APP_A_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(APP_A_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case APP_A_WAKEUP_MID:
                APP_A_ProcessNewCmds();
                APP_A_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                   automatically publish new output. */
                APP_A_SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(APP_A_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_A - Recvd invalid SCH msgId (0x%08X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, you can do something here, or nothing */
    }
    else
    {
        /* This is an example of exiting on an error.
        ** Note that a SB read error is not always going to result in an app quitting.
        */
        CFE_EVS_SendEvent(APP_A_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "APP_A: SB pipe read error (0x%08X), app will exit", iStatus);
        g_APP_A_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_A_ProcessNewData
**
** Purpose: To process incoming data subscribed by APP_A application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**
** Called By:
**    APP_A_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   TlmMsgPtr=NULL;
    CFE_SB_MsgId_t  TlmMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&TlmMsgPtr, g_APP_A_AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            TlmMsgId = CFE_SB_GetMsgId(TlmMsgPtr);
            switch (TlmMsgId)
            {
                /* TODO:  Add code to process all subscribed data here 
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         APP_A_ProcessNavData(TlmMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(APP_A_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "APP_A - Recvd invalid TLM msgId (0x%08X)", TlmMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(APP_A_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "APP_A: CMD pipe read error (0x%08X)", iStatus);
            g_APP_A_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: APP_A_ProcessNewCmds
**
** Purpose: To process incoming command messages for APP_A application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    APP_A_ProcessNewAppCmds
**    APP_A_ReportHousekeeping
**    APP_A_ProcessAppBCmds
**
** Called By:
**    APP_A_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, g_APP_A_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case APP_A_CMD_MID:
                    APP_A_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                case APP_A_SEND_HK_MID:
                    APP_A_ReportHousekeeping();
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         APP_A_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */
                case APP_B_OUT_DATA_MID:
                    APP_A_ProcessAppBCmds(CmdMsgPtr);
                    break;

                default:
                    CFE_EVS_SendEvent(APP_A_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "APP_A - Recvd invalid CMD msgId (0x%08X)", CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(APP_A_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "APP_A: CMD pipe read error (0x%08X)", iStatus);
            g_APP_A_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: APP_A_ProcessNewAppCmds
**
** Purpose: To process command messages targeting APP_A application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    APP_A_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_A_AppData.HkTlm.usCmdCnt
**    g_APP_A_AppData.HkTlm.usCmdErrCnt
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case APP_A_NOOP_CC:
                g_APP_A_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case APP_A_RESET_CC:
                g_APP_A_AppData.HkTlm.usCmdCnt = 0;
                g_APP_A_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the APP_A commands here */
            case APP_A_DEC_B:
                g_APP_A_AppData.HkTlm.usCmdCnt++;
                CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_A_AppData.OutData, APP_A_DEC_B);
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd Decrement APP_B cmd (%d)", uiCmdCode);
                break;

            case APP_A_INC_B:
                g_APP_A_AppData.HkTlm.usCmdCnt++;
                CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_A_AppData.OutData, APP_A_INC_B);
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd Increment APP_B cmd (%d)", uiCmdCode);
                break;

            default:
                g_APP_A_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(APP_A_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_A - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}

/*=====================================================================================
** Name: APP_A_ReportHousekeeping
**
** Purpose: To send housekeeping message
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    APP_A_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  GSFC, Patrick Custer
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_APP_A_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_APP_A_AppData.HkTlm);
}

/*=====================================================================================
** Name: APP_A_ProcessAppBCmds
**
** Purpose: To process command messages originating from the APP_B application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    APP_A_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_A_AppData.HkTlm.usCmdCnt
**    g_APP_A_AppData.HkTlm.counter
**
** Limitations, Assumptions, External Events, and Notes:
**   This function is triggered by the APP_B output pipeline
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_ProcessAppBCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case APP_A_NOOP_CC:
                // this is a consistent cmd sent from APP_B, ignoring
                break;

            case APP_A_DEC:
                g_APP_A_AppData.HkTlm.usCmdCnt++;
                g_APP_A_AppData.HkTlm.counter--;
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd Decrement cmd (%d)", uiCmdCode);
                break;

            case APP_A_INC:
                g_APP_A_AppData.HkTlm.usCmdCnt++;
                g_APP_A_AppData.HkTlm.counter++;
                CFE_EVS_SendEvent(APP_A_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_A - Recvd Increment cmd (%d)", uiCmdCode);
                break;

            default:
                g_APP_A_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(APP_A_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_A - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}

/*=====================================================================================
** Name: APP_A_SendOutData
**
** Purpose: To publish 1-Wakeup cycle output data
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    APP_A_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    APP_A_ReportHousekeeping();
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_APP_A_AppData.OutData);
    CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_A_AppData.OutData, APP_A_NOOP_CC);
}
    
/*=====================================================================================
** Name: APP_A_VerifyCmdLength
**
** Purpose: To verify command length for a particular command message
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr      - command message pointer
**    uint16         usExpLength - expected command length
**
** Returns:
**    boolean bResult - result of verification
**
** Routines Called:
**    TBD
**
** Called By:
**    APP_A_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean APP_A_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult=FALSE;
    uint16  usMsgLen=0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            CFE_EVS_SendEvent(APP_A_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "APP_A - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_APP_A_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: APP_A_AppMain
**
** Purpose: To define APP_A application's entry point and main process loop
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_RunLoop
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CFE_ES_ExitApp
**    CFE_ES_WaitForStartupSync
**    APP_A_InitApp
**    APP_A_RcvMsg
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  Patrick Custer 
**
** History:  Date Written  2021-07-12
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_A_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(APP_A_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (APP_A_InitApp() != CFE_SUCCESS)
    {
        g_APP_A_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    } else {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(APP_A_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(APP_A_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(APP_A_MAIN_TASK_PERF_ID);
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_APP_A_AppData.uiRunStatus) == TRUE)
    {
        APP_A_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(APP_A_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(g_APP_A_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file app_a_app.c
**=====================================================================================*/
    