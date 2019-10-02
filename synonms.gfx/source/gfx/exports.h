#pragma once
#ifndef SYNONMS_GFX_EXPORTS_H
#define SYNONMS_GFX_EXPORTS_H

#ifdef SYNONMS_GFX_EXPORTS
#define SYNONMS_GFX_API __declspec(dllexport)
#else
#define SYNONMS_GFX_API __declspec(dllimport)
#endif

#endif