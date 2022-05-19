/************************************************************************
*                                                                       *
*   Xinputdefs.h -- This module defines the structures and constants    *
*                   used by the XInput APIs                             *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/
#pragma once

#ifndef _XINPUTDEFS_H_
#define _XINPUTDEFS_H_



#ifdef __cplusplus
extern "C" {
#endif

// User index definitions
#define XUSER_MAX_COUNT                 4

#define XUSER_INDEX_FOCUS               0x000000FD
#define XUSER_INDEX_NONE                0x000000FE
#define XUSER_INDEX_ANY                 0x000000FF


// Device types available in XINPUT_CAPABILITIES
#define XINPUT_DEVTYPE_GAMEPAD          0x01
#define XINPUT_DEVTYPE_USB_KEYBOARD     0x02

// Device subtypes available in XINPUT_CAPABILITIES
#define XINPUT_DEVSUBTYPE_UNKNOWN            0x00
#define XINPUT_DEVSUBTYPE_GAMEPAD            0x01
#define XINPUT_DEVSUBTYPE_WHEEL              0x02
#define XINPUT_DEVSUBTYPE_ARCADE_STICK       0x03
#define XINPUT_DEVSUBTYPE_FLIGHT_STICK       0x04
#define XINPUT_DEVSUBTYPE_DANCEPAD           0x05
#define XINPUT_DEVSUBTYPE_GUITAR             0x06
#define XINPUT_DEVSUBTYPE_DRUM_KIT           0x08

#define XINPUT_DEVSUBTYPE_USB_KEYBOARD  0x00
#define XINPUT_DEVSUBTYPE_TEXT_INPUT    0x01

// Flags for XINPUT_CAPABILITIES
#define XINPUT_CAPS_FFB_SUPPORTED       0x0001
#define XINPUT_CAPS_WIRELESS            0x0002
#define XINPUT_CAPS_VOICE_SUPPORTED     0x0004
#define XINPUT_CAPS_PMD_SUPPORTED       0x0008

// Constants for gamepad buttons
#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000

//
// Gamepad thresholds
//

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

//
// Flags used in XINPUT_KEYSTROKE
//

#define XINPUT_KEYSTROKE_KEYDOWN        0x0001
#define XINPUT_KEYSTROKE_KEYUP          0x0002
#define XINPUT_KEYSTROKE_REPEAT         0x0004
// Modifiers
#define XINPUT_KEYSTROKE_SHIFT          0x0008
#define XINPUT_KEYSTROKE_CTRL           0x0010
#define XINPUT_KEYSTROKE_ALT            0x0020
#define XINPUT_KEYSTROKE_ALTGR          0x0040
// State Lock
#define XINPUT_KEYSTROKE_CAPSLOCK       0x0080
#define XINPUT_KEYSTROKE_NUMLOCK        0x0100
// Japanese - State Lock
#define XINPUT_KEYSTROKE_ROMAJI         0x0200
#define XINPUT_KEYSTROKE_HIRAGANA       0x0400
// Korean - State Lock
#define XINPUT_KEYSTROKE_HANGUL         0x0800
// Chinese Traditional - State Lock
#define XINPUT_KEYSTROKE_BOPOMOFO       0x2000
#define XINPUT_KEYSTROKE_CHAJEI         0x4000
// Valid
#define XINPUT_KEYSTROKE_VALIDUNICODE   0x1000
// Key is from IR remote
#define XINPUT_KEYSTROKE_REMOTE         0x8000

//
// Flags to pass to XInputGetKeystroke
//

#define XINPUT_FLAG_GAMEPAD             0x00000001
#define XINPUT_FLAG_KEYBOARD            0x00000002
#define XINPUT_FLAG_REMOTE              0x00000004
#define XINPUT_FLAG_ANYDEVICE           0x000000FF

#define XINPUT_FLAG_NO_MASQUERADE       0x10000000
#define XINPUT_FLAG_DISABLE_ABXY        0x20000000
#define XINPUT_FLAG_ANYUSER             0x40000000


//
// Flags used XINPUT_KEYBOARDSTATE modifiers
//

#define XINPUT_MODIFIER_LCONTROL        0xE0
#define XINPUT_MODIFIER_LSHIFT          0xE1
#define XINPUT_MODIFIER_LALT            0xE2
#define XINPUT_MODIFIER_LGUI            0xE3
#define XINPUT_MODIFIER_RCONTROL        0xE4
#define XINPUT_MODIFIER_RSHIFT          0xE5
#define XINPUT_MODIFIER_RALT            0xE6
#define XINPUT_MODIFIER_RGUI            0xE7

//
// Number of key codes in XINPUT_KEYBOARDSTATE
//

#define XINPUT_MAX_KEYBOARD_STATE       6

//
// Structures used by XInput APIs
//

typedef struct _XINPUT_GAMEPAD
{
    WORD                                wButtons;
    BYTE                                bLeftTrigger;
    BYTE                                bRightTrigger;
    SHORT                               sThumbLX;
    SHORT                               sThumbLY;
    SHORT                               sThumbRX;
    SHORT                               sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;

typedef struct _XINPUT_STATE
{
    DWORD                               dwPacketNumber;
    XINPUT_GAMEPAD                      Gamepad;
} XINPUT_STATE, *PXINPUT_STATE;

typedef struct _XINPUT_VIBRATION
{
    WORD                                wLeftMotorSpeed;
    WORD                                wRightMotorSpeed;
} XINPUT_VIBRATION, *PXINPUT_VIBRATION;

typedef struct _XINPUT_CAPABILITIES
{
    BYTE                                Type;
    BYTE                                SubType;
    WORD                                Flags;
    XINPUT_GAMEPAD                      Gamepad;
    XINPUT_VIBRATION                    Vibration;
} XINPUT_CAPABILITIES, *PXINPUT_CAPABILITIES;

typedef struct _XINPUT_KEYSTROKE
{
    WORD                                VirtualKey;
    WCHAR                               Unicode;
    WORD                                Flags;
    BYTE                                UserIndex;
    BYTE                                HidCode;
} XINPUT_KEYSTROKE, *PXINPUT_KEYSTROKE;

typedef struct _XINPUT_KEYBOARDSTATE {
    BYTE bModifiers;
    BYTE bReserved;
    BYTE HidCodes[XINPUT_MAX_KEYBOARD_STATE];
    WORD VKCodes[XINPUT_MAX_KEYBOARD_STATE];
} XINPUT_KEYBOARDSTATE, *PXINPUT_KEYBOARDSTATE;



#ifdef __cplusplus
}
#endif


#endif // _XINPUTDEFS_H_

