/*
 * Copyright 2012 Jared Boone
 *
 * This file is part of HackRF.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <stdint.h>
#include <stddef.h>

#include "usb_descriptor.h"
#include "usb_type.h"

#define USB_VENDOR_ID			(0x1D50)
#define USB_PRODUCT_ID			(0x604B)

#define USB_MAX_PACKET0     	(64)
#define USB_MAX_PACKET_BULK_FS	(64)
#define USB_MAX_PACKET_BULK_HS	(512)

#define USB_BULK_IN_EP_ADDR 	(0x81)
#define USB_BULK_OUT_EP_ADDR 	(0x02)

#define USB_STRING_LANGID		(0x0409)

#define DESCRIPTOR __attribute__((section(".data")))

DESCRIPTOR
const struct usb_device_descriptor usb_descriptor_device = {
	.bLength	     = USB_DT_DEVICE_SIZE,
	.bDescriptorType     = USB_DT_DEVICE,
	.bcdUSB		     = 0x0200,
	.bDeviceClass	     = 0x00,
	.bDeviceSubClass     = 0x00,
	.bDeviceProtocol     = 0x00,
	.bMaxPacketSize0     = USB_MAX_PACKET0,
	.idVendor	     = USB_VENDOR_ID,
	.idProduct	     = USB_PRODUCT_ID,
	.bcdDevice	     = 0x0100,
	.iManufacturer	     = 0x01,
	.iProduct	     = 0x02,
	.iSerialNumber	     = 0x00,
	.bNumConfigurations  = 0x01
};

DESCRIPTOR
const struct usb_device_qualifier_descriptor usb_descriptor_device_qualifier = {
	.bLength	     = 10,
	.bDescriptorType     = USB_DT_DEVICE,
	.bcdUSB		     = 0x0200,
	.bDeviceClass	     = 0x00,
	.bDeviceSubClass     = 0x00,
	.bDeviceProtocol     = 0x00,
	.bMaxPacketSize0     = 64,
	.bNumConfigurations  = 0x01,
	.bReserved	     = 0x00
};

DESCRIPTOR
const struct usb_endpoint_descriptor usb_full_speed_config1_endpoints[] = {
        { // IN
	.bLength	     = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType     = USB_DT_ENDPOINT,
	.bEndpointAddress    = USB_BULK_IN_EP_ADDR,
	.bmAttributes	     = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize	     = USB_MAX_PACKET_BULK_FS,
	.bInterval	     = 0x00
        },
        { // OUT
	.bLength	     = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType     = USB_DT_ENDPOINT,
	.bEndpointAddress    = USB_BULK_OUT_EP_ADDR,
	.bmAttributes	     = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize	     = USB_MAX_PACKET_BULK_FS,
	.bInterval	     = 0x00
        }
};

DESCRIPTOR
const struct usb_endpoint_descriptor usb_high_speed_config1_endpoints[] = {
        { // IN
	.bLength	     = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType     = USB_DT_ENDPOINT,
	.bEndpointAddress    = USB_BULK_IN_EP_ADDR,
	.bmAttributes	     = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize	     = USB_MAX_PACKET_BULK_HS,
	.bInterval	     = 0x00
        },
        { // OUT
	.bLength	     = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType     = USB_DT_ENDPOINT,
	.bEndpointAddress    = USB_BULK_OUT_EP_ADDR,
	.bmAttributes	     = USB_ENDPOINT_ATTR_BULK,
	.wMaxPacketSize	     = USB_MAX_PACKET_BULK_HS,
	.bInterval	     = 0x00
        }
};

DESCRIPTOR
const struct usb_interface_descriptor usb_configuration_full_speed_iface = {
	.bLength	    = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,
	.bInterfaceNumber   = 1,
	.bAlternateSetting  = 0,
	.bNumEndpoints	    = 2,
	.bInterfaceClass    = USB_CLASS_VENDOR,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface	    = 0,

	.endpoint	    = usb_full_speed_config1_endpoints
};

DESCRIPTOR
const struct usb_interface_descriptor usb_configuration_high_speed_iface = {
	.bLength	    = USB_DT_INTERFACE_SIZE,
	.bDescriptorType    = USB_DT_INTERFACE,
	.bInterfaceNumber   = 1,
	.bAlternateSetting  = 0,
	.bNumEndpoints	    = 2,
	.bInterfaceClass    = USB_CLASS_VENDOR,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface	    = 0,

	.endpoint	    = usb_high_speed_config1_endpoints,
};

DESCRIPTOR
const struct usb_interface interfaces[] = {
	{
	.num_altsetting	    = 0x01,
	.altsetting	    = &usb_configuration_full_speed_iface,
	},
	{
	.num_altsetting	    = 0x01,
	.altsetting	    = &usb_configuration_high_speed_iface,
	},
};

DESCRIPTOR
const struct usb_config_descriptor usb_descriptor_configuration_full_speed = {
	.bLength	     = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType     = USB_DT_CONFIGURATION,
	.wTotalLength	     = 32,
	.bNumInterfaces	     = 0x01,
	.bConfigurationValue = 0x01,
	.iConfiguration	     = 0x03,
	.bmAttributes	     = 0x80,
	.bMaxPower	     = 250,
	.interface	     = &interfaces[0]
};

DESCRIPTOR
const struct usb_config_descriptor usb_descriptor_configuration_high_speed = {
	.bLength	     = USB_DT_CONFIGURATION_SIZE,
	.bDescriptorType     = USB_DT_CONFIGURATION,
	.wTotalLength	     = 32,
	.bNumInterfaces	     = 0x01,
	.bConfigurationValue = 0x01,
	.iConfiguration	     = 0x03,
	.bmAttributes	     = 0x80,
	.bMaxPower	     = 250,
	.interface	     = &interfaces[1]
};

DESCRIPTOR
const struct usb_string_descriptor usb_descriptor_string_languages = {
	.bLength              = 0x04,
	.bDescriptorType      = USB_DT_STRING,
	.wData                = { USB_STRING_LANGID }
};

DESCRIPTOR
const char* const usb_strings[] = {
	"Great Scott Gadgets",
	"HackRF",
	"Transceiver",
	NULL
};
