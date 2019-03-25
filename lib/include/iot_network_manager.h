/*
 * Amazon FreeRTOS
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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


/**
 * @file  iot_network_manager.h
 * @brief Header file which defines APIS and network types for Network manager.
 */
#ifndef IOT_NETWORK_MANAGER_H
#define IOT_NETWORK_MANAGER_H

#include "aws_iot_network_config.h"
#include "iot_network.h"

#define IOT_NM_STATE_CHANGE_CB_INITIALIZER       ( NULL )

/**
 * @brief Default initializer for a subscription handle.
 */
#define IOT_NM_SUBSCRIPTION_INITIALIZER   { 0 }

typedef enum IotNetworkType
{
    IOT_NETWORK_TYPE__NONE     = 0,
    IOT_NETWORK_TYPE__ETHERNET = 1,
    IOT_NETWORK_TYPE__WIFI     = 2,
    IOT_NETWORK_TYPE__BLE      = 4,
    IOT_NETWORK_TYPE__802_15_4 = 8,
    IOT_NETWORK_TYPE__CELLULAR = 16
} IotNetworkType_t;

/**
 * @brief States defined for the network types.
 */
typedef enum IotNetworkState

{
    IOT_NETWORK_STATE_DISABLED,       //!< IOT_NETWORK_STATE_DISABLED State of the network is disabled, potentially off.
    IOT_NETWORK_STATE_DISCONNECTED,   //!< IOT_NETWORK_STATE_DISCONNECTED State of the network is idle and disconnected. Stack is initialized and
                                      //!< now connections can be established to and from the device.
    IOT_NETWORK_STATE_CONNECTED,      //!< IOT_NETWORK_STATE_CONNECTED State of the network is connected.
    IOT_NETWORK_STATE_PROVISIONED     //!< IOT_NETWORK_STATE_PROVISIONED A new configuration has been provisioned, e.g. a new set of credentials.

} IotNetworkState_t;


typedef enum IotNetworkManagerError
{
   IOT_NM_SUCCESS = 0,
   IOT_NM_INVALID,
   IOT_NM_NOT_SUPPORTED,
   IOT_NM_NO_MEMORY,
   IOT_NM_INIT_FAILED,
   IOT_NM_INVALID_CREDENTIALS,

} IotNetworkManagerError_t ;

/**
 *  @brief Unique handle for a subscription.
 */
struct NetworkManagerSubscription_t;


/**
 * @brief Callback used for passing state change events from network manager to the application.
 * Application can register callback of this type with the network manager for one or more network types.
 *
 * @param[in] xNetworkType Type of the network for which the callback is invoked
 * @param[in] xNetworkState State of the network
 * @param[in] pvContext Application context passed in for the callback at the time of subscription.
 */
typedef void ( *IotNetworkStateChangeCb_t ) ( IotNetworkType_t xNetworkType, IotNetworkState_t xNetworkState, void* pvContext );


/**
 * @brief Registers the state change callback with the network types provided.
 * Application can register callback per network type or a single callback for multiple network types.
 *
 * @param xNetworkTypes Represents a combination of one or more network types for which the callback needs to be invoked.
 * @param xCallback User implemented network state change callback.
 * @param pvContext Context parameter passed in to the state change callback invocation.
 * @param pxHandle  Unique handle to the subscription.
 * @return IOT_NM_SUCCESS on success or the error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_SubscribeForStateChange( IotNetworkType_t xNetworkTypes,
                                                         IotNetworkStateChangeCb_t xCallback,
                                                         void * pvContext,
                                                         struct NetworkManagerSubscription_t* pxSubscription );


/**
 * @brief Removes a subscription
 * @param[in] pxSubscription Pointer to the subscription
 * @return IOT_NM_SUCCESS on success or the error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_RemoveSubscription( struct NetworkManagerSubscription_t* pxSubscription );


/***
 * @brief Retrieves a mask that lists the available networks on the device.
 *
 * @param[out] Mask of all network types supported by the device.
 * @return IOT_NM_SUCCESS on success or specific error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_GetAvailableNetworks( IotNetworkType_t* networkTypes );

/**
 * @brief Gets the network state for a network type
 *
 * @param[in] Type of the network.
 * @param[out] state State of the network.
 * @return IOT_NM_SUCCESS on success or specific error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_GetNetworkState( IotNetworkType_t networkType, IotNetworkState_t * state );

/**
 * @brief Enables the given list of network types.
 *
 * @param[in] networkTypes Mask representing the given list of network types.
 * @return IOT_NM_SUCCESS on success or specific error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_EnableNetwork( IotNetworkType_t networkTypes );

/**
 * @brief Disables the given list of network types.
 *
 * @param[in] networkTypes Mask representing the given list of network types.
 * @return IOT_NM_SUCCESS on success or specific error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_DisableNetwork( IotNetworkType_t networkTypes );

/**
 * @brief Retrieves the network interface for one specific network.
 *
 * @param[in] networkType The type of the network.
 * @return Pointer to the network interface.
 */
const IotNetworkInterface_t * IotNetworkManager_GetNetworkInterface( IotNetworkType_t networkType );

/**
 * @brief Retrieves the endpoint information for one specified network.
 *
 * @param[in] networkType The type of the network.
 * @return A generic pointer to the endpoint information.
 */
const void * IotNetworkManager_GetEndpoint( IotNetworkType_t networkType );

/**
 * @brief Retrieves the credentials for one specific network.
 *
 * @param[in] networkType The type of the network.
 * @return A generic pointer to the credentials.
 */
const void * IotNetworkManager_GetCredentials( IotNetworkType_t networkType );

/**
 * @brief Function invoked by underlying network driver to notify a state change for a network.
 * @param networkType Type of the network.
 * @param state The new state for the network.
 * @return IOT_NM_SUCCESS on success or specific error type on failure.
 */
IotNetworkManagerError_t IotNetworkManager_NotifyStateChange( IotNetworkType_t networkType, IotNetworkState_t state );

#endif /* IOT_NETWORK_MANAGER_H */
