# - Find BioMedicalDataIO
#
# Find the BioMedicalDataIO includes and libraries
# This module defines
#  BioMedicalDataIO_FOUND           - TRUE if found, FALSE otherwise
#  BioMedicalDataIO_INCLUDE_DIR     - Include directories for BioMedicalDataIO
#  BioMedicalDataIO_LIBRARIES       - The libraries to link against to use BioMedicalDataIO

FIND_PACKAGE(PackageHandleStandardArgs)

SET(BioMedicalDataIO_SEARCHPATH
    /usr/include/
    /usr/local/include/
    /opt/include/
    /opt/local/include/
    )

FIND_PATH(BioMedicalDataIO_INCLUDE_DIR
    NAMES biomedicaldataio.h
    PATHS ${BioMedicalDataIO_SEARCHPATH}
    DOC "The BioMedicalDataIO include directory")

FIND_LIBRARY(BioMedicalDataIO_LIBRARY
    NAMES biomedicaldataio libbiomedicaldataio
    PATHS
    /usr/lib
    /usr/local/lib
    /usr/lib64
    /usr/local/lib64
    /opt/lib
    /opt/local/lib
    /opt/lib64
    /opt/local/lib64
    DOC "The BioMedicalDataIO libraries")

FIND_LIBRARY(TIFF_LIBRARY
    NAMES tiff libtiff
    PATHS
    /usr/lib
    /usr/local/lib
    /usr/lib64
    /usr/local/lib64
    /opt/lib
    /opt/local/lib
    /opt/lib64
    /opt/local/lib64
    DOC "The TIFF libraries")

FIND_LIBRARY(NIfTI_LIBRARY
    NAMES niftiio libniftiio
    PATHS
    /usr/lib
    /usr/local/lib
    /usr/lib64
    /usr/local/lib64
    /opt/lib
    /opt/local/lib
    /opt/lib64
    /opt/local/lib64
    DOC "The NIfTI library")

FIND_LIBRARY(Z_LIBRARY
    NAMES znz libznz
    PATHS
    /usr/lib
    /usr/local/lib
    /usr/lib64
    /usr/local/lib64
    /opt/lib
    /opt/local/lib
    /opt/lib64
    /opt/local/lib64
    DOC "The Z library")

SET(NIfTI_LIBRARIES ${NIfTI_LIBRARY} ${Z_LIBRARY})
SET(BioMedicalDataIO_LIBRARIES ${BioMedicalDataIO_LIBRARY} ${TIFF_LIBRARY} ${NIfTI_LIBRARIES})

IF(BioMedicalDataIO_INCLUDE_DIR AND BioMedicalDataIO_LIBRARIES)
    SET(BioMedicalDataIO_FOUND TRUE)
ELSE(BioMedicalDataIO_INCLUDE_DIR AND BioMedicalDataIO_LIBRARIES)
    SET(BioMedicalDataIO_FOUND FALSE)
ENDIF(BioMedicalDataIO_INCLUDE_DIR AND BioMedicalDataIO_LIBRARIES)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BioMedicalDataIO REQUIRED_VARS BioMedicalDataIO_INCLUDE_DIR BioMedicalDataIO_LIBRARIES)

MARK_AS_ADVANCED( BioMedicalDataIO_INCLUDE_DIR BioMedicalDataIO_LIBRARIES )
