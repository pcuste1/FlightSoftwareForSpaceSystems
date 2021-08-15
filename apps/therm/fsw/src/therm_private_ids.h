/*=======================================================================================
** File Name:  therm_private_ids.h
**
** Title:  ID Header File for THERM Application
**
** $Author:    Runtime Terror
** $Revision: 1.1 $
** $Date:      2021-08-14
**
** Purpose:  This header file contains declarations and definitions of THERM's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2021-08-14 | Runtime Terror | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _THERM_PRIVATE_IDS_H_
#define _THERM_PRIVATE_IDS_H_

/*
** Pragmas
*/

/*
** Include Files
*/

/*
** Local Defines
*/

/* Event IDs */
#define THERM_RESERVED_EID  0

#define THERM_INF_EID        1
#define THERM_INIT_INF_EID   2
#define THERM_ILOAD_INF_EID  3
#define THERM_CDS_INF_EID    4
#define THERM_CMD_INF_EID    5

#define THERM_ERR_EID         51
#define THERM_INIT_ERR_EID    52
#define THERM_ILOAD_ERR_EID   53
#define THERM_CDS_ERR_EID     54
#define THERM_CMD_ERR_EID     55
#define THERM_PIPE_ERR_EID    56
#define THERM_MSGID_ERR_EID   57
#define THERM_MSGLEN_ERR_EID  58

#define THERM_EVT_CNT  14

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

#define POWERED_MINIMUM_TEMP 50 // 5 degrees
#define POWERED_MAXIMUM_TEMP 400 // 40 degrees

#define OBSERVING_MINIMUM_TEMP 200 // 20 degrees
#define OBSERVING_MAXIMUM_TEMP 250 // 25 degrees

#define HTR_

#define WISE_HTR_A (0)
#define WISE_HTR_B (1)

#define WISE_HTR_ON  (0)
#define WISE_HTR_OFF (1)

#define WISE_LVR_A (0)
#define WISE_LVR_B (1)

#define WISE_LVR_OPEN   (0)
#define WISE_LVR_CLOSED (1)

#define WISE_SBC_OFF       (0)
#define WISE_SBC_POWERED   (1)
#define WISE_SBC_OBSERVING (2)
#define WISE_SBC_ERROR     (3)

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#endif /* _THERM_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file therm_private_ids.h
**=====================================================================================*/
    