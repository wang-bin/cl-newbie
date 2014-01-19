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

void platform_info(cl_platform_id id)
{
    printf("platform id: %p\n", id);
    struct {
        cl_platform_info info;
        const char* name;
    } platform_infos[] = {
    { CL_PLATFORM_PROFILE, "CL_PLATFORM_PROFILE" },
    { CL_PLATFORM_VERSION, "CL_PLATFORM_VERSION" },
    { CL_PLATFORM_NAME, "CL_PLATFORM_NAME" },
    { CL_PLATFORM_VENDOR, "CL_PLATFORM_VENDOR" },
    { CL_PLATFORM_EXTENSIONS, "CL_PLATFORM_EXTENSIONS" },
    { 0, 0 }
    };
    const int kValueSize = 4096; //extensions maybe very long
    for (int i = 0; platform_infos[i].name; ++i) {
        char value[kValueSize];
        size_t ret_size;
        cl_int ret = clGetPlatformInfo(id, platform_infos[i].info, kValueSize, value, &ret_size);
        if (ret != CL_SUCCESS) {
            fprintf(stderr, "clGetPlatformInfo %s error (%#x)\n", platform_infos[i].name, ret);
            //return ret;
        }
        value[ret_size] = 0;
        printf("%s: %s\n", platform_infos[i].name, value);
    }
}

void device_info(cl_device_id id)
{
    printf("device id: %p\n", id);
    struct {
        cl_device_info info;
        const char* name;
    } device_infos[] = {
    //{ CL_DEVICE_ADDRESS_BITS, "CL_DEVICE_ADDRESS_BITS" },
    //{ CL_DEVICE_AVAILABLE, "CL_DEVICE_AVAILABLE" }, //bool
    //{ CL_DEVICE_COMPILER_AVAILABLE, "CL_DEVICE_COMPILER_AVAILABLE" }, //bool
    //{ CL_DEVICE_DOUBLE_FP_CONFIG, "CL_DEVICE_DOUBLE_FP_CONFIG" }, //cl_device_fp_config
    //{ CL_DEVICE_ENDIAN_LITTLE, "CL_DEVICE_ENDIAN_LITTLE" }, //bool
    //{ CL_DEVICE_ERROR_CORRECTION_SUPPORT, "CL_DEVICE_ERROR_CORRECTION_SUPPORT" }, //bool
    //{ CL_DEVICE_EXECUTION_CAPABILITIES, "CL_DEVICE_EXECUTION_CAPABILITIES" }, // cl_device_exec_capabilities
    { CL_DEVICE_NAME, "CL_DEVICE_NAME" },
    { CL_DEVICE_PROFILE, "CL_DEVICE_PROFILE" },
    { CL_DEVICE_VENDOR, "CL_DEVICE_VENDOR" },
    { CL_DEVICE_VERSION, "CL_DEVICE_VERSION" },
    { CL_DRIVER_VERSION, "CL_DRIVER_VERSION" },
    { CL_DEVICE_EXTENSIONS, "CL_DEVICE_EXTENSIONS" },
    { 0, 0 },
    };
    const int kValueSize = 4096;
    for (int i = 0; device_infos[i].name; ++i) {
        char value[kValueSize];
        size_t ret_size;
        cl_int ret = clGetDeviceInfo(id, device_infos[i].info, kValueSize, value, &ret_size);
        if (ret != CL_SUCCESS) {
            fprintf(stderr, "clGetDeviceInfo %s error (%#x)\n", device_infos[i].name, ret);
            //return ret;
        }
        value[ret_size] = 0;
        printf("%s: %s\n", device_infos[i].name, value);
    }
}

int main()
{
    cl_int ret = CL_SUCCESS;
    cl_uint nb_platforms;
    /*
     * num_entries: The number of cl_platform_id entries that can be added to platforms
     * If platforms is not NULL, the num_entries must be greater than zero.
     */
    clGetPlatformIDs(0 /*num_entries*/, NULL /*cl_platform_id* */, &nb_platforms);
    fprintf(stdout, "platforms count: %d\n", nb_platforms);

    cl_platform_id *platform_ids = (cl_platform_id*)calloc(nb_platforms, sizeof(cl_platform_id));
    clGetPlatformIDs(nb_platforms, platform_ids, NULL);

    for (size_t i = 0; i < nb_platforms; ++i) {
        printf("platform %d\n", i);
        platform_info(platform_ids[i]);
        struct {
            cl_device_type type;
            const char* name;
        } device_types[] = {
        { CL_DEVICE_TYPE_CPU, "CL_DEVICE_TYPE_CPU" },
        { CL_DEVICE_TYPE_GPU, "CL_DEVICE_TYPE_GPU" },
        { CL_DEVICE_TYPE_ACCELERATOR, "CL_DEVICE_TYPE_ACCELERATOR" },
        { CL_DEVICE_TYPE_DEFAULT, "CL_DEVICE_TYPE_DEFAULT" },
        { CL_DEVICE_TYPE_ALL, "CL_DEVICE_TYPE_ALL" },
        { 0, 0 }
        };
        for (int j = 0; device_types[j].name; ++j) {
            cl_uint nb_devices;
            clGetDeviceIDs(platform_ids[i], device_types[j].type, 0, NULL, &nb_devices);
            printf("%s devices: %d\n", device_types[j].name, nb_devices);
            cl_device_id *devices = (cl_device_id*)calloc(nb_devices, sizeof(cl_device_id));
            clGetDeviceIDs(platform_ids[i], device_types[j].type, nb_devices, devices, NULL);
            for (size_t k = 0; k < nb_devices; ++k) {
                device_info(devices[k]);
            }
            free(devices);
        }
    }
    free(platform_ids);
    return 0;
}
