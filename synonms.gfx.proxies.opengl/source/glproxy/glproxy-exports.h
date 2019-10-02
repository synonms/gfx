#pragma once
#ifndef GLPROXY_EXPORTS_H
#define GLPROXY_EXPORTS_H

#ifdef GLPROXY_EXPORTS
#define GLPROXY_API __declspec(dllexport)
#else
#define GLPROXY_API __declspec(dllimport)
#endif

#endif