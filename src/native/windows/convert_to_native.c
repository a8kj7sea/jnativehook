/* JNativeHook: Global keyboard and mouse hooking for Java.
 * Copyright (C) 2006-2013 Alexander Barker.  All Rights Received.
 * http://code.google.com/p/jnativehook/
 *
 * JNativeHook is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JNativeHook is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <nativehook.h>

#include <w32api.h>
#define WINVER Windows2000
#define _WIN32_WINNT WINVER
#include <windows.h>

#include "convert_to_native.h"
#include "win_input_helpers.h"

unsigned int convert_to_native_key(unsigned int virtual_keycode) {
	UINT native_keycode = MapVirtualKey(virtual_keycode, MAPVK_VK_TO_VSC);

	return native_keycode;
}

unsigned int convert_to_native_button(unsigned short int virtual_button) {
	unsigned short int native_button;

	switch (virtual_button) {
		case MOUSE_BUTTON1:
		case MOUSE_BUTTON2:
			native_button = virtual_button;
			break;
			
		case MOUSE_BUTTON3:
		case MOUSE_BUTTON4:
		case MOUSE_BUTTON5:
			native_button = virtual_button + 1;
			break;

		default:
		case MOUSE_NOBUTTON:
			native_button = 0;
			break;
	}

	return native_button;
}

unsigned short int convert_to_native_mask(unsigned short int virtual_mask) {
	unsigned short int native_mask = 0x0000;

	if (virtual_mask & MASK_SHIFT_L)	native_mask |= MOD_LSHIFT;
	if (virtual_mask & MASK_CTRL_L)		native_mask |= MOD_LCONTROL;
	if (virtual_mask & MASK_META_L)		native_mask |= MOD_LWIN;
	if (virtual_mask & MASK_ALT_L)		native_mask |= MOD_LALT;

	if (virtual_mask & MASK_SHIFT_R)	native_mask |= MOD_RSHIFT;
	if (virtual_mask & MASK_CTRL_R)		native_mask |= MOD_RCONTROL;
	if (virtual_mask & MASK_META_R)		native_mask |= MOD_RWIN;
	if (virtual_mask & MASK_ALT_R)		native_mask |= MOD_RALT;

	if (virtual_mask & MASK_BUTTON1)	native_mask |= MOD_RBUTTON;
	if (virtual_mask & MASK_BUTTON2)	native_mask |= MOD_LBUTTON;
	if (virtual_mask & MASK_BUTTON3)	native_mask |= MOD_MBUTTON;
	if (virtual_mask & MASK_BUTTON4)	native_mask |= MOD_XBUTTON1;
	if (virtual_mask & MASK_BUTTON5)	native_mask |= MOD_XBUTTON2;

	return native_mask;
}
