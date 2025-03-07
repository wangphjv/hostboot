# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/usr/diag/prdf/common/plat/axone/prdf_plat_axone.mk $
#
# OpenPOWER HostBoot Project
#
# Contributors Listed Below - COPYRIGHT 2016,2019
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

# NOTE: PRD_SRC_PATH must be defined before including this file.

################################################################################
# Paths common to both FSP and Hostboot
################################################################################

prd_vpath += ${PRD_SRC_PATH}/common/plat/axone

prd_incpath += ${PRD_SRC_PATH}/common/plat/axone

################################################################################
# Object files common to both FSP and Hostboot
################################################################################

# plat/axone/ (rule plugin related)
prd_rule_plugin += prdfOmicPlugins.o

