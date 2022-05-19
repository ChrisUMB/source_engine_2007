//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       d3dx9shader.h
//  Content:    D3DX Shader APIs
//
//////////////////////////////////////////////////////////////////////////////

#include "d3dx9.h"

#ifndef __D3DX9SHADER_H__
#define __D3DX9SHADER_H__


//---------------------------------------------------------------------------
// D3DXTX_VERSION:
// --------------
// Version token used to create a procedural texture filler in effects
// Used by D3DXFill[]TX functions
//---------------------------------------------------------------------------
#define D3DXTX_VERSION(_Major,_Minor) (('T' << 24) | ('X' << 16) | ((_Major) << 8) | (_Minor))


// begin_internal
//----------------------------------------------------------------------------
// D3DXFXL_VERSION:
// ----------------
// Version token used by host expression evaluator.
//----------------------------------------------------------------------------

#define D3DXFXL_VERSION(_Major,_Minor) (('F' << 24) | ('X' << 16) | ((_Major) << 8) | (_Minor)) // internal
// end_internal


//----------------------------------------------------------------------------
// D3DXSHADER/EX flags:
// -----------------
// D3DXSHADER_DEBUG
//   Insert debug file/line/type/symbol information.
//
// D3DXSHADER_SKIPVALIDATION
//   Do not validate the generated code against known capabilities and
//   constraints.  This option is only recommended when compiling shaders
//   you KNOW will work.  (ie. have compiled before without this option.)
//   Shaders are always validated by D3D before they are set to the device.
//
// D3DXSHADER_SKIPOPTIMIZATION (valid for D3DXCompileShader calls only)
//   Instructs the compiler to skip optimization steps during code generation.
//   Unless you are trying to isolate a problem in your code, and suspect the
//   compiler, using this option is not recommended.
//
// D3DXSHADER_PACKMATRIX_ROWMAJOR
//   Unless explicitly specified, matrices will be packed in row-major order
//   on input and output from the shader.
//
// D3DXSHADER_PACKMATRIX_COLUMNMAJOR
//   Unless explicitly specified, matrices will be packed in column-major
//   order on input and output from the shader.  This is generally more
//   efficient, since it allows vector-matrix multiplication to be performed
//   using a series of dot-products.
//
// D3DXSHADER_PARTIAL_PRECISION
//   Force all computations in resulting shader to occur at partial precision.
//   This may result in faster evaluation of shaders on some hardware.
//
// D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT
//   Force compiler to compile against the next highest available software
//   target for vertex shaders.  This flag also turns optimizations off,
//   and debugging on.
//
// D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT
//   Force compiler to compile against the next highest available software
//   target for pixel shaders.  This flag also turns optimizations off,
//   and debugging on.
//
// D3DXSHADER_NO_PRESHADER
//   Disables Preshaders. Using this flag will cause the compiler to not
//   pull out static expression for evaluation on the host cpu
//
// D3DXSHADER_AVOID_FLOW_CONTROL
//   Hint compiler to avoid flow-control constructs where possible.
//
// D3DXSHADER_PREFER_FLOW_CONTROL
//   Hint compiler to prefer flow-control constructs where possible.
//
// D3D10_SHADER_ENABLE_STRICTNESS
//   By default, the HLSL/Effect compilers are not strict on deprecated syntax.
//   Specifying this flag enables the strict mode. Deprecated syntax may be
//   removed in a future release, and enabling syntax is a good way to make sure
//   your shaders comply to the latest spec.
//
// D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY
//   This enables older shaders to compile to 4_0 targets.

// begin internal
//
// D3DXSHADER_FRAGMENT
//   Indicates that you are compiling code as a fragment, to be linked
//   together at a later time.  This flag implies D3DXSHADER_SKIPVALIDATION.
//
// D3DXSHADER_SKIPASMBLOCKS
//   Indicates that the parser should skip over ASM blocks without invoking
//   the assembler.  This flag is implied by D3DXCompileShader APIs.
// end internal
//----------------------------------------------------------------------------

#define D3DXSHADER_DEBUG                    (1 << 0)
#define D3DXSHADER_SKIPVALIDATION           (1 << 1)
#define D3DXSHADER_SKIPOPTIMIZATION         (1 << 2)
#define D3DXSHADER_PACKMATRIX_ROWMAJOR      (1 << 3)
#define D3DXSHADER_PACKMATRIX_COLUMNMAJOR   (1 << 4)
#define D3DXSHADER_PARTIALPRECISION         (1 << 5)
#define D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT  (1 << 6)
#define D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT  (1 << 7)
#define D3DXSHADER_NO_PRESHADER             (1 << 8)
#define D3DXSHADER_AVOID_FLOW_CONTROL       (1 << 9)
#define D3DXSHADER_PREFER_FLOW_CONTROL      (1 << 10)
#define D3D10_SHADER_ENABLE_STRICTNESS      (1 << 11)
#define D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY (1 << 12)
#define D3DXSHADER_SKIPMICROCODEOPTIMIZATION_DEPRECATED (1 << 17) // Xbox extension
#define D3DXSHADER_ZERO_INIT_LOCAL_VARS     (1 << 18)  // Xbox extension
#define D3DXSHADER_DISABLE_ZPASS_COMPARISON_VALIDATION (1 << 19) //Xbox extension
#define D3DXSHADER_SKIPMICROCODE_DEPRECATED (1 << 20)  // Xbox extension
#define D3DXSHADER_ENABLEVERIFIER           (1 << 22)  // Xbox extension
#define D3DXSHADER_MICROCODE_BACKEND_NEW    (1 << 24)  // Xbox extension
#define D3DXSHADER_MICROCODE_BACKEND_OLD_DEPRECATED (1 << 25)  // Xbox extension
// from fxl.h
//#define D3DXSHADER_FXLANNOTATE_VARIABLE_NAMES       (1 << 26)
//#define D3DXSHADER_FXLANNOTATE_SEMANTIC_NAMES       (1 << 27)
//#define D3DXSHADER_FXLPARAMETERS_AS_VARIABLE_NAMES  (1 << 28)
//#define D3DXSHADER_FXLEFFECT_NATIVE_ENDIAN          (1 << 29)
#define D3DXSHADER_FRAGMENT                 (1 << 30) // internal
#define D3DXSHADER_SKIPASMBLOCKS            (1 << 31) // internal


// begin internal
#define D3DXSHADER_VALID_ASSEMBLER_FLAGS \
    ( D3DXSHADER_DEBUG                    | \
    D3DXSHADER_SKIPVALIDATION           | \
    D3DXSHADER_SKIPMICROCODE_DEPRECATED | \
    D3DXSHADER_SKIPMICROCODEOPTIMIZATION_DEPRECATED | \
    D3DXSHADER_DISABLE_ZPASS_COMPARISON_VALIDATION)

