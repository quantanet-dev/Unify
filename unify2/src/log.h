#pragma once

#include "spdlog/spdlog.h"

#define UNIFY_LOGGER_NAME "UnifyLogger"

#define LOG_TRACE(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->trace(__VA_ARGS__);}
#define LOG_INFO(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->info(__VA_ARGS__);}
#define LOG_WARN(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->warn(__VA_ARGS__);}
#define LOG_DEBUG(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->debug(__VA_ARGS__);}
#define LOG_ERROR(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->error(__VA_ARGS__);}
#define LOG_FATAL(...)	if (spdlog::get(UNIFY_LOGGER_NAME) != NULL) {spdlog::get(UNIFY_LOGGER_NAME)->critical(__VA_ARGS__);}