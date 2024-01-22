#pragma once

#include "CoreMinimal.h"

#include "Containers/UnrealString.h"

DECLARE_LOG_CATEGORY_EXTERN(Player, Log, All);


#define DEBUG_CALLINFO FString::Printf(TEXT("%s %d"), *FString(__FUNCTION__), __LINE__)

/*
#if WITH_EDITOR
	#define DEBUG_LOG(Category, Verbosity, Format) \
	{ \
		UE_LOG(Category, Verbosity, TEXT("%s %s") , Format, *DEBUG_CALLINFO) \
		if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Log) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::White, TEXT("%s %s") , Format, *DEBUG_CALLINFO) ); \
		} \
		else if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Warning) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Yellow, TEXT("%s %s") , Format, *DEBUG_CALLINFO) ); \
		} \
		else if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Error) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red, TEXT("%s %s") , Format, *DEBUG_CALLINFO) ); \
		} \
		else \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::White, TEXT("%s %s") , Format, *DEBUG_CALLINFO) ); \
		} \
	}

	#define DEBUG_LOG(Category, Verbosity, Format, ...) \
	{ \
		FString NewString = FString::Printf(Format, ##__VA_ARGS__); \
		UE_LOG(Category, Verbosity, TEXT("%s %s") , *NewString, *DEBUG_CALLINFO) \
		if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Log) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::White, FString::Printf(TEXT("%s %s"), *NewString, *DEBUG_CALLINFO) ); \
		} \
		else if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Warning) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Yellow, FString::Printf(TEXT("%s %s"), *NewString, *DEBUG_CALLINFO) ); \
		} \
		else if (::ELogVerbosity::Verbosity == ::ELogVerbosity::Error) \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red, FString::Printf(TEXT("%s %s"), *NewString, *DEBUG_CALLINFO) ); \
		} \
		else \
		{ \
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::White, FString::Printf(TEXT("%s %s"), *NewString, *DEBUG_CALLINFO) ); \
		} \
	}
#endif
*/