#define D3DXSHADER_VALID_COMPILER_FLAGS \
    ( D3DXSHADER_DEBUG                    | \
    D3DXSHADER_SKIPVALIDATION           | \
    D3DXSHADER_SKIPOPTIMIZATION         | \
    D3DXSHADER_PACKMATRIX_ROWMAJOR      | \
    D3DXSHADER_PACKMATRIX_COLUMNMAJOR   | \
    D3DXSHADER_PARTIALPRECISION         | \
    D3DXSHADER_AVOID_FLOW_CONTROL       | \
    D3DXSHADER_PREFER_FLOW_CONTROL      | \
    D3D10_SHADER_ENABLE_STRICTNESS      | \
    D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | \
    D3DXSHADER_SKIPMICROCODE_DEPRECATED | \
    D3DXSHADER_SKIPMICROCODEOPTIMIZATION_DEPRECATED | \
    D3DXSHADER_ZERO_INIT_LOCAL_VARS     | \
    D3DXSHADER_MICROCODE_BACKEND_OLD_DEPRECATED | \
    D3DXSHADER_MICROCODE_BACKEND_NEW    | \
    D3DXSHADER_ENABLEVERIFIER           | \
    D3DXSHADER_DISABLE_ZPASS_COMPARISON_VALIDATION)

#define D3DXSHADER_VALID \
    ( D3DXSHADER_VALID_ASSEMBLER_FLAGS    | \
    D3DXSHADER_VALID_COMPILER_FLAGS     | \
    D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT  | \
    D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT  )

#define D3DXSHADEREX_CPUCODE_NO_INTRINSICS              (1 << 0) // Xbox extension
#define D3DXSHADEREX_GENERATE_UPDB                      (1 << 1) // Xbox extension
#define D3DXSHADEREX_OPTIMIZE_UCODE                     (1 << 2) // Xbox extension
#define D3DXSHADEREX_NO_MASKED_EXPORTS                  (1 << 3) // Xbox extension
#define D3DXSHADEREX_DEBUGGABLE_UCODE                   (1 << 4) // Xbox extension
#define D3DXSHADEREX_AUTOZ                              (1 << 5) // Xbox extension
#define D3DXSHADEREX_REMOVE_UNUSED_PS_INPUTS            (1 << 6) // Xbox extension
#define D3DXSHADEREX_AUTO_VFETCHE                       (1 << 7) // Xbox extension

#define D3DXSHADEREX_VALID_COMPILER_FLAGS \
    ( D3DXSHADEREX_CPUCODE_NO_INTRINSICS    | \
    D3DXSHADEREX_GENERATE_UPDB              | \
    D3DXSHADEREX_OPTIMIZE_UCODE             | \
    D3DXSHADEREX_NO_MASKED_EXPORTS          | \
    D3DXSHADEREX_DEBUGGABLE_UCODE           | \
    D3DXSHADEREX_AUTOZ                      | \
    D3DXSHADEREX_REMOVE_UNUSED_PS_INPUTS    | \
    D3DXSHADEREX_AUTO_VFETCHE               )
// end internal

#define D3DXDISASSEMBLER_ENABLE_COLOR                   (1 << 0)
#define D3DXDISASSEMBLER_SHOW_CONSTANT_TABLE_DEFAULTS   (1 << 1)
#define D3DXDISASSEMBLER_SHOW_DETAILS                   (1 << 2)
#define D3DXDISASSEMBLER_HIDE_PATCHED                   (1 << 3)
#define D3DXDISASSEMBLER_OUTPUT_FORMAT_RTF              (1 << 4)
#define D3DXDISASSEMBLER_SHOW_ADDRESSES                 (1 << 6)
#define D3DXDISASSEMBLER_SHOW_MICROCODE_DEFAULTS        (1 << 7)
#define D3DXDISASSEMBLER_SHOW_RUNTIME_DATA              (1 << 8)
#define D3DXDISASSEMBLER_SHOW_TIMING_ESTIMATE           (1 << 11)

// begin internal
//----------------------------------------------------------------------------
// D3DXAPI:
// --------
// Identifies different API entrypoint sets.  Used by D3DXGetTargetDesc.
//----------------------------------------------------------------------------

#define D3DXAPI_ASSEMBLE_SHADER    (1 << 0)
#define D3DXAPI_COMPILE_SHADER     (1 << 1)
#define D3DXAPI_FILL_TEXTURE       (1 << 2)
// end internal


//----------------------------------------------------------------------------
// D3DXHANDLE:
// -----------
// Handle values used to efficiently reference shader and effect parameters.
// On Xbox 360, strings cannot be used as handles (handles are never strings).
//----------------------------------------------------------------------------

typedef DWORD D3DXHANDLE;
typedef D3DXHANDLE *LPD3DXHANDLE;


//----------------------------------------------------------------------------
// D3DXMACRO:
// ----------
// Preprocessor macro definition.  The application pass in a NULL-terminated
// array of this structure to various D3DX APIs.  This enables the application
// to #define tokens at runtime, before the file is parsed.
//----------------------------------------------------------------------------

typedef struct _D3DXMACRO
{
    LPCSTR Name;
    LPCSTR Definition;

} D3DXMACRO, *LPD3DXMACRO;


//----------------------------------------------------------------------------
// D3DXSEMANTIC:
//----------------------------------------------------------------------------

typedef struct _D3DXSEMANTIC
{
    UINT Usage;
    UINT UsageIndex;

} D3DXSEMANTIC, *LPD3DXSEMANTIC;


// begin internal
//----------------------------------------------------------------------------
// D3DXTARGET_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXTARGET_DESC
{
    LPCSTR Name;
    DWORD Version;
    DWORD API;

} D3DXTARGET_DESC, *LPD3DXTARGET_DESC;
// end internal


//----------------------------------------------------------------------------
// D3DXFRAGMENT_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXFRAGMENT_DESC
{
    LPCSTR Name;
    DWORD Target;

} D3DXFRAGMENT_DESC, *LPD3DXFRAGMENT_DESC;


//----------------------------------------------------------------------------
// D3DXREGISTER_SET:
//----------------------------------------------------------------------------

typedef enum _D3DXREGISTER_SET
{
    D3DXRS_BOOL,
    D3DXRS_INT4,
    D3DXRS_FLOAT4,
    D3DXRS_SAMPLER,

    // force 32-bit size enum
    D3DXRS_FORCE_DWORD = 0x7fffffff

} D3DXREGISTER_SET, *LPD3DXREGISTER_SET;


