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

#define USB_WORD(x)	(x & 0xFF), ((x >> 8) & 0xFF)

#define USB_MAX_PACKET0     	(64)
#define USB_MAX_PACKET_BULK_FS	(64)
#define USB_MAX_PACKET_BULK_HS	(512)

#define USB_BULK_IN_EP_ADDR 	(0x81)
#define USB_BULK_OUT_EP_ADDR 	(0x02)

#define USB_STRING_LANGID		(0x0409)

uint8_t usb_descriptor_device[] = {
	18,				   // bLength
	USB_DESCRIPTOR_TYPE_DEVICE,	   // bDescriptorType
	USB_WORD(0x0200),		   // bcdUSB
	0x00,				   // bDeviceClass
	0x00,				   // bDeviceSubClass
	0x00,				   // bDeviceProtocol
	USB_MAX_PACKET0,		   // bMaxPacketSize0
	USB_WORD(USB_VENDOR_ID),	   // idVendor
	USB_WORD(USB_PRODUCT_ID),	   // idProduct
	USB_WORD(0x0100),		   // bcdDevice
	0x01,				   // iManufacturer
	0x02,				   // iProduct
	0x00,				   // iSerialNumber
	0x01				   // bNumConfigurations
};

uint8_t usb_descriptor_device_qualifier[] = {
	10,					// bLength
	USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,	// bDescriptorType
	USB_WORD(0x0200),			// bcdUSB
	0x00,					// bDeviceClass
	0x00,					// bDeviceSubClass
	0x00,					// bDeviceProtocol
	64,					// bMaxPacketSize0
	0x01,					// bNumOtherSpeedConfigurations
	0x00					// bReserved
};

uint8_t usb_descriptor_configuration_full_speed[] = {
	9,					// bLength
	USB_DESCRIPTOR_TYPE_CONFIGURATION,	// bDescriptorType
	USB_WORD(32),				// wTotalLength
	0x01,					// bNumInterfaces
	0x01,					// bConfigurationValue
	0x03,					// iConfiguration
	0x80,					// bmAttributes: USB-powered
	250,					// bMaxPower: 500mA

	9,							// bLength
	USB_DESCRIPTOR_TYPE_INTERFACE,		// bDescriptorType
	0x00,							// bInterfaceNumber
	0x00,							// bAlternateSetting
	0x02,							// bNumEndpoints
	0xFF,							// bInterfaceClass: vendor-specific
	0xFF,							// bInterfaceSubClass
	0xFF,							// bInterfaceProtocol: vendor-specific
	0x00,							// iInterface

	7,							// bLength
	USB_DESCRIPTOR_TYPE_ENDPOINT,		// bDescriptorType
	USB_BULK_IN_EP_ADDR,				// bEndpointAddress
	0x02,							// bmAttributes: BULK
	USB_WORD(USB_MAX_PACKET_BULK_FS),	// wMaxPacketSize
	0x00,							// bInterval: no NAK

	7,							// bLength
	USB_DESCRIPTOR_TYPE_ENDPOINT,		// bDescriptorType
	USB_BULK_OUT_EP_ADDR,			// bEndpointAddress
	0x02,							// bmAttributes: BULK
	USB_WORD(USB_MAX_PACKET_BULK_FS),	// wMaxPacketSize
	0x00,							// bInterval: no NAK

	0,									// TERMINATOR
};

uint8_t usb_descriptor_configuration_high_speed[] = {
	9,							// bLength
	USB_DESCRIPTOR_TYPE_CONFIGURATION,	// bDescriptorType
	USB_WORD(32),						// wTotalLength
	0x01,							// bNumInterfaces
	0x01,							// bConfigurationValue
	0x03,							// iConfiguration
	0x80,							// bmAttributes: USB-powered
	250,							// bMaxPower: 500mA

	9,							// bLength
	USB_DESCRIPTOR_TYPE_INTERFACE,		// bDescriptorType
	0x00,							// bInterfaceNumber
	0x00,							// bAlternateSetting
	0x02,							// bNumEndpoints
	0xFF,							// bInterfaceClass: vendor-specific
	0xFF,							// bInterfaceSubClass
	0xFF,							// bInterfaceProtocol: vendor-specific
	0x00,							// iInterface

	7,							// bLength
	USB_DESCRIPTOR_TYPE_ENDPOINT,		// bDescriptorType
	USB_BULK_IN_EP_ADDR,				// bEndpointAddress
	0x02,							// bmAttributes: BULK
	USB_WORD(USB_MAX_PACKET_BULK_HS),	// wMaxPacketSize
	0x00,							// bInterval: no NAK

	7,								// bLength
	USB_DESCRIPTOR_TYPE_ENDPOINT,		// bDescriptorType
	USB_BULK_OUT_EP_ADDR,			// bEndpointAddress
	0x02,							// bmAttributes: BULK
	USB_WORD(USB_MAX_PACKET_BULK_HS),	// wMaxPacketSize
	0x00,							// bInterval: no NAK

	0,									// TERMINATOR
};

struct usb_string_descriptor usb_descriptor_string_languages = {
	.bLength              = 0x04,
	.bDescriptorType      = USB_DT_STRING,
	.wData                = { USB_STRING_LANGID }
};

char* const usb_strings[] = {
	"Great Scott Gadgets",
	"HackRF",
	"Transceiver",
	NULL
};
