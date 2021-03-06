﻿#ifndef __READWRITELOCK_H__
#define __READWRITELOCK_H__

#include "VarStr.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
//Func项目的DLL动态库文件导入导出符号宏。
#if( defined __NAME_FUNC__ ) //如果正在编译Func项目。
	#if( ( defined __MS_VCXX__ ) ) //如果正在使用MS VC++编译器。
		#if( defined __COMLIB__ ) //如果正在编译LIB静态库文件。
			#define __FUNC_DLLAPI__
		#elif( defined __COMDLL__ ) //如果正在编译DLL动态库文件。
			#define __FUNC_DLLAPI__ __declspec( dllexport )
		#elif( defined __COMEXE__ ) //如果正在编译EXE可执行文件。
			#define __FUNC_DLLAPI__
		#endif
	#elif( ( defined __LINUX_GCC__ ) || ( defined __CYGWIN_GCC__ ) || ( defined __ANDROID_GCC__ ) || ( defined __KEIL_ARMC__ ) ) //如果正在使用Cygwin GCC/G++、Linux GCC/G++、Android GCC/G++、KEIL ARMCLANG/ARMCC编译器。
		#if( defined __COMLIB__ ) //如果正在编译LIB静态库文件。
			#define __FUNC_DLLAPI__
		#elif( defined __COMDLL__ ) //如果正在编译DLL动态库文件。
			#define __FUNC_DLLAPI__ __attribute__( ( visibility( "default" ) ) )
		#elif( defined __COMEXE__ ) //如果正在编译EXE可执行文件。
			#define __FUNC_DLLAPI__
		#endif
	#else //如果正在使用未知编译器。
		#define __FUNC_DLLAPI__
	#endif
#else //如果正在编译其他项目。
	#if( ( defined __MS_VCXX__ ) ) //如果正在使用MS VC++编译器。
		#if( defined __LNKLIB__ ) //如果正在链接LIB静态库文件。
			#define __FUNC_DLLAPI__
		#elif( defined __LNKDLL__ ) //如果正在链接DLL动态库文件。
			#define __FUNC_DLLAPI__ __declspec( dllimport )
		#endif
	#elif( ( defined __LINUX_GCC__ ) || ( defined __CYGWIN_GCC__ ) || ( defined __ANDROID_GCC__ ) || ( defined __KEIL_ARMC__ ) ) //如果正在使用Cygwin GCC/G++、Linux GCC/G++、Android GCC/G++、KEIL ARMCLANG/ARMCC编译器。
		#define __FUNC_DLLAPI__
	#else //如果正在使用未知编译器。
		#define __FUNC_DLLAPI__
	#endif
#endif
	
//互斥锁。
#ifdef __cplusplus
}
#include <atomic>
typedef struct MutexLock
{
	std::atomic_flag m_FlagCount = ATOMIC_FLAG_INIT;
}MutexLock;
extern "C"
{
#endif
typedef struct MutexLock MutexLock;

__FUNC_DLLAPI__ int MutexLockInit( MutexLock * * MutexLockPtPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int MutexLockLock( MutexLock * MutexLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int MutexLockUnlock( MutexLock * MutexLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int MutexLockDestroy( MutexLock * MutexLockPt, VarStr * ErrInfoVarStrPt );

//读写锁。
typedef struct RWLock RWLock;

__FUNC_DLLAPI__ int RWLockInit( RWLock * * RWLockPtPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int RWLockRLock( RWLock * RWLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int RWLockRUnlock( RWLock * RWLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int RWLockWLock( RWLock * RWLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int RWLockWUnlock( RWLock * RWLockPt, VarStr * ErrInfoVarStrPt );
__FUNC_DLLAPI__ int RWLockDestroy( RWLock * RWLockPt, VarStr * ErrInfoVarStrPt );

#ifdef __cplusplus
}
#endif

#endif