//----------------------------------------------------------------------------
// D3DXPARAMETER_CLASS:
//----------------------------------------------------------------------------

typedef enum _D3DXPARAMETER_CLASS
{
    D3DXPC_SCALAR,
    D3DXPC_VECTOR,
    D3DXPC_MATRIX_ROWS,
    D3DXPC_MATRIX_COLUMNS,
    D3DXPC_OBJECT,
    D3DXPC_STRUCT,

    // force 32-bit size enum
    D3DXPC_FORCE_DWORD = 0x7fffffff

} D3DXPARAMETER_CLASS, *LPD3DXPARAMETER_CLASS;


//----------------------------------------------------------------------------
// D3DXPARAMETER_TYPE:
//----------------------------------------------------------------------------

typedef enum _D3DXPARAMETER_TYPE
{
    D3DXPT_VOID,
    D3DXPT_BOOL,
    D3DXPT_INT,
    D3DXPT_FLOAT,
    D3DXPT_STRING,
    D3DXPT_TEXTURE,
    D3DXPT_TEXTURE1D,
    D3DXPT_TEXTURE2D,
    D3DXPT_TEXTURE3D,
    D3DXPT_TEXTURECUBE,
    D3DXPT_SAMPLER,
    D3DXPT_SAMPLER1D,
    D3DXPT_SAMPLER2D,
    D3DXPT_SAMPLER3D,
    D3DXPT_SAMPLERCUBE,
    D3DXPT_PIXELSHADER,
    D3DXPT_VERTEXSHADER,
    D3DXPT_PIXELFRAGMENT,
    D3DXPT_VERTEXFRAGMENT,

    // force 32-bit size enum
    D3DXPT_FORCE_DWORD = 0x7fffffff

} D3DXPARAMETER_TYPE, *LPD3DXPARAMETER_TYPE;


//----------------------------------------------------------------------------
// D3DXCONSTANTTABLE_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXCONSTANTTABLE_DESC
{
    LPCSTR Creator;                     // Creator string
    DWORD Version;                      // Shader version
    UINT Constants;                     // Number of constants

} D3DXCONSTANTTABLE_DESC, *LPD3DXCONSTANTTABLE_DESC;


//----------------------------------------------------------------------------
// D3DXCONSTANT_DESC:
//----------------------------------------------------------------------------

typedef struct _D3DXCONSTANT_DESC
{
    LPCSTR Name;                        // Constant name

    D3DXREGISTER_SET RegisterSet;       // Register set
    UINT RegisterIndex;                 // Register index
    UINT RegisterCount;                 // Number of registers occupied

    D3DXPARAMETER_CLASS Class;          // Class
    D3DXPARAMETER_TYPE Type;            // Component type

    UINT Rows;                          // Number of rows
    UINT Columns;                       // Number of columns
    UINT Elements;                      // Number of array elements
    UINT StructMembers;                 // Number of structure member sub-parameters

    UINT Bytes;                         // Data size, in bytes
    LPCVOID DefaultValue;               // Pointer to default value

} D3DXCONSTANT_DESC, *LPD3DXCONSTANT_DESC;



//----------------------------------------------------------------------------
// ID3DXConstantTable:
//----------------------------------------------------------------------------

// {9DCA3190-38B9-4fc3-92E3-39C6DDFB358B}
DEFINE_GUID( IID_ID3DXConstantTable,
            0x9dca3190, 0x38b9, 0x4fc3, 0x92, 0xe3, 0x39, 0xc6, 0xdd, 0xfb, 0x35, 0x8b);


#undef INTERFACE
#define INTERFACE ID3DXConstantTable

DECLARE_INTERFACE_(ID3DXConstantTable, ID3DXBuffer)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBuffer
    STDMETHOD_(LPVOID, GetBufferPointer)(THIS) PURE;
    STDMETHOD_(DWORD, GetBufferSize)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ D3DXCONSTANTTABLE_DESC *pDesc) PURE;
    STDMETHOD(GetConstantDesc)(THIS_ D3DXHANDLE hConstant, D3DXCONSTANT_DESC *pConstantDesc, UINT *pCount) PURE;
    STDMETHOD_(UINT, GetSamplerIndex)(THIS_ D3DXHANDLE hConstant) PURE;

    // Handle operations
    STDMETHOD_(D3DXHANDLE, GetConstant)(THIS_ D3DXHANDLE hConstant, UINT Index) PURE;
    STDMETHOD_(D3DXHANDLE, GetConstantByName)(THIS_ D3DXHANDLE hConstant, LPCSTR pName) PURE;
    STDMETHOD_(D3DXHANDLE, GetConstantElement)(THIS_ D3DXHANDLE hConstant, UINT Index) PURE;

    // Set Constants
    STDMETHOD(SetDefaults)(THIS_ LPDIRECT3DDEVICE9 pDevice) PURE;
    STDMETHOD(SetValue)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, LPCVOID pData, UINT Bytes) PURE;
    STDMETHOD(SetBool)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, BOOL b) PURE;
    STDMETHOD(SetBoolArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST BOOL* pb, UINT Count) PURE;
    STDMETHOD(SetInt)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, INT n) PURE;
    STDMETHOD(SetIntArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST INT* pn, UINT Count) PURE;
    STDMETHOD(SetFloat)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, FLOAT f) PURE;
    STDMETHOD(SetFloatArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST FLOAT* pf, UINT Count) PURE;
    STDMETHOD(SetVector)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXVECTOR4* pVector) PURE;
    STDMETHOD(SetVectorArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXVECTOR4* pVector, UINT Count) PURE;
    STDMETHOD(SetMatrix)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixPointerArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX* pMatrix, UINT Count) PURE;
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ LPDIRECT3DDEVICE9 pDevice, D3DXHANDLE hConstant, CONST D3DXMATRIX** ppMatrix, UINT Count) PURE;
};

typedef interface ID3DXConstantTable ID3DXConstantTable;
typedef interface ID3DXConstantTable *LPD3DXCONSTANTTABLE;


//----------------------------------------------------------------------------
// ID3DXFragmentLinker
//----------------------------------------------------------------------------

#undef INTERFACE
#define INTERFACE ID3DXFragmentLinker

// {D59D3777-C973-4a3c-B4B0-2A62CD3D8B40}
DEFINE_GUID(IID_ID3DXFragmentLinker,
            0xd59d3777, 0xc973, 0x4a3c, 0xb4, 0xb0, 0x2a, 0x62, 0xcd, 0x3d, 0x8b, 0x40);


