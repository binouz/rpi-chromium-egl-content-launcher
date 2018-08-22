// Copyright 2018 Aubin REBILLAT
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "display_delegate.h"

#include <EGL/egl.h>
#include <bcm_host.h>

#include <iostream>

static std::string kLibEGLName =  "libEGL.so.1";
static std::string kLibGLESName = "libGLESv2.so.2";

RpiDisplayDelegate::RpiDisplayDelegate(int width, int height)
  : width_(width), height_(height) {
}

RpiDisplayDelegate::~RpiDisplayDelegate() {
}

EGLNativeDisplayType RpiDisplayDelegate::CreateNativeDisplay() {
  bcm_host_init();
  return EGL_DEFAULT_DISPLAY;
}

void RpiDisplayDelegate::ReleaseNativeDisplay() {
}

EGLNativeWindowType RpiDisplayDelegate::CreateNativeWindow() {
  DISPMANX_UPDATE_HANDLE_T dispmanx_update;
  VC_RECT_T dst_rect;
  VC_RECT_T src_rect;;

  if (graphics_get_display_size(
        DISPMANX_ID_HDMI,
        (uint32_t *)&(native_window_.width),
        (uint32_t *)&(native_window_.height)) < 0)
  {
    std::cout << "RpiDisplayDelegate::CreateNativeWindow : graphics_get_display_size failed" << std::endl;
    native_window_.width = 1280;
    native_window_.height = 720;
  }

  std::cout << "RpiDisplayDelegate::CreateNativeWindow : width=" << native_window_.width << " height=" << native_window_.height << std::endl;

  dst_rect.x = 0;
  dst_rect.y = 0;
  dst_rect.width = native_window_.width;
  dst_rect.height = native_window_.height;

  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.width = native_window_.width << 16;
  src_rect.height = native_window_.height << 16;

  dispmanx_display_ = vc_dispmanx_display_open(DISPMANX_ID_HDMI);
  dispmanx_update = vc_dispmanx_update_start(0);

  native_window_.element = vc_dispmanx_element_add(
    dispmanx_update,
    dispmanx_display_,
    1,
    &dst_rect,
    0,
    &src_rect,
    DISPMANX_PROTECTION_NONE,
    NULL,
    NULL,
    DISPMANX_NO_ROTATE);

  vc_dispmanx_update_submit_sync(dispmanx_update);

  return &native_window_;
}

void RpiDisplayDelegate::ReleaseNativeWindow() {
}

bool RpiDisplayDelegate::Resize(int size, int height, float scale_factor) {
  return true;
}

void RpiDisplayDelegate::GetSize(int* width, int* height) {
  *width = width_;
  *height = height_;
}

const char *RpiDisplayDelegate::EGLLibraryName() {
  return kLibEGLName.c_str();
}

const char *RpiDisplayDelegate::GLESLibraryName() {
  return kLibGLESName.c_str();
}
