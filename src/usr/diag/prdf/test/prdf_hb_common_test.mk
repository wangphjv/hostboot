# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/usr/diag/prdf/test/prdf_hb_common_test.mk $
#
# OpenPOWER HostBoot Project
#
# Contributors Listed Below - COPYRIGHT 2012,2019
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

#------------------------------------------------------------------------------
# paths
#------------------------------------------------------------------------------
PRD_USR_PATH = ${ROOTPATH}/src/usr/diag/prdf
PRD_USR_TEST_PATH = ${ROOTPATH}/src/usr/diag/prdf/test
PRD_INC_PATH = ${ROOTPATH}/src/include/usr/diag/prdf

EXTRAINCDIR += ${PRD_INC_PATH}
EXTRAINCDIR += ${PRD_INC_PATH}/common

EXTRAINCDIR += ${PRD_USR_PATH}
EXTRAINCDIR += ${PRD_USR_PATH}/common
EXTRAINCDIR += ${PRD_USR_PATH}/common/plugins
EXTRAINCDIR += ${PRD_USR_PATH}/common/util
EXTRAINCDIR += ${PRD_USR_PATH}/common/framework/service
EXTRAINCDIR += ${PRD_USR_PATH}/common/framework/register
EXTRAINCDIR += ${PRD_USR_PATH}/common/framework/resolution
EXTRAINCDIR += ${PRD_USR_PATH}/common/framework/config
EXTRAINCDIR += ${PRD_USR_PATH}/common/rule
EXTRAINCDIR += ${PRD_USR_PATH}/common/plat
EXTRAINCDIR += ${PRD_USR_PATH}/common/plat/cen
EXTRAINCDIR += ${PRD_USR_PATH}/common/plat/mem
EXTRAINCDIR += ${PRD_USR_PATH}/common/plat/p9
EXTRAINCDIR += ${PRD_USR_PATH}/common/mnfgtools
EXTRAINCDIR += ${PRD_USR_PATH}/mnfgtools
EXTRAINCDIR += ${PRD_USR_PATH}/framework
EXTRAINCDIR += ${PRD_USR_PATH}/occ_firdata
EXTRAINCDIR += ${PRD_USR_PATH}/plat
EXTRAINCDIR += ${PRD_USR_PATH}/plat/cen
EXTRAINCDIR += ${PRD_USR_PATH}/plat/mem
EXTRAINCDIR += ${PRD_USR_PATH}/plat/p9
EXTRAINCDIR += ${PRD_USR_PATH}/test

EXTRAINCDIR += ${ROOTPATH}/src/include/usr/ecmddatabuffer
EXTRAINCDIR += ${ROOTPATH}/src/include/usr/errl
EXTRAINCDIR += ${ROOTPATH}/src/include/usr/fapi2
EXTRAINCDIR += ${ROOTPATH}/src/include/usr/util
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/centaur/common/include
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/centaur/procedures/hwp/memory
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/centaur/procedures/hwp/memory/lib/shared
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/common/include/
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/procedures/hwp/ffdc/
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/procedures/hwp/memory
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/procedures/hwp/cache/
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/procedures/hwp/pm/
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/procedures/hwp/lib/
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/p9/utils/imageProcs
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/common/utils
EXTRAINCDIR += ${ROOTPATH}/src/import/chips/common/utils/imageProcs
EXTRAINCDIR += ${ROOTPATH}/src/import/hwpf/fapi2/include
EXTRAINCDIR += ${ROOTPATH}/src/import/

#------------------------------------------------------------------------------
# objects
#------------------------------------------------------------------------------

OBJS += prdfsimHomRegisterAccess.o
OBJS += prdfsimRasServices.o
OBJS += prdfsimScrDataSet.o
OBJS += prdfsimScrDB.o
OBJS += prdfsimServices.o
OBJS += prdsimSignatureParser.o
OBJS += prdfsimUtil.o

TESTS += ${PRD_USR_TEST_PATH}/prdfTest_Proc.H
TESTS += ${PRD_USR_TEST_PATH}/prdfTest.H
TESTS += ${PRD_USR_TEST_PATH}/prdfTest_XBus.H
TESTS += ${PRD_USR_TEST_PATH}/prdfTest_ABus.H
TESTS += ${PRD_USR_TEST_PATH}/prdfTest_ProcCentFir.H
TESTS += ${PRD_USR_TEST_PATH}/prdfTest_Ex.H
TESTS += $(if $(CONFIG_AXONE_BRING_UP),,${PRD_USR_TEST_PATH}/prdfTest_NimbusTpLFir.H)
#@TODO RTC:178802
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_Mcs.H


# Wait for PLL code and Ben
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_ProcTpLFir.H

#TODO RTC 167288 - Once Cumulus/Centaur are ready we update these
# Need Centaurs for this (CUMULUS processor chip)
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_CentCs.H
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_Mba.H
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_ProcMbsFir.H
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_CenTpLFir.H
#TESTS += ${PRD_USR_TEST_PATH}/prdfTest_McsMciFir.H