DECLARE_INTERFACE_(ID3DXFragmentLinker, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXFragmentLinker

    // fragment access and information retrieval functions
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE9* ppDevice) PURE;
    STDMETHOD_(UINT, GetNumberOfFragments)(THIS) PURE;

    STDMETHOD_(D3DXHANDLE, GetFragmentHandleByIndex)(THIS_ UINT Index) PURE;
    STDMETHOD_(D3DXHANDLE, GetFragmentHandleByName)(THIS_ LPCSTR Name) PURE;
    STDMETHOD(GetFragmentDesc)(THIS_ D3DXHANDLE Name, LPD3DXFRAGMENT_DESC FragDesc) PURE;

    // add the fragments in the buffer to the linker
    STDMETHOD(AddFragments)(THIS_ CONST DWORD *Fragments) PURE;

    // Create a buffer containing the fragments.  Suitable for saving to disk
    STDMETHOD(GetAllFragments)(THIS_ LPD3DXBUFFER *ppBuffer) PURE;
    STDMETHOD(GetFragment)(THIS_ D3DXHANDLE Name, LPD3DXBUFFER *ppBuffer) PURE;

    STDMETHOD(LinkShader)(THIS_ LPCSTR pProfile, DWORD Flags, CONST D3DXHANDLE *rgFragmentHandles, UINT cFragments, LPD3DXBUFFER *ppBuffer, LPD3DXBUFFER *ppErrorMsgs) PURE;
    STDMETHOD(LinkVertexShader)(THIS_ LPCSTR pProfile, DWORD Flags, CONST D3DXHANDLE *rgFragmentHandles, UINT cFragments, LPDIRECT3DVERTEXSHADER9 *pVShader, LPD3DXBUFFER *ppErrorMsgs) PURE;
    STDMETHOD(LinkPixelShader)(THIS_ LPCSTR pProfile, DWORD Flags, CONST D3DXHANDLE *rgFragmentHandles, UINT cFragments, LPDIRECT3DPIXELSHADER9 *pPShader, LPD3DXBUFFER *ppErrorMsgs) PURE;

    STDMETHOD(ClearCache)(THIS) PURE;
};


//----------------------------------------------------------------------------
// D3DXINCLUDE_TYPE:
//----------------------------------------------------------------------------

typedef enum _D3DXINCLUDE_TYPE
{
    D3DXINC_LOCAL,
    D3DXINC_SYSTEM,

    // force 32-bit size enum
    D3DXINC_FORCE_DWORD = 0x7fffffff

} D3DXINCLUDE_TYPE, *LPD3DXINCLUDE_TYPE;


//----------------------------------------------------------------------------
// ID3DXInclude:
// -------------
// This interface is intended to be implemented by the application, and can
// be used by various D3DX APIs.  This enables application-specific handling
// of #include directives in source files.
//
// Open()
//    Opens an include file.  If successful, it should fill in ppData and
//    pBytes.  The data pointer returned must remain valid until Close is
//    subsequently called.
//
//    Xbox 360 Extension: To aid source level debugging, Open() may optionally
//    return the full path to the found include file, by storing it in the
//    buffer pointed to by pFullPath. The full path may be up to cbFullPath
//    characters long, including the terminating '\0' character.
//
// Close()
//    Closes an include file.  If Open was successful, Close is guaranteed
//    to be called before the API using this interface returns.
//----------------------------------------------------------------------------

typedef interface ID3DXInclude ID3DXInclude;
typedef interface ID3DXInclude *LPD3DXINCLUDE;

#undef INTERFACE
#define INTERFACE ID3DXInclude

DECLARE_INTERFACE(ID3DXInclude)
{
    STDMETHOD(Open)(THIS_ D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData,
        LPCVOID *ppData, UINT *pBytes,
        /* OUT */ LPSTR pFullPath, DWORD cbFullPath) PURE;
    STDMETHOD(Close)(THIS_ LPCVOID pData) PURE;
};

//----------------------------------------------------------------------------
// D3DXSHADER_COMPILE_PARAMETERS:
//----------------------------------------------------------------------------

typedef struct _D3DXSHADER_COMPILE_PARAMETERSA
{
    // Fields use by both assembler and compiler:

    DWORD   Flags;                      // D3DXSHADEREX_* flags
    DWORD   UPDBTimestamp;              // UPDB Timestamp for this compile.
    LPCSTR  UPDBPath;                   // UPDB path for this compile.
    LPD3DXBUFFER pUPDBBuffer;           // OUT parameter, the resulting UPDB data, caller is responsible for releasing.
    DWORD   TempRegisterLimit;          // Maximum number of general registers available to the generated microcode.
    LPVOID  pUPDBB;                     // Must be NULL.

    // Compiler-specific fields:

    LPCSTR  CpuFunctionName;            // Name to use for generated CPU shader function (NULL to use HLSL entry-point)
    BOOL    bXbox360ExtensionUsed;      // Filled in by CParse and/or the new back end. Used to avoid calling the old back end
    DWORD   PixelShaderSamplerRegisterBase;  // Starting sampler register available to pixel shaders.
    DWORD   PixelShaderSamplerRegisterCount;  // Number of sampler registers available to pixel shaders.
    DWORD   VertexShaderSamplerRegisterBase;  // Starting sampler register available to vertex shaders.
    DWORD   VertexShaderSamplerRegisterCount;  // Number of sampler registers available to vertex shaders.
    DWORD   PixelShaderInstructionCount;  // Number of instruction slots available to pixel shaders.
    DWORD   VertexShaderInstructionCount;  // Number of instruction slots available to vertex shaders.
} D3DXSHADER_COMPILE_PARAMETERSA, *LPD3DXSHADER_COMPILE_PARAMETERSA;

