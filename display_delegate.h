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

#ifndef DISPLAY_DELEGATE_H_
# define DISPLAY_DELEGATE_H_

#include <eglcontent/display_delegate.h>

#include <EGL/eglplatform.h>

class RpiDisplayDelegate: public EGLContent::DisplayDelegate {

  public:

    RpiDisplayDelegate(int width, int height);
    ~RpiDisplayDelegate();

    EGLNativeDisplayType CreateNativeDisplay() override;
    void ReleaseNativeDisplay() override;

    EGLNativeWindowType CreateNativeWindow() override;
    void ReleaseNativeWindow() override;

    bool Resize(int size, int height, float scale_factor) override;

    void GetSize(int* width, int* height) override;

    const char* EGLLibraryName() override;
    const char* GLESLibraryName() override;

  private:

    int width_;
    int height_;

    EGL_DISPMANX_WINDOW_T native_window_;
    DISPMANX_DISPLAY_HANDLE_T dispmanx_display_;
};

#endif /* !DISPLAY_DELEGATE.H */
