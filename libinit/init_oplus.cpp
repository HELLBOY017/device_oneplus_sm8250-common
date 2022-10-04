/*
 * Copyright (C) 2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/system_properties.h>
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor.",
    "vendor_dlkm."
};

/*
 * SetProperty does not allow updating read only properties and as a result
 * does not work for our use case. Write "property_override" to do practically
 * the same thing as "SetProperty" without this restriction.
 */

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void set_ro_build_prop(const std::string &prop, const std::string &value, bool product = true) {
    string prop_name;

    for (const auto &source : ro_props_default_source_order) {
        if (product)
            prop_name = "ro.product." + source + prop;
        else
            prop_name = "ro." + source + "build." + prop;

        property_override(prop_name.c_str(), value.c_str());
    }
}

void vendor_load_properties() {

  string model;
  string device;
  string name;

/*
 * Only for read-only properties. Properties that can be wrote to more
 * than once should be set in a typical init script (e.g. init.oplus.hw.rc)
 * after the original property has been set.
 */

  auto prj_version = std::stoi(GetProperty("ro.boot.prj_version", "0"));
  auto rf_version = std::stoi(GetProperty("ro.boot.rf_version", "0"));
  property_override("ro.build.fingerprint", "google/raven/raven:13/TP1A.221005.002/9012097:user/release-keys");

  switch(prj_version){
  	/* OnePlus 8 */
    case 19821:
	device = "OnePlus8";
	property_override("bluetooth.device.default_name", "OnePlus 8");
	property_override("ro.vendor.usb.name", "OnePlus 8");
      switch (rf_version){
          /* China */
        case 11:
          name = "OnePlus8";
          model = "IN2010";
          break;
        case 13:
          /* India */
          name = "OnePlus8_IND";
          model = "IN2011";
          break;
        case 14:
          /* Europe */
          name = "OnePlus8_EEA";
          model = "IN2013";
          break;
        case 15:
          /* Global / US Unlocked */
          name = "OnePlus8";
          model = "IN2015";
          break;
        default:
          /* Generic */
          name = "OnePlus8";
          model = "IN2015";
          break;
      }
      break;
        /* OnePlus 8 T-Mobile */
    case 19855:
	device = "OnePlus8";
	property_override("bluetooth.device.default_name", "OnePlus 8");
	property_override("ro.vendor.usb.name", "OnePlus 8");
      switch (rf_version){
            /* T-Mobile */
        case 12:
          name = "OnePlus8_TMO";
          model = "IN2017";
          break;
            /* Generic */
        default:
          name = "OnePlus8";
          model = "IN2015";
          break;
      }
      break;
        /* OnePlus 8 Verizon */
    case 19867:
	device = "OnePlus8";
	property_override("bluetooth.device.default_name", "OnePlus 8");
	property_override("ro.vendor.usb.name", "OnePlus 8");
      switch (rf_version){
            /* T-Mobile */
        case 25:
          name = "OnePlus8";
          model = "IN2019";
          break;
            /* Generic */
        default:
          name = "OnePlus8";
          model = "IN2015";
          break;
      }
      break;
        /* OnePlus 8 Pro */
    case 19811:
	device = "OnePlus8Pro";
	property_override("bluetooth.device.default_name", "OnePlus 8 Pro");
	property_override("ro.vendor.usb.name", "OnePlus 8 Pro");
      switch (rf_version){
          /* China */
        case 11:
          name = "OnePlus8Pro";
          model = "IN2020";
          break;
        case 13:
          /* India */
          name = "OnePlus8Pro_IND";
          model = "IN2021";
          break;
        case 14:
          /* Europe */
          name = "OnePlus8Pro_EEA";
          model = "IN2023";
          break;
        case 15:
          /* Global / US Unlocked */
          name = "OnePlus8Pro";
          model = "IN2025";
          break;
        default:
          /* Generic */
          name = "OnePlus8Pro";
          model = "IN2025";
          break;
      }
      break;
       /* OnePlus 8T */
    case 19805:
	device = "OnePlus8T";
	property_override("bluetooth.device.default_name", "OnePlus 8T");
	property_override("ro.vendor.usb.name", "OnePlus 8T");
      switch (rf_version){
           /* China */
        case 11:
          name = "OnePlus8T";
          model = "KB2000";
          break;
            /* India */
        case 13:
          name = "OnePlus8T_IND";
          model = "KB2001";
          break;
            /* Europe */
        case 14:
          name = "OnePlus8T_EEA";
          model = "KB2003";
          break;
            /* Global / US Unlocked */
        case 15:
          name = "OnePlus8T";
          model = "KB2005";
          break;
            /* Generic */
        default:
          name = "OnePlus8T";
          model = "KB2005";
          break;
      }
      break;
       /* OnePlus 8T T-Mobile */
    case 20809:
	device = "OnePlus8T";
	property_override("bluetooth.device.default_name", "OnePlus 8T");
	property_override("ro.vendor.usb.name", "OnePlus 8T");
      switch (rf_version){
            /* T-Mobile */
        case 12:
          name = "OnePlus8T_TMO";
          model = "KB2007";
          break;
            /* Generic */
        default:
          name = "OnePlus8T";
          model = "KB2005";
          break;
      }
      break;
      	/* OnePlus 9R */
   case 20828:
	device = "OnePlus9R";
	property_override("bluetooth.device.default_name", "OnePlus 9R");
	property_override("ro.vendor.usb.name", "OnePlus 9R");
      switch (rf_version){
            /* China */
      case 11:
          name = "OnePlus9R";
          model = "LE2100";
          break;
            /* India */
      case 13:
          name = "OnePlus9R_IND";
          model = "LE2101";
          break;
            /* Generic */
      default:
          name = "OnePlus9R_IND";
          model = "LE2101";
          break;
      }
      break;
   case 20838:
	device = "OnePlus9R";
	property_override("bluetooth.device.default_name", "OnePlus 9R");
	property_override("ro.vendor.usb.name", "OnePlus 9R");
      switch (rf_version){
            /* China */
      case 11:
          name = "OnePlus9R";
          model = "LE2100";
          break;
            /* India */
      case 13:
          name = "OnePlus9R_IND";
          model = "LE2101";
          break;
            /* Generic */
      default:
          name = "OnePlus9R_IND";
          model = "LE2101";
          break;
      }
      break;
   }

    set_ro_build_prop("device", device);
    set_ro_build_prop("model", model);
    set_ro_build_prop("name", name);
    set_ro_build_prop("product", model, false);
}
