/*
 * Amazon FreeRTOS
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */
#ifndef _IOT_NETWORK_CONFIG_DEFAULTS_H_
#define _IOT_NETWORK_CONFIG_DEFAULTS_H_

#ifndef configSUPPORTED_NETWORKS
#error "Flag 'configSUPPORTED_NETWORKS' is not defined. Please define the flag in \
    aws_iot_network_config.h with the all the networks supported by the board."
#endif

#ifndef configENABLED_NETWORKS
#error "Flag 'configENABLED_NETWORKS' not defined. Please define the flag in      \
    aws_iot_network_config.h with all the networks that needs to be enabled."
#endif

#if defined( configENABLED_NETWORKS ) && defined( configSUPPORTED_NETWORKS )
#if ( ( configENABLED_NETWORKS | configSUPPORTED_NETWORKS ) != configSUPPORTED_NETWORKS )
#error "Enabled networks should always be a subset of supported networks"
#endif
#endif

#endif /* _IOT_NETWORK_CONFIG_DEFAULTS_H_ */
