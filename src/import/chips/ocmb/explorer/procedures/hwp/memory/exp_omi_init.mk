# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/import/chips/ocmb/explorer/procedures/hwp/memory/exp_omi_init.mk $
#
# OpenPOWER HostBoot Project
#
# Contributors Listed Below - COPYRIGHT 2018,2019
# [+] International Business Machines Corp.
#
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.
#
# IBM_PROLOG_END_TAG
# Makefile for exp_omi_init HWP
PROCEDURE=exp_omi_init
$(eval $(call ADD_EXP_MEMORY_INCDIRS,$(PROCEDURE)))
lib$(PROCEDURE)_DEPLIBS+=exp_inband
$(call ADD_MODULE_INCDIR,$(PROCEDURE),$(ROOTPATH)/chips/ocmb/explorer/common/include)
$(call ADD_MODULE_INCDIR,$(PROCEDURE),$(ROOTPATH)/chips/ocmb/explorer/common/inband)
$(call ADD_MODULE_INCDIR,$(PROCEDURE),$(ROOTPATH)/chips/p9/procedures/hwp/nest)
$(call ADD_MODULE_INCDIR,$(PROCEDURE),$(ROOTPATH)/chips/p9a/procedures/hwp/memory/lib)
$(call ADD_MODULE_INCDIR,$(PROCEDURE),$(ROOTPATH))
$(call BUILD_PROCEDURE)