typedef struct _D3DXSHADER_COMPILE_PARAMETERSW
{
    // Fields use by both assembler and compiler:

    DWORD   Flags;                      // D3DXSHADEREX_* flags
    DWORD   UPDBTimestamp;              // UPDB Timestamp for this compile.
    LPWSTR  UPDBPath;                   // UPDB path for this compile.
    LPD3DXBUFFER pUPDBBuffer;           // OUT parameter, the resulting UPDB data, caller is responsible for releasing.
    DWORD   TempRegisterLimit;          // Maximum number of general registers available to the generated microcode.
    LPVOID  pUPDBB;                     // Used internally. Must be NULL.

    // Compiler-specific fields:

    LPCSTR  CpuFunctionName;            // Name to use for generated CPU shader function (NULL to use HLSL entry-point)
    BOOL    bXbox360ExtensionUsed;      // Filled in by CParse and/or the new back end. Used to avoid calling the old back end
    DWORD   PixelShaderSamplerRegisterBase;  // Starting sampler register available to pixel shaders.
    DWORD   PixelShaderSamplerRegisterCount;  // Number of sampler registers available to pixel shaders.
    DWORD   VertexShaderSamplerRegisterBase;  // Starting sampler register available to vertex shaders.
    DWORD   VertexShaderSamplerRegisterCount;  // Number of sampler registers available to vertex shaders.
    DWORD   PixelShaderInstructionCount;  // Number of instruction slots available to pixel shaders.
    DWORD   VertexShaderInstructionCount;  // Number of instruction slots available to vertex shaders.
} D3DXSHADER_COMPILE_PARAMETERSW, *LPD3DXSHADER_COMPILE_PARAMETERSW;

#ifdef UNICODE
#define D3DXSHADER_COMPILE_PARAMETERS D3DXSHADER_COMPILE_PARAMETERSW
#define LPD3DXSHADER_COMPILE_PARAMETERS LPD3DXSHADER_COMPILE_PARAMETERSW
#else
#define D3DXSHADER_COMPILE_PARAMETERS D3DXSHADER_COMPILE_PARAMETERSA
#define LPD3DXSHADER_COMPILE_PARAMETERS LPD3DXSHADER_COMPILE_PARAMETERSA
#endif

