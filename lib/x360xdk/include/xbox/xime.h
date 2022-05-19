/*

    Copyright (c) Microsoft Corporation. All rights reserved.

    XIME - public header file.

*/

#ifndef    __XIME_H__
#define    __XIME_H__

#include <xtl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XEIME_JP_MAX_INPUT_CHARACTERS       30
#define XEIME_JP_MAX_NUMBER_OF_CLAUSES      XEIME_JP_MAX_INPUT_CHARACTERS
#define XEIME_JP_SIZE_OF_USERDIC            18192
#define XIME_MAX_CANDIDATES_IN_PAGE         64
#define XIME_JP_MAX_USER_WORD_LENGTH        16

typedef DWORD (WINAPI *PFN_XIMECLOSE)(void);
typedef DWORD (WINAPI *PFN_XIMEINIT)(PFN_XIMECLOSE * pParam);


//  XIME Dictionary type
typedef enum XIMEDICTYPE{
    XIME_DIC_JP_USER = 0,
    XIME_DIC_JP_MAIN,
    XIME_DIC_JP_SUB,
    XIME_DIC_JP_TITLE,
    XIME_DIC_CHT_BOPOMOFO,
};

typedef struct _XIME_DICTIONARY{
    XIMEDICTYPE         eDicType;
    BOOL                fDicOnMemory;
    union{
        LPCSTR          pcszDicFile;
        LPVOID          pvDicMemory;
    };
}XIME_DICTIONARY, * PXIME_DICTIONARY;

typedef struct _XIME_CREATE{
    DWORD               dwNumberOfDictionaries;
    PXIME_DICTIONARY    pXimeDictionary;
    LPVOID              pvMemoryBlock;
    DWORD               dwSizeOfMemory;
    DWORD *             pdwRequiredSizeOfMemory;
    DWORD               dwProcessor;
    BOOL                fDisableJISLevel2Kanji;
    BOOL                fDisableJISAdditionalKanji;
    DWORD               dwNumberOfCandidateListInPage;
}XIME_CREATE, *PXIME_CREATE;


// XIME language type for XIMECreate()
extern
XBOXAPI
DWORD
WINAPI
XIMEJPInit(
    IN OUT      PFN_XIMECLOSE *     pParam
);

extern
XBOXAPI
DWORD
WINAPI
XIMEKRInit(
    IN OUT      PFN_XIMECLOSE *     pParam
);

extern
XBOXAPI
DWORD
WINAPI
XIMECHBopomofoInit(
    IN OUT      PFN_XIMECLOSE *     pParam
);


XBOXAPI
DWORD
WINAPI
XIMECreate(
    IN          PFN_XIMEINIT        pParam,
    IN          PXIME_CREATE        pXimeCreate
);

XBOXAPI
DWORD
WINAPI
XIMEClose(
    void
);

// XIME key type in XIMEInsertCharacter()
typedef enum XIMEKEY{
    XIME_KEY_UNICODE = 0,
    XIME_KEY_BACKSPACE,
    XIME_KEY_DELETE,
    XIME_KEY_HOME,
    XIME_KEY_END,
    XIME_KEY_RIGHT,
    XIME_KEY_LEFT,
    XIME_KEY_ALL_HIRAGANA,
    XIME_KEY_ALL_KATAKANA,
    XIME_KEY_ALL_ALPHANUMERIC_FULL_WIDTH,
    XIME_KEY_ALL_ALPHANUMERIC_HALF_WIDTH,
    XIME_KEY_REVERT,
    XIME_KEY_FLUSH,
    XIME_KEY_CONVERT,
    XIME_KEY_COMPLETE,
};

// Defines for dwXIMEMode : XIME combination method in XIMEInsertCharacter()
// Language Flag
#define XIME_LANGUAGE_MASK                  0xf0000000
#define XIME_LANGUAGE_JAPANESE              0x10000000
#define XIME_LANGUAGE_HANGUL                0x20000000
#define XIME_LANGUAGE_BOPOMOFO              0x30000000

