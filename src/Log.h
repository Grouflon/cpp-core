#pragma once

#define LOG(...)			{ fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#define LOG_WARNING(...)	{ fprintf(stdout, "[WARNING] "); fprintf(stderr, __VA_ARGS__); fprintf(stdout, "\n"); }
#define LOG_ERROR(...)		{ fprintf(stderr, "[ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); }