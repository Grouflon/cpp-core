﻿#pragma once

#define LOG(...)		fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n");
#define LOG_ERROR(...)	fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");