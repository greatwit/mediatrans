# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

COMMON_SRC_PATH := common
NET_SRC_PATH := net
SYSTEM_SRC_PATH := system
PROTO_SRC_PATH  := hnproto

#------------------------------------------>
#include $(PREBUILT_SHARED_LIBRARY) 

include $(CLEAR_VARS)

LOCAL_MODULE    := netproto

LOCAL_C_INCLUDES += $(COMMON_SRC_PATH)
LOCAL_C_INCLUDES += $(SYSTEM_SRC_PATH)
LOCAL_C_INCLUDES += $(NET_SRC_PATH)
LOCAL_C_INCLUDES += $(PROTO_SRC_PATH)



LOCAL_SRC_FILES := 	$(COMMON_SRC_PATH)/HnMd5.c	\
											$(NET_SRC_PATH)/epoll.c \
											$(NET_SRC_PATH)/net_api.c \
										$(SYSTEM_SRC_PATH)/date_time.c \
										$(SYSTEM_SRC_PATH)/hash.c \
										$(SYSTEM_SRC_PATH)/list.c \
										$(SYSTEM_SRC_PATH)/log.c \
										$(SYSTEM_SRC_PATH)/memory.c \
										$(SYSTEM_SRC_PATH)/os_api.c \
										$(SYSTEM_SRC_PATH)/queue.c \
										$(SYSTEM_SRC_PATH)/timer.c \
										$(SYSTEM_SRC_PATH)/datacache.c \
											$(PROTO_SRC_PATH)/HNnetApi.c \
											$(PROTO_SRC_PATH)/AndroidHNnetApi.c

LOCAL_LDLIBS :=  -llog

include $(BUILD_SHARED_LIBRARY)

  
 

