/******************************************************************************
    main.cpp: description
    Copyright (C) 2014 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    Alternatively, this file may be used under the terms of the GNU
    General Public License version 3.0 as published by the Free Software
    Foundation and appearing in the file LICENSE.GPL included in the
    packaging of this file.  Please review the following information to
    ensure the GNU General Public License version 3.0 requirements will be
    met: http://www.gnu.org/copyleft/gpl.html.
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#ifdef __APPLE__
    #include <OpenCL/cl.h>
#else
    #include <CL/cl.h>
#endif

int main(int argc, char** argv)
{
    cl_uint NumPlatforms;
    clGetPlatformIDs(0, NULL, &NumPlatforms);
    fprintf(stdout, "NumPlatforms: %d\n", NumPlatforms);

    cl_platform_id *PlatformIDs = (cl_platform_id*)calloc(NumPlatforms, sizeof(cl_platform_id));
    clGetPlatformIDs(NumPlatforms, PlatformIDs, NULL);

    char platformName[64];
    size_t nameLen;
    cl_int res = clGetPlatformInfo(PlatformIDs[0], CL_PLATFORM_NAME, 64, platformName, &nameLen);
    if (res != CL_SUCCESS) {
        fprintf(stderr, "Err @%d: %#x\n", __LINE__, res);
        return 1;
    }
    platformName[nameLen] = 0;

    char openclVersion[64];
    res = clGetPlatformInfo(PlatformIDs[0], CL_PLATFORM_VERSION, 64, openclVersion, &nameLen);
    if (res != CL_SUCCESS) {
        fprintf(stderr, "Err @%d: %#x\n", __LINE__, res);
        return 1;
    }
    openclVersion[nameLen] = 0;
    printf("hello, %s's %s\n", platformName, openclVersion);

    return 0;
}