// Keyboard layout flag
#define XIME_LAYOUT_MASK                    0x0000000f
#define XIME_LAYOUT_KANA                    0x00000001
#define XIME_LAYOUT_ALPHANUMERIC            0x00000002
#define XIME_LAYOUT_UI_KEYBOARD             0x00000003

// Comnibe method flag
#define XIME_COMBINE_MASK                   0x000000f0
#define XIME_COMBINE_ROMAJI_HIRAGANA        0x00000010
#define XIME_COMBINE_ROMAJI_KATAKANA        0x00000020
#define XIME_COMBINE_KANA_SHIFT             0x00000030

// Display mode flag
#define XIME_DISPLAY_MASK                      0x00000f00
#define XIME_DISPLAY_ALPHANUMERIC_FULLWIDTH    0x00000100

// defined mode
#define XIME_MODE_JP_HIRAGANA_UI_KEYBOARD \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_UI_KEYBOARD | \
     XIME_COMBINE_ROMAJI_HIRAGANA)

#define XIME_MODE_JP_ROMAJI_HIRAGANA \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC | \
     XIME_COMBINE_ROMAJI_HIRAGANA)

#define XIME_MODE_JP_ROMAJI_HIRAGANA_WITH_FULLWIDTH_ALPHANUMERIC \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC | \
     XIME_COMBINE_ROMAJI_HIRAGANA | \
     XIME_DISPLAY_ALPHANUMERIC_FULLWIDTH)

#define XIME_MODE_JP_KATAKANA_UI_KEYBOARD \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_UI_KEYBOARD | \
     XIME_COMBINE_ROMAJI_KATAKANA)

#define XIME_MODE_JP_ROMAJI_KATAKANA \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC | \
     XIME_COMBINE_ROMAJI_KATAKANA)

#define XIME_MODE_JP_ROMAJI_KATAKANA_WITH_FULLWIDTH_ALPHANUMERIC \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC | \
     XIME_COMBINE_ROMAJI_KATAKANA | \
     XIME_DISPLAY_ALPHANUMERIC_FULLWIDTH)

#define XIME_MODE_JP_KANAINPUT_WITH_KEYSTROKE_SHIFTFLAG_OFF \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_KANA)

#define XIME_MODE_JP_KANAINPUT_WITH_KEYSTROKE_SHIFTFLAG_ON  \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_KANA | \
     XIME_COMBINE_KANA_SHIFT)

#define XIME_MODE_JP_FULLWIDTH_ALPHANUMERIC_UI_KEYBOARD \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_UI_KEYBOARD | \
     XIME_DISPLAY_ALPHANUMERIC_FULLWIDTH)

#define XIME_MODE_JP_FULLWIDTH_ALPHANUMERIC \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC | \
     XIME_DISPLAY_ALPHANUMERIC_FULLWIDTH)

#define XIME_MODE_JP_HALFWIDTH_ALPHANUMERIC_UI_KEYBOARD \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_UI_KEYBOARD )

#define XIME_MODE_JP_HALFWIDTH_ALPHANUMERIC \
    (XIME_LANGUAGE_JAPANESE | \
     XIME_LAYOUT_ALPHANUMERIC)


#define XIME_MODE_KR_HANGUL         XIME_LANGUAGE_HANGUL
#define XIME_MODE_CHT_BOPOMOFO      XIME_LANGUAGE_BOPOMOFO


#define XIME_EXTEND_ERROR_KEY_TAKEN     0
#define XIME_EXTEND_ERROR_KEY_NOTTAKEN  1

XBOXAPI
DWORD
WINAPI
XIMEInsertCharacter(
    IN          WCHAR               wInsertChar,
    IN          XIMEKEY             eControlKey,
    IN          DWORD               dwXIMEMode,
    IN          PXOVERLAPPED        pXOverLapped
);

#define XIME_NO_CHARACTER_LIMIT          DWORD(-1)

XBOXAPI
DWORD
WINAPI
XIMESetCharacterLimit(
    IN          DWORD               cwchNumberOfCharacters
);


