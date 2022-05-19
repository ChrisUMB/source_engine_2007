/************************************************************************
*                                                                       *
*   Xinputdefs.h -- This module defines the structures and constants    *
*                   used by the force-feedback APIs                     *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef _XFFB_H_
#define _XFFB_H_



#ifdef __cplusplus
extern "C" {
#endif

//
// Flags used by Force-Feedback APIs
//

#define XINPUT_FFEFFECT_NONE                  0
#define XINPUT_FFEFFECT_CONSTANT              1
#define XINPUT_FFEFFECT_RAMP                  2
#define XINPUT_FFEFFECT_PERIODIC_SQUARE       3
#define XINPUT_FFEFFECT_PERIODIC_SINE         4
#define XINPUT_FFEFFECT_PERIODIC_TRIANGLE     5
#define XINPUT_FFEFFECT_PERIODIC_SAWTOOTHUP   6
#define XINPUT_FFEFFECT_PERIODIC_SAWTOOTHDOWN 7
#define XINPUT_FFEFFECT_CONDITION_SPRING      8
#define XINPUT_FFEFFECT_CONDITION_DAMPER      9
#define XINPUT_FFEFFECT_CONDITION_INERTIA     10
#define XINPUT_FFEFFECT_CONDITION_FRICTION    11



#define XINPUT_FFAXIS_X                       0x0004
#define XINPUT_FFAXIS_X_DIRECTION_NEGATIVE    0x0008
#define XINPUT_FFAXIS_Y                       0x0010
#define XINPUT_FFAXIS_Y_DIRECTION_NEGATIVE    0x0020
#define XINPUT_FFAXIS_Z                       0x0040
#define XINPUT_FFAXIS_Z_DIRECTION_NEGATIVE    0x0080

#define XINPUT_FFFLAG_EFFECT                  0x0100
#define XINPUT_FFFLAG_ENVELOPE                0x0200
#define XINPUT_FFFLAG_PARAMETERS              0x0400

#define XINPUT_FFFLAG_POWER_STATE             0x01
#define XINPUT_FFFLAG_PAUSE_STATE             0x02
#define XINPUT_FFFLAG_RESET_STATE             0x04
#define XINPUT_FFFLAG_CLEAR_STATE             0x10
#define XINPUT_FFFLAG_MOTOR_STATE             0x20
#define XINPUT_FFFLAG_NATIVE_EFFECT_STATE     0x40

#define XINPUT_FF_ALL                         0xFFFFFFFF
#define XINPUT_FF_INFINITE                    INFINITE



#define XINPUT_FFOPERATION_NOCHANGE           0
#define XINPUT_FFOPERATION_STOP               1
#define XINPUT_FFOPERATION_START              2
#define XINPUT_FFOPERATION_SOLO               3
#define XINPUT_FF_MAX_NUM_OPERATIONS          5



//
// Structures used by Force-Feedback APIs
//

typedef struct _XINPUT_FF_DEVICE_INFO
{
    DWORD MaxIndex;
    DWORD MaxSimultaneousEffects;
    DWORD FFAxes;
    DWORD DeviceState;
} XINPUT_FF_DEVICE_INFO, *PXINPUT_FF_DEVICE_INFO;

typedef struct _XINPUT_FF_EFFECT_OPERATION
{
    DWORD EffectIndex;
    DWORD Operation;
} XINPUT_FF_EFFECT_OPERATION, *PXINPUT_FF_EFFECT_OPERATION;

typedef struct _XINPUT_FF_EFFECT
{
    DWORD  EffectIndex;
    DWORD  EffectType;
    DWORD  Axes;
    DWORD  Gain;
    DWORD  Duration;
    DWORD  StartDelay;
    DWORD  LoopCount;

    struct
    {
        DWORD AttackLevel;
        DWORD FadeLevel;
        DWORD AttackTime;
        DWORD FadeTime;
    } Envelope;

    union
    {
        struct
        {
            INT    Magnitude;
        } ConstantForce;

        struct
        {
            INT    Start;
            INT    End;
        } RampForce;

        struct
        {
            DWORD  Magnitude;
            INT    Offset;
            DWORD  Phase;
            DWORD  Period;
        } PeriodicForce;

        struct
        {
            // Conditions for each axis: X, Y, Z, respectively
            INT    CenterOffset;            
            INT    PositiveCoefficient;
            INT    NegativeCoefficient;
            DWORD  PositiveSaturation;
            DWORD  NegativeSaturation;
            DWORD  Deadband;
        } ConditionForce[3];
    };
} XINPUT_FF_EFFECT, *PXINPUT_FF_EFFECT;


//
// Force-Feedback APIs
//

XBOXAPI
DWORD
WINAPI
XInputFFGetDeviceInfo(
    IN      DWORD                       dwUserIndex,
    OUT     XINPUT_FF_DEVICE_INFO      *pDeviceInfo
    );
    
XBOXAPI
DWORD 
WINAPI
XInputFFSetEffect(
    IN      DWORD                       dwUserIndex,
    IN      CONST XINPUT_FF_EFFECT     *pEffects,
    IN      DWORD                       dwCount,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD 
WINAPI
XInputFFUpdateEffect(
    IN      DWORD                       dwUserIndex,
    IN      CONST XINPUT_FF_EFFECT     *pEffect, 
    IN      DWORD                       dwUpdateMask,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD 
WINAPI
XInputFFEffectOperation(
    IN      DWORD                       dwUserIndex,
    IN      CONST XINPUT_FF_EFFECT_OPERATION *pEffectOperations,
    IN      DWORD                       dwNumOperations,
    IN      DWORD                       dwNativeOperation,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputFFEnableMotors(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        fEnable,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputFFPauseAllEffects(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        fPause,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputFFStopAllEffects(
    IN      DWORD                       dwUserIndex,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputFFResetDevice(
    IN      DWORD                       dwUserIndex,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD 
WINAPI
XInputFFSetDeviceGain(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwGain,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputFFCancelIo(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        fWait,
    IN      DWORD                       dwReserved
    );

XBOXAPI
DWORD
WINAPI
XInputFFSetRumble(
    IN      DWORD                       dwUserIndex,
    IN      CONST XINPUT_VIBRATION     *pVibration,
    IN      PXOVERLAPPED                Overlapped          OPTIONAL
    );


#ifdef __cplusplus
}
#endif



#endif // _XFFB_H_

