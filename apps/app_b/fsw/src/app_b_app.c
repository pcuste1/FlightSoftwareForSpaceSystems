/*=======================================================================================
** File Name:  app_b_app.c
**
** Title:  Function Definitions for APP_B Application
**
** $Author:    .
** $Revision: 1.1 $
** $Date:      2021-07-10
**
** Purpose:  This source file contains all necessary function definitions to run APP_B
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
**   2021-07-10 | . | Build #: Code Started
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

#include "app_b_platform_cfg.h"
#include "app_b_mission_cfg.h"
#include "app_b_app.h"
#include "app_a_msgids.h"

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
APP_B_AppData_t  g_APP_B_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: APP_B_InitEvent
**
** Purpose: To initialize and register event table for APP_B application
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
**    APP_B_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_APP_B_AppData.EventTbl
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_B_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_APP_B_AppData.EventTbl, 0x00, sizeof(g_APP_B_AppData.EventTbl));

    g_APP_B_AppData.EventTbl[0].EventID = APP_B_RESERVED_EID;
    g_APP_B_AppData.EventTbl[1].EventID = APP_B_INF_EID;
    g_APP_B_AppData.EventTbl[2].EventID = APP_B_INIT_INF_EID;
    g_APP_B_AppData.EventTbl[3].EventID = APP_B_ILOAD_INF_EID;
    g_APP_B_AppData.EventTbl[4].EventID = APP_B_CDS_INF_EID;
    g_APP_B_AppData.EventTbl[5].EventID = APP_B_CMD_INF_EID;

    g_APP_B_AppData.EventTbl[ 6].EventID = APP_B_ERR_EID;
    g_APP_B_AppData.EventTbl[ 7].EventID = APP_B_INIT_ERR_EID;
    g_APP_B_AppData.EventTbl[ 8].EventID = APP_B_ILOAD_ERR_EID;
    g_APP_B_AppData.EventTbl[ 9].EventID = APP_B_CDS_ERR_EID;
    g_APP_B_AppData.EventTbl[10].EventID = APP_B_CMD_ERR_EID;
    g_APP_B_AppData.EventTbl[11].EventID = APP_B_PIPE_ERR_EID;
    g_APP_B_AppData.EventTbl[12].EventID = APP_B_MSGID_ERR_EID;
    g_APP_B_AppData.EventTbl[13].EventID = APP_B_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_APP_B_AppData.EventTbl,
                               APP_B_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("APP_B - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_B_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for APP_B application
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
**    APP_B_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_B_AppData.usSchPipeDepth
**    g_APP_B_AppData.cSchPipeName
**    g_APP_B_AppData.SchPipeId
**    g_APP_B_AppData.usCmdPipeDepth
**    g_APP_B_AppData.cCmdPipeName
**    g_APP_B_AppData.CmdPipeId
**    g_APP_B_AppData.usTlmPipeDepth
**    g_APP_B_AppData.cTlmPipeName
**    g_APP_B_AppData.TlmPipeId
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_B_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe */
    g_APP_B_AppData.usSchPipeDepth = APP_B_SCH_PIPE_DEPTH;
    memset((void*)g_APP_B_AppData.cSchPipeName, '\0', sizeof(g_APP_B_AppData.cSchPipeName));
    strncpy(g_APP_B_AppData.cSchPipeName, "APP_B_SCH_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to Wakeup messages */
    iStatus = CFE_SB_CreatePipe(&g_APP_B_AppData.SchPipeId,
                                 g_APP_B_AppData.usSchPipeDepth,
                                 g_APP_B_AppData.cSchPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(APP_B_WAKEUP_MID, g_APP_B_AppData.SchPipeId, CFE_SB_Default_Qos, 1);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_B - Sch Pipe failed to subscribe to APP_B_WAKEUP_MID. (0x%08X)\n", iStatus);
            goto APP_B_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_B - Failed to create SCH pipe (0x%08X)\n", iStatus);
        goto APP_B_InitPipe_Exit_Tag;
    }

    /* Init command pipe */
    g_APP_B_AppData.usCmdPipeDepth = APP_B_CMD_PIPE_DEPTH ;
    memset((void*)g_APP_B_AppData.cCmdPipeName, '\0', sizeof(g_APP_B_AppData.cCmdPipeName));
    strncpy(g_APP_B_AppData.cCmdPipeName, "APP_B_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_APP_B_AppData.CmdPipeId,
                                 g_APP_B_AppData.usCmdPipeDepth,
                                 g_APP_B_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(APP_B_CMD_MID, g_APP_B_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_B - CMD Pipe failed to subscribe to APP_B_CMD_MID. (0x%08X)\n", iStatus);
            goto APP_B_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(APP_B_SEND_HK_MID, g_APP_B_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_B - CMD Pipe failed to subscribe to APP_B_SEND_HK_MID. (0x%08X)\n", iStatus);
            goto APP_B_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(APP_A_OUT_DATA_MID, g_APP_B_AppData.CmdPipeId);
        
        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("APP_B - CMD Pipe failed to subscribe to APP_A_OUT_DATA_MID. (0x%08X)\n", iStatus);
            goto APP_B_InitPipe_Exit_Tag;
        }
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_B - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto APP_B_InitPipe_Exit_Tag;
    }

    /* Init telemetry pipe */
    g_APP_B_AppData.usTlmPipeDepth = APP_B_TLM_PIPE_DEPTH;
    memset((void*)g_APP_B_AppData.cTlmPipeName, '\0', sizeof(g_APP_B_AppData.cTlmPipeName));
    strncpy(g_APP_B_AppData.cTlmPipeName, "APP_B_TLM_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to telemetry messages on the telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g_APP_B_AppData.TlmPipeId,
                                 g_APP_B_AppData.usTlmPipeDepth,
                                 g_APP_B_AppData.cTlmPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, g_APP_B_AppData.TlmPipeId);
        */
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_B - Failed to create TLM pipe (0x%08X)\n", iStatus);
        goto APP_B_InitPipe_Exit_Tag;
    }

APP_B_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_B_InitData
**
** Purpose: To initialize global variables used by APP_B application
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
**    APP_B_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_APP_B_AppData.InData
**    g_APP_B_AppData.OutData
**    g_APP_B_AppData.HkTlm
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_B_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&g_APP_B_AppData.InData, 0x00, sizeof(g_APP_B_AppData.InData));

    /* Init output data */
    memset((void*)&g_APP_B_AppData.OutData, 0x00, sizeof(g_APP_B_AppData.OutData));
    CFE_SB_InitMsg(&g_APP_B_AppData.OutData,
                   APP_B_OUT_DATA_MID, sizeof(g_APP_B_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&g_APP_B_AppData.HkTlm, 0x00, sizeof(g_APP_B_AppData.HkTlm));
    CFE_SB_InitMsg(&g_APP_B_AppData.HkTlm,
                   APP_B_HK_TLM_MID, sizeof(g_APP_B_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_B_InitApp
**
** Purpose: To initialize all data local to and used by APP_B application
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
**    APP_B_InitEvent
**    APP_B_InitPipe
**    APP_B_InitData
**
** Called By:
**    APP_B_AppMain
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_B_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_APP_B_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("APP_B - Failed to register the app (0x%08X)\n", iStatus);
        goto APP_B_InitApp_Exit_Tag;
    }

    if ((APP_B_InitEvent() != CFE_SUCCESS) || 
        (APP_B_InitPipe() != CFE_SUCCESS) || 
        (APP_B_InitData() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto APP_B_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&APP_B_CleanupCallback);

APP_B_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(APP_B_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "APP_B - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("APP_B - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_B_CleanupCallback
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: APP_B_RcvMsg
**
** Purpose: To receive and process messages for APP_B application
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
**    APP_B_ProcessNewCmds
**    APP_B_ProcessNewData
**    APP_B_SendOutData
**
** Called By:
**    APP_B_Main
**
** Global Inputs/Reads:
**    g_APP_B_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_APP_B_AppData.uiRunStatus
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 APP_B_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(APP_B_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_APP_B_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(APP_B_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case APP_B_WAKEUP_MID:
                APP_B_ProcessNewCmds();
                APP_B_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                   automatically publish new output. */
                APP_B_SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(APP_B_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_B - Recvd invalid SCH msgId (0x%08X)", MsgId);
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
        CFE_EVS_SendEvent(APP_B_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "APP_B: SB pipe read error (0x%08X), app will exit", iStatus);
        g_APP_B_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: APP_B_ProcessNewData
**
** Purpose: To process incoming data subscribed by APP_B application
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
**    APP_B_RcvMsg
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   TlmMsgPtr=NULL;
    CFE_SB_MsgId_t  TlmMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&TlmMsgPtr, g_APP_B_AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            TlmMsgId = CFE_SB_GetMsgId(TlmMsgPtr);
            switch (TlmMsgId)
            {
                /* TODO:  Add code to process all subscribed data here 
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         APP_B_ProcessNavData(TlmMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(APP_B_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "APP_B - Recvd invalid TLM msgId (0x%08X)", TlmMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(APP_B_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "APP_B: CMD pipe read error (0x%08X)", iStatus);
            g_APP_B_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: APP_B_ProcessNewCmds
**
** Purpose: To process incoming command messages for APP_B application
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
**    APP_B_ProcessNewAppCmds
**    APP_B_ReportHousekeeping
**
** Called By:
**    APP_B_RcvMsg
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, g_APP_B_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case APP_B_CMD_MID:
                    APP_B_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                case APP_B_SEND_HK_MID:
                    APP_B_ReportHousekeeping();
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         APP_B_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */
                case APP_A_OUT_DATA_MID:
                    APP_B_ProcessAppBCmds(CmdMsgPtr);
                    break;

                default:
                    CFE_EVS_SendEvent(APP_B_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "APP_B - Recvd invalid CMD msgId (0x%08X)", CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(APP_B_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "APP_B: CMD pipe read error (0x%08X)", iStatus);
            g_APP_B_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: APP_B_ProcessNewAppCmds
**
** Purpose: To process command messages targeting APP_B application
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
**    APP_B_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_B_AppData.HkTlm.usCmdCnt
**    g_APP_B_AppData.HkTlm.usCmdErrCnt
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case APP_B_NOOP_CC:
                g_APP_B_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case APP_B_RESET_CC:
                g_APP_B_AppData.HkTlm.usCmdCnt = 0;
                g_APP_B_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the APP_B commands here */
            case APP_B_INC_A:
                g_APP_B_AppData.HkTlm.usCmdCnt++;
                CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_B_AppData.OutData, APP_B_INC_A);
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd Increment APP_A cmd (%d)", uiCmdCode);
                break;

            case APP_B_DEC_A:
                g_APP_B_AppData.HkTlm.usCmdCnt++;
                CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_B_AppData.OutData, APP_B_DEC_A);
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd Decrement APP_A cmd (%d)", uiCmdCode);
                break;

            default:
                g_APP_B_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(APP_B_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_B - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: APP_B_ReportHousekeeping
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
**    APP_B_ProcessNewCmds
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
** Author(s):  GSFC, .
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_APP_B_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_APP_B_AppData.HkTlm);
}

/*=====================================================================================
** Name: APP_B_ProcessAppBCmds
**
** Purpose: To process command messages originating from the APP_A application
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
**    APP_B_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_APP_B_AppData.HkTlm.counter
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
void APP_B_ProcessAppBCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case APP_B_NOOP_CC:
                // this is a consistent cmd sent from APP_A, ignoring
                break;

            case APP_B_DEC:
                g_APP_B_AppData.HkTlm.usCmdCnt++;
                g_APP_B_AppData.HkTlm.counter--;
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd Decrement cmd (%d)", uiCmdCode);
                break;

            case APP_B_INC:
                g_APP_B_AppData.HkTlm.usCmdCnt++;
                g_APP_B_AppData.HkTlm.counter++;
                CFE_EVS_SendEvent(APP_B_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "APP_B - Recvd Increment cmd (%d)", uiCmdCode);
                break;

            default:
                g_APP_B_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(APP_B_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "APP_B - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}

/*=====================================================================================
** Name: APP_B_SendOutData
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
**    APP_B_RcvMsg
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
** Author(s):  .
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    APP_B_ReportHousekeeping();
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_APP_B_AppData.OutData);
    CFE_SB_SetCmdCode((CFE_SB_Msg_t*)&g_APP_B_AppData.OutData, APP_B_NOOP_CC);
}
    
/*=====================================================================================
** Name: APP_B_VerifyCmdLength
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
**    APP_B_ProcessNewCmds
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean APP_B_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
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

            CFE_EVS_SendEvent(APP_B_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "APP_B - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_APP_B_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: APP_B_AppMain
**
** Purpose: To define APP_B application's entry point and main process loop
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
**    APP_B_InitApp
**    APP_B_RcvMsg
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
** Author(s):  . 
**
** History:  Date Written  2021-07-10
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void APP_B_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(APP_B_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (APP_B_InitApp() != CFE_SUCCESS)
    {
        g_APP_B_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    } else {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(APP_B_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(APP_B_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(APP_B_MAIN_TASK_PERF_ID);
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_APP_B_AppData.uiRunStatus) == TRUE)
    {
        APP_B_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(APP_B_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(g_APP_B_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file app_b_app.c
**=====================================================================================*/
    