// Type definition for XIMEGetClauseInfo()
#define XIME_NO_CURSOR              DWORD(-1)
#define XIME_NO_HIGHLIGHT_CLAUSE    DWORD(-1)
#define XIME_NO_DETERMINED_CLAUSE   DWORD(-1)

XBOXAPI
DWORD
WINAPI
XIMEGetClauseInfo(
    OUT         DWORD *         pdwHighLightClause,
    OUT         DWORD *         pdwNumberOfClauses                  OPTIONAL,
    OUT         DWORD *         pdwCursorPosition,
    OUT         DWORD *         pdwDeterminedClause,
    OUT         LPWSTR          pwszClauseString,
    IN          DWORD           cwchClauseString,
    OUT         DWORD *         pcwchRequiredClauseString           OPTIONAL,
    OUT         DWORD *         pdwNumberOfCandidateList            OPTIONAL,
    OUT         LPWSTR          pwszClauseReadingString             OPTIONAL,
    IN          DWORD           cwchClauseReadingString             OPTIONAL
);

XBOXAPI
DWORD
WINAPI
XIMERevertString(
    IN         PXOVERLAPPED     pXOverLapped
);

XBOXAPI
DWORD
WINAPI
XIMEMoveClauseFocus(
    IN          BOOL            fMoveToRight,
    IN          PXOVERLAPPED    pXOverLapped
);

XBOXAPI
DWORD
WINAPI
XIMEChangeClauseLength(
    IN          BOOL            fIncreaseCharacter,
    IN          PXOVERLAPPED    pXOverLapped
);

XBOXAPI
DWORD
WINAPI
XIMEBuildCandidateList(
    IN          PXOVERLAPPED    pXOverLapped
);

// Index type for XIMESetCandidateIndex()
typedef enum XIMEINDEX{
    XIME_INDEX_TOP = 0,
    XIME_INDEX_TOP_OF_PREV_PAGE,
    XIME_INDEX_END_OF_PREV_PAGE,
    XIME_INDEX_PREV,
    XIME_INDEX_CURRENT_PAGE_OFFSET,
    XIME_INDEX_CURRENT,
    XIME_INDEX_NEXT,
    XIME_INDEX_TOP_OF_NEXT_PAGE,
    XIME_INDEX_END_OF_NEXT_PAGE,
    XIME_INDEX_HIRAGANA_CANDIDATE,
    XIME_INDEX_KATAKANA_CANDIDATE,
    XIME_INDEX_HIRAGANA_KATAKANA_TOGGLE,
    XIME_INDEX_END,
};

XBOXAPI
DWORD
WINAPI
XIMESetCandidateIndex(
    IN          XIMEINDEX       eXimeIndex,
    IN          DWORD           dwCurrentPageOffset,
    IN          BOOL            fUpdateClause,
    IN          PXOVERLAPPED    pXOverLapped
);

XBOXAPI
DWORD
WINAPI
XIMEGetCandidateListInfo(
    OUT         LPWSTR      pwszCandidateStrings                    OPTIONAL,
    IN          DWORD       cwchCandidateStrings,
    OUT         DWORD *     pcwchRequiredCandidateStrings           OPTIONAL,
    OUT         DWORD *     pdwHightLightIndexInPage                OPTIONAL,
    OUT         DWORD *     pdwNumberOfCandidateStringsInPage       OPTIONAL,
    OUT         DWORD *     pdwHightLightIndexInList                OPTIONAL,
    OUT         DWORD *     pdwNumberOfCandidateStringsInList       OPTIONAL
);

XBOXAPI
DWORD
WINAPI
XIMEGetQueueState(
    OUT         DWORD *     pdwNumberOfQueueUsing
);


XBOXAPI
DWORD
WINAPI
XIMEUpdateUserDicMemory(
    IN          PXOVERLAPPED    pXOverLapped
);