//////////////////////////////////////////////////////////////////////////////
// APIs //////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


    //----------------------------------------------------------------------------
    // D3DXAssembleShader/Ex:
    // -------------------
    // Assembles a shader.
    //
    // Parameters:
    //  pSrcFile
    //      Source file name
    //  hSrcModule
    //      Module handle. if NULL, current module will be used
    //  pSrcResource
    //      Resource name in module
    //  pSrcData
    //      Pointer to source code
    //  SrcDataLen
    //      Size of source code, in bytes
    //  pDefines
    //      Optional NULL-terminated array of preprocessor macro definitions.
    //  pInclude
    //      Optional interface pointer to use for handling #include directives.
    //      If this parameter is NULL, #includes will be honored when assembling
    //      from file, and will error when assembling from resource or memory.
    //  Flags
    //      See D3DXSHADER_xxx flags
    //  ppShader
    //      Returns a buffer containing the created shader.  This buffer contains
    //      the assembled shader code, as well as any embedded debug info.
    //  ppErrorMsgs
    //      Returns a buffer containing a listing of errors and warnings that were
    //      encountered during assembly.  If you are running in a debugger,
    //      these are the same messages you will see in your debug output.
    //----------------------------------------------------------------------------


    HRESULT WINAPI
        D3DXAssembleShaderFromFileA(
        LPCSTR                          pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

    HRESULT WINAPI
        D3DXAssembleShaderFromFileW(
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

#ifdef UNICODE
#define D3DXAssembleShaderFromFile D3DXAssembleShaderFromFileW
#else
#define D3DXAssembleShaderFromFile D3DXAssembleShaderFromFileA
#endif


    HRESULT WINAPI
        D3DXAssembleShader(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

    // Ex version:

    HRESULT WINAPI
        D3DXAssembleShaderFromFileExA(
        LPCSTR                          pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters);

    HRESULT WINAPI
        D3DXAssembleShaderFromFileExW(
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters);

#ifdef UNICODE
#define D3DXAssembleShaderFromFileEx D3DXAssembleShaderFromFileExW
#else
#define D3DXAssembleShaderFromFileEx D3DXAssembleShaderFromFileExA
#endif


    HRESULT WINAPI
        D3DXAssembleShaderExA(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters);


    HRESULT WINAPI
        D3DXAssembleShaderExW(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters);

#ifdef UNICODE
#define D3DXAssembleShaderEx D3DXAssembleShaderExW
#else
#define D3DXAssembleShaderEx D3DXAssembleShaderExA
#endif


    //----------------------------------------------------------------------------
    // D3DXCompileShader/Ex:
    // ------------------
    // Compiles a shader.
    //
    // Parameters:
    //  pSrcFile
    //      Source file name.
    //  hSrcModule
    //      Module handle. if NULL, current module will be used.
    //  pSrcResource
    //      Resource name in module.
    //  pSrcData
    //      Pointer to source code.
    //  SrcDataLen
    //      Size of source code, in bytes.
    //  pDefines
    //      Optional NULL-terminated array of preprocessor macro definitions.
    //  pInclude
    //      Optional interface pointer to use for handling #include directives.
    //      If this parameter is NULL, #includes will be honored when compiling
    //      from file, and will error when compiling from resource or memory.
    //  pFunctionName
    //      Name of the entrypoint function where execution should begin.
    //  pProfile
    //      Instruction set to be used when generating code.  Currently supported
    //      profiles are "vs_3_0", "ps_3_0", and "tx_1_0". For backwards compatibility
    //      any profile starting with "vs" will automatically be promoted to "vs_3_0", and
    //      any profile starting with "ps" will automatically be promoted to "ps_3_0".
    //      
    //      
    //  Flags
    //      See D3DXSHADER_xxx flags.
    //  ppShader
    //      Returns a buffer containing the created shader.  This buffer contains
    //      the compiled shader code, as well as any embedded debug and symbol
    //      table info.  (See D3DXGetShaderConstantTable)
    //  ppErrorMsgs
    //      Returns a buffer containing a listing of errors and warnings that were
    //      encountered during the compile.  If you are running in a debugger,
    //      these are the same messages you will see in your debug output.
    //  ppConstantTable
    //      Returns a ID3DXConstantTable object which can be used to set
    //      shader constants to the device.  Alternatively, an application can
    //      parse the D3DXSHADER_CONSTANTTABLE block embedded as a comment within
    //      the shader.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXCompileShaderFromFileA(
        LPCSTR                          pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable);

    HRESULT WINAPI
        D3DXCompileShaderFromFileW(
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable);

#ifdef UNICODE
#define D3DXCompileShaderFromFile D3DXCompileShaderFromFileW
#else
#define D3DXCompileShaderFromFile D3DXCompileShaderFromFileA
#endif


    HRESULT WINAPI
        D3DXCompileShader(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable);



    HRESULT WINAPI
        D3DXCompileShaderFromFileExA(
        LPCSTR                          pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable,
        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters);

    HRESULT WINAPI
        D3DXCompileShaderFromFileExW(
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable,
        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters);

#ifdef UNICODE
#define D3DXCompileShaderFromFileEx D3DXCompileShaderFromFileExW
#else
#define D3DXCompileShaderFromFileEx D3DXCompileShaderFromFileExA
#endif


    HRESULT WINAPI
        D3DXCompileShaderExA(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable,
        LPD3DXSHADER_COMPILE_PARAMETERSA pParameters);

    HRESULT WINAPI
        D3DXCompileShaderExW(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pFunctionName,
        LPCSTR                          pProfile,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs,
        LPD3DXCONSTANTTABLE*            ppConstantTable,
        LPD3DXSHADER_COMPILE_PARAMETERSW pParameters);

#ifdef UNICODE
#define D3DXCompileShaderEx D3DXCompileShaderExW
#else
#define D3DXCompileShaderEx D3DXCompileShaderExA
#endif

    //----------------------------------------------------------------------------
    // D3DXDisassembleShader:
    // ----------------------
    // Takes a binary shader, and returns a buffer containing text assembly.
    //
    // Parameters:
    //  pShader
    //      Pointer to the shader byte code.
    //  ShaderSizeInBytes
    //      Size of the shader byte code in bytes.
    //  EnableColorCode
    //      Emit HTML tags for color coding the output?
    //  pComments
    //      Pointer to a comment string to include at the top of the shader.
    //  ppDisassembly
    //      Returns a buffer containing the disassembled shader.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXDisassembleShader(
        CONST DWORD*                    pShader,
        BOOL                            EnableColorCode,
        LPCSTR                          pComments,
        LPD3DXBUFFER*                   ppDisassembly);

    //----------------------------------------------------------------------------
    // D3DXDisassembleShaderEx:
    // ----------------------
    // Takes a binary shader, and returns a buffer containing text assembly.
    //
    // Parameters:
    //  pShader
    //      Pointer to the shader byte code.
    //  ShaderSizeInBytes
    //      Size of the shader byte code in bytes.
    //  Flags
    //      combination of D3DXDISASSEMBLER flags controlling output format.
    //  pComments
    //      Pointer to a comment string to include at the top of the shader.
    //  ppDisassembly
    //      Returns a buffer containing the disassembled shader.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXDisassembleShaderEx(
        CONST DWORD*                    pShader,
        DWORD                           Flags,
        LPCSTR                          pComments,
        LPD3DXBUFFER*                   ppDisassembly);

    //----------------------------------------------------------------------------
    // D3DXGetPixelShaderProfile/D3DXGetVertexShaderProfile:
    // -----------------------------------------------------
    // Returns the name of the HLSL profile best suited to a given device.
    //
    // Parameters:
    //  pDevice
    //      Pointer to the device in question
    //----------------------------------------------------------------------------

    LPCSTR WINAPI
        D3DXGetPixelShaderProfile(
        LPDIRECT3DDEVICE9               pDevice);

    LPCSTR WINAPI
        D3DXGetVertexShaderProfile(
        LPDIRECT3DDEVICE9               pDevice);


    //----------------------------------------------------------------------------
    // D3DXFindShaderComment:
    // ----------------------
    // Searches through a shader for a particular comment, denoted by a FourCC in
    // the first DWORD of the comment.  If the comment is not found, and no other
    // error has occurred, S_FALSE is returned.
    //
    // Parameters:
    //  pFunction
    //      Pointer to the function DWORD stream
    //  FourCC
    //      FourCC used to identify the desired comment block.
    //  ppData
    //      Returns a pointer to the comment data (not including comment token
    //      and FourCC).  Can be NULL.
    //  pSizeInBytes
    //      Returns the size of the comment data in bytes.  Can be NULL.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXFindShaderComment(
        CONST DWORD*                    pFunction,
        DWORD                           FourCC,
        LPCVOID*                        ppData,
        UINT*                           pSizeInBytes);


    //----------------------------------------------------------------------------
    // D3DXGetShaderSize:
    // ------------------
    // Returns the size of the shader byte-code, in bytes.
    //
    // Parameters:
    //  pFunction
    //      Pointer to the function DWORD stream
    //----------------------------------------------------------------------------

    UINT WINAPI
        D3DXGetShaderSize(
        CONST DWORD*                    pFunction);

    //----------------------------------------------------------------------------
    // D3DXGetShaderVersion:
    // -----------------------
    // Returns the shader version of a given shader.  Returns zero if the shader
    // function is NULL.
    //
    // Parameters:
    //  pFunction
    //      Pointer to the function DWORD stream
    //----------------------------------------------------------------------------

    DWORD WINAPI
        D3DXGetShaderVersion(
        CONST DWORD*                    pFunction);


    //----------------------------------------------------------------------------
    // D3DXGetShaderSemantics:
    // -----------------------
    // Gets semantics for all input elements referenced inside a given shader.
    //
    // Parameters:
    //  pFunction
    //      Pointer to the function DWORD stream
    //  pSemantics
    //      Pointer to an array of D3DXSEMANTIC structures.  The function will
    //      fill this array with the semantics for each input element referenced
    //      inside the shader.  This array is assumed to contain at least
    //      MAXD3DDECLLENGTH elements.
    //  pCount
    //      Returns the number of elements referenced by the shader
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXGetShaderInputSemantics(
        CONST DWORD*                    pFunction,
        D3DXSEMANTIC*                   pSemantics,
        UINT*                           pCount);

    HRESULT WINAPI
        D3DXGetShaderOutputSemantics(
        CONST DWORD*                    pFunction,
        D3DXSEMANTIC*                   pSemantics,
        UINT*                           pCount);


    //----------------------------------------------------------------------------
    // D3DXGetShaderSamplers:
    // ----------------------
    // Gets semantics for all input elements referenced inside a given shader.
    //
    // pFunction
    //      Pointer to the function DWORD stream
    // pSamplers
    //      Pointer to an array of LPCSTRs.  The function will fill this array
    //      with pointers to the sampler names contained within pFunction, for
    //      each sampler referenced inside the shader.  This array is assumed to
    //      contain at least 16 elements.
    // pCount
    //      Returns the number of samplers referenced by the shader
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXGetShaderSamplers(
        CONST DWORD*                    pFunction,
        LPCSTR*                         pSamplers,
        UINT*                           pCount);


    //----------------------------------------------------------------------------
    // D3DXGetShaderConstantTable:
    // ---------------------------
    // Gets shader constant table embedded inside shader.  A constant table is
    // generated by D3DXAssembleShader and D3DXCompileShader, and is embedded in
    // the body of the shader.
    //
    // Parameters:
    //  pFunction
    //      Pointer to the function DWORD stream
    //  ppConstantTable
    //      Returns a ID3DXConstantTable object which can be used to set
    //      shader constants to the device.  Alternatively, an application can
    //      parse the D3DXSHADER_CONSTANTTABLE block embedded as a comment within
    //      the shader.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXGetShaderConstantTable(
        CONST DWORD*                    pFunction,
        LPD3DXCONSTANTTABLE*            ppConstantTable);


    //----------------------------------------------------------------------------
    // D3DXGatherFragments:
    // -------------------
    // Assembles shader fragments into a buffer to be passed to a fragment linker.
    //   will generate shader fragments for all fragments in the file
    //
    // Parameters:
    //  pSrcFile
    //      Source file name
    //  hSrcModule
    //      Module handle. if NULL, current module will be used
    //  pSrcResource
    //      Resource name in module
    //  pSrcData
    //      Pointer to source code
    //  SrcDataLen
    //      Size of source code, in bytes
    //  pDefines
    //      Optional NULL-terminated array of preprocessor macro definitions.
    //  pInclude
    //      Optional interface pointer to use for handling #include directives.
    //      If this parameter is NULL, #includes will be honored when assembling
    //      from file, and will error when assembling from resource or memory.
    //  Flags
    //      See D3DXSHADER_xxx flags
    //  ppShader
    //      Returns a buffer containing the created shader fragments.  This buffer contains
    //      the assembled shader code, as well as any embedded debug info.
    //  ppErrorMsgs
    //      Returns a buffer containing a listing of errors and warnings that were
    //      encountered during assembly.  If you are running in a debugger,
    //      these are the same messages you will see in your debug output.
    //----------------------------------------------------------------------------


    HRESULT WINAPI
        D3DXGatherFragmentsFromFileA(
        LPCSTR                          pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

    HRESULT WINAPI
        D3DXGatherFragmentsFromFileW(
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

#ifdef UNICODE
#define D3DXGatherFragmentsFromFile D3DXGatherFragmentsFromFileW
#else
#define D3DXGatherFragmentsFromFile D3DXGatherFragmentsFromFileA
#endif


    HRESULT WINAPI
        D3DXGatherFragments(
        LPCSTR                          pSrcData,
        UINT                            SrcDataLen,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        DWORD                           Flags,
        LPD3DXBUFFER*                   ppShader,
        LPD3DXBUFFER*                   ppErrorMsgs);

    typedef ID3DXFragmentLinker *LPD3DXFRAGMENTLINKER;


    //----------------------------------------------------------------------------
    // D3DXCreateFragmentLinker:
    // -------------------------
    // Creates a fragment linker with a given cache size.  The interface returned
    // can be used to link together shader fragments.  (both HLSL & ASM fragements)
    //
    // Parameters:
    //  pDevice
    //      Pointer to the device on which to create the shaders
    //  ShaderCacheSize
    //      Size of the shader cache
    //  ppFragmentLinker
    //      pointer to a memory location to put the created interface pointer
    //
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXCreateFragmentLinker(
        LPDIRECT3DDEVICE9               pDevice,
        UINT                            ShaderCacheSize,
        LPD3DXFRAGMENTLINKER*           ppFragmentLinker);


    //----------------------------------------------------------------------------
    // D3DXPreprocessShader:
    // ---------------------
    // Runs the preprocessor on the specified shader or effect, but does
    // not actually compile it.  This is useful for evaluating the #includes
    // and #defines in a shader and then emitting a reformatted token stream
    // for debugging purposes or for generating a self-contained shader.
    //
    // Parameters:
    //  pSrcFile
    //      Source file name
    //  hSrcModule
    //      Module handle. if NULL, current module will be used
    //  pSrcResource
    //      Resource name in module
    //  pSrcData
    //      Pointer to source code
    //  SrcDataLen
    //      Size of source code, in bytes
    //  pDefines
    //      Optional NULL-terminated array of preprocessor macro definitions.
    //  pInclude
    //      Optional interface pointer to use for handling #include directives.
    //      If this parameter is NULL, #includes will be honored when assembling
    //      from file, and will error when assembling from resource or memory.
    //  ppShaderText
    //      Returns a buffer containing a single large string that represents
    //      the resulting formatted token stream
    //  ppErrorMsgs
    //      Returns a buffer containing a listing of errors and warnings that were
    //      encountered during assembly.  If you are running in a debugger,
    //      these are the same messages you will see in your debug output.
    //----------------------------------------------------------------------------

    HRESULT WINAPI 
        D3DXPreprocessShaderFromFileA(
        LPCSTR                       pSrcFile,
        CONST D3DXMACRO*             pDefines,
        LPD3DXINCLUDE                pInclude,
        LPD3DXBUFFER*                ppShaderText,
        LPD3DXBUFFER*                ppErrorMsgs);

    HRESULT WINAPI 
        D3DXPreprocessShaderFromFileW(
        LPCWSTR                      pSrcFile,
        CONST D3DXMACRO*             pDefines,
        LPD3DXINCLUDE                pInclude,
        LPD3DXBUFFER*                ppShaderText,
        LPD3DXBUFFER*                ppErrorMsgs);

#ifdef UNICODE
#define D3DXPreprocessShaderFromFile D3DXPreprocessShaderFromFileW
#else
#define D3DXPreprocessShaderFromFile D3DXPreprocessShaderFromFileA
#endif

#ifndef _XBOX

    HRESULT WINAPI 
        D3DXPreprocessShaderFromResourceA(
        HMODULE                      hSrcModule,
        LPCSTR                       pSrcResource,
        CONST D3DXMACRO*             pDefines,
        LPD3DXINCLUDE                pInclude,
        LPD3DXBUFFER*                ppShaderText,
        LPD3DXBUFFER*                ppErrorMsgs);

    HRESULT WINAPI 
        D3DXPreprocessShaderFromResourceW(
        HMODULE                      hSrcModule,
        LPCWSTR                      pSrcResource,
        CONST D3DXMACRO*             pDefines,
        LPD3DXINCLUDE                pInclude,
        LPD3DXBUFFER*                ppShaderText,
        LPD3DXBUFFER*                ppErrorMsgs);

#ifdef UNICODE
#define D3DXPreprocessShaderFromResource D3DXPreprocessShaderFromResourceW
#else
#define D3DXPreprocessShaderFromResource D3DXPreprocessShaderFromResourceA
#endif

#endif

    HRESULT WINAPI 
        D3DXPreprocessShader(
        LPCSTR                       pSrcData,
        UINT                         SrcDataSize,
        CONST D3DXMACRO*             pDefines,
        LPD3DXINCLUDE                pInclude,
        LPD3DXBUFFER*                ppShaderText,
        LPD3DXBUFFER*                ppErrorMsgs);

    // begin internal
    //----------------------------------------------------------------------------
    // D3DXGetTargetDesc:
    // ------------------
    // Functions to lookup and describe various shader target versions.
    //----------------------------------------------------------------------------

    HRESULT WINAPI
        D3DXGetTargetDescByName(
        LPCSTR                          pName,
        DWORD                           API,
        D3DXTARGET_DESC*                pTargetDesc);

    HRESULT WINAPI
        D3DXGetTargetDescByVersion(
        DWORD                           Version,
        DWORD                           API,
        D3DXTARGET_DESC*                pDesc);
    // end internal


#ifdef __cplusplus
}
#endif //__cplusplus


//////////////////////////////////////////////////////////////////////////////
// Shader comment block layouts //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// D3DXSHADER_CONSTANTTABLE:
// -------------------------
// Shader constant information; included as an CTAB comment block inside
// shaders.  All offsets are BYTE offsets from start of CONSTANTTABLE struct.
// Entries in the table are sorted by Name in ascending order.
//----------------------------------------------------------------------------

typedef struct _D3DXSHADER_CONSTANTTABLE
{
    DWORD Size;             // sizeof(D3DXSHADER_CONSTANTTABLE)
    DWORD Creator;          // LPCSTR offset
    DWORD Version;          // shader version
    DWORD Constants;        // number of constants
    DWORD ConstantInfo;     // D3DXSHADER_CONSTANTINFO[Constants] offset
    DWORD Flags;            // flags shader was compiled with
    DWORD Target;           // LPCSTR offset

} D3DXSHADER_CONSTANTTABLE, *LPD3DXSHADER_CONSTANTTABLE;

// begin internal
#define CONSTANTINFOFLAG_STATIC  0x1
#define CONSTANTINFOFLAG_USEROFFSET             0x2
#define CONSTANTINFOFLAG_USEROFFSETSHIFT         2
// end internal

typedef struct _D3DXSHADER_CONSTANTINFO
{
    DWORD Name;             // LPCSTR offset
    WORD  RegisterSet;      // D3DXREGISTER_SET
    WORD  RegisterIndex;    // register number
    WORD  RegisterCount;    // number of registers
    WORD  Flags;            // Fragment linker flags (internal field. this field is also known as Reserved).
    DWORD TypeInfo;         // D3DXSHADER_TYPEINFO offset
    DWORD DefaultValue;     // offset of default value

} D3DXSHADER_CONSTANTINFO, *LPD3DXSHADER_CONSTANTINFO;


typedef struct _D3DXSHADER_TYPEINFO
{
    WORD  Class;            // D3DXPARAMETER_CLASS
    WORD  Type;             // D3DXPARAMETER_TYPE
    WORD  Rows;             // number of rows (matrices)
    WORD  Columns;          // number of columns (vectors and matrices)
    WORD  Elements;         // array dimension
    WORD  StructMembers;    // number of struct members
    DWORD StructMemberInfo; // D3DXSHADER_STRUCTMEMBERINFO[Members] offset

} D3DXSHADER_TYPEINFO, *LPD3DXSHADER_TYPEINFO;


typedef struct _D3DXSHADER_STRUCTMEMBERINFO
{
    DWORD Name;             // LPCSTR offset
    DWORD TypeInfo;         // D3DXSHADER_TYPEINFO offset

} D3DXSHADER_STRUCTMEMBERINFO, *LPD3DXSHADER_STRUCTMEMBERINFO;



// begin internal

//----------------------------------------------------------------------------
// D3DXGetShaderDebugInfo:
// -----------------------
// Gets shader debug info.  Debug info is generated D3DXAssembleShader and
// D3DXCompileShader and is embedded the body of the shader.
//
// Parameters:
//  pFunction
//      Pointer to the function DWORD stream
//  ppDebugInfo
//      Buffer used to return debug info.  For information about the layout
//      of this buffer, see definition of D3DXSHADER_DEBUGINFO above.
//----------------------------------------------------------------------------

HRESULT WINAPI
D3DXGetShaderDebugInfo(
                       CONST DWORD*                    pFunction,
                       LPD3DXBUFFER*                   ppDebugInfo);

//----------------------------------------------------------------------------
// D3DXSHADER_DEBUGINFO:
// ---------------------
// Shader debug information; included as an DBUG comment block inside shaders.
// All offsets are BYTE offsets from start of DEBUGINFO struct.
//----------------------------------------------------------------------------

typedef struct _D3DXSHADER_DEBUGINFO
{
    DWORD Size;             // sizeof(D3DXSHADER_DEBUGINFO)
    DWORD Creator;          // LPCSTR offset
    DWORD SourceCode;       // LPCSTR offset
    DWORD Files;            // number of source files
    DWORD FileInfo;         // D3DXSHADER_FILEINFO[Files] offset
    DWORD Instructions;     // number of instructions
    DWORD InstructionInfo;  // D3DXSHADER_INSTRUCTIONINFO[Instructions] offset
    DWORD Variables;        // number of variables
    DWORD VariableInfo;     // D3DXSHADER_VARIABLEINFO[Variables] offset
    DWORD EntrypointName;   // LPCSTR offset

} D3DXSHADER_DEBUGINFO, *LPD3DXSHADER_DEBUGINFO;


typedef struct _D3DXSHADER_FILEINFO
{
    DWORD Name;             // LPCSTR offset

} D3DXSHADER_FILEINFO, *LPD3DXSHADER_FILEINFO;


typedef struct _D3DXSHADER_INSTRUCTIONINFO
{
    WORD  Line;             // line number
    WORD  File;             // file index
    DWORD Offset;           // BYTE offset of instruction from start of shader

} D3DXSHADER_INSTRUCTIONINFO, *LPD3DXSHADER_INSTRUCTIONINFO;


typedef struct _D3DXSHADER_VARIABLEINFO
{
    DWORD Scope;            // LPCSTR scope
    DWORD Name;             // LPCSTR offset
    DWORD TypeInfo;         // D3DXSHADER_TYPEINFO offset
    DWORD Writes;           // number of writes
    DWORD WriteInfo;        // D3DXSHADER_WRITEINFO[Writes] offset

} D3DXSHADER_VARIABLEINFO, *LPD3DXSHADER_VARIABLEINFO;


typedef struct _D3DXSHADER_WRITEINFO
{
    DWORD Instruction;      // instruction index
    WORD  Component[4];     // variable component per output value

} D3DXSHADER_WRITEINFO, *LPD3DXSHADER_WRITEINFO;
// end internal

#endif //__D3DX9SHADER_H__

