/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author:  Marco Accame
 * email:   marco.accame@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

// - include guard ----------------------------------------------------------------------------------------------------
#ifndef _EOTRANSMITTER_HID_H_
#define _EOTRANSMITTER_HID_H_

#ifdef __cplusplus
extern "C" {
#endif

/* @file       EOtransmitter_hid.h
    @brief      This header file implements hidden interface to a packet object.
    @author     marco.accame@iit.it
    @date       0111/2010
 **/


// - external dependencies --------------------------------------------------------------------------------------------

#include "EoCommon.h"
#include "EOpacket.h"
#include "EOropframe.h"
#include "EOrop.h"
#include "EOnvSet.h"
#include "EOagent.h"
#include "EOlist.h"
#include "EOVmutex.h"
#include "EOnv_hid.h"
#include "EOconfirmationManager.h"
#include "EOvector.h"

// - declaration of extern public interface ---------------------------------------------------------------------------
 
#include "EOtransmitter.h"


// - #define used with hidden struct ----------------------------------------------------------------------------------

#define USE_DEBUG_EOTRANSMITTER 

// - definition of the hidden struct implementing the object ----------------------------------------------------------


typedef struct      // 32 bytes on arm .... 
{
    eOropcode_t     ropcode;
    eObool_t        hasdata2update;       
    uint16_t        ropstarthere;           // the index where the rop starts inside teh ropframe. if data is available, then it is placed at ropstarthere+8
    uint16_t        ropsize;
    uint16_t        timeoffsetinsiderop;    // if time is not present its value is 0xffff 
    EOnv            thenv;
} eo_transm_regrop_info_t;  // EO_VERIFYsizeof(eo_transm_regrop_info_t, (8+24));


typedef struct
{
    uint32_t    txropframeistoobigforthepacket;
} EOtransmitterDEBUG_t;


/** @struct     EOtransmitter_hid
    @brief      Hidden definition. Implements private data used only internally by the 
                public or private (static) functions of the object and protected data
                used also by its derived objects.
 **/  
 
struct EOtransmitter_hid 
{
    EOpacket*                   txpacket;
    EOropframe*                 ropframereadytotx;
    EOropframe*                 ropframeregulars;
    EOropframe*                 ropframeoccasionals;    
    EOropframe*                 ropframereplies;
    EOrop*                      roptmp;
    EOagent*                    agent;
    EOnvSet*                    nvset;
    EOconfirmationManager*      confmanager;
    eOipv4addr_t                ipv4addr;
    eOipv4port_t                ipv4port;
    uint8_t*                    bufferropframeregulars;
    uint8_t*                    bufferropframeoccasionals;
    uint8_t*                    bufferropframereplies;
    EOlist*                     listofregropinfo; 
    eOabstime_t                 currenttime;   
    EOVmutexDerived*            mtx_replies;
    EOVmutexDerived*            mtx_regulars;
    EOVmutexDerived*            mtx_occasionals;
    EOVmutexDerived*            mtx_roptmp;
    uint64_t                    tx_seqnum;
#if defined(USE_DEBUG_EOTRANSMITTER)    
    EOtransmitterDEBUG_t        debug;
#endif 
    int32_t                     lasterror;
    int32_t                     lasterror_info0;
    int32_t                     lasterror_info1;
    int32_t                     lasterror_info2;
    uint64_t                    txdecimationprogressive;
    uint8_t                     txdecimationreplies;
    uint8_t                     txdecimationregulars;
    uint8_t                     txdecimationoccasionals;
}; 



// - declaration of extern hidden functions ---------------------------------------------------------------------------


#ifdef __cplusplus
}       // closing brace for extern "C"
#endif 
 
#endif  // include-guard

// - end-of-file (leave a blank line after)----------------------------------------------------------------------------