typedef enum XIMEPOS{
    XIMEPOS_NOUN = 100,
    XIMEPOS_PSEUDO_NOUN_SURU,
    XIMEPOS_PSEUDO_NOUN_ZURU,
    XIMEPOS_ADJECTIVAL_NOUN,
    XIMEPOS_ADVERBIAL_NOUN,
    XIMEPOS_PSEUDO_ADJECTIVAL_NOUN,
    XIMEPOS_HUMAN_NAME,
    XIMEPOS_FAMILY_NAME,
    XIMEPOS_GIVEN_NAME,
    XIMEPOS_PLACE_NAME,
    XIMEPOS_PROPER_NOUN = 118,
    XIMEPOS_VERB_5THSTEP_A_WA = 200,
    XIMEPOS_VERB_5THSTEP_KA,
    XIMEPOS_VERB_5THSTEP_GA,
    XIMEPOS_VERB_5THSTEP_SA,
    XIMEPOS_VERB_5THSTEP_TA,
    XIMEPOS_VERB_5THSTEP_NA,
    XIMEPOS_VERB_5THSTEP_BA,
    XIMEPOS_VERB_5THSTEP_MA,
    XIMEPOS_VERB_5THSTEP_RA,
    XIMEPOS_VERB_1STSTEP = 213,
    XIMEPOS_ADJECTIVE = 300,
    XIMEPOS_NOMINAL_ADJECTIVE = 400,
    XIMEPOS_ADVERB = 500,
    XIMEPOS_ADNOUN = 600,
    XIMEPOS_CONJUNCTION = 650,
    XIMEPOS_INTERJECTION = 670,
    XIMEPOS_PREFIX = 700,
    XIMEPOS_SUFFIX = 800,
    XIMEPOS_SUFFIX_FOR_NUMERALS = 827,
    XIMEPOS_SINGLE_KANJI = 900,
    XIMEPOS_FACE_MARK,
    XIMEPOS_IDIOM,
};


XBOXAPI
DWORD
WINAPI
XIMERegisterUserWord(
    IN      LPCWSTR                 pcwszReadingString,
    IN      LPCWSTR                 pcwszDisplayString,
    IN      XIMEPOS                 XimePos,
    IN      PXOVERLAPPED            pXOverLapped
);

#define XIME_DELETE_ALL_USER_WORDS  DWORD(-1)

XBOXAPI
DWORD
WINAPI
XIMEDeleteUserWord(
    IN      DWORD                   dwIndex,
    IN      PXOVERLAPPED            pXOverLapped
);

typedef struct _XIME_USER_WORD {
    OUT     DWORD                   dwIndex;
    OUT     WCHAR                   wchReadingString[XIME_JP_MAX_USER_WORD_LENGTH+1];
    OUT     WCHAR                   wchDisplayString[XIME_JP_MAX_USER_WORD_LENGTH+1];
    OUT     XIMEPOS                 XimePos;
}XIME_USER_WORD, *PXIME_USER_WORD;

XBOXAPI
DWORD
WINAPI
XIMEEnumerateUserWords (
    IN      DWORD                   dwStartIndex,
    IN OUT  DWORD     *             pdwNumberOfEnumUserWords,
    OUT     PXIME_USER_WORD         pXIMEEnumUserWord                OPTIONAL,
    IN      PXOVERLAPPED            pXOverLapped
);

typedef struct _XIME_ENUM_TITLE_DICTIONARY{
    IN      BOOL                    fDicOnMemory;
    union{
        IN  LPCSTR                pcszDicFile;
        IN  LPVOID                pvDicMemory;
    };
    OUT     LPWSTR              pwszDictionaryTitleString;
    IN      DWORD               cwchDictionaryTitleString;
}XIME_ENUM_TITLE_DICTIONARY, *PXIME_ENUM_TITLE_DICTIONARY;


XBOXAPI
DWORD
WINAPI
XIMEEnumerateDictionarySummary (
    IN OUT  DWORD *                         pdwNumberOfDictionaries,
    IN      PXIME_ENUM_TITLE_DICTIONARY     pXimeDicTitle,
    IN      PXOVERLAPPED                    pXOverLapped            OPTIONAL
);

#ifdef __cplusplus
} /* end of 'extern "C" {' */
#endif

#endif    //__XIME_H__
